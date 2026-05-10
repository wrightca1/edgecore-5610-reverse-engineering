#!/usr/bin/python
#
# Copyright 2013.  Cumulus Networks, Inc.
#
# porttab.py --
#
#    parse a porttab file and provide lookup methods.
#
import errno

class NoSuchLinuxInterface(Exception):
    pass
class NoSuchBCMInterface(Exception):
    pass
class NotConfigured(Exception):
    pass

class porttabEntry:
    def __init__(self, linux_intf, bcm, unit, is_fabric):
        self.linux_intf = linux_intf
        self.bcm = bcm
        self.unit = unit
        self.is_fabric = is_fabric

class porttab:
    def __init__(self, path='/var/lib/cumulus/porttab'):
        self._readpt(path)

    def _readpt(self, path):
        self.porttab = []

        try:
            ptfile = open(path, 'r')
        except IOError, e:
            if e.errno == errno.ENOENT:
                raise NotConfigured('porttab not configured')
            else:
                raise e

        for line in ptfile.readlines():
            line = line.strip()

            if '#' in line:
                continue

            try:
                pe = porttabEntry(*line.split(None, 4))
            except ValueError:
                continue

            self.porttab.append(pe)

    def linux2bcm(self, linux_intf):
        for pe in self.porttab:
            if pe.linux_intf == linux_intf:
                return pe.bcm

        raise NoSuchLinuxInterface(linux_intf)

    def bcm2linux(self, bcm):
        for pe in self.porttab:
            if pe.bcm == bcm:
                return pe.linux_intf

        raise NoSuchBCMInterface(bcm)

    def get_linux_ports(self):
        return [p.linux_intf for p in self.porttab]

    def get_bcm_ports(self):
        return [p.bcm for p in self.porttab]
