#! /usr/bin/python
# Copyright 2014 Cumulus Networks, Inc.
# All rights reserved

#############################################################################
# Platform and model specific eeprom subclass, inherits from the base class,
# and provides the followings:
# - the eeprom format definition
# - specific encoder/decoder if there is special need
#

try:
    import exceptions
    import binascii
    import time
    import optparse
    import warnings
    import os
    import sys
    import subprocess
    import tempfile
    import eeprom_base
    import eeprom_tlvinfo
except ImportError, e:
    raise ImportError (str(e) + "- required module not found")

#
# base board
#
class board(eeprom_tlvinfo.TlvInfoDecoder):

    EEPROM_MAX_SIZE = 0x10000

    def __init__(self, name, path, cpld_root, ro):
        super(board, self).__init__(path, 0, "", ro, self.EEPROM_MAX_SIZE)

    def write_eeprom(self, e):
        tmpfd, tmppath = tempfile.mkstemp();
        F = open(tmppath, "wb")
        F.write(e)
        F.close()
        os.close(tmpfd)
        os.system("/usr/sbin/flashcp %s %s" % (tmppath, self.p))
        os.remove(tmppath)


#
# power supply unit
#
class psu(eeprom_base.eepromDecoder):

    # This format is bogus.  Find out what it is later.
    ps_fmt = [ ('burn',        'x', 0x26),  # offset 0
               ('description', 's', 13),    # offset 0x26
               ('burn',        'x', 19),    # offset 0x33
               ('serial_num',  's', 15)
             ]

    def __init__(self, name, path, cpld_root, ro):
        cpld_path = cpld_root + '/psu_pwr' + name.split('psu')[1] + '_present'
        super(psu, self).__init__(path,         \
                                  self.ps_fmt,  \
                                  0,            \
                                  cpld_path,    \
                                  ro)

    def decoder(self, s, t):
        # not implemented
        return 0

    def check_status(self):
        status = super(psu, self).check_status()

        # each device may have a different status string, decide what
        # translates to 'ok' here.
        if status.startswith('1'):
            return 'ok'
        else:
            return 'not present'

    def is_checksum_valid(self, e):
        # not implemented
        return (True, 0)
