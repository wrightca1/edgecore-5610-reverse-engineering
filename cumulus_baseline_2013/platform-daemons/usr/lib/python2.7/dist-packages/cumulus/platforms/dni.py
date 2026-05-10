#
# Copyright 2012.  Cumulus Networks, Inc.
#
# dni.py --
#     DNI switch platforms
#
import os
import subprocess
import cumulus.platform
import cumulus.cpld
import cumulus.ledup
import cumulus.sunit
import cumulus.sfp
import cumulus.sensors

class DNI7448QSFPp(cumulus.platform.Trident40GPort):
    _set_led = '''
; DNI7448QSFPp - single led for activity and link
set_led:
        port	a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        tinv                    ; LEDs are active low
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

;;; DNI7448QSFPp_4x10
;;; OR together status of 4 ports for 4x10G QSFP port
;;; Two LED bits per port: yellow(active low), green(active low)
;;; Input: register A - first logical port of 4-port group
;;; Modified: register B - used as scratch space
set_led:
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
    def __init__(self, label, serdes, phy_addrs, leds):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=("84740",) * 4,
                                                 phy_addrs=phy_addrs,
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMBCM(phy_addrs[0], 'qsfp+')
    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}


        if (mode == "4x10G") and (sub != 0):
            # For 4x10G mode only update LEDs for the first
            # sub-interface.
            return set_calls

        fn_name = '%s' % self.__class__.__name__
        led_port = self.hw_port_num(mode, 0)
        if mode == "4x10G":
            call = (fn_name + "_4x10", self._set_led_4x10, led_port)
        elif mode == "40G":
            call = (fn_name, self._set_led, led_port)

        set_calls[led_index_list[0]] = call

        return set_calls

class DNI7448SFPp(cumulus.platform.Trident10GPort):
    _set_led = '''
; DNI7448SFPp - single led for activity and link
set_led:
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
        tinv                    ; LEDs are active low
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
        self.sfp = cumulus.sfp.SFPROMBCM(phy_addr, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        for led in led_index_list:
            set_calls[led] = call

        return set_calls

class DNI6448SFP(cumulus.platform.Triumph10GPort):
    def __init__(self, label, hw_port, phy_addr, leds):
        cumulus.platform.Triumph10GPort.__init__(self,
                                                 label=label,
                                                 hw_port=hw_port,
                                                 phy_type="8706",
                                                 phy_addr=phy_addr,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 unit=0)
        self.sfp = cumulus.sfp.SFPROMDTSWalk(label, 'sfp+')

    _set_led = '''
; DNI6448SFP - single led for activity and link
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
        tinv                    ; LEDs are active low
        pack

        ret
'''
    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s' % self.__class__.__name__
        call = (fn_name, self._set_led, self.hw_port_num(mode, 0))
        for led in led_index_list:
            set_calls[led] = call

        return set_calls


class DNI6448CPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/e0005000.localbus/fa000000.cpld'
    types = { 'port_raw_ctrl' : 'L' }

class DNI6448GigE(cumulus.platform.Triumph1GPort):
    def __init__(self, label, hw_port, phy_addr):
        cumulus.platform.Triumph1GPort.__init__(self,
                                                label=label,
                                                hw_port=hw_port,
                                                phy_type="54680",
                                                phy_addr=phy_addr,
                                                phy_layer='1GBaseT',
                                                leds=None,
                                                unit=0)

class DNI6448Combo(cumulus.platform.Triumph1GPort):
    modes = ('RJ45', 'SFP')
    default_mode = modes[0]
    _speed_map = { 'RJ45' : 1,
                   'SFP'  : 1 }
    _combo_map = { 'RJ45' : 'copper',
                   'SFP'  : 'fiber' }
    _set_led_rj45 = '''
; DNI6448Combo - two bi-color LEDs for activity and link
set_led:
        port    a

        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        tinv                    ; active low
        pack

        pushst  PORTSTATUS_ONE  ; high side of bi-color LED
        pack
        pushst  PORTSTATUS_LINKEN
        tinv                    ; active low
        pack

        pushst  PORTSTATUS_ONE  ; high side of bi-color LED
        pack

        ret
'''
    _set_led_sfp = '''
; DNI6448Combo - three active low LEDs for link and activity
set_led:
        port    a
        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor
        push    (BLINK_STATE_P)
        tand
        tinv                    ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        tinv                    ; LEDs are active low
        pack
        pushst  PORTSTATUS_LINKEN
        tinv                    ; LEDs are active low
        pack
        pushst  PORTSTATUS_ONE  ; yellow LED off
        pack
        ret
'''
    _set_led_map = { 'RJ45' : _set_led_rj45,
                     'SFP'  : _set_led_sfp }

    def __init__(self, label, hw_port, phy_addr, sfp_leds, rj45_leds):
        cumulus.platform.Triumph1GPort.__init__(self,
                                                label=label,
                                                hw_port=hw_port,
                                                phy_type="54680",
                                                phy_addr=phy_addr,
                                                phy_layer='1GBaseT',
                                                leds=tuple(list(sfp_leds) +
                                                           list(rj45_leds)),
                                                unit=0)
        self._leds_map = { 'RJ45' : rj45_leds,
                           'SFP'  : sfp_leds }
        self._leds_off_map = { 'RJ45' : sfp_leds,
                               'SFP'  : rj45_leds }
        self.sfp = cumulus.sfp.SFPROMDTSWalk(label, 'sfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        fn_name = '%s_%s' % (self.__class__.__name__, mode)
        code = self._set_led_map[mode]
        led_call_base = self._leds_map[mode][1]
        led_off_base = self._leds_off_map[mode][1]

        # Set the approprate LEDs for the given mode and turn off the others.
        set_calls[led_call_base] = (fn_name, code, self.hw_port_num(mode, 0))
        set_calls[led_call_base + 1] = None
        set_calls[led_call_base + 2] = None
        set_calls[led_off_base + 0] = 1
        set_calls[led_off_base + 1] = 1
        set_calls[led_off_base + 2] = 1
        if mode == 'SFP':
            set_calls[led_off_base + 3] = 1
        elif mode == 'RJ45':
            set_calls[led_call_base + 3] = None

        return set_calls

    def set_hardware(self, platform, mode):
        mux = 'port%s_mux' % self.label
        setattr(platform.cpld, mux, self._combo_map[mode])

class DNI7448CPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ffe05000.localbus/ffdf0000.cpld'

class DNI7448LED(cumulus.ledup.TridentLEDController):
    num_leds = 36

class DNI7448Switch(cumulus.platform.BCMSwitch):
    ledup = DNI7448LED
    _sfp = DNI7448SFPp
    _qsfp = DNI7448QSFPp
    has_phy_ucode_spi_rom = True
    has_phy_ucode_mdio = True
    ports = (
        _sfp(label="1",  serdes=0,  phy_addr=0x4,  leds=(0, 0)),
        _sfp(label="2",  serdes=1,  phy_addr=0x5,  leds=(0, 1)),
        _sfp(label="3",  serdes=2,  phy_addr=0x6,  leds=(0, 2)),
        _sfp(label="4",  serdes=3,  phy_addr=0x7,  leds=(0, 3)),
        _sfp(label="5",  serdes=4,  phy_addr=0x8,  leds=(0, 4)),
        _sfp(label="6",  serdes=5,  phy_addr=0x9,  leds=(0, 5)),
        _sfp(label="7",  serdes=6,  phy_addr=0xa,  leds=(0, 6)),
        _sfp(label="8",  serdes=7,  phy_addr=0xb,  leds=(0, 7)),
        _sfp(label="9",  serdes=8,  phy_addr=0xc,  leds=(0, 8)),
        _sfp(label="10", serdes=9,  phy_addr=0xd,  leds=(0, 9)),
        _sfp(label="11", serdes=10, phy_addr=0xe,  leds=(0, 10)),
        _sfp(label="12", serdes=11, phy_addr=0xf,  leds=(0, 11)),
        _sfp(label="13", serdes=12, phy_addr=0x10, leds=(0, 12)),
        _sfp(label="14", serdes=13, phy_addr=0x11, leds=(0, 13)),
        _sfp(label="15", serdes=14, phy_addr=0x12, leds=(0, 14)),
        _sfp(label="16", serdes=15, phy_addr=0x13, leds=(0, 15)),
        _sfp(label="17", serdes=20, phy_addr=0x14, leds=(0, 20)),
        _sfp(label="18", serdes=21, phy_addr=0x15, leds=(0, 21)),
        _sfp(label="19", serdes=22, phy_addr=0x16, leds=(0, 22)),
        _sfp(label="20", serdes=23, phy_addr=0x17, leds=(0, 23)),
        _sfp(label="21", serdes=24, phy_addr=0x18, leds=(0, 24)),
        _sfp(label="22", serdes=25, phy_addr=0x19, leds=(0, 25)),
        _sfp(label="23", serdes=26, phy_addr=0x1a, leds=(0, 26)),
        _sfp(label="24", serdes=27, phy_addr=0x1b, leds=(0, 27)),
        _sfp(label="25", serdes=28, phy_addr=0x24, leds=(0, 28)),
        _sfp(label="26", serdes=29, phy_addr=0x25, leds=(0, 29)),
        _sfp(label="27", serdes=30, phy_addr=0x26, leds=(0, 30)),
        _sfp(label="28", serdes=31, phy_addr=0x27, leds=(0, 31)),
        _sfp(label="29", serdes=32, phy_addr=0x28, leds=(0, 32)),
        _sfp(label="30", serdes=33, phy_addr=0x29, leds=(0, 33)),
        _sfp(label="31", serdes=34, phy_addr=0x2a, leds=(0, 34)),
        _sfp(label="32", serdes=35, phy_addr=0x2b, leds=(0, 35)),
        _sfp(label="33", serdes=36, phy_addr=0x2c, leds=(1, 0)),
        _sfp(label="34", serdes=37, phy_addr=0x2d, leds=(1, 1)),
        _sfp(label="35", serdes=38, phy_addr=0x2e, leds=(1, 2)),
        _sfp(label="36", serdes=39, phy_addr=0x2f, leds=(1, 3)),
        _sfp(label="37", serdes=40, phy_addr=0x30, leds=(1, 4)),
        _sfp(label="38", serdes=41, phy_addr=0x31, leds=(1, 5)),
        _sfp(label="39", serdes=42, phy_addr=0x32, leds=(1, 6)),
        _sfp(label="40", serdes=43, phy_addr=0x33, leds=(1, 7)),
        _sfp(label="41", serdes=44, phy_addr=0x34, leds=(1, 8)),
        _sfp(label="42", serdes=45, phy_addr=0x35, leds=(1, 9)),
        _sfp(label="43", serdes=46, phy_addr=0x36, leds=(1, 10)),
        _sfp(label="44", serdes=47, phy_addr=0x37, leds=(1, 11)),
        _sfp(label="45", serdes=48, phy_addr=0x38, leds=(1, 12)),
        _sfp(label="46", serdes=49, phy_addr=0x39, leds=(1, 13)),
        _sfp(label="47", serdes=50, phy_addr=0x3a, leds=(1, 14)),
        _sfp(label="48", serdes=51, phy_addr=0x3b, leds=(1, 15)),

        _qsfp(label="49", serdes=(68,69,70,71), phy_addrs=(0x50,0x51,0x52,0x53), leds=(1,32)),
        _qsfp(label="50", serdes=(56,57,58,59), phy_addrs=(0x44,0x45,0x46,0x47), leds=(1,20)),
        _qsfp(label="51", serdes=(64,65,66,67), phy_addrs=(0x4c,0x4d,0x4e,0x4f), leds=(1,28)),
        _qsfp(label="52", serdes=(60,61,62,63), phy_addrs=(0x48,0x49,0x4a,0x4b), leds=(1,24)),
    )

class DNI7448PSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0042'
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr1']

class DNI7448PSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0040'
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr2']

class DNI7448Board(cumulus.sensors.Board_Unit):
    name = 'Board'
    description = 'S4810 CPLD Board'
    cpld_hwmon = ['board']

class DNI7448Fan(cumulus.sensors.Fan_Unit):
    minpwm = 136
    maxpwm = 221
    fan_max = 14500
    fan_min = 3000
    driver_hwmon = ['fan1']

class DNI7448Fan1(DNI7448Fan):
    name = 'Fan1'
    description = 'Tray2, Fan1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-001b'
    cpld_hwmon = ['fan_0']

class DNI7448Fan2(DNI7448Fan):
    name = 'Fan2'
    description = 'Tray2, Fan2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-001f'
    cpld_hwmon = ['fan_0']

class DNI7448Fan3(DNI7448Fan):
    name = 'Fan3'
    description = 'Tray1, Fan1'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0048'
    cpld_hwmon = ['fan_1']

class DNI7448Fan4(DNI7448Fan):
    name = 'Fan4'
    description = 'Tray1, Fan2'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004b'
    cpld_hwmon = ['fan_1']

class DNI7448Temp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'
    temp_max = 100
    temp_crit = 105

class DNI7448Temp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'CPU Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-0049'

class DNI7448Temp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'Left PHY Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004c'

class DNI7448Temp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'Right PHY Temp Sensor'
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004d'

class DNI7448Temp5(cumulus.sensors.Temp_Unit):
    name = 'Temp5'
    description = cumulus.sensors.Temp_Unit.mac_board_sensor_name
    driver_path = '/sys/devices/soc.0/ffe03100.i2c/i2c-1/1-004a'

class DNI7448PSULED(cumulus.sensors.StatusLED_Unit):
    name = 'PSU'
    sources = ['PSU1', 'PSU2']
    led_location = 'led_power'

class DNI7448FanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan'
    sources = ['Fan1', 'Fan2', 'Fan3', 'Fan4']
    led_location = 'led_fan'

class DNI7448SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_status'
    bad_led_color = 'green_blinking'

class DNI7448FanTray1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 1'
    sources = ['Fan1', 'Fan2']
    led_location = 'led_fan_tray_0'
    bad_led_color = 'red'

class DNI7448FanTray2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan Tray 2'
    sources = ['Fan3', 'Fan4']
    led_location = 'led_fan_tray_1'
    bad_led_color = 'red'

class DNI7448PWM1(cumulus.sensors.PWM_Unit):
    fans = (DNI7448Fan1(),
            DNI7448Fan2(),
            DNI7448Fan3(),
            DNI7448Fan4()
            )
    temps = (DNI7448Temp1(),
             DNI7448Temp2(),
             DNI7448Temp3(),
             DNI7448Temp4(),
             DNI7448Temp5()
             )

class DNI7448Sensors():
    units = ( DNI7448PSU1(),
              DNI7448PSU2(),
              DNI7448Board(),
              DNI7448Fan1(),
              DNI7448Fan2(),
              DNI7448Fan3(),
              DNI7448Fan4(),
              DNI7448Temp1(),
              DNI7448Temp2(),
              DNI7448Temp3(),
              DNI7448Temp4(),
              DNI7448Temp5(),
              )

class DNI7448PWMs():
    units = (DNI7448PWM1(),
             )

class DNI7448LEDs():
    units = (DNI7448PSULED(),
             DNI7448FanLED(),
             DNI7448FanTray1LED(),
             DNI7448FanTray2LED(),
             DNI7448SystemLED(),
             )

class DNI7448(cumulus.platform.Platform):
    name = 'dni,et-7448bf'
    cpld = DNI7448CPLD()
    switch = DNI7448Switch(cumulus.platform.TridentChip())
    statusleds = DNI7448LEDs()
    pwms = DNI7448PWMs()
    sensors = DNI7448Sensors()

class DNI6448LED(cumulus.ledup.TriumphLEDController):
    num_leds = 40

class DNI6448Switch(cumulus.platform.BCMSwitch):
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
    ledup = DNI6448LED
    _gige = DNI6448GigE
    _combo = DNI6448Combo
    # The 8727 revB PHYs on the 10G modules do not support microcode
    # download via MDIO.
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

        _combo(label="45", hw_port='ge44', phy_addr=0x35,
               sfp_leds=(0,0), rj45_leds=(0, 12)),
        _combo(label="46", hw_port='ge45', phy_addr=0x36,
               sfp_leds=(0,3), rj45_leds=(0, 16)),
        _combo(label="47", hw_port='ge46', phy_addr=0x37,
               sfp_leds=(0,6), rj45_leds=(0, 20)),
        _combo(label="48", hw_port='ge47', phy_addr=0x38,
               sfp_leds=(0,9), rj45_leds=(0, 24)),
    )

class DNI6448PSU1(cumulus.sensors.PSU_Unit):
    name = 'PSU1'
    driver_path = '/sys/devices/soc.0/e0003100.i2c/i2c-1/i2c-7/7-0040'
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr1']

class DNI6448PSU2(cumulus.sensors.PSU_Unit):
    name = 'PSU2'
    driver_path = '/sys/devices/soc.0/e0003100.i2c/i2c-1/i2c-7/7-0040'
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr2']

class DNI6448Temp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    driver_path = '/sys/devices/soc.0/e0003100.i2c/i2c-1/i2c-6/6-0048'

class DNI6448Temp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    driver_path = '/sys/devices/soc.0/e0003100.i2c/i2c-1/i2c-6/6-0049'

class DNI6448Fan1(cumulus.sensors.Fan_Unit):
    name = 'Fan1'
    driver_path = '/sys/devices/soc.0/e0003100.i2c/i2c-1/i2c-8/8-0048'
    cpld_hwmon = ['fan_0']
    driver_hwmon = ['fan1']

class DNI6448Fan2(cumulus.sensors.Fan_Unit):
    name = 'Fan2'
    driver_path = '/sys/devices/soc.0/e0003100.i2c/i2c-1/i2c-8/8-0048'
    cpld_hwmon = ['fan_1']
    driver_hwmon = ['fan2']

class DNI6448FanLED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan'
    sources = ['Fan1', 'Fan2']
    led_location = 'led_fan'
    bad_led_color = 'red'

class DNI6448SystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_status'
    bad_led_color = 'green_blinking'

class DNI6448PWM1(cumulus.sensors.PWM_Unit):
    fans = (DNI6448Fan1(),
            )
    temps = (DNI6448Temp1(),
             DNI6448Temp2(),
             )

class DNI6448Sensors():
    units = ( DNI6448PSU1(),
              DNI6448PSU2(),
              DNI6448Fan1(),
              DNI6448Fan2(),
              DNI6448Temp1(),
              DNI6448Temp2(),
              )

class DNI6448PWMs():
    units = (DNI6448PWM1(),
             )

class DNI6448LEDs():
    units = (DNI6448SystemLED(),
             DNI6448FanLED(),
             )

class DNI6448(cumulus.platform.Platform):
    name = 'dni,et-6448r'
    cpld = DNI6448CPLD()
    switch = DNI6448Switch(cumulus.platform.TriumphChip())
    pwms = DNI6448PWMs()
    sensors = DNI6448Sensors()
    statusleds = DNI6448LEDs()

# 6448 with expansion modules side-by-side
class DNI6448SbSSwitch(DNI6448Switch):
    _sfp = DNI6448SFP
    ports = DNI6448Switch.ports + (
        _sfp(label="49", hw_port='hg0', phy_addr=0x44, leds=(0,28)),
        _sfp(label="50", hw_port='hg1', phy_addr=0x45, leds=(0,29)),
        _sfp(label="51", hw_port='hg2', phy_addr=0x48, leds=(0,31)),
        _sfp(label="52", hw_port='hg3', phy_addr=0x49, leds=(0,32)),
    )

# 6448 with expansion modules side-by-side
class DNI6448SbS(DNI6448):
    revision = '160'
    switch = DNI6448SbSSwitch(cumulus.platform.TriumphChip())

# 6448 with expansion modules over/under
class DNI6448OUSwitch(DNI6448Switch):
    _sfp = DNI6448SFP
    ports = DNI6448Switch.ports + (
        _sfp(label="49", hw_port='hg0', phy_addr=0x48, leds=(0,28)),
        _sfp(label="50", hw_port='hg1', phy_addr=0x49, leds=(0,29)),
        _sfp(label="51", hw_port='hg2', phy_addr=0x44, leds=(0,31)),
        _sfp(label="52", hw_port='hg3', phy_addr=0x45, leds=(0,32)),
    )

# 6448 with expansion modules over/under
class DNI6448OU(DNI6448):
    revision = '128'
    switch = DNI6448OUSwitch(cumulus.platform.TriumphChip())

class DNI6448OU2(DNI6448OU):
    revision = '192'

# DNI ET-7048P = 6448 with expansion modules side-by-side and PoE
class DNI7048P(DNI6448):
    revision = '32'
    switch = DNI6448SbSSwitch(cumulus.platform.TriumphChip())

'''
     DNI C7448N
'''
class DNIC7448NQSFPp(cumulus.platform.Trident40GPort):
    _set_led = '''
; DNIC7448NQSFP -
;   Three bits per port:
;    1st: activity
;    2nd: 1 (constant)
;    3rd: link
;
set_led:
; 1st activity
        port    a
        pushst  PORTSTATUS_RX
        pushst  PORTSTATUS_TX
        tor

        push    (BLINK_STATE_P)
        tand
        tinv
        pack
; 2nd 1
        pushst PORTSTATUS_ONE
        pack
; 3rd link
        pushst PORTSTATUS_LINKEN
        tinv
        pack

        ret
'''
    _set_led_4x10 = '''
set_led:
; 1st activity
        call   get_p_act

        call   get_p_act
        tor

        call   get_p_act
        tor

        call   get_p_act
        tor
        push   (BLINK_STATE_P)
        tand
        tinv
        pack
; 2nd 1
        pushst PORTSTATUS_ONE
        pack
; 3rd link
        sub    a,4
        call   get_p_lnk

        call   get_p_lnk
        tor

        call   get_p_lnk
        tor

        call   get_p_lnk
        tor
        tinv
        pack
        ret

get_p_act:
        port   a

        pushst PORTSTATUS_RX
        pushst PORTSTATUS_TX
        tor
        inc    a
        ret

get_p_lnk:
        port   a

        pushst PORTSTATUS_LINKEN
        inc    a
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
        self.sfp = cumulus.sfp.SFPROMBCM(phy_addrs[0], 'qsfp+')

    def set_leds(self, mode, led_port, sub, led_index_list):
        self._check_mode(mode)

        set_calls = {}

        if (mode == "4x10G") and (sub != 0):
            # For 4x10G mode only update LEDs for the first
            # sub-interface.
            return set_calls

        fn_name = '%s' % self.__class__.__name__
        led_port = self.hw_port_num(mode, 0)
        if mode == "4x10G":
            call = (fn_name + "_4x10", self._set_led_4x10, led_port)
        elif mode == "40G":
            call = (fn_name, self._set_led, led_port)

        set_calls[led_index_list[0]] = call

        return set_calls


class DNIC7448N10GT(cumulus.platform.Trident10GPort):
    _set_led = '''
; DNIC7448N10GT - three bits are allocated for each 10GT port
;                  but they are ignored by the hardware (the 10GT
;                  port LEDs are controlled by the phys). Just
;                  pack whatever
set_led:
        pack
        pack
        pack
        ret
'''

    def __init__(self, label, serdes, phy_addr, leds):

        cumulus.platform.Trident10GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_type="84740",
                                                 phy_addr=phy_addr,
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


class DNIC7448NCPLD(cumulus.cpld.SysFS):
    path = '/sys/devices/ffe05000.localbus/ffdf0000.cpld'


class DNIC7448NLED(cumulus.ledup.TridentLEDController):
    num_leds = 36


class DNIC7448NSwitch(cumulus.platform.BCMSwitch):
    ledup = DNIC7448NLED
    _10GT = DNIC7448N10GT
    _qsfp = DNIC7448NQSFPp
    has_phy_ucode_spi_rom = True
    has_phy_ucode_mdio = True
    ports = (
        _10GT(label="1",  serdes=0,  phy_addr=0x4,  leds=(0, 0)),
        _10GT(label="2",  serdes=1,  phy_addr=0x5,  leds=(0, 1)),
        _10GT(label="3",  serdes=2,  phy_addr=0x6,  leds=(0, 2)),
        _10GT(label="4",  serdes=3,  phy_addr=0x7,  leds=(0, 3)),
        _10GT(label="5",  serdes=4,  phy_addr=0x8,  leds=(0, 4)),
        _10GT(label="6",  serdes=5,  phy_addr=0x9,  leds=(0, 5)),
        _10GT(label="7",  serdes=6,  phy_addr=0xa,  leds=(0, 6)),
        _10GT(label="8",  serdes=7,  phy_addr=0xb,  leds=(0, 7)),
        _10GT(label="9",  serdes=8,  phy_addr=0xc,  leds=(0, 8)),
        _10GT(label="10", serdes=9,  phy_addr=0xd,  leds=(0, 9)),
        _10GT(label="11", serdes=10, phy_addr=0xe,  leds=(0, 10)),
        _10GT(label="12", serdes=11, phy_addr=0xf,  leds=(0, 11)),
        _10GT(label="13", serdes=12, phy_addr=0x10, leds=(0, 12)),
        _10GT(label="14", serdes=13, phy_addr=0x11, leds=(0, 13)),
        _10GT(label="15", serdes=14, phy_addr=0x12, leds=(0, 14)),
        _10GT(label="16", serdes=15, phy_addr=0x13, leds=(0, 15)),
        _10GT(label="17", serdes=20, phy_addr=0x14, leds=(0, 16)),
        _10GT(label="18", serdes=21, phy_addr=0x15, leds=(0, 17)),
        _10GT(label="19", serdes=22, phy_addr=0x16, leds=(0, 18)),
        _10GT(label="20", serdes=23, phy_addr=0x17, leds=(0, 19)),
        _10GT(label="21", serdes=24, phy_addr=0x18, leds=(0, 20)),
        _10GT(label="22", serdes=25, phy_addr=0x19, leds=(0, 21)),
        _10GT(label="23", serdes=26, phy_addr=0x1a, leds=(0, 22)),
        _10GT(label="24", serdes=27, phy_addr=0x1b, leds=(0, 23)),
        _10GT(label="25", serdes=28, phy_addr=0x24, leds=(0, 24)),
        _10GT(label="26", serdes=29, phy_addr=0x25, leds=(0, 25)),
        _10GT(label="27", serdes=30, phy_addr=0x26, leds=(0, 26)),
        _10GT(label="28", serdes=31, phy_addr=0x27, leds=(0, 27)),
        _10GT(label="29", serdes=32, phy_addr=0x28, leds=(0, 28)),
        _10GT(label="30", serdes=33, phy_addr=0x29, leds=(0, 29)),
        _10GT(label="31", serdes=34, phy_addr=0x2a, leds=(0, 30)),
        _10GT(label="32", serdes=35, phy_addr=0x2b, leds=(0, 31)),
        _10GT(label="33", serdes=36, phy_addr=0x2c, leds=(0, 32)),
        _10GT(label="34", serdes=37, phy_addr=0x2d, leds=(0, 33)),
        _10GT(label="35", serdes=38, phy_addr=0x2e, leds=(0, 34)),
        _10GT(label="36", serdes=39, phy_addr=0x2f, leds=(0, 35)),
        _10GT(label="37", serdes=40, phy_addr=0x30, leds=(1, 0)),
        _10GT(label="38", serdes=41, phy_addr=0x31, leds=(1, 1)),
        _10GT(label="39", serdes=42, phy_addr=0x32, leds=(1, 2)),
        _10GT(label="40", serdes=43, phy_addr=0x33, leds=(1, 3)),
        _10GT(label="41", serdes=44, phy_addr=0x34, leds=(1, 4)),
        _10GT(label="42", serdes=45, phy_addr=0x35, leds=(1, 5)),
        _10GT(label="43", serdes=46, phy_addr=0x36, leds=(1, 10)),
        _10GT(label="44", serdes=47, phy_addr=0x37, leds=(1, 11)),
        _10GT(label="45", serdes=48, phy_addr=0x38, leds=(1, 12)),
        _10GT(label="46", serdes=49, phy_addr=0x39, leds=(1, 13)),
        _10GT(label="47", serdes=50, phy_addr=0x3a, leds=(1, 14)),
        _10GT(label="48", serdes=51, phy_addr=0x3b, leds=(1, 15)),

        _qsfp(label="49", serdes=(68,69,70,71), phy_addrs=(0x50,0x51,0x52,0x53), leds=(1, 8)),
        _qsfp(label="50", serdes=(56,57,58,59), phy_addrs=(0x44,0x45,0x46,0x47), leds=(1, 6)),
        _qsfp(label="51", serdes=(64,65,66,67), phy_addrs=(0x54,0x55,0x56,0x57), leds=(1, 9)),
        _qsfp(label="52", serdes=(60,61,62,63), phy_addrs=(0x48,0x49,0x4a,0x4b), leds=(1, 7)),
    )

''' tmp75: path for temp sensor #1 '''
DNIC7448N_i2c_1_49_path = '/sys/bus/i2c/devices/1-0049'

''' tmp75: path for temp sensor #2 '''
DNIC7448N_i2c_1_4a_path = '/sys/bus/i2c/devices/1-004a'

''' tmp75: path for temp sensor #3 '''
DNIC7448N_i2c_1_4b_path = '/sys/bus/i2c/devices/1-004b'

''' tmp75: path for temp sensor #4 '''
DNIC7448N_i2c_1_4c_path = '/sys/bus/i2c/devices/1-004c'

''' dni_dps460: path for the PSU1 PMBus driver - Fan5, temp5, temp6 '''
DNIC7448N_i2c_1_59_path = '/sys/bus/i2c/devices/1-0059'

''' dni_dps460: path for the PSU2 PMBus driver - Fan6, temp7, temp8 '''
DNIC7448N_i2c_1_58_path = '/sys/bus/i2c/devices/1-0058'

''' path for MAC temp sensor - temp #9 '''
DNIC7448N_pci_0100_path = '/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0'

''' max6620: path for fan #1 - #4 '''
DNIC7448N_i2c_1_29_path = '/sys/bus/i2c/devices/1-0029'

''' ltc4215: path for PSU1 '''
DNIC7448N_i2c_1_42_path = '/sys/bus/i2c/devices/1-0042'

''' ltc4215: path for PSU2 '''
DNIC7448N_i2c_1_40_path = '/sys/bus/i2c/devices/1-0040'

class DNIC7448NSystemLED(cumulus.sensors.StatusLED_Unit):
    name = 'System'
    led_location = 'led_system'
    good_led_color = 'blue'
    bad_led_color = 'blue_blinking'

class DNIC7448NFan1LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan1'
    sources = ['Fan1', 'Fan2']
    led_location = 'led_fan_tray_0'
    bad_led_color = 'off'

class DNIC7448NFan2LED(cumulus.sensors.StatusLED_Unit):
    name = 'Fan2'
    sources = ['Fan3', 'Fan4']
    led_location = 'led_fan_tray_1'
    bad_led_color = 'off'

class DNIC7448NPSU(cumulus.sensors.PSU_Unit):
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

class DNIC7448NPSU1(DNIC7448NPSU):
    name = 'PSU1'
    driver_path = DNIC7448N_i2c_1_42_path
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr1']

class DNIC7448NPSU2(DNIC7448NPSU):
    name = 'PSU2'
    driver_path = DNIC7448N_i2c_1_40_path
    driver_hwmon = ['power1', 'in1', 'in2', 'curr1']
    cpld_hwmon = ['psu_pwr2']

class DNIC7448NTemp1(cumulus.sensors.Temp_Unit):
    name = 'Temp1'
    description = 'CPU Sensor'
    driver_path = DNIC7448N_i2c_1_49_path

class DNIC7448NTemp2(cumulus.sensors.Temp_Unit):
    name = 'Temp2'
    description = 'MAC Sensor'
    driver_path = DNIC7448N_i2c_1_4a_path

class DNIC7448NTemp3(cumulus.sensors.Temp_Unit):
    name = 'Temp3'
    description = 'Left of Phy'
    driver_path = DNIC7448N_i2c_1_4b_path

class DNIC7448NTemp4(cumulus.sensors.Temp_Unit):
    name = 'Temp4'
    description = 'Right of Phy'
    driver_path = DNIC7448N_i2c_1_4c_path

class DNIC7448NPSUTemp(cumulus.sensors.Temp_Unit):
    temp_crit = 85
    temp_max = 50
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

class DNIC7448NTemp5(DNIC7448NPSUTemp):
    name = 'PSU1Temp1'
    description = 'PSU1 Temp Sensor'
    driver_path = DNIC7448N_i2c_1_59_path
    driver_hwmon = ['temp1']
    psu = 'PSU1'

class DNIC7448NTemp6(DNIC7448NPSUTemp):
    name = 'PSU1Temp2'
    description = 'PSU1 Temp Sensor'
    driver_path = DNIC7448N_i2c_1_59_path
    driver_hwmon = ['temp2']
    psu = 'PSU1'

class DNIC7448NTemp7(DNIC7448NPSUTemp):
    name = 'PSU2Temp1'
    description = 'PSU2 Temp Sensor'
    driver_path = DNIC7448N_i2c_1_58_path
    driver_hwmon = ['temp1']
    psu = 'PSU2'

class DNIC7448NTemp8(DNIC7448NPSUTemp):
    name = 'PSU2Temp2'
    description = 'PSU2 Temp Sensor'
    driver_path = DNIC7448N_i2c_1_58_path
    driver_hwmon = ['temp2']
    psu = 'PSU2'

class DNIC7448NTemp9(cumulus.sensors.Temp_Unit):
    name = 'Temp9'
    description = cumulus.sensors.Temp_Unit.mac_die_sensor_name
    driver_path = DNIC7448N_pci_0100_path
    driver_hwmon = ['temp1']
    temp_max = 100
    temp_crit = 105

class DNIC7448NFan(cumulus.sensors.Fan_Unit):
    rpmmode = 1
    minpwm = 136
    maxpwm = 221
    fan_min = 4500
    fan_max = 18000
    driver_path = DNIC7448N_i2c_1_29_path

class DNIC7448NPSUFan(cumulus.sensors.Fan_Unit):
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

class DNIC7448NFan1(DNIC7448NFan):
    name = 'Fan1'
    description = 'Tray 1, Fan 1'
    driver_hwmon = ['fan3']
    cpld_hwmon = ['fan_0']

class DNIC7448NFan2(DNIC7448NFan):
    name = 'Fan2'
    description = 'Tray 1, Fan 2'
    driver_hwmon = ['fan4']
    cpld_hwmon = ['fan_0']

class DNIC7448NFan3(DNIC7448NFan):
    name = 'Fan3'
    description = 'Tray 2, Fan 1'
    driver_hwmon = ['fan1']
    cpld_hwmon = ['fan_1']

class DNIC7448NFan4(DNIC7448NFan):
    name = 'Fan4'
    description = 'Tray 2, Fan 2'
    driver_hwmon = ['fan2']
    cpld_hwmon = ['fan_1']

class DNIC7448NFan5(DNIC7448NPSUFan):
    name = 'PSU1Fan1'
    description = "PSU1 Fan"
    driver_path = DNIC7448N_i2c_1_59_path
    driver_hwmon = ['fan1']
    psu = 'PSU1'

class DNIC7448NFan6(DNIC7448NPSUFan):
    name = 'PSU2Fan1'
    description = "PSU2 Fan"
    driver_path = DNIC7448N_i2c_1_58_path
    driver_hwmon = ['fan1']
    psu = 'PSU2'

class DNIC7448NLEDs():
    units = (
        DNIC7448NSystemLED(),
        DNIC7448NFan1LED(),
        DNIC7448NFan2LED(),
    )

class DNIC7448NPWM1(cumulus.sensors.PWM_Unit):
    fans = (DNIC7448NFan1(),
            DNIC7448NFan2(),
            DNIC7448NFan3(),
            DNIC7448NFan4(),
            )
    temps = (DNIC7448NTemp1(),
             DNIC7448NTemp2(),
             DNIC7448NTemp3(),
             DNIC7448NTemp4(),
             DNIC7448NTemp9(),
             )

class DNIC7448NPWM2(cumulus.sensors.PWM_Unit):
    name = 'PSU1 PWM'
    fans = (DNIC7448NFan5(),
            )
    temps = (DNIC7448NTemp5(),
             DNIC7448NTemp6(),
             )

class DNIC7448NPWM3(cumulus.sensors.PWM_Unit):
    name = 'PSU2 PWM'
    fans = (DNIC7448NFan6(),
            )
    temps = (DNIC7448NTemp7(),
             DNIC7448NTemp8(),
             )

class DNIC7448NSensors():
    units = (DNIC7448NPSU1(),
             DNIC7448NPSU2(),
             DNIC7448NFan1(),
             DNIC7448NFan2(),
             DNIC7448NFan3(),
             DNIC7448NFan4(),
             DNIC7448NFan5(),
             DNIC7448NFan6(),
             DNIC7448NTemp1(),
             DNIC7448NTemp2(),
             DNIC7448NTemp3(),
             DNIC7448NTemp4(),
             DNIC7448NTemp5(),
             DNIC7448NTemp6(),
             DNIC7448NTemp7(),
             DNIC7448NTemp8(),
             DNIC7448NTemp9(),
        )

class DNIC7448NPWMs():
    units = (DNIC7448NPWM1(),
             DNIC7448NPWM2(),
             DNIC7448NPWM3(),
             )

class DNIC7448N(cumulus.platform.Platform):
    name = 'dni,c7448n'
    cpld = DNIC7448NCPLD()
    switch = DNIC7448NSwitch(cumulus.platform.TridentChip())
    statusleds = DNIC7448NLEDs()
    pwms = DNIC7448NPWMs()
    sensors = DNIC7448NSensors()

