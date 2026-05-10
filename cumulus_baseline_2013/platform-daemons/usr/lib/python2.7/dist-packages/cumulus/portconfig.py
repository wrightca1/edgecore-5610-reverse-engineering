#
# Copyright 2012.  Cumulus Networks, Inc.
#
# portconfig.py --
#     Generate port configuration fragments.
#

import ConfigParser
import StringIO
import sys
import subprocess
import syslog
from itertools import groupby

import platformdb
import sfp

class DecodeSysEEPROM:
    '''
    Helper for decode-syseeprom.  Supports a dummy mode for testing.
    '''
    def __init__(self, dummy=False):
        self.dummy = dummy

    @property
    def macaddr(self):
        if self.dummy:
            return 'ff:ff:ff:ff:ff:00'
        else:
            return subprocess.check_output(('/usr/cumulus/bin/decode-syseeprom', '-a'))

    @property
    def macrange(self):
        if self.dummy:
            return 0xff
        else:
            mrange = subprocess.check_output(('/usr/cumulus/bin/decode-syseeprom', '-r'))

        try:
            mrange = int(mrange)
        except ValueError:
            raise RuntimeError('error: decode-syseeprom -r returned bogus value: %s' % mrange)

        return mrange

class IPRoute2:
    '''
    Helper for iproute2.  Supports a dummy mode for testing.
    '''
    def __init__(self, dummy=False):
        self.dummy = dummy

    def run(self, args):
        if self.dummy:
            return str()
        else:
            return subprocess.check_output([ 'ip' ] + args)

class Config:
    '''
    Base class for port configuration.  Understands ports.conf format and how
    to lookup a platform.
    '''
    def __init__(self, platform, revision=None, verbose=False, exploded=False, dummy=False):
        self.platform = platformdb.lookup(platform, revision)()
        self.verbose = verbose
        self.exploded = exploded
        self.dummy = dummy

        self.eeprom = DecodeSysEEPROM(dummy=dummy)
        self.iproute2 = IPRoute2(dummy=dummy)

        self.ports = []
        self.macbase = []
        self.macrange = self.eeprom.macrange
        for byte in self.eeprom.macaddr.split(':'):
            self.macbase.append(int(byte, 16))
        self.macmode = 'standard'

    def config(self, config):
        '''
        Read a ports.conf config from a string

        configfile - config file string
        '''

        # add a default section so we can use ConfigParser
        configStr = '[ports]\n' + config
        configFP = StringIO.StringIO(configStr)

        parser = ConfigParser.RawConfigParser()
        parser.readfp(configFP)

        self.config_map = dict(parser.items('ports'))

    def read_config(self, configfile):
        '''
        Read a ports.conf config file and store its key/value pairs in a dict.

        configfile - config file path
        '''

        if configfile == 'hw_desc' :
            self.hw_desc = self.platform.switch.chip.get_config(configfile)

        elif configfile == 'rc.forwarding' :
            self.rc_forwarding = self.platform.switch.chip.get_config(configfile)

        elif configfile == 'datapath.conf' :
            self.datapath_conf = self.platform.switch.chip.get_config(configfile)

        elif configfile == 'sdk.bcm' :
            self.sdk_bcm = self.platform.switch.chip.get_config(configfile)

        else :
            self.config(open(configfile, 'r').read())

    def set_macmode(self, mode):
        '''
        Set the default mac mode for a configuration
        '''
        self.macmode = mode

    def makemacaddr(self, inmac, index):

        if inmac is None:
            return None

        curmac = [0] * 6
        # Increment the MAC (only the non-OUI part).
        ext = (inmac[5] | (inmac[4] << 8) | (inmac[3] << 16))
        ext += index
        if (ext & 0xff000000):
            sys.stdout.write('Tried to carry into OUI.\n')
            return 0
        curmac[5] = ext & 0xff
        curmac[4] = (ext >> 8) & 0xff
        curmac[3] = (ext >> 16) & 0xff
        curmac[2] = inmac[2]
        curmac[1] = inmac[1]
        curmac[0] = inmac[0]
        return curmac

    def destroytaps(self, interface_set):
        for i in interface_set:
            cmd = 'tuntap del dev %s mode tap' % i
            self.iproute2.run(cmd.split())
        interface_set.clear()

    def maketap(self, portname, index, interface_set):
        if portname in interface_set:
            interface_set.remove(portname)
        else:
            if self.macmode == 'l3-only' :
                index = 0
            themac = self.makemacaddr(self.macbase, index)
            if themac is not None:
                cmd = 'tuntap add dev %s mode tap one_queue' % portname
                self.iproute2.run(cmd.split())
                cmd = 'link set dev %s address %x:%x:%x:%x:%x:%x' % \
                       (portname, themac[0], themac[1], themac[2], themac[3],
                        themac[4], themac[5])
                self.iproute2.run(cmd.split())

class CPLDConfig(Config):
    def set_hardware(self):
        '''
        Write changes to hardware.  Typically sets values in a CPLD.
        '''
        raise NotImplementedError

class ConfiguredPort:
    '''
    Represents a port configured in a specific mode.
    '''
    def __init__(self, mode, mac_index):
        self.mode = mode
        self.mac_index = mac_index

    @property
    def label(self):
        '''
        The text printed on the front of the switch.
        '''
        raise NotImplementedError

    @property
    def speed(self):
        '''
        The port speed in gigabits/sec.
        '''
        raise NotImplementedError

    @property
    def num_logical_ports(self):
        '''
        The number of logical ports (swp interfaces) for the port.
        '''
        raise NotImplementedError

    @property
    def max_logical_ports(self):
        '''
        The maximum number of logical ports (swp interfaces) for the port.
        '''
        raise NotImplementedError

    @property
    def leds(self):
        raise NotImplementedError

    @property
    def linux_prefix(self):
        if self.physical_port.is_fabric:
            return '_'
        else:
            return 'swp'

    def set_hardware(self):
        '''
        Set hardware configuration
        '''
        raise NotImplementedError

    @property
    def gang_label(self):
        '''
        Gang Identifier for Ganged ports
        Port Label for unganged port
        Assumption: Port numbering starts at swp1
        '''
        if self.mode == '40G/4':
            return str((((int(self.label)-1)/4) * 4) + 1)
        else:
            return self.label

    @property
    def serdes_if_type(self):
        raise NotImplementedError

class BCMConfiguredPort(ConfiguredPort):
    '''
    Broadcom specific port configuration implementation.
    '''
    def __init__(self, mode, physical_port, mac_index):
        ConfiguredPort.__init__(self, mode, mac_index)
        self.physical_port = physical_port

    @property
    def label(self):
        return self.physical_port.label

    @property
    def oversub(self):
        return self.physical_port.oversub

    @property
    def speed(self):
        return self.physical_port.speed(self.mode)

    @property
    def num_logical_ports(self):
        return self.physical_port.num_logical_ports(self.mode)

    @property
    def max_logical_ports(self):
        return self.physical_port.max_logical_ports

    @property
    def num_physical_ports(self):
        return self.physical_port.num_physical_ports(self.mode)

    @property
    def num_phys(self):
        return self.physical_port.num_phys

    @property
    def enable_auto_neg(self):
        return self.physical_port.phy_layer in ('10GBaseT', '1GBaseT')

    def hw_intf_num(self, sub):
        '''
        Return the hardware interface number for the given sub-interface (The
        number in hg0).  Never mapped.
        '''
        return int(self.physical_port.hw_intf_num(self.mode, sub))

    def base_hw_intf_num(self, sub):
        '''
        Return the lowest hardware interface number for the given sub-interface
        Never mapped.
        '''
        return int(self.physical_port.base_hw_intf_num(self.mode, sub))

    def bcm_intf_prefix(self, sub):
        '''
        Return the Broadcom interface prefix for the given sub-interface (xe,
        ge, etc...).  This is the interface name after configuration (hg may
        become xe here).
        '''
        # assume 'xe' ports by default
        prefix = self.physical_port.hw_intf_prefix(self.mode, sub)[:2]
        if prefix == 'hg':
            return 'xe'
        else:
            return prefix

    def bcm_intf_num(self, sub):
        '''
        Return the Broadcom interface number for the given sub-interface (the
        number in "xe0")
        '''
        return self.hw_intf_num(sub)

    def bcm_intf(self, sub):
        '''
        Return the full Broadcom name for the sub-interface (xe0, ge0, etc...)
        '''
        return '%s%u' % (self.bcm_intf_prefix(sub), self.bcm_intf_num(sub))

    def bcm_pbmp(self, sub):
        '''
        Return the Broadcom port bitmap mask for the sub-interface.
        '''
        return self.physical_port.hw_pbmp(self.mode, sub)

    def phy_addr(self, sub):
        return self.physical_port.phy_addrs[sub]

    @property
    def prim_offset(self):
        return self.physical_port.prim_offset

    @property
    def phy_id1(self):
        return self.physical_port.phy_id1

    @property
    def sys_interface(self):
        return self.physical_port.sys_interface

    def phy_type(self, sub):
        if self.physical_port.phy_types is not None:
            return self.physical_port.phy_types[sub]
        else:
            return None

    def phy_autodetect(self, sub):
        return self.physical_port.phy_autodetect(self.mode, sub)

    def set_leds(self, led_port, sub, led_index_list):
        return self.physical_port.set_leds(self.mode, led_port, sub, led_index_list)

    def set_hardware(self, platform):
        self.physical_port.set_hardware(platform, self.mode)

    def hw_port_num(self, sub):
        return self.physical_port.hw_port_num(self.mode, sub)

    @property
    def leds(self):
        return self.physical_port.leds

    @property
    def unit(self):
        return self.physical_port.unit

    @property
    def rx_polarity_flip(self):
        return self.physical_port.rx_polarity_flip

    @property
    def tx_polarity_flip(self):
        return self.physical_port.tx_polarity_flip

    def rx_logical_polarity_flip(self, sub):
        return self.physical_port.rx_logical_polarity_flip(self.mode, sub)

    def tx_logical_polarity_flip(self, sub):
        return self.physical_port.tx_logical_polarity_flip(self.mode, sub)

    @property
    def is_fabric(self):
        return self.physical_port.is_fabric

    @property
    def rx_lane_map(self):
        return self.physical_port.rx_lane_map

    @property
    def tx_lane_map(self):
        return self.physical_port.tx_lane_map

    @property
    def pre_emphasis(self):
        return self.physical_port.pre_emphasis

    @property
    def drv_current(self):
        return self.physical_port.drv_current

    @property
    def pre_drv_current(self):
        return self.physical_port.pre_drv_current

    @property
    def phy_init(self):
        return self.physical_port.phy_init

    @property
    def serdes_if_type(self):
        return self.physical_port.serdes_if_type(self.speed)

class BCMConfiguredMappedPort(BCMConfiguredPort):
    '''
    A port remapped using portmap_ directives
    '''
    def __init__(self, mode, physical_port, port_base, mac_index):
        BCMConfiguredPort.__init__(self, mode, physical_port, mac_index)
        self.port_base = port_base

    def bcm_pbmp(self, sub):
        '''
        Mapped ports are sequential based on the port_base
        '''
        return 1 << (self.port_base + sub)

    def bcm_intf_num(self, sub):
        '''
        Return the mapped BCM interface number for the sub-interface.
        '''
        return (self.port_base + sub) - 1


class BCMConfig(CPLDConfig):
    '''
    Broadcom SDK configuration implementation
    '''

    # Interface types taken from bcm-sdk/include/shared/port.h
    serdes_if_type_map = {'XGMII':6, 'SFI':9, 'XFI':10, 'SR4':28}

    def __init__(self, platform, revision=None, verbose=False, exploded=False, dummy=False):
        CPLDConfig.__init__(self, platform, revision, verbose, exploded, dummy=dummy)
        self.read_config('hw_desc')
        self.read_config('rc.forwarding')
        self.read_config('datapath.conf')
        self.read_config('sdk.bcm')

    def config(self, config):
        CPLDConfig.config(self, config)
        max_mac_index = self._calculate_configuration()
        self._calculate_leds()
        if max_mac_index > self.macrange :
            # default to l3 only mode as we do not have enough mac's
            syslog.syslog('Not enough macs in platform, falling to l3-only')
            self.set_macmode('l3-only')

    def _calculate_configuration(self):
        '''
        Calculate port mappings.  Derives internal state, but does not implment
        changes in hardware or configuration files.
        '''
        self.ports = []
        ports_by_prefix = {}

        # create config objects for every port
        mac_index = 0
        mapped_portnums = {}
        for port in self.platform.switch.ports:
            mapped_portnum = mapped_portnums.get(port.unit, 1)
            mode = self.config_map.get(port.label, port.default_mode)
            if self.platform.switch.chip.portmap_capable is True:
                cp = BCMConfiguredMappedPort(mode, port, mapped_portnum, mac_index)
                mapped_portnum += cp.num_logical_ports
            else:
                cp = BCMConfiguredPort(mode, port, mac_index)
            mac_index += port.max_logical_ports
            self.ports.append(cp)
            mapped_portnums[port.unit] = mapped_portnum
        return (mac_index)

    def _calculate_leds(self):
        '''
        Calculate led programs for switch chip controlled LEDs
        '''
        self._led_programs = {}

        controllers = set([ x.leds[0] for x in self.ports if x.leds is not None ])

        # Create an LED program for each controller in the platform
        for controller in sorted(controllers):
            try:
                ledup = self.platform.switch.ledup[controller]()
            except TypeError:
                ledup = self.platform.switch.ledup()

            ports = [ x for x in self.ports if (x.leds is not None and x.leds[0] == controller) ]
            ledup.set_ports(ports)

            self._led_programs[controller] = ledup

    def set_hardware(self):
        for port in self.ports:
            port.set_hardware(self.platform)

    @property
    def led_chains(self):
        return self._led_programs.keys()

    @property
    def led_asm(self):
        return dict([ (x, self._led_programs[x].asm) for x in self._led_programs.keys() ])

    @property
    def led_hex(self):
        return dict([ (x, self._led_programs[x].hex) for x in self._led_programs.keys() ])

    @property
    def bcm_pbmp(self):
        pbmp = []

        pbmps = {}
        valid = {}
        oversub = {}
        for port in self.ports:
            for sub in range(port.num_logical_ports):
                prefix = '%s.%u' % (port.bcm_intf_prefix(sub), port.unit)
                bits = pbmps.get(prefix, 0) | port.bcm_pbmp(sub)
                pbmps[prefix] = bits
                valid[port.unit] = valid.get(port.unit,
                        self.platform.switch.chip.base_pbmp) | bits
                if port.oversub:
                    oversub[port.unit] = oversub.get(port.unit, 0) | bits

        for intf in pbmps.keys():
            pbmp.append('pbmp_xport_%s=0x%x' % (intf, pbmps[intf]))

        for unit in valid.keys():
            pbmp.append('pbmp_valid.%u=0x%x' % (unit, valid[unit]))
            if unit in oversub:
                pbmp.append('pbmp_oversubscribe.%u=0x%x' % (unit, oversub[unit]))

        return '\n'.join(pbmp)

    @property
    def portmap(self):
        if self.platform.switch.chip.portmap_capable is not True:
            raise RuntimeError('platform: %s is not portmap capable' % self.platform.name)

        portmap = []

        map_nums = {}
        for port in self.ports:
            for sub in range(port.num_logical_ports):
                map_num = map_nums.get(port.unit, 1)
                portmap.append('portmap_%u.%u=%u:%s' % (map_num, port.unit, port.hw_intf_num(sub) + 1,
                                                        port.speed))
                if port.rx_polarity_flip is not None:
                    if port.rx_polarity_flip is True:
                        portmap.append('phy_xaui_rx_polarity_flip_%u.%u=1' % (map_num, port.unit))
                    else:
                        portmap.append('phy_xaui_rx_polarity_flip_%u.%u=0x%04x' % (map_num, port.unit,
                                port.rx_logical_polarity_flip(sub)))
                if port.tx_polarity_flip is not None:
                    if port.tx_polarity_flip is True:
                        portmap.append('phy_xaui_tx_polarity_flip_%u.%u=1' % (map_num, port.unit))
                    else:
                        portmap.append('phy_xaui_tx_polarity_flip_%u.%u=0x%04x' % (map_num, port.unit,
                                port.tx_logical_polarity_flip(sub)))
                if port.rx_lane_map is not None:
                    portmap.append('xgxs_rx_lane_map_%u.%u=0x%04x' %
                                   (map_num, port.unit, port.rx_lane_map))
                if port.tx_lane_map is not None:
                    portmap.append('xgxs_tx_lane_map_%u.%u=0x%04x' %
                                   (map_num, port.unit, port.tx_lane_map))
                map_nums[port.unit] = map_num + 1

        return '\n'.join(portmap)

    @property
    def port_emphasis(self):
        port_emp = []
        map_nums = {}
        for port in self.ports:
            for sub in range(port.num_logical_ports):
                map_num = map_nums.get(port.unit, 1)
                #for 40G we need to set emphasis for all 4 lanes, for 10G we 
                #set just one value for the entire port which is mapped by 
                #the sdk to the associated lane.
                if port.mode == '40G':
                    lane_num = 4
                else:
                    lane_num = 1
                if port.pre_emphasis is not None:
                    if lane_num > 1:
                        for lane in range(lane_num):
                            port_emp.append(
                                'serdes_preemphasis_lane%1d_%u.%u=0x%04x' % 
                                (lane, map_num, port.unit, 
                                port.pre_emphasis[lane]))
                    else:
                        port_emp.append(
                            'serdes_preemphasis_%u.%u=0x%04x' % 
                            (map_num, port.unit, port.pre_emphasis[sub]))

                if port.drv_current is not None:
                    if lane_num > 1:
                        for lane in range(lane_num):
                            port_emp.append(
                                'serdes_driver_current_lane%1d_%u.%u=0x%x' % 
                                (lane, map_num, port.unit, 
                                port.drv_current[lane]))
                    else:
                        port_emp.append(
                            'serdes_driver_current_%u.%u=0x%04x' % 
                            (map_num, port.unit, port.drv_current[sub]))

                if port.pre_drv_current is not None:
                    if lane_num > 1:
                        for lane in range(lane_num):
                            port_emp.append(
                                'serdes_pre_driver_current_lane%1d_%u.%u=0x%x' % 
                                (lane, map_num, port.unit, 
                                port.pre_drv_current[lane]))
                    else:
                        port_emp.append(
                            'serdes_pre_driver_current_%u.%u=0x%04x' % 
                            (map_num, port.unit, port.pre_drv_current[sub]))

                map_nums[port.unit] = map_num + 1
        return '\n'.join(port_emp)

    @property
    def port_init(self):

        port_init = []

        port_init.append('#   set full duplex for all ports')
        port_init.append('port_init_duplex=1')

        for port in self.ports:
            for sub in range(port.num_logical_ports):
                port_init.append('port_init_speed_%s=%s000' % (port.bcm_intf(sub), port.speed))
                if port.enable_auto_neg:
                    port_init.append('port_init_autoneg_%s=1' % (port.bcm_intf(sub)))
                else:
                    port_init.append('port_init_autoneg_%s=0' % (port.bcm_intf(sub)))
                if port.serdes_if_type is not None:
                    port_init.append('serdes_if_type_%s=%u #%s' %
                        (port.bcm_intf(sub), BCMConfig.serdes_if_type_map[port.serdes_if_type],
                            port.serdes_if_type))

        return '\n'.join(port_init)

    @property
    def phys(self):
        phys = []

        for port in self.ports:
            for sub in range(port.num_logical_ports):
                if port.phy_type(sub) is not None and not port.phy_autodetect(sub):
                    phys.append('phy_%s_%s=1' % (port.phy_type(sub), port.bcm_intf(sub)))

        return ('\n').join(phys)

    @property
    def phy_addrs(self):
        addrs = []

        for port in self.ports:
            for sub in range(port.num_logical_ports):
                if (port.phy_type(sub) is not None):
                    addrs.append('port_phy_addr_%s=0x%x' %
                                 (port.bcm_intf(sub), port.phy_addr(sub)))
        return ('\n').join(addrs)

    @property
    def prim_offsets(self):
        prim_offsets = []

        for port in self.ports:
            if port.prim_offset is not None:
                prim_offsets.append('phy_port_primary_and_offset_%s=0x%x' %
                                    (port.bcm_intf(0), port.prim_offset))

        return ('\n').join(prim_offsets)

    @property
    def phy_id1s(self):
        phy_id1s = []

        for port in self.ports:
            if port.phy_id1 is not None:
                phy_id1s.append('port_phy_id1_%s=0x%x' %
                                    (port.bcm_intf(0), port.phy_id1))


        return ('\n').join(phy_id1s)

    @property
    def sys_interfaces(self):
        sys_interfaces = []

        for port in self.ports:
            if port.sys_interface is not None:
                sys_interfaces.append('phy_sys_interface_%s=0x%x' %
                                    (port.bcm_intf(0), port.sys_interface))

        return ('\n').join(sys_interfaces)

    @property
    def phytab(self):
        phytab = []

        (phy_addr, linux_intf, bcm_intf) = (None, None, None)
        for port in self.ports:
            for phy in range(port.num_phys):
                phy_addr = port.phy_addr(phy)
                if port.num_logical_ports > phy:
                    bcm_intf = port.bcm_intf(phy)
                    if port.num_logical_ports > 1:
                        linux_intf = '%s%ss%u' % (port.linux_prefix, port.gang_label, phy)
                    elif port.num_logical_ports == 1:
                        linux_intf = '%s%s' % (port.linux_prefix, port.gang_label)
                phytab.append('0x%x\t%s\t%s\t%s' %
                              (phy_addr, linux_intf, bcm_intf, port.mode))

        return ('\n').join(phytab)

    def _compress_portlist(self, portlist):
        # The BCM SDK has a limit on the size of setreg commands and/or port
        # range specifiers.  This code compresses ranges of sequential ports so
        # they take up less space.  For example, "xe0,xe1,xe2" becomes "xe0-xe2"
        key = lambda x: '%s%03u' % (x[:2], int(x[2:]))
        grouper = lambda (i, intf): '%s%u' % (intf[:2], i - int(intf[2:]))
        spans = [ list(y) for x,y in groupby(enumerate(sorted(portlist, key=key)), grouper) ]

        compressed = []
        for span in spans:
            if len(span) > 2:
                compressed.append('%s-%s' % (span[0][1], span[-1][1]))
            else:
                compressed += [ x[1] for x in span ]

        return ','.join(compressed)

    @property
    def rcports(self):
        rcports = []

        allports = []
        speeds = {}
        for port in self.ports:
            for sub in range(port.num_logical_ports):
                allports.append(port.bcm_intf(sub))
                if port.speed not in speeds:
                    speeds[port.speed] = list()
                speeds[port.speed].append(port.bcm_intf(sub))

        rcports.append('setenv allports %s' % self._compress_portlist(allports))
        for speed in speeds:
            if speed == 1:
                rcports.append('setenv 1Gports %s' % self._compress_portlist(speeds[1]))
            else:
                rcports.append('setenv %sGports %s' %
                               (speed, self._compress_portlist(speeds[speed])))

        return '\n'.join(rcports)

    @property
    def porttab(self):
        porttab = []
        active_interfaces = set([])

        # first build list of all existing port.linux_prefix's
        cmd = 'tuntap show'
        out = self.iproute2.run(cmd.split())
        for interface in out.splitlines():
            taps = interface.split(':')
            if taps[0]:
                active_interfaces.add(taps[0])

        # now create the porttab entries and swp devices
        for port in self.ports:
            if port.num_logical_ports > 1:
                for sub in range(port.num_logical_ports):
                    portname = '%s%ss%u' % (port.linux_prefix, port.gang_label,
                                            sub)
                    porttab.append('%s\t%s\t%u\t%i' %
                                   (portname, port.bcm_intf(sub),
                                    port.unit, port.is_fabric))
                    self.maketap(portname, port.mac_index + sub, active_interfaces)
            elif port.num_logical_ports > 0:
                portname = '%s%s' % (port.linux_prefix, port.gang_label)
                porttab.append('%s\t%s\t%u\t%i' %
                               (portname, port.bcm_intf(0),
                                port.unit, port.is_fabric))
                self.maketap(portname, port.mac_index, active_interfaces)


        # now erase the interfaces which are left over
        self.destroytaps(active_interfaces)
        del active_interfaces

        return ('\n').join(porttab)

    @property
    def rcled(self):
        rcled = []
        for led in self._led_programs.keys():
          rcled.append('led %d stop\n'
                       'led %d auto on\n'
                       'led %d load /etc/bcm.d/led%d.hex\n'
                       'led %d start\n' % (led, led, led, led, led))
        return '\n'.join(rcled)

    @property
    def rcphy(self):
        rcphy = []

        for port in self.ports:
            for phy in range(port.num_phys):
                phy_addr = port.phy_addr(phy)
                if port.num_logical_ports > phy:
                    for reg in port.phy_init.keys():
                        rcphy.append('phy raw c45 %s %s %s' %
                                     (phy_addr, reg, port.phy_init[reg]))

        return ('\n').join(rcphy)

    @property
    def ethertab(self):
        ethertab = []

        # now create the porttab entries and swp devices
        for port in self.ports:
            if port.num_logical_ports > 1:
                for sub in range(port.num_logical_ports):
                    portname = '%s%ss%u' % (port.linux_prefix, port.gang_label, sub)
                    ethertab.append('%s\t%s' % (portname, port.mac_index + sub))
            elif port.num_logical_ports > 0:
                portname = '%s%s' % (port.linux_prefix, port.gang_label)
                ethertab.append('%s\t%s' % (portname, port.mac_index))

        return ('\n').join(ethertab)

    @property
    def sfptab(self):
        sfptab = []
        linux_intf = None
        for port in self.ports:
            psfp = port.physical_port.sfp
            if not psfp:
                continue
            if psfp.accessmethod == "bcmsdk":
                sfpaddress = '0x%x' %psfp.address
            else:
                sfpaddress = '%s' %psfp.address
            if port.num_logical_ports > 1:
                for sub in range(port.num_logical_ports):
                    linux_intf = '%s%ss%u' % (port.linux_prefix,
                                        port.gang_label, sub)
                    sfptab.append('%s\t%s\t%s\t%s' %
                                (linux_intf, psfp.type, psfp.accessmethod,
                                sfpaddress))
            else:
                linux_intf = '%s%s' % (port.linux_prefix, port.gang_label)
                sfptab.append('%s\t%s\t%s\t%s' %
                            (linux_intf, psfp.type, psfp.accessmethod,
                            sfpaddress))
        return ('\n').join(sfptab)

    def output(self, configfile):
        if configfile == 'portsbcm':
            out = [
                '\n# pbmp',
                self.bcm_pbmp,
            ]

            if self.platform.switch.chip.portmap_capable is True:
                out += [
                    '\n# portmap',
                    self.portmap,
                ]
            out += [
                '\n# emphasis',
                self.port_emphasis,
                '\n# port initializations',
                self.port_init,
                '\n# phys',
                self.phys,
                '\n# addrs',
                self.phy_addrs,
                '\n# prime_offsets',
                self.prim_offsets,
                '\n# phy_id1s',
                self.phy_id1s,
                '\n# sys_interfaces',
                self.sys_interfaces,

            ]
        elif configfile == 'porttab':
            out = [
                '# linux_intf\tsdk_intf\tunit\tis_fabric',
                self.porttab,
            ]
        elif configfile == 'phytab':
            out = [
                '# phy_addr\tlinux_intf\tsdk_intf',
                self.phytab,
            ]
        elif configfile == 'rcports':
            out = [
                self.rcports,
            ]
        elif configfile == 'rcled':
            out = [
                self.rcled,
            ]
        elif configfile == 'rcphy':
            out = [
                self.rcphy,
            ]
        elif configfile == 'ethertab':
            out = [
                self.ethertab,
            ]
        elif configfile == 'ucodebcm':
            if self.exploded:
                if self.platform.switch.has_phy_ucode_mdio:
                    mode = "MDIO"
                    rom_boot = 0
                else:
                    mode = "SPI-ROM"
                    rom_boot = 3000
            else:
                if self.platform.switch.has_phy_ucode_spi_rom:
                    mode = "SPI-ROM"
                    rom_boot = 3000
                else:
                    mode = "MDIO"
                    rom_boot = 0

            out = [
                '# use %s method for ucode download' % (mode),
                'phy_ext_rom_boot=%d' % (rom_boot)
            ]
        elif configfile == 'sfptab':
            out = [
                '# linux_intf\tmode\tsfp_addrtype\tsfp_addr',
                self.sfptab,
            ]

        elif configfile == 'hwdesc' :
            if self.hw_desc == None :
                return None
            out = [
                ' # chip description file',
                self.hw_desc,
                ]

        elif configfile == 'datapath' :
            if self.datapath_conf == None :
                return None
            out = [
                ' # chip datapath configuration file',
                self.datapath_conf,
                ]

        elif configfile == 'sdk' :
            if self.sdk_bcm == None :
                return None
            out = [
                self.sdk_bcm,
                ]

        elif configfile == 'rcforwarding' :
            if self.rc_forwarding == None :
                return None
            out = [
                ' # chip forwarding configuration file',
                self.rc_forwarding,
                ]

        return '\n'.join(out)
