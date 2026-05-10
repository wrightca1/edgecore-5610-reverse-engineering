#! /usr/bin/python
#--------------------------------------------------------------------------
#
# Copyright 2014 Cumulus Networks, inc  all rights reserved
#
# SFP utility sub-class for the Accton AS5610_52X.
#
#--------------------------------------------------------------------------
try:
        from cumulus.sfputilbase import sfputilbase
except ImportError, e:
        raise ImportError (str(e) + "- required module not found")


class sfputil(sfputilbase):
        """Accton AS5610_52X class for sfp utility."""
        port_start = 1
        port_end = 52

	_qsfp_ports = [49, 50, 51, 52]

        def __init__(self, port_num):
                sfputilbase.__init__(self, port_num)
