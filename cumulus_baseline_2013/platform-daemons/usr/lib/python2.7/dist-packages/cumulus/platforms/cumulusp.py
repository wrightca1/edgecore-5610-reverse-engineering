#
# Copyright 2012.  Cumulus Networks, Inc.
#
# dni.py --
#     DNI switch platforms
#

import cumulus.platform
import cumulus.ledup

class CumulusP2020LC1FabricPort(cumulus.platform.Trident40GPort):
    is_fabric = True
    def __init__(self, label, serdes, unit):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=None,
                                                 unit=unit)

class CumulusP2020LC1SFPp(cumulus.platform.Trident10GPort):
    def __init__(self, label, serdes, unit, leds, rx_polarity_flip=None):
        cumulus.platform.Trident10GPort.__init__(self,
                                                 label=label,
                                                 serdes=(serdes,),
                                                 phy_type=None,
                                                 phy_addr=None,
                                                 phy_layer='SFP+',
                                                 leds=leds,
                                                 unit=unit,
                                                 rx_polarity_flip=rx_polarity_flip)

class CumulusP2020LC1LED(cumulus.ledup.TridentLEDController):
    num_leds = 64

class CumulusP2020LC1Switch(cumulus.platform.BCMSwitch):
    ledup = CumulusP2020LC1LED
    _sfp = CumulusP2020LC1SFPp
    _fab = CumulusP2020LC1FabricPort

    # No PHYs
    has_phy_ucode_spi_rom = False
    has_phy_ucode_mdio = False
    ports = (
        _sfp(label="1",  unit=0, serdes=20, leds=(0,0)),
        _sfp(label="2",  unit=0, serdes=22, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="3",  unit=0, serdes=21, leds=(0,0)),
        _sfp(label="4",  unit=0, serdes=23, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="5",  unit=0, serdes=24, leds=(0,0)),
        _sfp(label="6",  unit=0, serdes=26, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="7",  unit=0, serdes=25, leds=(0,0)),
        _sfp(label="8",  unit=0, serdes=27, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="9",  unit=0, serdes=28, leds=(0,0)),
        _sfp(label="10", unit=0, serdes=30, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="11", unit=0, serdes=29, leds=(0,0)),
        _sfp(label="12", unit=0, serdes=31, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="13", unit=0, serdes=32, leds=(0,0)),
        _sfp(label="14", unit=0, serdes=34, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="15", unit=0, serdes=33, leds=(0,0)),
        _sfp(label="16", unit=0, serdes=35, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="17", unit=0, serdes=36, leds=(0,0)),
        _sfp(label="18", unit=0, serdes=38, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="19", unit=0, serdes=37, leds=(0,0)),
        _sfp(label="20", unit=0, serdes=39, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="21", unit=0, serdes=40, leds=(0,0)),
        _sfp(label="22", unit=0, serdes=42, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="23", unit=0, serdes=41, leds=(0,0)),
        _sfp(label="24", unit=0, serdes=43, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="25", unit=0, serdes=44, leds=(0,0)),
        _sfp(label="26", unit=0, serdes=46, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="27", unit=0, serdes=45, leds=(0,0)),
        _sfp(label="28", unit=0, serdes=47, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="29", unit=0, serdes=48, leds=(0,0)),
        _sfp(label="30", unit=0, serdes=50, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="31", unit=0, serdes=49, leds=(0,0)),
        _sfp(label="32", unit=0, serdes=51, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="33", unit=1, serdes=20, leds=(0,0)),
        _sfp(label="34", unit=1, serdes=22, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="35", unit=1, serdes=21, leds=(0,0)),
        _sfp(label="36", unit=1, serdes=23, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="37", unit=1, serdes=24, leds=(0,0)),
        _sfp(label="38", unit=1, serdes=26, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="39", unit=1, serdes=25, leds=(0,0)),
        _sfp(label="40", unit=1, serdes=27, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="41", unit=1, serdes=28, leds=(0,0)),
        _sfp(label="42", unit=1, serdes=30, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="43", unit=1, serdes=29, leds=(0,0)),
        _sfp(label="44", unit=1, serdes=31, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="45", unit=1, serdes=32, leds=(0,0)),
        _sfp(label="46", unit=1, serdes=34, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="47", unit=1, serdes=33, leds=(0,0)),
        _sfp(label="48", unit=1, serdes=35, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="49", unit=1, serdes=36, leds=(0,0)),
        _sfp(label="50", unit=1, serdes=38, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="51", unit=1, serdes=37, leds=(0,0)),
        _sfp(label="52", unit=1, serdes=39, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="53", unit=1, serdes=40, leds=(0,0)),
        _sfp(label="54", unit=1, serdes=42, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="55", unit=1, serdes=41, leds=(0,0)),
        _sfp(label="56", unit=1, serdes=43, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="57", unit=1, serdes=44, leds=(0,0)),
        _sfp(label="58", unit=1, serdes=46, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="59", unit=1, serdes=45, leds=(0,0)),
        _sfp(label="60", unit=1, serdes=47, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="61", unit=1, serdes=48, leds=(0,0)),
        _sfp(label="62", unit=1, serdes=50, leds=(0,0), rx_polarity_flip=True),
        _sfp(label="63", unit=1, serdes=49, leds=(0,0)),
        _sfp(label="64", unit=1, serdes=51, leds=(0,0), rx_polarity_flip=True),

        # slot A
        _fab(label="fp0" , unit=0, serdes=(12,13,14,15)),
        _fab(label="fp1" , unit=0, serdes=(8 ,9,10,11)),
        _fab(label="fp2" , unit=1, serdes=(12,13,14,15)),
        _fab(label="fp3" , unit=1, serdes=(8 ,9,10,11)),
        # slot B
        _fab(label="fp4" , unit=0, serdes=(4 , 5, 6, 7)),
        _fab(label="fp5" , unit=0, serdes=(0 , 1, 2, 3)),
        _fab(label="fp6" , unit=1, serdes=(4 , 5, 6, 7)),
        _fab(label="fp7" , unit=1, serdes=(0 , 1, 2, 3)),
        # slot C
        _fab(label="fp8" , unit=0, serdes=(68,69,70,71)),
        _fab(label="fp9" , unit=0, serdes=(64,65,66,67)),
        _fab(label="fp10", unit=1, serdes=(68,69,70,71)),
        _fab(label="fp11", unit=1, serdes=(64,65,66,67)),
        # slot D
        _fab(label="fp12", unit=0, serdes=(60,61,62,63)),
        _fab(label="fp13", unit=0, serdes=(56,57,58,59)),
        _fab(label="fp14", unit=1, serdes=(60,61,62,63)),
        _fab(label="fp15", unit=1, serdes=(56,57,58,59)),
    )

class CumulusP2020LC1(cumulus.platform.Platform):
    name = 'cumulus,cumulus_p2020_lc64x10'
    switch = CumulusP2020LC1Switch(cumulus.platform.TridentChip())

class CumulusP2020LC2FabricPort(CumulusP2020LC1FabricPort):
    pass

class CumulusP2020LC2QSFPpA(cumulus.platform.Trident40GPort):
    '''
    QSFP Plus port with polarity mapping "A" (tx_polarity_flip=0x000f)
    '''
    def __init__(self, label, serdes, unit, leds):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=leds,
                                                 unit=unit,
                                                 rx_polarity_flip=0xf0f0,
                                                 tx_polarity_flip=0x000f)

class CumulusP2020LC2QSFPpB(cumulus.platform.Trident40GPort):
    '''
    QSFP Plus port with polarity mapping "B" (tx_polarity_flip=0x0f00)
    '''
    def __init__(self, label, serdes, unit, leds, polarity_flip=None):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=leds,
                                                 unit=unit,
                                                 rx_polarity_flip=0xf0f0,
                                                 tx_polarity_flip=0x0f00)

class CumulusP2020LC2LED(CumulusP2020LC1LED):
    pass

class CumulusP2020LC2Switch(cumulus.platform.BCMSwitch):
    ledup = CumulusP2020LC2LED
    _qsfpA = CumulusP2020LC2QSFPpA
    _qsfpB = CumulusP2020LC2QSFPpB
    _fab = CumulusP2020LC2FabricPort

    ports = (
        _qsfpA(label="1" ,  unit=0, serdes=(20,21,22,23), leds=(0,0)),
        _qsfpA(label="2" ,  unit=0, serdes=(24,25,26,27), leds=(0,0)),
        _qsfpA(label="3" ,  unit=0, serdes=(28,29,30,31), leds=(0,0)),
        _qsfpA(label="4" ,  unit=0, serdes=(32,33,34,35), leds=(0,0)),
        _qsfpB(label="5" ,  unit=0, serdes=(36,36,37,38), leds=(0,0)),
        _qsfpB(label="6" ,  unit=0, serdes=(40,41,42,43), leds=(0,0)),
        _qsfpB(label="7" ,  unit=0, serdes=(44,45,46,47), leds=(0,0)),
        _qsfpB(label="8" ,  unit=0, serdes=(48,49,50,51), leds=(0,0)),
        _qsfpA(label="9" ,  unit=1, serdes=(20,21,22,23), leds=(0,0)),
        _qsfpA(label="10",  unit=1, serdes=(24,25,26,27), leds=(0,0)),
        _qsfpA(label="11",  unit=1, serdes=(28,29,30,31), leds=(0,0)),
        _qsfpA(label="12",  unit=1, serdes=(32,33,34,35), leds=(0,0)),
        _qsfpB(label="13",  unit=1, serdes=(36,36,37,38), leds=(0,0)),
        _qsfpB(label="14",  unit=1, serdes=(40,41,42,43), leds=(0,0)),
        _qsfpB(label="15",  unit=1, serdes=(44,45,46,47), leds=(0,0)),
        _qsfpB(label="16",  unit=1, serdes=(48,49,50,51), leds=(0,0)),

        # slot A
        _fab(label="fp0" , unit=0, serdes=(12,13,14,15)),
        _fab(label="fp1" , unit=0, serdes=( 8, 9,10,11)),
        _fab(label="fp2" , unit=1, serdes=(12,13,14,15)),
        _fab(label="fp3" , unit=1, serdes=( 8, 9,10,11)),
        # slot B
        _fab(label="fp4" , unit=0, serdes=( 4, 5, 6, 7)),
        _fab(label="fp5" , unit=0, serdes=( 0, 1, 2, 3)),
        _fab(label="fp6" , unit=1, serdes=( 4, 5, 6, 7)),
        _fab(label="fp7" , unit=1, serdes=( 0, 1, 2, 3)),
        # slot C
        _fab(label="fp8" , unit=0, serdes=(68,69,70,71)),
        _fab(label="fp9" , unit=0, serdes=(64,65,66,67)),
        _fab(label="fp10", unit=1, serdes=(68,69,70,71)),
        _fab(label="fp11", unit=1, serdes=(64,65,66,67)),
        # slot D
        _fab(label="fp12", unit=0, serdes=(60,61,62,63)),
        _fab(label="fp13", unit=0, serdes=(56,57,58,59)),
        _fab(label="fp14", unit=1, serdes=(60,61,62,63)),
        _fab(label="fp15", unit=1, serdes=(56,57,58,59)),
    )

class CumulusP2020LC2(cumulus.platform.Platform):
    name = 'cumulus,cumulus_p2020_lc16x40'
    switch = CumulusP2020LC2Switch(cumulus.platform.TridentChip())

class CumulusP2020Trident2Port(cumulus.platform.Trident40GPort):
    def __init__(self, label, serdes, tx_lane_map=None):
        cumulus.platform.Trident40GPort.__init__(self,
                                                 label=label,
                                                 serdes=serdes,
                                                 phy_types=None,
                                                 phy_addrs=None,
                                                 leds=None,
                                                 unit=0,
                                                 rx_lane_map=0x3012,
                                                 tx_lane_map=tx_lane_map,
                                                 )

class CumulusP2020Trident2Switch(cumulus.platform.BCMSwitch):
    _qsfp = CumulusP2020Trident2Port
    has_phy_ucode_spi_rom = False
    has_phy_ucode_mdio = False
    ports = (
# XXX - Trident2 has bandwidth limitations that mean we can't enable all the
# ports.  Investigate pbmp_oversub=
        _qsfp(label="1",  serdes=(0,1,2,3)        , tx_lane_map=0x1230),
        _qsfp(label="2",  serdes=(4,5,6,7)                            ),
        _qsfp(label="3",  serdes=(8,9,10,11)      , tx_lane_map=0x1230),
#        _qsfp(label="4",  serdes=(12,13,14,15)                        ),
#        _qsfp(label="5",  serdes=(16,17,18,19)    , tx_lane_map=0x1230),
        _qsfp(label="6",  serdes=(20,21,22,23)                        ),
        _qsfp(label="7",  serdes=(24,25,26,27)    , tx_lane_map=0x1230),
        _qsfp(label="8",  serdes=(28,29,30,31)                        ),
        _qsfp(label="9",  serdes=(32,33,34,35)    , tx_lane_map=0x1230),
        _qsfp(label="10", serdes=(36,37,38,39)                        ),
        _qsfp(label="11", serdes=(40,41,42,43)    , tx_lane_map=0x1230),
#        _qsfp(label="12", serdes=(44,45,46,47)                       ),
#        _qsfp(label="13", serdes=(48,49,50,51)    , tx_lane_map=0x1230),
        _qsfp(label="14", serdes=(52,53,54,55)                        ),
        _qsfp(label="15", serdes=(56,57,58,59)    , tx_lane_map=0x1230),
        _qsfp(label="16", serdes=(60,61,62,63)                        ),
        _qsfp(label="17", serdes=(64,65,66,67)    , tx_lane_map=0x1230),
        _qsfp(label="18", serdes=(68,69,70,71)                        ),
        _qsfp(label="19", serdes=(72,73,74,75)    , tx_lane_map=0x1230),
#        _qsfp(label="20", serdes=(76,77,78,79)                        ),
#        _qsfp(label="21", serdes=(80,81,82,83)    , tx_lane_map=0x1230),
        _qsfp(label="22", serdes=(84,85,86,87)                        ),
        _qsfp(label="23", serdes=(88,89,90,91)    , tx_lane_map=0x1230),
        _qsfp(label="24", serdes=(92,93,94,95)                        ),
        _qsfp(label="25", serdes=(96,97,98,99)    , tx_lane_map=0x1230),
        _qsfp(label="26", serdes=(100,101,102,103)                    ),
        _qsfp(label="27", serdes=(104,105,106,107), tx_lane_map=0x1230),
#        _qsfp(label="28", serdes=(108,109,110,111)                    ),
#        _qsfp(label="29", serdes=(112,113,114,115), tx_lane_map=0x1230),
        _qsfp(label="30", serdes=(116,117,118,119)                    ),
        _qsfp(label="31", serdes=(120,121,122,123), tx_lane_map=0x1230),
        _qsfp(label="32", serdes=(124,125,126,127)                    ),
       )

class CumulusP2020Trident2(cumulus.platform.Platform):
    name = 'cumulus,cumulus_p2020_trident2'
    switch = CumulusP2020Trident2Switch(cumulus.platform.TridentTwo_56850_Chip())

class CumulusP2020Standalone(cumulus.platform.Platform):
    name = 'cumulus,cumulus_p2020'
