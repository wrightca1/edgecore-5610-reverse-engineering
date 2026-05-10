#
# Copyright 2013.  Cumulus Networks, Inc.
#
# sunit.py --
#     System units which are shared platform-specific objects.  Typically used by
#     specific switch platforms defined in platformdb.py
#

#-------------------------------------------------------------------------------
#
# Imports
#
import errno
import struct
import os


#-------------------------------------------------------------------------------
#
# Classes
#
class NoSuchSUnit(RuntimeError):
    pass

#-------------------------------------------------------------------------------
#
# System Unit
#       Base class to represent  system unit which controls system LEDs. All
#       system units inherit from this class and customize platform specific as
#       well as system unit specific information.
#
class SystemUnit:
    """
    System Unit.

    label - Name of the system unit
    state - state of the unit
    states - Possible states for a system unit

    sources - Files which determine the state of the system unit.
                i.e. <cpld-path>/psu_pwr1
    System Unit operational status will be derived from multiple sources.

    operational_status_file - Files which maintain state of the system unit
    led_location - Files which have the led information
    state_ledcolor_map - Dict which represents mapping between state to color

    sources, led_location, state_ledcolor_map should be defined
    for all system units under every platform.

    default_unit_count - Minimum count required for system to function properly
    has_config - Boolean whether system unit requires configuration
    """
    label = None
    states = ('OK', 'BAD')
    default_state = states[0]
    state = default_state

    _state_ledcolor_map = {}
    _state_gpio_map = {}
    sources = ()
    led_location = None

    operational_status_file = None

    default_unit_count = 0
    has_config = None

    def __init__(self, label):
        self.label = label

    def _calculate_state(self, platform, expected_unit_count):
        """
        Determine state of the system unit based on
        status of sources.
        """
        raise NotImplementedError

#-------------------------------------------------------------------------------
#
# CPLDSUnit
#
#       Class which contains all accessors for cpld specific information.
#       Both the status and led information for system units is managed by CPLD
#

class CPLDSUnit(SystemUnit):
    """
     CPLD System Unit.

     Accessors for managing attributes in cpld
    """
    def set_cpld_status(self, platform, source, state):
        """
         Set State configuration in CPLD (if any).
        """
        setattr(platform.cpld, source, state)


    def get_cpld_status(self, platform, source):
        """
        Get CPLD status configuration from hardware (if any).
        """
        return getattr(platform.cpld, source)


    def set_led_color(self, platform,  state):
        """
        Set LED color configuration in hardware (if any).
        """
        if all([self.led_location != None, self._state_ledcolor_map]):
            if self._state_gpio_map:
                self.set_gpio_value(platform, self.led_location,
                            self._state_gpio_map[state])
            else:
                self.set_cpld_status(platform, self.led_location,
                            self._state_ledcolor_map[state])

    def get_led_color(self, platform):
        """
        Get LED color configuration from hardware (if any).
        """
        color = None
        if self.led_location != None:
            if self._state_gpio_map:
                value = self.get_gpio_value(platform, self.led_location)
                for state in self._state_gpio_map:
                    if self._state_gpio_map[state] == value:
                        color = self._state_ledcolor_map[state]
                        break
            else:
                color = self.get_cpld_status(platform, self.led_location)
        return color

#-------------------------------------------------------------------------------
#
# SMonSUnit
#
#       Class which contains  accessors for oeprational status of system unit.
#       Accessors for set/get oeprational status
#
#
class SMonSUnit(CPLDSUnit):
    """
     Status Monitoring System Unit.

     Accessors for managing unit attributes
    """

    sunit_status_path = '/var/cache/cumulus/sysledstate/'
    gpio_path = '/sys/class/gpio/'

    def __init__(self, label):
        SystemUnit.__init__(self, label)
        self.label = label

    def get_value(self, path, name):
        """
        Get the Operational Staus for the system unit
        """
        fn = os.path.join(path, name)
        try:
            value = open(fn, 'r').read()
        except IOError, e:
            if e.errno == errno.ENOENT:
                raise AttributeError('sunit_status has no entry: %s' % fn)
            else:
                raise e

        return value.strip().rstrip('\0')

    def set_value(self, path, name, value):
        """
        Set the Operational Status i.e. /var/cache/cumulus/sysledstate
        """
        fn = os.path.join(path, name)
        try:
            fh = open(fn, 'w+')
        except IOError, e:
            if e.errno == errno.ENOENT:
                raise AttributeError('sunit_status has no entry: %s' % fn)
            else:
                raise e

        return fh.write(value)

    def get_operational_status(self, name):
        """
        Get the Operational Staus for the system unit
        """
        return self.get_value(self.sunit_status_path, name)

    def set_operational_status(self, name, value):
        """
        Set the Operational Status i.e. /var/cache/cumulus/sysledstate
        """
        return self.set_value(self.sunit_status_path, name, value)

    def set_gpio_value(self, platform, source, value):
        """
         Set State configuration in GPIO (if any).
        """
        source += '/value'
        return self.set_value(self.gpio_path, source, value)

    def get_gpio_value(self, platform, source):
        """
        Get GPIO value from hardware (if any).
        """
        source += '/value'
        return self.get_value(self.gpio_path, source)

    def set_state(self, state):
        """
        Set the state i.e. /var/cache/cumulus/sysledstate
        """
        self.set_operational_status(self.operational_status_file, state)

    def init_state(self):
        """
        Initialize the state
        """
        self.set_state("UNKNOWN")

    def get_state(self):
        """
        Return state of the unit
        """
        return self.get_operational_status(self.operational_status_file)

    def update_state(self, platform, expected_unit_count):
        """
        Determine and update  state of the unit
        Return values
        1 - If the state changed to good
        2 - If the state changed to bad

        """
        cur_state =  self.get_state()
        expected_state = self._calculate_state(platform,expected_unit_count)
        if cur_state != expected_state:
            self.set_state(expected_state)
            if expected_state == 'OK':
                return 1
            else:
                return 2
        else:
            return 0

    def set_led(self, platform):
        """
        Set the LED color based on the current state of the nent
        """
        cur_state =  self.get_state()
        return self.set_led_color(platform, cur_state)

    def get_led(self, platform):
        """
        Get the configured LED color
        """
        return self.get_led_color(platform)

#-------------------------------------------------------------------------------
#
# PSU
#
#       Class which monitors individual power supply unit
#
#
class PSU(SMonSUnit):
    """
      Individual Pluggable Power Supply Unit.
    """
    led_location = None
    _state_ledcolor_map = {}

    def __init__(self, unit):
        if unit == 1:
            SystemUnit.__init__(self, label="psu_1")
            self.operational_status_file = "psu_pwr1"
        elif unit == 2:
            SystemUnit.__init__(self, label="psu_2")
            self.operational_status_file = "psu_pwr2"


#-------------------------------------------------------------------------------
#
# PSUCombo
#
#       Class which monitors operational status of all power supply units in the
#       system and determines operational status of entire PSU sub system based on
#       redundancy policy configuration
#
#       Expected number of units - policy behavior
#       1 - Redundant Power Supply not required
#       2 - Redundant Power Supply should be operational
#
#       Note: Only for PSU Combo, sources are common across all platforms
#
class PSUCombo(SMonSUnit):
    """
      Combination of all PSUs in the system
    """
    sources = ('psu_pwr1', 'psu_pwr2')
    operational_status_file = "psu_power"

    default_unit_count = 2
    has_config = True

    def __init__(self):
        SystemUnit.__init__(self, label="psu_status")

    def _calculate_state(self, platform, expected_unit_count):
        """
        Expected number of power system unit is based on configuration.

        Expected number of power system unit : 2
        BAD - One of PS is BAD
        OK  - Two PSU(s) is running OK


        Expected number of power system unit : 1
        BAD - Both the PSU(s) are PS_POWER_BAD, PS_FAN_BAD, PS_TEMP_BAD
                or PS_NOT_INSTALLED
        OK  - atleast one PS is running OK
        """
        state = self.default_state
        num_unit = len(self.sources)
        for power_source in self.sources:
            status =  self.get_operational_status(power_source)
            if status != 'OK':
                num_unit -= 1

        if num_unit < expected_unit_count:
            state = 'BAD'

        return state

#-------------------------------------------------------------------------------
#
# FAN
#
#       Class which monitors operational status of all system fans subsystem
#
#
class Fan(SMonSUnit):
    """
      System Fan Unit.
    """
    operational_status_file = "fan"
    led_location = "led_fan"

    def __init__(self, label):
        SystemUnit.__init__(self, label)


#-------------------------------------------------------------------------------
#
# Board Power
#
#       Class which monitors operational status of Power Rails
#
#
class BoardPower(SMonSUnit):
    """
      Board Power Unit.
    """
    sources = ('board_power')
    operational_status_file = "board_power"

    def __init__(self):
        SystemUnit.__init__(self, label="board power")

    def _calculate_state(self, platform, expected_unit_count):
        state = self.default_state

        status =  self.get_cpld_status(platform, 'board_power')
        if status != 'ok':
            state = 'BAD'

        return state

#-------------------------------------------------------------------------------
#
# System
#
#       Class which monitors operational status of Entire System
#
#
class System(SMonSUnit):
    """
      Platform Status.
    """
    states = ('OK', 'ERROR')
    default_state = states[0]

    operational_status_file = "system_status"

    def __init__(self):
        SystemUnit.__init__(self, label="system")


    def _calculate_state(self, platform, expected_unit_count):
        """
        ERROR - One of system units i.e. Fan/PSU is Bad
        OK  - All units listed under sources are running OK
        """
        state = self.default_state
        for source in self.sources:
            status =  self.get_operational_status(source)
            if status != 'OK':
                state = 'ERROR'
                break

        return state
