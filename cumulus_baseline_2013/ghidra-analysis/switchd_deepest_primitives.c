/* Deepest chip-access primitives in switchd, decompiled */

/* === FUN_108623e4 @ 0x108623e4 (size=8176) === */

int FUN_108623e4(int param_1,uint *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  code *pcVar5;
  uint local_b8;
  int local_b4;
  undefined1 auStack_98 [12];
  undefined4 local_8c;
  uint local_80;
  int local_28;
  uint *local_24;
  int local_20;
  int local_1c;
  int local_18;
  
  iVar3 = *(int *)((&DAT_1212d2dc)[param_1] + 0xe1fc);
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  iVar1 = FUN_113128a8();
  if (iVar1 != 0) {
    FUN_11312544("! sal_int_context()",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/schan.c"
                 ,0x17f);
  }
  if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) &&
     ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0)) {
    iVar1 = 0x14;
  }
  else {
    iVar1 = 0x16;
  }
  if (iVar1 < local_20) {
    FUN_11312544("dwc_write <= CMIC_SCHAN_WORDS(unit)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/schan.c"
                 ,0x180);
  }
  if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) &&
     ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0)) {
    iVar1 = 0x14;
  }
  else {
    iVar1 = 0x16;
  }
  if (iVar1 < local_1c) {
    FUN_11312544("dwc_read <= CMIC_SCHAN_WORDS(unit)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/schan.c"
                 ,0x181);
  }
  if (((*(int *)(&DAT_1212d36c + local_28 * 4) != 1) ||
      (*(int *)((&DAT_1212d2dc)[local_28] + 0xe6d0) != 0)) &&
     (*(int *)(&DAT_1212d36c + local_28 * 4) != 4)) goto LAB_10862898;
  switch(*local_24 >> 0x1a) {
  case 7:
    if (*(int *)(&DAT_1212d36c + local_28 * 4) == 4) {
      memset(local_24,0,0x58);
      *local_24 = *local_24 & 0x3ffffff | 0x20000000;
      return 0;
    }
    goto LAB_10862898;
  default:
    goto LAB_10862898;
  case 9:
    local_b4 = 0;
    break;
  case 0xb:
    if (*(int *)(&DAT_1212d36c + local_28 * 4) == 4) {
      memset(local_24,0,0x58);
      *local_24 = *local_24 & 0x3ffffff | 0x30000000;
      return 0;
    }
    goto LAB_10862898;
  case 0xd:
    *local_24 = *local_24 & 0x3ffffff | 0x38000000;
    local_b4 = 0;
    break;
  case 0xf:
    *local_24 = *local_24 & 0x3ffffff | 0x40000000;
    local_b4 = 0;
    break;
  case 0x11:
    *local_24 = *local_24 & 0x3ffffff | 0x48000000;
    local_b4 = 0;
    break;
  case 0x15:
    local_b4 = 0;
    break;
  case 0x19:
  case 0x1e:
    if (*(int *)(&DAT_1212d36c + local_28 * 4) == 4) {
      return -7;
    }
    goto LAB_10862898;
  case 0x1a:
    *local_24 = *local_24 & 0x3ffffff | 0x6c000000;
    local_b4 = 0;
    break;
  case 0x1c:
    *local_24 = *local_24 & 0x3ffffff | 0x74000000;
    local_b4 = 0;
    break;
  case 0x20:
    if (*(int *)(&DAT_1212d36c + local_28 * 4) == 4) {
      *local_24 = *local_24 & 0x3ffffff | 0x84000000;
      return -7;
    }
    goto LAB_10862898;
  case 0x22:
    if (*(int *)(&DAT_1212d36c + local_28 * 4) == 4) {
      *local_24 = *local_24 & 0x3ffffff | 0x8c000000;
      return -7;
    }
LAB_10862898:
    FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0xe1e4),0xffffffff);
    iVar1 = FUN_10761b70(2);
    if (iVar1 != 0) {
      uVar2 = FUN_108617f8(*local_24 >> 0x1a);
      FUN_1076193c("S-CHANNEL %s: (unit %d)\n",uVar2,local_28);
      FUN_10861dbc(local_28,local_24,local_20);
    }
    local_b4 = 0;
    for (local_b8 = 0; (int)local_b8 < local_20; local_b8 = local_b8 + 1) {
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
        if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
          if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
            iVar1 = local_b8 << 2;
          }
          else {
            iVar1 = (local_b8 + 0x200) * 4;
          }
          (**(code **)(&DAT_12125c64 + local_28 * 0x78))
                    (&DAT_12125c2c + local_28 * 0x78,iVar1,local_24[local_b8]);
        }
        else {
          if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
            uVar4 = local_b8 << 2 | local_b8 >> 0x1e;
          }
          else {
            uVar4 = (local_b8 + 0x200) * 4 | local_b8 + 0x200 >> 0x1e;
          }
          *(uint *)(((int)uVar4 >> 2) * 4 + *(int *)(&DAT_12125c5c + local_28 * 0x78)) =
               local_24[local_b8];
        }
      }
      else if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
        (**(code **)(&DAT_12125c64 + local_28 * 0x78))
                  (&DAT_12125c2c + local_28 * 0x78,iVar3 * 0x1000 + 0x3100c + local_b8 * 4,
                   local_24[local_b8]);
      }
      else {
        *(uint *)(((int)(iVar3 * 0x1000 + 0x3100c + local_b8 * 4) >> 2) * 4 +
                 *(int *)(&DAT_12125c5c + local_28 * 0x78)) = local_24[local_b8];
      }
    }
    if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
      if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
        (**(code **)(&DAT_12125c64 + local_28 * 0x78))(&DAT_12125c2c + local_28 * 0x78,0x50,0x80);
      }
      else {
        *(undefined4 *)(*(int *)(&DAT_12125c5c + local_28 * 0x78) + 0x50) = 0x80;
      }
    }
    else if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
      pcVar5 = *(code **)(&DAT_12125c64 + local_28 * 0x78);
      iVar1 = local_28 * 0x78;
      if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
        uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                          (&DAT_12125c2c + local_28 * 0x78,(iVar3 + 0x31) * 0x1000);
      }
      else {
        uVar4 = *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 +
                         *(int *)(&DAT_12125c5c + local_28 * 0x78));
      }
      (*pcVar5)(&DAT_12125c2c + iVar1,(iVar3 + 0x31) * 0x1000,uVar4 | 1);
    }
    else {
      iVar1 = *(int *)(&DAT_12125c5c + local_28 * 0x78);
      if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
        uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                          (&DAT_12125c2c + local_28 * 0x78,(iVar3 + 0x31) * 0x1000);
      }
      else {
        uVar4 = *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 +
                         *(int *)(&DAT_12125c5c + local_28 * 0x78));
      }
      *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 + iVar1) = uVar4 | 1;
    }
    if ((local_18 == 0) || (*(int *)((&DAT_1212d2dc)[local_28] + 0xe6c4) == 0)) {
      FUN_10880ed8(auStack_98,*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0xe6bc),100);
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
        do {
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,0x50);
          }
          else {
            uVar4 = *(uint *)(*(int *)(&DAT_12125c5c + local_28 * 0x78) + 0x50);
          }
          if ((uVar4 & 2) != 0) goto LAB_10863b08;
          iVar1 = FUN_10880f30(auStack_98);
        } while (iVar1 == 0);
        local_b4 = -9;
LAB_10863b08:
        if (local_b4 == 0) {
          FUN_10761a94(2,"  Done in %d polls\n",local_8c);
        }
        if ((uVar4 & 0x200000) != 0) {
          local_b4 = -0xb;
          FUN_10761a94(2,"  NAK received from SCHAN.\n");
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              uVar2 = 4;
            }
            else {
              uVar2 = 0x804;
            }
            local_80 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                                 (&DAT_12125c2c + local_28 * 0x78,uVar2);
          }
          else {
            if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              iVar1 = 4;
            }
            else {
              iVar1 = 0x804;
            }
            local_80 = *(uint *)(iVar1 + *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          switch(*local_24 >> 0x1a) {
          case 7:
          case 0xb:
switchD_10863ca0_caseD_7:
            FUN_108679f4(local_28,local_24[1],*local_24 >> 0x14 & 0x3f,
                         (*local_24 & 0xfc000000) == 0x2c000000,0);
            break;
          default:
            break;
          case 0x24:
          case 0x26:
          case 0x28:
            if ((local_80 & 0x3c000000) == 0x3c000000) goto switchD_10863ca0_caseD_7;
          }
        }
        if (((uVar4 & 0x100000) != 0) &&
           ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c3c) & 0x400) != 0)) {
          local_b4 = -0xb;
          FUN_10761a94(0x200000,"  SER Parity Check Error.\n");
          FUN_113102e8(FUN_10867c68,local_28,local_24[1],0,0,0);
        }
        if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c14) & 0x200) != 0) &&
           ((uVar4 & 0x400000) != 0)) {
          local_b4 = -9;
        }
        if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
          (**(code **)(&DAT_12125c64 + local_28 * 0x78))(&DAT_12125c2c + local_28 * 0x78,0x50,1);
        }
        else {
          *(undefined4 *)(*(int *)(&DAT_12125c5c + local_28 * 0x78) + 0x50) = 1;
        }
      }
      else {
        do {
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,(iVar3 + 0x31) * 0x1000);
          }
          else {
            uVar4 = *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 +
                             *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          if ((uVar4 & 2) != 0) goto LAB_108633e8;
          iVar1 = FUN_10880f30(auStack_98);
        } while (iVar1 == 0);
        local_b4 = -9;
LAB_108633e8:
        if (local_b4 == 0) {
          FUN_10761a94(2,"  Done in %d polls\n",local_8c);
        }
        if ((uVar4 & 0x200000) != 0) {
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              uVar2 = 4;
            }
            else {
              uVar2 = 0x804;
            }
            local_80 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                                 (&DAT_12125c2c + local_28 * 0x78,uVar2);
          }
          else {
            if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              iVar1 = 4;
            }
            else {
              iVar1 = 0x804;
            }
            local_80 = *(uint *)(iVar1 + *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          local_b4 = -0xb;
          FUN_10761a94(2,"  NAK received from SCHAN.\n");
          switch(*local_24 >> 0x1a) {
          case 7:
          case 0xb:
switchD_10863580_caseD_7:
            FUN_108679f4(local_28,local_24[1],*local_24 >> 0x14 & 0x3f,
                         (*local_24 & 0xfc000000) == 0x2c000000,0);
          default:
            break;
          case 0x24:
          case 0x26:
          case 0x28:
            if ((local_80 & 0x3c000000) == 0x3c000000) goto switchD_10863580_caseD_7;
          }
        }
        if (((uVar4 & 0x100000) != 0) &&
           ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c3c) & 0x400) != 0)) {
          local_b4 = -0xb;
          FUN_10761a94(0x200000,"  SER Parity Check Error.\n");
          FUN_113102e8(FUN_10867c68,local_28,local_24[1],0,0,0);
        }
        if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c14) & 0x200) != 0) &&
           ((uVar4 & 0x400000) != 0)) {
          local_b4 = -9;
        }
        if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c44) & 0x1000) != 0) {
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            uVar2 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,iVar3 * 0x1000 + 0x31008);
          }
          else {
            uVar2 = *(undefined4 *)
                     ((iVar3 * 0x1000 + 0x31008 >> 2) * 4 +
                     *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          iVar1 = FUN_1084bf98(local_28,0xce2,uVar2,0x432c);
          if (iVar1 != 0) {
            local_b4 = -0xb;
            FUN_10761a94(0x200000,"  ERRBIT received in CMIC_SCHAN_ERR.\n");
          }
        }
        if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
          pcVar5 = *(code **)(&DAT_12125c64 + local_28 * 0x78);
          iVar1 = local_28 * 0x78;
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,(iVar3 + 0x31) * 0x1000);
          }
          else {
            uVar4 = *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 +
                             *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          (*pcVar5)(&DAT_12125c2c + iVar1,(iVar3 + 0x31) * 0x1000,uVar4 & 0xfffffffd);
        }
        else {
          iVar1 = *(int *)(&DAT_12125c5c + local_28 * 0x78);
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,(iVar3 + 0x31) * 0x1000);
          }
          else {
            uVar4 = *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 +
                             *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          *(uint *)(((iVar3 + 0x31) * 0x1000 >> 2) * 4 + iVar1) = uVar4 & 0xfffffffd;
        }
      }
    }
    else {
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
        FUN_107babcc(local_28,1);
      }
      else {
        FUN_107c96bc(local_28,0x100000);
      }
      iVar1 = FUN_10325634(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0xe6c0),
                           *(undefined4 *)((&DAT_1212d2dc)[local_28] + 0xe6bc));
      if (iVar1 == 0) {
        FUN_10761a94(2,"  Interrupt received\n");
        if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
          if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0xe6cc) & 0x200000) != 0) {
            local_b4 = -0xb;
          }
          if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c14) & 0x200) != 0) &&
             ((*(uint *)((&DAT_1212d2dc)[local_28] + 0xe6cc) & 0x400000) != 0)) {
            local_b4 = -9;
          }
        }
        else {
          if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0xe6cc) & 0x200000) != 0) {
            local_b4 = -0xb;
          }
          if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c14) & 0x200) != 0) &&
             ((*(uint *)((&DAT_1212d2dc)[local_28] + 0xe6cc) & 0x400000) != 0)) {
            local_b4 = -9;
          }
          if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c44) & 0x1000) != 0) {
            if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
              uVar2 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                                (&DAT_12125c2c + local_28 * 0x78,iVar3 * 0x1000 + 0x31008);
            }
            else {
              uVar2 = *(undefined4 *)
                       ((iVar3 * 0x1000 + 0x31008 >> 2) * 4 +
                       *(int *)(&DAT_12125c5c + local_28 * 0x78));
            }
            iVar1 = FUN_1084bf98(local_28,0xce2,uVar2,0x432c);
            if (iVar1 != 0) {
              local_b4 = -0xb;
              FUN_10761a94(0x200000,"  ERRBIT received in CMIC_SCHAN_ERR.\n");
            }
          }
        }
      }
      else {
        local_b4 = -9;
      }
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
        FUN_107bad6c(local_28,1);
      }
      else {
        FUN_107c9728(local_28,0x100000);
      }
    }
    if (local_b4 == -9) {
      if ((*(int *)((&DAT_1212d2dc)[local_28] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0x40) != 0)))) {
        if ((*local_24 & 0xfc000000) == 0x34000000) {
          if (((local_24[1] == 0x2029700) && (7 < (*local_24 >> 0x14 & 0x3f))) &&
             ((*local_24 >> 0x14 & 0x3f) < 0x10)) {
            local_b4 = 0;
          }
          goto LAB_1086403c;
        }
        iVar1 = FUN_10761b70(0x10000);
        if (iVar1 != 0) {
          FUN_1076193c("soc_schan_op: operation attempt timed out\n");
          *(int *)((&DAT_1212d2dc)[local_28] + 0xe874) =
               *(int *)((&DAT_1212d2dc)[local_28] + 0xe874) + 1;
        }
        FUN_1086190c(local_28);
      }
      else {
        iVar1 = FUN_10761b70(0x10000);
        if (iVar1 != 0) {
          FUN_1076193c("soc_schan_op: operation attempt timed out\n");
          *(int *)((&DAT_1212d2dc)[local_28] + 0xe874) =
               *(int *)((&DAT_1212d2dc)[local_28] + 0xe874) + 1;
        }
        FUN_1086190c(local_28);
      }
    }
    else {
LAB_1086403c:
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 2) == 0) {
        for (local_b8 = 0; (int)local_b8 < local_1c; local_b8 = local_b8 + 1) {
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              iVar1 = local_b8 << 2;
            }
            else {
              iVar1 = (local_b8 + 0x200) * 4;
            }
            uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,iVar1);
          }
          else {
            if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              uVar4 = local_b8 << 2 | local_b8 >> 0x1e;
            }
            else {
              uVar4 = (local_b8 + 0x200) * 4 | local_b8 + 0x200 >> 0x1e;
            }
            uVar4 = *(uint *)(((int)uVar4 >> 2) * 4 + *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          local_24[local_b8] = uVar4;
        }
      }
      else {
        for (local_b8 = 0; (int)local_b8 < local_1c; local_b8 = local_b8 + 1) {
          if (*(int *)(&DAT_12125c5c + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12125c60 + local_28 * 0x78))
                              (&DAT_12125c2c + local_28 * 0x78,
                               iVar3 * 0x1000 + 0x3100c + local_b8 * 4);
          }
          else {
            uVar4 = *(uint *)(((int)(iVar3 * 0x1000 + 0x3100c + local_b8 * 4) >> 2) * 4 +
                             *(int *)(&DAT_12125c5c + local_28 * 0x78));
          }
          local_24[local_b8] = uVar4;
        }
      }
      iVar1 = FUN_10761b70(2);
      if (iVar1 != 0) {
        FUN_10861dbc(local_28,local_24,local_1c);
      }
      *(int *)((&DAT_1212d2dc)[local_28] + 0xe830) =
           *(int *)((&DAT_1212d2dc)[local_28] + 0xe830) + 1;
    }
    FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0xe1e4));
    if ((local_b4 == -9) && (iVar1 = FUN_10761b70(0x200000), iVar1 != 0)) {
      FUN_10761a94(0x200000,"SchanTimeOut:soc_schan_op operation timed out\n");
      FUN_10861dbc(local_28,local_24,local_20);
    }
    break;
  case 0x24:
    *local_24 = *local_24 & 0x3ffffff | 0x94000000;
    local_b4 = 0;
    break;
  case 0x26:
    *local_24 = *local_24 & 0x3ffffff | 0x9c000000;
    local_b4 = 0;
    break;
  case 0x2a:
    *local_24 = *local_24 & 0x3ffffff | 0xac000000;
    local_b4 = 0;
    break;
  case 0x2c:
    *local_24 = *local_24 & 0x3ffffff | 0xb4000000;
    local_b4 = 0;
  }
  return local_b4;
}



/* === FUN_10619410 @ 0x10619410 (size=984) === */

/* WARNING: Removing unreachable block (ram,0x10619578) */
/* WARNING: Removing unreachable block (ram,0x1061954c) */
/* WARNING: Removing unreachable block (ram,0x106197b0) */

int FUN_10619410(uint param_1,uint param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  uint *local_10;
  
  local_1c = 0;
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_10643b10(param_1,&local_20);
    if (-1 < iVar1) {
      iVar1 = (int)local_14 >> 0x1a;
      if ((local_20 == 0) && (iVar1 != 10)) {
        iVar1 = -0x10;
      }
      else {
        if (local_14 >> 0x1a == 1) {
          if (local_14 >> 0x1a == 1) {
            local_14 = local_14 & 0x7ff;
          }
          else {
            local_14 = 0xffffffff;
          }
          *local_10 = local_14;
        }
        else if (local_14 == 0x14000000) {
          *local_10 = *(uint *)((&DAT_1212d2dc)[local_18] + 0x5ba0);
        }
        else if (iVar1 == 10) {
          *local_10 = local_14 & 0x7ff;
          if (((int)local_14 >> 0xb & 0x7fffU) != local_18) {
            return -0x12;
          }
        }
        else if (iVar1 == 2) {
          iVar1 = FUN_10645290(local_18,&local_24);
          if (iVar1 < 0) {
            return iVar1;
          }
          if ((int)local_14 >> 0x1a == 2) {
            uVar2 = (int)local_14 >> 0xb & 0x7fff;
            uVar3 = local_14 & 0x7ff;
          }
          else {
            uVar2 = 0xffffffff;
            uVar3 = 0xffffffff;
          }
          if (uVar2 == local_24) {
            *local_10 = uVar3;
          }
          else {
            if (local_20 < 2) {
              return -0x12;
            }
            iVar1 = FUN_106197e8(local_18,uVar2,&local_1c);
            if (iVar1 < 0) {
              return iVar1;
            }
            if (local_1c == 0) {
              return -0x12;
            }
            *local_10 = (uVar2 - local_24) * (*(int *)((&DAT_1212d2dc)[local_18] + 0xe0cc) + 1) +
                        uVar3;
          }
          if ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c38) & 0x80000) != 0) {
            FUN_1038b4a4(local_18,local_10);
          }
          if ((((int)*local_10 < 0) || (0x81 < (int)*local_10)) ||
             (*(int *)((&DAT_1212d2dc)[local_18] + (*local_10 + 0x1c84) * 4 + 4) == 0)) {
            return -0x12;
          }
        }
        else {
          if (iVar1 == 8) {
            return -0x12;
          }
          if (iVar1 != 0x11) {
            return -0x12;
          }
          *local_10 = local_14 & 0xffffff;
        }
        iVar1 = 0;
      }
    }
  }
  return iVar1;
}



/* === FUN_103230a4 @ 0x103230a4 (size=2372) === */

undefined4 FUN_103230a4(void)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  ssize_t sVar4;
  int iVar5;
  void *pvVar6;
  undefined4 uVar7;
  uint uVar8;
  int local_88;
  int local_84;
  uint local_7c;
  undefined4 local_78;
  int local_68 [2];
  uint local_60;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  char acStack_c [4];
  undefined4 local_8;
  
  local_8 = 0x50;
  if (DAT_11853c08 < 0) {
    DAT_11853c08 = open("/dev/linux-user-bde",0x101002);
    if (DAT_11853c08 < 0) {
      bVar2 = false;
      iVar3 = open("/proc/sys/kernel/osrelease",0);
      if (-1 < iVar3) {
        sVar4 = read(iVar3,acStack_c,4);
        if ((sVar4 == 4) && (iVar5 = strncmp(acStack_c,"2.4",3), iVar5 == 0)) {
          bVar2 = true;
        }
        close(iVar3);
      }
      if (bVar2) {
        system("/sbin/insmod linux-kernel-bde.o");
        system("/sbin/insmod linux-user-bde.o");
      }
      else {
        system("/sbin/insmod linux-kernel-bde.ko");
        system("/sbin/insmod linux-user-bde.ko");
      }
      DAT_11853c08 = open("/dev/linux-user-bde",0x101002);
      if (DAT_11853c08 < 0) {
        perror("open /dev/linux-user-bde: ");
        return 0xffffffff;
      }
    }
    FUN_1032301c(&DAT_11ebc218,&DAT_11ebc21c);
    DAT_11853c0c = open("/dev/mem",DAT_11853c14 | 2);
    if (DAT_11853c0c < 0) {
      perror("open /dev/mem: ");
      close(DAT_11853c08);
      uVar7 = 0xffffffff;
    }
    else if ((DAT_11ebc224 == 0) ||
            (DAT_11853c10 = open("/dev/linux-kernel-bde",0x101002), -1 < DAT_11853c10)) {
      memset(&DAT_11ebc1b4,0,0x50);
      local_68[0] = 0;
      local_60 = 0;
      iVar3 = FUN_10322de8(0x20004c01,local_68);
      if (iVar3 != 0) {
        FUN_11312544("_ioctl(LUBDE_GET_NUM_DEVICES, &devio) == 0",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                     ,0x2af);
      }
      DAT_11ebc204 = local_60;
      if (local_60 == 0) {
        puts("linux-user-bde: no devices");
      }
      local_68[0] = 1;
      iVar3 = FUN_10322de8(0x20004c01,local_68);
      if (iVar3 != 0) {
        FUN_11312544("_ioctl(LUBDE_GET_NUM_DEVICES, &devio) == 0",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                     ,0x2b7);
      }
      DAT_11ebc208 = local_60;
      if (local_60 == 0) {
        puts("linux-user-bde: no switching devices");
      }
      local_68[0] = 2;
      iVar3 = FUN_10322de8(0x20004c01,local_68);
      if (iVar3 != 0) {
        FUN_11312544("_ioctl(LUBDE_GET_NUM_DEVICES, &devio) == 0",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                     ,0x2bf);
      }
      DAT_11ebc20c = local_60;
      local_68[0] = 3;
      iVar3 = FUN_10322de8(0x20004c01,local_68);
      if (iVar3 != 0) {
        FUN_11312544("_ioctl(LUBDE_GET_NUM_DEVICES, &devio) == 0",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                     ,0x2c4);
      }
      DAT_11ebc210 = local_60;
      for (local_88 = 0; local_88 < (int)DAT_11ebc204; local_88 = local_88 + 1) {
        local_68[0] = local_88;
        local_60 = 0;
        local_5c = 0;
        local_58 = 0;
        local_54 = 0;
        iVar3 = FUN_10322de8(0x20004c0c,local_68);
        if (iVar3 != 0) {
          FUN_11312544("_ioctl(LUBDE_GET_DEVICE_TYPE, &devio) == 0",
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                       ,0x2d2);
        }
        local_7c = local_60;
        local_68[0] = local_88;
        iVar3 = FUN_10322de8(0x20004c02,local_68);
        if (iVar3 != 0) {
          FUN_11312544("_ioctl(LUBDE_GET_DEVICE, &devio) == 0",
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                       ,0x2d8);
        }
        pvVar6 = malloc(0x24);
        *(void **)(&DAT_11ebc1b4 + local_88 * 4) = pvVar6;
        memset(*(void **)(&DAT_11ebc1b4 + local_88 * 4),0,0x24);
        *(short *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 4) = (short)local_60;
        *(char *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 6) = (char)local_5c;
        if ((local_7c & 0x1008d) != 0) {
          local_78 = 0x10000;
          if ((local_7c & 0x40000000) == 0) {
            if ((local_7c & 0x20000000) == 0) {
              if ((int)local_7c < 0) {
                local_78 = 0x50000;
              }
            }
            else {
              local_78 = 0x40000;
            }
          }
          else {
            local_78 = 0x20000;
          }
          *(int *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 0x14) = local_58;
          sVar1 = *(short *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 4);
          if ((sVar1 == 0x7011) || (sVar1 == -0x5f00)) {
            local_78 = 0x10000000;
            local_7c = local_7c | 0x1000000;
          }
          else if (sVar1 == 0x4715) {
            local_78 = 0x300000;
          }
          iVar3 = *(int *)(&DAT_11ebc1b4 + local_88 * 4);
          uVar7 = FUN_10322e74(local_58,local_78);
          *(undefined4 *)(iVar3 + 0x18) = uVar7;
          *(undefined4 *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 8) =
               *(undefined4 *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 0x18);
          local_68[0] = local_88;
          local_60 = 1;
          iVar3 = FUN_10322de8(0x20004c1a,local_68);
          if ((iVar3 == 0) && (local_58 != 0)) {
            iVar3 = *(int *)(&DAT_11ebc1b4 + local_88 * 4);
            uVar7 = FUN_10322e74(local_58,local_78);
            *(undefined4 *)(iVar3 + 0x1c) = uVar7;
            for (local_84 = 0; local_84 < 8; local_84 = local_84 + 1) {
              uVar8 = *(uint *)(*(int *)(*(int *)(&DAT_11ebc1b4 + local_88 * 4) + 0x1c) +
                               (local_84 + 0xb00) * 4);
              if ((uVar8 & 1) == 0) {
                *(undefined4 *)(PTR_DAT_11e46d70 + local_84 * 8) = 0;
                *(undefined4 *)(PTR_DAT_11e46d70 + local_84 * 8 + 4) = 0;
              }
              else {
                *(uint *)(PTR_DAT_11e46d70 + local_84 * 8) = uVar8 & 0xfffff000;
                *(uint *)(PTR_DAT_11e46d70 + local_84 * 8 + 4) = uVar8 | 0xfff;
              }
            }
            if ((*(uint *)(PTR_DAT_11e46d70 + 0x10) & 0x1000) != 0) {
              local_7c = local_7c | 0x4000;
            }
          }
        }
        **(uint **)(&DAT_11ebc1b4 + local_88 * 4) = local_7c;
      }
      FUN_10325764();
      DAT_11ebc214 = FUN_10322e74(DAT_11ebc218,DAT_11ebc21c);
      if (DAT_11ebc214 == 0) {
        FUN_11312544("_dma_vbase = _mmap(_dma_pbase, _dma_size)",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                     ,0x340);
      }
      __nldbl_printf("DMA pool size: %d\n",DAT_11ebc21c);
      DAT_11ebc220 = FUN_10325a70(DAT_11ebc214,DAT_11ebc21c);
      if (DAT_11ebc220 == 0) {
        FUN_11312544("_dma_pool = mpool_create(_dma_vbase, _dma_size)",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                     ,0x342);
      }
      FUN_10325444(0);
      uVar7 = 0;
    }
    else {
      perror("open /dev/linux-kernel-bde: ");
      close(DAT_11853c08);
      close(DAT_11853c0c);
      uVar7 = 0xffffffff;
    }
  }
  else {
    uVar7 = 0;
  }
  return uVar7;
}



/* === FUN_1080c940 @ 0x1080c940 (size=4848) === */

int FUN_1080c940(int param_1,int param_2,uint param_3,uint param_4,void *param_5,void *param_6,
                uint *param_7)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int local_c8;
  uint local_c4;
  uint local_c0;
  uint *local_bc;
  uint local_b8;
  uint local_b4;
  uint local_94;
  uint local_90;
  uint local_8c [20];
  undefined1 auStack_3c [4];
  int local_38;
  uint local_34 [3];
  int local_28;
  int local_24;
  uint local_20;
  uint local_1c;
  void *local_18;
  void *local_14;
  uint *local_10;
  
  local_24 = param_2;
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c40) & 0x100) != 0) {
    if (param_2 == 0xcff) {
      local_24 = 0xcfe;
    }
    else if (param_2 == 0x1094) {
      local_24 = 0x1093;
    }
    else if (param_2 == 0x2e5) {
      local_24 = 0x26d;
    }
  }
  local_28 = param_1;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  local_10 = param_7;
  if ((((local_24 < 0) || (0x10e3 < local_24)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + local_24 * 4) == 0)
      ) || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                        local_24 * 4) & 2) == 0)) {
    FUN_11312544("SOC_MEM_IS_VALID(unit, mem)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x2535);
  }
  iVar2 = FUN_107958e0(local_28);
  if (iVar2 == 0) {
    FUN_11312544("soc_attached(unit)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x2536);
  }
  if (local_20 == 0xffffffff) {
    local_20 = *(uint *)((&DAT_1212d2dc)[local_28] + (local_24 + 0x2724) * 4 + 0x10);
  }
  if ((-1 < (int)local_20) && ((int)local_20 < 0x3a)) {
    if ((int)local_20 < 0x20) {
      uVar4 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x24) +
                                local_24 * 4) + 0x18) & 1 << (local_20 & 0x3f);
    }
    else {
      uVar4 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x24) +
                                local_24 * 4) + 0x1c) & 1 << (local_20 & 0x1f);
    }
    if ((uVar4 != 0) && (*(char *)((&DAT_1212d2dc)[local_28] + local_20 + 0x909c) != '\0')) {
      uVar4 = (int)(*(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x24) +
                              local_24 * 4) + 0x28) + 3) >> 2;
      FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_28] + local_24 * 700 + 0xe8f0),0xffffffff);
      if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c4c) & 0x4000) != 0) &&
         ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                   local_20 * 0x10) == 0x1f ||
          (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                   local_20 * 0x10) == 0x30)))) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0x2f18cc),0xffffffff);
      }
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
        uVar3 = *(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                          *(int *)((&DAT_1212d2dc)[local_28] + 0x5ba4) * 0x10 + 8) & 0x3f;
      }
      else {
        uVar3 = **(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x24) +
                           local_24 * 4) >> 0x16 & 7;
      }
      local_94 = uVar3 << 0xe | 0xa0000000;
      local_94 = (*(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                            local_20 * 0x10 + 8) & 0x3f) << 0x14 | local_94;
      if ((((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 0x100) == 0) ||
          ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x24) +
                       local_24 * 4) & 0x10000000) == 0)) &&
         (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 0x200) == 0 ||
          ((((local_24 != 0x7d6 && (local_24 != 0x83c)) && (local_24 != 0x82f)) &&
           (((local_24 != 0x82b && (local_24 != 0x837)) && (local_24 != 0x833)))))))) {
        local_94 = (local_1c & 3) << 1 | local_94;
      }
      local_94 = (uVar4 & 0x1f) << 9 | local_94;
      local_90 = FUN_107a8744(local_28,local_24,0,local_20,0,auStack_3c);
      if (((((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 0x100) != 0) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x24) +
                        local_24 * 4) & 0x10000000) != 0)) ||
          (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 0x200) != 0 &&
           ((((local_24 == 0x7d6 || (local_24 == 0x83c)) || (local_24 == 0x82f)) ||
            (((local_24 == 0x82b || (local_24 == 0x837)) || (local_24 == 0x833)))))))) &&
         ((local_1c != 0 && (local_1c != 0xffffffff)))) {
        if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 0x200) == 0) {
          uVar3 = FUN_107d141c(local_28,local_1c);
          local_90 = local_90 | ~uVar3 & 0xfffff;
        }
        else {
          local_90 = local_90 | ~local_1c & 0x3ff;
        }
      }
      memcpy(local_8c,local_18,uVar4 << 2);
      local_c8 = FUN_108623e4(local_28,&local_94,uVar4 + 2,uVar4 + 2,0);
      if ((local_94 & 0xfc000000) != 0xa4000000) {
        FUN_10761a94(0x200000,
                     "soc_mem_generic_lookup: invalid S-Channel reply, expected TABLE_LOOKUP_DONE_MSG:\n"
                    );
        FUN_10861dbc(local_28,&local_94,uVar4 + 2);
        if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c4c) & 0x4000) != 0) &&
           ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                     local_20 * 0x10) == 0x1f ||
            (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                     local_20 * 0x10) == 0x30)))) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0x2f18cc));
        }
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + local_24 * 700 + 0xe8f0));
        return -1;
      }
      if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c24) & 0x2000000) == 0) ||
         ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c24) & 0x4000000) != 0)) {
        local_c4 = local_90 >> 0x1a & 0xf;
      }
      else {
        local_c4 = local_90 >> 0x1c;
      }
      local_bc = local_8c;
      local_c0 = local_90 & 0xfffff;
      if (((local_94 & 1) == 0) && (local_c8 != -0xb)) {
        if (local_14 != (void *)0x0) {
          memcpy(local_14,local_bc,uVar4 << 2);
        }
        if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c40) & 0x1000000) != 0) &&
           (local_24 == 0x3fa)) {
          iVar2 = FUN_10efd19c(local_28,local_c0,&local_38,local_34);
          if (iVar2 < 0) {
            if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c4c) & 0x4000) != 0) &&
               ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                         local_20 * 0x10) == 0x1f ||
                (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                         local_20 * 0x10) == 0x30)))) {
              FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0x2f18cc));
            }
            FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + local_24 * 700 + 0xe8f0));
            return iVar2;
          }
          if (local_24 != local_38) {
            if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c4c) & 0x4000) != 0) &&
               ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                         local_20 * 0x10) == 0x1f ||
                (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                         local_20 * 0x10) == 0x30)))) {
              FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0x2f18cc));
            }
            FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + local_24 * 700 + 0xe8f0));
            return -1;
          }
          local_c0 = local_34[0];
        }
        if (local_10 != (uint *)0x0) {
          *local_10 = local_c0;
        }
        if (((int)local_c0 < 0) ||
           (*(int *)((&DAT_1212d324)[local_28] + local_24 * 0xec + 0x31bc) < (int)local_c0)) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (!bVar1) {
          FUN_10761a94(0x200000,"soc_mem_generic_lookup: invalid index %d for memory %s\n",local_c0,
                       (&PTR_s_ACTIONPROFILETABLE_11ab1c04)[local_24]);
          local_c8 = -1;
        }
      }
      else {
        if (local_10 != (uint *)0x0) {
          *local_10 = 0xffffffff;
        }
        if (local_c4 == 1) {
          local_c8 = -7;
          if ((((*(int *)((&DAT_1212d2dc)[local_28] + 0x10) == 0) &&
               ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0xc) != 0)) &&
              ((local_24 == 0x82b || (local_24 == 0x837)))) && (local_10 != (uint *)0x0)) {
            *local_10 = local_90 & 0xfffff;
          }
        }
        else if (*(char *)((&DAT_1212d2dc)[local_28] + 0x2f186d) == '\0') {
          local_c8 = -0xb;
        }
        else {
          iVar2 = *(int *)((&DAT_1212d2dc)[local_28] + (local_24 * 0xaf + local_20 + 0x3a3c) * 4 + 4
                          );
          if ((iVar2 != 0) && (*(char *)((&DAT_1212d2dc)[local_28] + 0x2f1868) == '\0')) {
            local_b8 = local_c0;
            local_b4 = 0xffffffff;
            if (((*(int *)((&DAT_1212d2dc)[local_28] + 0x10) == 0) &&
                ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0x10000000) != 0)) ||
               ((*(int *)((&DAT_1212d2dc)[local_28] + 0x10) == 0 &&
                ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0x8000000) != 0)))) {
              local_b8 = local_8c[0] & 0xffff;
              local_b4 = local_8c[0] >> 0x10;
            }
            local_c8 = FUN_1080c0a4(local_28,local_24,local_20,local_1c,local_18,local_14,local_b8,
                                    local_b4,local_10,iVar2,
                                    *(undefined4 *)
                                     ((&DAT_1212d2dc)[local_28] +
                                      (local_24 * 0xaf + local_20 + 0x3a74) * 4 + 0xc));
          }
        }
      }
      iVar2 = FUN_10761b70(4);
      if (iVar2 != 0) {
        FUN_1076193c("Lookup table[%s]: banks=%d",(&PTR_s_ACTIONPROFILETABLE_11ab1c04)[local_24],
                     local_1c);
        iVar2 = FUN_10761b70(0x10000);
        if (iVar2 != 0) {
          FUN_107ef4dc(local_28,local_24,local_bc);
        }
        if (local_c8 < 0) {
          if (local_c4 == 1) {
            FUN_1076193c(" Not found\n");
          }
          else {
            FUN_1076193c(" Fail\n");
          }
        }
        else {
          FUN_1076193c(" (index=%d)\n",local_c0);
        }
      }
      if (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c4c) & 0x4000) != 0) &&
         ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                   local_20 * 0x10) == 0x1f ||
          (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x30) +
                   local_20 * 0x10) == 0x30)))) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + 0x2f18cc));
      }
      FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_28] + local_24 * 700 + 0xe8f0));
      return local_c8;
    }
  }
  FUN_10761a94(0x8000000,"soc_mem_generic_lookup: invalid block %d for memory %s\n",local_20,
               (&PTR_s_ACTIONPROFILETABLE_11ab1c04)[local_24]);
  return -4;
}



/* === FUN_10803190 @ 0x10803190 (size=2636) === */

int FUN_10803190(int param_1,int param_2,undefined4 param_3,uint param_4,int param_5,int param_6,
                int param_7)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined *puVar4;
  int iVar5;
  int local_48;
  int local_44;
  uint local_1c;
  
  if ((((param_2 < 0) || (0x10e3 < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) == 0))
     || (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4)
          & 2) == 0 ||
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4)
          & 2) == 0)))) {
    return -2;
  }
  local_1c = param_4;
  if (param_4 == 0xffffffff) {
    local_1c = *(uint *)((&DAT_1212d2dc)[param_1] + (param_2 + 0x2724) * 4 + 0x10);
  }
  if (local_1c == 0xffffffff) {
    return -1;
  }
  if ((-1 < (int)local_1c) && ((int)local_1c < 0x3a)) {
    if ((int)local_1c < 0x20) {
      uVar2 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 0x18) & 1 << (local_1c & 0x3f);
    }
    else {
      uVar2 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 0x1c) & 1 << (local_1c & 0x1f);
    }
    if ((uVar2 != 0) && (*(char *)((&DAT_1212d2dc)[param_1] + local_1c + 0x909c) != '\0'))
    goto LAB_1080342c;
  }
  FUN_11312544("SOC_MEM_BLOCK_VALID(unit, mem, copyno)",
               "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
               ,0x1b67);
LAB_1080342c:
  if ((param_5 < *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                  param_2 * 4) + 0xc)) ||
     (*(int *)((&DAT_1212d324)[param_1] + param_2 * 0xec + 0x31bc) < param_5)) {
    FUN_11312544("soc_mem_index_valid(unit, mem, index_min)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x1b68);
  }
  if ((param_6 < *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                  param_2 * 4) + 0xc)) ||
     (*(int *)((&DAT_1212d324)[param_1] + param_2 * 0xec + 0x31bc) < param_6)) {
    FUN_11312544("soc_mem_index_valid(unit, mem, index_max)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x1b69);
  }
  if (param_6 < param_5) {
    FUN_11312544("index_min <= index_max",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x1b6a);
  }
  if (param_7 == 0) {
    FUN_11312544("buffer != NULL",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x1b6b);
  }
  piVar3 = (int *)(param_7 + -0x18);
  iVar1 = FUN_10760a3c(piVar3);
  if (iVar1 == 0) {
    iVar1 = FUN_107f5e94(param_1,param_2,local_1c);
    if (iVar1 != 0) {
      FUN_10761a94(0x200000,"ERROR:ATTN :%s:%d: Address:%p:probably not in shared memory region \n",
                   "soc_mem_array_read_range",0x1b7e,piVar3);
    }
  }
  else if ((*piVar3 == -0x55443323) &&
          (iVar1 = (uint)*(ushort *)
                          (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                   param_2 * 4) + 0x28) * ((param_6 - param_5) + 1),
          *(int *)(param_7 + -0x10) < iVar1)) {
    FUN_10761a94(0x8000000,"Some problem in calling :%s::%d:Desc:%s: Size:%u: length:%u\n",
                 "soc_mem_array_read_range",0x1b76,*(undefined4 *)(param_7 + -0x14),
                 *(undefined4 *)(param_7 + -0x10),iVar1);
  }
  local_44 = 0;
  if (local_1c == 0xffffffff) {
    puVar4 = &DAT_113c3ee4;
  }
  else {
    puVar4 = (undefined *)((&DAT_1212d2dc)[param_1] + (local_1c + 0x98f) * 0x10 + 0x10);
  }
  FUN_10761a94(4,"soc_mem_array_read_range: unit %d memory %s.%s [%d:%d]\n",param_1,
               (&PTR_s_ACTIONPROFILETABLE_11ab5f98)[param_2],puVar4,param_5,param_6);
  local_48 = param_5;
  if (*(int *)(&DAT_1212d36c + param_1 * 4) == 4) {
    for (; local_48 <= param_6; local_48 = local_48 + 1) {
      memcpy((void *)(param_7 +
                     ((int)(*(ushort *)
                             (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24
                                               ) + param_2 * 4) + 0x28) + 3) >> 2) * local_44 * 4),
             *(void **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 8),
             (uint)*(ushort *)
                    (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                             param_2 * 4) + 0x28));
      local_44 = local_44 + 1;
    }
    return 0;
  }
  iVar1 = FUN_107f5e94(param_1,param_2,local_1c);
  if ((((iVar1 != 0) && (iVar1 = FUN_10796190(param_1,"table_dma_enable",1), iVar1 != 0)) &&
      (*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0)) &&
     ((((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x7ffff67f) != 0 ||
       ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x10) != 0)) ||
      (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0 ||
       ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x20) != 0)))))) {
    iVar5 = *(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4);
    iVar1 = FUN_107fd344(param_1,param_2,param_3,local_1c,param_5,param_6,0,param_7);
    if (-1 < iVar1) {
      if ((*(int *)(iVar5 + 0x34) != 0) && ((*(uint *)(iVar5 + 0x3c) & 2) != 0)) {
        (**(code **)(iVar5 + 0x34))
                  (param_1,param_2,2,local_1c,param_5,param_6,param_7,*(undefined4 *)(iVar5 + 0x38))
        ;
      }
      return 0;
    }
    if (iVar1 != -0xb) {
      return iVar1;
    }
    if (*(char *)((&DAT_1212d2dc)[param_1] + 0x2f186d) == '\0') {
      return -0xb;
    }
    FUN_10761a94(0x10000,"Unit:%d Mem[%s] DMA fallback to pio.\n",param_1,
                 (&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_2]);
  }
  while( true ) {
    if (param_6 < local_48) {
      return 0;
    }
    iVar1 = FUN_10802b30(param_1,param_2,param_3,local_1c,local_48,
                         param_7 + ((int)(*(ushort *)
                                           (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] +
                                                                      0x2f26f4) + 0x24) +
                                                    param_2 * 4) + 0x28) + 3) >> 2) * local_44 * 4);
    if (iVar1 < 0) break;
    local_48 = local_48 + 1;
    local_44 = local_44 + 1;
  }
  return iVar1;
}



/* === FUN_10820164 @ 0x10820164 (size=1432) === */

undefined4 FUN_10820164(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int local_14;
  uint local_10;
  
  if ((((param_2 < 0) || (0x10e3 < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) == 0))
     || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4)
         & 2) == 0)) {
    FUN_11312544("SOC_MEM_IS_VALID(unit, mem)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x3a55);
  }
  iVar1 = FUN_107958e0(param_1);
  if (iVar1 == 0) {
    FUN_11312544("soc_attached(unit)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x3a56);
  }
  if ((((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
        8) == 0) &&
      ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
       0x20000) == 0)) &&
     (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
       0x80000) == 0 &&
      (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
        0x200000) == 0 && (param_2 != 0x1092)))))) {
    FUN_11312544("soc_mem_is_sorted(unit, mem) || soc_mem_is_hashed(unit, mem) || soc_mem_is_cam(unit, mem) || soc_mem_is_cmd(unit, mem) || mem == VLAN_TABm"
                 ,
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x3a5b);
  }
  local_10 = param_3;
  if (param_3 == 0xffffffff) {
    local_10 = *(uint *)((&DAT_1212d2dc)[param_1] + (param_2 + 0x2724) * 4 + 0x10);
  }
  if ((-1 < (int)local_10) && ((int)local_10 < 0x3a)) {
    if ((int)local_10 < 0x20) {
      uVar3 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 0x18) & 1 << (local_10 & 0x3f);
    }
    else {
      uVar3 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 0x1c) & 1 << (local_10 & 0x1f);
    }
    if ((uVar3 != 0) && (*(char *)((&DAT_1212d2dc)[param_1] + local_10 + 0x909c) != '\0')) {
      if (param_2 == 0x1092) {
        uVar2 = FUN_10820044(param_1);
        return uVar2;
      }
      if (param_2 == 0xcff) {
        local_14 = 0xcfe;
      }
      else {
        local_14 = param_2;
        if (param_2 < 0xd00) {
          if ((param_2 != 0x269) && (param_2 == 0x2e5)) {
            local_14 = 0x26d;
          }
        }
        else if (param_2 == 0x1085) {
          if (((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
              (((((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x7e6c247f) != 0 ||
                 ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x10) != 0)) ||
                ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)) ||
               ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x20) != 0)))) &&
             ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c40) & 0x100) == 0)) {
            local_14 = 0x1093;
          }
        }
        else if (param_2 == 0x1094) {
          local_14 = 0x1093;
        }
      }
      return *(undefined4 *)
              ((&DAT_1212d324)[param_1] + (local_14 * 0x3b + local_10 + 0xc34) * 4 + 4);
    }
  }
  FUN_10761a94(0x8000000,"soc_mem_entries: invalid block %d for memory %s\n",local_10,
               (&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_2]);
  return 0xfffffffc;
}



/* === FUN_10847ab4 @ 0x10847ab4 (size=544) === */

undefined4
FUN_10847ab4(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 local_34;
  undefined1 local_30 [8];
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_34 = 0;
  if (((param_2 < 0) || (0x901f < param_2)) ||
     (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
  {
    uVar1 = 0xfffffffc;
  }
  else {
    local_28 = param_1;
    local_24 = param_2;
    local_20 = param_3;
    local_1c = param_4;
    local_18 = param_5;
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                           param_2 * 4) + 0x10) & 0x100001) != 0) {
      FUN_1076193c("reg %s is > 32 bit , but called with soc_reg32_get\n",
                   (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2]);
    }
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                           local_24 * 4) + 0x10) & 0x100001) != 0) {
      FUN_11312544("!SOC_REG_IS_ABOVE_32(unit, reg)",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                   ,0x4a4);
    }
    uVar1 = FUN_108508ac(local_28,local_24,local_20,local_1c,&local_34,local_30);
    if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
      uVar1 = FUN_10847350(local_28,uVar1,local_18);
    }
    else {
      uVar1 = FUN_10846528(local_28,local_34,local_30[0],uVar1,local_18);
    }
  }
  return uVar1;
}



/* === FUN_10848708 @ 0x10848708 (size=540) === */

int FUN_10848708(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_68;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [24];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  undefined4 local_14;
  
  local_68 = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_18 = param_5;
  local_14 = param_6;
  do {
    if (99 < local_68) {
      FUN_10761a94(0x200000,"soc_reg64_write_iterative: operation failed:\n");
      return -0xb;
    }
    FUN_10880ed8(auStack_40,25000,0);
    do {
      iVar1 = FUN_11313a38();
      iVar2 = FUN_108469c0(local_28,0x5ef7,local_20,0,&local_48);
      iVar3 = FUN_1084c8b4(local_28,0x5ef7,local_48,local_44,0xdd79);
      if ((iVar3 != 0) || (iVar2 < 0)) break;
      iVar4 = FUN_10880f30(auStack_40);
    } while (iVar4 == 0);
    if (iVar2 < 0) {
      return iVar2;
    }
    if (iVar3 != 0) {
      iVar2 = FUN_1084a984(local_28,local_24,local_18,local_14);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_108469c0(local_28,0x5ef7,local_20,0,&local_48);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_1084c8b4(local_28,0x5ef7,local_48,local_44,0xdd79);
      iVar3 = FUN_11313a38();
      if ((iVar2 != 0) && (iVar3 - iVar1 < 20000)) {
        return 0;
      }
      FUN_10761a94(0x8010000,"soc_reg64_write_iterative: WARNING: iteration %d PLL went out of lock"
                   ,local_68);
    }
    local_68 = local_68 + 1;
  } while( true );
}



/* === FUN_1083bfbc @ 0x1083bfbc (size=1016) === */

int FUN_1083bfbc(int param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
                int param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int local_58;
  int local_4c;
  int local_48;
  int local_44;
  undefined1 auStack_40 [24];
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  local_4c = 0;
  local_48 = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  local_10 = param_7;
  FUN_10761a94(0x50000,"entered soc_phyctrl_redirect_loopback_set: unit %d, port %d, enable %d\n",
               param_1,param_2,param_6);
  FUN_1083a2a0(local_28,local_24,local_20,&local_48,&local_4c);
  if (local_18 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x40;
  }
  *(uint *)(local_4c + 0xf0) = *(uint *)(local_4c + 0xf0) | uVar1;
  iVar2 = *(int *)(*(int *)(&DAT_12136ddc + local_28 * 4) + local_24 * 4);
  iVar3 = *(int *)(*(int *)(&DAT_12136d94 + local_28 * 4) + local_24 * 4);
  if ((iVar3 == 0) && (iVar2 == 0)) {
    local_58 = -0x11;
  }
  else {
    if (*(int *)(local_48 + 0xfc) == 0) {
      local_58 = -4;
    }
    else if (*(int *)(*(int *)(local_48 + 0xfc) + 0x44) == 0) {
      local_58 = -0x10;
    }
    else {
      local_58 = (**(code **)(*(int *)(local_48 + 0xfc) + 0x44))(local_28,local_24,local_14);
    }
    if (((local_10 != 0) &&
        (((*(int *)((&DAT_1212d2dc)[local_28] + 0x10) != 0 ||
          (((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0x80000) == 0 &&
           ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x14) & 0x40) == 0)))) && (-1 < local_58)))) &&
       (((local_14 != 0 && (iVar2 != 0)) &&
        (((*(uint *)(*(int *)(&DAT_12136e24 + local_28 * 4) + local_24 * 0x18 + 0xc) & 4) != 0 ||
         (iVar3 == 0)))))) {
      FUN_10880ed8(auStack_40,5000000,0);
      local_44 = 0;
      if ((*(int *)(iVar2 + 0xfc) != 0) && (*(int *)(*(int *)(iVar2 + 0xfc) + 0xc) != 0)) {
        (**(code **)(*(int *)(iVar2 + 0xfc) + 0xc))(local_28,local_24,&local_44);
      }
      do {
        if (*(int *)(iVar2 + 0xfc) == 0) {
          local_58 = -4;
        }
        else if (*(int *)(*(int *)(iVar2 + 0xfc) + 0xc) == 0) {
          local_58 = -0x10;
        }
        else {
          local_58 = (**(code **)(*(int *)(iVar2 + 0xfc) + 0xc))(local_28,local_24,&local_44);
        }
      } while (((local_44 == 0) && (-1 < local_58)) &&
              (iVar3 = FUN_10880f30(auStack_40), iVar3 == 0));
      if (local_44 == 0) {
        FUN_10761a94(0x8000000,"soc_phyctrl_redirect_loopback_set: u=%d p=%d TIMEOUT\n",local_28,
                     local_24);
        local_58 = -9;
      }
    }
    *(uint *)(local_4c + 0xf0) = *(uint *)(local_4c + 0xf0) & 0xffffff7f;
    *(uint *)(local_4c + 0xf0) = *(uint *)(local_4c + 0xf0) & 0xffffffbf;
  }
  return local_58;
}



/* === FUN_107a213c @ 0x107a213c (size=2748) === */

void FUN_107a213c(int param_1,uint *param_2,int param_3,int param_4,int param_5)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *local_58;
  uint local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint local_44;
  int *local_40;
  int *local_3c;
  int *local_38;
  
  local_58 = (int *)0x0;
  local_40 = (int *)param_2[0xb];
  local_38 = local_40;
  if ((*local_40 != param_4) &&
     (local_38 = local_40 + (*(ushort *)((int)param_2 + 0x2a) - 1) * 3, *local_38 != param_4)) {
    local_3c = local_40 + (uint)(*(ushort *)((int)param_2 + 0x2a) >> 1) * 3;
    while ((((local_40 < local_38 && (local_3c < local_38)) && (*local_40 != param_4)) &&
           (*local_3c != param_4))) {
      if (param_4 < *local_3c) {
        local_38 = local_3c + -3;
      }
      else {
        if (param_4 <= *local_3c) break;
        local_40 = local_3c + 3;
      }
      uVar3 = ((int)local_38 - (int)local_40 >> 2) * -0x55555555 + 1;
      local_3c = local_40 + (((int)uVar3 >> 1) + (uint)((int)uVar3 < 0 && (uVar3 & 1) != 0)) * 3;
    }
    if (*local_3c == param_4) {
      local_58 = local_3c;
      local_38 = local_58;
    }
    else {
      local_38 = local_58;
      if (*local_40 == param_4) {
        local_58 = local_40;
        local_38 = local_58;
      }
    }
  }
  local_58 = local_38;
  if (local_58 == (int *)0x0) {
    FUN_1076193c("mem %s field %s is invalid\n",(&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_1],
                 (&PTR_DAT_11d34bbc)[param_4]);
    FUN_11312544("fieldinfo",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                 ,0x36e);
  }
  iVar2 = FUN_107a065c(local_58,param_5);
  if (iVar2 == 0) {
    FUN_1076193c("mem %s field %s value does not fit\n",
                 (&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_1],(&PTR_DAT_11d34bbc)[param_4]);
    iVar2 = FUN_107a065c(local_58,param_5);
    if (iVar2 == 0) {
      FUN_11312544("_soc_field_value_fit(fieldinfo, fldbuf)",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                   ,0x37d);
    }
  }
  uVar1 = *(ushort *)((int)local_58 + 6);
  local_48 = (uint)uVar1;
  if ((*(ushort *)(local_58 + 2) & 1) == 0) {
    local_44 = (uint)*(ushort *)(local_58 + 1);
    while (0 < (int)local_44) {
      local_44 = local_44 - 1;
      iVar2 = (int)local_48 >> 5;
      if ((*param_2 & 0x8000000) == 0) {
        iVar4 = iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0);
      }
      else {
        iVar4 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) -
                (iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0));
      }
      if ((*param_2 & 0x8000000) == 0) {
        iVar5 = iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0);
      }
      else {
        iVar5 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) -
                (iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0));
      }
      *(uint *)(param_3 + iVar4 * 4) = *(uint *)(param_3 + iVar5 * 4) & ~(1 << (local_48 & 0x1f));
      if ((*param_2 & 0x8000000) == 0) {
        iVar4 = iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0);
      }
      else {
        iVar4 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) -
                (iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0));
      }
      if ((*param_2 & 0x8000000) == 0) {
        iVar2 = iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0);
      }
      else {
        iVar2 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) -
                (iVar2 + (uint)((int)local_48 < 0 && (local_48 & 0x1f) != 0));
      }
      *(uint *)(param_3 + iVar4 * 4) =
           *(uint *)(param_3 + iVar2 * 4) |
           (*(uint *)(param_5 +
                     (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                     4) >> (local_44 & 0x1f) & 1) << (local_48 & 0x1f);
      local_48 = local_48 + 1;
    }
  }
  else {
    local_4c = (int)local_48 >> 5;
    local_48 = local_48 & 0x1f;
    local_50 = 0;
    for (local_44 = (uint)*(ushort *)(local_58 + 1); iVar2 = local_4c, 0 < (int)local_44;
        local_44 = local_44 - 0x20) {
      if ((uVar1 & 0x1f) == 0) {
        if ((int)local_44 < 0x20) {
          if ((*param_2 & 0x8000000) == 0) {
            iVar4 = local_4c << 2;
          }
          else {
            iVar4 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
          }
          if ((*param_2 & 0x8000000) == 0) {
            iVar5 = local_4c << 2;
          }
          else {
            iVar5 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
          }
          *(uint *)(param_3 + iVar4) = *(uint *)(param_3 + iVar5) & ~((1 << (local_44 & 0x3f)) - 1U)
          ;
          if ((*param_2 & 0x8000000) == 0) {
            local_4c = local_4c << 2;
          }
          else {
            local_4c = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
          }
          *(uint *)(param_3 + local_4c) =
               *(uint *)(param_3 + local_4c) | *(int *)(param_5 + local_50 * 4) << local_48;
        }
        else {
          if ((*param_2 & 0x8000000) == 0) {
            local_4c = local_4c << 2;
          }
          else {
            local_4c = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
          }
          *(undefined4 *)(param_3 + local_4c) = *(undefined4 *)(param_5 + local_50 * 4);
        }
      }
      else {
        if ((int)local_44 < 0x20) {
          local_54 = (1 << (local_44 & 0x3f)) - 1;
        }
        else {
          local_54 = 0xffffffff;
        }
        if ((*param_2 & 0x8000000) == 0) {
          iVar4 = local_4c << 2;
        }
        else {
          iVar4 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
        }
        if ((*param_2 & 0x8000000) == 0) {
          iVar5 = local_4c << 2;
        }
        else {
          iVar5 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
        }
        *(uint *)(param_3 + iVar4) = *(uint *)(param_3 + iVar5) & ~(local_54 << local_48);
        if ((*param_2 & 0x8000000) == 0) {
          iVar4 = local_4c << 2;
        }
        else {
          iVar4 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c) * 4;
        }
        local_4c = local_4c + 1;
        *(uint *)(param_3 + iVar4) =
             *(uint *)(param_3 + iVar4) | *(int *)(param_5 + local_50 * 4) << local_48;
        if ((int)(0x20 - local_48) < (int)local_44) {
          iVar4 = local_4c;
          if ((*param_2 & 0x8000000) != 0) {
            iVar4 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c;
          }
          iVar5 = local_4c;
          if ((*param_2 & 0x8000000) != 0) {
            iVar5 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c;
          }
          *(uint *)(param_3 + iVar4 * 4) =
               *(uint *)(param_3 + iVar5 * 4) & ~(local_54 >> (0x20 - local_48 & 0x3f));
          iVar4 = local_4c;
          if ((*param_2 & 0x8000000) != 0) {
            iVar4 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c;
          }
          if ((*param_2 & 0x8000000) != 0) {
            local_4c = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_4c;
          }
          *(uint *)(param_3 + iVar4 * 4) =
               *(uint *)(param_3 + local_4c * 4) |
               *(uint *)(param_5 + local_50 * 4) >> (0x20 - local_48 & 0x3f) & (1 << local_48) - 1U;
        }
      }
      local_4c = iVar2 + 1;
      local_50 = local_50 + 1;
    }
  }
  return;
}



