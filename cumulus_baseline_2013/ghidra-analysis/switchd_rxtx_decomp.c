/* Packet RX/TX functions in switchd */

/* === FUN_100467f8 @ 0x100467f8 (size=348) === */

void FUN_100467f8(pthread_t param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  ssize_t sVar2;
  int *piVar3;
  pthread_t *ppVar4;
  uint local_38;
  pthread_t local_34;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  pthread_t local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_34 = 0xffffffff;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  for (local_38 = 0; local_38 < DAT_11f1e07c; local_38 = local_38 + 1) {
    ppVar4 = (pthread_t *)(DAT_11f1e084 + local_38 * 8);
    iVar1 = pthread_equal(*ppVar4,local_18);
    if (iVar1 != 0) {
      local_34 = ppVar4[1];
      break;
    }
  }
  if ((int)local_34 < 0) {
    FUN_11312544("fd >= 0",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/poll/poll.c"
                 ,0x121);
  }
  local_28 = local_14;
  local_24 = local_10;
  local_20 = local_c;
  do {
    sVar2 = write(local_34,&local_28,0xc);
    if (-1 < sVar2) break;
    piVar3 = __errno_location();
  } while (*piVar3 == 4);
  if (sVar2 < 1) {
    FUN_11312544("rv > 0",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/poll/poll.c"
                 ,300);
  }
  return;
}



/* === FUN_10085208 @ 0x10085208 (size=520) === */

ssize_t FUN_10085208(char *param_1,void *param_2,size_t param_3,int param_4)

{
  undefined4 uVar1;
  int __fd;
  int *piVar2;
  char *pcVar3;
  __off64_t _Var4;
  ssize_t local_30;
  
  if (3 < DAT_11e46cd4) {
    uVar1 = bcm_l3_route_get();
    FUN_10047ec4(4,"%s %s:%d %s: reading sfp eeprom file %s\n",0x29,uVar1,"hal_bcm_sfp.c",0xfd,
                 "hal_bcm_read_eeprom_file",param_1);
  }
  __fd = open64(param_1,0);
  if (__fd < 0) {
    if (3 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      piVar2 = __errno_location();
      pcVar3 = strerror(*piVar2);
      FUN_10047ec4(4,"%s %s:%d error opening sfp eeprom file %s (%s)\n",0x30,uVar1,"hal_bcm_sfp.c",
                   0x102,param_1,pcVar3);
    }
    piVar2 = __errno_location();
    local_30 = -*piVar2;
  }
  else {
    _Var4 = lseek64(__fd,(longlong)param_4,0);
    if (_Var4 == -1) {
      if (3 < DAT_11e46cd4) {
        uVar1 = bcm_l3_route_get();
        FUN_10047ec4(4,"%s %s:%d %s: lseek to offset %d on file %s failed\n",0x33,uVar1,
                     "hal_bcm_sfp.c",0x107,"hal_bcm_read_eeprom_file",param_4,param_1);
      }
      piVar2 = __errno_location();
      local_30 = -*piVar2;
    }
    else {
      local_30 = read(__fd,param_2,param_3);
    }
    close(__fd);
  }
  return local_30;
}



/* === FUN_1021905c @ 0x1021905c (size=908) === */

undefined4 FUN_1021905c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_38;
  int local_34;
  
  iVar2 = *(int *)(&DAT_11ebac4c + param_1 * 4);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    if (*(int *)(iVar2 + 0x274) != 0) {
      FUN_112b4a58(param_1,*(undefined4 *)(iVar2 + 0x274));
      *(undefined4 *)(iVar2 + 0x274) = 0;
    }
    bcm_rx_unregister(*(undefined4 *)(iVar2 + 0x2d8),FUN_102172b0,0xff);
    iVar1 = FUN_10219030(*(undefined4 *)(iVar2 + 0x2d8),iVar2);
    if (iVar1 < 0) {
      FUN_10112e60(param_1,"Unable to deactivate receiver.\n");
      uVar3 = 0xffffffff;
    }
    else {
      for (local_38 = 0; local_38 < 1; local_38 = local_38 + 1) {
        iVar1 = FUN_10419698(param_1,*(undefined4 *)(iVar2 + local_38 * 4 + 4),
                             iVar2 + local_38 * 0x114 + 0x14);
        if (iVar1 < 0) {
          if ((iVar1 < 1) && (-0x13 < iVar1)) {
            iVar1 = -iVar1;
          }
          else {
            iVar1 = 0x13;
          }
          FUN_10112e60(param_1,"Unable to restore port %d: %s\n",
                       *(undefined4 *)(iVar2 + local_38 * 4 + 4),(&PTR_DAT_11e45348)[iVar1]);
          return 0xffffffff;
        }
      }
      if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c28) & 0x2000000) != 0) {
        for (local_34 = 0; local_34 < 1; local_34 = local_34 + 1) {
          iVar1 = FUN_103abae0(param_1,*(undefined4 *)(iVar2 + (local_34 + 0x94) * 4 + 8));
          if (iVar1 < 0) {
            if ((iVar1 < 1) && (-0x13 < iVar1)) {
              iVar4 = -iVar1;
            }
            else {
              iVar4 = 0x13;
            }
            FUN_10321ae0("call to %s line %d failed:%d %s\n","bcm_field_entry_remove",0x4ab,iVar1,
                         (&PTR_DAT_11e45348)[iVar4]);
          }
          iVar1 = FUN_103aaa20(param_1,*(undefined4 *)(iVar2 + (local_34 + 0x94) * 4 + 8));
          if (iVar1 < 0) {
            if ((iVar1 < 1) && (-0x13 < iVar1)) {
              iVar4 = -iVar1;
            }
            else {
              iVar4 = 0x13;
            }
            FUN_10321ae0("call to %s line %d failed:%d %s\n","bcm_field_entry_destroy",0x4ad,iVar1,
                         (&PTR_DAT_11e45348)[iVar4]);
          }
        }
      }
      uVar3 = 0;
    }
  }
  return uVar3;
}



/* === FUN_1010e44c @ 0x1010e44c (size=1332) === */

undefined4 FUN_1010e44c(int param_1)

{
  int iVar1;
  int iVar2;
  int local_28;
  int local_24;
  
  for (local_28 = 0; local_28 < DAT_11fc9010; local_28 = local_28 + 1) {
    iVar2 = *(int *)(&DAT_11f22298 + (local_28 + 0x29b4c) * 4);
    if (*(int *)(param_1 + 0x10) != 0) {
      FUN_10321ae0("Unregistering Rx callback on unit %d\n",iVar2);
    }
    iVar1 = bcm_rx_unregister(iVar2,FUN_101b8f54,0xff);
    if (iVar1 < 0) {
      FUN_10321ae0("Failed to unregister RX handler.\n");
    }
    if (*(int *)(param_1 + 0x10) != 0) {
      FUN_10321ae0("Stopping Rx on unit %d\n",iVar2);
    }
    iVar1 = FUN_1042cce4(iVar2,0);
    if (iVar1 < 0) {
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar1 = -iVar1;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10321ae0("system_snake_done: could not stop packet driver: %s\n",
                   (&PTR_DAT_11e45348)[iVar1]);
    }
    if (*(int *)(&DAT_11f2f210 + iVar2 * 0x90c8) != 0) {
      FUN_112b4ce8(iVar2,*(undefined4 *)(&DAT_11f2f210 + iVar2 * 0x90c8),
                   *(undefined4 *)(&DAT_11f222a0 + (iVar2 + 0x29b38) * 4));
      *(undefined4 *)(&DAT_11f2f210 + iVar2 * 0x90c8) = 0;
    }
    if (*(int *)(&DAT_11f2f228 + iVar2 * 0x90c8) != 0) {
      FUN_11312078(*(undefined4 *)(&DAT_11f2f228 + iVar2 * 0x90c8));
      *(undefined4 *)(&DAT_11f2f228 + iVar2 * 0x90c8) = 0;
    }
    if (*(int *)(&DAT_11f2f214 + iVar2 * 0x90c8) != 0) {
      for (local_24 = 0; local_24 < *(int *)(&DAT_11f222a0 + (iVar2 + 0x29b38) * 4);
          local_24 = local_24 + 1) {
        if (*(int *)(*(int *)(&DAT_11f2f214 + iVar2 * 0x90c8) + local_24 * 0x1f8 + 0x108) != 0) {
          FUN_1042aee0(iVar2,*(undefined4 *)
                              (*(int *)(&DAT_11f2f214 + iVar2 * 0x90c8) + local_24 * 0x1f8 + 0x108))
          ;
        }
      }
      FUN_11312078(*(undefined4 *)(&DAT_11f2f214 + iVar2 * 0x90c8));
      *(undefined4 *)(&DAT_11f2f214 + iVar2 * 0x90c8) = 0;
    }
    if (*(int *)(&DAT_11f2f1f8 + iVar2 * 0x90c8) != 0) {
      FUN_103255e0(*(undefined4 *)(&DAT_11f2f1f8 + iVar2 * 0x90c8));
      *(undefined4 *)(&DAT_11f2f1f8 + iVar2 * 0x90c8) = 0;
    }
    if (*(int *)(&DAT_11f222a4 + (iVar2 + 0x29b5c) * 4) != 0) {
      FUN_11312078(*(undefined4 *)(&DAT_11f222a4 + (iVar2 + 0x29b5c) * 4));
      *(undefined4 *)(&DAT_11f222a4 + (iVar2 + 0x29b5c) * 4) = 0;
    }
  }
  return 0;
}



/* === FUN_101920b4 @ 0x101920b4 (size=1504) === */

undefined4 FUN_101920b4(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  ulong uVar3;
  char *pcVar4;
  undefined4 local_28;
  undefined4 local_1c;
  int local_18;
  undefined4 *local_14;
  
  local_28 = 0;
  local_18 = param_1;
  local_14 = param_2;
  iVar1 = FUN_100ed7bc(*param_2,param_1);
  if (iVar1 == 0) {
    local_28 = 0xffffffff;
  }
  else {
    FUN_10429b38(local_18,&local_1c);
    if ((int)local_14[0x802] < (int)local_14[0x801]) {
      pcVar4 = (char *)local_14[local_14[0x802] + 1];
      local_14[0x802] = local_14[0x802] + 1;
    }
    else {
      pcVar4 = (char *)0x0;
    }
    if (pcVar4 == (char *)0x0) {
      FUN_10321ae0("Active bitmap for RX is %x.\n",local_1c);
      local_28 = 0;
    }
    else {
      iVar1 = strcasecmp(pcVar4,"init");
      if (iVar1 == 0) {
        iVar1 = FUN_10191fa8(local_18);
        if (iVar1 < 0) {
          local_28 = 0xffffffff;
        }
        else {
          local_28 = 0;
        }
      }
      else {
        iVar1 = strcasecmp(pcVar4,"enqueue");
        if (iVar1 == 0) {
          if (*(int *)(&DAT_11eb9edc + local_18 * 4) == 0) {
            uVar2 = FUN_11312cf0("rxmon");
            *(undefined4 *)(&DAT_11eb9edc + local_18 * 4) = uVar2;
            uVar2 = FUN_1032554c("rxmon",1,0);
            *(undefined4 *)(&DAT_11eb9f24 + local_18 * 4) = uVar2;
            iVar1 = FUN_113132d8("rxmon",0x4000,0x50,FUN_10191e98,local_18);
            if (iVar1 == -1) {
              FUN_10321ae0("FAILED to start rxmon packet free thread\n");
              FUN_11312d30(*(undefined4 *)(&DAT_11eb9edc + local_18 * 4));
              *(undefined4 *)(&DAT_11eb9edc + local_18 * 4) = 0;
              FUN_103255e0(*(undefined4 *)(&DAT_11eb9f24 + local_18 * 4));
              *(undefined4 *)(&DAT_11eb9f24 + local_18 * 4) = 0;
              return 0xffffffff;
            }
          }
          *(undefined4 *)(&DAT_11eb9fb4 + local_18 * 4) = 1;
          if ((int)local_14[0x802] < (int)local_14[0x801]) {
            pcVar4 = (char *)local_14[local_14[0x802] + 1];
            local_14[0x802] = local_14[0x802] + 1;
          }
          else {
            pcVar4 = (char *)0x0;
          }
          if (pcVar4 != (char *)0x0) {
            uVar3 = strtoul(pcVar4,(char **)0x0,0);
            *(ulong *)(&DAT_11eb9fb4 + local_18 * 4) = uVar3;
          }
        }
        else {
          iVar1 = strcasecmp(pcVar4,"-enqueue");
          if (iVar1 == 0) {
            *(undefined4 *)(&DAT_11eb9fb4 + local_18 * 4) = 0;
          }
          else {
            iVar1 = strcasecmp(pcVar4,"start");
            if (iVar1 == 0) {
              DAT_11eb9ed8 = 0;
              iVar1 = FUN_104294a4(local_18);
              if ((iVar1 == 0) && (iVar1 = FUN_10191fa8(local_18), iVar1 < 0)) {
                FUN_10321ae0("Warning:  init failed.  Will attempt register\n");
              }
              iVar1 = FUN_1042c140(local_18,"RX CMD",FUN_10191ae0,100,0,0x40000000);
              if (iVar1 < 0) {
                if ((iVar1 < 1) && (-0x13 < iVar1)) {
                  iVar1 = -iVar1;
                }
                else {
                  iVar1 = 0x13;
                }
                FUN_10321ae0("%s: bcm_rx_register failed: %s\n",*local_14,(&PTR_DAT_11e45348)[iVar1]
                            );
                local_28 = 0xffffffff;
              }
              else {
                FUN_10321ae0("NOTE:  \'debugmod diag rx\' required for rxmon output\n");
              }
            }
            else {
              iVar1 = strcasecmp(pcVar4,"stop");
              if (iVar1 == 0) {
                iVar1 = FUN_1042cce4(local_18,&DAT_1184e3b0);
                if (iVar1 < 0) {
                  if ((iVar1 < 1) && (-0x13 < iVar1)) {
                    iVar1 = -iVar1;
                  }
                  else {
                    iVar1 = 0x13;
                  }
                  FUN_10321ae0("%s: Error: Cannot stop RX: %s.  Is it running?\n",*local_14,
                               (&PTR_DAT_11e45348)[iVar1]);
                  local_28 = 0xffffffff;
                }
                else {
                  iVar1 = bcm_rx_unregister(local_18,FUN_10191ae0,100);
                  if (iVar1 < 0) {
                    if ((iVar1 < 1) && (-0x13 < iVar1)) {
                      iVar1 = -iVar1;
                    }
                    else {
                      iVar1 = 0x13;
                    }
                    FUN_10321ae0("%s: bcm_rx_unregister failed: %s\n",*local_14,
                                 (&PTR_DAT_11e45348)[iVar1]);
                    local_28 = 0xffffffff;
                  }
                }
              }
              else {
                iVar1 = strcasecmp(pcVar4,"show");
                if (iVar1 == 0) {
                  FUN_1042c5c4(local_18);
                }
                else {
                  local_28 = 0xfffffffe;
                }
              }
            }
          }
        }
      }
    }
  }
  return local_28;
}



/* === FUN_1002b8cc @ 0x1002b8cc (size=744) === */

void FUN_1002b8cc(int param_1,uint *param_2)

{
  ssize_t sVar1;
  undefined4 uVar2;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  void *local_38;
  iovec local_34;
  uint local_2c;
  undefined4 local_28;
  int local_24;
  uint local_20;
  int local_18;
  uint *local_14;
  int local_10;
  int iStack_c;
  
  local_38 = (void *)param_2[2];
  local_18 = param_1;
  local_14 = param_2;
  if ((*param_2 & 1) != 0) {
    if (0x3fff < (int)param_2[1]) {
      FUN_11312544("packet->length < PKT_BUF_SZ","nic.c",0x17a);
    }
    memcpy(DAT_11e47780,(void *)local_14[2],local_14[1]);
    local_38 = DAT_11e47780;
    local_14[1] = 0x4000;
  }
  if (((*local_14 & 4) != 0) || ((*local_14 & 8) != 0)) {
    FUN_1002b48c(local_18,local_14);
  }
  if ((*local_14 & 2) == 0) {
    if (local_14[3] == 0) {
      sVar1 = write(*(int *)(DAT_11e46f24 + local_18 * 0x200),local_38,local_14[1]);
      if (sVar1 < 1) {
        iVar5 = DAT_11e46f24 + local_18 * 0x200;
        iStack_c = *(uint *)(iVar5 + 0x1a4) + 1;
        local_10 = *(int *)(iVar5 + 0x1a0) + (uint)(0xfffffffe < *(uint *)(iVar5 + 0x1a4));
        *(ulonglong *)(iVar5 + 0x1a0) = CONCAT44(local_10,iStack_c);
        if (3 < DAT_11e46cd4) {
          uVar2 = bcm_l3_route_get();
          piVar3 = __errno_location();
          pcVar4 = strerror(*piVar3);
          FUN_10047ec4(4,"%s %s:%d Dropped packet: tapdev queue full. (%s)\n",0x32,uVar2,"nic.c",
                       0x199,pcVar4);
        }
      }
    }
    else {
      local_34.iov_base = local_38;
      local_34.iov_len = 0xc;
      local_2c = local_14[3];
      local_28 = 4;
      local_24 = (int)local_38 + 0xc;
      local_20 = local_14[1];
      sVar1 = writev(*(int *)(DAT_11e46f24 + local_18 * 0x200),&local_34,3);
      if (sVar1 < 1) {
        iVar5 = DAT_11e46f24 + local_18 * 0x200;
        iStack_c = *(uint *)(iVar5 + 0x1a4) + 1;
        local_10 = *(int *)(iVar5 + 0x1a0) + (uint)(0xfffffffe < *(uint *)(iVar5 + 0x1a4));
        *(ulonglong *)(iVar5 + 0x1a0) = CONCAT44(local_10,iStack_c);
        if (3 < DAT_11e46cd4) {
          uVar2 = bcm_l3_route_get();
          piVar3 = __errno_location();
          pcVar4 = strerror(*piVar3);
          FUN_10047ec4(4,"%s %s:%d Dropped packet: tapdev queue full. (%s)\n",0x32,uVar2,"nic.c",
                       0x1a6,pcVar4);
        }
      }
    }
  }
  return;
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



/* === FUN_1032bff0 @ 0x1032bff0 (size=432) === */

undefined4 FUN_1032bff0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *local_28;
  undefined4 local_20 [2];
  int local_18;
  
  local_28 = DAT_11ebc534;
  local_20[0] = 0;
  if (DAT_11e470ac == 0) {
    local_20[0] = 0xffffffef;
  }
  else if (DAT_11e470a4 < 1) {
    local_20[0] = 0xfffffff1;
  }
  else if (((param_1 < 0) || (0x7f < param_1)) ||
          (local_18 = param_1, (&DAT_11ebec60)[param_1] == 0)) {
    local_20[0] = 0xfffffffc;
  }
  else {
    for (; local_28 != (undefined4 *)0x0; local_28 = (undefined4 *)*local_28) {
      iVar1 = bcm_rx_unregister(local_18,local_28[3],*(undefined1 *)(local_28 + 5));
      iVar2 = FUN_10329894(local_18,iVar1,0xfffffff9,local_20);
      if (((iVar2 < 0) && (iVar2 = bcm_port_link_failed_clear(&PTR_DAT_11853cec,0x200), iVar2 != 0))
         && (PTR_FUN_11e46d7c != (undefined *)0x0)) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar1 = -iVar1;
        }
        else {
          iVar1 = 0x13;
        }
        (*(code *)PTR_FUN_11e46d7c)
                  ("BCMX RX: Unit %d unregister failed: %s\n",local_18,(&PTR_DAT_11e45348)[iVar1]);
      }
    }
  }
  return local_20[0];
}



/* === FUN_10071964 @ 0x10071964 (size=1020) === */

size_t FUN_10071964(void *param_1,size_t param_2)

{
  bool bVar1;
  int iVar2;
  pthread_t __thread1;
  char *__haystack;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  size_t sVar6;
  int *piVar7;
  
  iVar2 = FUN_113136a4();
  __thread1 = pthread_self();
  bVar1 = true;
  sVar6 = param_2;
  if ((DAT_11e46fe0 == '\x01') && (iVar2 == DAT_11e46fec)) {
    if (((DAT_11e498dc != 0) && (sVar6 = write(DAT_1181b45c,param_1,param_2), (int)sVar6 < 0)) &&
       (piVar7 = __errno_location(), *piVar7 != 4)) {
      DAT_11e498dc = 0;
      sVar6 = FUN_10071964(param_1,param_2);
    }
  }
  else {
    __haystack = (char *)FUN_10071338(param_2 + 1,"hal_bcm_console.c",0xa3);
    memcpy(__haystack,param_1,param_2);
    __haystack[param_2] = '\0';
    if ((DAT_11e46fe0 != '\x01') && (0xf < DAT_11e498e0)) {
      bVar1 = false;
    }
    if ((iVar2 == DAT_11e46fec) || (iVar3 = pthread_equal(__thread1,DAT_11e46f1c), iVar3 != 0)) {
      if (iVar2 == DAT_11e46fec) {
        if (-2 < DAT_11e46cd4) {
          uVar4 = bcm_l3_route_get();
          FUN_10047ec4(0xffffffff,"%s %s:%d %s",0xc,uVar4,"hal_bcm_console.c",0xc4,__haystack);
        }
      }
      else if (1 < DAT_11e46cd4) {
        uVar4 = bcm_l3_route_get();
        FUN_10047ec4(2,"%s %s:%d WARN %s",0x11,uVar4,"hal_bcm_console.c",0xc2,__haystack);
      }
      pcVar5 = strstr(__haystack,"ERROR loading rc script on unit ");
      if (pcVar5 == __haystack) {
        if (-1 < DAT_11e46cd4) {
          uVar4 = bcm_l3_route_get();
          FUN_10047ec4(0,"%s %s:%d CRIT loading of rc script failed, aborting!\n",0x36,uVar4,
                       "hal_bcm_console.c",0xc9);
        }
        system("cl-support \'switchd rc script failed\'");
      }
      free(__haystack);
    }
    else {
      if (bVar1) {
        *(int *)(PTR_DAT_11e46cb8 + 4) = *(int *)(PTR_DAT_11e46cb8 + 4) + 1;
        FUN_100467f8(DAT_11e46f1c,FUN_10071868,iVar2 != DAT_11e46fec,__haystack);
      }
      else {
        if (DAT_11e46fe4 == 0) {
          __nldbl_snprintf(__haystack,param_2,"skipping BCM log(s)\n");
          *(int *)(PTR_DAT_11e46cb8 + 4) = *(int *)(PTR_DAT_11e46cb8 + 4) + 1;
          FUN_100467f8(DAT_11e46f1c,FUN_10071868,iVar2 != DAT_11e46fec,__haystack);
        }
        DAT_11e46fe4 = DAT_11e46fe4 + 1;
      }
      if (DAT_11e46fe0 != '\x01') {
        DAT_11e498e0 = DAT_11e498e0 + 1;
      }
    }
  }
  return sVar6;
}



/* === FUN_101c71c4 @ 0x101c71c4 (size=736) === */

uint FUN_101c71c4(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint local_28;
  int local_24;
  
  local_28 = 0;
  iVar3 = *(int *)(param_1 + 0x3c8);
  uVar4 = *(undefined4 *)(param_1 + 0x3cc);
  if ((iVar3 != 0) && (*(int *)(iVar3 + 0xec) == 0)) {
    iVar1 = bcm_rx_unregister(*(undefined4 *)(param_1 + 0x3cc),FUN_101b8f54,0xff);
    if (iVar1 < 0) {
      FUN_10112e60(*(undefined4 *)(param_1 + 0x3cc),"Failed to unregister RX handler.\n");
    }
    local_28 = FUN_1042cce4(*(undefined4 *)(param_1 + 0x3cc),0);
    if ((int)local_28 < 0) {
      if (((int)local_28 < 1) && (-0x13 < (int)local_28)) {
        iVar1 = -local_28;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10321ae0("lbu_done: could not stop packet driver: %s\n",(&PTR_DAT_11e45348)[iVar1]);
    }
    if (*(int *)(param_1 + 0x90a0) != 0) {
      FUN_112b4ce8(uVar4,*(undefined4 *)(param_1 + 0x90a0),*(undefined4 *)(iVar3 + 0x94));
      *(undefined4 *)(param_1 + 0x90a0) = 0;
    }
    if (*(int *)(param_1 + 0x90a4) != 0) {
      for (local_24 = 0; local_24 < *(int *)(iVar3 + 0x94); local_24 = local_24 + 1) {
        if (*(int *)(*(int *)(param_1 + 0x90a4) + local_24 * 0x1f8 + 0x120) != 0) {
          FUN_1042aee0(*(undefined4 *)(param_1 + 0x3cc),
                       *(undefined4 *)(*(int *)(param_1 + 0x90a4) + local_24 * 0x1f8 + 0x120));
        }
      }
      memset(*(void **)(param_1 + 0x90a4),0,*(int *)(iVar3 + 0x94) * 0x1f8);
      FUN_11312078(*(undefined4 *)(param_1 + 0x90a4));
      *(undefined4 *)(param_1 + 0x90a4) = 0;
    }
  }
  if (*(int *)(param_1 + 37000) != 0) {
    FUN_103255e0(*(undefined4 *)(param_1 + 37000));
    *(undefined4 *)(param_1 + 37000) = 0;
  }
  FUN_101bb644(param_1);
  if (iVar3 != 0) {
    uVar2 = FUN_101c6bc0(param_1);
    local_28 = local_28 | uVar2;
  }
  return local_28;
}



/* === FUN_1032b8a8 @ 0x1032b8a8 (size=432) === */

int FUN_1032b8a8(undefined4 param_1,uint param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_38;
  int local_34;
  int local_24;
  undefined4 *local_20 [2];
  undefined4 local_18;
  uint local_14;
  
  local_24 = -0x10;
  if (DAT_11e470ac == 0) {
    local_24 = -0x11;
  }
  else if (DAT_11e470a4 < 1) {
    local_24 = -0xf;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    FUN_11312da0(DAT_11e470ac,0xffffffff);
    puVar1 = (undefined4 *)FUN_1032b44c(local_18,local_14,local_20);
    if (puVar1 == (undefined4 *)0x0) {
      FUN_11312efc(DAT_11e470ac);
      local_24 = 0;
    }
    else {
      if (local_20[0] == (undefined4 *)0x0) {
        DAT_11ebc534 = *puVar1;
      }
      else {
        *local_20[0] = *puVar1;
      }
      FUN_11312078(puVar1);
      FUN_11312efc(DAT_11e470ac);
      local_34 = 0;
      local_38 = DAT_1211d644;
      while (local_34 < DAT_11e470a4) {
        uVar2 = bcm_rx_unregister(local_38,local_18,local_14 & 0xff);
        iVar3 = FUN_10329894(local_38,uVar2,0xfffffff9,&local_24);
        if (iVar3 < 0) {
          return iVar3;
        }
        local_34 = local_34 + 1;
        local_38 = (&DAT_1211d644)[local_34];
      }
    }
  }
  return local_24;
}



/* === FUN_10071d60 @ 0x10071d60 (size=372) === */

ssize_t FUN_10071d60(undefined2 *param_1,size_t param_2)

{
  int iVar1;
  int *piVar2;
  ssize_t sVar3;
  ssize_t local_28;
  
  iVar1 = FUN_113136a4();
  if (iVar1 != DAT_11e46fec) {
    FUN_11312544("sal_thread_self() == shell_thread","hal_bcm_console.c",0xe6);
  }
  if ((DAT_11e498dc == 0) && (iVar1 = FUN_100714c4(), iVar1 != 0)) {
    FUN_100715a4();
  }
  if (DAT_11e498dc == 0) {
    if ((int)param_2 < 1) {
      FUN_11312544("count >= 1","hal_bcm_console.c",0xf5);
    }
    if (DAT_11e498d8 == '\n') {
      *param_1 = 0x2000;
    }
    else {
      *param_1 = 0xa00;
    }
    local_28 = 1;
  }
  else {
    local_28 = read(DAT_1181b45c,param_1,param_2);
    if ((local_28 == 0) || ((local_28 < 0 && (piVar2 = __errno_location(), *piVar2 != 4)))) {
      DAT_11e498dc = 0;
      sVar3 = FUN_10071d60(param_1,param_2);
      return sVar3;
    }
  }
  FUN_1007142c(local_28,param_1);
  return local_28;
}



/* === FUN_10045c90 @ 0x10045c90 (size=208) === */

void FUN_10045c90(int param_1,undefined4 param_2,undefined4 param_3)

{
  ssize_t sVar1;
  int *piVar2;
  code *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  while( true ) {
    sVar1 = read(local_18,&local_24,0xc);
    if (sVar1 < 1) break;
    if (sVar1 != 0xc) {
      FUN_11312544("rv == sizeof (msg)",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/poll/poll.c"
                   ,0x65);
    }
    (*local_24)(local_20,local_1c);
  }
  piVar2 = __errno_location();
  if (*piVar2 != 0xb) {
    FUN_11312544("errno == EAGAIN",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/poll/poll.c"
                 ,0x68);
  }
  return;
}



/* === FUN_102173e0 @ 0x102173e0 (size=80) === */

undefined4 FUN_102173e0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = bcm_rx_unregister(param_1,FUN_102172b0,0xff);
  return uVar1;
}



/* === FUN_10136bec @ 0x10136bec (size=540) === */

undefined4 FUN_10136bec(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  char *__s1;
  undefined4 uVar2;
  
  if ((int)param_2[0x802] < (int)param_2[0x801]) {
    __s1 = (char *)param_2[param_2[0x802] + 1];
    param_2[0x802] = param_2[0x802] + 1;
  }
  else {
    __s1 = (char *)0x0;
  }
  if (__s1 == (char *)0x0) {
    uVar2 = 0xfffffffe;
  }
  else {
    iVar1 = strcasecmp(__s1,"start");
    if (iVar1 == 0) {
      FUN_1042cbcc(param_1,0);
      iVar1 = FUN_1042c140(param_1,&DAT_113564e8,FUN_10136ac4,0x65,0,0x40000000);
      if (iVar1 < 0) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar1 = -iVar1;
        }
        else {
          iVar1 = 0x13;
        }
        FUN_10321ae0("%s: bcm_rx_register failed: %s\n",*param_2,(&PTR_DAT_11e45348)[iVar1]);
        return 0xffffffff;
      }
    }
    iVar1 = strcasecmp(__s1,"stop");
    if (iVar1 == 0) {
      FUN_1042cce4(param_1,0);
      iVar1 = bcm_rx_unregister(param_1,FUN_10136ac4,0x65);
      if (iVar1 < 0) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar1 = -iVar1;
        }
        else {
          iVar1 = 0x13;
        }
        FUN_10321ae0("%s: bcm_rx_unregister failed: %s\n",*param_2,(&PTR_DAT_11e45348)[iVar1]);
        return 0xffffffff;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_1002b044 @ 0x1002b044 (size=1096) === */

void FUN_1002b044(int param_1,uint param_2,int param_3)

{
  int iVar1;
  ssize_t sVar2;
  int *piVar3;
  undefined4 uVar4;
  char cVar5;
  int iVar6;
  uint local_48;
  int local_44;
  int local_40;
  undefined4 local_2c;
  int local_28;
  uint local_24;
  int local_20;
  int local_18;
  int iStack_14;
  
  local_48 = 0;
  local_40 = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  if ((param_2 & 4) == 0) {
    if ((param_2 & 1) == 0) {
      FUN_11312544("mask & POLL_MASK_READ","nic.c",0xe5);
    }
    do {
      iVar1 = FUN_1002a910(DAT_11e4757c);
      if (DAT_11e47578 == iVar1) {
        if (3 < DAT_11e46cd4) {
          uVar4 = bcm_l3_route_get();
          FUN_10047ec4(4,"%s %s:%d Tx_Ring queue full (Head %d, Tail %d).\n",0x31,uVar4,"nic.c",0xfc
                       ,DAT_11e47578,DAT_11e4757c);
        }
        break;
      }
      iVar6 = *(int *)(&DAT_11e47580 + DAT_11e4757c * 4);
      *(undefined4 *)(iVar6 + 4) = 0x4000;
      if (iVar6 == 0) {
        FUN_11312544("packet","nic.c",0x100);
      }
      sVar2 = read(local_28,*(void **)(iVar6 + 8),*(size_t *)(iVar6 + 4));
      if ((sVar2 < 0) && (piVar3 = __errno_location(), *piVar3 != 0xb)) {
        if (0 < DAT_11e46cd4) {
          uVar4 = bcm_l3_route_get();
          piVar3 = __errno_location();
          FUN_10047ec4(1,"%s %s:%d ERR read error on fd errno %d\n",0x28,uVar4,"nic.c",0x104,*piVar3
                      );
        }
        iStack_14 = *(uint *)(param_3 + 0x19c) + 1;
        local_18 = *(int *)(param_3 + 0x198) + (uint)(0xfffffffe < *(uint *)(param_3 + 0x19c));
        *(ulonglong *)(param_3 + 0x198) = CONCAT44(local_18,iStack_14);
        piVar3 = __errno_location();
        if (*piVar3 == 0x4d) {
          FUN_100461bc(local_28);
        }
        break;
      }
      if (0 < sVar2) {
        *(ssize_t *)(iVar6 + 4) = sVar2;
        if (local_40 == 0) {
          local_44 = DAT_11e4757c;
        }
        else {
          *(int *)(local_40 + 0x1c) = iVar6;
        }
        local_48 = local_48 + 1;
        DAT_11e4757c = iVar1;
        local_40 = iVar6;
      }
    } while (0 < sVar2);
    if (0x80 < (int)local_48) {
      FUN_11312544("pkt_count <= RB_SZ","nic.c",0x11b);
    }
    if (local_48 != 0) {
      *(undefined4 *)(local_40 + 0x1c) = 0;
      cVar5 = FUN_10023940(*(undefined4 *)(param_3 + 0x18),
                           *(undefined4 *)(&DAT_11e47580 + local_44 * 4),&local_2c);
      if (cVar5 != '\x01') {
        iStack_14 = *(uint *)(param_3 + 0x19c) + local_48;
        local_18 = *(int *)(param_3 + 0x198) + ((int)local_48 >> 0x1f) +
                   (uint)CARRY4(*(uint *)(param_3 + 0x19c),local_48);
        *(ulonglong *)(param_3 + 0x198) = CONCAT44(local_18,iStack_14);
        if (1 < DAT_11e46cd4) {
          uVar4 = bcm_l3_route_get();
          FUN_10047ec4(2,"%s %s:%d WARN tx failed with count %d, start %p\n",0x31,uVar4,"nic.c",
                       0x128,local_48,*(undefined4 *)(&DAT_11e47580 + local_44 * 4));
        }
        DAT_11e4757c = FUN_1002a950(local_44,local_2c);
      }
    }
  }
  else {
    FUN_11312544("FALSE","nic.c",0xe1);
  }
  return;
}



