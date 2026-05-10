# Copyright 2014.  Cumulus Networks, Inc.

#-------------------------------------------------------------------------------
#
# Imports
#
import os
import re
import subprocess
import time
import cPickle
import exceptions
import syslog
#-------------------------------------------------------------------------------
#
# Classes
#
class Unit:
    """
    Base Class all for all Sensors.

    name - Name of the sensor
    description - Description about the sensor
    attrs - Contains the attributes obtained from sensors and
            other useful info
    handlers - dict containing state and handler method.
    status_path - Path where sensors info is stored. Used by smonctl.
    cpld_path - CPLD Path to access params
    driver_path - Driver Path to access params
    """
    attrs = None
    handlers = None
    status_path = '/var/cache/cumulus/unit_state'

    def __init__(self):

        self.attrs = dict()
        self.handlers = dict()
        if not hasattr(self, 'name'):
            self.attrs['name'] = self.__class__.__name__
        else:
            self.attrs['name'] = self.name
        if not hasattr(self, 'description'):
            self.attrs['description'] = self.attrs['name']
        else:
            self.attrs['description'] = self.description
        self.attrs['prev_state'] = 'UNKNOWN'
        self.attrs['state'] = 'UNKNOWN'
        self.attrs['msg'] = None
        self.attrs['prev_msg'] = None
        self.add_state('UNKNOWN', self.do_nothing)
        self.add_state('ABSENT', self.do_nothing)
        self.add_state('BAD', self.do_nothing)
        self.add_state('OK', self.do_nothing)

    def update_cpld_path(self, path):
        """
        Update the CPLD Path
        """
        self.cpld_path = path

    def update_cache(self):
        """
        Writes the sensor info at the status path.
        Default status path is: /var/cache/cumulus/unit_state
        """
        if not os.path.exists(self.status_path):
            os.makedirs(self.status_path)
        direct = os.path.join(self.status_path, self.attrs['name'])
        if not os.path.exists(direct):
            os.makedirs(direct)
        path = os.path.join(direct, 'state')
        f = open(path, 'w')
        f.write(self.attrs['state'] + '\n')
        f.close()
        path = os.path.join(direct, 'dump')
        f = open(path, 'w')
        cPickle.dump(self.attrs, f)
        f.close()

    def add_state(self, name, handler):
        """
        Add state and handler in the handlers dict
        """
        self.handlers[name] = handler

    def set_state(self, name):
        """
        Update the state, previous state and reset time
        spent in a state
        """
        self.attrs['prev_state'] = self.attrs['state']
        self.attrs['state'] = name
        cur_st = self.attrs['state']
        prev_st = self.attrs['prev_state']
        if cur_st != prev_st:
            self.reset_time()

    def detect_state_plat(self):
        """
        First thing that runs in detect_state. This is the place
        to add platform specific checks.
        Default returns 'OK'
        """
        return 'OK'

    def detect_state(self):
        """
        Detect the state the sensor is in.
        Return state. Default possible states are: UNKNOWN, ABSENT, OK and BAD.
        Default state is UNKNOWN
        """
        return 'UNKNOWN'

    def override_defaults(self):
        """
        override_defaults runs in detect_state after the attributes/values have
        been collected. Use this method to change/manipulate values.
        """
        pass

    def run_state(self):
        """
        Detect the state and run its handler.
        Update sensors information at the cache path
        """
        self.clear_msg()
        st = self.detect_state()
        self.set_state(st)
        if self.handlers[st] is not None:
            self.handlers[st]()
        self.update_cache()

    def do_nothing(self):
        """
        As said, do nothing. Used as a handler
        """
        pass

    def update_status(self, status, attr):
        if status is None:
            status = attr
        else:
            status = status + ', %s' %attr
        return status

    def update_msg(self, msg):
        """
        Add msg to the self.attrs in the format:
        name(description): msg
        attrs['msg'] can be used is a display tool to provide
        more info.
        """
        if self.attrs['msg'] is None:
            self.attrs['msg'] = ''
        else:
            self.attrs['msg'] += '\n'
        self.attrs['msg'] += '%s' %self.attrs['name']
        if self.attrs['name'] != self.attrs['description']:
            self.attrs['msg'] += '(%s)' %self.attrs['description']
        self.attrs['msg'] += (':  ' + msg)

    def clear_msg(self):
        """
        Copy attrs['msg'] to attrs['prev_msg'] (prev_state msg).
        set attrs['msg'] to None
        """
        self.attrs['prev_msg'] = self.attrs['msg']
        self.attrs['msg'] = None

    def reset_time(self):
        """
        Update attrs,start_time and log_time, with current time.
        start_time indicates when you got into a state.
        log_time is the time when the last log msg was created.
        log_time is used in thresh_handler and crit_handler.
        """
        attrs = ['start_time', 'log_time']
        y = int(time.time())
        for x in attrs:
            self.attrs[x] = y

    def update_attrs(self, path, hwmon):
        """
        At the given path, find attributes with hwmon(e.g. temp1, in1, fan2).
        The attributes are added to the dict: attrs.
        Return -1 if if attributes are not found.
        """
        return -1

    def find_and_add_attrs(self):
        """
        Each Sensor provides a cpld_path, driver_path or a pwm_path.
        Corresponding to the path is a hwmon (e.g. temp1, fan1, power1)
        Based on path and the hwmon find the attributes at the location
        and add it to the dict: attrs
        Return -1 on failure.
        """
        return -1

    def get_gpio_value(self, source):
        """
        Get the GPIO value from a given source. Path is:
        /sys/class/gpio/source/value
        """
        gpio_path = '/sys/class/gpio/'
        source += '/value'
        fn = os.path.join(gpio_path, source)
        try:
            value = open(fn, 'r').read()
        except:
            self.update_msg('Unable to update GPIO: %s' %source)
            return None
        return value.strip().rstrip('\0')

    def set_gpio_value(self, source, value):
        """
        Set the value at a given GPIO source. Path is:
        /sys/class/gpio/source/value
        """
        gpio_path = '/sys/class/gpio/'
        source += '/value'
        fn = os.path.join(gpio_path, source)
        try:
            fh = open(fn, 'w+')
            x = fh.write(value)
            fh.close()
        except:
            self.update_msg('Unable to update GPIO: %s' %source)
            return None
        return x

class PSU_Unit(Unit):
    """
    PSU System Unit.
    """
    def __init__(self):
        Unit.__init__(self)
        self.attrs['type'] = 'power'


    def update_attrs(self, path, hwmon):
        err = 0
        float_attrs = ['input']
        files = [ f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f)) ]
        for x in hwmon:
            count = 0
            for f in files:
                if re.match(x, f) is None:
                    continue
                count += 1
                with open(os.path.join(path, f)) as fp:
                    try:
                        val =  fp.read().rsplit('\n')[0]
                    except:
                        self.update_msg('Unable to read device')
                        err |= -1
                        break
                y = f.split('_', 1)
                if (len(y) > 1) and (y[1] in float_attrs):
                    if re.match('power', y[0]):
                        self.attrs[f] = float(val)/1000000
                    else:
                        # for current/voltage
                        self.attrs[f] = float(val)/1000
                elif f.endswith('alarm'):
                    self.attrs[f] = int(val)
                else:
                    self.attrs[f] = val
            if count == 0:
                self.update_msg('Unable to read device')
                err |= -1
        return err

    def find_and_add_attrs(self):
        err = 0
        for p in ['cpld', 'driver']:
            # find attributes only if path and hwmon are given
            if not hasattr(self, p + '_path'):
                continue
            if not hasattr(self, p + '_hwmon'):
                continue
            path = getattr(self, p + '_path')
            hwmon = getattr(self, p + '_hwmon')
            if not (os.path.isdir(path)):
                self.update_msg('%s Path:%s doesnt exist' %(p, path))
                err |= -1
                continue
            err |= self.update_attrs(path, hwmon)
        return err

    def get_status(self):
        # PSU status information is provided in the following ways:
        # 1. Binary format in files psu_pwr[0,1]_dc_ok, psu_pwr[0,1]_dc_power_ok,
        #    psu_pwr[0,1]_ac_ok, psu_pwr[0,1]_fan_ok, psu_pwr[0,1]_all_ok
        # 2. string format in psu_pwr[0,1] (installed, ok, dc_ok ...)
        # PSU power info in provided by a hwmon driver which has hwmon attrs like
        #    power[0-9]*_input, power[0-9]*_alarm, in[0-9]*_input ...
        status = None
        for key,value in self.attrs.iteritems():
            if re.match('psu_pwr[0-9]*_present', key):
                if int(value) > 0:
                    status = self.update_status(status, 'installed')
                else:
                    status = self.update_status(status, 'not_installed')
            elif re.match('psu_pwr[0-9]*_dc_ok', key):
                if int(value) == 0:
                    status = self.update_status(status, 'dc_not_ok')
                else:
                    status = self.update_status(status, 'dc_ok')
            elif re.match('psu_pwr[0-9]*_dc_power_ok', key):
                if int(value) == 0:
                    status = self.update_status(status, 'dc_not_ok')
                else:
                    status = self.update_status(status, 'dc_ok')
            elif re.match('psu_pwr[0-9]*_ac_ok', key):
                if int(value) == 0:
                    status = self.update_status(status, 'ac_not_ok')
                else:
                    status = self.update_status(status, 'ac_ok')
            elif re.match('psu_pwr[0-9]*_fan_ok', key):
                if int(value) == 0:
                    status = self.update_status(status, 'fan_not_ok')
                else:
                    status = self.update_status(status, 'fan_ok')
            elif re.match('psu_pwr[0-9]*_all_ok', key):
                if int(value) == 0:
                    status = self.update_status(status, 'all_not_ok')
                else:
                    status = self.update_status(status, 'ok')
            elif re.match('psu_pwr[0-9]*', key):
                status = self.update_status(status, value)

        if status is None:
            status = self.update_status(status, 'ok')
        return status

    def get_hwmon_info(self):
        err = 0; inp = None
        for key,value in self.attrs.iteritems():
            if re.match('power[0-9]*_input', key):
                inp = int(value)
            elif re.match('power[0-9a-z_]*_alarm', key):
                if int(value):
                    self.update_msg('%s alarm detected' %key)
                    err |= -1
            # Since we dont do current/voltage limit checks here, leaving the
            # alarm checks.
            elif re.match('in[0-9a-z_]*_alarm', key):
                if int(value):
                    self.update_msg('%s alarm detected' %key)
                    err |= -1
            elif re.match('curr[0-9a-z_]*_alarm', key):
                if int(value):
                    self.update_msg('%s alarm detected' %key)
                    err |= -1
        return(inp, err)


    def detect_state(self):
        st = self.detect_state_plat()
        if st != 'OK':
            return st

        if self.find_and_add_attrs():
            return 'ABSENT'

        status = self.get_status()
        inp, err = self.get_hwmon_info()

        status_attrs = status.replace(' ', '').split(',')
        if 'not_installed' in status_attrs:
            self.update_msg('Not installed')
            return 'ABSENT'
        if 'ok' not in status_attrs:
            self.update_msg('status is %s' %status)
            err |= -1
        if inp is not None:
            if (inp == 0):
                self.update_msg('Power input is at 0')
                err |= -1
        if err:
            return 'BAD'
        return 'OK'

class Fan_Unit(Unit):
    """
    Fan Sensor Unit.

    pwm_path - Path where PWM for a Fan exists
    fan_max - Max speed for the fan
    fan_max - Min speed for the fan
    fan_var - Variance of fan speed in %
    minpwm -  Min PWM value
    maxpwm - Max PWM value
    rpmmode - Indicates if fan is in RPM Mode
    """
    fan_max = 29000
    fan_min = 2500
    fan_var = 15
    minpwm = 64
    maxpwm = 255
    rpmmode = 0

    def __init__(self):
        Unit.__init__(self)
        self.attrs['type'] = 'fan'
        self.add_state('LOW', self.do_nothing)
        self.add_state('HIGH', self.do_nothing)

        if not hasattr(self, 'driver_hwmon'):
            self.driver_hwmon = ['fan1']

        if self.rpmmode:
            self.minpwm = self.fan_min
            self.maxpwm = self.fan_max
        else:
            if not hasattr(self, 'pwm_path'):
                self.pwm_path = self.driver_path
            if not hasattr(self, 'pwm_hwmon'):
                self.pwm_hwmon = ['pwm1']

    def override_defaults(self):
        self.attrs[self.driver_hwmon[0] + '_max'] = self.fan_max
        self.attrs[self.driver_hwmon[0] + '_min'] = self.fan_min
        self.attrs[self.driver_hwmon[0] + '_var'] = self.fan_var

    def update_attrs(self, path, hwmon):
        err = 0
        float_attrs = ['input', 'target']
        files = [ f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f)) ]
        for x in hwmon:
            count = 0
            for f in files:
                if re.match(x, f) is None:
                    continue
                count += 1
                with open(os.path.join(path, f)) as fp:
                    try:
                        val =  fp.read().rsplit('\n')[0]
                    except:
                        self.update_msg('Unable to read device')
                        err |= -1
                        break
                y = f.split('_', 1)
                #fan[0-9]*_input
                if (len(y) > 1) and (y[1] in float_attrs):
                    self.attrs[f] = int(val)
                #fan[0-9]*_alarm
                elif f.endswith('alarm'):
                    self.attrs[f] = int(val)
                #pwm and pwm_enable
                elif re.match('pwm[0-9]*', f):
                    self.attrs[f] = int(val)
                else:
                    self.attrs[f] = val
        if count == 0:
            self.update_msg('Unable to read device')
            err |= -1
        return err

    def find_and_add_attrs(self):
        """
        Each Sensor provides a cpld_path, driver_path or a pwm_path.
        Corresponding to the path is a hwmon (e.g. temp1, fan1, power1)
        Based on path and the hwmon find the attributes at the location
        and add it to the dict: attrs
        """
        err = 0
        for p in ['cpld', 'driver', 'pwm']:
            if not hasattr(self, p + '_path'):
                continue
            if not hasattr(self, p + '_hwmon'):
                continue
            path = getattr(self, p + '_path')
            hwmon = getattr(self, p + '_hwmon')
            if not (os.path.isdir(path)):
                self.update_msg('%s Path:%s doesnt exist' %(p, path))
                err |= -1
                continue
            err |= self.update_attrs(path, hwmon)
        return err

    def get_status(self):
        status = None
        for key, value in self.attrs.iteritems():
            if re.match('fan_[0-9]*', key):
                status = self.update_status(status, value)
            elif re.match('system_fan[0-9]*_present', key):
                if int(value) > 0:
                    status = self.update_status(status, 'installed')
                else:
                    status = self.update_status(status, 'not_installed')
            elif re.match('system_fan[0-9]*_ok', key):
                if int(value) > 0:
                    status = self.update_status(status, 'ok')
                else:
                    status = self.update_status(status, 'not_ok')
            elif re.match('fan[0-9]*_ok', key):
                if int(value) > 0:
                    status = self.update_status(status, 'ok')
                else:
                    status = self.update_status(status, 'not_ok')
        if status is None:
            status = self.update_status(status, 'ok')
        return status

    def get_hwmon_info(self):
        for key, value in self.attrs.iteritems():
            if re.match('fan[0-9]*_input', key):
                return int(value)
        return None

    def detect_state(self):
        st = self.detect_state_plat()
        if st != 'OK':
            return st

        if self.find_and_add_attrs():
            return 'ABSENT'
        self.override_defaults()

        status = self.get_status()
        inp = self.get_hwmon_info()

        status_attrs = status.replace(' ', '').split(',')
        if 'not_installed' in status_attrs:
            self.update_msg('Not installed')
            return 'ABSENT'
        if 'ok' not in status_attrs:
            self.update_msg('status is %s' %status)
            return 'BAD'
        if inp is not None:
            if (inp == 0):
                self.update_msg('Fan speed is at 0 RPM (not working or absent)')
                return 'ABSENT'
            elif (inp <= (self.fan_min * (1 - (float(self.fan_var)/100)))):
                self.update_msg('Fan input %d RPM is lower than %d RPM' %(inp, self.fan_min))
                return 'LOW'
            elif (inp >= (self.fan_max * (1 + (float(self.fan_var)/100)))):
                self.update_msg('Fan speed %d RPM greater than %d RPM' %(inp, self.fan_max))
                return 'HIGH'

        return 'OK'

class Board_Unit(Unit):
    """
    Board/System Unit.
    """

    def __init__(self):
        Unit.__init__(self)
        self.attrs['type'] = 'board'

    def update_attrs(self, path, hwmon):
        err = 0
        files = [ f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f)) ]
        for x in hwmon:
            count = 0
            for f in files:
                if re.match(x, f) is None:
                    continue
                count += 1
                with open(os.path.join(path, f)) as fp:
                    try:
                        val =  fp.read().rsplit('\n')[0]
                    except:
                        self.update_msg('Unable to read device')
                        err |= -1
                        break
                    self.attrs[f] = val
            if count == 0:
                self.update_msg('Unable to read device')
                err |= -1
        return err

    def find_and_add_attrs(self):
        err = 0
        for p in ['cpld', 'driver']:
            if not hasattr(self, p + '_path'):
                continue
            if not hasattr(self, p + '_hwmon'):
                continue
            path = getattr(self, p + '_path')
            hwmon = getattr(self, p + '_hwmon')
            if not (os.path.isdir(path)):
                self.update_msg('%s Path:%s doesnt exist' %(p, path))
                err |= -1
                continue
            err |= self.update_attrs(path, hwmon)
        return err

    def get_status(self):
        status = None
        for key, value in self.attrs.iteritems():
            if re.match('board_power', key):
                status = self.attrs['board_power']
            if re.match('system_all_ok', key):
                if int(value) > 0:
                    status = self.update_status(status, 'ok')
                else:
                    status = self.update_status(status, 'all_not_ok')
            if re.match('system_dc_power_ok', key):
                if int(value) > 0:
                    status = self.update_status(status, 'dc_ok')
                else:
                    status = self.update_status(status, 'dc_not_ok')
        if status is None:
            status = self.update_status(status, 'ok')
        return status

    def detect_state(self):
        st = self.detect_state_plat()
        if st != 'OK':
            return st

        if self.find_and_add_attrs():
            return 'ABSENT'

        status = self.get_status()
        status_attrs = status.replace(' ', '').split(',')
        if 'ok' not in status_attrs:
            self.update_msg(status)
            return 'BAD'
        return 'OK'

class Temp_Unit(Unit):
    """
    Temp Sensor Unit.

    Possible states: OK, BAD, UNKNOWN, ABSENT, HIGH, LOW, CRITICAL, LCRITICAL
    temp_crit = Critical Temp
    temp_max = Max Temp
    temp_max_hyst = Max Temp Hyst. (Used by pwm monitors)
    temp_min = Min Temp
    temp_lcrit = Low Crit Temp
    thres_log_interval = Log message and run if Temp is in HIGH/LOW state every
                         thres_log_interval secs
    crit_log_interval = Log message if Temp is in CRITICAL/LCRITICAL state every
                        crit_log_interval secs
    crit_shutdown_time = Shutdown system if sensor is in CRITICAL/LCRITICAL state
                         for crit_shutdown_time secs
    """
    temp_crit = 85
    temp_max = 80
    temp_max_hyst = 25
    temp_min = 5
    temp_lcrit = 0
    thres_log_interval = 300
    crit_log_interval = 10
    crit_shutdown_time = 60

    # Some common sensor names
    mac_die_sensor_name = "Networking ASIC Die Temp Sensor"
    mac_board_sensor_name = "Temp Sensor close to Networking ASIC"
    dimm_sensor_name = "DIMM Temp Sensor"
    intel_cpu_sensor_name = "Intel CPU die sensor"
    p2020_cpu_sensor_name = "P2020 CPU die sensor"

    def __init__(self):
        Unit.__init__(self)
        if not hasattr(self, 'driver_hwmon'):
            self.driver_hwmon = ['temp1']

        self.attrs['type'] = 'temp'
        self.attrs['start_time'] = None
        self.attrs['log_time'] = None
        self.add_state('HIGH', self.thres_handler)
        self.add_state('LOW', self.thres_handler)
        self.add_state('CRITICAL', self.crit_handler)
        self.add_state('LCRITICAL', self.crit_handler)

    def override_defaults(self):
        self.attrs[self.driver_hwmon[0] + '_max'] = self.temp_max
        self.attrs[self.driver_hwmon[0] + '_min'] = self.temp_min
        self.attrs[self.driver_hwmon[0] + '_crit'] = self.temp_crit
        self.attrs[self.driver_hwmon[0] + '_lcrit'] = self.temp_lcrit
        self.attrs[self.driver_hwmon[0] + '_max_hyst'] = self.temp_max_hyst

    def update_crit_action_path(self, path):
        """
        Sets crit_action_path which will point to the script which will run when 
        the unit status is CRTITICAL or LCRITICAL.
        """
        self.attrs['crit_action_path'] = path

    def update_thres_action_path(self, path):
        """
        Sets crit_action_path which will point to the script which will run when 
        the unit status is HIGH or LOW.
        """
        self.attrs['thres_action_path'] = path


    def update_attrs(self, path, hwmon):
        err = 0
        float_attrs = ['input']
        files = [ f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f)) ]
        for x in hwmon:
            # A driver could have 10 or more sensors. This is to differentiate temp1
            # from temp10
            x = x + '_'
            count = 0
            for f in files:
                if re.match(x, f) is None:
                    continue
                count += 1
                with open(os.path.join(path, f)) as fp:
                    try:
                        val =  fp.read().rsplit('\n')[0]
                    except:
                        self.update_msg('Unable to read device.')
                        err |= -1
                        break
                y = f.split('_', 1)
                if (len(y) > 1) and (y[1] in float_attrs):
                    self.attrs[f] = float(val)/1000
                elif f.endswith('alarm'):
                    self.attrs[f] = int(val)
                else:
                    self.attrs[f] = val
            if count == 0:
                self.update_msg('Unable to read device')
                err |= -1
        return err

    def find_and_add_attrs(self):
        err = 0
        for p in ['cpld', 'driver']:
            if not hasattr(self, p + '_path'):
                continue
            if not hasattr(self, p + '_hwmon'):
                continue
            path = getattr(self, p + '_path')
            hwmon = getattr(self, p + '_hwmon')
            if not (os.path.isdir(path)):
                self.update_msg('%s Path:%s doesnt exist' %(p, path))
                err |= -1
                continue
            err |= self.update_attrs(path, hwmon)
        return err

    def get_hwmon_info(self):
        inp = None; err = 0
        for key, value in self.attrs.iteritems():
            if re.match('temp[0-9a-z_]*_fault', key):
                if int(value):
                    self.update_msg('%s fault detected' %key)
                    err |= -1
            elif re.match('temp[0-9]*_input', key):
                inp = int(value)
        return (inp, err)

    def detect_state(self):
        st = self.detect_state_plat()
        if st != 'OK':
            return st

        if self.find_and_add_attrs():
            return 'ABSENT'
        self.override_defaults()

        inp, err = self.get_hwmon_info()

        if err == -1:
            return 'BAD'
        if inp is None:
            self.update_msg('Sensor has no value to read')
            return 'BAD'
        elif inp >= self.temp_crit:
            return 'CRITICAL'
        elif inp >= self.temp_max:
            return 'HIGH'
        elif inp <= self.temp_lcrit:
            return 'LCRITICAL'
        elif inp <= self.temp_min:
            return 'LOW'

        return 'OK'

    def thres_handler(self):
        """
        This is the handler when the state is HIGH or LOW.
        time_from_last_log indicates when the last log message was updated.
        time_in_state indicates how long unit has been in the state.
        This modules updates the msg attribute based on thres_log_interval,
        time_in_state and current time.
        Every time we in this handler, we run the script pointed by
        thres_action_path.
        """
        log_t = self.attrs['log_time']
        start_t = self.attrs['start_time']
        cur_t = int(time.time())
        time_from_last_log = cur_t - log_t
        time_in_state = cur_t - start_t
        temp = None
        for key, value in self.attrs.iteritems():
            if re.match('temp[0-9]*_input', key):
                temp = int(value)
        if time_from_last_log >= self.thres_log_interval:
            self.attrs['log_time'] = cur_t
            self.update_msg('Temperature(%d C) is %s for last %s secs' \
                            %(temp, self.attrs['state'],time_in_state))
        else:
            self.update_msg('Temperature(%d C) is %s for last %s secs' \
                            %(temp, self.attrs['state'],time_in_state))
            self.attrs['prev_msg'] = self.attrs['msg']
        if self.attrs['thres_action_path'] is not None:
            subprocess.call(self.attrs['thres_action_path'], shell=True)

    def crit_handler(self):
        """
        This is the handler when the state is CRITICAL or LCRITICAL.
        time_from_last_log indicates when the last log message was updated.
        time_in_state indicates how long unit has been in the state.
        time_to_shutdown is time left for shutdown action.
        This modules updates the msg attribute based on crit_log_interval,
        time_in_state, time_to_shutdown and current time.
        When time_in_state equals time_to_shutdown, shutdown the system.
        Every time we are in this handler, we run the script pointed by
        crit_action_path.
        """
        cur_t = int(time.time())
        log_t = self.attrs['log_time']
        start_t = self.attrs['start_time']
        time_from_last_log = cur_t - log_t
        time_in_state = cur_t - start_t
        time_to_shutdown = self.crit_shutdown_time - time_in_state
        temp = None
        for key, value in self.attrs.iteritems():
            if re.match('temp[0-9]*_input', key):
                temp = int(value)

        if time_to_shutdown <= 0:
            msg = 'Temperature %d C is %s for last %s secs. Shutting down the system' \
                  %(temp, self.attrs['state'], self.crit_shutdown_time)
            self.update_msg(msg)
            subprocess.call('echo %s | wall' %msg, shell=True)
            subprocess.call("poweroff", shell=True)
        else:
            if time_from_last_log >= self.crit_log_interval:
                self.attrs['log_time'] = cur_t
                msg = 'Temperature %d C is %s. System will shutdown in %s secs' \
                            %(temp, self.attrs['state'], time_to_shutdown)
                self.update_msg(msg)
                subprocess.call('echo %s | wall' %msg, shell=True)
        if self.attrs['crit_action_path'] is not None:
            subprocess.call(self.attrs['crit_action_path'], shell=True)

class Volt_Unit(Unit):

    volt_max = None
    volt_min = None

    def __init__(self):
        Unit.__init__(self)
        self.attrs['type'] = 'volt'

        if not hasattr(self, 'driver_hwmon'):
            self.driver_hwmon = ['in10']

    def override_defaults(self):
        self.attrs[self.driver_hwmon[0] + '_max'] = self.volt_max
        self.attrs[self.driver_hwmon[0] + '_min'] = self.volt_min

    def update_attrs(self, path, hwmon):
        err = 0
        float_attrs = ['input']
        files = [ f for f in os.listdir(path) if os.path.isfile(os.path.join(path,f)) ]
        for x in hwmon:
            count = 0
            for f in files:
                if re.match(x, f) is None:
                    continue
                count += 1
                with open(os.path.join(path, f)) as fp:
                    try:
                        val =  fp.read().rsplit('\n')[0]
                    except:
                        self.update_msg('Unable to read device')
                        err |= -1
                        break
                y = f.split('_', 1)
                if (len(y) > 1) and (y[1] in float_attrs):
                    self.attrs[f] = float(val)/1000
                elif f.endswith('alarm'):
                    self.attrs[f] = int(val)
                else:
                    self.attrs[f] = val
            if count == 0:
                self.update_msg('Unable to read device')
                err |= -1
        return err

    def find_and_add_attrs(self):
        err = 0
        for p in ['cpld', 'driver']:
            if not hasattr(self, p + '_path'):
                continue
            if not hasattr(self, p + '_hwmon'):
                continue
            path = getattr(self, p + '_path')
            hwmon = getattr(self, p + '_hwmon')
            if not (os.path.isdir(path)):
                self.update_msg('%s Path:%s doesnt exist' %(p, path))
                err |= -1
                continue
            err |= self.update_attrs(path, hwmon)
        return err

    def get_hwmon_info(self):
        for key, value in self.attrs.iteritems():
            if re.match('in[0-9]*_input', key):
                return float(value)
        return None

    def detect_state(self):
        st = self.detect_state_plat()
        if st != 'OK':
            return st

        if self.find_and_add_attrs():
            return 'ABSENT'
        self.override_defaults()

        inp = self.get_hwmon_info()
        if inp is None:
            self.update_msg('Sensor has no value to read')
            return 'BAD'
        elif inp <= 0:
            self.update_msg('Voltage is 0, sensor maybe absent or not working')
            return 'ABSENT'
        if self.volt_min is not None:
            if (inp <= self.volt_min):
                self.update_msg('%s V is less than min voltage %s V' %(inp, self.volt_min))
                return 'LOW'
        if self.volt_max is not None:
            if (inp >= self.volt_max):
                self.update_msg('%s V is greater than max voltage %s V' %(inp, self.volt_max))
                return 'HIGH'
        return 'OK'

class PWM_Unit():
    """
    PWM Unit.

    fans - dictionary containing fan name and Fan Unit
    temps - dictionary containing Temp name and Temp Unit
    """

    fans = None
    temps = None
    attrs = None

    def __init__(self):
        self.attrs = dict()
        if not hasattr(self, 'name'):
            self.attrs['name'] = self.__class__.__name__
        else:
            self.attrs['name'] = self.name
        if not hasattr(self, 'description'):
            self.attrs['description'] = self.attrs['name']
        else:
            self.attrs['description'] = self.description

        self.attrs['fans'] = dict()
        self.attrs['temps'] = dict()

        for x in self.fans:
            self.attrs['fans'][x.attrs['name']] = x
        for x in self.temps:
            self.attrs['temps'][x.attrs['name']] = x

    def update_msg(self, msg):
        syslog.syslog(syslog.LOG_WARNING, msg)

    def update_temps(self):
        for name, t in self.attrs['temps'].iteritems():
            t.find_and_add_attrs()

    def calc_speed(self, fan):
        """
        For a given fan, calculate the PWM value using Temp Units
        in attrs['temps'] dict.
        For a given temp sensor:
        speed = minpwm + (temp - max_hyst)*(maxpwm - minpwm)/(max - max_hyst)
        Max speed among given temp sensors is returned.
        """
        speed = fan.minpwm
        for name, t in self.attrs['temps'].iteritems():
            t_in = None
            for key, value in t.attrs.iteritems():
                if re.match('temp[0-9]*_input', key):
                    t_in = int(value)

            if t_in < t.temp_max_hyst:
                tmp = fan.minpwm
            elif t_in > t.temp_max:
                tmp = fan.maxpwm
            else:
                tmp = int(fan.minpwm +
                          (t_in - t.temp_max_hyst) * (fan.maxpwm - fan.minpwm) /
                          (t.temp_max - t.temp_max_hyst))
            if tmp > speed:
                speed = tmp
        return speed

    def read_speed(self, fan):
        """
        Read the Fan speed using pwm_path and pwm_hwmon.
        If RPM mode, path is driver_path and driver_hwmon.
        """
        if fan.rpmmode == 1:
            target = fan.driver_hwmon[0] + '_target'
            path = os.path.join(fan.driver_path, target)
        else:
            target = fan.pwm_hwmon[0]
            path = os.path.join(fan.pwm_path, target)

        # print 'speed: %s path %s' %(speed, path)
        self.attrs['speed'] = 'unknown'
        if os.path.exists(path):
            try:
                with open(path, 'r') as fp:
                    self.attrs['speed'] = fp.read().strip('\n')
            except:
                self.attrs['speed'] = 'unknown'

        return self.attrs['speed']

    def set_speed(self, fan, speed):
        """
        Update the Fan speed using pwm_path and pwm_hwmon.
        If RPM mode, path is driver_path and driver_hwmon.
        """
        if fan.rpmmode == 1:
            target = fan.driver_hwmon[0] + '_target'
            path = os.path.join(fan.driver_path, target)
        else:
            path = os.path.join(fan.pwm_path, fan.pwm_hwmon[0] + '_enable')
            if os.path.exists(path):
                try:
                    with open(path, 'w') as fp:
                        fp.write('1')
                except:
                    return
            target = fan.pwm_hwmon[0]
            path = os.path.join(fan.pwm_path, target)
        # print 'speed: %s path %s' %(speed, path)
        if os.path.exists(path):
            try:
                with open(path, 'w') as fp:
                    fp.write(str(speed))
            except:
                return

    def run_state(self):
        self.update_temps()
        for name, fan in self.attrs['fans'].iteritems():
            speed = self.calc_speed(fan)
            self.set_speed(fan, speed)

class StatusLED_Unit():
    """
    Status LED Unit.
    Manages Status LED present on the front panel

    sources - Indicates the sensors to look at. Sensors state is obtained from
              /var/cache/cumulus/unit_state/source/state
              If None, look at all the the sensors in unit_state.
    good_states - If all sources, have good_state, set good_led_color.
    good_led_color - If all sources, have good_state, set good_led_color,
                     default is green.
    bad_states - If any of the sources, have bad_state, set bad_led_color.
    bad_led_color - If any of the sources, have bad_state, set bad_led_color,
                    default is yellow.
    led_path  - Location of the LED, if not specified, use CPLD path.
    led_location - Led is at led_path/led_location.
    """
    sources = None
    good_states = ('OK',)
    bad_states = ('BAD', 'UNKNOWN', 'ABSENT', 'HIGH', 'LOW', 'CRITICAL', 'LCRITICAL')
    good_led_color = 'green'
    bad_led_color = 'yellow'
    attrs = None
    status_path = '/var/cache/cumulus/unit_state'

    def __init__(self):

        self.attrs = dict()
        self.handlers = dict()
        if not hasattr(self, 'name'):
            self.attrs['name'] = self.__class__.__name__
        else:
            self.attrs['name'] = self.name
        if not hasattr(self, 'description'):
            self.attrs['description'] = self.attrs['name']
        else:
            self.attrs['description'] = self.description

    def update_msg(self, msg):
        syslog.syslog(syslog.LOG_WARNING, msg)

    def update_cpld_path(self, path):
        """
        Update the CPLD Path as led_path
        """
        if not hasattr(self, 'led_path'):
            self.led_path = path

    def led_update_status(self):
        """
        Return a dict of source and state.
        """
        status = dict()

        if os.path.exists(self.status_path):
            files = os.listdir(self.status_path)
        else:
            return status

        if self.sources is None:
            self.sources = files

        for x in self.sources:
            if x in files:
                path = os.path.join(self.status_path, x, 'state')
                # ledmgrd can reach here before smond has created the status files for sensors.
                # In such a case, assume the sensor is absent, and move on, instead of crashing.
                try:
                    fp = open(path, 'r')
                    status[x] = fp.read().strip('\n')
                    fp.close()
                except IOError, e:
                    status[x] = 'ABSENT'
        return status

    def led_find_color(self, status):
        """
        If any of the sources has bad_state, return bad_led_color.
        Else return good_led_color.
        """
        color = self.good_led_color
        for source in self.sources:
            if status.has_key(source):
                state = status[source]
                if state in self.bad_states:
                    color = self.bad_led_color
                    break
        return color

    def led_update(self, color):
        """
        Update the led color at  led_path/led_location
        """
        path = os.path.join(self.led_path, self.led_location)
        # print '%15s: %s' %(self.led_location, color)
        try:
            fp = open(path, 'w')
            fp.write(color)
            fp.close()
        except:
            self.update_msg('Cannot update led: %s' %self.led_location)

    def led_read(self):
        """
        Read the led at led_path/led_location
        """
        path = os.path.join(self.led_path, self.led_location)
        try:
            fp = open(path, 'r')
            color = fp.read().strip('\n')
            fp.close()
        except:
            self.update_msg('Cannot update led: %s' %self.led_location)
        return self.attrs['name'], color

    def run_state(self):
        """
        From the dict of (source, state), find the led color and
        update it.
        """
        if not os.path.exists(self.status_path):
            # Dont update till smond writes to status_path
            return
        status = self.led_update_status()
        color = self.led_find_color(status)
        self.led_update(color)

    def get_gpio_value(self, source):
        """
        Get the GPIO value from a given source. Path is:
        /sys/class/gpio/source/value
        """
        gpio_path = '/sys/class/gpio/'
        source += '/value'
        fn = os.path.join(gpio_path, source)
        try:
            value = open(fn, 'r').read()
        except:
            self.update_msg('Unable to read GPIO: %s' %source)
            return None

        return value.strip().rstrip('\0')

    def set_gpio_value(self, source, value):
        """
        Set the value at a given GPIO source. Path is:
        /sys/class/gpio/source/value
        """
        gpio_path = '/sys/class/gpio/'
        source += '/value'
        try:
            fn = os.path.join(gpio_path, source)
            fh = open(fn, 'w+')
            x = fh.write(value)
            fh.close()
        except:
            self.update_msg('Unable to update GPIO: %s' %source)
            return None
        return x
