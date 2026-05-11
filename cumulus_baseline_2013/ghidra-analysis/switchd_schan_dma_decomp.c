/* SCHAN engine + DMA setup + packet I/O decomp */

/* === FUN_10861634 (size=8176) === */

int FUN_10861634(int param_1,uint *param_2,int param_3,int param_4,int param_5)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
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
  undefined4 local_8;
  
  local_8 = 0x50;
  iVar5 = *(int *)((&DAT_1212b9c4)[param_1] + 0xe1fc);
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  iVar2 = FUN_11311714();
  if (iVar2 != 0) {
    FUN_113113b0("! sal_int_context()",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/schan.c"
                 ,0x17f);
  }
  if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) &&
     ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0)) {
    iVar2 = 0x14;
  }
  else {
    iVar2 = 0x16;
  }
  if (iVar2 < local_20) {
    FUN_113113b0("dwc_write <= CMIC_SCHAN_WORDS(unit)",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/schan.c"
                 ,0x180);
  }
  if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) &&
     ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0)) {
    iVar2 = 0x14;
  }
  else {
    iVar2 = 0x16;
  }
  if (iVar2 < local_1c) {
    FUN_113113b0("dwc_read <= CMIC_SCHAN_WORDS(unit)",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/schan.c"
                 ,0x181);
  }
  if (((*(int *)(&DAT_1212ba54 + local_28 * 4) != 1) ||
      (*(int *)((&DAT_1212b9c4)[local_28] + 0xe6d0) != 0)) &&
     (*(int *)(&DAT_1212ba54 + local_28 * 4) != 4)) goto LAB_10861ae8;
  switch(*local_24 >> 0x1a) {
  case 7:
    if (*(int *)(&DAT_1212ba54 + local_28 * 4) == 4) {
      memset(local_24,0,0x58);
      *local_24 = *local_24 & 0x3ffffff | 0x20000000;
      return 0;
    }
    goto LAB_10861ae8;
  default:
    goto LAB_10861ae8;
  case 9:
    local_b4 = 0;
    break;
  case 0xb:
    if (*(int *)(&DAT_1212ba54 + local_28 * 4) == 4) {
      memset(local_24,0,0x58);
      *local_24 = *local_24 & 0x3ffffff | 0x30000000;
      return 0;
    }
    goto LAB_10861ae8;
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
    if (*(int *)(&DAT_1212ba54 + local_28 * 4) == 4) {
      return -7;
    }
    goto LAB_10861ae8;
  case 0x1a:
    *local_24 = *local_24 & 0x3ffffff | 0x6c000000;
    local_b4 = 0;
    break;
  case 0x1c:
    *local_24 = *local_24 & 0x3ffffff | 0x74000000;
    local_b4 = 0;
    break;
  case 0x20:
    if (*(int *)(&DAT_1212ba54 + local_28 * 4) == 4) {
      *local_24 = *local_24 & 0x3ffffff | 0x84000000;
      return -7;
    }
    goto LAB_10861ae8;
  case 0x22:
    if (*(int *)(&DAT_1212ba54 + local_28 * 4) == 4) {
      *local_24 = *local_24 & 0x3ffffff | 0x8c000000;
      return -7;
    }
LAB_10861ae8:
    FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xe1e4),0xffffffff);
    iVar2 = FUN_10760db0(2);
    if (iVar2 != 0) {
      uVar3 = FUN_10860a48(*local_24 >> 0x1a);
      FUN_10760b7c("S-CHANNEL %s: (unit %d)\n",uVar3,local_28);
      FUN_1086100c(local_28,local_24,local_20);
    }
    local_b4 = 0;
    for (local_b8 = 0; (int)local_b8 < local_20; local_b8 = local_b8 + 1) {
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
        if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
            iVar2 = local_b8 << 2;
          }
          else {
            iVar2 = (local_b8 + 0x200) * 4;
          }
          (**(code **)(&DAT_1212434c + local_28 * 0x78))
                    (&DAT_12124314 + local_28 * 0x78,iVar2,local_24[local_b8]);
        }
        else {
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
            uVar4 = local_b8 << 2 | local_b8 >> 0x1e;
          }
          else {
            uVar4 = (local_b8 + 0x200) * 4 | local_b8 + 0x200 >> 0x1e;
          }
          *(uint *)(((int)uVar4 >> 2) * 4 + *(int *)(&DAT_12124344 + local_28 * 0x78)) =
               local_24[local_b8];
        }
      }
      else if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
        (**(code **)(&DAT_1212434c + local_28 * 0x78))
                  (&DAT_12124314 + local_28 * 0x78,iVar5 * 0x1000 + 0x3100c + local_b8 * 4,
                   local_24[local_b8]);
      }
      else {
        *(uint *)(((int)(iVar5 * 0x1000 + 0x3100c + local_b8 * 4) >> 2) * 4 +
                 *(int *)(&DAT_12124344 + local_28 * 0x78)) = local_24[local_b8];
      }
    }
    if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
      if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
        (**(code **)(&DAT_1212434c + local_28 * 0x78))(&DAT_12124314 + local_28 * 0x78,0x50,0x80);
      }
      else {
        *(undefined4 *)(*(int *)(&DAT_12124344 + local_28 * 0x78) + 0x50) = 0x80;
      }
    }
    else if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
      pcVar1 = *(code **)(&DAT_1212434c + local_28 * 0x78);
      iVar2 = local_28 * 0x78;
      if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
        uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                          (&DAT_12124314 + local_28 * 0x78,(iVar5 + 0x31) * 0x1000);
      }
      else {
        uVar4 = *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 +
                         *(int *)(&DAT_12124344 + local_28 * 0x78));
      }
      (*pcVar1)(&DAT_12124314 + iVar2,(iVar5 + 0x31) * 0x1000,uVar4 | 1);
    }
    else {
      iVar2 = *(int *)(&DAT_12124344 + local_28 * 0x78);
      if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
        uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                          (&DAT_12124314 + local_28 * 0x78,(iVar5 + 0x31) * 0x1000);
      }
      else {
        uVar4 = *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 +
                         *(int *)(&DAT_12124344 + local_28 * 0x78));
      }
      *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 + iVar2) = uVar4 | 1;
    }
    if ((local_18 == 0) || (*(int *)((&DAT_1212b9c4)[local_28] + 0xe6c4) == 0)) {
      FUN_10880128(auStack_98,*(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xe6bc),100);
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
        do {
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,0x50);
          }
          else {
            uVar4 = *(uint *)(*(int *)(&DAT_12124344 + local_28 * 0x78) + 0x50);
          }
          if ((uVar4 & 2) != 0) goto LAB_10862d58;
          iVar2 = FUN_10880180(auStack_98);
        } while (iVar2 == 0);
        local_b4 = -9;
LAB_10862d58:
        if (local_b4 == 0) {
          FUN_10760cd4(2,"  Done in %d polls\n",local_8c);
        }
        if ((uVar4 & 0x200000) != 0) {
          local_b4 = -0xb;
          FUN_10760cd4(2,"  NAK received from SCHAN.\n");
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              uVar3 = 4;
            }
            else {
              uVar3 = 0x804;
            }
            local_80 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                                 (&DAT_12124314 + local_28 * 0x78,uVar3);
          }
          else {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              iVar2 = 4;
            }
            else {
              iVar2 = 0x804;
            }
            local_80 = *(uint *)(iVar2 + *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          switch(*local_24 >> 0x1a) {
          case 7:
          case 0xb:
switchD_10862ef0_caseD_7:
            FUN_10866c44(local_28,local_24[1],*local_24 >> 0x14 & 0x3f,
                         (*local_24 & 0xfc000000) == 0x2c000000,0);
            break;
          default:
            break;
          case 0x24:
          case 0x26:
          case 0x28:
            if ((local_80 & 0x3c000000) == 0x3c000000) goto switchD_10862ef0_caseD_7;
          }
        }
        if (((uVar4 & 0x100000) != 0) &&
           ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c3c) & 0x400) != 0)) {
          local_b4 = -0xb;
          FUN_10760cd4(0x200000,"  SER Parity Check Error.\n");
          FUN_1130f154(FUN_10866eb8,local_28,local_24[1],0,0,0);
        }
        if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c14) & 0x200) != 0) &&
           ((uVar4 & 0x400000) != 0)) {
          local_b4 = -9;
        }
        if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
          (**(code **)(&DAT_1212434c + local_28 * 0x78))(&DAT_12124314 + local_28 * 0x78,0x50,1);
        }
        else {
          *(undefined4 *)(*(int *)(&DAT_12124344 + local_28 * 0x78) + 0x50) = 1;
        }
      }
      else {
        do {
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,(iVar5 + 0x31) * 0x1000);
          }
          else {
            uVar4 = *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 +
                             *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          if ((uVar4 & 2) != 0) goto LAB_10862638;
          iVar2 = FUN_10880180(auStack_98);
        } while (iVar2 == 0);
        local_b4 = -9;
LAB_10862638:
        if (local_b4 == 0) {
          FUN_10760cd4(2,"  Done in %d polls\n",local_8c);
        }
        if ((uVar4 & 0x200000) != 0) {
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              uVar3 = 4;
            }
            else {
              uVar3 = 0x804;
            }
            local_80 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                                 (&DAT_12124314 + local_28 * 0x78,uVar3);
          }
          else {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              iVar2 = 4;
            }
            else {
              iVar2 = 0x804;
            }
            local_80 = *(uint *)(iVar2 + *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          local_b4 = -0xb;
          FUN_10760cd4(2,"  NAK received from SCHAN.\n");
          switch(*local_24 >> 0x1a) {
          case 7:
          case 0xb:
switchD_108627d0_caseD_7:
            FUN_10866c44(local_28,local_24[1],*local_24 >> 0x14 & 0x3f,
                         (*local_24 & 0xfc000000) == 0x2c000000,0);
          default:
            break;
          case 0x24:
          case 0x26:
          case 0x28:
            if ((local_80 & 0x3c000000) == 0x3c000000) goto switchD_108627d0_caseD_7;
          }
        }
        if (((uVar4 & 0x100000) != 0) &&
           ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c3c) & 0x400) != 0)) {
          local_b4 = -0xb;
          FUN_10760cd4(0x200000,"  SER Parity Check Error.\n");
          FUN_1130f154(FUN_10866eb8,local_28,local_24[1],0,0,0);
        }
        if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c14) & 0x200) != 0) &&
           ((uVar4 & 0x400000) != 0)) {
          local_b4 = -9;
        }
        if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c44) & 0x1000) != 0) {
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            uVar3 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,iVar5 * 0x1000 + 0x31008);
          }
          else {
            uVar3 = *(undefined4 *)
                     ((iVar5 * 0x1000 + 0x31008 >> 2) * 4 +
                     *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          iVar2 = FUN_1084b1d8(local_28,0xce2,uVar3,0x432c);
          if (iVar2 != 0) {
            local_b4 = -0xb;
            FUN_10760cd4(0x200000,"  ERRBIT received in CMIC_SCHAN_ERR.\n");
          }
        }
        if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
          pcVar1 = *(code **)(&DAT_1212434c + local_28 * 0x78);
          iVar2 = local_28 * 0x78;
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,(iVar5 + 0x31) * 0x1000);
          }
          else {
            uVar4 = *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 +
                             *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          (*pcVar1)(&DAT_12124314 + iVar2,(iVar5 + 0x31) * 0x1000,uVar4 & 0xfffffffd);
        }
        else {
          iVar2 = *(int *)(&DAT_12124344 + local_28 * 0x78);
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,(iVar5 + 0x31) * 0x1000);
          }
          else {
            uVar4 = *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 +
                             *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          *(uint *)(((iVar5 + 0x31) * 0x1000 >> 2) * 4 + iVar2) = uVar4 & 0xfffffffd;
        }
      }
    }
    else {
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
        FUN_107b9e0c(local_28,1);
      }
      else {
        FUN_107c88fc(local_28,0x100000);
      }
      iVar2 = FUN_10324874(*(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xe6c0),
                           *(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xe6bc));
      if (iVar2 == 0) {
        FUN_10760cd4(2,"  Interrupt received\n");
        if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0xe6cc) & 0x200000) != 0) {
            local_b4 = -0xb;
          }
          if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c14) & 0x200) != 0) &&
             ((*(uint *)((&DAT_1212b9c4)[local_28] + 0xe6cc) & 0x400000) != 0)) {
            local_b4 = -9;
          }
        }
        else {
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0xe6cc) & 0x200000) != 0) {
            local_b4 = -0xb;
          }
          if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c14) & 0x200) != 0) &&
             ((*(uint *)((&DAT_1212b9c4)[local_28] + 0xe6cc) & 0x400000) != 0)) {
            local_b4 = -9;
          }
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c44) & 0x1000) != 0) {
            if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
              uVar3 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                                (&DAT_12124314 + local_28 * 0x78,iVar5 * 0x1000 + 0x31008);
            }
            else {
              uVar3 = *(undefined4 *)
                       ((iVar5 * 0x1000 + 0x31008 >> 2) * 4 +
                       *(int *)(&DAT_12124344 + local_28 * 0x78));
            }
            iVar2 = FUN_1084b1d8(local_28,0xce2,uVar3,0x432c);
            if (iVar2 != 0) {
              local_b4 = -0xb;
              FUN_10760cd4(0x200000,"  ERRBIT received in CMIC_SCHAN_ERR.\n");
            }
          }
        }
      }
      else {
        local_b4 = -9;
      }
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
        FUN_107b9fac(local_28,1);
      }
      else {
        FUN_107c8968(local_28,0x100000);
      }
    }
    if (local_b4 == -9) {
      if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)))) {
        if ((*local_24 & 0xfc000000) == 0x34000000) {
          if (((local_24[1] == 0x2029700) && (7 < (*local_24 >> 0x14 & 0x3f))) &&
             ((*local_24 >> 0x14 & 0x3f) < 0x10)) {
            local_b4 = 0;
          }
          goto LAB_1086328c;
        }
        iVar5 = FUN_10760db0(0x10000);
        if (iVar5 != 0) {
          FUN_10760b7c("soc_schan_op: operation attempt timed out\n");
          *(int *)((&DAT_1212b9c4)[local_28] + 0xe874) =
               *(int *)((&DAT_1212b9c4)[local_28] + 0xe874) + 1;
        }
        FUN_10860b5c(local_28);
      }
      else {
        iVar5 = FUN_10760db0(0x10000);
        if (iVar5 != 0) {
          FUN_10760b7c("soc_schan_op: operation attempt timed out\n");
          *(int *)((&DAT_1212b9c4)[local_28] + 0xe874) =
               *(int *)((&DAT_1212b9c4)[local_28] + 0xe874) + 1;
        }
        FUN_10860b5c(local_28);
      }
    }
    else {
LAB_1086328c:
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 2) == 0) {
        for (local_b8 = 0; (int)local_b8 < local_1c; local_b8 = local_b8 + 1) {
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              iVar5 = local_b8 << 2;
            }
            else {
              iVar5 = (local_b8 + 0x200) * 4;
            }
            uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,iVar5);
          }
          else {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c0c) & 0x400000) == 0) {
              uVar4 = local_b8 << 2 | local_b8 >> 0x1e;
            }
            else {
              uVar4 = (local_b8 + 0x200) * 4 | local_b8 + 0x200 >> 0x1e;
            }
            uVar4 = *(uint *)(((int)uVar4 >> 2) * 4 + *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          local_24[local_b8] = uVar4;
        }
      }
      else {
        for (local_b8 = 0; (int)local_b8 < local_1c; local_b8 = local_b8 + 1) {
          if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_28 * 0x78))
                              (&DAT_12124314 + local_28 * 0x78,
                               iVar5 * 0x1000 + 0x3100c + local_b8 * 4);
          }
          else {
            uVar4 = *(uint *)(((int)(iVar5 * 0x1000 + 0x3100c + local_b8 * 4) >> 2) * 4 +
                             *(int *)(&DAT_12124344 + local_28 * 0x78));
          }
          local_24[local_b8] = uVar4;
        }
      }
      iVar5 = FUN_10760db0(2);
      if (iVar5 != 0) {
        FUN_1086100c(local_28,local_24,local_1c);
      }
      *(int *)((&DAT_1212b9c4)[local_28] + 0xe830) =
           *(int *)((&DAT_1212b9c4)[local_28] + 0xe830) + 1;
    }
    FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xe1e4));
    if ((local_b4 == -9) && (iVar5 = FUN_10760db0(0x200000), iVar5 != 0)) {
      FUN_10760cd4(0x200000,"SchanTimeOut:soc_schan_op operation timed out\n");
      FUN_1086100c(local_28,local_24,local_20);
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



/* === FUN_10848590 (size=1776) === */

undefined4
FUN_10848590(int param_1,int param_2,uint param_3,undefined4 param_4,int param_5,undefined4 param_6)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint local_68;
  int local_4c;
  undefined1 local_48 [16];
  int local_38;
  int local_34;
  uint local_30;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  
  if (((param_2 < 0) || (0x901f < param_2)) ||
     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
  {
    uVar3 = 0xfffffffc;
  }
  else {
    local_38 = param_1;
    local_34 = param_2;
    local_30 = param_3;
    local_2c = param_4;
    local_28 = param_5;
    local_24 = param_6;
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                           param_2 * 4) + 0x10) & 0x100000) == 0) {
      uVar3 = FUN_1084faec(param_1,param_2,param_3,param_4,&local_4c,local_48);
      if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x18) +
                             local_34 * 4) + 0x10) & 1) == 0) {
        if (local_28 != 0) {
          FUN_10760cd4(0x8000000,
                       "soc_reg_set: WARNING: write to 32-bit reg %s with hi order data, 0x%x\n",
                       (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[local_34],local_28);
        }
        uVar1 = local_24;
        if ((*(uint *)((&DAT_1212b9c4)[local_38] + 0x2f2c3c) & 0x8000) != 0) {
          FUN_108647ec(local_38,local_34,local_30,local_2c,local_24);
        }
        if ((*(uint *)((&DAT_1212b9c4)[local_38] + 0x2f2c24) & 0x2000000) == 0) {
          uVar3 = FUN_108495c4(local_38,uVar3,uVar1);
        }
        else {
          uVar3 = FUN_10848458(local_38,local_4c,local_48[0],uVar3,uVar1);
        }
      }
      else {
        uVar1 = **(undefined4 **)
                  (*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x18) + local_34 * 4);
        if ((*(uint *)((&DAT_1212b9c4)[local_38] + 0x2f2c3c) & 0x8000) != 0) {
          FUN_108644ec(local_38,local_34,local_30,local_2c,local_28,local_24);
        }
        if ((*(uint *)((&DAT_1212b9c4)[local_38] + 0x2f2c24) & 0x2000000) == 0) {
          uVar3 = FUN_10847ee4(local_38,local_34,uVar3);
        }
        else {
          iVar4 = FUN_10761cd8(uVar1,0x61);
          if ((iVar4 == 0) || (iVar4 = FUN_108443a4(local_34), iVar4 == 0)) {
            uVar3 = FUN_10847b64(local_38,local_4c,local_48[0],uVar3,local_28,local_24);
          }
          else {
            for (local_68 = *(uint *)((&DAT_1212b9c4)[local_38] + 0x37b8);
                (-1 < (int)local_68 &&
                ((int)local_68 <= *(int *)((&DAT_1212b9c4)[local_38] + 0x37bc)));
                local_68 = local_68 + 1) {
              if ((*(uint *)((&DAT_1212b9c4)[local_38] +
                             (((int)local_68 >> 5) +
                              (uint)((int)local_68 < 0 && (local_68 & 0x1f) != 0) + 0xdec) * 4 +
                            0x10) &
                  1 << (local_68 +
                        (((int)local_68 >> 5) + (uint)((int)local_68 < 0 && (local_68 & 0x1f) != 0))
                        * -0x20 & 0x3f)) != 0) {
                if (*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x48) < 2) {
                  iVar4 = local_68 << 3;
                }
                else {
                  iVar4 = *(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x48) * local_68
                          * 8;
                }
                if (*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x48) < 2) {
                  iVar2 = local_68 << 3;
                }
                else {
                  iVar2 = *(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x48) * local_68
                          * 8;
                }
                if ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x30) +
                              *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) +
                                               0x34) + iVar4) * 0x10 + 8) == local_4c) &&
                   (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_38] + 0x2f26f4) + 0x34) +
                              iVar2 + 4) == param_3)) break;
              }
            }
            if ((*(uint *)((&DAT_1212b9c4)[local_38] +
                           (((int)local_30 >> 5) +
                            (uint)((int)local_30 < 0 && (local_30 & 0x1f) != 0) + 0xdec) * 4 + 0x10)
                & 1 << (local_30 +
                        (((int)local_30 >> 5) + (uint)((int)local_30 < 0 && (local_30 & 0x1f) != 0))
                        * -0x20 & 0x3f)) == 0) {
              uVar3 = FUN_10847b64(local_38,local_4c,local_48[0],uVar3,local_28,local_24);
            }
            else {
              uVar3 = FUN_10847cb8(local_38,local_4c,local_48[0],uVar3,local_30,1,local_28,local_24)
              ;
            }
          }
        }
      }
    }
    else {
      FUN_10760cd4(0x200000,"soc_reg_set: Use soc_reg_above_64_set \n");
      uVar3 = 0xfffffff5;
    }
  }
  return uVar3;
}



/* === FUN_10848458 (size=312) === */

undefined4
FUN_10848458(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  uint local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_28;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_84 = (param_2 & 0x3f) << 0x14 | (param_3 & 0x3f) << 0xe | 0x34000200;
  local_80 = param_4;
  local_7c = param_5;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  iVar1 = FUN_10760db0(0x20000000);
  if (iVar1 != 0) {
    FUN_108440cc(local_28,0x20,"write",local_24,local_20,local_1c,0,local_18);
  }
  FUN_10843e08(local_28,local_24,local_20,local_1c,1,0,local_18);
  uVar2 = FUN_10861634(local_28,&local_84,3,0,0);
  return uVar2;
}



/* === FUN_10845768 (size=1176) === */

int FUN_10845768(int param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 *param_5)

{
  int iVar1;
  int iVar2;
  undefined4 local_b8;
  uint local_a4;
  undefined4 local_a0;
  undefined1 auStack_4c [8];
  int local_44;
  int local_40;
  undefined4 local_38;
  undefined4 local_34;
  int local_28;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  
  local_a4 = (param_2 & 0x3f) << 0x14 | (param_3 & 0x3f) << 0xe | 0x2c000200;
  local_a0 = param_4;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  iVar1 = FUN_10861634(param_1,&local_a4,2,2,0);
  if (iVar1 < 0) {
    local_b8 = 0;
    if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c3c) & 0x400) == 0) {
      return iVar1;
    }
    FUN_10765ca8(local_28,auStack_4c,local_24,local_20,local_1c);
    if (local_44 == -1) {
      return iVar1;
    }
    if ((((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                             local_44 * 4) + 0x10) & 2) == 0) ||
        (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                          local_44 * 4) + 4) == 5)) ||
       (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                         local_44 * 4) + 4) == 10)) {
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c3c) & 0x8000) != 0) {
        if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                             local_44 * 4) + 4) == 2) {
          local_b8 = local_38;
        }
        else if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                                  local_44 * 4) + 4) == 4) {
          local_b8 = local_34;
        }
        if (local_40 == -1) {
          local_40 = 0;
        }
        iVar2 = FUN_10864b9c(local_28,local_44,local_b8,local_40,local_18);
        if (iVar2 != 0) {
          iVar2 = FUN_10864c60(local_28,local_44);
          if (iVar2 == 0) {
            return iVar1;
          }
          *local_18 = 0;
        }
      }
    }
    else {
      *local_18 = 0;
    }
  }
  if (((local_a4 & 0xfc000000) == 0x30000000) && ((local_a4 & 0x40) == 0)) {
    *local_18 = local_a0;
    iVar1 = FUN_10760db0(0x20000000);
    if (iVar1 != 0) {
      FUN_108440cc(local_28,0x20,&DAT_113c7d90,local_24,local_20,local_1c,0,*local_18);
    }
    FUN_10843e08(local_28,local_24,local_20,local_1c,2,0,*local_18);
    iVar1 = 0;
  }
  else {
    FUN_10760cd4(0x200000,"_soc_reg32_get: invalid S-Channel reply, expected READ_REG_ACK:\n");
    FUN_1086100c(local_28,&local_a4,2);
    iVar1 = -1;
  }
  return iVar1;
}



/* === FUN_10845c00 (size=1576) === */

int FUN_10845c00(int param_1,int param_2,uint param_3,undefined4 param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_58;
  int local_38;
  undefined1 local_34 [4];
  undefined4 local_30 [2];
  int local_28;
  int local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  
  if (((param_2 < 0) || (0x901f < param_2)) ||
     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
  {
    iVar3 = -4;
  }
  else {
    local_28 = param_1;
    local_24 = param_2;
    local_20 = param_3;
    local_1c = param_4;
    local_18 = param_5;
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                           param_2 * 4) + 0x10) & 0x100000) == 0) {
      uVar2 = FUN_1084faec(param_1,param_2,param_3,param_4,&local_38,local_34);
      if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                             local_24 * 4) + 0x10) & 1) == 0) {
        if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
          iVar3 = FUN_10846590(local_28,uVar2,local_30);
        }
        else {
          iVar3 = FUN_10845768(local_28,local_38,local_34[0],uVar2,local_30);
        }
        if (-1 < iVar3) {
          *local_18 = 0;
          local_18[1] = local_30[0];
          iVar3 = 0;
        }
      }
      else if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
        iVar3 = FUN_10844dac(local_28,local_24,uVar2,local_18);
      }
      else {
        iVar3 = FUN_10761cd8(**(undefined4 **)
                               (*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                               local_24 * 4),0x61);
        if ((iVar3 == 0) || (iVar3 = FUN_108443a4(local_24), iVar3 == 0)) {
          iVar3 = FUN_1084467c(local_28,local_38,local_34[0],uVar2,local_18);
        }
        else {
          for (local_58 = *(uint *)((&DAT_1212b9c4)[local_28] + 0x37b8);
              (-1 < (int)local_58 && ((int)local_58 <= *(int *)((&DAT_1212b9c4)[local_28] + 0x37bc))
              ); local_58 = local_58 + 1) {
            if ((*(uint *)((&DAT_1212b9c4)[local_28] +
                           (((int)local_58 >> 5) +
                            (uint)((int)local_58 < 0 && (local_58 & 0x1f) != 0) + 0xdec) * 4 + 0x10)
                & 1 << (local_58 +
                        (((int)local_58 >> 5) + (uint)((int)local_58 < 0 && (local_58 & 0x1f) != 0))
                        * -0x20 & 0x3f)) != 0) {
              if (*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x48) < 2) {
                iVar3 = local_58 << 3;
              }
              else {
                iVar3 = *(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x48) * local_58 *
                        8;
              }
              if (*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x48) < 2) {
                iVar1 = local_58 << 3;
              }
              else {
                iVar1 = *(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x48) * local_58 *
                        8;
              }
              if ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x30) +
                            *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x34)
                                    + iVar3) * 0x10 + 8) == local_38) &&
                 (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x34) + iVar1
                           + 4) == param_3)) break;
            }
          }
          if ((*(uint *)((&DAT_1212b9c4)[local_28] +
                         (((int)local_20 >> 5) + (uint)((int)local_20 < 0 && (local_20 & 0x1f) != 0)
                         + 0xdec) * 4 + 0x10) &
              1 << (local_20 +
                    (((int)local_20 >> 5) + (uint)((int)local_20 < 0 && (local_20 & 0x1f) != 0)) *
                    -0x20 & 0x3f)) == 0) {
            iVar3 = FUN_1084467c(local_28,local_38,local_34[0],uVar2,local_18);
          }
          else {
            iVar3 = FUN_10844b88(local_28,local_38,local_34[0],uVar2,local_20,local_18);
          }
        }
      }
    }
    else {
      FUN_10760cd4(0x200000,"soc_reg_get: Use soc_reg_above_64_get \n");
      iVar3 = -0xb;
    }
  }
  return iVar3;
}



/* NO FUNCTION at 0x10844380 */

/* === FUN_10846590 (size=1892) === */

int FUN_10846590(int param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  int local_b8;
  undefined4 local_b4;
  uint local_9c;
  uint local_98;
  undefined1 auStack_44 [8];
  int local_3c;
  int local_38;
  undefined4 local_30;
  undefined4 local_2c;
  int local_18;
  uint local_14;
  uint *local_10;
  
  iVar2 = *(int *)((&DAT_1212b9c4)[param_1] + 0xe1fc);
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c40) & 2) == 0) ||
     (*(int *)((&DAT_1212b9c4)[param_1] + 0xe1e8) == 0)) {
    local_9c = (param_2 >> 0x14 & 0xf | (param_2 >> 0x1e) << 4) << 0x14 |
               (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x30) +
                          *(int *)((&DAT_1212b9c4)[param_1] + 0x5ba4) * 0x10 + 8) & 0x3f) << 0xe |
               0x2c000200;
    local_98 = param_2;
    local_b8 = FUN_10861634(param_1,&local_9c,2,2,0);
    if (local_b8 < 0) {
      local_b4 = 0;
      if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c3c) & 0x400) == 0) {
        return local_b8;
      }
      FUN_10764bec(local_18,auStack_44,local_14);
      if (local_3c == -1) {
        return local_b8;
      }
      if ((((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x18) +
                               local_3c * 4) + 0x10) & 2) == 0) ||
          (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x18) +
                            local_3c * 4) + 4) == 5)) ||
         (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x18) +
                           local_3c * 4) + 4) == 10)) {
        if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c3c) & 0x8000) != 0) {
          if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x18) +
                               local_3c * 4) + 4) == 2) {
            local_b4 = local_30;
          }
          else if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x18)
                                    + local_3c * 4) + 4) == 4) {
            local_b4 = local_2c;
          }
          if (local_38 == -1) {
            local_38 = 0;
          }
          iVar2 = FUN_10864b9c(local_18,local_3c,local_b4,local_38,local_10);
          if (iVar2 != 0) {
            iVar2 = FUN_10864c60(local_18,local_3c);
            if (iVar2 == 0) {
              return local_b8;
            }
            *local_10 = 0;
          }
          if (*(char *)((&DAT_1212b9c4)[local_18] + 0x2f186f) == '\0') {
            local_b8 = 0;
          }
        }
      }
      else {
        *local_10 = 0;
        if (*(char *)((&DAT_1212b9c4)[local_18] + 0x2f186f) == '\0') {
          local_b8 = 0;
        }
      }
    }
    if ((-1 < local_b8) && (((local_9c & 0xfc000000) != 0x30000000 || ((local_9c & 0x40) != 0)))) {
      FUN_10760cd4(0x200000,"soc_reg32_read: invalid S-Channel reply, expected READ_REG_ACK:\n");
      FUN_1086100c(local_18,&local_9c,2);
      return -1;
    }
    *local_10 = local_98;
  }
  else {
    FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0xe1e8),0xffffffff);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_18 * 0x78))
                (&DAT_12124314 + local_18 * 0x78,iVar2 * 0x1000 + 0x31070,local_14);
    }
    else {
      *(uint *)((iVar2 * 0x1000 + 0x31070 >> 2) * 4 + *(int *)(&DAT_12124344 + local_18 * 0x78)) =
           local_14;
    }
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      uVar1 = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                        (&DAT_12124314 + local_18 * 0x78,iVar2 * 0x1000 + 0x31074);
    }
    else {
      uVar1 = *(uint *)((iVar2 * 0x1000 + 0x31074 >> 2) * 4 +
                       *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0xe1e8));
    *local_10 = uVar1;
  }
  iVar2 = FUN_10760db0(0x20000000);
  if (iVar2 != 0) {
    FUN_10843fac(local_18,0x20,&DAT_113c7d90,local_14,0,*local_10);
  }
  FUN_10843e08(local_18,0,0,local_14,2,0,*local_10);
  return 0;
}



/* === FUN_108495c4 (size=1024) === */

undefined4 FUN_108495c4(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_7c;
  uint local_78;
  undefined4 local_74;
  int local_18;
  uint local_14;
  undefined4 local_10;
  
  iVar1 = *(int *)((&DAT_1212b9c4)[param_1] + 0xe1fc);
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  iVar2 = FUN_10760db0(0x20000000);
  if (iVar2 != 0) {
    FUN_10843fac(local_18,0x20,"write",local_14,0,local_10);
  }
  FUN_10843e08(local_18,0,0,local_14,1,0,local_10);
  if (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 2) == 0) ||
     (*(int *)((&DAT_1212b9c4)[local_18] + 0xe1e8) == 0)) {
    local_78 = local_14;
    local_7c = (local_14 >> 0x14 & 0xf | (local_14 >> 0x1e) << 4) << 0x14 |
               (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                          *(int *)((&DAT_1212b9c4)[local_18] + 0x5ba4) * 0x10 + 8) & 0x3f) << 0xe |
               0x34000200;
    local_74 = local_10;
    uVar3 = FUN_10861634(local_18,&local_7c,3,0,0);
  }
  else {
    FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0xe1e8),0xffffffff);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_18 * 0x78))
                (&DAT_12124314 + local_18 * 0x78,iVar1 * 0x1000 + 0x31070,local_14);
    }
    else {
      *(uint *)((iVar1 * 0x1000 + 0x31070 >> 2) * 4 + *(int *)(&DAT_12124344 + local_18 * 0x78)) =
           local_14;
    }
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_18 * 0x78))
                (&DAT_12124314 + local_18 * 0x78,iVar1 * 0x1000 + 0x31074,local_10);
    }
    else {
      *(undefined4 *)
       ((iVar1 * 0x1000 + 0x31074 >> 2) * 4 + *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_10;
    }
    FUN_10863624(local_18);
    FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0xe1e8));
    uVar3 = 0;
  }
  return uVar3;
}



/* === FUN_108440cc (size=320) === */

void FUN_108440cc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int param_7,undefined4 param_8)

{
  undefined1 auStack_b0 [4];
  int local_ac;
  int local_a8;
  undefined2 local_8c;
  undefined1 local_8a;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  
  local_30 = param_1;
  local_2c = param_2;
  local_28 = param_3;
  local_24 = param_4;
  local_20 = param_5;
  local_1c = param_6;
  local_18 = param_7;
  local_14 = param_8;
  FUN_10765ca8(param_1,auStack_b0,param_4,param_5,param_6);
  if ((local_ac == 0) || (local_a8 < 0)) {
    local_8c = DAT_113c7bcc;
    local_8a = DAT_113c7bce;
  }
  else {
    FUN_10762f58(local_30,&local_8c,auStack_b0);
  }
  if (local_18 == 0) {
    FUN_10760cd4(0x20000000,"soc_reg%d_%s unit %d: %s[%d][0x%x] data=0x%08x\n",local_2c,local_28,
                 local_30,&local_8c,local_24,local_1c,local_14);
  }
  else {
    FUN_10760cd4(0x20000000,"soc_reg%d_%s unit %d: %s[%d][0x%x] data=0x%08x_%08x\n",local_2c,
                 local_28,local_30,&local_8c,local_24,local_1c,local_18,local_14);
  }
  return;
}



/* === FUN_10843e08 (size=420) === */

void FUN_10843e08(int param_1,int param_2,int param_3,undefined4 param_4,uint param_5,
                 undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  undefined1 auStack_50 [8];
  int local_48;
  int local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  local_10 = param_7;
  iVar1 = FUN_10760db0(0x8000);
  if (iVar1 != 0) {
    if ((local_24 == 0) && (local_20 == 0)) {
      FUN_10764bec(local_28,auStack_50,local_1c);
    }
    else {
      FUN_10765ca8(local_28,auStack_50,local_24,local_20,local_1c);
    }
    if ((((-1 < local_48) && (local_48 < 0x9020)) &&
        (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) + local_48 * 4) !=
         0)) && ((iVar1 = *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                                  local_48 * 4), *(int *)(iVar1 + 0x34) != 0 &&
                 ((*(uint *)(iVar1 + 0x3c) & local_18) != 0)))) {
      (**(code **)(iVar1 + 0x34))
                (local_28,local_48,auStack_50,local_18,local_14,local_10,
                 *(undefined4 *)(iVar1 + 0x38));
    }
  }
  return;
}



/* === FUN_1085c36c (size=2072) === */

undefined4 FUN_1085c36c(int param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_28;
  int local_24;
  undefined4 local_1c;
  int local_18;
  uint local_14;
  
  local_24 = 0;
  local_18 = param_1;
  local_14 = param_2;
  uVar2 = FUN_11311498();
  if ((uVar2 & 0x10000) == 0) {
    iVar4 = 10000000;
  }
  else {
    iVar4 = 30000000;
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 0x80) == 0) {
    local_28 = *(int *)((&DAT_1212b9c4)[local_18] + 0xe1fc);
    if (((int)local_14 < 0) || (3 < (int)local_14)) {
      return 0xfffffffc;
    }
  }
  else {
    if (((int)local_14 < 0) || (0xc < (int)local_14)) {
      return 0xfffffffc;
    }
    local_28 = ((int)local_14 >> 2) + (uint)((int)local_14 < 0 && (local_14 & 3) != 0);
    local_14 = local_14 +
               (((int)local_14 >> 2) + (uint)((int)local_14 < 0 && (local_14 & 3) != 0)) * -4;
  }
  if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
    local_1c = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                         (&DAT_12124314 + local_18 * 0x78,local_28 * 0x1000 + 0x312c0 + local_14 * 4
                         );
  }
  else {
    local_1c = *(undefined4 *)
                (((int)(local_28 * 0x1000 + 0x312c0 + local_14 * 4) >> 2) * 4 +
                *(int *)(&DAT_12124344 + local_18 * 0x78));
  }
  iVar3 = FUN_1084b1d8(local_18,0xc38,local_1c,0x3e95);
  if (iVar3 == 0) {
    uVar5 = 0;
  }
  else {
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      local_1c = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                           (&DAT_12124314 + local_18 * 0x78,
                            local_28 * 0x1000 + 0x312c0 + local_14 * 4);
    }
    else {
      local_1c = *(undefined4 *)
                  (((int)(local_28 * 0x1000 + 0x312c0 + local_14 * 4) >> 2) * 4 +
                  *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    FUN_1084c7bc(local_18,0xc38,&local_1c,0x10,1);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_18 * 0x78))
                (&DAT_12124314 + local_18 * 0x78,local_28 * 0x1000 + 0x312c0 + local_14 * 4,local_1c
                );
    }
    else {
      *(undefined4 *)
       (((int)(local_28 * 0x1000 + 0x312c0 + local_14 * 4) >> 2) * 4 +
       *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_1c;
    }
    FUN_10324684(1000);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      local_1c = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                           (&DAT_12124314 + local_18 * 0x78,
                            local_28 * 0x1000 + 0x31364 + local_14 * 4);
    }
    else {
      local_1c = *(undefined4 *)
                  (((int)(local_28 * 0x1000 + 0x31364 + local_14 * 4) >> 2) * 4 +
                  *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    while ((iVar3 = FUN_1084b1d8(local_18,0xc45,local_1c,0x3325), iVar3 == 0 &&
           (bVar1 = local_24 < iVar4, local_24 = local_24 + 1, bVar1))) {
      FUN_10324684(1000);
      if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
        local_1c = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                             (&DAT_12124314 + local_18 * 0x78,
                              local_28 * 0x1000 + 0x31364 + local_14 * 4);
      }
      else {
        local_1c = *(undefined4 *)
                    (((int)(local_28 * 0x1000 + 0x31364 + local_14 * 4) >> 2) * 4 +
                    *(int *)(&DAT_12124344 + local_18 * 0x78));
      }
    }
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      local_1c = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                           (&DAT_12124314 + local_18 * 0x78,
                            local_28 * 0x1000 + 0x312c0 + local_14 * 4);
    }
    else {
      local_1c = *(undefined4 *)
                  (((int)(local_28 * 0x1000 + 0x312c0 + local_14 * 4) >> 2) * 4 +
                  *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    FUN_1084c7bc(local_18,0xc38,&local_1c,0x3e95,0);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_18 * 0x78))
                (&DAT_12124314 + local_18 * 0x78,local_28 * 0x1000 + 0x312c0 + local_14 * 4,local_1c
                );
    }
    else {
      *(undefined4 *)
       (((int)(local_28 * 0x1000 + 0x312c0 + local_14 * 4) >> 2) * 4 +
       *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_1c;
    }
    if (local_24 < iVar4) {
      uVar5 = 0;
    }
    else {
      FUN_10760cd4(0x200000,"FIFO DMA abort failed !!\n");
      uVar5 = 0xffffffff;
    }
  }
  return uVar5;
}



/* NO FUNCTION at 0x101b8f54 */

/* NO FUNCTION at 0x1002b8cc */

/* NO FUNCTION at 0x1002b044 */

