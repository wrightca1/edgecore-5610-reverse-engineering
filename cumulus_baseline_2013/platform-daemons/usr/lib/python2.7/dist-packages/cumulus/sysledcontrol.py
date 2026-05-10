#
# Copyright 2013.  Cumulus Networks, Inc.
#
# sysledcontrol.py --
#     Maintain Database of all system led components.
#

import errno
import ConfigParser
import StringIO
import os

import platformdb

#-------------------------------------------------------------------------------
#
# SUnitConfig
#
#       Class which contains data and accessors for monitoring a system unit
#
class SUnitConfig:
    """
    System Unit configuration implementation.
    init
    State/Platform DB
        Set
        Get
        Update
    Led Color
        Set
        Get
        Update
    """
    def __init__(self, sunit, expected_unit_count):
        self.sunit = sunit
        self.new_status = 'UNKNOWN'
        self.expected_unit_count = expected_unit_count

    @property
    def label(self):
        """
        Return  name of the system unit
        """
        return self.sunit.label

    @property
    def default_sunit_count(self):
        """
        Return  expected number of the system unit
        """
        return self.sunit.default_sunit_count

    @property
    def state(self):
        """
        Return the state of the system unit
        """
        return self.sunit.get_state()

    def init_state(self):
        """
        Initalize the state of the system unit
        """
        return self.sunit.init_state()

    def set_state(self, state):
        """
        Set the state of the system unit.
        """
        return self.sunit.set_state(state)

    def update_state(self, platform):
        """
        Calculate  the current state of system unit and update it.
        """
        return self.sunit.update_state(platform, self.expected_unit_count)

    def get_led(self, platform):
        """
        Return the led color for system unit if exist
        """
        return self.sunit.get_led(platform)

    def set_led(self, platform):
        """
        Set the led color for system unit if exist
        """
        return self.sunit.set_led(platform)

#-------------------------------------------------------------------------------
#
# Config
#
#       Base Class to read system unit related configuration
#       i.e./etc/cumulus/sysledcontrol.conf
#
class Config:
    """
    Base class for system unit configuration.
    Understands sysledcontrol.conf format and how
    to lookup a platform.
    """
    def __init__(self, platform, revision=None, verbose=False, interval=None):
        self.platform = platformdb.lookup(platform, revision)()
        self.sunits = []
        self.verbose = verbose
        self.default_interval = interval

    def config(self, config):
        """
        Read a sysledcontrol.conf config from a string

        configfile - config file string
        """
        raise NotImplementedError

    def read_config(self, configfile):
        """
        Read a sysledcontrol.conf config file and store it's key/value pairs in a dict.

        configfile - config file path
        """
        self.config(open(configfile, 'r').read())

#-------------------------------------------------------------------------------
#
# SystemLEDControl
#
#       Class which contains information for all system units that are being
#       monitored for system leds
#
class SystemLEDControl(Config):
    """
    Configuration database for all system units in the platform
    """
    def __init__(self, platform, revision=None, verbose=False, interval=0):
        Config.__init__(self, platform, revision, verbose, interval)

    def config(self, config):
        """
        Set the configuration for Status Monitor daemon
        and all the monitoring system units
        """
        self._calculate_configuration(config)
        self._calculate_sunit_configuration(config)

    def get_config_value(self, config, label, key, default_value):
        """
        Return the value for specified key under the label
        """
        configFP = StringIO.StringIO(config)

        parser = ConfigParser.RawConfigParser()
        parser.readfp(configFP)

        self.config_map = dict(parser.items(label))
        return self.config_map.get(key, default_value)

    def _calculate_configuration(self, config):
        """
        Set the configuration for Status monitoring,
        """
        self.interval = int(self.get_config_value(config, 'default',
                            'led_update_interval', self.default_interval))


    def _calculate_sunit_configuration(self, config):
        """
        Set the configuration for individual system units
        """
        self.sunit = []

        # create config objects for every system unit
        for sunit in self.platform.sysled.sunits:
            expected_unit_count = 0
            if sunit.has_config:
                expected_unit_count = int(self.get_config_value(config, sunit.label,
                            'count', sunit.default_unit_count))
            cp = SUnitConfig(sunit, expected_unit_count)

            self.sunits.append(cp)

    def init_operational_state(self):
        """
        Initialize Operational status database for monitoring system unit
        """
        sysledcontrolpath = '/var/cache/cumulus/sysledstate'
        try:
            os.makedirs(sysledcontrolpath)
        except OSError, e:
            if e.errno == errno.EEXIST:
                pass
            else:
                raise e

        # initialize state for every system unit
        for sunit in self.sunits:
            sunit.init_state()

    def update_state(self):
        """
        Update the state for all monitoring system units
        """
        change_led = None
        sunits = []
        for sunit in self.sunits:
            sunit.new_status = 'UNKNOWN'
            ret_state = sunit.update_state(self.platform)
            if ret_state:
                change_led = True
                if ret_state == 1:
                    sunit.new_status = 'OK'
                elif ret_state == 2:
                    sunit.new_status = 'ERROR'
                sunits.append(sunit)

        return (change_led, sunits)

    def set_leds(self):
        """
        Update the led(s) for all monitoring system units
        """
        for sunit in self.sunits:
            sunit.set_led(self.platform)

    def get_leds(self):
        """
        Return led state for all monitoring system units
        """
        led_map = ['System Unit :Led Color']

        for sunit in self.sunits:
            led_color = sunit.get_led(self.platform)
            if all([led_color != None, led_color != 'hw_ctrl']):
                led_map.append('%-12s:%s'
                    % (sunit.label, led_color))

        return '\n'.join(led_map)
