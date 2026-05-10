#
# Copyright 2012.  Cumulus Networks, Inc.
#
# platform.py --
#     Shared platform-specific objects.  Typically used by specific switch
#     platforms defined in platformdb.py
#

import os

class NoSuchPlatform(RuntimeError):
    pass

class Platform:
    revision = None
    cpld = None
    switch = None

class BCMChip:
    '''
    BCM chip common attributes

    portmap_capable       - true if platform supports the "portmap_" bcm config entry
    base_pbmp - bitmap of valid pbmp bits that should always be enabled

    '''

    hsp_bw          = None
    portmap_capable = None
    base_pbmp       = None
    file_list       = None

    def __init__(self) :
        self.chip_dir_list   = ['/bcm']

    @property
    def chip_config_path(self):
            return os.path.dirname(__file__) + '/__chip_config/'

    def get_config(self, file_name) :
        if self.file_list == None :
            return None
        if file_name in self.file_list :
            for prefix in self.chip_dir_list :
                file_path = self.chip_config_path + prefix + '/' + file_name
                if os.path.exists(file_path) :
                    with open(file_path, 'r') as config_file :
                        config = config_file.read()
                        return config
        return None

class TridentChip(BCMChip):
    '''
    Trident chip common attributes
    '''
    portmap_capable = True
    base_pbmp = 0x20000000000000001 # (LBPORT0 | CPU)
    file_list = 'datapath.conf', 'rc.forwarding', 'hw_desc', 'sdk.bcm'

    def __init__(self) :
        BCMChip.__init__(self)
        self.chip_dir_list.insert(0,self.chip_dir_list[0] + '/Trident')

class TridentTwoChip(BCMChip):
    '''
    Trident2 chip common attributes

    '''
    portmap_capable = True
    base_pbmp = (0x1 << 105) | 0x1 # (LBPORT0 | CPU)
    file_list = 'datapath.conf', 'rc.forwarding', 'hw_desc', 'sdk.bcm'

    def __init__(self) :
        BCMChip.__init__(self)
        self.chip_dir_list.insert(0,self.chip_dir_list[0] + '/TridentTwo')

class TridentTwo_56850_Chip(TridentTwoChip):
    hsp_bw = 100

    def __init__(self) :
        TridentTwoChip.__init__(self)
        self.chip_dir_list.insert(0,self.chip_dir_list[0] + '/56850')

class TridentTwo_56854_Chip(TridentTwoChip):
    hsp_bw = 40
    def __init__(self) :
        TridentTwoChip.__init__(self)
        self.chip_dir_list.insert(0,self.chip_dir_list[0] + '/56854')

class TriumphChip(BCMChip) :
    portmap_capable = False
    base_pbmp = 0x1 # (CPU)
    file_list = 'rc.forwarding', 'sdk.bcm'
    def __init__(self) :
        BCMChip.__init__(self)
        self.chip_dir_list.insert(0,self.chip_dir_list[0] + '/Triumph')

class ApolloChip(BCMChip):
    portmap_capable = False
    base_pbmp = 0x1 # (CPU)
    file_list = 'rc.forwarding', 'sdk.bcm'

    def __init__(self) :
        BCMChip.__init__(self)
        self.chip_dir_list.insert(0,self.chip_dir_list[0] + '/Apollo')

class BCMSwitch:
    '''
    BCM platform common attributes

    has_phy_ucode_spi_rom - true if platform supports SPI-ROM for phy microcode
    has_phy_ucode_mdio    - true if platform supports MDIO for phy microcode
    '''

    has_phy_ucode_spi_rom = None
    has_phy_ucode_mdio = None

    def __init__(self, chip) :
        self.chip = chip

class NoSuchMode(RuntimeError):
    pass

class Port:
    '''
    A physical switch port.  Typically on the front panel with one physical
    text label per port.

    label - the text written next to the physical port
    '''
    is_fabric = False
    def __init__(self, label):
        self.label = label
        self.sfp = None

    '''
    Set port configuration in hardware (if any).
    '''
    def set_hardware(self, platform, mode):
        raise NotImplementedError

class BCMPort(Port):
    '''
    Broadcom-specific port data.

    modes - tuple of valid modes (e.g. 4x10G, 40G/4)
    default_mode - the default mode
    pbmp_map - a map from hardware interface name to BCM SDK pbmp position (e.g. "hg0 -> 1")
    phy_init - a map of register to values used to initalize PHYs
    '''
    modes = ()
    default_mode = None
    pbmp_map = {}
    phy_init = {}
    _speed_map = {}
    # phys which are automatically detectable by the BCM sdk
    _autodetect_phys = ('8727',
                        '8747',
                        '8754',
                        '54680',
                        '54280',
                        '84328',
                        '84848')

    # Serdes Interface map is dictionary of (Port speed, Interface Mode)
    # which is platform specific
    # Ex: 10:'SFI', 40: 'XLAUI'
    _serdes_intf_map = {}

    def __init__(self, label, hw_ports, phy_types, phy_addrs, phy_layer, prim_offset,
		 leds, unit, rx_polarity_flip, tx_polarity_flip,
	         rx_lane_map, tx_lane_map, pre_emphasis, drv_current, 
	         pre_drv_current, oversub, phy_id1, sys_interface):
        '''
        hw_ports - An ordered list of hardware interfaces associated with the port.
                   In this context, ports are identified by their unmapped
                   interface name as in the Broadcom chip datasheets (For example,
                   the "Ports Summary" on page 143 of 56840-PR101-R).  This usually
                   means 10G interfaces are specified using their "hg" prefix.

        phy_types - An ordered list of PHY device types associated with the port.
        phy_addrs - An ordered list of PHY addresses associated with the port.
        phy_layer - A description of the PHY layer, one of: '10GBaseT',
                      'SFP+', 'QSSFP+', '10BaseT'
        leds - An ordered list of led chain addresses associated with the port.
               (controller, chain position)
        unit - In multi-chip systems, the chip number, "unit" in SDK terms.
        rx_polarity_flip - flip the rx polarity in hardware
                               (True/False for single serdes ports, BCM-style
                                4-digit hex number for multi-serdes ports)
        tx_polarity_flip - flip the tx polarity in hardware
        rx_lane_map - controls lane swapping
        tx_lane_map - controls lane swapping
        pre_emphasis - per-lane pre-emphasis (Ref: Table7 56840-AN603-R)
        drv_current - per-lane driver current (Ref: Table7 56840-AN603-R)
        pre_drv_current - per-lane pre-driver current (Ref: Table7 56840-AN603-R)
        oversub  - a bool whether the port bandwidth is over-subscribed
        phy_id1 - Second part of a uniqe PHY identifier
        sys_interface - Specify the sytem side interface to be configured for the PHY
        '''
        Port.__init__(self, label)
        self.hw_ports = hw_ports
        self.prim_offset = prim_offset
        self.phy_types = phy_types
        self.phy_addrs = phy_addrs
        self.phy_layer = phy_layer
        self.leds = leds
        self.unit = unit
        self.rx_polarity_flip = rx_polarity_flip
        self.tx_polarity_flip = tx_polarity_flip
        self.rx_lane_map = rx_lane_map
        self.tx_lane_map = tx_lane_map
        self.pre_emphasis = pre_emphasis
        self.drv_current = drv_current
        self.pre_drv_current = pre_drv_current
        self.oversub = oversub
        self.phy_id1 = phy_id1
        self.sys_interface = sys_interface

    def phy_autodetect(self, mode, sub):
        return self.phy_types[sub] in self._autodetect_phys

    @classmethod
    def _check_mode(self, mode):
        '''
        Verify the mode specified in the config file is valid.
        '''
        if mode not in self.modes:
            raise NoSuchMode('error: mode not found: %s, must be one of: %s' %
                             (mode, str(self.modes)))

    @classmethod
    def speed(self, mode):
        '''
        Return the port speed in gigabits per second for a given mode.
        '''
        self._check_mode(mode)
        return self._speed_map[mode]

    def num_physical_ports(self, mode):
        '''
        Return the number of physical (front panel holes) for a given port.
        '''
        return self.num_logical_ports(mode)

    def num_logical_ports(self, mode):
        '''
        Return the number of logical (Linux interfaces) for a given port.
        '''
        raise NotImplementedError

    @property
    def max_logical_ports(self):
        '''
        Return the maximum number of logical (Linux interfaces) for a given port.
        '''
        raise NotImplementedError

    @property
    def num_phys(self):
        '''
        Return the number of phys for a given port.
        '''
        if self.phy_addrs is not None:
            return len(filter(lambda x: x is not None, self.phy_addrs))
        else:
            return 0

    def hw_intf_prefix(self, mode, sub):
        '''
        Return the physical port interface prefix (always unmapped by portmap)
        '''
        return self.hw_ports[sub][:2]

    def hw_intf_num(self, mode, sub):
        '''
        Return the physical port interface number (always unmapped by portmap)
        '''
        return int(self.hw_ports[sub][2:])

    def base_hw_intf_num(self, mode, sub):
        '''
        Return the lowest numbered hw_intf_num that makes up a logical port.
        '''
        lports = self.num_logical_ports(mode)
        hports = len(self.hw_ports)
        if hports > lports:
            # the interface uses of multiple serdes
            return min([ self.hw_intf_num(mode, x) for x in range(hports) ])
        else:
            return self.hw_intf_num(mode, sub)

    def hw_intf(self, mode, sub):
        '''
        Return the physical hardware port for the sub-interface (prefix
        concatenated with number).
        '''
        return '%s%u' % (self.bcm_intf_prefix(sub), self.hw_intf_num(sub))

    def hw_pbmp(self, mode, sub):
        '''
        Return the hardware port bitmap mask for the sub-interface.
        '''
        return 1 << self.pbmp_map[self.hw_ports[sub]]

    def hw_port_num(self, mode, sub):
        '''
        Return the hardware port number (pbmp bit position)
        '''
        return self.pbmp_map[self.hw_ports[sub]]

    def led_port_num(self, mode, sub):
        '''
        Return the led port number (identical to the hw_port_num on most platforms)
        '''
        return self.pbmp_map[self.hw_ports[sub]]

    def set_leds(self, mode, led_port, sub, led_index_list):
        return {}

    def set_hardware(self, platform, mode):
        pass

    def rx_logical_polarity_flip(self, mode, sub):
        '''
        Return the rx_polarity_flip for the sub-interface (prefix
        concatenated with number).
        '''
        raise NotImplementedError

    def tx_logical_polarity_flip(self, mode, sub):
        '''
        Return the tx_polarity_flip for the sub-interface (prefix
        concatenated with number).
        '''
        raise NotImplementedError

    def serdes_if_type(self, speed):
        '''
        Return the serdes interface type based on the port speed
        '''
        return self._serdes_intf_map.get(speed, None)


class TridentTwoPort(BCMPort):
    pbmp_map = dict([ (v,k) for k,v in enumerate(
                        [ 'hg%u' % x for x in range(0, 128) ], 1) ])

    def led_port_num(self, mode, sub):
	raise RuntimeError('Trident 2 LED port unknown')

    def __init__(self, label, serdes, phy_types, phy_addrs, phy_layer,
                 prim_offset, leds, unit=0,
                 rx_polarity_flip=None, tx_polarity_flip=None,
                 rx_lane_map=None, tx_lane_map=None, pre_emphasis=None,
                 drv_current=None, pre_drv_current=None, oversub=False,
                 phy_id1=None, sys_interface=None):
        hw_port = tuple([ 'hg%u' % x for x in serdes ])
        BCMPort.__init__(self, label, hw_port, phy_types, phy_addrs,
                         phy_layer, prim_offset, leds, unit,
                         rx_polarity_flip, tx_polarity_flip,
                         rx_lane_map, tx_lane_map, pre_emphasis, 
                         drv_current, pre_drv_current, oversub, phy_id1,
                         sys_interface)

class TridentPort(BCMPort):
    pbmp_map = dict([ (v,k) for k,v in enumerate(
                        [ 'hg%u' % x for x in range(0, 72) ], 1) ])

    def __init__(self, label, serdes, phy_types, phy_addrs,
		 phy_layer, prim_offset, leds, unit=0,
                 rx_polarity_flip=None, tx_polarity_flip=None,
                 rx_lane_map=None, tx_lane_map=None):
        hw_port = tuple([ 'hg%u' % x for x in serdes ])
        BCMPort.__init__(self, label, hw_port, phy_types, phy_addrs,
			 phy_layer, prim_offset, leds, unit,
                         rx_polarity_flip, tx_polarity_flip,
                         rx_lane_map, tx_lane_map, pre_emphasis=None,
                         drv_current=None, pre_drv_current=None, 
                         oversub=False, phy_id1=None, sys_interface=None)

class TriumphPort(BCMPort):
    pbmp_map = dict([ (v,k) for k,v in enumerate(
        ('ge48', 'ge8',  'ge9',  'ge10', 'ge11', 'ge12',
         'ge13', 'ge14', 'ge15', 'ge20', 'ge21', 'ge22',
         'ge23', 'ge24', 'ge25', 'ge26', 'ge27', 'ge32',
         'ge33', 'ge34', 'ge35', 'ge36', 'ge37', 'ge38',
         'ge39', 'hg0',  'hg1',  'hg2',  'hg3',  'ge0',
         'ge1',  'ge2',  'ge3',  'ge4',  'ge5',  'ge6',
         'ge7',  'ge16', 'ge17', 'ge18', 'ge19', 'ge28',
         'ge29', 'ge30', 'ge31', 'ge40', 'ge41', 'ge42',
         'ge43', 'ge44', 'ge45', 'ge46', 'ge47'), 1) ])

    def __init__(self, label, hw_ports, phy_types, phy_addrs, phy_layer, prim_offset, leds, unit):
        BCMPort.__init__(self, label, hw_ports, phy_types, phy_addrs, phy_layer,
                         prim_offset, leds, unit, rx_polarity_flip=None, tx_polarity_flip=None,
                         rx_lane_map=None, tx_lane_map=None, 
                         pre_emphasis=None, drv_current=None, 
                         pre_drv_current=None, oversub=False,
                         phy_id1=None, sys_interface=None)


class ApolloPort(BCMPort):
    def hw_port_num(self, mode, sub):
        num = self.hw_intf_num(mode, sub)
        prefix = self.hw_intf_prefix(mode, sub)

        # this platform has a hole at 36 and hg interfaces start at index 50
        if prefix == 'ge':
            if num > 35:
                return num + 2
            else:
                return num + 1
        elif prefix == 'hg':
            return num + 50
        else:
            raise RuntimeError('bad interface prefix')

    def hw_pbmp(self, mode, sub):
        return 1 << self.hw_port_num(mode, sub)

    def led_port_num(self, mode, sub):
        num = self.hw_intf_num(mode, sub)
        prefix = self.hw_intf_prefix(mode, sub)

        # The led data array has no holes, hg starts at element 73 (on the 2nd
        # led controller)
        if prefix == 'ge':
            return num + 1
        elif prefix == 'hg':
            return num + 73
        else:
            raise RuntimeError('bad interface prefix')

    def __init__(self, label, hw_ports, phy_types, phy_addrs, phy_layer, prim_offset, leds, unit):
        BCMPort.__init__(self, label, hw_ports, phy_types, phy_addrs, phy_layer, prim_offset,
			 leds, unit, rx_polarity_flip=None, tx_polarity_flip=None,
                         rx_lane_map=None, tx_lane_map=None, 
                         pre_emphasis=None, drv_current=None, 
                         pre_drv_current=None, oversub=False,
                         phy_id1=None, sys_interface=None)

class Apollo1GPort(ApolloPort):
    modes = ('1G')
    default_mode = modes[0]

    def __init__(self, label, hw_port, phy_type, phy_addr, leds, unit, prim_offset=None):
        ApolloPort.__init__(self,
                            label=label,
                            hw_ports=(hw_port,),
                            phy_types=(phy_type,),
                            phy_addrs=(phy_addr,),
                            phy_layer='1GBaseT',
			    prim_offset=prim_offset,
                            leds=leds,
                            unit=unit)

    def speed(self, mode):
        return 1

    def num_logical_ports(self, mode):
        return 1

    @property
    def max_logical_ports(self):
        return 1

class Triumph1GPort(TriumphPort):
    modes = ('1G')
    default_mode = modes[0]

    def __init__(self, label, hw_port, phy_type, phy_addr, phy_layer, leds, unit, prim_offset=None):
        TriumphPort.__init__(self,
                             label=label,
                             hw_ports=(hw_port,),
                             phy_types=(phy_type,),
                             phy_addrs=(phy_addr,),
                             phy_layer='1GBaseT',
                             prim_offset=prim_offset,
                             leds=leds,
                             unit=unit)

    def speed(self, mode):
        return 1

    def num_logical_ports(self, mode):
        return 1

    @property
    def max_logical_ports(self):
        return 1

class Apollo10GPort(ApolloPort):
    modes = ('10G',)
    default_mode = modes[0]
    _speed_map = { '10G' : 10 }

    def __init__(self, label, hw_port, phy_type, phy_addr, phy_layer, leds, unit):
        ApolloPort.__init__(self,
                            label=label,
                            hw_ports=(hw_port,),
                            phy_types=(phy_type,),
                            phy_addrs=(phy_addr,),
                            phy_layer=phy_layer,
			    prim_offset=None,
                            leds=leds,
                            unit=unit)

    # return how many logical ports when configured in the given mode
    def num_logical_ports(self, mode):
        return 1

    @property
    def max_logical_ports(self):
        return 1

class Triumph10GPort(TriumphPort):
    modes = ('10G',)
    default_mode = modes[0]
    _speed_map = { '10G' : 10 }

    def __init__(self, label, hw_port, phy_type, phy_addr, phy_layer, leds, unit):
        TriumphPort.__init__(self,
                             label=label,
                             hw_ports=(hw_port,),
                             phy_types=(phy_type,),
                             phy_addrs=(phy_addr,),
                             phy_layer=phy_layer,
			     prim_offset=None,
                             leds=leds,
                             unit=unit)

    # return how many logical ports when configured in the given mode
    def num_logical_ports(self, mode):
        return 1

    @property
    def max_logical_ports(self):
        return 1

class Trident10GPort(TridentPort):
    modes = ('10G', '40G/4')
    default_mode = modes[0]
    _speed_map = { '10G'   : 10,
                   '40G/4' : 40 }

    def __init__(self, label, serdes, phy_type, phy_addr, phy_layer, leds, unit,
                 rx_lane_map=None, rx_polarity_flip=None,
                 tx_lane_map=None, tx_polarity_flip=None):
        TridentPort.__init__(self,
                             label=label,
                             serdes=(serdes,),
                             phy_types=(phy_type,),
                             phy_addrs=(phy_addr,),
                             phy_layer=phy_layer,
                             prim_offset=None,
                             leds=leds,
                             unit=unit,
                             rx_polarity_flip=rx_polarity_flip,
                             tx_polarity_flip=tx_polarity_flip,
                             rx_lane_map=rx_lane_map,
                             tx_lane_map=tx_lane_map)

    def num_logical_ports(self, mode):
        self._check_mode(mode)
        if mode == '10G':
            return 1
        elif mode == '40G/4':
            if int(self.hw_ports[0][2:]) % 4 == 0:
                return 1
            else:
                return 0

    @property
    def max_logical_ports(self):
        return 1

    def num_physical_ports(self, mode):
        self._check_mode(mode)
        if mode == '10G':
            return 1
        elif mode == '40G/4':
            if int(self.hw_ports[0][2:]) % 4 == 0:
                return 4
            else:
                return 0

    def polarity_flip_val(self, mode, sub, polarity_flip):
        self._check_mode(mode)

        if mode == '10G':
            if polarity_flip is True:
                return 1
            else:
                return 0
        elif mode == '40G/4':
            '''
            TODO:polarity_flip and serdes ganging need rework
            but there is no platform with this configuration
            '''
            raise NotImplementedError

    def rx_logical_polarity_flip(self, mode, sub):
        if self.rx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.rx_polarity_flip)

    def tx_logical_polarity_flip(self, mode, sub):
        if self.tx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.tx_polarity_flip)

class TridentTwo10GPort(TridentTwoPort):
    modes = ('10G', '40G/4')
    default_mode = modes[0]
    _speed_map = { '10G'   : 10,
                   '40G/4' : 40 }

    def __init__(self, label, serdes, phy_types, phy_addrs, phy_layer, leds, unit,
                 rx_lane_map=None, rx_polarity_flip=None,
                 tx_lane_map=None, tx_polarity_flip=None,
                 pre_emphasis=None, drv_current=None, pre_drv_current=None,
                 oversub=False, phy_id1=None, sys_interface=None, prim_offset=None):
        TridentTwoPort.__init__(self,
                                label=label,
                                serdes=serdes,
                                phy_types=phy_types,
                                phy_addrs=phy_addrs,
                                phy_layer=phy_layer,
                                prim_offset=prim_offset,
                                leds=leds,
                                unit=unit,
                                rx_polarity_flip=rx_polarity_flip,
                                tx_polarity_flip=tx_polarity_flip,
                                rx_lane_map=rx_lane_map,
                                tx_lane_map=tx_lane_map,
                                pre_emphasis=pre_emphasis,
                                drv_current=drv_current,
                                pre_drv_current=pre_drv_current,
                                oversub=oversub,
                                phy_id1=phy_id1, sys_interface=sys_interface)

    def num_logical_ports(self, mode):
        self._check_mode(mode)
        if mode == '10G':
            return 1
        elif mode == '40G/4':
            if int(self.hw_ports[0][2:]) % 4 == 0:
                return 1
            else:
                return 0

    @property
    def max_logical_ports(self):
        return 1

    def num_physical_ports(self, mode):
        self._check_mode(mode)
        if mode == '10G':
            return 1
        elif mode == '40G/4':
            if int(self.hw_ports[0][2:]) % 4 == 0:
                return 4
            else:
                return 0

    def polarity_flip_val(self, mode, sub, polarity_flip):
        self._check_mode(mode)

        if mode == '10G':
            if polarity_flip is True:
                return 1
            else:
                return 0
        elif mode == '40G/4':
            '''
            TODO:polarity_flip and serdes ganging need rework
            but there is no platform with this configuration
            '''
            raise NotImplementedError

    def rx_logical_polarity_flip(self, mode, sub):
        if self.rx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.rx_polarity_flip)

    def tx_logical_polarity_flip(self, mode, sub):
        if self.tx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.tx_polarity_flip)

class Trident40GPort(TridentPort):
    modes = ('40G', '4x10G')
    default_mode = modes[0]
    _speed_map = { '4x10G' : 10,
                   '40G'   : 40 }

    def __init__(self, label, serdes, phy_types, phy_addrs, leds, unit,
                 rx_lane_map=None, rx_polarity_flip=None,
                 tx_lane_map=None, tx_polarity_flip=None,
                 prim_offset=None):
        TridentPort.__init__(self,
                             label=label,
                             serdes=serdes,
                             phy_types=phy_types,
                             phy_addrs=phy_addrs,
                             phy_layer='QSFP+',
                             prim_offset=prim_offset,
                             leds=leds,
                             unit=unit,
                             rx_polarity_flip=rx_polarity_flip,
                             tx_polarity_flip=tx_polarity_flip,
                             rx_lane_map=rx_lane_map,
                             tx_lane_map=tx_lane_map)

    def num_logical_ports(self, mode):
        self._check_mode(mode)

        if mode == '4x10G':
            return 4
        elif mode == '40G':
            return 1

    @property
    def max_logical_ports(self):
        return 4

    def polarity_flip_val(self, mode, sub, polarity_flip_list):
        self._check_mode(mode)

        if mode == '4x10G':
            polarity_flip = polarity_flip_list[sub]
            if polarity_flip is True:
                return 1
            else:
                return 0
        elif mode == '40G':
            flip_intf = 0x0
            for polarity_flip in reversed(polarity_flip_list):
                if polarity_flip is True:
                    flip_intf = (flip_intf << 4) | 0xf
                else:
                    flip_intf = (flip_intf << 4) | 0x0

            return flip_intf

    def rx_logical_polarity_flip(self, mode, sub):
        if self.rx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.rx_polarity_flip)

    def tx_logical_polarity_flip(self, mode, sub):
        if self.tx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.tx_polarity_flip)

class TridentTwo40GPort(TridentTwoPort):
    modes = ('40G', '4x10G')
    default_mode = modes[0]
    _speed_map = { '4x10G' : 10,
                   '40G'   : 40 }

    def __init__(self, label, serdes, phy_types, phy_addrs, leds, unit,
                 rx_lane_map=None, rx_polarity_flip=None,
                 tx_lane_map=None, tx_polarity_flip=None,
                 pre_emphasis=None, drv_current=None, pre_drv_current=None,
                 oversub=False, phy_id1=None, sys_interface=None, prim_offset=None):
        TridentTwoPort.__init__(self,
                                label=label,
                                serdes=serdes,
                                phy_types=phy_types,
                                phy_addrs=phy_addrs,
                                phy_layer='QSFP+',
                                prim_offset=prim_offset,
                                leds=leds,
                                unit=unit,
                                rx_polarity_flip=rx_polarity_flip,
                                tx_polarity_flip=tx_polarity_flip,
                                rx_lane_map=rx_lane_map,
                                tx_lane_map=tx_lane_map,
                                pre_emphasis=pre_emphasis,
                                drv_current=drv_current,
                                pre_drv_current=pre_drv_current,
                                oversub=oversub,
                                phy_id1=phy_id1,
                                sys_interface=sys_interface)

    def num_logical_ports(self, mode):
        self._check_mode(mode)

        if mode == '4x10G':
            return 4
        elif mode == '40G':
            return 1

    @property
    def max_logical_ports(self):
        return 4

    def polarity_flip_val(self, mode, sub, polarity_flip_list):
        self._check_mode(mode)

        if mode == '4x10G':
            if polarity_flip_list & (1 << sub):
                return 1
            else:
                return 0
        elif mode == '40G':
            return polarity_flip_list

    def rx_logical_polarity_flip(self, mode, sub):
        if self.rx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.rx_polarity_flip)

    def tx_logical_polarity_flip(self, mode, sub):
        if self.tx_polarity_flip is None:
            return

        return self.polarity_flip_val(mode, sub, self.tx_polarity_flip)
