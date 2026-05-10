#
# Copyright 2012.  Cumulus Networks, Inc.
#
# cpld.py --
#
#     Python access to CPLDs
#

import os
import errno
import struct

class CPLD(object):
    pass

class CPLDMerged(CPLD):
    '''
    Implemets a "merged" CPLD where sysfs entries are looked up in several
    CPLDs.  The order depends on the list of CPLDs passwd to __init__().
    Useful when a vendor implements system functionality across more than one
    device.
    '''
    def __init__(self, cplds):
        self._cplds = cplds

    def __getattr__(self, name):
        if name.startswith('_'):
            return CPLD.__getattr__(self, name)

        try:
            return CPLD.__getattr__(self, name)
        except AttributeError:
            pass

        for cpld in self._cplds:
            try:
                return getattr(cpld, name)
            except AttributeError:
                pass

        raise AttributeError('merged cpld has no entry: %s' % name)

    def __setattr__(self, name, value):
        if name.startswith('_'):
            return CPLD.__setattr__(self, name, value)

        for cpld in self._cplds:
            try:
                return setattr(cpld, name, value)
            except AttributeError:
                pass

        raise AttributeError('merged cpld has no entry: %s' % name)

class SysFS(CPLD):
    path = None
    # Types are assumed to be strings with a trailing whitespace.  Add
    # struct.pack style format characters here to pack and unpack binary data
    # and avoid stripping whitespace from binary values.
    types = {}

    def __getattr__(self, name):
        fn = os.path.join(self.path, name)
        try:
            value = open(fn, 'r').read()
        except IOError, e:
            if e.errno == errno.ENOENT:
                raise AttributeError('sysfs has no entry: %s' % fn)
            else:
                raise e

        if self.types.has_key(name):
            value = struct.unpack(self.types[name], value)
            if len(self.types[name]) == 1:
                return value[0]
            else:
                return value
        else:
            return value.strip().rstrip('\0')

    def __setattr__(self, name, value):
        fn = os.path.join(self.path, name)
        try:
            fh = open(fn, 'w')
        except IOError, e:
            if e.errno == errno.ENOENT:
                raise AttributeError('sysfs has no entry: %s' % fn)
            else:
                raise e

        if self.types.has_key(name):
            if len(self.types[name]) == 1:
                fh.write(struct.pack(self.types[name], value))
            else:
                fh.write(struct.pack(self.types[name], *value))
        else:
            return fh.write(value)
