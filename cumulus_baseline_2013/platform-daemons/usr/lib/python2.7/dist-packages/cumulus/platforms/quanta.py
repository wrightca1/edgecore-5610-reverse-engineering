#
# Copyright 2012.  Cumulus Networks, Inc.
#
# quanta.py --
#     Quanta platform data.
#

import cumulus.platform
import cumulus.sunit
import cumulus.ledup
import subprocess
import os

class QuantaLB8SFPp(cumulus.platform.Trident10GPort):
    def __init__(self, label, serdes, phy_addr):
        cumulus.platform.Trident10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_type="8754",
                                                 phy_addr=phy_addr,
                                                 phy_layer='SFP+',
                                                 leds=None,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSWalk(label, 'sfp+')

class QuantaLB8PSUCombo(cumulus.sunit.PSUCombo):
    pass

class QuantaLB8Fan(cumulus.sunit.Fan):
    pass

class QuantaLB8System(cumulus.sunit.System):
    pass

class QuantaLB8Switch(cumulus.platform.BCMSwitch):
    _sfp = QuantaLB8SFPp
    has_phy_ucode_spi_rom = True
    has_phy_ucode_mdio = True
    ports = (
        _sfp(label="1",  serdes=8,  phy_addr=0x4),
        _sfp(label="2",  serdes=9,  phy_addr=0x5),
        _sfp(label="3",  serdes=10, phy_addr=0x6),
        _sfp(label="4",  serdes=11, phy_addr=0x7),
        _sfp(label="5",  serdes=12, phy_addr=0x8),
        _sfp(label="6",  serdes=13, phy_addr=0x9),
        _sfp(label="7",  serdes=14, phy_addr=0xa),
        _sfp(label="8",  serdes=15, phy_addr=0xb),
        _sfp(label="9",  serdes=16, phy_addr=0xc),
        _sfp(label="10", serdes=17, phy_addr=0xd),
        _sfp(label="11", serdes=18, phy_addr=0xe),
        _sfp(label="12", serdes=19, phy_addr=0xf),
        _sfp(label="13", serdes=24, phy_addr=0x10),
        _sfp(label="14", serdes=25, phy_addr=0x11),
        _sfp(label="15", serdes=26, phy_addr=0x12),
        _sfp(label="16", serdes=27, phy_addr=0x13),
        _sfp(label="17", serdes=28, phy_addr=0x24),
        _sfp(label="18", serdes=29, phy_addr=0x25),
        _sfp(label="19", serdes=30, phy_addr=0x26),
        _sfp(label="20", serdes=31, phy_addr=0x27),
        _sfp(label="21", serdes=32, phy_addr=0x28),
        _sfp(label="22", serdes=33, phy_addr=0x29),
        _sfp(label="23", serdes=34, phy_addr=0x2a),
        _sfp(label="24", serdes=35, phy_addr=0x2b),
        _sfp(label="25", serdes=44, phy_addr=0x2c),
        _sfp(label="26", serdes=45, phy_addr=0x2d),
        _sfp(label="27", serdes=46, phy_addr=0x2e),
        _sfp(label="28", serdes=47, phy_addr=0x2f),
        _sfp(label="29", serdes=48, phy_addr=0x30),
        _sfp(label="30", serdes=49, phy_addr=0x31),
        _sfp(label="31", serdes=50, phy_addr=0x32),
        _sfp(label="32", serdes=51, phy_addr=0x33),
        _sfp(label="33", serdes=52, phy_addr=0x44),
        _sfp(label="34", serdes=53, phy_addr=0x45),
        _sfp(label="35", serdes=54, phy_addr=0x46),
        _sfp(label="36", serdes=55, phy_addr=0x47),
        _sfp(label="37", serdes=60, phy_addr=0x48),
        _sfp(label="38", serdes=61, phy_addr=0x49),
        _sfp(label="39", serdes=62, phy_addr=0x4a),
        _sfp(label="40", serdes=63, phy_addr=0x4b),
        _sfp(label="41", serdes=64, phy_addr=0x4c),
        _sfp(label="42", serdes=65, phy_addr=0x4d),
        _sfp(label="43", serdes=66, phy_addr=0x4e),
        _sfp(label="44", serdes=67, phy_addr=0x4f),
        _sfp(label="45", serdes=68, phy_addr=0x50),
        _sfp(label="46", serdes=69, phy_addr=0x51),
        _sfp(label="47", serdes=70, phy_addr=0x52),
        _sfp(label="48", serdes=71, phy_addr=0x53),
    )

class QuantaLB8(cumulus.platform.Platform):
    name = 'quanta,lb8'
    switch = QuantaLB8Switch(cumulus.platform.TridentChip())

class QuantaLY2QSFPp(cumulus.platform.Trident40GPort):
    _set_led = '''
; QuantaLY2QSFPp - green link, amber activity
set_led:
        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pack
        pushst  PORTSTATUS_LINKEN
        tinv                    ; LEDs are active low
        pack

        ret
'''

    def __init__(self, label, serdes, phy_addrs, leds):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=("84740",) * 4,
                                                 phy_addrs=phy_addrs,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class QuantaLY2SFPp(cumulus.platform.Trident10GPort):
    # LEDs, set register 0xc808 devad 1 for green link, amber activity
    phy_init = { '1 0xc808' : '0x0860' }

    def __init__(self, label, serdes, phy_addr):
        cumulus.platform.Trident10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_type="8754",
                                                 phy_addr=phy_addr,
                                                 phy_layer='SFP+',
                                                 leds=None,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')

class QuantaLY2LED(cumulus.ledup.TridentLEDController):
    num_leds = 8
    # the phy-connected port LEDs blink with a 120ms period, make the QSFP
    # ports match.
    blink_period = 120

class QuantaLY2Switch(cumulus.platform.BCMSwitch):
    ledup = QuantaLY2LED
    _sfp = QuantaLY2SFPp
    _qsfp = QuantaLY2QSFPp
    has_phy_ucode_spi_rom = True
    has_phy_ucode_mdio = True
    ports = (
        _sfp(label="1",  serdes=4,  phy_addr=0x0),
        _sfp(label="2",  serdes=5,  phy_addr=0x1),
        _sfp(label="3",  serdes=6,  phy_addr=0x2),
        _sfp(label="4",  serdes=7,  phy_addr=0x3),
        _sfp(label="5",  serdes=8,  phy_addr=0x4),
        _sfp(label="6",  serdes=9,  phy_addr=0x5),
        _sfp(label="7",  serdes=10, phy_addr=0x6),
        _sfp(label="8",  serdes=11, phy_addr=0x7),
        _sfp(label="9",  serdes=12, phy_addr=0x8),
        _sfp(label="10", serdes=13, phy_addr=0x9),
        _sfp(label="11", serdes=14, phy_addr=0xa),
        _sfp(label="12", serdes=15, phy_addr=0xb),
        _sfp(label="13", serdes=16, phy_addr=0xc),
        _sfp(label="14", serdes=17, phy_addr=0xd),
        _sfp(label="15", serdes=18, phy_addr=0xe),
        _sfp(label="16", serdes=19, phy_addr=0xf),
        _sfp(label="17", serdes=20, phy_addr=0x20),
        _sfp(label="18", serdes=21, phy_addr=0x21),
        _sfp(label="19", serdes=22, phy_addr=0x22),
        _sfp(label="20", serdes=23, phy_addr=0x23),
        _sfp(label="21", serdes=24, phy_addr=0x24),
        _sfp(label="22", serdes=25, phy_addr=0x25),
        _sfp(label="23", serdes=26, phy_addr=0x26),
        _sfp(label="24", serdes=27, phy_addr=0x27),
        _sfp(label="25", serdes=28, phy_addr=0x28),
        _sfp(label="26", serdes=29, phy_addr=0x29),
        _sfp(label="27", serdes=30, phy_addr=0x2a),
        _sfp(label="28", serdes=31, phy_addr=0x2b),
        _sfp(label="29", serdes=32, phy_addr=0x2c),
        _sfp(label="30", serdes=33, phy_addr=0x2d),
        _sfp(label="31", serdes=34, phy_addr=0x2e),
        _sfp(label="32", serdes=35, phy_addr=0x2f),
        _sfp(label="33", serdes=40, phy_addr=0x30),
        _sfp(label="34", serdes=41, phy_addr=0x31),
        _sfp(label="35", serdes=42, phy_addr=0x32),
        _sfp(label="36", serdes=43, phy_addr=0x33),
        _sfp(label="37", serdes=44, phy_addr=0x34),
        _sfp(label="38", serdes=45, phy_addr=0x35),
        _sfp(label="39", serdes=46, phy_addr=0x36),
        _sfp(label="40", serdes=47, phy_addr=0x37),
        _sfp(label="41", serdes=48, phy_addr=0x38),
        _sfp(label="42", serdes=49, phy_addr=0x39),
        _sfp(label="43", serdes=50, phy_addr=0x3a),
        _sfp(label="44", serdes=51, phy_addr=0x3b),
        _sfp(label="45", serdes=52, phy_addr=0x3c),
        _sfp(label="46", serdes=53, phy_addr=0x3d),
        _sfp(label="47", serdes=54, phy_addr=0x3e),
        _sfp(label="48", serdes=55, phy_addr=0x3f),

        _qsfp(label="49", serdes=(56,57,58,59), phy_addrs=(0x40,0x41,0x42,0x43), leds=(1,6)),
        _qsfp(label="50", serdes=(60,61,62,63), phy_addrs=(0x44,0x45,0x46,0x47), leds=(1,4)),
        _qsfp(label="51", serdes=(64,65,66,67), phy_addrs=(0x48,0x49,0x4a,0x4b), leds=(1,2)),
        _qsfp(label="52", serdes=(68,69,70,71), phy_addrs=(0x4c,0x4d,0x4e,0x4f), leds=(1,0)),
    )

class QuantaLY2_PSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1_present'] = 1
        else:
            self.attrs['psu_pwr1_present'] = 0
        if self.get_gpio_value(self.psu_all_ok) == '1':
            self.attrs['psu_pwr1_all_ok'] = 1
        else:
            self.attrs['psu_pwr1_all_ok'] = 0
        return 0

class QuantaLY2Fan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    fan_min = 2500
    fan_max = 23000
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-4/4-002e'

class QuantaLY2Fan1(QuantaLY2Fan):
    name = 'Fan1'
    driver_hwmon = ['fan1']

class QuantaLY2Fan2(QuantaLY2Fan):
    name = 'Fan2'
    driver_hwmon = ['fan2']

class QuantaLY2Fan3(QuantaLY2Fan):
    name = 'Fan3'
    driver_hwmon = ['fan3']

class QuantaLY2Fan4(QuantaLY2Fan):
    name = 'Fan4'
    driver_hwmon = ['fan4']

class QuantaLY2Fan5(QuantaLY2Fan):
    name = 'Fan5'
    driver_hwmon = ['fan5']

class QuantaLY2Fan6(QuantaLY2Fan):
    name = 'Fan6'
    driver_hwmon = ['fan6']

class QuantaLY2Fan7(QuantaLY2Fan):
    name = 'Fan7'
    driver_hwmon = ['fan7']

class QuantaLY2Fan8(QuantaLY2Fan):
    name = 'Fan8'
    driver_hwmon = ['fan8']

class QuantaLY2PSU1(QuantaLY2_PSU):
    name = 'PSU1'
    psu_present = 'gpio192'
    psu_all_ok = 'gpio193'

class QuantaLY2PSU2(QuantaLY2_PSU):
    name = 'PSU2'
    psu_present = 'gpio208'
    psu_all_ok = 'gpio209'

class QuantaLY2SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'gpio235'
    good_led_color = '1'  # Off
    bad_led_color = '0'   # Yellow

    def led_update(self, color):
        self.set_gpio_value(self.led_location, color)
        #print 'loc: %s color %s' %(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '0':
            color = 'yellow'
        else:
            color = 'off'
        return self.name, color

class QuantaLY2Temp(cumulus.sensors.Temp_Unit):
    #These are approx numbers from data provided by Quanta.
    temp_max = 68
    temp_crit = 75

class QuantaLY2Temp1(QuantaLY2Temp):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'
    temp_max = 100
    temp_crit = 105

class QuantaLY2Temp2(QuantaLY2Temp):
    name = 'Temp2'
    description = "Right Side of Networking ASIC"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-4/4-002e'
    driver_hwmon = ['temp1']

class QuantaLY2Temp3(QuantaLY2Temp):
    name = 'Temp3'
    description = "Near CPU"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-4/4-002e'
    driver_hwmon = ['temp2']

class QuantaLY2Temp4(QuantaLY2Temp):
    name = 'Temp4'
    description = "Left Side of Networking ASIC"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-4/4-002e'
    driver_hwmon = ['temp3']

class QuantaLY2Temp5(QuantaLY2Temp):
    name = 'Temp5'
    description = "Left Corner near PHY"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-4/4-002e'
    driver_hwmon = ['temp4']

class QuantaLY2Temp6(QuantaLY2Temp):
    name = 'Temp6'
    description = "Fan Outlet sensor"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-4/4-002e'
    driver_hwmon = ['temp5']

class QuantaLY2PWM1(cumulus.sensors.PWM_Unit):
    fans = (QuantaLY2Fan1(),
            QuantaLY2Fan2(),
            QuantaLY2Fan3(),
            QuantaLY2Fan4(),
            QuantaLY2Fan5(),
            QuantaLY2Fan6(),
            QuantaLY2Fan7(),
            QuantaLY2Fan8(),
            )
    temps = (QuantaLY2Temp1(),
             QuantaLY2Temp2(),
             QuantaLY2Temp3(),
             QuantaLY2Temp4(),
             QuantaLY2Temp5(),
             QuantaLY2Temp6(),
             )

class QuantaLY2Sensors():
    units = ( QuantaLY2PSU1(),
              QuantaLY2PSU2(),
              QuantaLY2Fan1(),
              QuantaLY2Fan2(),
              QuantaLY2Fan3(),
              QuantaLY2Fan4(),
              QuantaLY2Fan5(),
              QuantaLY2Fan6(),
              QuantaLY2Fan7(),
              QuantaLY2Fan8(),
              QuantaLY2Temp1(),
              QuantaLY2Temp2(),
              QuantaLY2Temp3(),
              QuantaLY2Temp4(),
              QuantaLY2Temp5(),
              QuantaLY2Temp6(),
              )

class QuantaLY2PWMs():
    units = (QuantaLY2PWM1(),
             )

class QuantaLY2LEDs():
    units = (QuantaLY2SystemLED(),
             )

class QuantaLY2(cumulus.platform.Platform):
    name = 'quanta,ly2'
    switch = QuantaLY2Switch(cumulus.platform.TridentChip())
    statusleds = QuantaLY2LEDs()
    pwms = QuantaLY2PWMs()
    sensors = QuantaLY2Sensors()

class QuantaLY2RQSFPp(cumulus.platform.Trident40GPort):
    _set_led = '''
;;; QuantaLY2RQSFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed is always zero
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
set_led:
        port a

        pushst PORTSTATUS_ZERO
        pack

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        ret

'''
    _set_led_4x10 = '''
;;;
;;; Input : register A, logical port
;;; Input / Output : register B, accumulated port status

;;; For each port accumulate 2 bits of information in register B:
;;;   register B[0] - link enabled
;;;   register B[1] - activity (TX _OR_ RX)

SUB_INTF_LINKEN     equ 0x0  ; link enabled
SUB_INTF_ACTIVITY   equ 0x1  ; activity

sub_intf_info:

        ;;; push OR of current TX/RX activity onto stack
        port a
        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor

        ;;; push accumlated link activity onto stack
        tst B, SUB_INTF_ACTIVITY
        push cy

        ;;; OR accumlated activity with current activity and store
        ;;; result back in register B
        tor
        pop
        bit B, SUB_INTF_ACTIVITY

        ;;; push current LINKEN onto stack
        pushst  PORTSTATUS_LINKEN

        ;;; push accumlated link enable onto stack
        tst B, SUB_INTF_LINKEN
        push cy

        ;;; OR accumlated LINKEN with current LINKEN and store
        ;;; result back in register B
        tor
        pop
        bit B, SUB_INTF_LINKEN

        ret

;;; QuantaLY6QSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active high), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:

        port a
        pushst PORTSTATUS_ZERO
        pack

        ;;; initialize B
        ld  b,0

        ;;; load sub-0 info
        call    sub_intf_info

        ;;; load sub-1 info
        inc a
        call    sub_intf_info

        ;;; load sub-2 info
        inc a
        call    sub_intf_info

        ;;; load sub-3 info
        inc a
        call    sub_intf_info

        ;;; push accumlated link activity onto stack
        tst B, SUB_INTF_ACTIVITY
        push    cy

        ;;; combine with BLINK state
        push    (BLINK_STATE_P)
        tand
        tinv    ; flash off with activity

        ;;; push accumlated link enable onto stack
        tst B, SUB_INTF_LINKEN
        push    cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand
        pack

        ret

'''
    def __init__(self, label, serdes, leds):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=leds,
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
        led_port = self.led_port_num(mode, 0)
        if mode == "4x10G":
            call = (fn_name + "_4x10", self._set_led_4x10, led_port)
        elif mode == "40G":
            call = (fn_name, self._set_led, led_port)

        led_index = led_index_list[0]
        set_calls[led_index] = call
        set_calls[led_index + 1] = None
        set_calls[led_index + 2] = None
        set_calls[led_index + 3] = None
        set_calls[led_index + 4] = None
        set_calls[led_index + 5] = None
        set_calls[led_index + 6] = None
        set_calls[led_index + 7] = None

        return set_calls

class QuantaLY2RSFPp(cumulus.platform.Trident10GPort):
    _set_led = '''
;;; QuantaLY2RSFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed should always be zero;
;;;
;;; 2nd bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
set_led:
        port 1
        pushst PORTSTATUS_ZERO
        pack

        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        ret
'''
    def __init__(self, label, serdes, leds):
        cumulus.platform.Trident10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_type=None,
                                                 phy_addr=None,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        for led in led_index_list:
            set_calls[led] = call
            set_calls[led + 1] = None

        return set_calls

class QuantaLY2RLED(cumulus.ledup.TridentLEDController):
    num_leds = 64

class QuantaLY2RSwitch(cumulus.platform.BCMSwitch):
    ledup = QuantaLY2RLED
    _sfp = QuantaLY2RSFPp
    _qsfp = QuantaLY2RQSFPp
    has_phy_ucode_spi_rom = False
    has_phy_ucode_mdio = False
    ports = (
        _sfp(label="1",  serdes=5,  leds=(0, 0)),
        _sfp(label="2",  serdes=7,  leds=(0, 2)),
        _sfp(label="3",  serdes=4,  leds=(0, 4)),
        _sfp(label="4",  serdes=6,  leds=(0, 6)),
        _sfp(label="5",  serdes=11, leds=(0, 8)),
        _sfp(label="6",  serdes=9,  leds=(0, 10)),
        _sfp(label="7",  serdes=8,  leds=(0, 12)),
        _sfp(label="8",  serdes=10, leds=(0, 14)),
        _sfp(label="9",  serdes=12, leds=(0, 16)),
        _sfp(label="10", serdes=13, leds=(0, 18)),
        _sfp(label="11", serdes=15, leds=(0, 20)),
        _sfp(label="12", serdes=14, leds=(0, 22)),
        _sfp(label="13", serdes=17, leds=(0, 24)),
        _sfp(label="14", serdes=19, leds=(0, 26)),
        _sfp(label="15", serdes=16, leds=(0, 28)),
        _sfp(label="16", serdes=18, leds=(0, 30)),
        _sfp(label="17", serdes=20, leds=(0, 32)),
        _sfp(label="18", serdes=21, leds=(0, 34)),
        _sfp(label="19", serdes=23, leds=(0, 36)),
        _sfp(label="20", serdes=22, leds=(0, 38)),
        _sfp(label="21", serdes=24, leds=(0, 40)),
        _sfp(label="22", serdes=25, leds=(0, 42)),
        _sfp(label="23", serdes=27, leds=(0, 44)),
        _sfp(label="24", serdes=26, leds=(0, 46)),
        _sfp(label="25", serdes=29, leds=(0, 48)),
        _sfp(label="26", serdes=31, leds=(0, 50)),
        _sfp(label="27", serdes=28, leds=(0, 52)),
        _sfp(label="28", serdes=30, leds=(0, 54)),
        _sfp(label="29", serdes=32, leds=(0, 56)),
        _sfp(label="30", serdes=33, leds=(0, 58)),
        _sfp(label="31", serdes=35, leds=(0, 60)),
        _sfp(label="32", serdes=34, leds=(0, 62)),
        _sfp(label="33", serdes=43, leds=(1, 0)),
        _sfp(label="34", serdes=41, leds=(1, 2)),
        _sfp(label="35", serdes=40, leds=(1, 4)),
        _sfp(label="36", serdes=42, leds=(1, 6)),
        _sfp(label="37", serdes=45, leds=(1, 8)),
        _sfp(label="38", serdes=47, leds=(1, 10)),
        _sfp(label="39", serdes=46, leds=(1, 12)),
        _sfp(label="40", serdes=44, leds=(1, 14)),
        _sfp(label="41", serdes=48, leds=(1, 16)),
        _sfp(label="42", serdes=49, leds=(1, 18)),
        _sfp(label="43", serdes=51, leds=(1, 20)),
        _sfp(label="44", serdes=50, leds=(1, 22)),
        _sfp(label="45", serdes=52, leds=(1, 24)),
        _sfp(label="46", serdes=53, leds=(1, 26)),
        _sfp(label="47", serdes=55, leds=(1, 28)),
        _sfp(label="48", serdes=54, leds=(1, 30)),


        _qsfp(label="49", serdes=(56,57,58,59), leds=(1,32)),
        _qsfp(label="50", serdes=(60,63,61,62), leds=(1,40)),
        _qsfp(label="51", serdes=(64,65,66,67), leds=(1,48)),
        _qsfp(label="52", serdes=(68,71,69,70), leds=(1,56)),
    )

class QuantaLY2R_PSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1_present'] = 1
        else:
            self.attrs['psu_pwr1_present'] = 0
        if self.get_gpio_value(self.psu_dc_ok) == '1':
            self.attrs['psu_pwr1_dc_ok'] = 1
        else:
            self.attrs['psu_pwr1_dc_ok'] = 0
        if self.attrs['psu_pwr1_present'] and self.attrs['psu_pwr1_dc_ok']:
            self.attrs['psu_pwr1_all_ok'] = 1
        return 0

class QuantaLY2R_Fan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    fan_min = 9500
    fan_max = 21000
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-002e'

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '0':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class QuantaLY2RFan1(QuantaLY2R_Fan):
    fan_present = 'gpio212'
    name = 'Fan1'
    driver_hwmon = ['fan1']

class QuantaLY2RFan2(QuantaLY2R_Fan):
    fan_present = 'gpio212'
    name = 'Fan2'
    driver_hwmon = ['fan2']

class QuantaLY2RFan3(QuantaLY2R_Fan):
    fan_present = 'gpio213'
    name = 'Fan3'
    driver_hwmon = ['fan3']

class QuantaLY2RFan4(QuantaLY2R_Fan):
    fan_present = 'gpio213'
    name = 'Fan4'
    driver_hwmon = ['fan5']

class QuantaLY2RFan5(QuantaLY2R_Fan):
    fan_present = 'gpio214'
    name = 'Fan5'
    driver_hwmon = ['fan6']

class QuantaLY2RFan6(QuantaLY2R_Fan):
    fan_present = 'gpio214'
    name = 'Fan6'
    driver_hwmon = ['fan7']

class QuantaLY2RPSU1(QuantaLY2R_PSU):
    name = 'PSU1'
    psu_present = 'gpio152'
    psu_dc_ok = 'gpio153'

class QuantaLY2RPSU2(QuantaLY2R_PSU):
    name = 'PSU2'
    psu_present = 'gpio136'
    psu_dc_ok = 'gpio137'

class QuantaLY2RSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'gpio235'
    good_led_color = '1'  # Green
    bad_led_color = '0'   # Off

    def led_update(self, color):
        self.set_gpio_value(self.led_location, color)
        #print 'loc: %s color %s' %(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '0':
            color = 'off'
        else:
            color = 'green'
        return self.name, color

class QuantaLY2RTemp(cumulus.sensors.Temp_Unit):
    temp_max = 68
    temp_crit = 80

class QuantaLY2RTemp1(QuantaLY2RTemp):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'
    driver_hwmon = ['temp1']
    temp_max = 100
    temp_crit = 105

class QuantaLY2RTemp2(QuantaLY2RTemp):
    name = 'Temp2'
    description = "Left Corner near PHY"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-002e'
    driver_hwmon = ['temp1']

class QuantaLY2RTemp3(QuantaLY2RTemp):
    name = 'Temp3'
    description = "Left Side of Networking ASIC"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-002e'
    driver_hwmon = ['temp2']

class QuantaLY2RTemp4(QuantaLY2RTemp):
    name = 'Temp4'
    description = "Right Side of Networking ASIC"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-002e'
    driver_hwmon = ['temp3']

class QuantaLY2RTemp5(QuantaLY2RTemp):
    name = 'Temp5'
    description = "Fan Outlet Sensor located near CPU"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-002e'
    driver_hwmon = ['temp4']

class QuantaLY2RPWM1(cumulus.sensors.PWM_Unit):
    fans = (QuantaLY2RFan1(),
            QuantaLY2RFan2(),
            QuantaLY2RFan3(),
            QuantaLY2RFan4(),
            QuantaLY2RFan5(),
            QuantaLY2RFan6(),
            )
    temps = (QuantaLY2RTemp1(),
             QuantaLY2RTemp2(),
             QuantaLY2RTemp3(),
             QuantaLY2RTemp4(),
             QuantaLY2RTemp5(),
             )

class QuantaLY2RSensors():
    units = ( QuantaLY2RPSU1(),
              QuantaLY2RPSU2(),
              QuantaLY2RFan1(),
              QuantaLY2RFan2(),
              QuantaLY2RFan3(),
              QuantaLY2RFan4(),
              QuantaLY2RFan5(),
              QuantaLY2RFan6(),
              QuantaLY2RTemp1(),
              QuantaLY2RTemp2(),
              QuantaLY2RTemp3(),
              QuantaLY2RTemp4(),
              QuantaLY2RTemp5(),
              )

class QuantaLY2RPWMs():
    units = (QuantaLY2RPWM1(),
             )

class QuantaLY2RLEDs():
    units = (QuantaLY2RSystemLED(),
             )

class QuantaLY2R(cumulus.platform.Platform):
    name = 'quanta,ly2r'
    switch = QuantaLY2RSwitch(cumulus.platform.TridentChip())
    statusleds = QuantaLY2RLEDs()
    pwms = QuantaLY2RPWMs()
    sensors = QuantaLY2RSensors()

class QuantaLB9SFPp(cumulus.platform.Triumph10GPort):
    def __init__(self, label, hw_port, phy_addr, leds):
        cumulus.platform.Triumph10GPort.__init__(self,
                                                 label=label,
                                                 hw_port=hw_port,
                                                 phy_type="8727",
                                                 phy_addr=phy_addr,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')
    _set_led_link = '''
; QuantaLB9SFPp - link
set_led:
        port a

        pushst  PORTSTATUS_LINKEN
        tinv                    ; LEDs are active low
        pack

        ret
'''
    _set_led_activity = '''
; QuantaLB9SFPp - activity
set_led:
        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        tinv ; LEDs active low
        pack

        ret
    '''
    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call_link = (fn_name + '_link', self._set_led_link, self.hw_port_num(mode, 0))
        call_activity = (fn_name + '_activity', self._set_led_activity, self.hw_port_num(mode, 0))
        set_calls[led_index_list[0]] = call_link
        set_calls[led_index_list[0] + 2] = call_activity

        return set_calls

class QuantaLB9GigE(cumulus.platform.Triumph1GPort):
    def __init__(self, label, hw_port, phy_addr):
        cumulus.platform.Triumph1GPort.__init__(self,
                                                label=label,
                                                hw_port=hw_port,
                                                phy_type="54680",
                                                phy_addr=phy_addr,
                                                phy_layer='1GBaseT',
                                                leds=None,
                                                unit=0)

class QuantaLB9LED(cumulus.ledup.TriumphLEDController):
    num_leds = 8

class QuantaLB9Switch(cumulus.platform.BCMSwitch):
    '''
    led chain starting from bit 1 and ending on bit 40....
     1 : sfp_45_act, sfp_45_link_g, sfp_45_link_y,
     4 : sfp_46_act, sfp_46_link_g, sfp_46_link_y,
     7 : sfp_47_act, sfp_47_link_g, sfp_47_link_y,
    10 : sfp_48_act, sfp_48_link_g, sfp_48_link_y,
    13 : rj_45_act, 1, rj_45_link_g, rj_45_link_y,
    17 : rj_46_act, 1, rj_46_link_g, rj_46_link_y,
    21 : rj_47_act, 1, rj_47_link_g, rj_47_link_y,
    25 : rj_48_act, 1, rj_48_link_g, rj_48_link_y,
    29 : mod_a_0, mod_a_1, mod_a_2,
    32 : mod_b_0, mod_b_1, mod_b_2,
    35 : 1, 1, 1,
    38 : 1, 1, 1
    '''
    ledup = QuantaLB9LED
    _gige = QuantaLB9GigE
    _sfp = QuantaLB9SFPp
    has_phy_ucode_mdio = False
    has_phy_ucode_spi_rom = True

    ports = (
        _gige(label="1",  hw_port='ge0',  phy_addr=0x1),
        _gige(label="2",  hw_port='ge1',  phy_addr=0x2),
        _gige(label="3",  hw_port='ge2',  phy_addr=0x3),
        _gige(label="4",  hw_port='ge3',  phy_addr=0x4),
        _gige(label="5",  hw_port='ge4',  phy_addr=0x5),
        _gige(label="6",  hw_port='ge5',  phy_addr=0x6),
        _gige(label="7",  hw_port='ge6',  phy_addr=0x7),
        _gige(label="8",  hw_port='ge7',  phy_addr=0x8),
        _gige(label="9",  hw_port='ge8',  phy_addr=0x9),
        _gige(label="10", hw_port='ge9' , phy_addr=0xa),
        _gige(label="11", hw_port='ge10', phy_addr=0xb),
        _gige(label="12", hw_port='ge11', phy_addr=0xc),
        _gige(label="13", hw_port='ge12', phy_addr=0xd),
        _gige(label="14", hw_port='ge13', phy_addr=0xe),
        _gige(label="15", hw_port='ge14', phy_addr=0xf),
        _gige(label="16", hw_port='ge15', phy_addr=0x10),
        _gige(label="17", hw_port='ge16', phy_addr=0x11),
        _gige(label="18", hw_port='ge17', phy_addr=0x12),
        _gige(label="19", hw_port='ge18', phy_addr=0x13),
        _gige(label="20", hw_port='ge19', phy_addr=0x14),
        _gige(label="21", hw_port='ge20', phy_addr=0x15),
        _gige(label="22", hw_port='ge21', phy_addr=0x16),
        _gige(label="23", hw_port='ge22', phy_addr=0x17),
        _gige(label="24", hw_port='ge23', phy_addr=0x18),
        _gige(label="25", hw_port='ge24', phy_addr=0x21),
        _gige(label="26", hw_port='ge25', phy_addr=0x22),
        _gige(label="27", hw_port='ge26', phy_addr=0x23),
        _gige(label="28", hw_port='ge27', phy_addr=0x24),
        _gige(label="29", hw_port='ge28', phy_addr=0x25),
        _gige(label="30", hw_port='ge29', phy_addr=0x26),
        _gige(label="31", hw_port='ge30', phy_addr=0x27),
        _gige(label="32", hw_port='ge31', phy_addr=0x28),
        _gige(label="33", hw_port='ge32', phy_addr=0x29),
        _gige(label="34", hw_port='ge33', phy_addr=0x2a),
        _gige(label="35", hw_port='ge34', phy_addr=0x2b),
        _gige(label="36", hw_port='ge35', phy_addr=0x2c),
        _gige(label="37", hw_port='ge36', phy_addr=0x2d),
        _gige(label="38", hw_port='ge37', phy_addr=0x2e),
        _gige(label="39", hw_port='ge38', phy_addr=0x2f),
        _gige(label="40", hw_port='ge39', phy_addr=0x30),
        _gige(label="41", hw_port='ge40', phy_addr=0x31),
        _gige(label="42", hw_port='ge41', phy_addr=0x32),
        _gige(label="43", hw_port='ge42', phy_addr=0x33),
        _gige(label="44", hw_port='ge43', phy_addr=0x34),
        _gige(label="45", hw_port='ge44', phy_addr=0x35),
        _gige(label="46", hw_port='ge45', phy_addr=0x36),
        _gige(label="47", hw_port='ge46', phy_addr=0x37),
        _gige(label="48", hw_port='ge47', phy_addr=0x38),
        _sfp(label="49",  hw_port='hg0',  phy_addr=0x42, leds=(0,0)),
        _sfp(label="50",  hw_port='hg1',  phy_addr=0x43, leds=(0,1)),
        _sfp(label="51",  hw_port='hg2',  phy_addr=0x46, leds=(0,4)),
        _sfp(label="52",  hw_port='hg3',  phy_addr=0x47, leds=(0,5)),
    )

class QuantaLB9_PSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1_present'] = 1
        else:
            self.attrs['psu_pwr1_present'] = 0
        if self.get_gpio_value(self.psu_all_ok) == '1':
            self.attrs['psu_pwr1_all_ok'] = 1
        else:
            self.attrs['psu_pwr1_all_ok'] = 0
        return 0

QuantaLB9_5_2c_path = '/sys/devices/soc8541.0/e0003000.i2c/i2c-0/i2c-5/5-002c'
QuantaLB9_6_2f_path = '/sys/devices/soc8541.0/e0003000.i2c/i2c-0/i2c-6/6-002f'

class QuantaLB9Fan(cumulus.sensors.Fan_Unit):
    minpwm = 64
    maxpwm = 255
    fan_min = 2500
    fan_max = 14000
    def __init__(self):
        off = int(self.__class__.__name__[12:])%4 + 1
        self.name = 'Fan' + str(off)
        self.driver_hwmon = ['fan' + str(off)]
        self.pwm_hwmon = ['pwm' + str(off)]

        cumulus.sensors.Fan_Unit.__init__(self)


class QuantaLB9Fan1(QuantaLB9Fan):
    driver_path = QuantaLB9_5_2c_path

class QuantaLB9Fan2(QuantaLB9Fan):
    driver_path = QuantaLB9_5_2c_path

class QuantaLB9Fan3(QuantaLB9Fan):
    driver_path = QuantaLB9_5_2c_path

class QuantaLB9Fan4(QuantaLB9Fan):
    driver_path = QuantaLB9_5_2c_path

class QuantaLB9Fan5(QuantaLB9Fan):
    driver_path = QuantaLB9_6_2f_path

class QuantaLB9Fan6(QuantaLB9Fan):
    driver_path = QuantaLB9_6_2f_path

class QuantaLB9Fan7(QuantaLB9Fan):
    driver_path = QuantaLB9_6_2f_path

class QuantaLB9Fan8(QuantaLB9Fan):
    driver_path = QuantaLB9_6_2f_path

class QuantaLB9PSU1(QuantaLB9_PSU):
    name = 'PSU1'
    psu_present = 'gpio96'
    psu_all_ok = 'gpio97'

class QuantaLB9PSU2(QuantaLB9_PSU):
    name = 'PSU2'
    psu_present = 'gpio112'
    psu_all_ok = 'gpio113'

class QuantaLB9SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'gpio246'
    good_led_color = '1'  # Off
    bad_led_color = '0'   # Yellow

    def led_update(self, color):
        self.set_gpio_value(self.led_location, color)
        #print 'loc: %s color %s' %(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '0':
            color = 'yellow'
        else:
            color = 'off'
        return self.name, color

class QuantaLB9Temp(cumulus.sensors.Temp_Unit):
    def __init__(self):
        self.name = (self.__class__.__name__[9:])
        self.driver_path = QuantaLB9_5_2c_path
        off = int(self.__class__.__name__[13:])
        self.driver_hwmon = ['temp' + str(off)]

        cumulus.sensors.Temp_Unit.__init__(self)

class QuantaLB9Temp1(QuantaLB9Temp):
    description = "Fan outlet Sensor"
    temp_max_hyst = 35
    temp_max = 50
    temp_crit = 55

class QuantaLB9Temp2(QuantaLB9Temp):
    description = "MPC8541(CPU) Sensor"

class QuantaLB9Temp3(QuantaLB9Temp):
    description = "Front Right Side"
    temp_max_hyst = 35
    temp_max = 58
    temp_crit = 65

class QuantaLB9Temp4(QuantaLB9Temp):
    description = "Front Left Side"
    temp_max_hyst = 35
    temp_max = 58
    temp_crit = 65

class QuantaLB9Temp5(QuantaLB9Temp):
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name

def QuantaLB9FindFans():
    # Quick hack to prevent other platforms from running this. CM-2908
    # Need to fix this elegantly.
    plat = os.popen('platform-detect -m').read().strip()
    if plat != 'quanta,lb9':
        return ()

    # Logic taken from /usr/share/platform-config/quanta/lb9/hw_init.d/S20fan_config.sh
    f2b_fans = (QuantaLB9Fan1(),
                QuantaLB9Fan2(),
                QuantaLB9Fan3(),
                QuantaLB9Fan4(),
    )
    b2f_fans = (QuantaLB9Fan5(),
                QuantaLB9Fan6(),
                QuantaLB9Fan7(),
                QuantaLB9Fan8(),
    )
    f_name = subprocess.check_output("decode-syseeprom |grep 'Part Number'|awk '{print $5}'", shell=True)

    found = 0
    if f_name == "1LB9BZZ0STQ":
        return f2b_fans
    elif f_name == "1LB9BZZ0STR":
        return b2f_fans

    b2f_count = 0
    f2b_count = 0
    for fan in b2f_fans:
        if fan.detect_state() != 'ABSENT':
            b2f_count = b2f_count + 1
    for fan in f2b_fans:
        if fan.detect_state() != 'ABSENT':
            f2b_count = f2b_count + 1
    if f2b_count > b2f_count:
        return f2b_fans

    return b2f_fans

class QuantaLB9PWM1(cumulus.sensors.PWM_Unit):
    temps = (QuantaLB9Temp1(),
             QuantaLB9Temp2(),
             QuantaLB9Temp3(),
             QuantaLB9Temp4(),
             QuantaLB9Temp5(),
    )
    fans = QuantaLB9FindFans()

class QuantaLB9Sensors():
    temps = (QuantaLB9Temp1(),
             QuantaLB9Temp2(),
             QuantaLB9Temp3(),
             QuantaLB9Temp4(),
             QuantaLB9Temp5(),
    )
    fans = QuantaLB9FindFans()

    units = fans + temps

class QuantaLB9PWMs():
    units = (QuantaLB9PWM1(),
             )

class QuantaLB9LEDs():
    units = (QuantaLB9SystemLED(),
             )

class QuantaLB9(cumulus.platform.Platform):
    name = 'quanta,lb9'
    switch = QuantaLB9Switch(cumulus.platform.TriumphChip())
    statusleds = QuantaLB9LEDs()
    pwms = QuantaLB9PWMs()
    sensors = QuantaLB9Sensors()

### Quanta LY6
class QuantaLY6QSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
; QuantaLY6QSFPp - green link, amber activity
set_led:
        port  a

        pushst PORTSTATUS_ZERO
        pack

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack

        ret

'''
    _set_led_4x10 = '''
;;;
;;; Input : register A, logical port
;;; Input / Output : register B, accumulated port status

;;; For each port accumulate 2 bits of information in register B:
;;;   register B[0] - link enabled
;;;   register B[1] - activity (TX _OR_ RX)

SUB_INTF_LINKEN     equ 0x0  ; link enabled
SUB_INTF_ACTIVITY   equ 0x1  ; activity

sub_intf_info:

        ;;; push OR of current TX/RX activity onto stack
        port a
        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor

        ;;; push accumlated link activity onto stack
        tst B, SUB_INTF_ACTIVITY
        push cy

        ;;; OR accumlated activity with current activity and store
        ;;; result back in register B
        tor
        pop
        bit B, SUB_INTF_ACTIVITY

        ;;; push current LINKEN onto stack
        pushst  PORTSTATUS_LINKEN

        ;;; push accumlated link enable onto stack
        tst B, SUB_INTF_LINKEN
        push cy

        ;;; OR accumlated LINKEN with current LINKEN and store
        ;;; result back in register B
        tor
        pop
        bit B, SUB_INTF_LINKEN

        ret

;;; QuantaLY6QSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active high), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:

        port a
        pushst PORTSTATUS_ZERO
        pack

        ;;; initialize B
        ld  b,0

        ;;; load sub-0 info
        call    sub_intf_info

        ;;; load sub-1 info
        inc a
        call    sub_intf_info

        ;;; load sub-2 info
        inc a
        call    sub_intf_info

        ;;; load sub-3 info
        inc a
        call    sub_intf_info

        ;;; push accumlated link activity onto stack
        tst B, SUB_INTF_ACTIVITY
        push    cy

        ;;; combine with BLINK state
        push    (BLINK_STATE_P)
        tand
        tinv    ; flash off with activity

        ;;; push accumlated link enable onto stack
        tst B, SUB_INTF_LINKEN
        push    cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand
        pack

        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack
        pushst PORTSTATUS_ZERO
        pack

        ret

'''
    def __init__(self, label, serdes, leds):
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                    label=label,
                                                    serdes=serdes,
                                                    phy_types=None,
                                                    phy_addrs=None,
                                                    leds=leds,
                                                    oversub=True,
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

        # Only one LED per QSFP on this platform
        led_index = led_index_list[0]
        set_calls[led_index] = call
        set_calls[led_index + 1 ] = None
        set_calls[led_index + 2 ] = None
        set_calls[led_index + 3 ] = None
        set_calls[led_index + 4 ] = None
        set_calls[led_index + 5 ] = None
        set_calls[led_index + 6 ] = None
        set_calls[led_index + 7 ] = None

        return set_calls

class QuantaLY6LED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 128

class QuantaLY6_PSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        err = False
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1'] = 'installed'
        else:
            self.attrs['psu_pwr1'] = 'not_installed'
            err = True
        if self.get_gpio_value(self.psu_dc_ok) == '1':
            self.attrs['psu_pwr1'] += ', dc_ok'
        else:
            self.attrs['psu_pwr1'] += ', dc_not_ok'
            err = True
        if self.get_gpio_value(self.psu_ac_ok) == '1':
            self.attrs['psu_pwr1'] += ', ac_ok'
        else:
            self.attrs['psu_pwr1'] += ', ac_not_ok'
            err = True

        if err is False:
            self.attrs['psu_pwr1'] += ', ok'

        return 0

class QuantaLY6_Fan(cumulus.sensors.Fan_Unit):
    fan_min = 5000
    fan_max = 16500
    rpmmode = 1
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '0':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class QuantaLY6Fan1(QuantaLY6_Fan):
    fan_present = 'gpio172'
    name = 'Fan1'
    driver_hwmon = ['fan1']

class QuantaLY6Fan2(QuantaLY6_Fan):
    fan_present = 'gpio172'
    name = 'Fan2'
    driver_hwmon = ['fan2']

class QuantaLY6Fan3(QuantaLY6_Fan):
    fan_present = 'gpio173'
    name = 'Fan3'
    driver_hwmon = ['fan3']

class QuantaLY6Fan4(QuantaLY6_Fan):
    fan_present = 'gpio173'
    name = 'Fan4'
    driver_hwmon = ['fan5']

class QuantaLY6Fan5(QuantaLY6_Fan):
    fan_present = 'gpio174'
    name = 'Fan5'
    driver_hwmon = ['fan6']

class QuantaLY6Fan6(QuantaLY6_Fan):
    fan_present = 'gpio174'
    name = 'Fan6'
    driver_hwmon = ['fan7']

class QuantaLY6PSU1(QuantaLY6_PSU):
    name = 'PSU1'
    psu_present = 'gpio184'
    psu_ac_ok = 'gpio190'
    psu_dc_ok = 'gpio185'

class QuantaLY6PSU2(QuantaLY6_PSU):
    name = 'PSU2'
    psu_present = 'gpio187'
    psu_ac_ok = 'gpio191'
    psu_dc_ok = 'gpio188'

class QuantaLY6_LED(cumulus.sensors.StatusLED_Unit):
    good_led_color = '1'  # Green
    bad_led_color = '0'   # Off

    def led_update(self, color):
        self.set_gpio_value(self.led_location, color)
        #print 'loc: %s color %s' %(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '1':
            color = 'green'
        else:
            color = 'off'
        return self.name, color

class QuantaLY6PSU1LED(QuantaLY6_LED):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'gpio194'

class QuantaLY6PSU2LED(QuantaLY6_LED):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'gpio196'

class QuantaLY6FanLED(QuantaLY6_LED):
    name = 'Fan'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4', 'Fan5', 'Fan6']
    led_location = 'gpio198'

class QuantaLY6SystemLED(QuantaLY6_LED):
    name = 'System'
    led_location = 'gpio235'

class QuantaLY6Temp(cumulus.sensors.Temp_Unit):
    temp_max = 75

class QuantaLY6Temp1(QuantaLY6Temp):
    name = 'Temp1'
    description = "Right Corner near PHY"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'
    driver_hwmon = ['temp1']

class QuantaLY6Temp2(QuantaLY6Temp):
    name = 'Temp2'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'
    driver_hwmon = ['temp2']

class QuantaLY6Temp3(QuantaLY6Temp):
    name = 'Temp3'
    description = "Near Fan Outlet"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'
    driver_hwmon = ['temp3']

class QuantaLY6Temp4(QuantaLY6Temp):
    name = 'Temp4'
    description = "Near CPU on CPU Board"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'
    driver_hwmon = ['temp5']

class QuantaLY6Temp5(QuantaLY6Temp):
    name = 'Temp5'
    description = "Left Top Corner on CPU Board"
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'
    driver_hwmon = ['temp6']

class QuantaLY6PWM1(cumulus.sensors.PWM_Unit):
    fans = (QuantaLY6Fan1(),
            QuantaLY6Fan2(),
            QuantaLY6Fan3(),
            QuantaLY6Fan4(),
            QuantaLY6Fan5(),
            QuantaLY6Fan6(),
            )
    temps = (QuantaLY6Temp1(),
             QuantaLY6Temp2(),
             QuantaLY6Temp3(),
             QuantaLY6Temp4(),
             QuantaLY6Temp5(),
             )

class QuantaLY6Sensors():
    units = ( QuantaLY6PSU1(),
              QuantaLY6PSU2(),
              QuantaLY6Fan1(),
              QuantaLY6Fan2(),
              QuantaLY6Fan3(),
              QuantaLY6Fan4(),
              QuantaLY6Fan5(),
              QuantaLY6Fan6(),
              QuantaLY6Temp1(),
              QuantaLY6Temp2(),
              QuantaLY6Temp3(),
              QuantaLY6Temp4(),
              QuantaLY6Temp5(),
              )

class QuantaLY6PWMs():
    units = (QuantaLY6PWM1(),
             )

class QuantaLY6LEDs():
    units = (QuantaLY6PSU1LED(),
             QuantaLY6PSU2LED(),
             QuantaLY6SystemLED(),
             QuantaLY6FanLED(),
             )

class QuantaLY6Switch(cumulus.platform.BCMSwitch):
    ledup = QuantaLY6LED
    _qsfp = QuantaLY6QSFPp

    has_phy_ucode_spi_rom = False
    has_phy_ucode_mdio = False

    ports = (
        _qsfp(label="1", serdes=(  0,   1,   2,   3), leds=(0, 0*8)),
        _qsfp(label="2", serdes=(  4,   5,   6,   7), leds=(0, 1*8)),
        _qsfp(label="3", serdes=(  8,   9,  10,  11), leds=(0, 2*8)),
        _qsfp(label="4", serdes=( 12,  13,  14,  15), leds=(0, 3*8)),
        _qsfp(label="5", serdes=( 16,  17,  18,  19), leds=(0, 4*8)),
        _qsfp(label="6", serdes=( 20,  21,  22,  23), leds=(0, 5*8)),
        _qsfp(label="7", serdes=( 24,  25,  26,  27), leds=(0, 6*8)),
        _qsfp(label="8", serdes=( 28,  29,  30,  31), leds=(0, 7*8)),
        _qsfp(label="9", serdes=( 32,  33,  34,  35), leds=(0, 8*8)),
        _qsfp(label="10", serdes=( 36,  37,  38,  39), leds=(0, 9*8)),
        _qsfp(label="11", serdes=( 40,  41,  42,  43), leds=(0, 10*8)),
        _qsfp(label="12", serdes=( 44,  45,  46,  47), leds=(0, 11*8)),
        _qsfp(label="13", serdes=( 48,  49,  50,  51), leds=(0, 12*8)),
        _qsfp(label="14", serdes=( 52,  53,  54,  55), leds=(0, 13*8)),
        _qsfp(label="15", serdes=( 56,  57,  58,  59), leds=(0, 14*8)),
        _qsfp(label="16", serdes=( 60,  61,  62,  63), leds=(0, 15*8)),
        _qsfp(label="17", serdes=( 64,  65,  66,  67), leds=(1, 0*8)),
        _qsfp(label="18", serdes=( 68,  69,  70,  71), leds=(1, 1*8)),
        _qsfp(label="19", serdes=( 72,  73,  74,  75), leds=(1, 2*8)),
        _qsfp(label="20", serdes=( 76,  77,  78,  79), leds=(1, 3*8)),
        _qsfp(label="21", serdes=( 80,  81,  82,  83), leds=(1, 4*8)),
        _qsfp(label="22", serdes=( 84,  85,  86,  87), leds=(1, 5*8)),
        _qsfp(label="23", serdes=( 88,  89,  90,  91), leds=(1, 6*8)),
        _qsfp(label="24", serdes=( 92,  93,  94,  95), leds=(1, 7*8)),
        _qsfp(label="25", serdes=( 96,  97,  98,  99), leds=(1, 8*8)),
        _qsfp(label="26", serdes=(100, 101, 102, 103), leds=(1, 9*8)),
        _qsfp(label="27", serdes=(104, 105, 106, 107), leds=(1, 10*8)),
        _qsfp(label="28", serdes=(108, 109, 110, 111), leds=(1, 11*8)),
        _qsfp(label="29", serdes=(112, 113, 114, 115), leds=(1, 12*8)),
        _qsfp(label="30", serdes=(116, 117, 118, 119), leds=(1, 13*8)),
        _qsfp(label="31", serdes=(120, 121, 122, 123), leds=(1, 14*8)),
        _qsfp(label="32", serdes=(124, 125, 126, 127), leds=(1, 15*8)),
    )

class QuantaLY6P2020(cumulus.platform.Platform):
    name = 'quanta,ly6_p2020'
    switch = QuantaLY6Switch(cumulus.platform.TridentTwo_56850_Chip())
    statusleds = QuantaLY6LEDs()
    pwms = QuantaLY6PWMs()
    sensors = QuantaLY6Sensors()


### Quanta LY6Rangeley
class QuantaLY6RangeleyFan(cumulus.sensors.Fan_Unit):
    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-004e'
                driver_path = os.path.join(pci_path, x, c)
                break

    fan_min = 9400
    fan_max = 16500
    rpmmode = 1

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '0':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class QuantaLY6RangeleyCoreTemp(cumulus.sensors.Temp_Unit):
    description = cumulus.sensors.Temp_Unit.intel_cpu_sensor_name
    driver_path = '/sys/devices/platform/coretemp.0'
    temp_max_hyst = 65
    temp_max = 90
    temp_crit = 98

class QuantaLY6RangeleyCY8Temp(cumulus.sensors.Temp_Unit):
    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-004e'
                driver_path = os.path.join(pci_path, x, c)
                break
    temp_max_hyst = 45
    temp_max = 70
    # OTP Temp is 80C as per Quanta
    temp_crit = 80

class QuantaLY6RangeleyPSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1_present'] = 1
        else:
            self.attrs['psu_pwr1_present'] = 0
        if ((self.get_gpio_value(self.psu_ac_ok) == '1') and
            (self.get_gpio_value(self.psu_dc_ok) == '1')):
            self.attrs['psu_pwr1_all_ok'] = 1
        else:
            self.attrs['psu_pwr1_all_ok'] = 0
        return 0

class QuantaLY6RangeleyLED(cumulus.sensors.StatusLED_Unit):
    good_led_color = '1'  # Green
    bad_led_color = '0'   # Off

    def led_update(self, color):
        #print 'loc: %s color %s' %(self.led_location, color)
        self.set_gpio_value(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '0':
            color = 'off'
        else:
            color = 'green'
        return self.name, color

class QuantaLY6RangeleyFan1(QuantaLY6RangeleyFan):
    fan_present = 'fan1_present'
    name = 'Fan1'
    description = 'Fan Tray 1'
    driver_hwmon = ['fan1']

class QuantaLY6RangeleyFan2(QuantaLY6RangeleyFan):
    fan_present = 'fan1_present'
    name = 'Fan2'
    description = 'Fan Tray 1'
    driver_hwmon = ['fan5']

class QuantaLY6RangeleyFan3(QuantaLY6RangeleyFan):
    fan_present = 'fan2_present'
    name = 'Fan3'
    description = 'Fan Tray 2'
    driver_hwmon = ['fan2']

class QuantaLY6RangeleyFan4(QuantaLY6RangeleyFan):
    fan_present = 'fan2_present'
    name = 'Fan4'
    description = 'Fan Tray 2'
    driver_hwmon = ['fan6']

class QuantaLY6RangeleyFan5(QuantaLY6RangeleyFan):
    fan_present = 'fan3_present'
    name = 'Fan5'
    description = 'Fan Tray 3'
    driver_hwmon = ['fan3']

class QuantaLY6RangeleyFan6(QuantaLY6RangeleyFan):
    fan_present = 'fan3_present'
    name = 'Fan6'
    description = 'Fan Tray 3'
    driver_hwmon = ['fan7']

class QuantaLY6RangeleyPSU1(QuantaLY6RangeleyPSU):
    name = 'PSU1'
    psu_present = 'psu_pwr1_present'
    psu_ac_ok = 'psu_pwr1_ac_ok'
    psu_dc_ok = 'psu_pwr1_dc_ok'

class QuantaLY6RangeleyPSU2(QuantaLY6RangeleyPSU):
    name = 'PSU2'
    psu_present = 'psu_pwr2_present'
    psu_ac_ok = 'psu_pwr2_ac_ok'
    psu_dc_ok = 'psu_pwr2_dc_ok'

class QuantaLY6RangeleyTemp1(QuantaLY6RangeleyCoreTemp):
    name = 'Temp1'
    driver_hwmon = ['temp2']

class QuantaLY6RangeleyTemp2(QuantaLY6RangeleyCoreTemp):
    name = 'Temp2'
    driver_hwmon = ['temp3']

class QuantaLY6RangeleyTemp3(QuantaLY6RangeleyCoreTemp):
    name = 'Temp3'
    driver_hwmon = ['temp4']

class QuantaLY6RangeleyTemp4(QuantaLY6RangeleyCoreTemp):
    name = 'Temp4'
    driver_hwmon = ['temp5']

class QuantaLY6RangeleyTemp5(QuantaLY6RangeleyCoreTemp):
    name = 'Temp5'
    driver_hwmon = ['temp6']

class QuantaLY6RangeleyTemp6(QuantaLY6RangeleyCoreTemp):
    name = 'Temp6'
    driver_hwmon = ['temp7']

class QuantaLY6RangeleyTemp7(QuantaLY6RangeleyCoreTemp):
    name = 'Temp7'
    driver_hwmon = ['temp8']

class QuantaLY6RangeleyTemp8(QuantaLY6RangeleyCoreTemp):
    name = 'Temp8'
    driver_hwmon = ['temp9']

class QuantaLY6RangeleyTemp9(QuantaLY6RangeleyCY8Temp):
    name = 'Temp9'
    description = "Right Corner near PHY"
    driver_hwmon = ['temp1']

class QuantaLY6RangeleyTemp10(QuantaLY6RangeleyCY8Temp):
    name = 'Temp10'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_hwmon = ['temp2']

class QuantaLY6RangeleyTemp11(QuantaLY6RangeleyCY8Temp):
    name = 'Temp11'
    description = "Near Fan Outlet"
    driver_hwmon = ['temp3']

class QuantaLY6RangeleyTemp12(QuantaLY6RangeleyCY8Temp):
    name = 'Temp12'
    description = "Near CPU on CPU Board"
    driver_hwmon = ['temp5']

class QuantaLY6RangeleyTemp13(QuantaLY6RangeleyCY8Temp):
    name = 'Temp13'
    description = "Left Top Corner on CPU Board"
    driver_hwmon = ['temp6']

class QuantaLY6RangeleyTemp14(cumulus.sensors.Temp_Unit):
    name = 'Temp14'
    description = cumulus.sensors.Temp_Unit.dimm_sensor_name
    driver_hwmon = ['temp1']
    temp_max_hyst = 65
    temp_max = 90
    temp_crit = 95

    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-001a'
                driver_path = os.path.join(pci_path, x, c)
                break

class QuantaLY6RangeleyPSU1LED(QuantaLY6RangeleyLED):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'psu1_green_led'

class QuantaLY6RangeleyPSU2LED(QuantaLY6RangeleyLED):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'psu2_green_led'

class QuantaLY6RangeleyFanLED(QuantaLY6RangeleyLED):
    name = 'Fan'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4', 'Fan5', 'Fan6']
    led_location = 'fan_green_led'

class QuantaLY6RangeleySensors():
    units = (QuantaLY6RangeleyTemp1(),
             QuantaLY6RangeleyTemp2(),
             QuantaLY6RangeleyTemp3(),
             QuantaLY6RangeleyTemp4(),
             QuantaLY6RangeleyTemp5(),
             QuantaLY6RangeleyTemp6(),
             QuantaLY6RangeleyTemp7(),
             QuantaLY6RangeleyTemp8(),
             QuantaLY6RangeleyTemp9(),
             QuantaLY6RangeleyTemp10(),
             QuantaLY6RangeleyTemp11(),
             QuantaLY6RangeleyTemp12(),
             QuantaLY6RangeleyTemp13(),
             QuantaLY6RangeleyTemp14(),
             QuantaLY6RangeleyFan1(),
             QuantaLY6RangeleyFan2(),
             QuantaLY6RangeleyFan3(),
             QuantaLY6RangeleyFan4(),
             QuantaLY6RangeleyFan5(),
             QuantaLY6RangeleyFan6(),
             QuantaLY6RangeleyPSU1(),
             QuantaLY6RangeleyPSU2(),
             )

class QuantaLY6RangeleyPWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (QuantaLY6RangeleyFan1(),
            QuantaLY6RangeleyFan2(),
            QuantaLY6RangeleyFan3(),
            QuantaLY6RangeleyFan4(),
            QuantaLY6RangeleyFan5(),
            QuantaLY6RangeleyFan6(),
            )
    temps = (QuantaLY6RangeleyTemp1(),
             QuantaLY6RangeleyTemp2(),
             QuantaLY6RangeleyTemp3(),
             QuantaLY6RangeleyTemp4(),
             QuantaLY6RangeleyTemp5(),
             QuantaLY6RangeleyTemp6(),
             QuantaLY6RangeleyTemp7(),
             QuantaLY6RangeleyTemp8(),
             QuantaLY6RangeleyTemp9(),
             QuantaLY6RangeleyTemp10(),
             QuantaLY6RangeleyTemp11(),
             QuantaLY6RangeleyTemp12(),
             QuantaLY6RangeleyTemp13(),
             QuantaLY6RangeleyTemp14(),
             )

class QuantaLY6RangeleyPWMs():
    units = (QuantaLY6RangeleyPWM1(),
             )

class QuantaLY6RangeleyLEDs():
    units = (QuantaLY6RangeleyPSU1LED(),
             QuantaLY6RangeleyPSU2LED(),
             QuantaLY6RangeleyFanLED(),
             )

class QuantaLY6Rangeley(cumulus.platform.Platform):
    name = 'quanta,ly6_rangeley'
    switch = QuantaLY6Switch(cumulus.platform.TridentTwo_56850_Chip())
    statusleds = QuantaLY6RangeleyLEDs()
    pwms = QuantaLY6RangeleyPWMs()
    sensors = QuantaLY6RangeleySensors()

### Quanta LY8

class QuantaLY8_Fan(cumulus.sensors.Fan_Unit):
    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-004e'
                driver_path = os.path.join(pci_path, x, c)
                break

    fan_min = 7600
    fan_max = 18000
    rpmmode = 1

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '0':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class QuantaLY8CoreTemp(cumulus.sensors.Temp_Unit):
    description = cumulus.sensors.Temp_Unit.intel_cpu_sensor_name
    driver_path = '/sys/devices/platform/coretemp.0'
    temp_max_hyst = 65
    temp_max = 90
    temp_crit = 98

class QuantaLY8CY8Temp(cumulus.sensors.Temp_Unit):
    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-004e'
                driver_path = os.path.join(pci_path, x, c)
                break

    temp_max_hyst = 45
    temp_max = 55
    # OTP temp among sensors specified by Quanta is between 60C-70C
    # Critical temp specified is between 53C - 58C
    temp_crit = 65

class QuantaLY8PSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1_present'] = 1
        else:
            self.attrs['psu_pwr1_present'] = 0
        if ((self.get_gpio_value(self.psu_ac_ok) == '0') and
            (self.get_gpio_value(self.psu_dc_ok) == '1')):
            self.attrs['psu_pwr1_all_ok'] = 1
        else:
            self.attrs['psu_pwr1_all_ok'] = 0
        return 0

class QuantaLY8LED(cumulus.sensors.StatusLED_Unit):
    good_led_color = '1'  # Green
    bad_led_color = '0'   # Off

    def led_update(self, color):
        #print 'loc: %s color %s' %(self.led_location, color)
        self.set_gpio_value(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '0':
            color = 'off'
        else:
            color = 'green'
        return self.name, color

class QuantaLY8PSU1LED(QuantaLY8LED):
    name = 'PSU1'
    led_location = 'psu1_green_led'
    sources = ['PSU1']

class QuantaLY8PSU2LED(QuantaLY8LED):
    name = 'PSU2'
    led_location = 'psu2_green_led'
    sources = ['PSU2']

class QuantaLY8FanLED(QuantaLY8LED):
    name = 'Fans'
    led_location = 'fan_green_led'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4', 'Fan5', 'Fan6']

class QuantaLY8PSU1(QuantaLY8PSU):
    name = 'PSU1'
    psu_present = 'psu_pwr1_present'
    psu_ac_ok = 'psu_pwr1_ac_ok'
    psu_dc_ok = 'psu_pwr1_dc_ok'

class QuantaLY8PSU2(QuantaLY8PSU):
    name = 'PSU2'
    psu_present = 'psu_pwr2_present'
    psu_ac_ok = 'psu_pwr2_ac_ok'
    psu_dc_ok = 'psu_pwr2_dc_ok'

class QuantaLY8Fan1(QuantaLY8_Fan):
    fan_present = 'fan1_present'
    name = 'Fan1'
    driver_hwmon = ['fan1']

class QuantaLY8Fan2(QuantaLY8_Fan):
    fan_present = 'fan1_present'
    name = 'Fan2'
    driver_hwmon = ['fan5']

class QuantaLY8Fan3(QuantaLY8_Fan):
    fan_present = 'fan2_present'
    name = 'Fan3'
    driver_hwmon = ['fan2']

class QuantaLY8Fan4(QuantaLY8_Fan):
    fan_present = 'fan2_present'
    name = 'Fan4'
    driver_hwmon = ['fan6']

class QuantaLY8Fan5(QuantaLY8_Fan):
    fan_present = 'fan3_present'
    name = 'Fan5'
    driver_hwmon = ['fan3']

class QuantaLY8Fan6(QuantaLY8_Fan):
    fan_present = 'fan3_present'
    name = 'Fan6'
    driver_hwmon = ['fan7']

class QuantaLY8Temp1(QuantaLY8CoreTemp):
    name = 'Temp1'
    driver_hwmon = ['temp2']

class QuantaLY8Temp2(QuantaLY8CoreTemp):
    name = 'Temp2'
    driver_hwmon = ['temp3']

class QuantaLY8Temp3(QuantaLY8CoreTemp):
    name = 'Temp3'
    driver_hwmon = ['temp4']

class QuantaLY8Temp4(QuantaLY8CoreTemp):
    name = 'Temp4'
    driver_hwmon = ['temp5']

class QuantaLY8Temp5(QuantaLY8CoreTemp):
    name = 'Temp5'
    driver_hwmon = ['temp6']

class QuantaLY8Temp6(QuantaLY8CoreTemp):
    name = 'Temp6'
    driver_hwmon = ['temp7']

class QuantaLY8Temp7(QuantaLY8CoreTemp):
    name = 'Temp7'
    driver_hwmon = ['temp8']

class QuantaLY8Temp8(QuantaLY8CoreTemp):
    name = 'Temp8'
    driver_hwmon = ['temp9']

class QuantaLY8Temp9(QuantaLY8CY8Temp):
    name = 'Temp9'
    driver_hwmon = ['temp1']
    description = 'Rear Outlet Air Temp sensor'

class QuantaLY8Temp10(QuantaLY8CY8Temp):
    name = 'Temp10'
    driver_hwmon = ['temp2']
    description = 'Front Outlet Air Temp sensor'

class QuantaLY8Temp11(QuantaLY8CY8Temp):
    name = 'Temp11'
    driver_hwmon = ['temp3']
    description = 'Front Outlet Air Temp sensor'

class QuantaLY8Temp12(QuantaLY8CY8Temp):
    name = 'Temp12'
    driver_hwmon = ['temp5']
    description = 'CPU Board Temp sensor'

class QuantaLY8Temp13(QuantaLY8CY8Temp):
    name = 'Temp13'
    driver_hwmon = ['temp6']
    description = 'CPU Board Temp sensor'

class QuantaLY8Temp14(cumulus.sensors.Temp_Unit):
    name = 'Temp14'
    description = cumulus.sensors.Temp_Unit.dimm_sensor_name
    driver_hwmon = ['temp1']
    temp_max_hyst = 65
    temp_max = 90
    temp_crit = 95

    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-001a'
                driver_path = os.path.join(pci_path, x, c)
                break

class QuantaLY8Sensors():
    units = (QuantaLY8Temp1(),
             QuantaLY8Temp2(),
             QuantaLY8Temp3(),
             QuantaLY8Temp4(),
             QuantaLY8Temp5(),
             QuantaLY8Temp6(),
             QuantaLY8Temp7(),
             QuantaLY8Temp8(),
             QuantaLY8Temp9(),
             QuantaLY8Temp10(),
             QuantaLY8Temp11(),
             QuantaLY8Temp12(),
             QuantaLY8Temp13(),
             QuantaLY8Temp14(),
             QuantaLY8Fan1(),
             QuantaLY8Fan2(),
             QuantaLY8Fan3(),
             QuantaLY8Fan4(),
             QuantaLY8Fan5(),
             QuantaLY8Fan6(),
             QuantaLY8PSU1(),
             QuantaLY8PSU2(),
             )

class QuantaLY8PWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (QuantaLY8Fan1(),
            QuantaLY8Fan2(),
            QuantaLY8Fan3(),
            QuantaLY8Fan4(),
            QuantaLY8Fan5(),
            QuantaLY8Fan6(),
            )
    temps = (QuantaLY8Temp1(),
             QuantaLY8Temp2(),
             QuantaLY8Temp3(),
             QuantaLY8Temp4(),
             QuantaLY8Temp5(),
             QuantaLY8Temp6(),
             QuantaLY8Temp7(),
             QuantaLY8Temp8(),
             QuantaLY8Temp9(),
             QuantaLY8Temp10(),
             QuantaLY8Temp11(),
             QuantaLY8Temp12(),
             QuantaLY8Temp13(),
             QuantaLY8Temp14(),
             )

class QuantaLY8PWMs():
    units = (QuantaLY8PWM1(),
             )

class QuantaLY8LEDs():
    units = (QuantaLY8PSU1LED(),
             QuantaLY8PSU2LED(),
             QuantaLY8FanLED(),
             )

class QuantaLY8SFPp(cumulus.platform.TridentTwo10GPort):
    _set_led = '''
;;; QuantaLY8SFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed should always be zero;
;;;
;;; 2nd bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
set_any_led:
set_led:
        port 1
        pushst PORTSTATUS_ZERO
        pack

        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        ret
'''
    def __init__(self, label, serdes, leds):
        cumulus.platform.TridentTwo10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 unit=0)

        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')
        self._serdes_intf_map = {10:'SFI'}

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, led_port)

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls


class QuantaLY8QSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; QuantaLY8QSFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed is always zero
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
set_led:
        call    set_any_led    ; set the first led green/off

        push    PORTSTATUS_ZERO ; 0, 0 => led 2 off
        pack
        push    PORTSTATUS_ZERO
        pack
        push    PORTSTATUS_ZERO ; 0, 0 => led 3 off
        pack
        push    PORTSTATUS_ZERO
        pack
        push    PORTSTATUS_ZERO ; 0, 0 => led 4 off
        pack
        push    PORTSTATUS_ZERO
        pack
        ret

'''

    _set_led_4x10 = '''
;;; QuantaLY8QSFPp_4x10
;;
;;  For 4x10G mode, we use an LED for each port.
;;
set_led:
        call    set_any_led
        inc     a
        call    set_any_led
        inc     a
        call    set_any_led
        inc     a
        call    set_any_led

        ret

'''
    def __init__(self, label, serdes, leds, phy_addrs, prim_offset,
                 phy_id1, sys_interface, phy_types):
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_addrs=phy_addrs,
                                                 phy_types=phy_types,
                                                 prim_offset=prim_offset,
                                                 phy_id1=phy_id1,
                                                 sys_interface=sys_interface,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')
        if (self.label == "53") or (self.label == "54"):
            self._serdes_intf_map = {40:'SR4'}

    @property
    def max_logical_ports(self):
        if (self.label == "53" or self.label == "54"):
            return 1
        else:
            return 4

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

class QuantaLY8LED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 128

class QuantaLY8Switch(cumulus.platform.BCMSwitch):
    ledup = QuantaLY8LED
    _sfp = QuantaLY8SFPp
    _qsfp = QuantaLY8QSFPp
    has_phy_ucode_mdio = False
    has_phy_ucode_spi_rom = False

    ports = (
        _sfp(label="1",  serdes=(24,), leds=(0, 4)),
        _sfp(label="2",  serdes=(25,), leds=(0, 6)),
        _sfp(label="3",  serdes=(26,), leds=(0, 8)),
        _sfp(label="4",  serdes=(27,), leds=(0, 10)),
        _sfp(label="5",  serdes=(28,), leds=(0, 12)),
        _sfp(label="6",  serdes=(29,), leds=(0, 14)),
        _sfp(label="7",  serdes=(30,), leds=(0, 16)),
        _sfp(label="8",  serdes=(31,), leds=(0, 18)),
        _sfp(label="9",  serdes=(44,), leds=(0, 44)),
        _sfp(label="10", serdes=(45,), leds=(0, 46)),
        _sfp(label="11", serdes=(46,), leds=(0, 48)),
        _sfp(label="12", serdes=(47,), leds=(0, 50)),
        _sfp(label="13", serdes=(48,), leds=(0, 52)),
        _sfp(label="14", serdes=(49,), leds=(0, 54)),
        _sfp(label="15", serdes=(50,), leds=(0, 56)),
        _sfp(label="16", serdes=(51,), leds=(0, 58)),
        _sfp(label="17", serdes=(52,), leds=(0, 60)),
        _sfp(label="18", serdes=(53,), leds=(0, 62)),
        _sfp(label="19", serdes=(54,), leds=(0, 64)),
        _sfp(label="20", serdes=(55,), leds=(0, 66)),
        _sfp(label="21", serdes=(56,), leds=(0, 68)),
        _sfp(label="22", serdes=(57,), leds=(0, 70)),
        _sfp(label="23", serdes=(58,), leds=(0, 72)),
        _sfp(label="24", serdes=(59,), leds=(0, 74)),

        _sfp(label="25", serdes=(76,), leds=(1, 108)),
        _sfp(label="26", serdes=(77,), leds=(1, 110)),
        _sfp(label="27", serdes=(78,), leds=(1, 112)),
        _sfp(label="28", serdes=(79,), leds=(1, 114)),
        _sfp(label="29", serdes=(80,), leds=(1, 116)),
        _sfp(label="30", serdes=(81,), leds=(1, 118)),
        _sfp(label="31", serdes=(82,), leds=(1, 120)),
        _sfp(label="32", serdes=(83,), leds=(1, 122)),

        _sfp(label="33", serdes=(96,), leds=(1, 20)),
        _sfp(label="34", serdes=(97,), leds=(1, 22)),
        _sfp(label="35", serdes=(98,), leds=(1, 24)),
        _sfp(label="36", serdes=(99,), leds=(1, 26)),
        _sfp(label="37", serdes=(100,), leds=(1,28)),
        _sfp(label="38", serdes=(101,), leds=(1,30)),
        _sfp(label="39", serdes=(102,), leds=(1,32)),
        _sfp(label="40", serdes=(103,), leds=(1,34)),
        _sfp(label="41", serdes=(104,), leds=(1,36)),
        _sfp(label="42", serdes=(105,), leds=(1,38)),
        _sfp(label="43", serdes=(106,), leds=(1,40)),
        _sfp(label="44", serdes=(107,), leds=(1,42)),
        _sfp(label="45", serdes=(108,), leds=(1,44)),
        _sfp(label="46", serdes=(109,), leds=(1,46)),
        _sfp(label="47", serdes=(110,), leds=(1,48)),
        _sfp(label="48", serdes=(111,), leds=(1,50)),

        _qsfp(label="49", serdes=(60, 61, 62, 63), leds=(0, 76),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="50", serdes=(64, 65, 66, 67), leds=(1, 84),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="51", serdes=(68, 69, 70, 71), leds=(1, 92),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="52", serdes=(72, 73, 74, 75), leds=(1, 100),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="53", serdes=(20, 21, 22, 23), leds=(0, 124),
              phy_addrs = (0x10, 0x11, 0x12, 0x13), prim_offset=0x3500, phy_id1=0x8500, sys_interface=9,
              phy_types = ("84328",) * 4),
        _qsfp(label="54", serdes=(12, 13, 14, 15), leds=(0, 108),
              phy_addrs = (0x14, 0x15, 0x16, 0x17), prim_offset=0x3600, phy_id1=0x8500, sys_interface=9,
              phy_types = ("84328",) * 4),
    )

class QuantaLY8(cumulus.platform.Platform):
    name = 'quanta,ly8_rangeley'
    switch = QuantaLY8Switch(cumulus.platform.TridentTwo_56854_Chip())
    pwms = QuantaLY8PWMs()
    sensors = QuantaLY8Sensors()
    statusleds = QuantaLY8LEDs()

### Quanta LY9Rangeley

# TODO: Sensors data needs to be updated. Awaiting data from Quanta.  
class QuantaLY9Rangeley_Fan(cumulus.sensors.Fan_Unit):
    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-004e'
                driver_path = os.path.join(pci_path, x, c)
                break

    fan_min = 11000
    fan_max = 24000
    rpmmode = 1

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '0':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class QuantaLY9RangeleyCoreTemp(cumulus.sensors.Temp_Unit):
    description = cumulus.sensors.Temp_Unit.intel_cpu_sensor_name
    driver_path = '/sys/devices/platform/coretemp.0'
    temp_max_hyst = 65
    temp_max = 90
    temp_crit = 98

class QuantaLY9RangeleyCY8Temp(cumulus.sensors.Temp_Unit):
    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-004e'
                driver_path = os.path.join(pci_path, x, c)
                break

    # This box runs hot with PHYs on it
    temp_max_hyst = 50
    temp_max = 68
    temp_crit = 73

class QuantaLY9RangeleyPSU(cumulus.sensors.PSU_Unit):
    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '0':
            self.attrs['psu_pwr1_present'] = 1
        else:
            self.attrs['psu_pwr1_present'] = 0
        if ((self.get_gpio_value(self.psu_ac_ok) == '0') and
            (self.get_gpio_value(self.psu_dc_ok) == '1')):
            self.attrs['psu_pwr1_all_ok'] = 1
        else:
            self.attrs['psu_pwr1_all_ok'] = 0
        return 0

class QuantaLY9RangeleyLED(cumulus.sensors.StatusLED_Unit):
    good_led_color = '1'  # Green
    bad_led_color = '0'   # Off

    def led_update(self, color):
        #print 'loc: %s color %s' %(self.led_location, color)
        self.set_gpio_value(self.led_location, color)

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        if color == '0':
            color = 'off'
        else:
            color = 'green'
        return self.name, color

class QuantaLY9RangeleyPSU1LED(QuantaLY9RangeleyLED):
    name = 'PSU1'
    led_location = 'psu1_green_led'
    sources = ['PSU1']

class QuantaLY9RangeleyPSU2LED(QuantaLY9RangeleyLED):
    name = 'PSU2'
    led_location = 'psu2_green_led'
    sources = ['PSU2']

class QuantaLY9RangeleyFanLED(QuantaLY9RangeleyLED):
    name = 'Fans'
    led_location = 'fan_green_led'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4', 'Fan5', 'Fan6']

class QuantaLY9RangeleyPSU1(QuantaLY9RangeleyPSU):
    name = 'PSU1'
    psu_present = 'psu_pwr1_present'
    psu_ac_ok = 'psu_pwr1_ac_ok'
    psu_dc_ok = 'psu_pwr1_dc_ok'

class QuantaLY9RangeleyPSU2(QuantaLY9RangeleyPSU):
    name = 'PSU2'
    psu_present = 'psu_pwr2_present'
    psu_ac_ok = 'psu_pwr2_ac_ok'
    psu_dc_ok = 'psu_pwr2_dc_ok'

class QuantaLY9RangeleyFan1(QuantaLY9Rangeley_Fan):
    fan_present = 'fan1_present'
    name = 'Fan1'
    description = 'Fan Tray 1'
    driver_hwmon = ['fan1']

class QuantaLY9RangeleyFan2(QuantaLY9Rangeley_Fan):
    fan_present = 'fan1_present'
    name = 'Fan2'
    description = 'Fan Tray 1'
    driver_hwmon = ['fan5']

class QuantaLY9RangeleyFan3(QuantaLY9Rangeley_Fan):
    fan_present = 'fan2_present'
    name = 'Fan3'
    description = 'Fan Tray 2'
    driver_hwmon = ['fan2']

class QuantaLY9RangeleyFan4(QuantaLY9Rangeley_Fan):
    fan_present = 'fan2_present'
    name = 'Fan4'
    description = 'Fan Tray 2'
    driver_hwmon = ['fan6']

class QuantaLY9RangeleyFan5(QuantaLY9Rangeley_Fan):
    fan_present = 'fan3_present'
    name = 'Fan5'
    description = 'Fan Tray 3'
    driver_hwmon = ['fan3']

class QuantaLY9RangeleyFan6(QuantaLY9Rangeley_Fan):
    fan_present = 'fan3_present'
    name = 'Fan6'
    description = 'Fan Tray 3'
    driver_hwmon = ['fan7']

class QuantaLY9RangeleyTemp1(QuantaLY9RangeleyCoreTemp):
    name = 'Temp1'
    driver_hwmon = ['temp2']

class QuantaLY9RangeleyTemp2(QuantaLY9RangeleyCoreTemp):
    name = 'Temp2'
    driver_hwmon = ['temp3']

class QuantaLY9RangeleyTemp3(QuantaLY9RangeleyCoreTemp):
    name = 'Temp3'
    driver_hwmon = ['temp4']

class QuantaLY9RangeleyTemp4(QuantaLY9RangeleyCoreTemp):
    name = 'Temp4'
    driver_hwmon = ['temp5']

class QuantaLY9RangeleyTemp5(QuantaLY9RangeleyCoreTemp):
    name = 'Temp5'
    driver_hwmon = ['temp6']

class QuantaLY9RangeleyTemp6(QuantaLY9RangeleyCoreTemp):
    name = 'Temp6'
    driver_hwmon = ['temp7']

class QuantaLY9RangeleyTemp7(QuantaLY9RangeleyCoreTemp):
    name = 'Temp7'
    driver_hwmon = ['temp8']

class QuantaLY9RangeleyTemp8(QuantaLY9RangeleyCoreTemp):
    name = 'Temp8'
    driver_hwmon = ['temp9']

class QuantaLY9RangeleyTemp9(QuantaLY9RangeleyCY8Temp):
    name = 'Temp9'
    driver_hwmon = ['temp1']
    description = 'Right Front Outlet Temp sensor'

class QuantaLY9RangeleyTemp10(QuantaLY9RangeleyCY8Temp):
    name = 'Temp10'
    driver_hwmon = ['temp2']
    description = 'Middle Front Outlet Temp sensor'
    # Located near the PHYs
    temp_max_hyst = 72
    temp_max = 82
    temp_crit = 90

class QuantaLY9RangeleyTemp11(QuantaLY9RangeleyCY8Temp):
    name = 'Temp11'
    driver_hwmon = ['temp3']
    description = 'Left Front Outlet Temp sensor'
    # Located near the PHYs
    temp_max_hyst = 72
    temp_max = 82
    temp_crit = 90

class QuantaLY9RangeleyTemp12(QuantaLY9RangeleyCY8Temp):
    name = 'Temp12'
    driver_hwmon = ['temp4']
    description = "Rear Outlet Temp Sensor"

class QuantaLY9RangeleyTemp13(QuantaLY9RangeleyCY8Temp):
    name = 'Temp13'
    driver_hwmon = ['temp5']
    description = 'CPU Board Temp sensor'

class QuantaLY9RangeleyTemp14(QuantaLY9RangeleyCY8Temp):
    name = 'Temp14'
    driver_hwmon = ['temp6']
    description = 'CPU Board Temp sensor'

class QuantaLY9RangeleyTemp15(cumulus.sensors.Temp_Unit):
    name = 'Temp15'
    description = cumulus.sensors.Temp_Unit.dimm_sensor_name
    driver_hwmon = ['temp1']
    temp_max_hyst = 65
    temp_max = 90
    temp_crit = 95

    driver_path = ''
    pci_path = '/sys/devices/pci0000:00/0000:00:1f.3'
    if os.path.exists(pci_path):
        for x in os.listdir(pci_path):
            if x.startswith('i2c-'):
                a,b = x.split('-')
                c = b + '-001a'
                driver_path = os.path.join(pci_path, x, c)
                break

class QuantaLY9RangeleySensors():
    units = (QuantaLY9RangeleyTemp1(),
             QuantaLY9RangeleyTemp2(),
             QuantaLY9RangeleyTemp3(),
             QuantaLY9RangeleyTemp4(),
             QuantaLY9RangeleyTemp5(),
             QuantaLY9RangeleyTemp6(),
             QuantaLY9RangeleyTemp7(),
             QuantaLY9RangeleyTemp8(),
             QuantaLY9RangeleyTemp9(),
             QuantaLY9RangeleyTemp10(),
             QuantaLY9RangeleyTemp11(),
             QuantaLY9RangeleyTemp12(),
             QuantaLY9RangeleyTemp13(),
             QuantaLY9RangeleyTemp14(),
             QuantaLY9RangeleyTemp15(),
             QuantaLY9RangeleyFan1(),
             QuantaLY9RangeleyFan2(),
             QuantaLY9RangeleyFan3(),
             QuantaLY9RangeleyFan4(),
             QuantaLY9RangeleyFan5(),
             QuantaLY9RangeleyFan6(),
             QuantaLY9RangeleyPSU1(),
             QuantaLY9RangeleyPSU2(),
             )

class QuantaLY9RangeleyPWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (QuantaLY9RangeleyFan1(),
            QuantaLY9RangeleyFan2(),
            QuantaLY9RangeleyFan3(),
            QuantaLY9RangeleyFan4(),
            QuantaLY9RangeleyFan5(),
            QuantaLY9RangeleyFan6(),
            )
    temps = (QuantaLY9RangeleyTemp1(),
             QuantaLY9RangeleyTemp2(),
             QuantaLY9RangeleyTemp3(),
             QuantaLY9RangeleyTemp4(),
             QuantaLY9RangeleyTemp5(),
             QuantaLY9RangeleyTemp6(),
             QuantaLY9RangeleyTemp7(),
             QuantaLY9RangeleyTemp8(),
             QuantaLY9RangeleyTemp9(),
             QuantaLY9RangeleyTemp10(),
             QuantaLY9RangeleyTemp11(),
             QuantaLY9RangeleyTemp12(),
             QuantaLY9RangeleyTemp13(),
             QuantaLY9RangeleyTemp14(),
             QuantaLY9RangeleyTemp15(),
             )

class QuantaLY9RangeleyPWMs():
    units = (QuantaLY9RangeleyPWM1(),
             )

class QuantaLY9RangeleyLEDs():
    units = (QuantaLY9RangeleyPSU1LED(),
             QuantaLY9RangeleyPSU2LED(),
             QuantaLY9RangeleyFanLED(),
             )

class QuantaLY9Rangeley10GT(cumulus.platform.TridentTwo10GPort):
    _set_led = '''
;;; QuantaLY9Rangeley10GT
;;;
;;; 2 bits per port. Since leds are set by PHY, pack anything.
;;;
set_led:
        port 1
        pushst PORTSTATUS_ZERO
        pack
        port 1
        pushst PORTSTATUS_ZERO
        pack

        ret
'''
    def __init__(self, label, serdes, phy_addrs, leds):
        cumulus.platform.TridentTwo10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=("84848",),
                                                 phy_addrs=phy_addrs,
                                                 phy_layer='10GBaseT',
                                                 leds=leds,
                                                 unit=0)

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        for led in range(self.num_physical_ports(mode)):
            set_calls[self.leds[1] + led] = call

        return set_calls

class QuantaLY9RangeleyQSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; QuantaLY9RangeleyQSFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed is always zero
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
;;; QuantaLY9Rangeley10GT
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed should always be zero;
;;;
;;; 2nd bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
set_any_led:
        port 1
        pushst PORTSTATUS_ZERO
        pack

        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        ret

set_led:
    	call set_any_led

        push    PORTSTATUS_ZERO
        pack
        push    PORTSTATUS_ZERO ; 0, 0 => led 2 off
        pack
        push    PORTSTATUS_ZERO
        pack
        push    PORTSTATUS_ZERO ; 0, 0 => led 3 off
        pack
        push    PORTSTATUS_ZERO
        pack
        push    PORTSTATUS_ZERO ; 0, 0 => led 4 off
        pack

        ret

'''

    _set_led_4x10 = '''
;;; QuantaLY9RangeleyQSFPp_4x10
;;
;;  For 4x10G mode, we use an LED for each port.
;;
set_led:
        call    set_any_led
        inc     a
        call    set_any_led
        inc     a
        call    set_any_led
        inc     a
        call    set_any_led

        ret

'''
    def __init__(self, label, serdes, leds, phy_addrs, prim_offset,
                 phy_id1, sys_interface, phy_types):
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_addrs=phy_addrs,
                                                 phy_types=phy_types,
                                                 prim_offset=prim_offset,
                                                 phy_id1=phy_id1,
                                                 sys_interface=sys_interface,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')
        if (self.label == "53") or (self.label == "54"):
            self._serdes_intf_map = {40:'SR4'}

    @property
    def max_logical_ports(self):
        if (self.label == "53" or self.label == "54"):
            return 1
        else:
            return 4

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

class QuantaLY9RangeleyLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 128

class QuantaLY9RangeleySwitch(cumulus.platform.BCMSwitch):
    ledup = QuantaLY9RangeleyLED
    _10GT = QuantaLY9Rangeley10GT
    _qsfp = QuantaLY9RangeleyQSFPp
    has_phy_ucode_spi_rom = False
    has_phy_ucode_mdio = True

    ports = (
        _10GT(label="1",   serdes=(25,),  phy_addrs=(0x22,),  leds=(0, 0)),
        _10GT(label="2",   serdes=(24,),  phy_addrs=(0x21,),  leds=(0, 0)),
        _10GT(label="3",   serdes=(27,),  phy_addrs=(0x24,),  leds=(0, 0)),        
        _10GT(label="4",   serdes=(26,),  phy_addrs=(0x23,),  leds=(0, 0)),

        _10GT(label="5",   serdes=(29,),  phy_addrs=(0x26,),  leds=(0, 0)),
        _10GT(label="6",   serdes=(28,),  phy_addrs=(0x25,),  leds=(0, 0)),
        _10GT(label="7",   serdes=(31,),  phy_addrs=(0x28,),  leds=(0, 0)),
        _10GT(label="8",   serdes=(30,),  phy_addrs=(0x27,),  leds=(0, 0)),

        _10GT(label="9",   serdes=(45,),  phy_addrs=(0x2a,),  leds=(0, 0)),        
        _10GT(label="10",  serdes=(44,),  phy_addrs=(0x29,),  leds=(0, 0)),
        _10GT(label="11",  serdes=(47,),  phy_addrs=(0x2c,),  leds=(0, 0)),
        _10GT(label="12",  serdes=(46,),  phy_addrs=(0x2b,),  leds=(0, 0)),

        _10GT(label="13",  serdes=(49,),  phy_addrs=(0x2e,),  leds=(0, 0)),
        _10GT(label="14",  serdes=(48,),  phy_addrs=(0x2d,),  leds=(0, 0)),
        _10GT(label="15",  serdes=(51,),  phy_addrs=(0x30,),  leds=(0, 0)),        
        _10GT(label="16",  serdes=(50,),  phy_addrs=(0x2f,),  leds=(0, 0)),

        _10GT(label="17",  serdes=(53,),  phy_addrs=(0x32,),  leds=(0, 0)),
        _10GT(label="18",  serdes=(52,),  phy_addrs=(0x31,),  leds=(0, 0)),
        _10GT(label="19",  serdes=(55,),  phy_addrs=(0x34,),  leds=(0, 0)),        
        _10GT(label="20",  serdes=(54,),  phy_addrs=(0x33,),  leds=(0, 0)),

        _10GT(label="21",  serdes=(57,),  phy_addrs=(0x36,),  leds=(0, 0)),        
        _10GT(label="22",  serdes=(56,),  phy_addrs=(0x35,),  leds=(0, 0)),
        _10GT(label="23",  serdes=(59,),  phy_addrs=(0x38,),  leds=(0, 0)),
        _10GT(label="24",  serdes=(58,),  phy_addrs=(0x37,),  leds=(0, 0)),

        _10GT(label="25",  serdes=(61,),  phy_addrs=(0x42,),  leds=(0, 0)),        
        _10GT(label="26",  serdes=(60,),  phy_addrs=(0x41,),  leds=(0, 0)),
        _10GT(label="27",  serdes=(63,),  phy_addrs=(0x44,),  leds=(0, 0)),        
        _10GT(label="28",  serdes=(62,),  phy_addrs=(0x43,),  leds=(0, 0)),

        _10GT(label="29",  serdes=(65,),  phy_addrs=(0x46,),  leds=(1, 0)),
        _10GT(label="30",  serdes=(64,),  phy_addrs=(0x45,),  leds=(1, 0)),
        _10GT(label="31",  serdes=(67,),  phy_addrs=(0x48,),  leds=(1, 0)),        
        _10GT(label="32",  serdes=(66,),  phy_addrs=(0x47,),  leds=(1, 0)),

        _10GT(label="33",  serdes=(69,),  phy_addrs=(0x4a,),  leds=(1, 0)),        
        _10GT(label="34",  serdes=(68,),  phy_addrs=(0x49,),  leds=(1, 0)),
        _10GT(label="35",  serdes=(71,),  phy_addrs=(0x4c,),  leds=(1, 0)),
        _10GT(label="36",  serdes=(70,),  phy_addrs=(0x4b,),  leds=(1, 0)),

        _10GT(label="37",  serdes=(73,),  phy_addrs=(0x4e,),  leds=(1, 0)),        
        _10GT(label="38",  serdes=(72,),  phy_addrs=(0x4d,),  leds=(1, 0)),
        _10GT(label="39",  serdes=(75,),  phy_addrs=(0x50,),  leds=(1, 0)),
        _10GT(label="40",  serdes=(74,),  phy_addrs=(0x4f,),  leds=(1, 0)),

        _10GT(label="41",  serdes=(77,),  phy_addrs=(0x52,),  leds=(1, 0)),        
        _10GT(label="42",  serdes=(76,),  phy_addrs=(0x51,),  leds=(1, 0)),
        _10GT(label="43",  serdes=(79,),  phy_addrs=(0x54,),  leds=(1, 0)),        
        _10GT(label="44",  serdes=(78,),  phy_addrs=(0x53,),  leds=(1, 0)),

        _10GT(label="45",  serdes=(81,),  phy_addrs=(0x56,),  leds=(1, 0)),
        _10GT(label="46",  serdes=(80,),  phy_addrs=(0x55,),  leds=(1, 0)),
        _10GT(label="47",  serdes=(83,),  phy_addrs=(0x58,),  leds=(1, 0)),        
        _10GT(label="48",  serdes=(82,),  phy_addrs=(0x57,),  leds=(1, 0)),

        _qsfp(label="49", serdes=(96, 97, 98, 99), leds=(1, 19),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="50", serdes=(100, 101, 102, 103), leds=(1, 23),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="51", serdes=(104, 105, 106, 107), leds=(1, 27),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="52", serdes=(108, 109, 110, 111), leds=(1, 31),
              phy_addrs=None, prim_offset=None, phy_id1=None, sys_interface=None, phy_types=None),
        _qsfp(label="53", serdes=(20, 21, 22, 23), leds=(0, 107),
              phy_addrs = (0x14, 0x15, 0x16, 0x17), prim_offset=0x3600, phy_id1=0x8500, sys_interface=9,
              phy_types = ("84328",) * 4),
        _qsfp(label="54", serdes=(12, 13, 14, 15), leds=(0, 123),
              phy_addrs = (0x10, 0x11, 0x12, 0x13), prim_offset=0x3500, phy_id1=0x8500, sys_interface=9,
              phy_types = ("84328",) * 4),
    )

class QuantaLY9Rangeley(cumulus.platform.Platform):
    name = 'quanta,ly9_rangeley'
    switch = QuantaLY9RangeleySwitch(cumulus.platform.TridentTwo_56854_Chip())
    pwms = QuantaLY9RangeleyPWMs()
    sensors = QuantaLY9RangeleySensors()
    statusleds = QuantaLY9RangeleyLEDs()
