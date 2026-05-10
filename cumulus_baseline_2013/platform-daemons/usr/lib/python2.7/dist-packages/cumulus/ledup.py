#
# Copyright 2012.  Cumulus Networks, Inc.
#
# ledup.py --
#
#     LED microcontroller code generation
#

import os
import errno
import struct
import tempfile
import subprocess
import shutil
import itertools

class LEDController:
    pass

class BCMLEDController(LEDController):
    '''
    "the SML LED interface contains a very small, very simple processor (1500
     gates) to do all the appropriate data formatting and interface control. It
     is vast overkill"
    '''
    _ledasm = '/usr/lib/cumulus/ledasm'

    # number port data elements accessible from each controller
    ports_per_chain = None

    # leds in output shift register
    num_leds = None

    # period of activity blink (in milliseconds)
    blink_period = 90

    # pad_n_XXX adds 5 extra bytes of asm code. So do it only
    # if more than 5 pad_XXX
    pad_n_threshold = 6

    static_code = { 'constants' : '''
;;;
;;; Constants
;;;

;;;
;;; The link scan base address points to an array of per-port data (32
;;; elements, 2 bytes each) which is continually updated by the main CPU's
;;; linkscan task.
LINKSCAN_P         equ    0x80 ; port data base address

;;; bits in the port data fields
LINKSCAN_LINK      equ    0x0  ; link down/up
LINKSCAN_TX        equ    0x4  ; transmitted packet
LINKSCAN_RX        equ    0x5  ; received packet

;;;
;;; The port status base address points to an array of per-port data (32
;;; elements, 2 bytes each) which is continually updated by the switch chip.
;;; This address is implied by port related op codes
PORTSTATUS_P       equ    0x00 ; port status base address

;;; bits in the linkscan port status fields
PORTSTATUS_RX      equ    0x0  ; received packet
PORTSTATUS_TX      equ    0x1  ; transmitted packet
PORTSTATUS_COLL    equ    0x2  ; collision
PORTSTATUS_SPEED_C equ    0x3  ; 100Mbps
PORTSTATUS_SPEED_M equ    0x4  ; 1Gbps
PORTSTATUS_DUPLEX  equ    0x5  ; half/full duplex
PORTSTATUS_FLOW    equ    0x6  ; flow control capable
PORTSTATUS_LINKUP  equ    0x7  ; link down/up
PORTSTATUS_LINKEN  equ    0x8  ; link disabled/enabled
PORTSTATUS_ZERO    equ    0xe  ; always 0
PORTSTATUS_ONE     equ    0xf  ; always 1

;;;
;;; Blink constants
TICKS_PER_SEC      equ    30   ; LED program runs at 30Hz
''',
    'variables' : '''
;;;
;;; Variables
;;;
;;; Addresses 0xa0 to 0xff are initialized to zero and usable by the program.
;;;

;;;
;;; Keep track of blink state, modified each cycle as a timer
BLINK_TICKS_P      equ    0xf0
BLINK_STATE_P      equ    0xf1
''',
    'functions' : '''
blink_update_state:
        ld      a,(BLINK_TICKS_P)
        cmp     a,0
        jz      blink_toggle
        dec     a
        ld      (BLINK_TICKS_P),a
        ret
blink_toggle:
        ld      a,(BLINK_STATE_P)
        xor     a,0x01
        and     a,0x01
        ld      (BLINK_STATE_P),a
        ld      a,TICKS_PER_BLINK
        ld      (BLINK_TICKS_P),a
        ret
''',
    }

    @property
    def defines(self):
        tpb = self.blink_period / 30.0
        if tpb != int(tpb):
            raise RuntimeError('non-integer blink cycles, correct period to multiple of 30')
        return '''
;;;
;;; Platform-specific defines
TICKS_PER_BLINK    equ    %(ticks_per_blink)u    ; 0 to alternate every cycle (15Hz)
NUM_LEDS           equ    %(num_leds)u
''' % { 'ticks_per_blink' : int(tpb),
        'num_leds' : self.num_leds }

    pad_zero = '''
pad_zero:
        port 1
        pushst  PORTSTATUS_ZERO
        pack
        ret
'''

    pad_one = '''
pad_one:
        port 1
        pushst  PORTSTATUS_ONE
        pack
        ret
'''

    pad_n_zero = '''
pad_n_zero:
        port 1
        pushst  PORTSTATUS_ZERO
        pack
        sub a, 1
        jnz pad_n_zero
        ret
'''

    pad_n_one = '''
pad_n_one:
        port 1
        pushst  PORTSTATUS_ONE
        pack
        sub a, 1
        jnz pad_n_one
        ret
'''

    def __init__(self):
        self.set_functions = set()
        self.set_calls = []
        self._template = '''
%(constants)s
%(defines)s
%(variables)s

main:
        %(set_calls)s

        call blink_update_state
        send NUM_LEDS

%(functions)s
%(set_functions)s
'''
    def set_ports(self, ports):
        '''
        Ask each port which LEDs it wants to claim and which code should run.
        We call the port.set_leds() method of each port which returns a
        dictionary mapping led number to a set_led function call.  By default,
        we assume all LEDs require padding.  The ports should put a 'None' in
        the dictionary for LEDs that don't need padding.
        '''
        calls = dict.fromkeys(range(self.num_leds), 1)

        '''
        Mapping between logical port to led index should be part
        from Port container class. Port container class should have relationships
        between physical ports, logical ports, linux interfaces , led indexes and
        serdes which spawn across various port classes. The fix to include this
        information as part of ledup.py is a short term fix.
        Ex:logical_to_led_index for Ganged port (40G/4) swp13
        '13': [28, 30, 32, 34]
        '''
        logical_to_led_index = {}
        for port in sorted(ports, key=lambda x: x.gang_label):
            ganged_port = port.gang_label
            if logical_to_led_index.get(ganged_port) == None:
                logical_to_led_index[ganged_port] =  [port.leds[1]]
            else:
                logical_to_led_index[ganged_port].append(port.leds[1])

        lport = 1
        for port in sorted(ports, key=lambda x: x.hw_port_num(0)):
            for sub in range(port.num_logical_ports):
                # Arguments for set_leds should be led_index_list and  hw_interface_number only
                # All other arguments need to be cleaned up
                calls.update(port.set_leds(lport, sub, logical_to_led_index[port.gang_label]))
                lport += 1

        sorted_calls = [ calls[x] for x in sorted(calls.keys()) ]
        for call, count in [ (k, len(list(g))) for k, g in
	                     itertools.groupby(sorted_calls) ]:
             if call in (0, 1):
                 self._led_pad_call(call, count)
             elif call is not None:
                 self._led_port_call(call, count)

    def _chain_port(self, port_num):
        '''
        convert a hardware port number to a led chain port number
        '''
        return ((port_num - 1) % self.ports_per_chain) + 1

    def _led_pad_call(self, value, length):
        if length == 0:
            return

        if value == 0:
            pad = 'zero'
        elif value == 1:
            pad = 'one'
        else:
            raise RuntimeError('bad pad value: %s', value)

        if length < self.pad_n_threshold:
            func = 'pad_%s' % pad
            for x in range(length):
                self.set_calls.append('''
        call    %s''' % func)
        else:
            func = 'pad_n_%s' % pad
            self.set_calls.append('''
        ld      a, %u''' % length)
            self.set_calls.append('''
        call    %s''' % func)
        self.set_functions.add(getattr(self, func))

    def _led_port_call(self, call, length):
        if length == 0:
            return
        (call_name, call_code, call_port) = call

        for x in range(0, length):
        # rename the function to be unique to the port class
            fn_name = 'set_led_%s' % call_name
            fn_code = call_code.replace('set_led:', '%s:' % fn_name)
            self.set_functions.add(fn_code)
            if call_port is not None:
                self.set_calls.append('''
        ld      a,%u''' % self._chain_port(call_port))
                self.set_calls.append('''
        call    %s''' % fn_name)

    @property
    def asm(self):
        code = self.static_code.copy()
        code.update({ 'set_functions' : ''.join(self.set_functions),
                      'set_calls'     : ''.join(self.set_calls),
                      'defines'       : self.defines })
        return self._template % code

    @property
    def hex(self):
        return self._compile(self.asm)

    def _compile(self, asm):
        '''
        Compile a LED program.  We have to do this in a temporary directory
        because the assembler only deals in files.

        XXX- For extra credit, someone should append stdout and stderr to any
        raised exceptions.
        '''
        tempdir = tempfile.mkdtemp()
        try:
           asm_filename = os.path.join(tempdir, 'code.asm')
           asm_file = open(asm_filename, 'w')
           asm_file.write(asm)
           asm_file.close()

           null = open('/dev/null')
           subprocess.check_call((self._ledasm, asm_filename[:-4]),
                                 stdin=null, stdout=null, stderr=null)

           hex_filename = os.path.join(tempdir, 'code.hex')
           hex_file = open(hex_filename, 'r')

           return hex_file.read()
        finally:
           shutil.rmtree(tempdir)

class TriumphLEDController(BCMLEDController):
    ports_per_chain = 64

class TridentLEDController(BCMLEDController):
    ports_per_chain = 36

class TridentTwoLEDController(BCMLEDController):
    ports_per_chain = 64
