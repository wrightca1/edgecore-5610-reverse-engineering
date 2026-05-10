#!/usr/bin/python
#
# Copyright 2013.  Cumulus Networks, Inc.
#
# sfptab.py --
#    parse a sfptab file and provide lookup methods.
#    methods to get sfp accessmethod and sfp eeprom address
#
import eeprom_dts
import os

class sfptabEntry:
    def __init__(self, linux_intf, mode, addrtype, addr):
        self.linux_intf = linux_intf
        self.mode = mode
        self.addrtype = addrtype
        self.addr = addr

class sfptab:
    def __init__(self, path='/var/lib/cumulus/sfptab'):
        self._readpt(path)

    def _readpt(self, path):
        self.sfptab = []

        stfile = open(path, 'r')

        for line in stfile.readlines():
            line = line.strip()

            if '#' in line:
                continue

            try:
                se = sfptabEntry(*line.split(None, 4))
            except ValueError:
                continue

            self.sfptab.append(se)

class SFPROM:
    accessmethod = None
    @property
    def address(self):
        raise NotImplementedError

class SFPROMDTSLabel(SFPROM):
    accessmethod = 'dts-sysfs'

    def __init__(self, label, type):
        self._label = label
        self._type = type

    @property
    def address(self):
        return self._getfilenamebydtslabel(self._label)

    @property
    def type(self):
        return self._type

    def _getfilenamebydtslabel(self, label):
        eeprom_dev = '/sys/class/eeprom_dev'
        for eeprom_path in [ os.path.join(eeprom_dev, x)
                    for x in os.listdir(eeprom_dev) ]:
            eeprom_label = open(os.path.join(eeprom_path, 'label'),
                                'r').read().strip()
            if eeprom_label.startswith('port'):
                port = eeprom_label[4:]
                if label == port:
                    return os.path.join(eeprom_path, 'device', 'eeprom')
        return None

class SFPROMDTSWalk(SFPROM):
    accessmethod = 'dts-sysfs'
    eep_dict = None

    def __init__(self, label, type):
        self._label = label
        self._type = type
        self.eep_dict = eeprom_dts.get_dev_attr_from_dtb(['sfp'])

    @property
    def address(self):
        return self._getfilenamebydts(self._label)

    @property
    def type(self):
        return self._type

    def _getfilenamebydts(self, label):
        i2c_dev = '/sys/class/i2c-adapter'
        if not self.eep_dict:
            self.eep_dict = eeprom_dts.get_dev_attr_from_dtb(['sfp'])
            if not self.eep_dict:
                return
        i2cbus_list = []
        s = 1
        plabel = int(label)
        for sfp_sysfs_path, attrs in sorted(self.eep_dict.iteritems()):
            i2cbus = attrs.get('dev-id')
            if not i2cbus:
                raise Exception('No \'dev-id\' attribute found in attr: ' +
                                repr(attrs))
            if i2cbus in i2cbus_list:
                continue
            i2cbus_list.append(i2cbus)
            if s == plabel:
                return '%s/i2c-%d/%d-0050/eeprom' %(i2c_dev, i2cbus, i2cbus)
            s = s + 1

        return None

class SFPROMBCM(SFPROM):
    accessmethod = 'bcmsdk'

    def __init__(self, phy_addr, type):
        self._phy_addr = phy_addr
        self._type = type

    @property
    def address(self):
        return self._phy_addr

    @property
    def type(self):
        return self._type
