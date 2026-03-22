#
# Copyright 2012.  Cumulus Networks, Inc.
#
# accton.py --
#     Accton platform data.
#

import cumulus.cpld
import cumulus.platform
import cumulus.ledup
import cumulus.sunit
import cumulus.sfp
import cumulus.sensors
import os
import subprocess

##
## Accton 5652 Section -- Trident based.  48x10G, 4x40G
##

class Accton5652QSFPp(cumulus.platform.Trident40GPort):
    def __init__(self, label, serdes, phy_addrs, leds):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=("84740",) * 4,
                                                 phy_addrs=phy_addrs,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')
    _set_led = '''
;;; Accton5652SFPp
;;;
;;; XXX - this is wrong for subdivided ports, need to OR all four ports together
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed on stack controls amber LED:
;;; 0 - off
;;; 1 - on
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
;;; We will only use green LED.  1st bit pushed is always zero to
;;; disable amber LED.
set_led:
        port 1
        pushst  PORTSTATUS_ZERO ; disable amber LED
        pack

        port    a
        ld      b,LINKSCAN_P
        add     b,a
        ld      b,(b)
        tst     b,LINKSCAN_TX
        push    cy
        tst     b,LINKSCAN_RX
        push    cy
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
;;;   register B[0] - activity (TX _OR_ RX)
;;;   register B[1] - link enabled

SUB_INTF_ACTIVITY	equ	0x0  ; activity
SUB_INTF_LINKEN		equ	0x1  ; link enabled

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

;;; AcctonAS5652QSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
        pack

        ;;; initialize B
        ld	b,0

        ;;; load sub-0 info
        call	sub_intf_info

        ;;; load sub-1 info
        inc	a
        call	sub_intf_info

        ;;; load sub-2 info
        inc	a
        call	sub_intf_info

        ;;; load sub-3 info
        inc	a
        call	sub_intf_info

        ;;; push accumlated link activity onto stack
        tst	B, SUB_INTF_ACTIVITY
        push	cy

        ;;; combine with BLINK state
        push	(BLINK_STATE_P)
        tand
        tinv	; flash off with activity

        ;;; push accumlated link enable onto stack
        tst	B, SUB_INTF_LINKEN
        push	cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand

        pack

        ret
'''
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

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None


        return set_calls


class Accton5652SFPp(cumulus.platform.Trident10GPort):
    _set_led = '''
;;; Accton5652SFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed on stack controls amber LED:
;;; 0 - off
;;; 1 - on
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
;;; We will only use green LED.  1st bit pushed is always zero to
;;; disable amber LED.
set_led:
        port 1
        pushst  PORTSTATUS_ZERO ; disable amber LED
        pack

        port    a
        ld      b,LINKSCAN_P
        add     b,a
        ld      b,(b)
        tst     b,LINKSCAN_TX
        push    cy
        tst     b,LINKSCAN_RX
        push    cy
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack

        ret
'''

    def __init__(self, label, serdes, phy_addr, leds):
        cumulus.platform.Trident10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_type="84754",
                                                 phy_addr=phy_addr,
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

class Accton5652CPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ff705000.localbus/ea000000.cpld'

class Accton5652LED(cumulus.ledup.TridentLEDController):
    num_leds = 52

class Accton5652Switch(cumulus.platform.BCMSwitch):
    ledup = Accton5652LED
    _sfp = Accton5652SFPp
    _qsfp = Accton5652QSFPp
    has_phy_ucode_mdio = True
    # This board does not have SPI-ROMs.
    has_phy_ucode_spi_rom = False
    ports = (
        _sfp(label="1",  serdes=64, phy_addr=0x00, leds=(1, 14)),
        _sfp(label="2",  serdes=65, phy_addr=0x01, leds=(1, 12)),
        _sfp(label="3",  serdes=66, phy_addr=0x02, leds=(1, 10)),
        _sfp(label="4",  serdes=67, phy_addr=0x03, leds=(1, 8)),
        _sfp(label="5",  serdes=8,  phy_addr=0x04, leds=(0, 42)),
        _sfp(label="6",  serdes=9,  phy_addr=0x05, leds=(0, 40)),
        _sfp(label="7",  serdes=10, phy_addr=0x06, leds=(0, 38)),
        _sfp(label="8",  serdes=11, phy_addr=0x07, leds=(0, 36)),
        _sfp(label="9",  serdes=60, phy_addr=0x08, leds=(1, 22)),
        _sfp(label="10", serdes=61, phy_addr=0x09, leds=(1, 20)),
        _sfp(label="11", serdes=62, phy_addr=0x0a, leds=(1, 18)),
        _sfp(label="12", serdes=63, phy_addr=0x0b, leds=(1, 16)),
        _sfp(label="13", serdes=68, phy_addr=0x0c, leds=(1, 6)),
        _sfp(label="14", serdes=69, phy_addr=0x0d, leds=(1, 4)),
        _sfp(label="15", serdes=70, phy_addr=0x0e, leds=(1, 2)),
        _sfp(label="16", serdes=71, phy_addr=0x0f, leds=(1, 0)),
        _sfp(label="17", serdes=12, phy_addr=0x10, leds=(0, 34)),
        _sfp(label="18", serdes=13, phy_addr=0x11, leds=(0, 32)),
        _sfp(label="19", serdes=14, phy_addr=0x12, leds=(0, 30)),
        _sfp(label="20", serdes=15, phy_addr=0x13, leds=(0, 28)),
        _sfp(label="21", serdes=4,  phy_addr=0x34, leds=(0, 50)),
        _sfp(label="22", serdes=5,  phy_addr=0x35, leds=(0, 48)),
        _sfp(label="23", serdes=6,  phy_addr=0x36, leds=(0, 46)),
        _sfp(label="24", serdes=7,  phy_addr=0x37, leds=(0, 44)),
        _sfp(label="25", serdes=16, phy_addr=0x38, leds=(0, 26)),
        _sfp(label="26", serdes=17, phy_addr=0x39, leds=(0, 24)),
        _sfp(label="27", serdes=18, phy_addr=0x3a, leds=(0, 22)),
        _sfp(label="28", serdes=19, phy_addr=0x3b, leds=(0, 20)),
        _sfp(label="29", serdes=20, phy_addr=0x3c, leds=(0, 18)),
        _sfp(label="30", serdes=21, phy_addr=0x3d, leds=(0, 16)),
        _sfp(label="31", serdes=22, phy_addr=0x3e, leds=(0, 14)),
        _sfp(label="32", serdes=23, phy_addr=0x3f, leds=(0, 12)),
        _sfp(label="33", serdes=40, phy_addr=0x20, leds=(1, 48)),
        _sfp(label="34", serdes=41, phy_addr=0x21, leds=(1, 46)),
        _sfp(label="35", serdes=42, phy_addr=0x22, leds=(1, 44)),
        _sfp(label="36", serdes=43, phy_addr=0x23, leds=(1, 42)),
        _sfp(label="37", serdes=24, phy_addr=0x24, leds=(0, 10)),
        _sfp(label="38", serdes=25, phy_addr=0x25, leds=(0, 8)),
        _sfp(label="39", serdes=26, phy_addr=0x26, leds=(0, 6)),
        _sfp(label="40", serdes=27, phy_addr=0x27, leds=(0, 4)),
        _sfp(label="41", serdes=48, phy_addr=0x48, leds=(1, 32)),
        _sfp(label="42", serdes=49, phy_addr=0x49, leds=(1, 30)),
        _sfp(label="43", serdes=50, phy_addr=0x4a, leds=(1, 28)),
        _sfp(label="44", serdes=51, phy_addr=0x4b, leds=(1, 26)),
        _sfp(label="45", serdes=44, phy_addr=0x4c, leds=(1, 40)),
        _sfp(label="46", serdes=45, phy_addr=0x4d, leds=(1, 38)),
        _sfp(label="47", serdes=46, phy_addr=0x4e, leds=(1, 36)),
        _sfp(label="48", serdes=47, phy_addr=0x4f, leds=(1, 34)),

        _qsfp(label="49", serdes=(36,37,38,39), phy_addrs=(0x54,0x55,0x56,0x57),
              leds=(1, 50)),
        _qsfp(label="50", serdes=(28,29,30,31), phy_addrs=(0x50,0x51,0x52,0x53),
              leds=(0, 2)),
        _qsfp(label="51", serdes=(56,57,58,59), phy_addrs=(0x5c,0x5d,0x5e,0x5f),
              leds=(1, 24)),
        _qsfp(label="52", serdes=(32,33,34,35), phy_addrs=(0x58,0x59,0x5a,0x5b),
              leds=(0, 0)),
    )


class Accton5652Board(cumulus.sensors.Board_Unit):
    name = 'Board'
    cpld_hwmon = ['system']

class Accton5652PSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class Accton5652PSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

Accton5652_9_29_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0029'
Accton5652_9_18_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0018'
Accton5652_9_1a_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-001a'
Accton5652_9_4c_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-004c'
Accton5652_pci_0100_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'

# Temp sensor parameters provided by Accton seem conservative. In our lab and
# at customer sites, we see that fans are running at full speed for normal operation.
# Collecting some temperature sensor data from our lab at normal operation, this box
# just runs at a higher temperature than other boxes, and running the fan at full speed,
# doesnt seem to change much. Hence raising the limits for all sensors. (CM-4335)
class Accton5652Temp(cumulus.sensors.Temp_Unit):
    temp_max_hyst = 57
    temp_max = 77
    temp_crit = 90

    def __init__(self):
        self.name =  (self.__class__.__name__[10:])
        cumulus.sensors.Temp_Unit.__init__(self)

# Temp values added below are an approximation to the values
# provided by Accton. They have 2 models: B2F and F2B. I have taken
# the average of the values provided and avoided the extremes.
class Accton5652Temp1(Accton5652Temp):
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = Accton5652_pci_0100_path
    temp_max_hyst = 65
    temp_max = 100
    temp_crit = 105

class Accton5652Temp2(Accton5652Temp):
    description = 'Near the CPU (Right)'
    driver_path = Accton5652_9_29_path

class Accton5652Temp3(Accton5652Temp):
    description = 'Top right corner'
    driver_path = Accton5652_9_29_path
    driver_hwmon = ['temp2']

class Accton5652Temp4(Accton5652Temp):
    description = 'Right side of Networking ASIC'
    driver_path = Accton5652_9_29_path
    driver_hwmon = ['temp3']

class Accton5652Temp5(Accton5652Temp):
    description = 'Middle of the board'
    driver_path = Accton5652_9_18_path

class Accton5652Temp6(Accton5652Temp):
    description = cumulus.sensors.Temp_Unit.p2020_cpu_sensor_name
    driver_path = Accton5652_9_18_path
    driver_hwmon = ['temp2']
    temp_max_hyst = 65
    temp_max = 100
    #P2020 (Tj) Temperature Operating range is 0-125 C
    temp_crit = 120

class Accton5652Temp7(Accton5652Temp):
    description = 'Left side of the board'
    driver_path = Accton5652_9_1a_path

class Accton5652Temp8(Accton5652Temp):
    description = 'Left side of the board'
    driver_path = Accton5652_9_1a_path
    driver_hwmon = ['temp2']

class Accton5652Temp9(Accton5652Temp):
    description = 'Right side of the board'
    driver_path = Accton5652_9_4c_path

class Accton5652Temp10(Accton5652Temp):
    description = 'Right side of the board'
    driver_path = Accton5652_9_4c_path
    driver_hwmon = ['temp2']

class Accton5652Fan(cumulus.sensors.Fan_Unit):
    name = 'Fan'
    cpld_hwmon = ['system_fan']
    pwm_path = Accton5652_9_29_path

class Accton5652Sensors():
    units = ( Accton5652Board(),
              Accton5652PSU1(),
              Accton5652PSU2(),
              Accton5652Temp1(),
              Accton5652Temp2(),
              Accton5652Temp3(),
              Accton5652Temp4(),
              Accton5652Temp5(),
              Accton5652Temp6(),
              Accton5652Temp7(),
              Accton5652Temp8(),
              Accton5652Temp9(),
              Accton5652Temp10(),
              Accton5652Fan(),
              )
class Accton5652PWM1(cumulus.sensors.PWM_Unit):
    fans = (Accton5652Fan(),
            )
    temps = ( Accton5652Temp1(),
              Accton5652Temp2(),
              Accton5652Temp3(),
              Accton5652Temp4(),
              Accton5652Temp5(),
              Accton5652Temp6(),
              Accton5652Temp7(),
              Accton5652Temp8(),
              Accton5652Temp9(),
              Accton5652Temp10(),
              )

class Accton5652PWMs():
    units = (Accton5652PWM1(),
             )

class Accton5652PSU1LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'led_psu1'

class Accton5652PSU2LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'led_psu2'

class Accton5652FanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan'
    sources = ['Fan']
    led_location = 'led_fan'

class Accton5652SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_diag'

class Accton5652LEDs():
    units = (Accton5652PSU1LED(),
             Accton5652PSU2LED(),
             Accton5652FanLED(),
             Accton5652SystemLED(),
             )

class Accton5652(cumulus.platform.Platform):
    name = 'accton,es5652bt1'
    cpld = Accton5652CPLD()
    switch = Accton5652Switch(cumulus.platform.TridentChip())
    sensors = Accton5652Sensors()
    pwms = Accton5652PWMs()
    statusleds = Accton5652LEDs()
##
## Accton 4654
##

class Accton4654SFPp(cumulus.platform.Apollo10GPort):
    def __init__(self, label, hw_port, phy_addr, leds):
        cumulus.platform.Apollo10GPort.__init__(self,
                                                label=label,
                                                hw_port=hw_port,
                                                phy_type="84754",
                                                phy_addr=phy_addr,
                                                phy_layer='SFP+',
                                                leds=leds,
                                                unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')
    # one LED per port, two bits per LED:
    #   0, 1 -> green
    #   1, 0 -> orange
    _set_leds = '''
; Accton4654SFPp - activity
set_led:
        port a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX    ;; This bit indicates linkup
        tor
        tinv    ; active zero
        pack

        pushst  PORTSTATUS_ONE
        pack

        ret
    '''
    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call_set_leds = (fn_name, self._set_leds, self.led_port_num(mode, 0))
        set_calls[led_index_list[0]] = call_set_leds
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class Accton4654LED0(cumulus.ledup.TriumphLEDController):
    num_leds = 48*4

class Accton4654LED1(cumulus.ledup.TriumphLEDController):
    num_leds = 12*2

class Accton4654GigE(cumulus.platform.Apollo1GPort):
    def __init__(self, label, hw_port, phy_addr, prim_offset, leds=None):
        cumulus.platform.Apollo1GPort.__init__(self,
                                               label=label,
                                               hw_port=hw_port,
                                               phy_type="54280",
                                               phy_addr=phy_addr,
                                               prim_offset=prim_offset,
                                               leds=leds,
                                               unit=0)
    # two LEDs per port, two bits per LED:
    #   left
    #   0, 1 -> green
    #   1, 0 -> orange
    #
    #   right
    #   0, 1 -> green
    #   1, 0 -> orange
    _set_leds = '''
; Accton4654GigE - link/activity
set_led:
        port a

        pushst  PORTSTATUS_ONE
        pack

        pushst  PORTSTATUS_LINKEN
        tinv    ; active low
        pack

        pushst  PORTSTATUS_ONE
        pack

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        tinv    ; active low
        pack

        ret
    '''
    _set_leds_orange = '''
; Accton4654GigE - link/activity
set_led:
        port 1

        pushst  PORTSTATUS_ZERO
        pack
        pushst  PORTSTATUS_ONE
        pack
        pushst  PORTSTATUS_ZERO
        pack
        pushst  PORTSTATUS_ONE
        pack

        ret
    '''
    _set_leds_green = '''
; Accton4654GigE - link/activity
set_led:
        port 1

        pushst  PORTSTATUS_ONE
        pack
        pushst  PORTSTATUS_ZERO
        pack
        pushst  PORTSTATUS_ONE
        pack
        pushst  PORTSTATUS_ZERO
        pack

        ret
    '''
    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        led_index = led_index_list[0]
        fn_name = '%s' % self.__class__.__name__
#	fn_name = fn_name + '_swp' + self.label + '_phy0x%x' % self.phy_addrs[0] + '_' + self.hw_ports[0]
#        set_calls[led_index_list] = ('orange', self._set_leds_orange, None)
        set_calls[led_index] = (fn_name, self._set_leds, self.led_port_num(mode, 0))
        set_calls[led_index + 1] = None
        set_calls[led_index + 2] = None
        set_calls[led_index + 3] = None


#	for x in range(0*4, 48*4, 4):
#            set_calls[x] = ('green', self._set_leds_green, None)
#            set_calls[x + 1] = None
#            set_calls[x + 2] = None
#            set_calls[x + 3] = None
#
#        import os
#        set_calls[int(os.getenv('FOO'))*4] = ('orange', self._set_leds_orange, None)

        return set_calls

class Accton4654CPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ff705000.localbus/ea000000.cpld'

class Accton4654Switch(cumulus.platform.BCMSwitch):
    ledup = (Accton4654LED0, Accton4654LED1)
    _gige = Accton4654GigE
    _sfp = Accton4654SFPp
    has_phy_ucode_mdio = True
    has_phy_ucode_spi_rom = False

    ports = (
        _gige(label="1",  hw_port='ge1',  phy_addr=0x2,  prim_offset=0x0101, leds=(0, 6*4)),
        _gige(label="2",  hw_port='ge0',  phy_addr=0x1,  prim_offset=0x0100, leds=(0, 7*4)),
        _gige(label="3",  hw_port='ge3',  phy_addr=0x4,  prim_offset=0x0103, leds=(0, 4*4)),
        _gige(label="4",  hw_port='ge2',  phy_addr=0x3,  prim_offset=0x0102, leds=(0, 5*4)),
        _gige(label="5",  hw_port='ge5',  phy_addr=0x6,  prim_offset=0x0105, leds=(0, 2*4)),
        _gige(label="6",  hw_port='ge4',  phy_addr=0x5,  prim_offset=0x0104, leds=(0, 3*4)),
        _gige(label="7",  hw_port='ge7',  phy_addr=0x8,  prim_offset=0x0107, leds=(0, 0*4)),
        _gige(label="8",  hw_port='ge6',  phy_addr=0x7,  prim_offset=0x0106, leds=(0, 1*4)),
        _gige(label="9",  hw_port='ge33', phy_addr=0xa,  prim_offset=0x0901, leds=(0, 14*4)),
        _gige(label="10", hw_port='ge32', phy_addr=0x9,  prim_offset=0x0900, leds=(0, 15*4)),
        _gige(label="11", hw_port='ge35', phy_addr=0xc,  prim_offset=0x0903, leds=(0, 12*4)),
        _gige(label="12", hw_port='ge34', phy_addr=0xb,  prim_offset=0x0902, leds=(0, 13*4)),
        _gige(label="13", hw_port='ge37', phy_addr=0xe,  prim_offset=0x0905, leds=(0, 10*4)),
        _gige(label="14", hw_port='ge36', phy_addr=0xd,  prim_offset=0x0904, leds=(0, 11*4)),
        _gige(label="15", hw_port='ge39', phy_addr=0x10, prim_offset=0x0907, leds=(0, 8*4)),
        _gige(label="16", hw_port='ge38', phy_addr=0xf,  prim_offset=0x0906, leds=(0, 9*4)),
        _gige(label="17", hw_port='ge41', phy_addr=0x12, prim_offset=0x1101, leds=(0, 22*4)),
        _gige(label="18", hw_port='ge40', phy_addr=0x11, prim_offset=0x1100, leds=(0, 23*4)),
        _gige(label="19", hw_port='ge43', phy_addr=0x14, prim_offset=0x1103, leds=(0, 20*4)),
        _gige(label="20", hw_port='ge42', phy_addr=0x13, prim_offset=0x1102, leds=(0, 21*4)),
        _gige(label="21", hw_port='ge45', phy_addr=0x16, prim_offset=0x1105, leds=(0, 18*4)),
        _gige(label="22", hw_port='ge44', phy_addr=0x15, prim_offset=0x1104, leds=(0, 19*4)),
        _gige(label="23", hw_port='ge47', phy_addr=0x18, prim_offset=0x1107, leds=(0, 16*4)),
        _gige(label="24", hw_port='ge46', phy_addr=0x17, prim_offset=0x1106, leds=(0, 17*4)),
        _gige(label="25", hw_port='ge9' , phy_addr=0x22, prim_offset=0x2101, leds=(0, 30*4)),
        _gige(label="26", hw_port='ge8',  phy_addr=0x21, prim_offset=0x2100, leds=(0, 31*4)),
        _gige(label="27", hw_port='ge11', phy_addr=0x24, prim_offset=0x2103, leds=(0, 28*4)),
        _gige(label="28", hw_port='ge10', phy_addr=0x23, prim_offset=0x2102, leds=(0, 29*4)),
        _gige(label="29", hw_port='ge13', phy_addr=0x26, prim_offset=0x2105, leds=(0, 26*4)),
        _gige(label="30", hw_port='ge12', phy_addr=0x25, prim_offset=0x2104, leds=(0, 27*4)),
        _gige(label="31", hw_port='ge15', phy_addr=0x28, prim_offset=0x2107, leds=(0, 24*4)),
        _gige(label="32", hw_port='ge14', phy_addr=0x27, prim_offset=0x2106, leds=(0, 25*4)),
        _gige(label="33", hw_port='ge17', phy_addr=0x2a, prim_offset=0x2a01, leds=(0, 38*4)),
        _gige(label="34", hw_port='ge16', phy_addr=0x29, prim_offset=0x2a00, leds=(0, 39*4)),
        _gige(label="35", hw_port='ge19', phy_addr=0x2c, prim_offset=0x2a03, leds=(0, 36*4)),
        _gige(label="36", hw_port='ge18', phy_addr=0x2b, prim_offset=0x2a02, leds=(0, 37*4)),
        _gige(label="37", hw_port='ge21', phy_addr=0x2e, prim_offset=0x2a05, leds=(0, 34*4)),
        _gige(label="38", hw_port='ge20', phy_addr=0x2d, prim_offset=0x2a04, leds=(0, 35*4)),
        _gige(label="39", hw_port='ge23', phy_addr=0x30, prim_offset=0x2a07, leds=(0, 32*4)),
        _gige(label="40", hw_port='ge22', phy_addr=0x2f, prim_offset=0x2a06, leds=(0, 33*4)),
        _gige(label="41", hw_port='ge25', phy_addr=0x32, prim_offset=0x3201, leds=(0, 46*4)),
        _gige(label="42", hw_port='ge24', phy_addr=0x31, prim_offset=0x3200, leds=(0, 47*4)),
        _gige(label="43", hw_port='ge27', phy_addr=0x34, prim_offset=0x3203, leds=(0, 44*4)),
        _gige(label="44", hw_port='ge26', phy_addr=0x33, prim_offset=0x3202, leds=(0, 45*4)),
        _gige(label="45", hw_port='ge29', phy_addr=0x36, prim_offset=0x3205, leds=(0, 42*4)),
        _gige(label="46", hw_port='ge28', phy_addr=0x35, prim_offset=0x3204, leds=(0, 43*4)),
        _gige(label="47", hw_port='ge31', phy_addr=0x38, prim_offset=0x3207, leds=(0, 40*4)),
        _gige(label="48", hw_port='ge30', phy_addr=0x37, prim_offset=0x3206, leds=(0, 41*4)),
        _sfp(label="49",  hw_port='hg0',  phy_addr=0x40, leds=(1,11*2)),
        _sfp(label="50",  hw_port='hg1',  phy_addr=0x41, leds=(1,10*2)),
        _sfp(label="51",  hw_port='hg2',  phy_addr=0x42, leds=(1,9*2)),
        _sfp(label="52",  hw_port='hg3',  phy_addr=0x43, leds=(1,8*2)),
    )

class Accton4654PSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class Accton4654PSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

class Accton4654Temp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0049'
    driver_hwmon = ['temp1']
    temp_max_hyst = 55
    temp_max = 75
    temp_crit = 85

class Accton4654Temp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = cumulus.sensors.Temp_Unit.p2020_cpu_sensor_name    
    driver_path = '/sys/devices/soc.0/ff703100.i2c/i2c-1/1-002e'
    driver_hwmon = ['temp1']
    temp_max_hyst = 65
    temp_max = 100
    #P2020 (Tj) Temperature Operating range is 0-125 C
    temp_crit = 120

# Accton has suggested a minpwm of 0xBF(191). Seems to high to
# start with. Sticking to our minpwm 64.
class Accton4654Fan1(cumulus.sensors.Fan_Unit):
    name = 'Fan1'
    cpld_hwmon = ['fan0']
    pwm_path = '/sys/devices/soc.0/ff703100.i2c/i2c-1/1-002e'
    pwm_hwmon = ['pwm1']
    minpwm = 64

class Accton4654Fan2(cumulus.sensors.Fan_Unit):
    name = 'Fan2'
    cpld_hwmon = ['fan1']
    pwm_path = '/sys/devices/soc.0/ff703100.i2c/i2c-1/1-002e'
    pwm_hwmon = ['pwm3']
    minpwm = 64

class Accton4654Sensors():
    units = ( Accton4654PSU1(),
              Accton4654PSU2(),
              Accton4654Temp1(),
              Accton4654Temp2(),
              Accton4654Fan1(),
              Accton4654Fan2(),
              )
class Accton4654PWM1(cumulus.sensors.PWM_Unit):
    fans = (Accton4654Fan1(),
            Accton4654Fan2(),
            )
    temps = ( Accton4654Temp1(),
              Accton4654Temp2(),
              )

class Accton4654PWMs():
    units = (Accton4654PWM1(),
             )

class Accton4654PSU1LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'led_psu1'

class Accton4654PSU2LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'led_psu2'

class Accton4654Fan1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan1'
    sources = ['Fan1']
    led_location = 'led_fan0'

class Accton4654Fan2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan2'
    sources = ['Fan2']
    led_location = 'led_fan1'

class Accton4654SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_diag'

class Accton4654LEDs():
    units = (Accton4654PSU1LED(),
             Accton4654PSU2LED(),
             Accton4654Fan1LED(),
             Accton4654Fan2LED(),
             Accton4654SystemLED(),
             )

class Accton4654(cumulus.platform.Platform):
    name = 'accton,as4600_54t'
    cpld = Accton4654CPLD()
    switch = Accton4654Switch(cumulus.platform.ApolloChip())
    sensors = Accton4654Sensors()
    pwms = Accton4654PWMs()
    statusleds = Accton4654LEDs()

##
## Accton AS5610_52X Section -- Trident+ based.  48x10G, 4x40G
##

class AcctonAS5610_52XQSFPp(cumulus.platform.Trident40GPort):
    def __init__(self, label, serdes, leds):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'qsfp+')
    _set_led = '''
;;; AcctonAS5610_52XQSFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed on stack controls amber LED:
;;; 0 - off
;;; 1 - on
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
;;; We will only use green LED.  1st bit pushed is always zero to
;;; disable amber LED.
set_led:
	port 1
	pushst PORTSTATUS_ZERO
	pack

        port    a
        ld      b,LINKSCAN_P
        add     b,a
        ld      b,(b)
        tst     b,LINKSCAN_TX
        push    cy
        tst     b,LINKSCAN_RX
        push    cy
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
;;;   register B[0] - activity (TX _OR_ RX)
;;;   register B[1] - link enabled

SUB_INTF_ACTIVITY	equ	0x0  ; activity
SUB_INTF_LINKEN		equ	0x1  ; link enabled

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

;;; AcctonAS5610_52XQSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
        pack

        ;;; initialize B
        ld	b,0

        ;;; load sub-0 info
        call	sub_intf_info

        ;;; load sub-1 info
        inc	a
        call	sub_intf_info

        ;;; load sub-2 info
        inc	a
        call	sub_intf_info

        ;;; load sub-3 info
        inc	a
        call	sub_intf_info

        ;;; push accumlated link activity onto stack
        tst	B, SUB_INTF_ACTIVITY
        push	cy

        ;;; combine with BLINK state
        push	(BLINK_STATE_P)
        tand
        tinv	; flash off with activity

        ;;; push accumlated link enable onto stack
        tst	B, SUB_INTF_LINKEN
        push	cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand

        pack

        ret
'''

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

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class AcctonAS5610_52XSFPp(cumulus.platform.Trident10GPort):
    _set_led = '''
;;; AcctonAS5610_52XSFPp
;;;
;;; Two bits per port:
;;;
;;; 1st bit pushed on stack controls amber LED:
;;; 0 - off
;;; 1 - on
;;;
;;; 2n bit pushed on stack controls green LED:
;;; 0 - off
;;; 1 - on
;;;
;;; We will only use green LED.  1st bit pushed is always zero to
;;; disable amber LED.
set_led:
	port 1
	pushst PORTSTATUS_ZERO
	pack

        port    a
        ld      b,LINKSCAN_P
        add     b,a
        ld      b,(b)
        tst     b,LINKSCAN_TX
        push    cy
        tst     b,LINKSCAN_RX
        push    cy
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

class AcctonAS5610_52XCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ff705000.localbus/ea000000.cpld'

class AcctonAS5610_52XLED(cumulus.ledup.TridentLEDController):
    num_leds = 64

class AcctonAS5610_52XSwitch(cumulus.platform.BCMSwitch):
    ledup = AcctonAS5610_52XLED
    _sfp = AcctonAS5610_52XSFPp
    _qsfp = AcctonAS5610_52XQSFPp
    has_phy_ucode_mdio = False
    # This board does not have SPI-ROMs.
    has_phy_ucode_spi_rom = False
    ports = (
        _sfp(label="1",  serdes=64, leds=(1, 34)),
        _sfp(label="2",  serdes=65, leds=(1, 32)),
        _sfp(label="3",  serdes=66, leds=(1, 38)),
        _sfp(label="4",  serdes=67, leds=(1, 36)),
        _sfp(label="5",  serdes=68, leds=(1, 62)),
        _sfp(label="6",  serdes=69, leds=(1, 60)),
        _sfp(label="7",  serdes=70, leds=(1, 58)),
        _sfp(label="8",  serdes=71, leds=(1, 56)),
        _sfp(label="9",  serdes=4,  leds=(0, 2)),
        _sfp(label="10", serdes=5,  leds=(0, 0)),
        _sfp(label="11", serdes=6,  leds=(0, 6)),
        _sfp(label="12", serdes=7,  leds=(0, 4)),
        _sfp(label="13", serdes=8,  leds=(0, 50)),
        _sfp(label="14", serdes=9,  leds=(0, 48)),
        _sfp(label="15", serdes=10, leds=(0, 54)),
        _sfp(label="16", serdes=11, leds=(0, 52)),
        _sfp(label="17", serdes=12, leds=(0, 46)),
        _sfp(label="18", serdes=13, leds=(0, 44)),
        _sfp(label="19", serdes=14, leds=(0, 42)),
        _sfp(label="20", serdes=15, leds=(0, 40)),
        _sfp(label="21", serdes=17, leds=(0, 62)),
        _sfp(label="22", serdes=16, leds=(0, 60)),
        _sfp(label="23", serdes=19, leds=(0, 58)),
        _sfp(label="24", serdes=18, leds=(0, 56)),
        _sfp(label="25", serdes=21, leds=(0, 38)),
        _sfp(label="26", serdes=20, leds=(0, 36)),
        _sfp(label="27", serdes=23, leds=(0, 34)),
        _sfp(label="28", serdes=22, leds=(0, 32)),
        _sfp(label="29", serdes=24, leds=(0, 30)),
        _sfp(label="30", serdes=25, leds=(0, 28)),
        _sfp(label="31", serdes=26, leds=(0, 26)),
        _sfp(label="32", serdes=27, leds=(0, 24)),
        _sfp(label="33", serdes=28, leds=(0, 14)),
        _sfp(label="34", serdes=29, leds=(0, 8)),
        _sfp(label="35", serdes=30, leds=(0, 10)),
        _sfp(label="36", serdes=31, leds=(0, 12)),
        _sfp(label="37", serdes=32, leds=(0, 22)),
        _sfp(label="38", serdes=33, leds=(0, 20)),
        _sfp(label="39", serdes=34, leds=(0, 18)),
        _sfp(label="40", serdes=35, leds=(0, 16)),
        _sfp(label="41", serdes=36, leds=(1, 44)),
        _sfp(label="42", serdes=37, leds=(1, 42)),
        _sfp(label="43", serdes=38, leds=(1, 40)),
        _sfp(label="44", serdes=39, leds=(1, 46)),
        _sfp(label="45", serdes=40, leds=(1, 52)),
        _sfp(label="46", serdes=41, leds=(1, 50)),
        _sfp(label="47", serdes=42, leds=(1, 48)),
        _sfp(label="48", serdes=43, leds=(1, 54)),

        _qsfp(label="49", serdes=(48,49,50,51), leds=(1, 26)),
        _qsfp(label="50", serdes=(44,45,46,47), leds=(1, 24)),
        _qsfp(label="51", serdes=(60,61,62,63), leds=(1, 30)),
        _qsfp(label="52", serdes=(56,57,58,59), leds=(1, 28)),
    )

class AcctonAS5610_52xPSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class AcctonAS5610_52xPSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

class AcctonAS5610_52xTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'
    driver_hwmon = ['temp1']
    temp_max_hyst = 65
    temp_max = 100
    temp_crit = 105

class AcctonAS5610_52BoardTemp(cumulus.sensors.Temp_Unit):
    def __init__(self):
        self.name =  (self.__class__.__name__[16:])
        self.temp_max_hyst = 55
        self.temp_max = 75
        self.temp_crit = 85
        self.description = 'Board Temperature Sensor'
        self.driver_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-004d'
        cumulus.sensors.Temp_Unit.__init__(self)

class AcctonAS5610_52xTemp2(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp1']

class AcctonAS5610_52xTemp3(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp2']

class AcctonAS5610_52xTemp4(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp3']

class AcctonAS5610_52xTemp5(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp4']

class AcctonAS5610_52xTemp6(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp5']

class AcctonAS5610_52xTemp7(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp6']

class AcctonAS5610_52xTemp8(AcctonAS5610_52BoardTemp):
    driver_hwmon = ['temp7']

class AcctonAS5610_52xTemp9(cumulus.sensors.Temp_Unit):
    name = 'Temp9'
    description = 'NE1617A Sensor Temperature'
    driver_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0018'
    driver_hwmon = ['temp1']
    temp_max_hyst = 55
    temp_max = 75
    temp_crit = 85

class AcctonAS5610_52xTemp10(cumulus.sensors.Temp_Unit):
    name = 'Temp10'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0018'
    driver_hwmon = ['temp2']
    temp_max_hyst = 65
    temp_max = 80
    temp_crit = 90

class AcctonAS5610_52xFan(cumulus.sensors.Fan_Unit):
    name = 'Fan'
    description = 'System Fan'
    cpld_hwmon = ['system_fan']
    pwm_path = '/sys/devices/ff705000.localbus/ea000000.cpld'

class AcctonAS5610_52xPSU1LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'led_psu1'

class AcctonAS5610_52xPSU2LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'led_psu2'

class AcctonAS5610_52xFanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan'
    sources = ['Fan']
    led_location = 'led_fan'

class AcctonAS5610_52xSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_diag'

class AcctonAS5610_52xSensors():
    units = ( AcctonAS5610_52xTemp1(),
              AcctonAS5610_52xTemp2(),
              AcctonAS5610_52xTemp3(),
              AcctonAS5610_52xTemp4(),
              AcctonAS5610_52xTemp5(),
              AcctonAS5610_52xTemp6(),
              AcctonAS5610_52xTemp7(),
              AcctonAS5610_52xTemp8(),
              AcctonAS5610_52xTemp9(),
              AcctonAS5610_52xTemp10(),
              AcctonAS5610_52xPSU1(),
              AcctonAS5610_52xPSU2(),
              AcctonAS5610_52xFan(),
        )

class AcctonAS5610_52xPWM1(cumulus.sensors.PWM_Unit):
    fans = (AcctonAS5610_52xFan(),
            )
    temps = ( AcctonAS5610_52xTemp1(),
              AcctonAS5610_52xTemp2(),
              AcctonAS5610_52xTemp3(),
              AcctonAS5610_52xTemp4(),
              AcctonAS5610_52xTemp5(),
              AcctonAS5610_52xTemp6(),
              AcctonAS5610_52xTemp7(),
              AcctonAS5610_52xTemp8(),
              AcctonAS5610_52xTemp9(),
              AcctonAS5610_52xTemp10(),
              )

class AcctonAS5610_52xPWMs():
    units = (AcctonAS5610_52xPWM1(),
             )

class AcctonAS5610_52xLEDs():
    units = (AcctonAS5610_52xPSU1LED(),
             AcctonAS5610_52xPSU2LED(),
             AcctonAS5610_52xFanLED(),
             AcctonAS5610_52xSystemLED(),
             )

class AcctonAS5610_52X(cumulus.platform.Platform):
    name = 'accton,as5610_52x'
    cpld = AcctonAS5610_52XCPLD()
    switch = AcctonAS5610_52XSwitch(cumulus.platform.TridentChip())
    sensors = AcctonAS5610_52xSensors()
    pwms = AcctonAS5610_52xPWMs()
    statusleds = AcctonAS5610_52xLEDs()

##
## Accton AS670x_32X -- Trident2 based 32x40G.  Two variants, P2020 and P2041
## CPU modules
##

class AcctonAS670x_32XQSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; AcctonAS670x_32XQSFPp
;;; Two bits per port: yellow(active low), green(active low)
set_led:
        port a

        pushst  PORTSTATUS_ONE
        pack

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
    _set_led_4x10 = '''
;;;
;;; Input : register A, logical port
;;; Input / Output : register B, accumulated port status

;;; For each port accumulate 2 bits of information in register B:
;;;   register B[0] - activity (TX _OR_ RX)
;;;   register B[1] - link enabled

SUB_INTF_ACTIVITY	equ	0x0  ; activity
SUB_INTF_LINKEN		equ	0x1  ; link enabled

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

;;; AcctonAS670x_32XQSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active low), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:
        ;;; disable yellow LED
        pushst  PORTSTATUS_ONE
        pack

        ;;; initialize B
        ld	b,0

        ;;; load sub-0 info
        call	sub_intf_info

        ;;; load sub-1 info
        inc	a
        call	sub_intf_info

        ;;; load sub-2 info
        inc	a
        call	sub_intf_info

        ;;; load sub-3 info
        inc	a
        call	sub_intf_info

        ;;; push accumlated link activity onto stack
        tst	B, SUB_INTF_ACTIVITY
        push	cy

        ;;; combine with BLINK state
        push	(BLINK_STATE_P)
        tand
        tinv	; flash off with activity

        ;;; push accumlated link enable onto stack
        tst	B, SUB_INTF_LINKEN
        push	cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand

        ;;; LEDs are active low
        tinv
        pack

        ret
'''
    _serdes_intf_map = { 40:'XGMII', 10:'XFI' }

    def __init__(self, label, base_serdes, leds, xr_lane_map=None):
        serdes = [ base_serdes + x for x in range(4) ]
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                    label=label,
                                                    serdes=serdes,
                                                    phy_types=None,
                                                    phy_addrs=None,
                                                    leds=leds,
                                                    rx_lane_map=xr_lane_map,
                                                    rx_polarity_flip=None,
                                                    tx_lane_map=xr_lane_map,
                                                    tx_polarity_flip=None,
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

        fn_name = self.__class__.__name__
        if mode == "4x10G":
            call = (fn_name + "_4x10", self._set_led_4x10, led_port)
        elif mode == "40G":
            call = (fn_name, self._set_led, led_port)

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class AcctonAS670x_32XLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 32

class AcctonAS670x_32XSwitch(cumulus.platform.BCMSwitch):
    ledup = AcctonAS670x_32XLED
    _qsfp = AcctonAS670x_32XQSFPp

    has_phy_ucode_mdio = False
    has_phy_ucode_spi_rom = False

    ports = (
        _qsfp(label="1" , base_serdes=12,  leds=(0, 0)),
        _qsfp(label="2" , base_serdes=16,  leds=(0, 2)),
        _qsfp(label="3" , base_serdes=20,  leds=(0, 4)),
        _qsfp(label="4" , base_serdes=24,  leds=(0, 6)),
        _qsfp(label="5" , base_serdes=28,  leds=(0, 8)),
        _qsfp(label="6" , base_serdes=32,  leds=(0, 10)),
        _qsfp(label="7" , base_serdes=36,  leds=(0, 12)),
        _qsfp(label="8" , base_serdes=40,  leds=(0, 14)),
        _qsfp(label="9" , base_serdes=44,  leds=(0, 16)),
        _qsfp(label="10", base_serdes=48,  leds=(0, 18)),
        _qsfp(label="11", base_serdes=64,  leds=(1, 0)),
        _qsfp(label="12", base_serdes=68,  leds=(1, 2)),
        _qsfp(label="13", base_serdes=72,  leds=(1, 4)),
        _qsfp(label="14", base_serdes=76,  leds=(1, 6)),
        _qsfp(label="15", base_serdes=80,  leds=(1, 8)),
        _qsfp(label="16", base_serdes=96,  leds=(1, 10)),
        _qsfp(label="17", base_serdes=100, leds=(1, 12)),
        _qsfp(label="18", base_serdes=104, leds=(1, 14)),
        _qsfp(label="19", base_serdes=108, leds=(1, 16)),
        _qsfp(label="20", base_serdes=112, leds=(1, 18)),
        _qsfp(label="21", base_serdes=116, xr_lane_map=0x2301, leds=(1, 26)),
        _qsfp(label="22", base_serdes=120, xr_lane_map=0x2301, leds=(1, 28)),
        _qsfp(label="23", base_serdes=124, xr_lane_map=0x2301, leds=(1, 30)),
        _qsfp(label="24", base_serdes=0,   xr_lane_map=0x2301, leds=(0, 20)),
        _qsfp(label="25", base_serdes=4,   xr_lane_map=0x2301, leds=(0, 22)),
        _qsfp(label="26", base_serdes=8,   xr_lane_map=0x2301, leds=(0, 24)),
        _qsfp(label="27", base_serdes=84,  xr_lane_map=0x2301, leds=(1, 20)),
        _qsfp(label="28", base_serdes=88,  xr_lane_map=0x2301, leds=(1, 22)),
        _qsfp(label="29", base_serdes=92,  xr_lane_map=0x2301, leds=(1, 24)),
        _qsfp(label="30", base_serdes=52,  xr_lane_map=0x2301, leds=(0, 26)),
        _qsfp(label="31", base_serdes=56,  xr_lane_map=0x2301, leds=(0, 28)),
        _qsfp(label="32", base_serdes=60,  xr_lane_map=0x2301, leds=(0, 30)),
    )

class AcctonAS670xSYSCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0031'

class AcctonAS670xFANCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'

class AcctonAS670xPSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0031'
    driver_hwmon = ['psu_pwr1']

class AcctonAS670xPSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0031'
    cpld_hwmon = ['psu_pwr2']

class AcctonAS670xTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp1']

class AcctonAS670xTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp2']

class AcctonAS670xTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp3']

class AcctonAS670xTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp4']

class AcctonAS670xTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp5']

class AcctonAS670xTemp6(cumulus.sensors.Temp_Unit):
    name = 'Temp6'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp6']

class AcctonAS670xTemp7(cumulus.sensors.Temp_Unit):
    name = 'Temp7'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp7']

class AcctonAS670xTemp8(cumulus.sensors.Temp_Unit):
    name = 'Temp8'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/i2c-5/5-004d'
    driver_hwmon = ['temp8']

class AcctonAS670xFan1(cumulus.sensors.Fan_Unit):
    name = 'Fan1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan1']

class AcctonAS670xFan2(cumulus.sensors.Fan_Unit):
    name = 'Fan2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan2']

class AcctonAS670xFan3(cumulus.sensors.Fan_Unit):
    name = 'Fan3'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan3']

class AcctonAS670xFan4(cumulus.sensors.Fan_Unit):
    name = 'Fan4'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan4']

class AcctonAS670xFan5(cumulus.sensors.Fan_Unit):
    name = 'Fan5'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan5']

class AcctonAS670xFan6(cumulus.sensors.Fan_Unit):
    name = 'Fan6'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan6']

class AcctonAS670xFan7(cumulus.sensors.Fan_Unit):
    name = 'Fan7'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan7']

class AcctonAS670xFan8(cumulus.sensors.Fan_Unit):
    name = 'Fan8'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan8']

class AcctonAS670xFan9(cumulus.sensors.Fan_Unit):
    name = 'Fan9'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan9']

class AcctonAS670xFan10(cumulus.sensors.Fan_Unit):
    name = 'Fan10'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0035'
    driver_hwmon = ['fan10']

class AcctonAS670xSensors():
    units = ( AcctonAS670xPSU1(),
              AcctonAS670xPSU2(),
              AcctonAS670xTemp1(),
              AcctonAS670xTemp2(),
              AcctonAS670xTemp3(),
              AcctonAS670xTemp4(),
              AcctonAS670xTemp5(),
              AcctonAS670xTemp6(),
              AcctonAS670xTemp7(),
              AcctonAS670xTemp8(),
              AcctonAS670xFan1(),
              AcctonAS670xFan2(),
              AcctonAS670xFan3(),
              AcctonAS670xFan4(),
              AcctonAS670xFan5(),
              AcctonAS670xFan6(),
              AcctonAS670xFan7(),
              AcctonAS670xFan8(),
              AcctonAS670xFan9(),
              AcctonAS670xFan10(),
              )
class AcctonAS670xPWM1(cumulus.sensors.PWM_Unit):
    fans = (  AcctonAS670xFan1(),
	      AcctonAS670xFan2(),
              AcctonAS670xFan3(),
              AcctonAS670xFan4(),
              AcctonAS670xFan5(),
              AcctonAS670xFan6(),
              AcctonAS670xFan7(),
              AcctonAS670xFan8(),
              AcctonAS670xFan9(),
              AcctonAS670xFan10(),
            )
    temps = ( AcctonAS670xTemp1(),
              AcctonAS670xTemp2(),
              AcctonAS670xTemp3(),
              AcctonAS670xTemp4(),
              AcctonAS670xTemp5(),
              AcctonAS670xTemp6(),
              AcctonAS670xTemp7(),
              AcctonAS670xTemp8(),
            )

class AcctonAS670xPWMs():
    units = (AcctonAS670xPWM1(),
             )

class AcctonAS670xSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_sys'
    bad_led_color = 'green_blinking'

class AcctonAS670xLEDs():
    units = ( AcctonAS670xSystemLED(),
             )
class AcctonAS670x_32X(cumulus.platform.Platform):
    switch = AcctonAS670x_32XSwitch(cumulus.platform.TridentTwo_56850_Chip())
    cpld = cumulus.cpld.CPLDMerged((AcctonAS670xSYSCPLD(), AcctonAS670xFANCPLD()))
    sensors = AcctonAS670xSensors()
    pwms = AcctonAS670xPWMs()
    statusleds = AcctonAS670xLEDs()

class AcctonAS6700_32X(AcctonAS670x_32X):
    name = 'accton,as6700_32x'

class AcctonAS6701_32X(AcctonAS670x_32X):
    name = 'accton,as6701_32x'

##
## Accton AS5712_54X -- Trident2 based 48x10G + 6x40G.
##
class AcctonAS5712_54XSFPp(cumulus.platform.TridentTwo10GPort):
    _set_led = '''
;;; AcctonAS5712_54XSFPp
;;; Two bits per port: red (active low), green (active low)
set_led:
set_bicolor_led:
        pushst  PORTSTATUS_ONE   ; turn off red LED
        pack
set_green_led:
        port a

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
    def __init__(self, label, serdes, leds):
        cumulus.platform.TridentTwoPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 phy_layer='SFP+',
                                                 prim_offset=None,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, led_port)

        for led in led_index_list:
            set_calls[led] = call
            set_calls[led + 1] = None

        return set_calls

class AcctonAS5712_54XQSFPp(cumulus.platform.TridentTwo40GPort):
    '''
    ;;;
    ;;; There are 5 leds per qsfp port on this platform
    ;;;   1 led to use when the port is in 40G mode
    ;;;   The other 4 are used when the port is in 4x10G mode
    ;;;   all are 1 bit per led, green - active low
    ;;;
    '''
    _set_led_40G = '''
;;; AcctonAS5712_54XQSFPp
set_led:
        call    set_green_led ; set the first led green/off
        ret
'''
    _set_led_4x10 = '''
;;; AcctonAS5712_54XQSFPp_4x10
set_led:
        call    set_green_led
        inc     a
        call    set_green_led
        inc     a
        call    set_green_led
        inc     a
        call    set_green_led

        ret
'''
    _set_led_4x10_off = '''
;;; AcctonAS5712_54XQSFPp_4x10_off
;;;   when the port is in 40G mode, we turn these 4 leds off
set_led:
        ld      a,4
        call    pad_n_one
        ret
'''
    def __init__(self, label, serdes, leds):

        cumulus.platform.TridentTwo40GPort.__init__(self,
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

        if mode == '4x10G' and sub != 0:
            return set_calls

        if mode == "4x10G":
            # turn the single 40G led off
            call_40G = 1
            # use the group of 4 leds for link/activity
            call_4x10G = ("Act5712_QSFP_4x10",     self._set_led_4x10,     led_port)
        elif mode == "40G":
            # use the single led for link/activity
            call_40G = ("Act5712_QSFP_40G",      self._set_led_40G,      led_port)
            # turn the group of 4 leds off
            call_4x10G = ("Act5712_QSFP_4x10_off", self._set_led_4x10_off, led_port)

        set_calls[self.leds[1]] = call_40G
        set_calls[self.leds[2]] = call_4x10G
        set_calls[self.leds[3]] = None
        set_calls[self.leds[4]] = None
        set_calls[self.leds[5]] = None

        return set_calls


class AcctonAS5712_54XLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 72

class AcctonAS5712_54XSwitch(cumulus.platform.BCMSwitch):
    ledup = AcctonAS5712_54XLED
    _sfp = AcctonAS5712_54XSFPp
    _qsfp = AcctonAS5712_54XQSFPp

    has_phy_ucode_mdio = False
    has_phy_ucode_spi_rom = False

    ports = (
        _sfp(label="1",  serdes=(12,), leds=(0, 70)),
        _sfp(label="2",  serdes=(13,), leds=(0, 68)),
        _sfp(label="3",  serdes=(14,), leds=(0, 66)),
        _sfp(label="4",  serdes=(15,), leds=(0, 64)),
        _sfp(label="5",  serdes=(20,), leds=(0, 62)),
        _sfp(label="6",  serdes=(21,), leds=(0, 60)),
        _sfp(label="7",  serdes=(22,), leds=(0, 58)),
        _sfp(label="8",  serdes=(23,), leds=(0, 56)),
        _sfp(label="9",  serdes=(24,), leds=(0, 54)),
        _sfp(label="10", serdes=(25,), leds=(0, 52)),
        _sfp(label="11", serdes=(26,), leds=(0, 50)),
        _sfp(label="12", serdes=(27,), leds=(0, 48)),
        _sfp(label="13", serdes=(28,), leds=(0, 46)),
        _sfp(label="14", serdes=(29,), leds=(0, 44)),
        _sfp(label="15", serdes=(30,), leds=(0, 42)),
        _sfp(label="16", serdes=(31,), leds=(0, 40)),
        _sfp(label="17", serdes=(44,), leds=(0, 38)),
        _sfp(label="18", serdes=(45,), leds=(0, 36)),
        _sfp(label="19", serdes=(46,), leds=(0, 34)),
        _sfp(label="20", serdes=(47,), leds=(0, 32)),
        _sfp(label="21", serdes=(48,), leds=(0, 30)),
        _sfp(label="22", serdes=(49,), leds=(0, 28)),
        _sfp(label="23", serdes=(50,), leds=(0, 26)),
        _sfp(label="24", serdes=(51,), leds=(0, 24)),
        _sfp(label="25", serdes=(52,), leds=(0, 22)),
        _sfp(label="26", serdes=(53,), leds=(0, 20)),
        _sfp(label="27", serdes=(54,), leds=(0, 18)),
        _sfp(label="28", serdes=(55,), leds=(0, 16)),
        _sfp(label="29", serdes=(56,), leds=(0, 14)),
        _sfp(label="30", serdes=(57,), leds=(0, 12)),
        _sfp(label="31", serdes=(58,), leds=(0, 10)),
        _sfp(label="32", serdes=(59,), leds=(0,  8)),
        _sfp(label="33", serdes=(60,), leds=(0,  6)),
        _sfp(label="34", serdes=(61,), leds=(0,  4)),
        _sfp(label="35", serdes=(62,), leds=(0,  2)),
        _sfp(label="36", serdes=(63,), leds=(0,  0)),
        _sfp(label="37", serdes=(64,), leds=(1, 70)),
        _sfp(label="38", serdes=(65,), leds=(1, 68)),
        _sfp(label="39", serdes=(66,), leds=(1, 66)),
        _sfp(label="40", serdes=(67,), leds=(1, 64)),
        _sfp(label="41", serdes=(68,), leds=(1, 62)),
        _sfp(label="42", serdes=(69,), leds=(1, 60)),
        _sfp(label="43", serdes=(70,), leds=(1, 58)),
        _sfp(label="44", serdes=(71,), leds=(1, 56)),
        _sfp(label="45", serdes=(72,), leds=(1, 54)),
        _sfp(label="46", serdes=(73,), leds=(1, 52)),
        _sfp(label="47", serdes=(74,), leds=(1, 50)),
        _sfp(label="48", serdes=(75,), leds=(1, 48)),

        _qsfp(label="49", serdes=(96, 97, 98, 99),     leds=(1, 45, 18, 19, 20, 21)),
        _qsfp(label="50", serdes=(100, 101, 102, 103), leds=(1, 44, 22, 23, 24, 25)),
        _qsfp(label="51", serdes=(80, 81, 82, 83),     leds=(1, 46, 26, 27, 28, 29)),
        _qsfp(label="52", serdes=(104, 105, 106, 107), leds=(1, 43, 30, 31, 32, 33)),
        _qsfp(label="53", serdes=(108, 109, 110, 111), leds=(1, 42, 34, 35, 36, 37)),
        _qsfp(label="54", serdes=(76, 77, 78, 79),     leds=(1, 47, 38, 39, 40, 41)),
    )

class AcctonAS5712_54XCPLD(cumulus.cpld.SysFS):
    path = '/sys/bus/platform/devices/accton_as5712_54x_cpld.0'

'''
   Accton AS5712_54X LEDs
       Front Panel PSU1:
         leave under hardware control, not managed by software.
       Front Panel PSU2:
         leave under hardware control, not managed by software.
       Front Panel Diag:
         GREEN, RED, YELLOW, OFF
       Front Panel FAN Status:
         leave under hardware control, not managed by software.
       Front Panel Locator:
         YELLOW, Blinking YELLOW, OFF
       Back Panel - 5 individual FAN tray LEDs:
         leave under hardware control, not managed by software.

'''

class AcctonAS5712_54XSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'Diag'
    led_location = 'led_diag'

class AcctonAS5712_54XPSU1LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'led_psu1'

class AcctonAS5712_54XPSU2LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'led_psu2'

class AcctonAS5712_54XFanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan'
    # Depends on system fans 01 through 10
    sources = [ "Fan%02d" % (x) for x in range(1,11) ]
    led_location = 'led_fan'

class AcctonAS5712_54XLEDs():
    units = (AcctonAS5712_54XSystemLED(),
             AcctonAS5712_54XPSU1LED(),
             AcctonAS5712_54XPSU2LED(),
             AcctonAS5712_54XFanLED(),
             )

class AcctonAS5712_54XTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/bus/i2c/devices/15-0048'
    # Accton has specified that fan speed should be at 40% till 49.5 C
    # and then increase to 100% at 57.7
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50

class AcctonAS5712_54XTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'Rear Air sensor'
    driver_path = '/sys/bus/i2c/devices/16-0049'
    # Accton has specified that fan speed should be at 40% till 49.5 C
    # and then increase to 100% at 57.7
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50

class AcctonAS5712_54XTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'Front Air sensor'
    driver_path = '/sys/bus/i2c/devices/17-004a'
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50

AcctonAS5712_54X_core_path = '/sys/devices/platform/coretemp.0'
class AcctonAS5712_54XTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS5712_54X_core_path
    driver_hwmon = ['temp2']
    temp_crit = 98

class AcctonAS5712_54XTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS5712_54X_core_path
    driver_hwmon = ['temp3']
    temp_max_hyst = 50
    temp_crit = 98

class AcctonAS5712_54XTemp6(cumulus.sensors.Temp_Unit):
    name = 'Temp6'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS5712_54X_core_path
    driver_hwmon = ['temp4']
    temp_max_hyst = 50
    temp_crit = 98

class AcctonAS5712_54XTemp7(cumulus.sensors.Temp_Unit):
    name = 'Temp7'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS5712_54X_core_path
    driver_hwmon = ['temp5']
    temp_max_hyst = 50
    temp_crit = 98

class AcctonAS5712_54XDIMMTemp(cumulus.sensors.Temp_Unit):
    description = cumulus.sensors.Temp_Unit.dimm_sensor_name
    driver_hwmon = ['temp1']
    temp_crit = 95
    temp_max_hyst = 50
    temp_max = 90

    def generate_driver_path(self, i2c_addr):
        pci_0_1f_3_path = '/sys/devices/pci0000:00/0000:00:1f.3'

        if os.path.exists(pci_0_1f_3_path):
            for x in os.listdir(pci_0_1f_3_path):
                if x.startswith('i2c-'):
                    a,b = x.split('-')
                    return os.path.join(pci_0_1f_3_path, x) + '/' + b + '-00' + i2c_addr
        return None

class AcctonAS5712_54XTemp8(AcctonAS5712_54XDIMMTemp):
    name = 'Temp8'

    def __init__(self):
        self.driver_path = self.generate_driver_path('1a')
        AcctonAS5712_54XDIMMTemp.__init__(self)

class AcctonAS5712_54XTemp9(AcctonAS5712_54XDIMMTemp):
    name = 'Temp9'

    def __init__(self):
        self.driver_path = self.generate_driver_path('1b')
        AcctonAS5712_54XDIMMTemp.__init__(self)

class AcctonAS5712_54X_PSU(cumulus.sensors.PSU_Unit):
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

class AcctonAS5712_54XPSU1(AcctonAS5712_54X_PSU):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class AcctonAS5712_54XPSU2(AcctonAS5712_54X_PSU):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

# The fan modules on the AS5712_54X contain two fans each, one called
# "FAN" (21500 RPM) and one called "FANR" (18000 RPM).  All the odd
# fans are of type FAN and the evens are of type FANR.  Create a base
# class for each type.
class AcctonAS5712_54XFan(cumulus.sensors.Fan_Unit):
    driver_path = AcctonAS5712_54XCPLD.path
    fan_min = 2500
    fan_max = 23500

class AcctonAS5712_54XFanR(cumulus.sensors.Fan_Unit):
    driver_path = AcctonAS5712_54XCPLD.path
    fan_min = 2500
    fan_max = 20000

class AcctonAS5712_54XFan1(AcctonAS5712_54XFan):
    name = 'Fan01'
    description = 'Fan Tray 1, Fan A'
    # driver is fan speed ...
    driver_hwmon = ['fan01']
    # status is "cpld_hwmon"
    cpld_hwmon = ['fan01']

    # The CPLD driver only exports "pwm1", which controls all the
    # fans.
    pwm_hwmon = ['pwm1']
    # Accton has specified that the default fan speed must be 40% of max.
    minpwm = 102

class AcctonAS5712_54XFan2(AcctonAS5712_54XFanR):
    name = 'Fan02'
    description = 'Fan Tray 1, Fan B'
    driver_hwmon = ['fan02']
    cpld_hwmon = ['fan02']

class AcctonAS5712_54XFan3(AcctonAS5712_54XFan):
    name = 'Fan03'
    description = 'Fan Tray 2, Fan A'
    driver_hwmon = ['fan03']
    cpld_hwmon = ['fan03']

class AcctonAS5712_54XFan4(AcctonAS5712_54XFanR):
    name = 'Fan04'
    description = 'Fan Tray 2, Fan B'
    driver_hwmon = ['fan04']
    cpld_hwmon = ['fan04']

class AcctonAS5712_54XFan5(AcctonAS5712_54XFanR):
    name = 'Fan05'
    description = 'Fan Tray 3, Fan A'
    driver_hwmon = ['fan05']
    cpld_hwmon = ['fan05']

class AcctonAS5712_54XFan6(AcctonAS5712_54XFan):
    name = 'Fan06'
    description = 'Fan Tray 3, Fan B'
    driver_hwmon = ['fan06']
    cpld_hwmon = ['fan06']

class AcctonAS5712_54XFan7(AcctonAS5712_54XFanR):
    name = 'Fan07'
    description = 'Fan Tray 4, Fan A'
    driver_hwmon = ['fan07']
    cpld_hwmon = ['fan07']

class AcctonAS5712_54XFan8(AcctonAS5712_54XFan):
    name = 'Fan08'
    description = 'Fan Tray 4, Fan B'
    driver_hwmon = ['fan08']
    cpld_hwmon = ['fan08']

class AcctonAS5712_54XFan9(AcctonAS5712_54XFanR):
    name = 'Fan09'
    description = 'Fan Tray 5, Fan A'
    driver_hwmon = ['fan09']
    cpld_hwmon = ['fan09']

class AcctonAS5712_54XFan10(AcctonAS5712_54XFan):
    name = 'Fan10'
    description = 'Fan Tray 5, Fan B'
    driver_hwmon = ['fan10']
    cpld_hwmon = ['fan10']

# PSU I2C addresses
AcctonAS5712_54X_PSU1_i2c_path = '/sys/bus/i2c/devices/11-003c'
AcctonAS5712_54X_PSU2_i2c_path = '/sys/bus/i2c/devices/12-003f'

# PSU Temp Sensors
class AcctonAS5712_54XPSUTemp(cumulus.sensors.Temp_Unit):
    temp_crit = 100
    temp_max = 60
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

class AcctonAS5712_54XTemp10(AcctonAS5712_54XPSUTemp):
    psu = 'PSU1'
    name = psu + 'Temp1'
    description = psu + ' Inlet Temp Sensor'
    driver_path = AcctonAS5712_54X_PSU1_i2c_path
    driver_hwmon = ['temp1']

class AcctonAS5712_54XTemp11(AcctonAS5712_54XPSUTemp):
    psu = 'PSU1'
    name = psu + 'Temp2'
    description = psu + ' Max Temp Sensor'
    driver_path = AcctonAS5712_54X_PSU1_i2c_path
    driver_hwmon = ['temp2']

class AcctonAS5712_54XTemp12(AcctonAS5712_54XPSUTemp):
    psu = 'PSU2'
    name = psu + 'Temp1'
    description = psu + ' Inlet Temp Sensor'
    driver_path = AcctonAS5712_54X_PSU2_i2c_path
    driver_hwmon = ['temp1']

class AcctonAS5712_54XTemp13(AcctonAS5712_54XPSUTemp):
    psu = 'PSU2'
    name = psu + 'Temp2'
    description = psu + ' Max Temp Sensor'
    driver_path = AcctonAS5712_54X_PSU2_i2c_path
    driver_hwmon = ['temp2']

# PSU Fan Sensors
class AcctonAS5712_54XPSUFan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    driver_hwmon = ['fan1']
    fan_max = 22000
    fan_min = 2000
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

class AcctonAS5712_54XFan11(AcctonAS5712_54XPSUFan):
    psu = 'PSU1'
    name = psu + 'Fan1'
    description = psu + ' Fan'
    driver_path = AcctonAS5712_54X_PSU1_i2c_path

class AcctonAS5712_54XFan12(AcctonAS5712_54XPSUFan):
    psu = 'PSU2'
    name = psu + 'Fan1'
    description = psu + ' Fan'
    driver_path = AcctonAS5712_54X_PSU2_i2c_path

class AcctonAS5712_54XSensors():
    units = ( AcctonAS5712_54XPSU1(),
              AcctonAS5712_54XPSU2(),
              AcctonAS5712_54XTemp1(),
              AcctonAS5712_54XTemp2(),
              AcctonAS5712_54XTemp3(),
              AcctonAS5712_54XTemp4(),
              AcctonAS5712_54XTemp5(),
              AcctonAS5712_54XTemp6(),
              AcctonAS5712_54XTemp7(),
              AcctonAS5712_54XTemp8(),
              AcctonAS5712_54XTemp9(),
              AcctonAS5712_54XTemp10(),
              AcctonAS5712_54XTemp11(),
              AcctonAS5712_54XTemp12(),
              AcctonAS5712_54XTemp13(),
              AcctonAS5712_54XFan1(),
              AcctonAS5712_54XFan2(),
              AcctonAS5712_54XFan3(),
              AcctonAS5712_54XFan4(),
              AcctonAS5712_54XFan5(),
              AcctonAS5712_54XFan6(),
              AcctonAS5712_54XFan7(),
              AcctonAS5712_54XFan8(),
              AcctonAS5712_54XFan9(),
              AcctonAS5712_54XFan10(),
              AcctonAS5712_54XFan11(),
              AcctonAS5712_54XFan12(),
              )

class AcctonAS5712_54XPWM1(cumulus.sensors.PWM_Unit):
    # This is only one PWM control knob for all 10 system fans, so
    # only use Fan1 here.
    name = 'System PWM'
    fans = (AcctonAS5712_54XFan1(),
            AcctonAS5712_54XFan2(),
            AcctonAS5712_54XFan3(),
            AcctonAS5712_54XFan4(),
            AcctonAS5712_54XFan5(),
            AcctonAS5712_54XFan6(),
            AcctonAS5712_54XFan7(),
            AcctonAS5712_54XFan8(),
            AcctonAS5712_54XFan9(),
            AcctonAS5712_54XFan10(),
            )
    temps = ( AcctonAS5712_54XTemp1(),
              AcctonAS5712_54XTemp2(),
              AcctonAS5712_54XTemp3(),
              AcctonAS5712_54XTemp4(),
              AcctonAS5712_54XTemp5(),
              AcctonAS5712_54XTemp6(),
              AcctonAS5712_54XTemp7(),
              AcctonAS5712_54XTemp8(),
              AcctonAS5712_54XTemp9(),
              )

# PSU1 Fan Controller
class AcctonAS5712_54XPWM2(cumulus.sensors.PWM_Unit):
    name = 'PSU1 PWM'
    fans = (AcctonAS5712_54XFan11(),
            )
    temps = (AcctonAS5712_54XTemp10(),
             AcctonAS5712_54XTemp11(),
             )

# PSU2 Fan Controller
class AcctonAS5712_54XPWM3(cumulus.sensors.PWM_Unit):
    name = 'PSU2 PWM'
    fans = (AcctonAS5712_54XFan12(),
            )
    temps = (AcctonAS5712_54XTemp12(),
             AcctonAS5712_54XTemp13(),
             )

class AcctonAS5712_54XPWMs():
    units = (AcctonAS5712_54XPWM1(),
             AcctonAS5712_54XPWM2(),
             AcctonAS5712_54XPWM3(),
             )

class AcctonAS5712_54X(cumulus.platform.Platform):
    name = 'accton,as5712_54x'
    switch = AcctonAS5712_54XSwitch(cumulus.platform.TridentTwo_56854_Chip())
    cpld = AcctonAS5712_54XCPLD()
    statusleds = AcctonAS5712_54XLEDs()
    pwms = AcctonAS5712_54XPWMs()
    sensors = AcctonAS5712_54XSensors()

##
## Accton AS6712_32X -- Trident2 based 32x40G.
##
class AcctonAS6712_32XQSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; AcctonAS6712_32XQSFPp
;;; Two bits per port: yellow(active low), green(active low)
set_led:
        port a

        pushst  PORTSTATUS_ONE
        pack

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
    _set_led_4x10 = '''
;;;
;;; Input : register A, logical port
;;; Input / Output : register B, accumulated port status

;;; For each port accumulate 2 bits of information in register B:
;;;   register B[0] - activity (TX _OR_ RX)
;;;   register B[1] - link enabled

SUB_INTF_ACTIVITY	equ	0x0  ; activity
SUB_INTF_LINKEN		equ	0x1  ; link enabled

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

;;; AcctonAS6712_32XQSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active low), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:
        ;;; disable yellow LED
        pushst  PORTSTATUS_ONE
        pack

        ;;; initialize B
        ld	b,0

        ;;; load sub-0 info
        call	sub_intf_info

        ;;; load sub-1 info
        inc	a
        call	sub_intf_info

        ;;; load sub-2 info
        inc	a
        call	sub_intf_info

        ;;; load sub-3 info
        inc	a
        call	sub_intf_info

        ;;; push accumlated link activity onto stack
        tst	B, SUB_INTF_ACTIVITY
        push	cy

        ;;; combine with BLINK state
        push	(BLINK_STATE_P)
        tand
        tinv	; flash off with activity

        ;;; push accumlated link enable onto stack
        tst	B, SUB_INTF_LINKEN
        push	cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand

        ;;; LEDs are active low
        tinv
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

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None
        return set_calls

class AcctonAS6712_32XLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 128

class AcctonAS6712_32XSwitch(cumulus.platform.BCMSwitch):
    ledup = AcctonAS6712_32XLED
    _qsfp = AcctonAS6712_32XQSFPp

    has_phy_ucode_mdio = False
    has_phy_ucode_spi_rom = False

    ports = (
        _qsfp(label="1", serdes=(  0,   1,   2,   3), leds=(0, 0)),
        _qsfp(label="2", serdes=(  4,   5,   6,   7), leds=(0, 2)),
        _qsfp(label="3", serdes=(  8,   9,  10,  11), leds=(0, 4)),
        _qsfp(label="4", serdes=( 12,  13,  14,  15), leds=(0, 6)),
        _qsfp(label="5", serdes=( 16,  17,  18,  19), leds=(0, 8)),
        _qsfp(label="6", serdes=( 20,  21,  22,  23), leds=(0, 10)),
        _qsfp(label="7", serdes=( 24,  25,  26,  27), leds=(0, 12)),
        _qsfp(label="8", serdes=( 28,  29,  30,  31), leds=(0, 14)),
        _qsfp(label="9", serdes=( 32,  33,  34,  35), leds=(0, 16)),
        _qsfp(label="10", serdes=( 36,  37,  38,  39), leds=(0, 18)),
        _qsfp(label="11", serdes=( 40,  41,  42,  43), leds=(0, 20)),
        _qsfp(label="12", serdes=( 44,  45,  46,  47), leds=(0, 22)),
        _qsfp(label="13", serdes=( 48,  49,  50,  51), leds=(0, 24)),
        _qsfp(label="14", serdes=( 52,  53,  54,  55), leds=(0, 26)),
        _qsfp(label="15", serdes=( 56,  57,  58,  59), leds=(0, 28)),
        _qsfp(label="16", serdes=( 60,  61,  62,  63), leds=(0, 30)),
        _qsfp(label="17", serdes=( 64,  65,  66,  67), leds=(1, 32)),
        _qsfp(label="18", serdes=( 68,  69,  70,  71), leds=(1, 34)),
        _qsfp(label="19", serdes=( 72,  73,  74,  75), leds=(1, 36)),
        _qsfp(label="20", serdes=( 76,  77,  78,  79), leds=(1, 38)),
        _qsfp(label="21", serdes=( 80,  81,  82,  83), leds=(1, 40)),
        _qsfp(label="22", serdes=( 84,  85,  86,  87), leds=(1, 42)),
        _qsfp(label="23", serdes=( 88,  89,  90,  91), leds=(1, 44)),
        _qsfp(label="24", serdes=( 92,  93,  94,  95), leds=(1, 46)),
        _qsfp(label="25", serdes=( 96,  97,  98,  99), leds=(1, 48)),
        _qsfp(label="26", serdes=(100, 101, 102, 103), leds=(1, 50)),
        _qsfp(label="27", serdes=(104, 105, 106, 107), leds=(1, 52)),
        _qsfp(label="28", serdes=(108, 109, 110, 111), leds=(1, 54)),
        _qsfp(label="29", serdes=(112, 113, 114, 115), leds=(1, 56)),
        _qsfp(label="30", serdes=(116, 117, 118, 119), leds=(1, 58)),
        _qsfp(label="31", serdes=(120, 121, 122, 123), leds=(1, 60)),
        _qsfp(label="32", serdes=(124, 125, 126, 127), leds=(1, 62)),
    )

class AcctonAS6712_32XCPLD(cumulus.cpld.SysFS):
    path = '/sys/bus/platform/devices/accton_as6712_32x_cpld.0'

'''
   Accton AS6712_32X LEDs
       Front Panel PSU1:
         leave under hardware control, not managed by software.
       Front Panel PSU2:
         leave under hardware control, not managed by software.
       Front Panel Diag:
         GREEN, RED, YELLOW, OFF
       Front Panel FAN Status:
         leave under hardware control, not managed by software.
       Front Panel Locator:
         YELLOW, Blinking YELLOW, OFF
       Back Panel - 5 individual FAN tray LEDs:
         leave under hardware control, not managed by software.

'''

class AcctonAS6712_32XSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'Diag'
    led_location = 'led_diag'

class AcctonAS6712_32XPSU1LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU1'
    sources = ['PSU1']
    led_location = 'led_psu1'

class AcctonAS6712_32XPSU2LED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU2'
    sources = ['PSU2']
    led_location = 'led_psu2'

class AcctonAS6712_32XFanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan'
    # Depends on system fans 01 through 10
    sources = [ "Fan%02d" % (x) for x in range(1,11) ]
    led_location = 'led_fan'

class AcctonAS6712_32XLEDs():
    units = (AcctonAS6712_32XSystemLED(),
             AcctonAS6712_32XPSU1LED(),
             AcctonAS6712_32XPSU2LED(),
             AcctonAS6712_32XFanLED(),
             )

## TODO: sensors limits need to be updated.
## Also need to add PSU Temp and fan sensors.
## Waiting on Accton Engg team for data.
class AcctonAS6712_32XTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/bus/i2c/devices/14-0048'
    # Accton has specified that fan speed should be at 40% till 49.5 C
    # and then increase to 100% at 57.7
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50

class AcctonAS6712_32XTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'Front Air sensor'
    driver_path = '/sys/bus/i2c/devices/15-0049'
    # Accton has specified that fan speed should be at 40% till 49.5 C
    # and then increase to 100% at 57.7
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50

class AcctonAS6712_32XTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'Front Air sensor'
    driver_path = '/sys/bus/i2c/devices/16-004a'
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50

class AcctonAS6712_32XTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'Rear Air sensor'
    driver_path = '/sys/bus/i2c/devices/17-004b'
    temp_crit = 85
    temp_max = 58
    temp_max_hyst = 50
    
AcctonAS6712_32X_core_path = '/sys/devices/platform/coretemp.0'
class AcctonAS6712_32XTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS6712_32X_core_path
    driver_hwmon = ['temp2']
    temp_crit = 98

class AcctonAS6712_32XTemp6(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS6712_32X_core_path
    driver_hwmon = ['temp3']
    temp_max_hyst = 50
    temp_crit = 98

class AcctonAS6712_32XTemp7(cumulus.sensors.Temp_Unit):
    name = 'Temp6'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS6712_32X_core_path
    driver_hwmon = ['temp4']
    temp_max_hyst = 50
    temp_crit = 98

class AcctonAS6712_32XTemp8(cumulus.sensors.Temp_Unit):
    name = 'Temp7'
    description = 'Intel CPU die sensor'
    driver_path = AcctonAS6712_32X_core_path
    driver_hwmon = ['temp5']
    temp_max_hyst = 50
    temp_crit = 98

class AcctonAS6712_32XDIMMTemp(cumulus.sensors.Temp_Unit):
    description = cumulus.sensors.Temp_Unit.dimm_sensor_name
    driver_hwmon = ['temp1']
    temp_crit = 95
    temp_max_hyst = 50
    temp_max = 90

    def generate_driver_path(self, i2c_addr):
        pci_0_1f_3_path = '/sys/devices/pci0000:00/0000:00:1f.3'

        if os.path.exists(pci_0_1f_3_path):
            for x in os.listdir(pci_0_1f_3_path):
                if x.startswith('i2c-'):
                    a,b = x.split('-')
                    return os.path.join(pci_0_1f_3_path, x) + '/' + b + '-00' + i2c_addr
        return None

class AcctonAS6712_32XTemp9(AcctonAS6712_32XDIMMTemp):
    name = 'Temp8'

    def __init__(self):
        self.driver_path = self.generate_driver_path('1a')
        AcctonAS6712_32XDIMMTemp.__init__(self)

class AcctonAS6712_32XTemp10(AcctonAS6712_32XDIMMTemp):
    name = 'Temp9'

    def __init__(self):
        self.driver_path = self.generate_driver_path('1b')
        AcctonAS6712_32XDIMMTemp.__init__(self)

class AcctonAS6712_32X_PSU(cumulus.sensors.PSU_Unit):
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

class AcctonAS6712_32XPSU1(AcctonAS6712_32X_PSU):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class AcctonAS6712_32XPSU2(AcctonAS6712_32X_PSU):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

# The fan modules on the AS6712_32X contain two fans each, one called
# "FAN" (21500 RPM) and one called "FANR" (18000 RPM).  All the odd
# fans are of type FAN and the evens are of type FANR.  Create a base
# class for each type.
class AcctonAS6712_32XFan(cumulus.sensors.Fan_Unit):
    driver_path = AcctonAS6712_32XCPLD.path
    fan_min = 2500
    fan_max = 23500
    # Accton has specified that the default fan speed must be 40% of max.
    minpwm = 102
    
class AcctonAS6712_32XFanR(cumulus.sensors.Fan_Unit):
    driver_path = AcctonAS6712_32XCPLD.path
    fan_min = 2500
    fan_max = 20000
    # Accton has specified that the default fan speed must be 40% of max.
    minpwm = 102
    
class AcctonAS6712_32XFan1(AcctonAS6712_32XFan):
    name = 'Fan01'
    description = 'Fan Tray 1, Fan A'
    # driver is fan speed ...
    driver_hwmon = ['fan09']
    # status is "cpld_hwmon"
    cpld_hwmon = ['fan09']

    # The CPLD driver only exports "pwm1", which controls all the
    # fans.
    pwm_hwmon = ['pwm1']

class AcctonAS6712_32XFan2(AcctonAS6712_32XFanR):
    name = 'Fan02'
    description = 'Fan Tray 1, Fan B'
    driver_hwmon = ['fan10']
    cpld_hwmon = ['fan10']

class AcctonAS6712_32XFan3(AcctonAS6712_32XFan):
    name = 'Fan03'
    description = 'Fan Tray 2, Fan A'
    driver_hwmon = ['fan07']
    cpld_hwmon = ['fan07']

class AcctonAS6712_32XFan4(AcctonAS6712_32XFanR):
    name = 'Fan04'
    description = 'Fan Tray 2, Fan B'
    driver_hwmon = ['fan08']
    cpld_hwmon = ['fan08']

class AcctonAS6712_32XFan5(AcctonAS6712_32XFanR):
    name = 'Fan05'
    description = 'Fan Tray 3, Fan A'
    driver_hwmon = ['fan05']
    cpld_hwmon = ['fan05']

class AcctonAS6712_32XFan6(AcctonAS6712_32XFan):
    name = 'Fan06'
    description = 'Fan Tray 3, Fan B'
    driver_hwmon = ['fan06']
    cpld_hwmon = ['fan06']

class AcctonAS6712_32XFan7(AcctonAS6712_32XFanR):
    name = 'Fan07'
    description = 'Fan Tray 4, Fan A'
    driver_hwmon = ['fan03']
    cpld_hwmon = ['fan03']

class AcctonAS6712_32XFan8(AcctonAS6712_32XFan):
    name = 'Fan08'
    description = 'Fan Tray 4, Fan B'
    driver_hwmon = ['fan04']
    cpld_hwmon = ['fan04']

class AcctonAS6712_32XFan9(AcctonAS6712_32XFanR):
    name = 'Fan09'
    description = 'Fan Tray 5, Fan A'
    driver_hwmon = ['fan01']
    cpld_hwmon = ['fan01']

class AcctonAS6712_32XFan10(AcctonAS6712_32XFan):
    name = 'Fan10'
    description = 'Fan Tray 5, Fan B'
    driver_hwmon = ['fan02']
    cpld_hwmon = ['fan02']

class AcctonAS6712_32XSensors():
    units = ( AcctonAS6712_32XPSU1(),
              AcctonAS6712_32XPSU2(),
              AcctonAS6712_32XTemp1(),
              AcctonAS6712_32XTemp2(),
              AcctonAS6712_32XTemp3(),
              AcctonAS6712_32XTemp4(),
              AcctonAS6712_32XTemp5(),
              AcctonAS6712_32XTemp6(),
              AcctonAS6712_32XTemp7(),
              AcctonAS6712_32XTemp8(),
              AcctonAS6712_32XTemp9(),
              AcctonAS6712_32XTemp10(),
              AcctonAS6712_32XFan1(),
              AcctonAS6712_32XFan2(),
              AcctonAS6712_32XFan3(),
              AcctonAS6712_32XFan4(),
              AcctonAS6712_32XFan5(),
              AcctonAS6712_32XFan6(),
              AcctonAS6712_32XFan7(),
              AcctonAS6712_32XFan8(),
              AcctonAS6712_32XFan9(),
              AcctonAS6712_32XFan10(),
              )

class AcctonAS6712_32XPWM1(cumulus.sensors.PWM_Unit):
    # This is only one PWM control knob for all 10 system fans, so
    # only use Fan1 here.
    name = 'System PWM'
    fans = (AcctonAS6712_32XFan1(),
            AcctonAS6712_32XFan2(),
            AcctonAS6712_32XFan3(),
            AcctonAS6712_32XFan4(),
            AcctonAS6712_32XFan5(),
            AcctonAS6712_32XFan6(),
            AcctonAS6712_32XFan7(),
            AcctonAS6712_32XFan8(),
            AcctonAS6712_32XFan9(),
            AcctonAS6712_32XFan10(),
            )
    temps = ( AcctonAS6712_32XTemp1(),
              AcctonAS6712_32XTemp2(),
              AcctonAS6712_32XTemp3(),
              AcctonAS6712_32XTemp4(),
              AcctonAS6712_32XTemp5(),
              AcctonAS6712_32XTemp6(),
              AcctonAS6712_32XTemp7(),
              AcctonAS6712_32XTemp8(),
              AcctonAS6712_32XTemp9(),
              AcctonAS6712_32XTemp10(),
              )

class AcctonAS6712_32XPWMs():
    units = (AcctonAS6712_32XPWM1(),
             )

class AcctonAS6712_32X(cumulus.platform.Platform):
    name = 'accton,as6712_32x'
    switch = AcctonAS6712_32XSwitch(cumulus.platform.TridentTwo_56854_Chip())
    cpld = AcctonAS6712_32XCPLD()
    statusleds = AcctonAS6712_32XLEDs()
    pwms = AcctonAS6712_32XPWMs()
    sensors = AcctonAS6712_32XSensors()
