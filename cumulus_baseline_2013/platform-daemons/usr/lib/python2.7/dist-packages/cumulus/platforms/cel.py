#
# Copyright 2013.  Cumulus Networks, Inc.
#
# cel.py --
#     Celestica switch platforms
#

import cumulus.platform
import cumulus.cpld
import cumulus.ledup
import cumulus.sunit
import cumulus.sfp
import subprocess

class CelKennisisGigE(cumulus.platform.Triumph1GPort):
    def __init__(self, label, hw_port, phy_addr, prim_offset):
        cumulus.platform.Triumph1GPort.__init__(self,
                                                label=label,
                                                hw_port=hw_port,
                                                phy_type="54680",
                                                phy_addr=phy_addr,
                                                phy_layer='SFP+',
                                                prim_offset=prim_offset,
                                                leds=None,
                                                unit=0)

class CelKennisisSFPp(cumulus.platform.Triumph10GPort):
    _set_led = '''
;;; CelKennisisSFPp
;;; Two bits per port: yellow(active high), green(active high)
set_led:
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

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
        pack

        ret
'''
    def __init__(self, label, hw_port, phy_addr, leds):
        cumulus.platform.Triumph10GPort.__init__(self,
                                                 label=label,
                                                 hw_port=hw_port,
                                                 phy_type="8747",
                                                 phy_addr=phy_addr,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMBCM(phy_addr, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        for led in led_index_list:
            set_calls[led] = call
            set_calls[led + 1] = None

        return set_calls

class CelKennisisCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ffe05000.localbus/ffb00000.CPLD'

class CelKennisisLED(cumulus.ledup.TriumphLEDController):
    num_leds = 8

class CelKennisisSwitch(cumulus.platform.BCMSwitch):
    ledup = CelKennisisLED
    _gige = CelKennisisGigE
    _sfp = CelKennisisSFPp
    has_phy_ucode_mdio = False # XXX unverified
    has_phy_ucode_spi_rom = False # XXX unverified

    ports = (
        _gige(label="1",  hw_port='ge1',  phy_addr=0x2,  prim_offset=0x1d02),
        _gige(label="2",  hw_port='ge0',  phy_addr=0x1,  prim_offset=0x1d01),
        _gige(label="3",  hw_port='ge3',  phy_addr=0x4,  prim_offset=0x1d04),
        _gige(label="4",  hw_port='ge2',  phy_addr=0x3,  prim_offset=0x1d03),
        _gige(label="5",  hw_port='ge5',  phy_addr=0x6,  prim_offset=0x1d06),
        _gige(label="6",  hw_port='ge4',  phy_addr=0x5,  prim_offset=0x1d05),
        _gige(label="7",  hw_port='ge7',  phy_addr=0x8,  prim_offset=0x2500),
        _gige(label="8",  hw_port='ge6',  phy_addr=0x7,  prim_offset=0x1d07),
        _gige(label="9",  hw_port='ge9',  phy_addr=0xa,  prim_offset=0x0102),
        _gige(label="10", hw_port='ge8' , phy_addr=0x9,  prim_offset=0x0101),
        _gige(label="11", hw_port='ge11', phy_addr=0xc,  prim_offset=0x0104),
        _gige(label="12", hw_port='ge10', phy_addr=0xb,  prim_offset=0x0103),
        _gige(label="13", hw_port='ge13', phy_addr=0xe,  prim_offset=0x0106),
        _gige(label="14", hw_port='ge12', phy_addr=0xd,  prim_offset=0x0105),
        _gige(label="15", hw_port='ge15', phy_addr=0x10, prim_offset=0x0900),
        _gige(label="16", hw_port='ge14', phy_addr=0xf,  prim_offset=0x0107),
        _gige(label="17", hw_port='ge17', phy_addr=0x12, prim_offset=0x2502),
        _gige(label="18", hw_port='ge16', phy_addr=0x11, prim_offset=0x2501),
        _gige(label="19", hw_port='ge19', phy_addr=0x14, prim_offset=0x2504),
        _gige(label="20", hw_port='ge18', phy_addr=0x13, prim_offset=0x2503),
        _gige(label="21", hw_port='ge21', phy_addr=0x16, prim_offset=0x0506),
        _gige(label="22", hw_port='ge20', phy_addr=0x15, prim_offset=0x0505),
        _gige(label="23", hw_port='ge23', phy_addr=0x18, prim_offset=0x0d00),
        _gige(label="24", hw_port='ge22', phy_addr=0x17, prim_offset=0x0507),
        _gige(label="25", hw_port='ge25', phy_addr=0x22, prim_offset=0x0d02),
        _gige(label="26", hw_port='ge24', phy_addr=0x21, prim_offset=0x0d01),
        _gige(label="27", hw_port='ge27', phy_addr=0x24, prim_offset=0x0d04),
        _gige(label="28", hw_port='ge26', phy_addr=0x23, prim_offset=0x0d03),
        _gige(label="29", hw_port='ge29', phy_addr=0x26, prim_offset=0x2506),
        _gige(label="30", hw_port='ge28', phy_addr=0x25, prim_offset=0x2505),
        _gige(label="31", hw_port='ge31', phy_addr=0x28, prim_offset=0x2d00),
        _gige(label="32", hw_port='ge30', phy_addr=0x27, prim_offset=0x2507),
        _gige(label="33", hw_port='ge33', phy_addr=0x2a, prim_offset=0x1102),
        _gige(label="34", hw_port='ge32', phy_addr=0x29, prim_offset=0x1101),
        _gige(label="35", hw_port='ge35', phy_addr=0x2c, prim_offset=0x1104),
        _gige(label="36", hw_port='ge34', phy_addr=0x2b, prim_offset=0x1103),
        _gige(label="37", hw_port='ge37', phy_addr=0x2e, prim_offset=0x1106),
        _gige(label="38", hw_port='ge36', phy_addr=0x2d, prim_offset=0x1105),
        _gige(label="39", hw_port='ge39', phy_addr=0x30, prim_offset=0x1900),
        _gige(label="40", hw_port='ge38', phy_addr=0x2f, prim_offset=0x1107),
        _gige(label="41", hw_port='ge41', phy_addr=0x32, prim_offset=0x2d02),
        _gige(label="42", hw_port='ge40', phy_addr=0x31, prim_offset=0x2d01),
        _gige(label="43", hw_port='ge43', phy_addr=0x34, prim_offset=0x2d04),
        _gige(label="44", hw_port='ge42', phy_addr=0x33, prim_offset=0x2d03),
        _gige(label="45", hw_port='ge45', phy_addr=0x36, prim_offset=0x2d06),
        _gige(label="46", hw_port='ge44', phy_addr=0x35, prim_offset=0x2d05),
        _gige(label="47", hw_port='ge47', phy_addr=0x38, prim_offset=0x3500),
        _gige(label="48", hw_port='ge46', phy_addr=0x37, prim_offset=0x2d07),

        _sfp(label="49", hw_port='hg0', phy_addr=0x47, leds=(0, 0)),
        _sfp(label="50", hw_port='hg1', phy_addr=0x46, leds=(0, 2)),
        _sfp(label="51", hw_port='hg2', phy_addr=0x45, leds=(0, 4)),
        _sfp(label="52", hw_port='hg3', phy_addr=0x44, leds=(0, 6)),
    )

class CelKennisisPSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class CelKennisisPSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

class CelKennisisTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004d'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 65
    temp_crit = 90

class CelKennisisTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'Front Right Corner Ambient Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004b'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelKennisisTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'System Rear Outlet Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004e'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 60

class CelKennisisTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'P2020 Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0048'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 65
    temp_crit = 90

class CelKennisisTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'Front Left Corner Ambient Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004f'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelKennisisFan1(cumulus.sensors.Fan_Unit):
    name = 'Fan1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan1']
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']

class CelKennisisFan2(cumulus.sensors.Fan_Unit):
    name = 'Fan2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan2']
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']

class CelKennisisFan3(cumulus.sensors.Fan_Unit):
    name = 'Fan3'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan3']
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']

class CelKennisisPWM1(cumulus.sensors.PWM_Unit):
    fans = (CelKennisisFan1(),
            CelKennisisFan2(),
            CelKennisisFan3(),
            )
    temps = (CelKennisisTemp1(),
             CelKennisisTemp2(),
             CelKennisisTemp3(),
             CelKennisisTemp4(),
             CelKennisisTemp5(),
             )

class CelKennisisSensors():
    units = ( CelKennisisPSU1(),
              CelKennisisPSU2(),
              CelKennisisFan1(),
              CelKennisisFan2(),
              CelKennisisFan3(),
              CelKennisisTemp1(),
              CelKennisisTemp2(),
              CelKennisisTemp3(),
              CelKennisisTemp4(),
              CelKennisisTemp5(),
              )

class CelKennisisPWMs():
    units = (CelKennisisPWM1(),
             )

class CelKennisisSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_status'
    bad_led_color = 'green_blinking'

class CelKennisisLEDs():
    units = (CelKennisisSystemLED(),
             )

class CelKennisis(cumulus.platform.Platform):
    name = 'cel,kennisis'
    switch = CelKennisisSwitch(cumulus.platform.TriumphChip())
    cpld = CelKennisisCPLD()
    statusleds = CelKennisisLEDs()
    pwms = CelKennisisPWMs()
    sensors = CelKennisisSensors()

class CelRedstoneSFPp(cumulus.platform.Trident10GPort):
    _set_led = '''
;;; CelRedstoneSFPp
;;; Two bits per port: yellow(active high), green(active high)
set_led:
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

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
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
                                                 rx_lane_map=0x1032,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        for led in led_index_list:
            # Increment the index by number of status bits per port
            set_calls[led] = call
            set_calls[led + 1] = None

        return set_calls

class CelRedstoneQSFPp(cumulus.platform.Trident40GPort):
    _set_led = '''
;;; CelRedstoneQSFPp
;;; Two bits per port: yellow(active high), green(active high)
set_led:
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

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
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

SUB_INTF_ACTIVITY       equ     0x0  ; activity
SUB_INTF_LINKEN         equ     0x1  ; link enabled

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

;;; CelRedstoneQSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active high), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:

        ;;; initialize B
        ld      b,0

        ;;; load sub-0 info
        call    sub_intf_info

        ;;; load sub-1 info
        inc     a
        call    sub_intf_info

        ;;; load sub-2 info
        inc     a
        call    sub_intf_info

        ;;; load sub-3 info
        inc     a
        call    sub_intf_info

        ;;; push accumlated link activity onto stack
        tst     B, SUB_INTF_ACTIVITY
        push    cy

        ;;; combine with BLINK state
        push    (BLINK_STATE_P)
        tand
        tinv    ; flash off with activity

        ;;; push accumlated link enable onto stack
        tst     B, SUB_INTF_LINKEN
        push    cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand

        ;;; LEDs are active low
        tinv
        pack

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
        pack

        ret
'''
    def __init__(self, label, serdes, leds, rx_lane_map, tx_lane_map, rx_polarity_flip=None, tx_polarity_flip=None):
        cumulus.platform.Trident40GPort.__init__(self,
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
            call = (fn_name + "_4x10", self._set_led_4x10,  self.led_port_num(mode, 0))
        elif mode == "40G":
            call = (fn_name, self._set_led, self.led_port_num(mode, 0))

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class CelRedstoneLED(cumulus.ledup.TridentLEDController):
    num_leds = 52

class CelRedstoneSwitch(cumulus.platform.BCMSwitch):
    ledup = CelRedstoneLED
    _sfp = CelRedstoneSFPp
    _qsfp = CelRedstoneQSFPp

    has_phy_ucode_mdio = False # XXX unverified
    has_phy_ucode_spi_rom = False # XXX unverified

    ports = (
        _sfp(label="1",  serdes=12, leds=(0,  4)),
        _sfp(label="2",  serdes=13, leds=(0,  6)),
        _sfp(label="3",  serdes=14, leds=(0,  8)),
        _sfp(label="4",  serdes=15, leds=(0, 10)),
        _sfp(label="5",  serdes=16, leds=(0, 12)),
        _sfp(label="6",  serdes=17, leds=(0, 14)),
        _sfp(label="7",  serdes=18, leds=(0, 16)),
        _sfp(label="8",  serdes=19, leds=(0, 18)),
        _sfp(label="9",  serdes=20, leds=(0, 20)),
        _sfp(label="10", serdes=21, leds=(0, 22)),
        _sfp(label="11", serdes=22, leds=(0, 24)),
        _sfp(label="12", serdes=23, leds=(0, 26)),
        _sfp(label="13", serdes=24, leds=(0, 28)),
        _sfp(label="14", serdes=25, leds=(0, 30)),
        _sfp(label="15", serdes=26, leds=(0, 32)),
        _sfp(label="16", serdes=27, leds=(0, 34)),
        _sfp(label="17", serdes=28, leds=(0, 36)),
        _sfp(label="18", serdes=29, leds=(0, 38)),
        _sfp(label="19", serdes=30, leds=(0, 40)),
        _sfp(label="20", serdes=31, leds=(0, 42)),
        _sfp(label="21", serdes=32, leds=(0, 44)),
        _sfp(label="22", serdes=33, leds=(0, 46)),
        _sfp(label="23", serdes=34, leds=(0, 48)),
        _sfp(label="24", serdes=35, leds=(0, 50)),
        _sfp(label="25", serdes=36, leds=(1,  0)),
        _sfp(label="26", serdes=37, leds=(1,  2)),
        _sfp(label="27", serdes=38, leds=(1,  4)),
        _sfp(label="28", serdes=39, leds=(1,  6)),
        _sfp(label="29", serdes=40, leds=(1,  8)),
        _sfp(label="30", serdes=41, leds=(1, 10)),
        _sfp(label="31", serdes=42, leds=(1, 12)),
        _sfp(label="32", serdes=43, leds=(1, 14)),
        _sfp(label="33", serdes=44, leds=(1, 16)),
        _sfp(label="34", serdes=45, leds=(1, 18)),
        _sfp(label="35", serdes=46, leds=(1, 20)),
        _sfp(label="36", serdes=47, leds=(1, 22)),
        _sfp(label="37", serdes=48, leds=(1, 24)),
        _sfp(label="38", serdes=49, leds=(1, 26)),
        _sfp(label="39", serdes=50, leds=(1, 28)),
        _sfp(label="40", serdes=51, leds=(1, 30)),
        _sfp(label="41", serdes=56, leds=(1, 32)),
        _sfp(label="42", serdes=57, leds=(1, 34)),
        _sfp(label="43", serdes=58, leds=(1, 36)),
        _sfp(label="44", serdes=59, leds=(1, 38)),
        _sfp(label="45", serdes=60, leds=(1, 40)),
        _sfp(label="46", serdes=61, leds=(1, 42)),
        _sfp(label="47", serdes=62, leds=(1, 44)),
        _sfp(label="48", serdes=63, leds=(1, 46)),

        _qsfp(label="49", serdes=(64, 65, 66, 67), leds=(1, 48),
            rx_lane_map=0x0213, tx_lane_map=0x2031),
        _qsfp(label="50", serdes=(68, 69, 70, 71), leds=(1, 50),
            rx_lane_map=0x2031, tx_lane_map=0x3120,
            tx_polarity_flip=(True, True,False, False)),
        _qsfp(label="51", serdes=( 0,  1,  2,  3), leds=(0, 0),
          rx_lane_map=0x2031, rx_polarity_flip=(True, False, False, False),
          tx_lane_map=0x3120, tx_polarity_flip=(False, True,False, False)),
        _qsfp(label="52", serdes=( 4,  5,  6,  7), leds=(0, 2),
            rx_lane_map=0x1230, rx_polarity_flip=(True, False, False, True),
            tx_lane_map=0x3120, tx_polarity_flip=(True,True,False, False)),
    )

class CelRedstoneCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ffe05000.localbus/ffb00000.CPLD1'

class CelRedstonePSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class CelRedstonePSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

class CelRedstoneTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 100
    temp_crit = 105

class CelRedstoneTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'Front Right Corner Ambient Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004b'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelRedstoneTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004e'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 65
    temp_crit = 90

class CelRedstoneTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'P2020 Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0048'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 65
    temp_crit = 90

class CelRedstoneTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'System Rear Outlet Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0049'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 60

class CelRedstoneTemp6(cumulus.sensors.Temp_Unit):
    name = 'Temp6'
    description = 'Front Left Corner Ambient Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004f'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelRedstoneFan1(cumulus.sensors.Fan_Unit):
    name = 'Fan1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan1']
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']

class CelRedstoneFan2(cumulus.sensors.Fan_Unit):
    name = 'Fan2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan2']
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']

class CelRedstoneFan3(cumulus.sensors.Fan_Unit):
    name = 'Fan3'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan3']
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']

class CelRedstoneFan4(cumulus.sensors.Fan_Unit):
    name = 'Fan4'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan4']
    driver_hwmon = ['fan4']
    pwm_hwmon = ['pwm4']

class CelRedstoneFan5(cumulus.sensors.Fan_Unit):
    name = 'Fan5'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan5']
    driver_hwmon = ['fan5']
    pwm_hwmon = ['pwm5']

class CelRedstonePWM1(cumulus.sensors.PWM_Unit):
    fans = (CelRedstoneFan1(),
            CelRedstoneFan2(),
            CelRedstoneFan3(),
            CelRedstoneFan4(),
            CelRedstoneFan5(),
            )
    temps = (CelRedstoneTemp1(),
             CelRedstoneTemp2(),
             CelRedstoneTemp3(),
             CelRedstoneTemp4(),
             CelRedstoneTemp5(),
             CelRedstoneTemp6(),
             )

class CelRedstoneSensors():
    units = ( CelRedstonePSU1(),
              CelRedstonePSU2(),
              CelRedstoneFan1(),
              CelRedstoneFan2(),
              CelRedstoneFan3(),
              CelRedstoneFan4(),
              CelRedstoneFan5(),
              CelRedstoneTemp1(),
              CelRedstoneTemp2(),
              CelRedstoneTemp3(),
              CelRedstoneTemp4(),
              CelRedstoneTemp5(),
              CelRedstoneTemp6(),
              )

class CelRedstonePWMs():
    units = (CelRedstonePWM1(),
             )

class CelRedstoneSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_status'
    bad_led_color = 'green_blinking'

class CelRedstoneLEDs():
    units = (CelRedstoneSystemLED(),
             )

class CelRedstone(cumulus.platform.Platform):
    name = 'cel,redstone'
    switch = CelRedstoneSwitch(cumulus.platform.TridentChip())
    cpld = CelRedstoneCPLD()
    statusleds = CelRedstoneLEDs()
    pwms = CelRedstonePWMs()
    sensors = CelRedstoneSensors()

''' Redstone XP
'''
class CelRedstoneXpSFPp(cumulus.platform.TridentTwo10GPort):

    _set_led = '''
;;; CelRedstoneXpSFPp
;;
;;; Each port on the Redstone XP uses two bits (SFP and QSFP), they
;;;  behave as follows:
;;;
;;;                  bit 0
;;;                0        1
;;;            +--------+-------+
;;;          0 | green  |  off  |
;;;   bit 1    +--------+-------+
;;;          1 |  red   |  off  |
;;;            +--------+-------+
set_led:
set_any_led:
;;; The first bit will indicate link/activity (low active)
;;; The second bit will always be 0
;;;
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

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
        pack

        ret
'''
    def __init__(self, label, serdes, leds, rx_polarity_flip=None, tx_polarity_flip=None):
        cumulus.platform.TridentTwo10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 rx_lane_map=0x3210,
                                                 tx_lane_map=0x1032,
                                                 rx_polarity_flip=rx_polarity_flip,
                                                 tx_polarity_flip=tx_polarity_flip,                                                 
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSLabel(label, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, led_port)

        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class CelRedstoneXpQSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; CelRedstoneXpQSFPp
;;;
;;; For 40G mode, we use only the first LED to indicate link/activity.
;;; The other 3 LEDs will be off.
;;;
set_led:
        call    set_any_led    ; set the first led green/off

        push    PORTSTATUS_ONE ; 1, 1 => led 2 off
        pack
        push    PORTSTATUS_ONE
        pack

        push    PORTSTATUS_ONE ; 1, 1 => led 3 off
        pack
        push    PORTSTATUS_ONE
        pack

        push    PORTSTATUS_ONE ; 1, 1 => led 4 off
        pack
        push    PORTSTATUS_ONE
        pack

        ret
'''
    _set_led_4x10 = '''
;;; CelRedstoneXpQSFPp_4x10
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
    def __init__(self, label, serdes, leds, tx_lane_map, rx_polarity_flip=None, tx_polarity_flip=None):
        cumulus.platform.TridentTwo40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=leds,
                                                 rx_lane_map=0x3210,
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

class CelRedstoneXpLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 72

class CelRedstoneXpCPLD(cumulus.cpld.SysFS):
    path = '/sys/bus/platform/devices/cel_redstone_xp_cpld.0'

'''
   Celestica Redstone XP LEDs
       System:
         green - all systems ok
         green blinking - fan missing or broken, psu missing or broken
       PSU1:
         green - psu1 installed and working
         off - psu1 missing or broken
       PSU2:
         green - psu2 installed and working
         off - psu2 missing or broken
       Fan1:
         green - fan installed and working
         off - fan missing or broken
       Fan2:
         green - fan installed and working
         off - fan missing or broken
       Fan3:
         green - fan installed and working
         off - fan missing or broken
       Fan4:
         green - fan installed and working
         off - fan missing or broken
'''

class CelRedstoneXpSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_system'
    bad_led_color = 'green_blinking'

class CelRedstoneXpPsu1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Psu1'
    sources = ['PSU1']
    led_location = 'led_psu1'
    bad_led_color = 'off'

class CelRedstoneXpPsu2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Psu2'
    sources = ['PSU2']
    led_location = 'led_psu2'
    bad_led_color = 'off'

class CelRedstoneXpFanLED(cumulus.sensors.StatusLED_Unit):
    bad_led_color = 'off'
    colormap = {'green':'1', 'off':'0', '0':'off', '1':'green'}

    def led_update(self, color):
        self.set_gpio_value(self.led_location, self.colormap[color])

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        return self.name, self.colormap[color]

class CelRedstoneXpFan1LED(CelRedstoneXpFanLED):
    name = 'Fan Tray 1'
    sources = ['Fan1', 'Fan5']
    led_location = 'led_fan1_green'

class CelRedstoneXpFan2LED(CelRedstoneXpFanLED):
    name = 'Fan Tray 2'
    sources = ['Fan2', 'Fan6']
    led_location = 'led_fan2_green'

class CelRedstoneXpFan3LED(CelRedstoneXpFanLED):
    name = 'Fan Tray 3'
    sources = ['Fan3', 'Fan7']
    led_location = 'led_fan3_green'

class CelRedstoneXpFan4LED(CelRedstoneXpFanLED):
    name = 'Fan Tray 4'
    sources = ['Fan4', 'Fan8']
    led_location = 'led_fan4_green'

class CelRedstoneXpTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = 'Intel CPU external sensor'
    driver_path = '/sys/bus/i2c/devices/14-0048'
    temp_crit = 70
    temp_max = 65

class CelRedstoneXpTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'Rear Outlet Air sensor'
    driver_path = '/sys/bus/i2c/devices/15-004e'
    temp_crit = 60
    temp_max = 48
    temp_min = -10
    temp_lcrit = -15

class CelRedstoneXpTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'Front Outlet Air sensor'
    driver_path = '/sys/bus/i2c/devices/24-0049'
    temp_crit = 60
    temp_max = 48
    temp_min = -10
    temp_lcrit = -15

class CelRedstoneXpTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/bus/i2c/devices/25-004a'
    temp_crit = 80
    temp_max = 75

CelRedstoneXp_core_path = '/sys/devices/platform/coretemp.0'
class CelRedstoneXpTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'Intel CPU die sensor'
    driver_path = CelRedstoneXp_core_path
    driver_hwmon = ['temp2']
    temp_crit = 98

class CelRedstoneXpTemp6(cumulus.sensors.Temp_Unit):
    name = 'Temp6'
    description = 'Intel CPU die sensor'
    driver_path = CelRedstoneXp_core_path
    driver_hwmon = ['temp3']
    temp_crit = 98

class CelRedstoneXpTemp7(cumulus.sensors.Temp_Unit):
    name = 'Temp7'
    description = 'Intel CPU die sensor'
    driver_path = CelRedstoneXp_core_path
    driver_hwmon = ['temp4']
    temp_crit = 98

class CelRedstoneXpTemp8(cumulus.sensors.Temp_Unit):
    name = 'Temp8'
    description = 'Intel CPU die sensor'
    driver_path = CelRedstoneXp_core_path
    driver_hwmon = ['temp5']
    temp_crit = 98

CelRedstoneXp_13_4d_path = '/sys/bus/i2c/devices/13-004d'
CelRedstoneXp_13_2e_path = '/sys/bus/i2c/devices/13-002e'

class CelRedstoneXpFan(cumulus.sensors.Fan_Unit):
    fan_min = 1000
    fan_max = 25000

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '1':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class CelRedstoneXpFan1(CelRedstoneXpFan):
    name = 'Fan1'
    description = 'Fan Tray 1'
    driver_path = CelRedstoneXp_13_4d_path
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']
    fan_present = 'fan1_present'

class CelRedstoneXpFan2(CelRedstoneXpFan):
    name = 'Fan2'
    description = 'Fan Tray 2'
    driver_path = CelRedstoneXp_13_4d_path
    driver_hwmon = ['fan4']
    pwm_hwmon = ['pwm4']
    fan_present = 'fan2_present'

class CelRedstoneXpFan3(CelRedstoneXpFan):
    name = 'Fan3'
    description = 'Fan Tray 3'
    driver_path = CelRedstoneXp_13_4d_path
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']
    fan_present = 'fan3_present'

class CelRedstoneXpFan4(CelRedstoneXpFan):
    name = 'Fan4'
    description = 'Fan Tray 4'
    driver_path = CelRedstoneXp_13_4d_path
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']
    fan_present = 'fan4_present'

class CelRedstoneXpFan5(CelRedstoneXpFan):
    name = 'Fan5'
    description = 'Fan Tray 1'
    driver_path = CelRedstoneXp_13_2e_path
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']
    fan_present = 'fan1_present'

class CelRedstoneXpFan6(CelRedstoneXpFan):
    name = 'Fan6'
    description = 'Fan Tray 2'
    driver_path = CelRedstoneXp_13_2e_path
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']
    fan_present = 'fan2_present'

class CelRedstoneXpFan7(CelRedstoneXpFan):
    name = 'Fan7'
    description = 'Fan Tray 3'
    driver_path = CelRedstoneXp_13_2e_path
    driver_hwmon = ['fan5']
    pwm_hwmon = ['pwm5']
    fan_present = 'fan3_present'

class CelRedstoneXpFan8(CelRedstoneXpFan):
    name = 'Fan8'
    description = 'Fan Tray 4'
    driver_path = CelRedstoneXp_13_2e_path
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']
    fan_present = 'fan4_present'

class CelRedstoneXp_PSU(cumulus.sensors.PSU_Unit):
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

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '1':
            self.attrs[self.psu_present] = 1
        else:
            self.attrs[self.psu_present] = 0
        if self.get_gpio_value(self.psu_all_ok) == '1':
            self.attrs[self.psu_all_ok] = 1
        else:
            self.attrs[self.psu_all_ok] = 0
        return 0

class CelRedstoneXpPSU1(CelRedstoneXp_PSU):
    name = 'PSU1'
    psu_present = 'psu_pwr1_present'
    psu_all_ok = 'psu_pwr1_all_ok'

class CelRedstoneXpPSU2(CelRedstoneXp_PSU):
    name = 'PSU2'
    psu_present = 'psu_pwr2_present'
    psu_all_ok = 'psu_pwr2_all_ok'

class CelRedstoneXpPSUTemp(cumulus.sensors.Temp_Unit):
    def find_and_add_attrs(self):
        if ((self.get_gpio_value(self.temp_present) == '1') and
            (self.get_gpio_value(self.temp_all_ok) == '1')):
            return cumulus.sensors.Temp_Unit.find_and_add_attrs(self)
        else:
           return -1

class CelRedstoneXpTemp9(CelRedstoneXpPSUTemp):
    name = 'PSU2Temp1'
    description = 'PSU2 Inlet Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/11-0059'
    driver_hwmon = ['temp1']
    temp_present = 'psu_pwr2_present'
    temp_all_ok = 'psu_pwr2_all_ok'
    temp_max = 60
    temp_crit = 100

class CelRedstoneXpTemp10(CelRedstoneXpPSUTemp):
    name = 'PSU2Temp2'
    description = 'PSU2 Max Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/11-0059'
    driver_hwmon = ['temp2']
    temp_present = 'psu_pwr2_present'
    temp_all_ok = 'psu_pwr2_all_ok'
    temp_max = 60
    temp_crit = 100

class CelRedstoneXpTemp11(CelRedstoneXpPSUTemp):
    name = 'PSU1Temp1'
    description = 'PSU1 Inlet Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/10-0058'
    driver_hwmon = ['temp1']
    temp_present = 'psu_pwr1_present'
    temp_all_ok = 'psu_pwr1_all_ok'
    temp_max = 60
    temp_crit = 100

class CelRedstoneXpTemp12(CelRedstoneXpPSUTemp):
    name = 'PSU1Temp2'
    description = 'PSU1 Max Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/10-0058'
    driver_hwmon = ['temp2']
    temp_present = 'psu_pwr1_present'
    temp_all_ok = 'psu_pwr1_all_ok'
    temp_max = 60
    temp_crit = 100

class CelRedstoneXpPSUFan(cumulus.sensors.Fan_Unit):
    driver_hwmon = ['fan1']
    rpmmode = 1
    fan_max = 22000
    fan_min = 2000

    def find_and_add_attrs(self):
        if ((self.get_gpio_value(self.fan_present) == '1') and
            (self.get_gpio_value(self.fan_all_ok) == '1')):
            return cumulus.sensors.Fan_Unit.find_and_add_attrs(self)
        else:
           return -1

class CelRedstoneXpFan9(CelRedstoneXpPSUFan):
    name = 'PSU2Fan1'
    description = 'PSU2 Fan'
    driver_path = '/sys/bus/i2c/devices/11-0059'
    fan_present = 'psu_pwr2_present'
    fan_all_ok = 'psu_pwr2_all_ok'

class CelRedstoneXpFan10(CelRedstoneXpPSUFan):
    name = 'PSU1Fan1'
    description = 'PSU1 Fan'
    driver_path = '/sys/bus/i2c/devices/10-0058'
    fan_present = 'psu_pwr1_present'
    fan_all_ok = 'psu_pwr1_all_ok'

class CelRedstoneXpPWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (CelRedstoneXpFan1(),
            CelRedstoneXpFan2(),
            CelRedstoneXpFan3(),
            CelRedstoneXpFan4(),
            CelRedstoneXpFan5(),
            CelRedstoneXpFan6(),
            CelRedstoneXpFan7(),
            CelRedstoneXpFan8(),
    )
    temps = (CelRedstoneXpTemp1(),
             CelRedstoneXpTemp2(),
             CelRedstoneXpTemp3(),
             CelRedstoneXpTemp4(),
             CelRedstoneXpTemp5(),
             CelRedstoneXpTemp6(),
             CelRedstoneXpTemp7(),
             CelRedstoneXpTemp8(),
             )

class CelRedstoneXpPWM2(cumulus.sensors.PWM_Unit):
    name = 'PSU1 PWM'
    fans = (CelRedstoneXpFan10(),
            )
    temps = (CelRedstoneXpTemp11(),
             CelRedstoneXpTemp12(),
             )

class CelRedstoneXpPWM3(cumulus.sensors.PWM_Unit):
    name = 'PSU2 PWM'
    fans = (CelRedstoneXpFan9(),
            )
    temps = (CelRedstoneXpTemp9(),
             CelRedstoneXpTemp10(),
             )

class CelRedstoneXpSensors():
    units = (CelRedstoneXpPSU1(),
             CelRedstoneXpPSU2(),
             CelRedstoneXpTemp1(),
             CelRedstoneXpTemp2(),
             CelRedstoneXpTemp3(),
             CelRedstoneXpTemp4(),
             CelRedstoneXpTemp5(),
             CelRedstoneXpTemp6(),
             CelRedstoneXpTemp7(),
             CelRedstoneXpTemp8(),
             CelRedstoneXpTemp9(),
             CelRedstoneXpTemp10(),
             CelRedstoneXpTemp11(),
             CelRedstoneXpTemp12(),
             CelRedstoneXpFan1(),
             CelRedstoneXpFan2(),
             CelRedstoneXpFan3(),
             CelRedstoneXpFan4(),
             CelRedstoneXpFan5(),
             CelRedstoneXpFan6(),
             CelRedstoneXpFan7(),
             CelRedstoneXpFan8(),
             CelRedstoneXpFan9(),
             CelRedstoneXpFan10(),
            )

class CelRedstoneXpPWMs():
    units = (CelRedstoneXpPWM1(),
             CelRedstoneXpPWM2(),
             CelRedstoneXpPWM3(),
             )

class CelRedstoneXpLEDs():
    units = (CelRedstoneXpPsu1LED(),
             CelRedstoneXpPsu2LED(),
             CelRedstoneXpSystemLED(),
             CelRedstoneXpFan1LED(),
             CelRedstoneXpFan2LED(),
             CelRedstoneXpFan3LED(),
             CelRedstoneXpFan4LED(),
             )

class CelRedstoneXpSwitch(cumulus.platform.BCMSwitch):
    ledup = CelRedstoneXpLED
    _sfp = CelRedstoneXpSFPp
    _qsfp = CelRedstoneXpQSFPp

    has_phy_ucode_mdio = False # XXX unverified
    has_phy_ucode_spi_rom = False # XXX unverified

    ports = (
        _sfp(label="1",  serdes=(12,), leds=(0,  0), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="2",  serdes=(13,), leds=(0,  2)),
        _sfp(label="3",  serdes=(14,), leds=(0,  4), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="4",  serdes=(15,), leds=(0,  6)),
        _sfp(label="5",  serdes=(20,), leds=(0,  8), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="6",  serdes=(21,), leds=(0, 10)),
        _sfp(label="7",  serdes=(22,), leds=(0, 12), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="8",  serdes=(23,), leds=(0, 14)),
        _sfp(label="9",  serdes=(24,), leds=(0, 16), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="10", serdes=(25,), leds=(0, 18)),
        _sfp(label="11", serdes=(26,), leds=(0, 20), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="12", serdes=(27,), leds=(0, 22)),
        _sfp(label="13", serdes=(28,), leds=(0, 24), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="14", serdes=(29,), leds=(0, 26)),
        _sfp(label="15", serdes=(30,), leds=(0, 28), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="16", serdes=(31,), leds=(0, 30)),
        _sfp(label="17", serdes=(44,), leds=(0, 32), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="18", serdes=(45,), leds=(0, 34)),
        _sfp(label="19", serdes=(46,), leds=(0, 36), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="20", serdes=(47,), leds=(0, 38)),
        _sfp(label="21", serdes=(48,), leds=(0, 40), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="22", serdes=(49,), leds=(0, 42)),
        _sfp(label="23", serdes=(50,), leds=(0, 44), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="24", serdes=(51,), leds=(0, 46)),
        _sfp(label="25", serdes=(52,), leds=(0, 48), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="26", serdes=(53,), leds=(0, 50)),
        _sfp(label="27", serdes=(54,), leds=(0, 52), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="28", serdes=(55,), leds=(0, 54)),
        _sfp(label="29", serdes=(56,), leds=(0, 56), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="30", serdes=(57,), leds=(0, 58)),
        _sfp(label="31", serdes=(58,), leds=(0, 60), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="32", serdes=(59,), leds=(0, 62)),
        _sfp(label="33", serdes=(60,), leds=(0, 64), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="34", serdes=(61,), leds=(0, 66)),
        _sfp(label="35", serdes=(62,), leds=(0, 68), rx_polarity_flip=True, tx_polarity_flip=True),
        _sfp(label="36", serdes=(63,), leds=(0, 70)),
        _sfp(label="37", serdes=(64,), leds=(1,  0), rx_polarity_flip=True),
        _sfp(label="38", serdes=(65,), leds=(1,  2), tx_polarity_flip=True),
        _sfp(label="39", serdes=(66,), leds=(1,  4)),
        _sfp(label="40", serdes=(67,), leds=(1,  6), tx_polarity_flip=True),
        _sfp(label="41", serdes=(68,), leds=(1,  8)),
        _sfp(label="42", serdes=(69,), leds=(1, 10), tx_polarity_flip=True),
        _sfp(label="43", serdes=(70,), leds=(1, 12)),
        _sfp(label="44", serdes=(71,), leds=(1, 14), tx_polarity_flip=True),
        _sfp(label="45", serdes=(72,), leds=(1, 16)),
        _sfp(label="46", serdes=(73,), leds=(1, 18), tx_polarity_flip=True),
        _sfp(label="47", serdes=(74,), leds=(1, 20)),
        _sfp(label="48", serdes=(75,), leds=(1, 22), tx_polarity_flip=True),

        _qsfp(label="49", serdes=(76, 77, 78, 79), leds=(1, 24),
		tx_lane_map=0x3012, rx_polarity_flip=0xf, tx_polarity_flip=0x8),
        _qsfp(label="50", serdes=(80, 81, 82, 83), leds=(1, 32),
		tx_lane_map=0x3210, rx_polarity_flip=0xa, tx_polarity_flip=0xf),
        _qsfp(label="51", serdes=( 96, 97, 98, 99), leds=(1, 40),
		tx_lane_map=0x1032, rx_polarity_flip=0xf, tx_polarity_flip=0x0),
        _qsfp(label="52", serdes=( 100, 101, 102, 103), leds=(1, 48),
		tx_lane_map=0x3210, rx_polarity_flip=0xf, tx_polarity_flip=0xf),
        _qsfp(label="53", serdes=( 104, 105, 106, 107), leds=(1, 56),
		tx_lane_map=0x1032, rx_polarity_flip=0xf, tx_polarity_flip=0x0),
        _qsfp(label="54", serdes=( 108, 109, 110, 111), leds=(1, 64),
		tx_lane_map=0x1230, rx_polarity_flip=0xa, tx_polarity_flip=0x7),
    )


class CelRedstoneXp(cumulus.platform.Platform):
    name = 'cel,redstone_xp'
    switch = CelRedstoneXpSwitch(cumulus.platform.TridentTwo_56854_Chip())
    cpld = CelRedstoneXpCPLD()
    statusleds = CelRedstoneXpLEDs()
    pwms = CelRedstoneXpPWMs()
    sensors = CelRedstoneXpSensors()

# Celestica Smallstone

class CelSmallstoneQSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; CelSmallstoneQSFPp
;;; Two bits per port: yellow(active high), green(active high)
set_led:
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

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
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

SUB_INTF_ACTIVITY       equ     0x0  ; activity
SUB_INTF_LINKEN         equ     0x1  ; link enabled

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

;;; CelSmallstoneQSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active high), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:

        ;;; initialize B
        ld      b,0

        ;;; load sub-0 info
        call    sub_intf_info

        ;;; load sub-1 info
        inc     a
        call    sub_intf_info

        ;;; load sub-2 info
        inc     a
        call    sub_intf_info

        ;;; load sub-3 info
        inc     a
        call    sub_intf_info

        ;;; push accumlated link activity onto stack
        tst     B, SUB_INTF_ACTIVITY
        push    cy

        ;;; combine with BLINK state
        push    (BLINK_STATE_P)
        tand
        tinv    ; flash off with activity

        ;;; push accumlated link enable onto stack
        tst     B, SUB_INTF_LINKEN
        push    cy

        ;;; AND activity-blink state with accumlated LINKEN
        tand

        ;;; LEDs are active low
        tinv
        pack

        port 1
        pushst  PORTSTATUS_ZERO ; disable yellow LED
        pack

        ret
'''
    def __init__(self, label, serdes, leds, rx_lane_map, tx_lane_map,
                 rx_polarity_flip=None, tx_polarity_flip=None):
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
        set_calls[led_index_list[0]] = call
        set_calls[led_index_list[0] + 1] = None

        return set_calls

class CelSmallstoneLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 32

class CelSmallstoneSwitch(cumulus.platform.BCMSwitch):
    ledup = CelSmallstoneLED
    _qsfp = CelSmallstoneQSFPp

    has_phy_ucode_mdio = False # XXX unverified
    has_phy_ucode_spi_rom = False # XXX unverified

    ports = (
        _qsfp(label="1", serdes=(  0,   1,   2,   3), leds=(0, 0),
              rx_lane_map=0x3120, tx_lane_map=0x2031,
              tx_polarity_flip=0x000F, rx_polarity_flip=0x000F),
        _qsfp(label="2", serdes=(  4,   5,   6,   7), leds=(0, 2),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="3", serdes=(  8,   9,  10,  11), leds=(0, 4),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000D, rx_polarity_flip=0x000F),
        _qsfp(label="4", serdes=( 12,  13,  14,  15), leds=(0, 6),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="5", serdes=( 16,  17,  18,  19), leds=(0, 8),
              rx_lane_map=0x3120, tx_lane_map=0x2031,
              tx_polarity_flip=0x000F, rx_polarity_flip=0x000F),
        _qsfp(label="6", serdes=( 20,  21,  22,  23), leds=(0, 10),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="7", serdes=( 24,  25,  26,  27), leds=(0, 12),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000D, rx_polarity_flip=0x000F),
        _qsfp(label="8", serdes=( 28,  29,  30,  31), leds=(0, 14),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="9", serdes=( 32,  33,  34,  35), leds=(0, 16),
              rx_lane_map=0x3120, tx_lane_map=0x2031,
              tx_polarity_flip=0x000F, rx_polarity_flip=0x000F),
        _qsfp(label="10", serdes=( 36,  37,  38,  39), leds=(0, 18),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="11", serdes=( 40,  41,  42,  43), leds=(0, 20),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000D, rx_polarity_flip=0x000F),
        _qsfp(label="12", serdes=( 44,  45,  46,  47), leds=(0, 22),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="13", serdes=( 48,  49,  50,  51), leds=(0, 24),
              rx_lane_map=0x3120, tx_lane_map=0x2031,
              tx_polarity_flip=0x000F, rx_polarity_flip=0x000F),
        _qsfp(label="14", serdes=( 52,  53,  54,  55), leds=(0, 26),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="15", serdes=( 56,  57,  58,  59), leds=(0, 28),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000D, rx_polarity_flip=0x000F),
        _qsfp(label="16", serdes=( 60,  61,  62,  63), leds=(0, 30),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x000C, rx_polarity_flip=0x000F),
        _qsfp(label="17", serdes=( 64,  65,  66,  67), leds=(1, 0),
              rx_lane_map=0x3120, tx_lane_map=0x2031,
              tx_polarity_flip=None, rx_polarity_flip=None),
        _qsfp(label="18", serdes=( 68,  69,  70,  71), leds=(1, 2),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="19", serdes=( 72,  73,  74,  75), leds=(1, 4),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x0002, rx_polarity_flip=None),
        _qsfp(label="20", serdes=( 76,  77,  78,  79), leds=(1, 6),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="21", serdes=( 80,  81,  82,  83), leds=(1, 8),
              rx_lane_map=0x3120, tx_lane_map=0x3120,
              tx_polarity_flip=None, rx_polarity_flip=None),
        _qsfp(label="22", serdes=( 84,  85,  86,  87), leds=(1, 10),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="23", serdes=( 88,  89,  90,  91), leds=(1, 12),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0002, rx_polarity_flip=None),
        _qsfp(label="24", serdes=( 92,  93,  94,  95), leds=(1, 14),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="25", serdes=( 96,  97,  98,  99), leds=(1, 16),
              rx_lane_map=0x3120, tx_lane_map=0x3120,
              tx_polarity_flip=None, rx_polarity_flip=None),
        _qsfp(label="26", serdes=(100, 101, 102, 103), leds=(1, 18),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="27", serdes=(104, 105, 106, 107), leds=(1, 20),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0002, rx_polarity_flip=None),
        _qsfp(label="28", serdes=(108, 109, 110, 111), leds=(1, 22),
              rx_lane_map=0x2031, tx_lane_map=0x1302,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="29", serdes=(112, 113, 114, 115), leds=(1, 24),
              rx_lane_map=0x3120, tx_lane_map=0x3120,
              tx_polarity_flip=None, rx_polarity_flip=None),
        _qsfp(label="30", serdes=(116, 117, 118, 119), leds=(1, 26),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
        _qsfp(label="31", serdes=(120, 121, 122, 123), leds=(1, 28),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x0002, rx_polarity_flip=None),
        _qsfp(label="32", serdes=(124, 125, 126, 127), leds=(1, 30),
              rx_lane_map=0x2031, tx_lane_map=0x0213,
              tx_polarity_flip=0x0003, rx_polarity_flip=None),
    )

class CelSmallstoneCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ffe05000.localbus/ffb00000.CPLD1'

class CelSmallstonePSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    cpld_hwmon = ['psu_pwr1']

class CelSmallstonePSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    cpld_hwmon = ['psu_pwr2']

class CelSmallstoneTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = 'Front Right Corner Ambient Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03000.i2c/i2c-0/0-004b'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelSmallstoneTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'P2020 Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0048'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 65
    temp_crit = 73

class CelSmallstoneTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'System Rear Outlet Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0049'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelSmallstoneTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004e'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 65
    temp_crit = 80

class CelSmallstoneTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'Front Left Corner Ambient Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004f'
    driver_hwmon = ['temp1']
    temp_max_hyst = 25
    temp_max = 45
    temp_crit = 65

class CelSmallstoneFan1(cumulus.sensors.Fan_Unit):
    name = 'Fan1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan1']
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']

class CelSmallstoneFan2(cumulus.sensors.Fan_Unit):
    name = 'Fan2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan2']
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']

class CelSmallstoneFan3(cumulus.sensors.Fan_Unit):
    name = 'Fan3'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan3']
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']

class CelSmallstoneFan4(cumulus.sensors.Fan_Unit):
    name = 'Fan4'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan4']
    driver_hwmon = ['fan4']
    pwm_hwmon = ['pwm4']

class CelSmallstoneFan5(cumulus.sensors.Fan_Unit):
    name = 'Fan5'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'
    cpld_hwmon = ['fan5']
    driver_hwmon = ['fan5']
    pwm_hwmon = ['pwm5']

class CelSmallstonePWM1(cumulus.sensors.PWM_Unit):
    fans = (CelSmallstoneFan1(),
            CelSmallstoneFan2(),
            CelSmallstoneFan3(),
	    CelSmallstoneFan4(),
	    CelSmallstoneFan5(),
            )
    temps = (CelSmallstoneTemp1(),
             CelSmallstoneTemp2(),
             CelSmallstoneTemp3(),
             CelSmallstoneTemp4(),
             CelSmallstoneTemp5(),
             )

class CelSmallstoneSensors():
    units = ( CelSmallstonePSU1(),
              CelSmallstonePSU2(),
              CelSmallstoneFan1(),
              CelSmallstoneFan2(),
              CelSmallstoneFan3(),
	      CelSmallstoneFan4(),
	      CelSmallstoneFan5(),
              CelSmallstoneTemp1(),
              CelSmallstoneTemp2(),
              CelSmallstoneTemp3(),
              CelSmallstoneTemp4(),
              CelSmallstoneTemp5(),
              )

class CelSmallstonePWMs():
    units = (CelSmallstonePWM1(),
             )

class CelSmallstoneSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_status'
    bad_led_color = 'green_blinking'

class CelSmallstoneLEDs():
    units = (CelSmallstoneSystemLED(),
             )

class CelSmallstone(cumulus.platform.Platform):
    name = 'cel,smallstone'
    switch = CelSmallstoneSwitch(cumulus.platform.TridentTwo_56850_Chip())
    cpld = CelSmallstoneCPLD()
    statusleds = CelSmallstoneLEDs()
    pwms = CelSmallstonePWMs()
    sensors = CelSmallstoneSensors()

# Celestica Smallstone XP

class CelSmallstoneXpQSFPp(cumulus.platform.TridentTwo40GPort):
    _set_led = '''
;;; CelSmallstoneXpQSFPp
;;; Each port on the Smallstone XP uses two bits, they
;;;  behave as follows:
;;;
;;;                  bit 0
;;;                0        1
;;;            +--------+-------+
;;;          0 | green  |  off  |
;;;   bit 1    +--------+-------+
;;;          1 | amber  |  off  |
;;;            +--------+-------+
;;;
;;; For 40G mode, we use only the first LED to indicate link/activity.
;;; The other 3 LEDs will be off.
;;;
set_led:
        call    set_any_led    ; set the first led green/off

        push    PORTSTATUS_ONE ; 1, 1 => led 2 off
        pack
        push    PORTSTATUS_ZERO
        pack

        push    PORTSTATUS_ONE ; 1, 1 => led 3 off
        pack
        push    PORTSTATUS_ZERO
        pack

        push    PORTSTATUS_ONE ; 1, 1 => led 4 off
        pack
        push    PORTSTATUS_ZERO
        pack

        ret

set_any_led:
;;; The first bit will indicate link/activity (low active)
;;; The second bit will always be 0
;;;
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

        port 1
        pushst  PORTSTATUS_ZERO
        pack

        ret
'''
    _set_led_4x10 = '''
;;; CelSmallstoneXpQSFPp_4x10
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

    def __init__(self, label, serdes, leds, rx_lane_map, tx_lane_map,
                 rx_polarity_flip=None, tx_polarity_flip=None):
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
        set_calls[led_index_list[0]+1] = None
        set_calls[led_index_list[0]+2] = None
        set_calls[led_index_list[0]+3] = None
        set_calls[led_index_list[0]+4] = None
        set_calls[led_index_list[0]+5] = None
        set_calls[led_index_list[0]+6] = None
        set_calls[led_index_list[0]+7] = None

        return set_calls

class CelSmallstoneXpLED(cumulus.ledup.TridentTwoLEDController):
    num_leds = 128

class CelSmallstoneXpCPLD(cumulus.cpld.SysFS):
    path = '/sys/bus/platform/devices/cel_smallstone_xp_cpld.0'

'''
   Celestica Smallstone XP LEDs
       System:
         green - all systems ok
         green blinking - fan missing or broken, psu missing or broken
       PSU1:
         green - psu1 installed and working
         off - psu1 missing or broken
       PSU2:
         green - psu2 installed and working
         off - psu2 missing or broken
       Fan1:
         green - fan installed and working
         off - fan missing or broken
       Fan2:
         green - fan installed and working
         off - fan missing or broken
       Fan3:
         green - fan installed and working
         off - fan missing or broken
       Fan4:
         green - fan installed and working
         off - fan missing or broken
'''

class CelSmallstoneXpSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'Status'
    led_location = 'led_status'
    bad_led_color = 'green_blinking'

class CelSmallstoneXpPsu1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Psu1'
    sources = ['PSU1']
    led_location = 'led_psu1'
    bad_led_color = 'off'

class CelSmallstoneXpPsu2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Psu2'
    sources = ['PSU2']
    led_location = 'led_psu2'
    bad_led_color = 'off'

class CelSmallstoneXpFanLED(cumulus.sensors.StatusLED_Unit):
    bad_led_color = 'off'
    colormap = {'green':'1', 'off':'0', '0':'off', '1':'green'}

    def led_update(self, color):
        self.set_gpio_value(self.led_location, self.colormap[color])

    def led_read(self):
        color = self.get_gpio_value(self.led_location)
        return self.name, self.colormap[color]

class CelSmallstoneXpFan1LED(CelSmallstoneXpFanLED):
    name = 'Fan Tray 1'
    sources = ['Fan1', 'Fan6']
    led_location = 'led_fan1_green'

class CelSmallstoneXpFan2LED(CelSmallstoneXpFanLED):
    name = 'Fan Tray 2'
    sources = ['Fan2', 'Fan7']
    led_location = 'led_fan2_green'

class CelSmallstoneXpFan3LED(CelSmallstoneXpFanLED):
    name = 'Fan Tray 3'
    sources = ['Fan3', 'Fan8']
    led_location = 'led_fan3_green'

class CelSmallstoneXpFan4LED(CelSmallstoneXpFanLED):
    name = 'Fan Tray 4'
    sources = ['Fan4', 'Fan9']
    led_location = 'led_fan4_green'

class CelSmallstoneXpFan5LED(CelSmallstoneXpFanLED):
    name = 'Fan Tray 5'
    sources = ['Fan5', 'Fan10']
    led_location = 'led_fan5_green'

# This sensor is giving low temperature (0-05C) readings at a customer site.
# Chances are this sensor is broken. So commenting it out of smond and pwmd.
# class CelSmallstoneXpTemp1(cumulus.sensors.Temp_Unit):
#     name = 'Temp1'
#     description = 'Intel CPU external sensor'
#     driver_path = '/sys/bus/i2c/devices/14-0048'
#     temp_crit = 70
#     temp_max = 65

class CelSmallstoneXpTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = 'Rear Outlet Air sensor'
    driver_path = '/sys/bus/i2c/devices/15-004e'
    temp_crit = 60
    temp_max = 48
    temp_min = -10
    temp_lcrit = -15

class CelSmallstoneXpTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'Front Outlet Air sensor'
    driver_path = '/sys/bus/i2c/devices/24-0049'
    temp_crit = 60
    temp_max = 48
    temp_min = -10
    temp_lcrit = -15

class CelSmallstoneXpTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/bus/i2c/devices/23-0048'
    temp_crit = 80
    temp_max = 75

CelSmallstoneXp_core_path = '/sys/devices/platform/coretemp.0'
class CelSmallstoneXpTemp5(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'Intel CPU die sensor'
    driver_path = CelSmallstoneXp_core_path
    driver_hwmon = ['temp2']
    temp_crit = 98

class CelSmallstoneXpTemp6(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = 'Intel CPU die sensor'
    driver_path = CelSmallstoneXp_core_path
    driver_hwmon = ['temp3']
    temp_crit = 98

class CelSmallstoneXpTemp7(cumulus.sensors.Temp_Unit):
    name = 'Temp6'
    description = 'Intel CPU die sensor'
    driver_path = CelSmallstoneXp_core_path
    driver_hwmon = ['temp4']
    temp_crit = 98

class CelSmallstoneXpTemp8(cumulus.sensors.Temp_Unit):
    name = 'Temp7'
    description = 'Intel CPU die sensor'
    driver_path = CelSmallstoneXp_core_path
    driver_hwmon = ['temp5']
    temp_crit = 98

CelSmallstoneXp_13_4d_path = '/sys/bus/i2c/devices/13-004d'
CelSmallstoneXp_13_2e_path = '/sys/bus/i2c/devices/13-002e'

class CelSmallstoneXpFan(cumulus.sensors.Fan_Unit):
    fan_min = 1000
    fan_max = 25000

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.fan_present) == '1':
            self.attrs['fan_0'] = 'installed, ok'
        else:
            self.attrs['fan_0'] = 'not_installed'
        cumulus.sensors.Fan_Unit.find_and_add_attrs(self)

class CelSmallstoneXpFan1(CelSmallstoneXpFan):
    name = 'Fan1'
    description = 'Fan Tray 1'
    driver_path = CelSmallstoneXp_13_4d_path
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']
    fan_present = 'fan1_present'

class CelSmallstoneXpFan2(CelSmallstoneXpFan):
    name = 'Fan2'
    description = 'Fan Tray 2'
    driver_path = CelSmallstoneXp_13_4d_path
    driver_hwmon = ['fan4']
    pwm_hwmon = ['pwm4']
    fan_present = 'fan2_present'

class CelSmallstoneXpFan3(CelSmallstoneXpFan):
    name = 'Fan3'
    description = 'Fan Tray 3'
    driver_path = CelSmallstoneXp_13_4d_path
    driver_hwmon = ['fan5']
    pwm_hwmon = ['pwm5']
    fan_present = 'fan3_present'

class CelSmallstoneXpFan4(CelSmallstoneXpFan):
    name = 'Fan4'
    description = 'Fan Tray 4'
    driver_path = CelSmallstoneXp_13_4d_path
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']
    fan_present = 'fan4_present'

class CelSmallstoneXpFan5(CelSmallstoneXpFan):
    name = 'Fan6'
    description = 'Fan Tray 1'
    driver_path = CelSmallstoneXp_13_2e_path
    driver_hwmon = ['fan2']
    pwm_hwmon = ['pwm2']
    fan_present = 'fan1_present'

class CelSmallstoneXpFan6(CelSmallstoneXpFan):
    name = 'Fan7'
    description = 'Fan Tray 2'
    driver_path = CelSmallstoneXp_13_2e_path
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']
    fan_present = 'fan2_present'

class CelSmallstoneXpFan7(CelSmallstoneXpFan):
    name = 'Fan8'
    description = 'Fan Tray 3'
    driver_path = CelSmallstoneXp_13_2e_path
    driver_hwmon = ['fan4']
    pwm_hwmon = ['pwm4']
    fan_present = 'fan3_present'

class CelSmallstoneXpFan8(CelSmallstoneXpFan):
    name = 'Fan9'
    description = 'Fan Tray 4'
    driver_path = CelSmallstoneXp_13_2e_path
    driver_hwmon = ['fan5']
    pwm_hwmon = ['pwm5']
    fan_present = 'fan4_present'

class CelSmallstoneXpFan11(CelSmallstoneXpFan):
    name = 'Fan5'
    description = 'Fan Tray 5'
    driver_path = CelSmallstoneXp_13_4d_path
    driver_hwmon = ['fan1']
    pwm_hwmon = ['pwm1']
    fan_present = 'fan5_present'

class CelSmallstoneXpFan12(CelSmallstoneXpFan):
    name = 'Fan10'
    description = 'Fan Tray 5'
    driver_path = CelSmallstoneXp_13_2e_path
    driver_hwmon = ['fan3']
    pwm_hwmon = ['pwm3']
    fan_present = 'fan5_present'

class CelSmallstoneXp_PSU(cumulus.sensors.PSU_Unit):
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

    def find_and_add_attrs(self):
        if self.get_gpio_value(self.psu_present) == '1':
            self.attrs[self.psu_present] = 1
        else:
            self.attrs[self.psu_present] = 0
        if self.get_gpio_value(self.psu_all_ok) == '1':
            self.attrs[self.psu_all_ok] = 1
        else:
            self.attrs[self.psu_all_ok] = 0
        return 0

class CelSmallstoneXpPSU1(CelSmallstoneXp_PSU):
    name = 'PSU1'
    psu_present = 'psu_pwr1_present'
    psu_all_ok = 'psu_pwr1_all_ok'

class CelSmallstoneXpPSU2(CelSmallstoneXp_PSU):
    name = 'PSU2'
    psu_present = 'psu_pwr2_present'
    psu_all_ok = 'psu_pwr2_all_ok'

class CelSmallstoneXpPSUTemp(cumulus.sensors.Temp_Unit):
    def find_and_add_attrs(self):
        if ((self.get_gpio_value(self.temp_present) == '1') and
            (self.get_gpio_value(self.temp_all_ok) == '1')):
            return cumulus.sensors.Temp_Unit.find_and_add_attrs(self)
        else:
           return -1

class CelSmallstoneXpTemp9(CelSmallstoneXpPSUTemp):
    name = 'PSU2Temp1'
    description = 'PSU2 Inlet Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/11-0059'
    driver_hwmon = ['temp1']
    temp_present = 'psu_pwr2_present'
    temp_all_ok = 'psu_pwr2_all_ok'
    temp_max = 60
    temp_crit = 100

class CelSmallstoneXpTemp10(CelSmallstoneXpPSUTemp):
    name = 'PSU2Temp2'
    description = 'PSU2 Max Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/11-0059'
    driver_hwmon = ['temp2']
    temp_present = 'psu_pwr2_present'
    temp_all_ok = 'psu_pwr2_all_ok'
    temp_max = 60
    temp_crit = 100

class CelSmallstoneXpTemp11(CelSmallstoneXpPSUTemp):
    name = 'PSU1Temp1'
    description = 'PSU1 Inlet Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/10-0058'
    driver_hwmon = ['temp1']
    temp_present = 'psu_pwr1_present'
    temp_all_ok = 'psu_pwr1_all_ok'
    temp_max = 60
    temp_crit = 100

class CelSmallstoneXpTemp12(CelSmallstoneXpPSUTemp):
    name = 'PSU1Temp2'
    description = 'PSU1 Max Temp Sensor'
    driver_path = '/sys/bus/i2c/devices/10-0058'
    driver_hwmon = ['temp2']
    temp_present = 'psu_pwr1_present'
    temp_all_ok = 'psu_pwr1_all_ok'
    temp_max = 60
    temp_crit = 100

class CelSmallstoneXpPSUFan(cumulus.sensors.Fan_Unit):
    driver_hwmon = ['fan1']
    rpmmode = 1
    fan_max = 22000
    fan_min = 2000

    def find_and_add_attrs(self):
        if ((self.get_gpio_value(self.fan_present) == '1') and
            (self.get_gpio_value(self.fan_all_ok) == '1')):
            return cumulus.sensors.Fan_Unit.find_and_add_attrs(self)
        else:
           return -1

class CelSmallstoneXpFan9(CelSmallstoneXpPSUFan):
    name = 'PSU2Fan1'
    description = 'PSU2 Fan'
    driver_path = '/sys/bus/i2c/devices/11-0059'
    fan_present = 'psu_pwr2_present'
    fan_all_ok = 'psu_pwr2_all_ok'

class CelSmallstoneXpFan10(CelSmallstoneXpPSUFan):
    name = 'PSU1Fan1'
    description = 'PSU1 Fan'
    driver_path = '/sys/bus/i2c/devices/10-0058'
    fan_present = 'psu_pwr1_present'
    fan_all_ok = 'psu_pwr1_all_ok'

class CelSmallstoneXpPWM1(cumulus.sensors.PWM_Unit):
    name = 'System PWM'
    fans = (CelSmallstoneXpFan1(),
            CelSmallstoneXpFan2(),
            CelSmallstoneXpFan3(),
            CelSmallstoneXpFan4(),
            CelSmallstoneXpFan11(),
            CelSmallstoneXpFan5(),
            CelSmallstoneXpFan6(),
            CelSmallstoneXpFan7(),
            CelSmallstoneXpFan8(),
            CelSmallstoneXpFan12(),
    )
    temps = (CelSmallstoneXpTemp2(),
             CelSmallstoneXpTemp3(),
             CelSmallstoneXpTemp4(),
             CelSmallstoneXpTemp5(),
             CelSmallstoneXpTemp6(),
             CelSmallstoneXpTemp7(),
             CelSmallstoneXpTemp8(),
             )

class CelSmallstoneXpPWM2(cumulus.sensors.PWM_Unit):
    name = 'PSU1 PWM'
    fans = (CelSmallstoneXpFan10(),
            )
    temps = (CelSmallstoneXpTemp11(),
             CelSmallstoneXpTemp12(),
             )

class CelSmallstoneXpPWM3(cumulus.sensors.PWM_Unit):
    name = 'PSU2 PWM'
    fans = (CelSmallstoneXpFan9(),
            )
    temps = (CelSmallstoneXpTemp9(),
             CelSmallstoneXpTemp10(),
             )

class CelSmallstoneXpSensors():
    units = (CelSmallstoneXpPSU1(),
             CelSmallstoneXpPSU2(),
             CelSmallstoneXpTemp2(),
             CelSmallstoneXpTemp3(),
             CelSmallstoneXpTemp4(),
             CelSmallstoneXpTemp9(),
             CelSmallstoneXpTemp5(),
             CelSmallstoneXpTemp6(),
             CelSmallstoneXpTemp7(),
             CelSmallstoneXpTemp8(),
             CelSmallstoneXpTemp10(),
             CelSmallstoneXpTemp11(),
             CelSmallstoneXpTemp12(),
             CelSmallstoneXpFan1(),
             CelSmallstoneXpFan2(),
             CelSmallstoneXpFan3(),
             CelSmallstoneXpFan4(),
             CelSmallstoneXpFan5(),
             CelSmallstoneXpFan6(),
             CelSmallstoneXpFan7(),
             CelSmallstoneXpFan8(),
             CelSmallstoneXpFan9(),
             CelSmallstoneXpFan10(),
             CelSmallstoneXpFan11(),
             CelSmallstoneXpFan12(),
            )

class CelSmallstoneXpPWMs():
    units = (CelSmallstoneXpPWM1(),
             CelSmallstoneXpPWM2(),
             CelSmallstoneXpPWM3(),
             )

class CelSmallstoneXpLEDs():
    units = (CelSmallstoneXpPsu1LED(),
             CelSmallstoneXpPsu2LED(),
             CelSmallstoneXpSystemLED(),
             CelSmallstoneXpFan1LED(),
             CelSmallstoneXpFan2LED(),
             CelSmallstoneXpFan3LED(),
             CelSmallstoneXpFan4LED(),
             CelSmallstoneXpFan5LED(),
             )

class CelSmallstoneXpSwitch(cumulus.platform.BCMSwitch):
    ledup = CelSmallstoneXpLED
    _qsfp = CelSmallstoneXpQSFPp

    has_phy_ucode_mdio = False # XXX unverified
    has_phy_ucode_spi_rom = False # XXX unverified

    ports = (
        _qsfp(label="1", serdes=(  0,   1,   2,   3), leds=(0, 0),
              tx_polarity_flip=0x0007, rx_polarity_flip=0x000f,
              rx_lane_map=0x3120, tx_lane_map=0x2031),
        _qsfp(label="2", serdes=(  4,   5,   6,   7), leds=(0, 8),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x0213),
        _qsfp(label="3", serdes=(  8,   9,  10,  11), leds=(0, 16),
              tx_polarity_flip=0x0005, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x3012),
        _qsfp(label="4", serdes=( 12,  13,  14,  15), leds=(0, 24),
              tx_polarity_flip=0x0002, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x1203),
        _qsfp(label="5", serdes=( 16,  17,  18,  19), leds=(0, 32),
              tx_polarity_flip=0x0007, rx_polarity_flip=0x000b,
              rx_lane_map=0x3120, tx_lane_map=0x2031),
        _qsfp(label="6", serdes=( 20,  21,  22,  23), leds=(0, 40),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x0213),
        _qsfp(label="7", serdes=( 24,  25,  26,  27), leds=(0, 48),
              tx_polarity_flip=0x0005, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x3012),
        _qsfp(label="8", serdes=( 28,  29,  30,  31), leds=(0, 56),
              tx_polarity_flip=0x0002, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x1203),
        _qsfp(label="9", serdes=( 32,  33,  34,  35), leds=(0, 64),
              tx_polarity_flip=0x0007, rx_polarity_flip=0x000b,
              rx_lane_map=0x3120, tx_lane_map=0x2031),
        _qsfp(label="10", serdes=( 36,  37,  38,  39), leds=(0, 72),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x0213),
        _qsfp(label="11", serdes=( 40,  41,  42,  43), leds=(0, 80),
              tx_polarity_flip=0x0005, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x3012),
        _qsfp(label="12", serdes=( 44,  45,  46,  47), leds=(0, 88),
              tx_polarity_flip=0x0002, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x1203),
        _qsfp(label="13", serdes=( 48,  49,  50,  51), leds=(0, 96),
              tx_polarity_flip=0x0007, rx_polarity_flip=0x000b,
              rx_lane_map=0x3120, tx_lane_map=0x2031),
        _qsfp(label="14", serdes=( 52,  53,  54,  55), leds=(0, 104),
              tx_polarity_flip=0x000b, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x0213),
        _qsfp(label="15", serdes=( 56,  57,  58,  59), leds=(0, 112),
              tx_polarity_flip=0x000f, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x3012),
        _qsfp(label="16", serdes=( 60,  61,  62,  63), leds=(0, 120),
              tx_polarity_flip=0x000b, rx_polarity_flip=0x000f,
              rx_lane_map=0x2031, tx_lane_map=0x1203),
        _qsfp(label="17", serdes=( 64,  65,  66,  67), leds=(1, 0),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x0005,
              rx_lane_map=0x3120, tx_lane_map=0x2031),
        _qsfp(label="18", serdes=( 68,  69,  70,  71), leds=(1, 8),
              tx_polarity_flip=0x0007,
              rx_lane_map=0x2031, tx_lane_map=0x0213),
        _qsfp(label="19", serdes=( 72,  73,  74,  75), leds=(1, 16),
              tx_polarity_flip=0x000a,
              rx_lane_map=0x2031, tx_lane_map=0x3012),
        _qsfp(label="20", serdes=( 76,  77,  78,  79), leds=(1, 24),
              tx_polarity_flip=0x000d,
              rx_lane_map=0x2031, tx_lane_map=0x0312),
        _qsfp(label="21", serdes=( 80,  81,  82,  83), leds=(1, 32),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x0004,
              rx_lane_map=0x3120, tx_lane_map=0x3120),
        _qsfp(label="22", serdes=( 84,  85,  86,  87), leds=(1, 40),
              tx_polarity_flip=0x0007,
              rx_lane_map=0x2031, tx_lane_map=0x1302),
        _qsfp(label="23", serdes=( 88,  89,  90,  91), leds=(1, 48),
              tx_polarity_flip=0x000a,
              rx_lane_map=0x2031, tx_lane_map=0x2103),
        _qsfp(label="24", serdes=( 92,  93,  94,  95), leds=(1, 56),
              tx_polarity_flip=0x000d,
              rx_lane_map=0x2031, tx_lane_map=0x0312),
        _qsfp(label="25", serdes=( 96,  97,  98,  99), leds=(1, 64),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x0004,
              rx_lane_map=0x3120, tx_lane_map=0x3120),
        _qsfp(label="26", serdes=(100, 101, 102, 103), leds=(1, 72),
              tx_polarity_flip=0x0007,
              rx_lane_map=0x2031, tx_lane_map=0x1302),
        _qsfp(label="27", serdes=(104, 105, 106, 107), leds=(1, 80),
              tx_polarity_flip=0x000a,
              rx_lane_map=0x2031, tx_lane_map=0x2103),
        _qsfp(label="28", serdes=(108, 109, 110, 111), leds=(1, 88),
              tx_polarity_flip=0x000d,
              rx_lane_map=0x2031, tx_lane_map=0x0312),
        _qsfp(label="29", serdes=(112, 113, 114, 115), leds=(1, 96),
              tx_polarity_flip=0x0008, rx_polarity_flip=0x0004,
              rx_lane_map=0x3120, tx_lane_map=0x3120),
        _qsfp(label="30", serdes=(116, 117, 118, 119), leds=(1, 104),
              tx_polarity_flip=0x0007,
              rx_lane_map=0x2031, tx_lane_map=0x0213),
        _qsfp(label="31", serdes=(120, 121, 122, 123), leds=(1, 112),
              tx_polarity_flip=0x000a,
              rx_lane_map=0x2031, tx_lane_map=0x3012),
        _qsfp(label="32", serdes=(124, 125, 126, 127), leds=(1, 120),
              tx_polarity_flip=0x000d,
              rx_lane_map=0x2031, tx_lane_map=0x1203),
    )

class CelSmallstoneXp(cumulus.platform.Platform):
    name = 'cel,smallstone_xp'
    switch = CelSmallstoneXpSwitch(cumulus.platform.TridentTwo_56850_Chip())
    cpld = CelSmallstoneXpCPLD()
    statusleds = CelSmallstoneXpLEDs()
    pwms = CelSmallstoneXpPWMs()
    sensors = CelSmallstoneXpSensors()
