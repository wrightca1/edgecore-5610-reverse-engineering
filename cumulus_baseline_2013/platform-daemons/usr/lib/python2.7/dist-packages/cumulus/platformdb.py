#
# Copyright 2012.  Cumulus Networks, Inc.
#
# platformdb.py --
#     Switch platform data.
#

import platform
import platforms.accton
import platforms.cel
import platforms.cumulusp
import platforms.dni
import platforms.quanta
import platforms.dell

platforms = (platforms.cel.CelKennisis,
             platforms.cel.CelRedstone,
             platforms.cel.CelRedstoneXp,
             platforms.cel.CelSmallstone,
             platforms.cel.CelSmallstoneXp,
             platforms.cumulusp.CumulusP2020LC1,
             platforms.cumulusp.CumulusP2020LC2,
             #platforms.cumulusp.CumulusP2020FC1,
             platforms.cumulusp.CumulusP2020Standalone,
             platforms.cumulusp.CumulusP2020Trident2,
             platforms.quanta.QuantaLB8,
             platforms.quanta.QuantaLB9,
             platforms.quanta.QuantaLY2,
             platforms.quanta.QuantaLY2R,
             platforms.quanta.QuantaLY6P2020,
             platforms.quanta.QuantaLY6Rangeley,
             platforms.quanta.QuantaLY8,
             platforms.quanta.QuantaLY9Rangeley,
             platforms.dell.DellS6000,
             platforms.dell.DellS4000,
             platforms.dni.DNI7448,
             platforms.dni.DNIC7448N,
             platforms.dni.DNI6448SbS,
             platforms.dni.DNI6448OU,
             platforms.dni.DNI6448OU2,
             platforms.dni.DNI7048P,
             platforms.accton.Accton4654,
             platforms.accton.Accton5652,
             platforms.accton.AcctonAS5610_52X,
             platforms.accton.AcctonAS5712_54X,
             platforms.accton.AcctonAS6700_32X,
             platforms.accton.AcctonAS6701_32X)

def lookup(name, revision=None):
    if revision == 'UNKNOWN':
        revision = None

    for sw_platform in platforms:
        if sw_platform.name == name and sw_platform.revision == revision:
            return sw_platform

    raise platform.NoSuchPlatform('platform not found: %s revision=%s' %
                                  (name, revision))
