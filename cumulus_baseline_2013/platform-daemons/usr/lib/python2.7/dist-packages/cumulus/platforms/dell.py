#
# Copyright 2012.  Cumulus Networks, Inc.
#
# dell.py --
#     DELL switch platforms
#

import cumulus.platform
import cumulus.cpld
import cumulus.ledup
import cumulus.sunit
import cumulus.sfp
import os
import subprocess
import syslog

class DellS6000QSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; DellS6000QSFPp
;;; - one led: on for link and flash with activity (low active)
set_led:
;;; this is a common entry point for any port to set its single led
set_any_led:
        port    a
        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        tinv
        pack

        ret
'''
    _set_led_4x10_even = '''
;;;  handle the four ports on this QSFP
;;;   on even ports the layout is 2 1 4 3
set_led:
        inc     a
        call    set_any_led
        dec     a
        call    set_any_led
        add     a,3
        call    set_any_led
        dec     a
        call    set_any_led
        ret
'''
    _set_led_4x10_odd = '''
;;;  handle the four ports on this QSFP
;;;   on odd ports the layout is 1, 2, 3, 4
set_led:
set_loop:
        call    set_any_led
        inc     a
        call    set_any_led
        inc     a
        call    set_any_led
        inc     a
        call    set_any_led
        ret
'''
    def __init__(self, label, serdes, leds, rx_lane_map, tx_lane_map,
                 rx_polarity_flip=None, tx_polarity_flip=None, 
                 pre_emphasis=None, drv_current=None, pre_drv_current=None):
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                    label=label,
                                                    serdes=serdes,
                                                    phy_types=None,
                                                    phy_addrs=None,
                                                    leds=leds,
                                                    rx_lane_map=rx_lane_map,
                                                    rx_polarity_flip=rx_polarity_flip,
                                                    tx_lane_map=tx_lane_map,
                                                    tx_polarity_flip=tx_polarity_flip,
                                                    pre_emphasis=pre_emphasis,
                                                    drv_current=drv_current,
                                                    pre_drv_current=pre_drv_current,
                                                    oversub=True,
                                                    unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        ''' - 4 leds per QSFP
            - in 40G mode, the first led indicates link/activity
            - in 4x10G mode, all four leds are used - one for each breakout port
            - led layouts are different for odd and even ports
        '''
        self._check_mode(mode)
        set_calls = {}

        if mode == "4x10G" and sub != 0:
            return set_calls

        fn_name = '%s' % self.__class__.__name__
        remap = 0
        if mode == "4x10G":
            for i in range(4):
                set_calls[self.leds[1] + i] = None
            if self._is_even_port():
                call = (fn_name + "_4x10_e", self._set_led_4x10_even, led_port)
            else:
                call = (fn_name + "_4x10_odd", self._set_led_4x10_odd, led_port)
        elif mode == "40G":
            if self._is_even_port():
                remap = 1
            call = (fn_name, self._set_led, led_port)
        set_calls[self.leds[1] + remap] = call

        return set_calls

    def _is_even_port(self):
        return (self.leds[1] / 4) & 1

class DellS6000LED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 64

class DellS6000CPLD(cumulus.cpld.SysFS):
    path = '/sys/bus/platform/devices/dell_s6000_cpld.0'


'''
   Dell S6000 LEDS
     System:
       green - all systems ok
       green blinking - fan missing or broken, psu missing or broken
     Power:
       green - both psu installed and working
       yellow blinking - psu missing or malfunction
     Fan:
       green - all 3 fans installed and working
       yellow blinking - fan missing or malfunction
     Fan_Tray_X (0 - 2):
       green - fan X installed and working
       yellow - fan X malfunction
     Master:
       off
'''

def DellS6000_get_paths():
    # Quick hack to prevent other platforms from running this. CM-2908
    # Need to fix this elegantly.
    plat = os.popen('platform-detect -m').read().strip()
    if plat != 'dell,s6000_s1220':
       return '', ''

    isch_path = '/sys/bus/pci/devices/0000:00:1f.0/isch_smbus.3168'
    if os.path.exists(isch_path):
        for x in os.listdir(isch_path):
            if x.startswith('i2c-'):
                isch_path = os.path.join(isch_path, x)
                break

    ismt_0_13_1_path = '/sys/bus/pci/devices/0000:00:13.1'
    if os.path.exists(ismt_0_13_1_path):
        for x in os.listdir(ismt_0_13_1_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                ismt_0_13_1_path = os.path.join(ismt_0_13_1_path, x) + '/' + b
                break

    return isch_path, ismt_0_13_1_path

DellS6000_isch_path, DellS6000_ismt_0_13_1_path = DellS6000_get_paths()
DellS6000_i2c_11_2a_path = DellS6000_isch_path + '/i2c-11/11-002a'
DellS6000_i2c_11_29_path = DellS6000_isch_path + '/i2c-11/11-0029'
DellS6000_i2c_10_4d_path = DellS6000_isch_path + '/i2c-10/10-004d'
DellS6000_i2c_2_58_path = DellS6000_ismt_0_13_1_path + '-0058'
DellS6000_i2c_2_59_path = DellS6000_ismt_0_13_1_path + '-0059'
DellS6000_w83627ehf_path = '/sys/devices/platform/w83627ehf.2560'

class DellS6000PSULED(cumulus.sensors.StatusLED_Unit):
    name = 'PSUs'
    sources = ['PSU1', 'PSU2']
    led_location = 'led_power'
    bad_led_color = 'yellow_blinking'

class DellS6000SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_system'
    bad_led_color = 'green_blinking'

class DellS6000FanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fans'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4', 'Fan5', 'Fan6']
    led_location = 'led_fan'
    bad_led_color = 'yellow_blinking'

class DellS6000Fan1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 1'
    sources = ['Fan1', 'Fan2']
    led_location = 'led_fan_tray_0'
    bad_led_color = 'yellow'

class DellS6000Fan2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 2'
    sources = ['Fan3', 'Fan4']
    led_location = 'led_fan_tray_1'
    bad_led_color = 'yellow'

class DellS6000Fan3LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 3'
    sources = ['Fan5', 'Fan6']
    led_location = 'led_fan_tray_2'
    bad_led_color = 'yellow'

class DellS6000Temp(cumulus.sensors.Temp_Unit):
    temp_crit = 85
    temp_max = 50
    temp_max_hyst = 25

class DellS6000Temp1(DellS6000Temp):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = DellS6000_isch_path + '/i2c-11/11-004c'

class DellS6000Temp2(DellS6000Temp):
    name = 'Temp2'
    description = 'Board Sensor near NIC'
    driver_path = DellS6000_isch_path + '/i2c-11/11-004d'

class DellS6000Temp3(DellS6000Temp):
    name = 'Temp3'
    description = 'Ambient Temp Sensor'
    driver_path = DellS6000_isch_path + '/i2c-11/11-004e'

class DellS6000Temp4(DellS6000Temp):
    name = 'Temp4'
    description = 'CPU0 Temp Sensor'
    driver_path = DellS6000_i2c_10_4d_path

class DellS6000Temp5(DellS6000Temp):
    name = 'Temp5'
    description = 'CPU1 Temp Sensor'
    driver_path = DellS6000_i2c_10_4d_path
    driver_hwmon = ['temp2']

class DellS6000Temp6(DellS6000Temp):
    name = 'Temp6'
    description = 'SoC Temp Sensor'
    driver_path = DellS6000_i2c_10_4d_path
    driver_hwmon = ['temp3']

class DellS6000Temp7(DellS6000Temp):
    name = 'Temp7'
    description = cumulus.sensors.Temp_Unit.dimm_sensor_name
    driver_path = DellS6000_isch_path + '/i2c-10/10-0018'
    driver_hwmon = ['temp1']

class DellS6000PSUTemp(cumulus.sensors.Temp_Unit):
    temp_crit = 70
    temp_max = 65
    temp_max_hyst = 25
    psu = None

    def find_and_add_attrs(self):
        state = 'OK'
        try:
            path = os.path.join(self.status_path, self.psu, 'state')
            with open(path) as fp:
                state = fp.read().rsplit('\n')[0]
        except:
            return -1
        if (state != 'OK'):
            return -1
        return cumulus.sensors.Temp_Unit.find_and_add_attrs(self)

class DellS6000Temp8(DellS6000PSUTemp):
    name = 'PSU1Temp1'
    description = 'PSU1 Temp Sensor'
    driver_path = DellS6000_i2c_2_59_path
    driver_hwmon = ['temp1']
    psu = 'PSU1'

class DellS6000Temp9(DellS6000PSUTemp):
    name = 'PSU1Temp2'
    description = 'PSU1 Temp Sensor'
    driver_path = DellS6000_i2c_2_59_path
    driver_hwmon = ['temp2']
    psu = 'PSU1'

class DellS6000Temp10(DellS6000PSUTemp):
    name = 'PSU2Temp1'
    description = 'PSU2 Temp Sensor'
    driver_path = DellS6000_i2c_2_58_path
    driver_hwmon = ['temp1']
    psu = 'PSU2'

class DellS6000Temp11(DellS6000PSUTemp):
    name = 'PSU2Temp2'
    description = 'PSU2 Temp Sensor'
    driver_path = DellS6000_i2c_2_58_path
    driver_hwmon = ['temp2']
    psu = 'PSU2'

# TODO: add T2 internal sensor

class DellS6000Fan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    fan_max = 19000
    fan_min = 7200

class DellS6000PSUFan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    fan_max = 18000
    fan_min = 7000
    psu = None

    def find_and_add_attrs(self):
        state = 'OK'
        try:
            path = os.path.join(self.status_path, self.psu, 'state')
            with open(path) as fp:
                state = fp.read().rsplit('\n')[0]
        except:
            return -1
        if (state != 'OK'):
            return -1
        return cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class DellS6000Fan1(DellS6000Fan):
    name = 'Fan1'
    description = 'Fan Tray 0'
    driver_path = DellS6000_i2c_11_29_path
    cpld_hwmon = ['fan_0']

class DellS6000Fan2(DellS6000Fan):
    name = 'Fan2'
    description = 'Fan Tray 0'
    driver_path = DellS6000_i2c_11_29_path
    driver_hwmon = ['fan2']
    cpld_hwmon = ['fan_0']

class DellS6000Fan3(DellS6000Fan):
    name = 'Fan3'
    description = 'Fan Tray 1'
    driver_path = DellS6000_i2c_11_29_path
    driver_hwmon = ['fan3']
    cpld_hwmon = ['fan_1']

class DellS6000Fan4(DellS6000Fan):
    name = 'Fan4'
    description = 'Fan Tray 1'
    driver_path = DellS6000_i2c_11_29_path
    driver_hwmon = ['fan4']
    cpld_hwmon = ['fan_1']

class DellS6000Fan5(DellS6000Fan):
    name = 'Fan5'
    description = 'Fan Tray 2'
    driver_path = DellS6000_i2c_11_2a_path
    cpld_hwmon = ['fan_2']

class DellS6000Fan6(DellS6000Fan):
    name = 'Fan6'
    description = 'Fan Tray 2'
    driver_path = DellS6000_i2c_11_2a_path
    driver_hwmon = ['fan2']
    cpld_hwmon = ['fan_2']

class DellS6000Fan7(DellS6000PSUFan):
    name = 'PSU1Fan1'
    description = 'PSU1 Fan'
    driver_path = DellS6000_i2c_2_59_path
    driver_hwmon = ['fan1']
    psu = 'PSU1'

class DellS6000Fan8(DellS6000PSUFan):
    name = 'PSU2Fan1'
    description = 'PSU2 Fan'
    driver_path = DellS6000_i2c_2_58_path
    driver_hwmon = ['fan1']
    psu = 'PSU2'

class DellS6000PSU(cumulus.sensors.PSU_Unit):
    init_done = False
    def __init__(self):
        cumulus.sensors.PSU_Unit.__init__(self)
        self.add_state('OK', self.ok_handler)

    def ok_handler(self):
        if self.init_done:
            return
        err_states = ['BAD', 'ABSENT'];
        if self.attrs['prev_state'] in err_states:
            cmd = 'rmmod dni_dps460 && modprobe dni_dps460'
            subprocess.call(cmd, shell=True)
            self.init_done = True

class DellS6000PSU1(DellS6000PSU):
    name = 'PSU1'
    driver_path = DellS6000_isch_path + '/i2c-11/11-0042'
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr1']

class DellS6000PSU2(DellS6000PSU):
    name = 'PSU2'
    driver_path = DellS6000_isch_path + '/i2c-11/11-0040'
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr2']

# The range for the voltage sensors in +/- 15% of the base value seen.
# This is an approximation, as range is not provided.
class DellS6000Volt1(cumulus.sensors.Volt_Unit):
    name = 'Volt1'
    description = 'CPU VCore'
    volt_min = 0.89
    volt_max = 1.21
    driver_path = DellS6000_w83627ehf_path
    driver_hwmon = ['in0']

class DellS6000Volt2(cumulus.sensors.Volt_Unit):
    name = 'Volt2'
    description = 'DDR VTT'
    volt_min = 1.00
    volt_max = 1.36
    driver_path = DellS6000_w83627ehf_path
    driver_hwmon = ['in4']

class DellS6000Volt3(cumulus.sensors.Volt_Unit):
    name = 'Volt3'
    description = '+3.3V'
    volt_min = 2.82
    volt_max = 3.82
    driver_path = DellS6000_w83627ehf_path
    driver_hwmon = ['in3']

class DellS6000PWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (DellS6000Fan1(),
            DellS6000Fan2(),
            DellS6000Fan3(),
            DellS6000Fan4(),
            DellS6000Fan5(),
            DellS6000Fan6(),
            )
    temps = (DellS6000Temp1(),
             DellS6000Temp2(),
             DellS6000Temp3(),
             DellS6000Temp4(),
             DellS6000Temp5(),
             DellS6000Temp6(),
             DellS6000Temp7(),
             )

class DellS6000PWM2(cumulus.sensors.PWM_Unit):
    name = 'PSU1 PWM'
    fans = (DellS6000Fan7(),
            )
    temps = (DellS6000Temp8(),
             DellS6000Temp9(),
             )

class DellS6000PWM3(cumulus.sensors.PWM_Unit):
    name = 'PSU2 PWM'
    fans = (DellS6000Fan8(),
            )
    temps = (DellS6000Temp10(),
             DellS6000Temp11(),
             )

class DellS6000Sensors():
    units = (DellS6000PSU1(),
             DellS6000PSU2(),
             DellS6000Volt1(),
             DellS6000Volt2(),
             DellS6000Volt3(),
             DellS6000Temp1(),
             DellS6000Temp2(),
             DellS6000Temp3(),
             DellS6000Temp4(),
             DellS6000Temp5(),
             DellS6000Temp6(),
             DellS6000Temp7(),
             DellS6000Temp8(),
             DellS6000Temp9(),
             DellS6000Temp10(),
             DellS6000Temp11(),
             DellS6000Fan1(),
             DellS6000Fan2(),
             DellS6000Fan3(),
             DellS6000Fan4(),
             DellS6000Fan5(),
             DellS6000Fan6(),
             DellS6000Fan7(),
             DellS6000Fan8(),
             )

class DellS6000PWMs():
    units = (DellS6000PWM1(),
             DellS6000PWM2(),
             DellS6000PWM3(),
             )

class DellS6000LEDs():
    units = (DellS6000PSULED(),
             DellS6000SystemLED(),
             DellS6000FanLED(),
             DellS6000Fan1LED(),
             DellS6000Fan2LED(),
             DellS6000Fan3LED(),
        )

class DellS6000Switch(cumulus.platform.BCMSwitch):
    ledup = DellS6000LED
    _qsfp = DellS6000QSFPp

    has_phy_ucode_mdio = False # XXX unverified
    has_phy_ucode_spi_rom = False # XXX unverified

    ports = (
        _qsfp(label="1", serdes=(  24,   25,   26,   27), leds=(0, 4),
              rx_lane_map=0x0213, tx_lane_map=0x2031,
              tx_polarity_flip=0x0002, rx_polarity_flip=0x000e,
              pre_emphasis=(0xcad0, 0xc6e0, 0xc6e0, 0xd2b0),
              drv_current=(0x5, 0x5, 0x5, 0x5),
              pre_drv_current=(0x5, 0x5, 0x5, 0x5)),
        _qsfp(label="2", serdes=(  28,   29,   30,   31), leds=(0, 0),
              rx_lane_map=0x0213, tx_lane_map=0x0213,
              tx_polarity_flip=0x0009, rx_polarity_flip=0x000c,
              pre_emphasis=(0xc2f0, 0xd2b0, 0xc6e0, 0xc2f0),
              drv_current=(0x6, 0x7, 0x6, 0x6),
              pre_drv_current=(0x6, 0x7, 0x6, 0x6)),
        _qsfp(label="3", serdes=( 32,  33,  34,  35), leds=(0, 12),
              rx_lane_map=0x0213, tx_lane_map=0x0132,
              tx_polarity_flip=0x0002, rx_polarity_flip=0x000e,
              pre_emphasis=(0xc6e0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="4", serdes=(  36,   37,  38,  39), leds=(0, 8),
              rx_lane_map=0x0213, tx_lane_map=0x1203,
              tx_polarity_flip=0x000e, rx_polarity_flip=0x0003,
              pre_emphasis=(0xcad0, 0xcad0, 0xc2f0, 0xc2f0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="5", serdes=( 44,  45,  46,  47), leds=(0, 20),
              rx_lane_map=0x0213, tx_lane_map=0x0213,
              tx_polarity_flip=0x0008, rx_polarity_flip=0x000e,
              pre_emphasis=(0xc2f0, 0xc2f0, 0xc2f0, 0xc2f0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="6", serdes=( 40,  41,  42,  43), leds=(0, 16),
              rx_lane_map=0x0213, tx_lane_map=0x3021,
              tx_polarity_flip=0x000b, rx_polarity_flip=0x0003,
              pre_emphasis=(0xc6e0, 0xc2f0, 0xc2f0, 0xcad0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="7", serdes=( 0,  1,  2,  3), leds=(0, 28),
              rx_lane_map=0x0213, tx_lane_map=0x2031,
              tx_polarity_flip=0x000d, rx_polarity_flip=0x000e,
              pre_emphasis=(0xc6e0, 0xcad0, 0xc6e0, 0xcad0),
              drv_current=(0x5, 0x5, 0x5, 0x5),
              pre_drv_current=(0x5, 0x5, 0x5, 0x5)),
        _qsfp(label="8", serdes=( 4,  5,  6,  7), leds=(0, 24),
              rx_lane_map=0x0213, tx_lane_map=0x1203,
              tx_polarity_flip=0x0001, rx_polarity_flip=0x000c,
              pre_emphasis=(0xc6e0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="9", serdes=( 12,  13,  14,  15), leds=(0, 36),
              rx_lane_map=0x0213, tx_lane_map=0x0132,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x000e,
              pre_emphasis=(0xb270, 0xbb10, 0xb720, 0xb720),
              drv_current=(0x2, 0x3, 0x2, 0x2),
              pre_drv_current=(0x2, 0x3, 0x2, 0x2)),
        _qsfp(label="10", serdes=( 8,  9,  10,  11), leds=(0, 32),
              rx_lane_map=0x3120, tx_lane_map=0x3021,
              tx_polarity_flip=0x0004, rx_polarity_flip=0x0000,
              pre_emphasis=(0xc2f0, 0xc6e0, 0xbf00, 0xc2f0),
              drv_current=(0x3, 0x3, 0x3, 0x3),
              pre_drv_current=(0x3, 0x3, 0x3, 0x3)),
        _qsfp(label="11", serdes=( 16,  17,  18,  19), leds=(0, 44),
              rx_lane_map=0x0213, tx_lane_map=0x0132,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x000e,
              pre_emphasis=(0xb330, 0xbb10, 0xbb10, 0xbb10),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="12", serdes=( 20,  21,  22,  23), leds=(0, 40),
              rx_lane_map=0x0123, tx_lane_map=0x1203,
              tx_polarity_flip=0x000e, rx_polarity_flip=0x000c,
              pre_emphasis=(0xb330, 0xb330, 0xb330, 0xb330),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="13", serdes=( 52,  53,  54,  55), leds=(0, 52),
              rx_lane_map=0x0213, tx_lane_map=0x0231,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0001,
              pre_emphasis=(0xaf40, 0xaf40, 0xaf40, 0xaf40),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="14", serdes=( 48,  49,  50,  51), leds=(0, 48),
              rx_lane_map=0x1302, tx_lane_map=0x2031,
              tx_polarity_flip=0x0003, rx_polarity_flip=0x000b,
              pre_emphasis=(0xa760, 0xa760, 0xa760, 0xa760),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="15", serdes=( 56,  57,  58,  59), leds=(0, 60),
              rx_lane_map=0x0213, tx_lane_map=0x2031,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0001,
              pre_emphasis=(0xa760, 0xa760, 0xa760, 0xa760),
              drv_current=(0x1, 0x1, 0x1, 0x1),
              pre_drv_current=(0x1, 0x1, 0x1, 0x1)),
        _qsfp(label="16", serdes=( 60,  61,  62,  63), leds=(0, 56),
              rx_lane_map=0x0132, tx_lane_map=0x0213,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0000,
              pre_emphasis=(0xa760, 0xa760, 0xa760, 0xa760),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="17", serdes=( 68,  69,  70, 71), leds=(1, 4),
              rx_lane_map=0x0213, tx_lane_map=0x2130,
              tx_polarity_flip=0x000f, rx_polarity_flip=0x0001,
              pre_emphasis=(0xa760, 0xa760, 0xa760, 0xa760),
              drv_current=(0x1, 0x1, 0x1, 0x1),
              pre_drv_current=(0x1, 0x1, 0x1, 0x1)),
        _qsfp(label="18", serdes=( 64,  65,  66,  67), leds=(1, 0),
              rx_lane_map=0x0132, tx_lane_map=0x2031,
              tx_polarity_flip=0x0009, rx_polarity_flip=0x0003,
              pre_emphasis=(0xa370, 0xa370, 0xa370, 0xa370),
              drv_current=(0x1, 0x1, 0x1, 0x1),
              pre_drv_current=(0x1, 0x1, 0x1, 0x1)),
        _qsfp(label="19", serdes=( 72,  73,  74,  75), leds=(1, 12),
              rx_lane_map=0x0213, tx_lane_map=0x2031,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0001,
              pre_emphasis=(0xa760, 0xa760, 0xa760, 0xa760),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="20", serdes=( 76,  77,  78,  79), leds=(1, 8),
              rx_lane_map=0x0123, tx_lane_map=0x1203,
              tx_polarity_flip=0x000e, rx_polarity_flip=0x0003,
              pre_emphasis=(0xaf40, 0xaf40, 0xaf40, 0xaf40),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="21", serdes=( 108,  109,  110,  111), leds=(1, 20),
              rx_lane_map=0x0132, tx_lane_map=0x0132,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0008,
              pre_emphasis=(0xb330, 0xb330, 0xb330, 0xbff0),
              drv_current=(0x1, 0x1, 0x1, 0x2),
              pre_drv_current=(0x1, 0x1, 0x1, 0x2)),
        _qsfp(label="22", serdes=( 104,  105,  106,  107), leds=(1, 16),
              rx_lane_map=0x1320, tx_lane_map=0x3021,
              tx_polarity_flip=0x000b, rx_polarity_flip=0x000d,
              pre_emphasis=(0xb330, 0xb330, 0xb330, 0xb330),
              drv_current=(0x1, 0x1, 0x1, 0x1),
              pre_drv_current=(0x1, 0x1, 0x1, 0x1)),
        _qsfp(label="23", serdes=( 112,  113,  114,  115), leds=(1, 28),
              rx_lane_map=0x0132, tx_lane_map=0x0132,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0008,
              pre_emphasis=(0xbb10, 0xbb10, 0xbb10, 0xc2f0),
              drv_current=(0x1, 0x1, 0x1, 0x1),
              pre_drv_current=(0x1, 0x1, 0x1, 0x1)),
        _qsfp(label="24", serdes=( 116,  117,  118,  119), leds=(1, 24),
              rx_lane_map=0x0231, tx_lane_map=0x1203,
              tx_polarity_flip=0x000e, rx_polarity_flip=0x0003,
              pre_emphasis=(0xc6e0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x3, 0x5, 0x3, 0x3),
              pre_drv_current=(0x3, 0x5, 0x3, 0x3)),
        _qsfp(label="25", serdes=(124, 125, 126, 127), leds=(1, 36),
              rx_lane_map=0x0132, tx_lane_map=0x0132,
              tx_polarity_flip=0x0000, rx_polarity_flip=0x0008,
              pre_emphasis=(0xc6e0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="26", serdes=( 120,  121,  122,  123), leds=(1, 32),
              rx_lane_map=0x1320, tx_lane_map=0x3021,
              tx_polarity_flip=0x000b, rx_polarity_flip=0x000d,
              pre_emphasis=(0xc6e0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="27", serdes=(80, 81, 82, 83), leds=(1, 44),
              rx_lane_map=0x1320, tx_lane_map=0x2031,
              tx_polarity_flip=0x0002, rx_polarity_flip=0x0001,
              pre_emphasis=(0xbb10, 0xbb10, 0xbf00, 0xbb10),
              drv_current=(0x2, 0x2, 0x2, 0x2),
              pre_drv_current=(0x2, 0x2, 0x2, 0x2)),
        _qsfp(label="28", serdes=(84, 85, 86, 87), leds=(1, 40),
              rx_lane_map=0x0213, tx_lane_map=0x1203,
              tx_polarity_flip=0x000e, rx_polarity_flip=0x000c,
              pre_emphasis=(0xc2f0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x4, 0x5, 0x4, 0x5),
              pre_drv_current=(0x4, 0x5, 0x4, 0x5)),
        _qsfp(label="29", serdes=(92, 93, 94, 95), leds=(1, 52),
              rx_lane_map=0x1320, tx_lane_map=0x2031,
              tx_polarity_flip=0x0002, rx_polarity_flip=0x0001,
              pre_emphasis=(0xc2f0, 0xc2f0, 0xc2f0, 0xc2f0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="30", serdes=(88, 89, 90, 91), leds=(1, 48),
              rx_lane_map=0x1320, tx_lane_map=0x3021,
              tx_polarity_flip=0x000b, rx_polarity_flip=0x0002,
              pre_emphasis=(0xcad0, 0xc6e0, 0xc6e0, 0xc6e0),
              drv_current=(0x4, 0x4, 0x4, 0x4),
              pre_drv_current=(0x4, 0x4, 0x4, 0x4)),
        _qsfp(label="31", serdes=(100, 101, 102, 103), leds=(1, 60),
              rx_lane_map=0x1320, tx_lane_map=0x1203,
              tx_polarity_flip=0x0006, rx_polarity_flip=0x0001,
              pre_emphasis=(0xcec0, 0xcec0, 0xcad0, 0xc6e0),
              drv_current=(0x6, 0x6, 0x6, 0x7),
              pre_drv_current=(0x6, 0x6, 0x6, 0x7)),
        _qsfp(label="32", serdes=(96, 97, 98, 99), leds=(1, 56),
              rx_lane_map=0x0213, tx_lane_map=0x2031,
              tx_polarity_flip=0x0003, rx_polarity_flip=0x000c,
              pre_emphasis=(0xcad0, 0xcad0, 0xcad0, 0xcad0),
              drv_current=(0x5, 0x5, 0x5, 0x5),
              pre_drv_current=(0x5, 0x5, 0x5, 0x5)),
    )

class DellS6000(cumulus.platform.Platform):
    name = 'dell,s6000_s1220'
    switch = DellS6000Switch(cumulus.platform.TridentTwo_56850_Chip())
    cpld = DellS6000CPLD()
    pwms = DellS6000PWMs()
    sensors = DellS6000Sensors()
    statusleds = DellS6000LEDs()


''' DELL S4000
'''
class DellS4000SFPp(cumulus.platform.TridentTwo10GPort):

    _set_led = '''
;;; DellS4000SFPp
;;
set_led:
;;; Each 10G port has two LEDs. One for link and one for activity.
;;; The link LED is dual-color green/yellow
;;; The activity LED is just green
;;; Three bits to pack all active high:
;;;   0: link_green
;;;   1: link_yellow
;;;   2: activity_green
;;; We use:
;;;   link_green on with link
;;;   link_yellow always off
;;;   activity_green flashes on with activity
;;;
        port a

        pushst  PORTSTATUS_LINKEN   ; link_green
        pack                        ;  - on with link

        pushst  PORTSTATUS_ZERO     ; link_yellow
        pack                        ;  - off

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand                        ; activity_green
        pack                        ;  - flash on with activity

        ret
'''
    def __init__(self, label, serdes, leds, rx_polarity_flip=None, tx_polarity_flip=None,
                       tx_lane_map=None, rx_lane_map=None):
        cumulus.platform.TridentTwo10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 rx_lane_map=rx_lane_map,
                                                 tx_lane_map=tx_lane_map,
                                                 rx_polarity_flip=rx_polarity_flip,
                                                 tx_polarity_flip=tx_polarity_flip,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, led_port)

        for led in led_index_list:
            set_calls[led] = call
            set_calls[led+1] = None
            set_calls[led+2] = None

        return set_calls

class DellS4000QSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; DellS4000QSFPp
;;;
;;; 40G ports have 4 green/yellow LEDs, two bits per LED.
;;; For 40G mode, we use only the first LED to indicate link/activity.
;;;    0: link_green   (active high)
;;;    1-7: off
;;;  We use the link_green led for link and activity
;;; The other 3 LEDs will be off.
;;;
set_led:
        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor                     ; on with link
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        ld      a, 7
qsfp_pack_loop:
        port 1
        pushst  PORTSTATUS_ZERO
        pack
        sub     a, 1
        jnz     qsfp_pack_loop

        ret
'''
    _set_led_4x10 = '''
;;; DellS4000QSFPp_4x10
;;;
;;;  For 4x10G mode, we use an LED for each port. Each port has
;;;  a single green/yellow LED:
;;;    0: link_green   (active high)
;;;    1: link_yellow  (active high)
;;;  We use the link_green led for link and activity
;;;  link_yellow is always off
;;
set_led:
        call    set_qsfp_4x10_led
        inc     a
        call    set_qsfp_4x10_led
        inc     a
        call    set_qsfp_4x10_led
        inc     a
        call    set_qsfp_4x10_led

        ret

set_qsfp_4x10_led:
        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor                     ; link_green on with link
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        pushst  PORTSTATUS_ZERO ; link_yellow off
        pack

        ret
'''
    def __init__(self, label, serdes, leds, rx_lane_map=None, tx_lane_map=None, rx_polarity_flip=None, tx_polarity_flip=None):
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=leds,
                                                 rx_lane_map=rx_lane_map,
                                                 rx_polarity_flip=rx_polarity_flip,
                                                 tx_lane_map=tx_lane_map,
                                                 tx_polarity_flip=tx_polarity_flip,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        if (mode == "4x10G") and (sub != 0):
            # For 4x10G mode only update LEDs for the first
            # sub-interface.
            return set_calls

        fn_name = '%s' % self.__class__.__name__
        if mode == "4x10G":
            call = (fn_name + "_4x10", self._set_led_4x10, led_port)
        elif mode == "40G":
            call = (fn_name, self._set_led, led_port)

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0]+1] = None
        set_calls[led_index_list[0]+2] = None
        set_calls[led_index_list[0]+3] = None
        set_calls[led_index_list[0]+4] = None
        set_calls[led_index_list[0]+5] = None
        set_calls[led_index_list[0]+6] = None
        set_calls[led_index_list[0]+7] = None


        return set_calls

class DellS4000LED_1_36(cumulus.ledup.TridentTwoLEDController):
    num_leds = 112

class DellS4000LED_37_54(cumulus.ledup.TridentTwoLEDController):
    num_leds = 84

class DellS4000CPLD(cumulus.cpld.SysFS):
    path = '/sys/bus/platform/devices/dell_s4000_cpld.0'


'''
   Dell S4000 LEDS
     System:
       green - all systems ok
       green blinking - fan missing or broken, psu missing or broken
     Fan:
       green - all 3 fans installed and working
       yellow blinking - fan missing or malfunction
     Fan_Tray_X (0 - 2):
       green - fan X installed and working
       yellow - fan X malfunction
'''

DellS4000_i2c_path = '/sys/bus/i2c/devices/'

''' tmp75: temp sensor 1 '''
DellS4000_i2c_11_4c_path = DellS4000_i2c_path + '11-004c'

''' tmp75: temp sensor 2 '''
DellS4000_i2c_10_4d_path = DellS4000_i2c_path + '10-004d'

''' tmp75: temp sensor 3 '''
DellS4000_i2c_11_4d_path = DellS4000_i2c_path + '11-004d'

''' tmp75: temp sensor 4 '''
DellS4000_i2c_11_4e_path = DellS4000_i2c_path + '11-004e'

''' dni_dps460: PSU1 Temp/Fan '''
DellS4000_i2c_14_58_path = DellS4000_i2c_path + '14-0058'

''' dni_dps460: PSU2 Temp/Fan '''
DellS4000_i2c_14_59_path = DellS4000_i2c_path + '14-0059'

''' max6620: Fan Tray 1, 2 Controller '''
DellS4000_i2c_11_2a_path = DellS4000_i2c_path + '11-002a'

''' max6620: Fan Tray 3, 4, 5, 6 Controller '''
DellS4000_i2c_11_29_path = DellS4000_i2c_path + '11-0029'

''' ltc4215: PSU1 '''
DellS4000_i2c_11_40_path = DellS4000_i2c_path + '11-0040'

''' ltc4215: PSU2 '''
DellS4000_i2c_11_42_path = DellS4000_i2c_path + '11-0042'

class DellS4000SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_system'
    bad_led_color = 'green_blinking'

class DellS4000FanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fans'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4', 'Fan5', 'Fan6']
    led_location = 'led_fan'
    bad_led_color = 'yellow_blinking'

class DellS4000Fan1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 1'
    sources = ['Fan1', 'Fan2']
    led_location = 'led_fan_tray_1'
    bad_led_color = 'yellow'

class DellS4000Fan2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 2'
    sources = ['Fan3', 'Fan4']
    led_location = 'led_fan_tray_2'
    bad_led_color = 'yellow'

class DellS4000Fan3LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 3'
    sources = ['Fan5', 'Fan6']
    led_location = 'led_fan_tray_3'
    bad_led_color = 'yellow'

class DellS4000Temp(cumulus.sensors.Temp_Unit):
    temp_crit = 85
    temp_max = 50
    temp_max_hyst = 25

class DellS4000Temp1(DellS4000Temp):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = DellS4000_i2c_11_4c_path

class DellS4000Temp2(DellS4000Temp):
    name = 'Temp2'
    description = 'Board Sensor near CPU'
    driver_path = DellS4000_i2c_10_4d_path

class DellS4000Temp3(DellS4000Temp):
    name = 'Temp3'
    description = 'Board Sensor near middle of SFP+ cage'
    driver_path = DellS4000_i2c_11_4d_path

class DellS4000Temp4(DellS4000Temp):
    name = 'Temp4'
    description = 'CPU Temp Sensor'
    driver_path = DellS4000_i2c_11_4e_path

class DellS4000PSUTemp(cumulus.sensors.Temp_Unit):
    temp_crit = 70
    temp_max = 65
    temp_max_hyst = 25
    psu = None

    def find_and_add_attrs(self):
        state = 'OK'
        try:
            path = os.path.join(self.status_path, self.psu, 'state')
            with open(path) as fp:
                state = fp.read().rsplit('\n')[0]
        except:
            return -1
        if (state == 'ABSENT'):
            return -1
        return cumulus.sensors.Temp_Unit.find_and_add_attrs(self)

class DellS4000Temp5(DellS4000PSUTemp):
    name = 'PSU1Temp1'
    description = 'PSU1 Temp Sensor'
    driver_path = DellS4000_i2c_14_59_path
    driver_hwmon = ['temp1']
    psu = 'PSU1'

class DellS4000Temp6(DellS4000PSUTemp):
    name = 'PSU1Temp2'
    description = 'PSU1 Temp Sensor'
    driver_path = DellS4000_i2c_14_59_path
    driver_hwmon = ['temp2']
    psu = 'PSU1'

class DellS4000Temp7(DellS4000PSUTemp):
    name = 'PSU2Temp1'
    description = 'PSU2 Temp Sensor'
    driver_path = DellS4000_i2c_14_58_path
    driver_hwmon = ['temp1']
    psu = 'PSU2'

class DellS4000Temp8(DellS4000PSUTemp):
    name = 'PSU2Temp2'
    description = 'PSU2 Temp Sensor'
    driver_path = DellS4000_i2c_14_58_path
    driver_hwmon = ['temp2']
    psu = 'PSU2'

class DellS4000Fan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    fan_max = 19000
    fan_min = 7200

class DellS4000PSUFan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    fan_max = 18000
    fan_min = 7000
    psu = None

    def find_and_add_attrs(self):
        state = 'OK'
        try:
            path = os.path.join(self.status_path, self.psu, 'state')
            with open(path) as fp:
                state = fp.read().rsplit('\n')[0]
        except:
            return -1
        if (state == 'ABSENT'):
            return -1
        return cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class DellS4000Fan1(DellS4000Fan):
    name = 'Fan1'
    description = 'Fan Tray 1'
    driver_path = DellS4000_i2c_11_2a_path
    driver_hwmon = ['fan1']
    cpld_hwmon = ['fan_1']

class DellS4000Fan2(DellS4000Fan):
    name = 'Fan2'
    description = 'Fan Tray 1'
    driver_path = DellS4000_i2c_11_2a_path
    driver_hwmon = ['fan2']
    cpld_hwmon = ['fan_1']

class DellS4000Fan3(DellS4000Fan):
    name = 'Fan3'
    description = 'Fan Tray 2'
    driver_path = DellS4000_i2c_11_29_path
    driver_hwmon = ['fan3']
    cpld_hwmon = ['fan_2']

class DellS4000Fan4(DellS4000Fan):
    name = 'Fan4'
    description = 'Fan Tray 2'
    driver_path = DellS4000_i2c_11_29_path
    driver_hwmon = ['fan4']
    cpld_hwmon = ['fan_2']

class DellS4000Fan5(DellS4000Fan):
    name = 'Fan5'
    description = 'Fan Tray 3'
    driver_path = DellS4000_i2c_11_29_path
    driver_hwmon = ['fan1']
    cpld_hwmon = ['fan_3']

class DellS4000Fan6(DellS4000Fan):
    name = 'Fan6'
    description = 'Fan Tray 3'
    driver_path = DellS4000_i2c_11_29_path
    driver_hwmon = ['fan2']
    cpld_hwmon = ['fan_3']

class DellS4000Fan7(DellS4000PSUFan):
    name = 'PSU1Fan1'
    description = 'PSU1 Fan'
    driver_path = DellS4000_i2c_14_59_path
    driver_hwmon = ['fan1']
    psu = 'PSU1'

class DellS4000Fan8(DellS4000PSUFan):
    name = 'PSU2Fan1'
    description = 'PSU2 Fan'
    driver_path = DellS4000_i2c_14_58_path
    driver_hwmon = ['fan1']
    psu = 'PSU2'

class DellS4000PSU(cumulus.sensors.PSU_Unit):
    init_done = False
    def __init__(self):
        cumulus.sensors.PSU_Unit.__init__(self)
        self.add_state('OK', self.ok_handler)

    def ok_handler(self):
        if self.init_done:
            return
        err_states = ['BAD', 'ABSENT'];
        if self.attrs['prev_state'] in err_states:
            cmd = 'rmmod dni_dps460 && modprobe dni_dps460'
            subprocess.call(cmd, shell=True)
            self.init_done = True

class DellS4000PSU1(DellS4000PSU):
    name = 'PSU1'
    driver_path = DellS4000_i2c_11_42_path
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr1']

class DellS4000PSU2(DellS4000PSU):
    name = 'PSU2'
    driver_path = DellS4000_i2c_11_40_path
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr2']


class DellS4000PWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (DellS4000Fan1(),
            DellS4000Fan2(),
            DellS4000Fan3(),
            DellS4000Fan4(),
            DellS4000Fan5(),
            DellS4000Fan6(),
            DellS4000Fan7(),
            DellS4000Fan8(),
            )

    temps = (DellS4000Temp1(),
             DellS4000Temp2(),
             DellS4000Temp3(),
             DellS4000Temp4(),
             DellS4000Temp5(),
             DellS4000Temp6(),
             DellS4000Temp7(),
             DellS4000Temp8(),
             )

class DellS4000PWM2(cumulus.sensors.PWM_Unit):
    name = 'PSU1 PWM'
    fans = (DellS4000Fan7(),
            )
    temps = (DellS4000Temp5(),
             DellS4000Temp6(),
             )

class DellS4000PWM3(cumulus.sensors.PWM_Unit):
    name = 'PSU2 PWM'
    fans = (DellS4000Fan8(),
            )
    temps = (DellS4000Temp7(),
             DellS4000Temp8(),
             )

class DellS4000Sensors():
    units = (DellS4000PSU1(),
             DellS4000PSU2(),
             DellS4000Temp1(),
             DellS4000Temp2(),
             DellS4000Temp3(),
             DellS4000Temp4(),
             DellS4000Temp5(),
             DellS4000Temp6(),
             DellS4000Temp7(),
             DellS4000Temp8(),
             DellS4000Fan1(),
             DellS4000Fan2(),
             DellS4000Fan3(),
             DellS4000Fan4(),
             DellS4000Fan5(),
             DellS4000Fan6(),
             DellS4000Fan7(),
             DellS4000Fan8(),
             )

class DellS4000PWMs():
    units = (DellS4000PWM1(),
             DellS4000PWM2(),
             DellS4000PWM3(),
             )

class DellS4000LEDs():
    units = (
             DellS4000SystemLED(),
             DellS4000FanLED(),
             DellS4000Fan1LED(),
             DellS4000Fan2LED(),
             DellS4000Fan3LED(),
        )

class DellS4000Switch(cumulus.platform.BCMSwitch):
    ledup = (DellS4000LED_1_36, DellS4000LED_37_54)
    _sfp = DellS4000SFPp
    _qsfp = DellS4000QSFPp

    has_phy_ucode_mdio = False
    has_phy_ucode_spi_rom = False

    ports = (
        _sfp(label="1",  serdes=(44,), leds=(0,  0),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="2",  serdes=(45,), leds=(0,  3),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="3",  serdes=(46,), leds=(0,  6),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="4",  serdes=(47,), leds=(0,  9),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="5",  serdes=(48,), leds=(0, 12),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="6",  serdes=(49,), leds=(0, 15),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="7",  serdes=(50,), leds=(0, 18),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="8",  serdes=(51,), leds=(0, 21),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="9",  serdes=(12,), leds=(0, 24),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="10", serdes=(13,), leds=(0, 27),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="11", serdes=(14,), leds=(0, 30),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="12", serdes=(15,), leds=(0, 33),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="13", serdes=(20,), leds=(0, 36),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="14", serdes=(21,), leds=(0, 39),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="15", serdes=(22,), leds=(0, 42),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="16", serdes=(23,), leds=(0, 45),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="17", serdes=(24,), leds=(0, 48),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="18", serdes=(25,), leds=(0, 51),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="19", serdes=(26,), leds=(0, 54),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="20", serdes=(27,), leds=(0, 57),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="21", serdes=(28,), leds=(0, 60),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="22", serdes=(29,), leds=(0, 63),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="23", serdes=(30,), leds=(0, 66),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="24", serdes=(31,), leds=(0, 69),
             rx_lane_map=0x3210, tx_lane_map=0x0123, rx_polarity_flip=True),
        _sfp(label="25", serdes=(52,), leds=(0, 72),
             rx_lane_map=0x3210, tx_lane_map=0x1032),
        _sfp(label="26", serdes=(53,), leds=(0, 75),
             rx_lane_map=0x3210, tx_lane_map=0x1032),
        _sfp(label="27", serdes=(54,), leds=(0, 78),
             rx_lane_map=0x3210, tx_lane_map=0x1032),
        _sfp(label="28", serdes=(55,), leds=(0, 81),
             rx_lane_map=0x3210, tx_lane_map=0x1032),
        _sfp(label="29", serdes=(56,), leds=(0, 84),
             rx_lane_map=0x3210, tx_lane_map=0x0123),
        _sfp(label="30", serdes=(57,), leds=(0, 87),
             rx_lane_map=0x3210, tx_lane_map=0x0123),
        _sfp(label="31", serdes=(58,), leds=(0, 90),
             rx_lane_map=0x3210, tx_lane_map=0x0123),
        _sfp(label="32", serdes=(59,), leds=(0, 93),
             rx_lane_map=0x3210, tx_lane_map=0x0123),
        _sfp(label="33", serdes=(60,), leds=(0, 96),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="34", serdes=(61,), leds=(0, 99),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="35", serdes=(62,), leds=(0,102),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="36", serdes=(63,), leds=(0,105),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="37", serdes=(64,), leds=(1,  0),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="38", serdes=(65,), leds=(1,  3),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="39", serdes=(66,), leds=(1,  6),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="40", serdes=(67,), leds=(1,  9),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="41", serdes=(68,), leds=(1, 12),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="42", serdes=(69,), leds=(1, 15),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="43", serdes=(70,), leds=(1, 18),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="44", serdes=(71,), leds=(1, 21),
             rx_lane_map=0x2301, tx_lane_map=0x3021),
        _sfp(label="45", serdes=(72,), leds=(1, 24),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="46", serdes=(73,), leds=(1, 27),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="47", serdes=(74,), leds=(1, 30),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _sfp(label="48", serdes=(75,), leds=(1, 33),
             rx_lane_map=0x2301, tx_lane_map=0x1032),
        _qsfp(label="49", serdes=(100, 101, 102, 103), leds=(1, 36),
                tx_lane_map=0x2031, rx_lane_map=0x0132,
                rx_polarity_flip=0x5, tx_polarity_flip=0x2
         ),
        _qsfp(label="50", serdes=(96, 97, 98, 99), leds=(1, 44),
                tx_lane_map=0x3021, rx_lane_map=0x1320,
                rx_polarity_flip=0xd, tx_polarity_flip=0xb
         ),
        _qsfp(label="51", serdes=(108, 109, 110, 111), leds=(1, 52),
                tx_lane_map=0x0213, rx_lane_map=0x0132,
                rx_polarity_flip=0x5, tx_polarity_flip=0x8
        ),
        _qsfp(label="52", serdes=(104, 105, 106, 107), leds=(1, 60),
                tx_lane_map=0x2031, rx_lane_map=0x0132,
                rx_polarity_flip=0x3, tx_polarity_flip=0x3
        ),
        _qsfp(label="53", serdes=( 80, 81, 82, 83), leds=(1, 68),
                tx_lane_map=0x0132, rx_lane_map=0x0132,
        rx_polarity_flip=0xb, tx_polarity_flip=0x0
        ),
        _qsfp(label="54", serdes=( 76,  77,  78,  79), leds=(1, 76),
                tx_lane_map=0x2031, rx_lane_map=0x1320,
                rx_polarity_flip=0xd, tx_polarity_flip=0x3
        ),
    )

class DellS4000(cumulus.platform.Platform):
    name = 'dell,s4000_c2338'
    switch = DellS4000Switch(cumulus.platform.TridentTwo_56854_Chip())
    cpld = DellS4000CPLD()
    pwms = DellS4000PWMs()
    sensors = DellS4000Sensors()
    statusleds = DellS4000LEDs()
