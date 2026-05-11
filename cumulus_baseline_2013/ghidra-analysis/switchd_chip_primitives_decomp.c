/* Candidate BCM chip-register primitive functions, decompiled */

/* === FUN_103230a4 @ 103230a4 (size=2372 depth=4 hw_refs=14) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
   "/dev/linux-kernel-bde"
   "_ioctl(LUBDE_GET_NUM_DEVICES, &devio) == 0"
   "/dev/linux-user-bde"
   ...
*/

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



/* === FUN_10820164 @ 10820164 (size=1432 depth=4 hw_refs=4) === */
/* String refs:
   "soc_mem_entries: invalid block %d for memory %s\n"
   "soc_mem_is_sorted(unit, mem) || soc_mem_is_hashed(unit, mem) || soc_mem_is_cam(unit, mem) || soc_mem_is_cmd(unit, mem) || mem == VLAN_TABm"
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
   "soc_attached(unit)"
*/

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



/* === FUN_10803190 @ 10803190 (size=2636 depth=4 hw_refs=3) === */
/* String refs:
   "soc_mem_index_valid(unit, mem, index_min)"
   "soc_mem_index_valid(unit, mem, index_max)"
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
*/

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



/* === FUN_10844e8c @ 10844e8c (size=320 depth=3 hw_refs=2) === */
/* String refs:
   "soc_reg%d_%s unit %d: %s[%d][0x%x] data=0x%08x_%08x\n"
   "soc_reg%d_%s unit %d: %s[%d][0x%x] data=0x%08x\n"
*/

void FUN_10844e8c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  FUN_10766a68(param_1,auStack_b0,param_4,param_5,param_6);
  if ((local_ac == 0) || (local_a8 < 0)) {
    local_8c = DAT_113c900c;
    local_8a = DAT_113c900e;
  }
  else {
    FUN_10763d18(local_30,&local_8c,auStack_b0);
  }
  if (local_18 == 0) {
    FUN_10761a94(0x20000000,"soc_reg%d_%s unit %d: %s[%d][0x%x] data=0x%08x\n",local_2c,local_28,
                 local_30,&local_8c,local_24,local_1c,local_14);
  }
  else {
    FUN_10761a94(0x20000000,"soc_reg%d_%s unit %d: %s[%d][0x%x] data=0x%08x_%08x\n",local_2c,
                 local_28,local_30,&local_8c,local_24,local_1c,local_18,local_14);
  }
  return;
}



/* === FUN_1083bfbc @ 1083bfbc (size=1016 depth=1 hw_refs=2) === */
/* String refs:
   "soc_phyctrl_redirect_loopback_set: u=%d p=%d TIMEOUT\n"
   "entered soc_phyctrl_redirect_loopback_set: unit %d, port %d, enable %d\n"
*/

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



/* === FUN_10847ab4 @ 10847ab4 (size=544 depth=1 hw_refs=2) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
   "reg %s is > 32 bit , but called with soc_reg32_get\n"
*/

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



/* === FUN_108158a4 @ 108158a4 (size=1820 depth=2 hw_refs=2) === */
/* String refs:
   "soc_mem_is_sorted(unit, mem) || soc_mem_is_hashed(unit, mem) || soc_mem_is_cam(unit, mem) || soc_mem_is_cmd(unit, mem)"
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
*/

undefined4
FUN_108158a4(int param_1,int param_2,uint param_3,int param_4,undefined4 param_5,int param_6,
            undefined4 param_7)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_24;
  uint local_20;
  
  uVar4 = 0;
  if (((((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4)
         & 8) == 0) &&
       ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
        0x20000) == 0)) &&
      ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
       0x80000) == 0)) &&
     ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) &
      0x200000) == 0)) {
    FUN_11312544("soc_mem_is_sorted(unit, mem) || soc_mem_is_hashed(unit, mem) || soc_mem_is_cam(unit, mem) || soc_mem_is_cmd(unit, mem)"
                 ,
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x2dde);
  }
  if (param_6 == 0) {
    FUN_11312544("entry_data",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x2ddf);
  }
  if (param_4 == 0) {
    FUN_11312544("index_ptr",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x2de0);
  }
  local_20 = param_3;
  if (param_3 == 0xffffffff) {
    local_20 = *(uint *)((&DAT_1212d2dc)[param_1] + (param_2 + 0x2724) * 4 + 0x10);
  }
  if (((int)local_20 < 0) || (0x39 < (int)local_20)) {
LAB_10815b94:
    FUN_11312544("SOC_MEM_BLOCK_VALID(unit, mem, copyno)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x2de5);
  }
  else {
    if ((int)local_20 < 0x20) {
      if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                             param_2 * 4) + 0x18) & 1 << (local_20 & 0x3f)) != 0) goto LAB_10815b5c;
      goto LAB_10815b94;
    }
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                           param_2 * 4) + 0x1c) & 1 << (local_20 & 0x1f)) == 0) goto LAB_10815b94;
LAB_10815b5c:
    if (*(char *)((&DAT_1212d2dc)[param_1] + local_20 + 0x909c) == '\0') goto LAB_10815b94;
  }
  local_24 = param_2;
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c24) & 0x20) != 0) {
    uVar3 = 0;
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
    if (local_24 < 0x7e3) {
      if (0x7df < local_24) goto LAB_10815d50;
      if (local_24 < 0x3fb) {
        if ((0x3f7 < local_24) || (local_24 == 0x26d)) goto LAB_10815d50;
        if (local_24 < 0x26e) {
          uVar1 = local_24 - 0x51;
joined_r0x10815cbc:
          if (uVar1 < 2) {
LAB_10815d50:
            puVar2 = &DAT_1212d2dc;
            if (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c40) & 0x100) != 0) &&
               (puVar2 = *(undefined4 **)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24),
               (*(uint *)puVar2[local_24] & 0x10000000) != 0)) {
              uVar3 = 0xffffffff;
            }
            uVar4 = FUN_1080c940(param_1,local_24,local_20,uVar3,param_5,param_6,param_4,puVar2,
                                 uVar3,uVar4);
            return uVar4;
          }
        }
        else if ((local_24 == 0x277) || (local_24 == 0x294)) goto LAB_10815d50;
      }
      else {
        if (local_24 == 0x680) goto LAB_10815d50;
        if (local_24 < 0x681) {
          uVar1 = local_24 - 0x4d4;
          goto joined_r0x10815cbc;
        }
        if ((local_24 == 0x6fa) || (local_24 == 0x7d6)) goto LAB_10815d50;
      }
    }
    else {
      if (local_24 == 0x837) goto LAB_10815d50;
      if (local_24 < 0x838) {
        if (local_24 == 0x82b) goto LAB_10815d50;
        if (local_24 < 0x82c) {
          if (local_24 - 0x822U < 3) goto LAB_10815d50;
        }
        else if ((local_24 == 0x82f) || (local_24 == 0x833)) goto LAB_10815d50;
      }
      else {
        if (local_24 == 0x1085) goto LAB_10815d50;
        if (local_24 < 0x1086) {
          if ((local_24 == 0xcfe) || (local_24 == 0xd02)) goto LAB_10815d50;
        }
        else if ((local_24 == 0x1093) || (local_24 == 0x1098)) goto LAB_10815d50;
      }
    }
  }
  if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
     (((((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x7ffff67f) != 0 ||
        ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x10) != 0)) ||
       ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)) ||
      ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x20) != 0)))) {
    if (local_24 != 0x82f) {
      if (local_24 < 0x830) {
        if (local_24 == 0x7fe) {
          uVar4 = FUN_10ece1b8(param_1,param_5,param_6,param_4);
          return uVar4;
        }
        if (local_24 != 0x82b) {
          if (local_24 == 0x7d6) {
            uVar4 = FUN_10eb7898(param_1,param_5,param_6,param_4);
            return uVar4;
          }
          goto LAB_10815f80;
        }
      }
      else if (local_24 != 0x837) {
        if (local_24 == 0x1085) {
          uVar4 = FUN_10fa88c0(param_1,param_5,param_6,param_4);
          return uVar4;
        }
        if (local_24 != 0x833) goto LAB_10815f80;
      }
    }
    uVar4 = FUN_10ebf558(param_1,param_5,param_6,param_4);
    return uVar4;
  }
LAB_10815f80:
  uVar4 = FUN_1080b060(param_1,local_24,local_20,param_4,param_5,param_6,param_7);
  return uVar4;
}



/* === FUN_107a213c @ 107a213c (size=2748 depth=3 hw_refs=2) === */
/* String refs:
   "_soc_field_value_fit(fieldinfo, fldbuf)"
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
*/

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



/* === FUN_10848708 @ 10848708 (size=540 depth=3 hw_refs=2) === */
/* String refs:
   "soc_reg64_write_iterative: WARNING: iteration %d PLL went out of lock"
   "soc_reg64_write_iterative: operation failed:\n"
*/

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



/* === FUN_1083bc3c @ 1083bc3c (size=896 depth=1 hw_refs=2) === */
/* String refs:
   "soc_phyctrl_loopback_set: u=%d p=%d TIMEOUT\n"
   "entered soc_phyctrl_loopback_set: unit %d, port %d, enable %d\n"
*/

int FUN_1083bc3c(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int local_48;
  int local_44;
  int local_38;
  undefined1 auStack_34 [28];
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_10761a94(0x50000,"entered soc_phyctrl_loopback_set: unit %d, port %d, enable %d\n",param_1,
               param_2,param_3);
  iVar1 = *(int *)(*(int *)(&DAT_12136ddc + local_18 * 4) + local_14 * 4);
  iVar2 = *(int *)(*(int *)(&DAT_12136d94 + local_18 * 4) + local_14 * 4);
  if ((iVar2 == 0) && (iVar1 == 0)) {
    local_48 = -0x11;
  }
  else {
    if (iVar2 == 0) {
      local_44 = *(int *)(iVar1 + 0xfc);
    }
    else {
      local_44 = *(int *)(iVar2 + 0xfc);
    }
    if (local_44 == 0) {
      local_48 = -4;
    }
    else if (*(int *)(local_44 + 0x44) == 0) {
      local_48 = -0x10;
    }
    else {
      local_48 = (**(code **)(local_44 + 0x44))(local_18,local_14,local_10);
    }
    if (((local_c != 0) &&
        (((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) != 0 ||
          (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x80000) == 0 &&
           ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) == 0)))) && (-1 < local_48)))) &&
       (((local_10 != 0 && (iVar1 != 0)) &&
        (((*(uint *)(*(int *)(&DAT_12136e24 + local_18 * 4) + local_14 * 0x18 + 0xc) & 4) != 0 ||
         (iVar2 == 0)))))) {
      FUN_10880ed8(auStack_34,5000000,0);
      local_38 = 0;
      if ((*(int *)(iVar1 + 0xfc) != 0) && (*(int *)(*(int *)(iVar1 + 0xfc) + 0xc) != 0)) {
        (**(code **)(*(int *)(iVar1 + 0xfc) + 0xc))(local_18,local_14,&local_38);
      }
      do {
        if (*(int *)(iVar1 + 0xfc) == 0) {
          local_48 = -4;
        }
        else if (*(int *)(*(int *)(iVar1 + 0xfc) + 0xc) == 0) {
          local_48 = -0x10;
        }
        else {
          local_48 = (**(code **)(*(int *)(iVar1 + 0xfc) + 0xc))(local_18,local_14,&local_38);
        }
      } while (((local_38 == 0) && (-1 < local_48)) &&
              (iVar2 = FUN_10880f30(auStack_34), iVar2 == 0));
      if (local_38 == 0) {
        FUN_10761a94(0x8000000,"soc_phyctrl_loopback_set: u=%d p=%d TIMEOUT\n",local_18,local_14);
        local_48 = -9;
      }
    }
  }
  return local_48;
}



/* === FUN_10845228 @ 10845228 (size=532 depth=3 hw_refs=2) === */
/* String refs:
   "soc_reg64_read_iterative: WARNING: iteration %d PLL went out of lock"
   "soc_reg64_read_iterative: operation failed:\n"
*/

int FUN_10845228(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_58;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 auStack_30 [24];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_58 = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  do {
    if (99 < local_58) {
      FUN_10761a94(0x200000,"soc_reg64_read_iterative: operation failed:\n");
      return -0xb;
    }
    FUN_10880ed8(auStack_30,25000,0);
    do {
      iVar1 = FUN_11313a38();
      iVar2 = FUN_108469c0(local_18,0x5ef7,local_10,0,&local_38);
      iVar3 = FUN_1084c8b4(local_18,0x5ef7,local_38,local_34,0xdd79);
      if ((iVar3 != 0) || (iVar2 < 0)) break;
      iVar4 = FUN_10880f30(auStack_30);
    } while (iVar4 == 0);
    if (iVar2 < 0) {
      return iVar2;
    }
    if (iVar3 != 0) {
      iVar2 = FUN_10847cd4(local_18,local_14,local_c);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_108469c0(local_18,0x5ef7,local_10,0,&local_38);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_1084c8b4(local_18,0x5ef7,local_38,local_34,0xdd79);
      iVar3 = FUN_11313a38();
      if ((iVar2 != 0) && (iVar3 - iVar1 < 20000)) {
        return 0;
      }
      FUN_10761a94(0x8010000,"soc_reg64_read_iterative: WARNING: iteration %d PLL went out of lock",
                   local_58);
    }
    local_58 = local_58 + 1;
  } while( true );
}



/* === bcm_port_duplex_set @ 105c90fc (size=1512 depth=0 hw_refs=2) === */
/* String refs:
   "PHY_DUPLEX_SET failed: %s\n"
   "PHY_AUTONEG_SET failed: %s\n"
*/

int bcm_port_duplex_set(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  int local_78;
  int local_74;
  uint local_6c [4];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_48;
  uint local_44;
  undefined4 local_40;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_78 = -0x11;
  }
  else {
    local_48 = param_1;
    local_44 = param_2;
    local_40 = param_3;
    local_78 = FUN_105a6a18(param_1,param_2,&local_44);
    if (-1 < local_78) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_48 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4),0xffffffff);
      }
      local_78 = FUN_1083b338(local_48,local_44,0);
      if (local_78 < 0) {
        if ((local_78 < 1) && (-0x13 < local_78)) {
          iVar2 = -local_78;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10761a94(0x10000,"PHY_AUTONEG_SET failed: %s\n",(&PTR_DAT_11e45348)[iVar2]);
      }
      if ((-1 < local_78) && (local_78 = FUN_1083ade8(local_48,local_44,local_40), local_78 < 0)) {
        if ((local_78 < 1) && (-0x13 < local_78)) {
          iVar2 = -local_78;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10761a94(0x10000,"PHY_DUPLEX_SET failed: %s\n",(&PTR_DAT_11e45348)[iVar2]);
      }
      if (-1 < local_78) {
        if (*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) == 0) {
          local_78 = -4;
        }
        else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x10)
                 == 0) {
          local_78 = -0x10;
        }
        else {
          local_78 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38)
                                 + 0x10))(local_48,local_44,local_40);
        }
        if (local_78 < 0) {
          if ((local_78 < 1) && (-0x13 < local_78)) {
            iVar2 = -local_78;
          }
          else {
            iVar2 = 0x13;
          }
          FUN_10761a94(0x10000,"MAC_DUPLEX_SET failed: %s\n",(&PTR_DAT_11e45348)[iVar2]);
        }
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
      }
      if ((-1 < local_78) && (uVar1 = FUN_1131262c(), (uVar1 & 0x8b0000) == 0)) {
        for (local_74 = 0; local_74 < 8; local_74 = local_74 + 1) {
          local_6c[local_74] = 0;
        }
        iVar2 = ((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0);
        local_6c[iVar2] =
             local_6c[iVar2] |
             1 << (local_44 +
                   (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                   -0x20 & 0x3f);
        local_30 = local_6c[0];
        local_2c = local_6c[1];
        local_28 = local_6c[2];
        local_24 = local_6c[3];
        local_20 = local_5c;
        local_1c = local_58;
        local_18 = local_54;
        local_14 = local_50;
        FUN_1053ae58(local_48,&local_30);
      }
      FUN_10761a94(0x800,"bcm_port_duplex_set: u=%d p=%d dup=%d rv=%d\n",local_48,local_44,local_40,
                   local_78);
    }
  }
  return local_78;
}



/* === FUN_10322de8 @ 10322de8 (size=140 depth=2 hw_refs=2) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
   "ioctl(_devfd, command, pdevio) == 0"
*/

undefined4 FUN_10322de8(ulong param_1,int param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_2 + 4) = 0xffffffff;
  iVar1 = ioctl(DAT_11853c08,param_1,param_2);
  if (iVar1 != 0) {
    FUN_11312544("ioctl(_devfd, command, pdevio) == 0",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                 ,0x1f7);
  }
  return *(undefined4 *)(param_2 + 4);
}



/* === FUN_10845948 @ 10845948 (size=548 depth=2 hw_refs=2) === */
/* String refs:
   "soc_reg64_get_iterative: WARNING: iteration %d PLL went out of lock"
   "soc_reg64_get_iterative: operation failed:\n"
*/

int FUN_10845948(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_68 = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  do {
    if (99 < local_68) {
      FUN_10761a94(0x200000,"soc_reg64_get_iterative: operation failed:\n");
      return -0xb;
    }
    FUN_10880ed8(auStack_40,25000,0);
    do {
      iVar1 = FUN_11313a38();
      iVar2 = FUN_108469c0(local_28,0x5ef7,local_18,0,&local_48);
      iVar3 = FUN_1084c8b4(local_28,0x5ef7,local_48,local_44,0xdd79);
      if ((iVar3 != 0) || (iVar2 < 0)) break;
      iVar4 = FUN_10880f30(auStack_40);
    } while (iVar4 == 0);
    if (iVar2 < 0) {
      return iVar2;
    }
    if (iVar3 != 0) {
      iVar2 = FUN_1084543c(local_28,local_24,local_20,local_1c,local_14);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_108469c0(local_28,0x5ef7,local_18,0,&local_48);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_1084c8b4(local_28,0x5ef7,local_48,local_44,0xdd79);
      iVar3 = FUN_11313a38();
      if ((iVar2 != 0) && (iVar3 - iVar1 < 20000)) {
        return 0;
      }
      FUN_10761a94(0x8010000,"soc_reg64_get_iterative: WARNING: iteration %d PLL went out of lock",
                   local_68);
    }
    local_68 = local_68 + 1;
  } while( true );
}



/* === FUN_10848a78 @ 10848a78 (size=556 depth=2 hw_refs=2) === */
/* String refs:
   "soc_reg64_set_iterative: operation failed:\n"
   "soc_reg64_set_iterative: WARNING: iteration %d PLL went out of lock"
*/

int FUN_10848a78(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

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
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_10;
  undefined4 local_c;
  
  local_68 = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_10 = param_7;
  local_c = param_8;
  do {
    if (99 < local_68) {
      FUN_10761a94(0x200000,"soc_reg64_set_iterative: operation failed:\n");
      return -0xb;
    }
    FUN_10880ed8(auStack_40,25000,0);
    do {
      iVar1 = FUN_11313a38();
      iVar2 = FUN_108469c0(local_28,0x5ef7,local_18,0,&local_48);
      iVar3 = FUN_1084c8b4(local_28,0x5ef7,local_48,local_44,0xdd79);
      if ((iVar3 != 0) || (iVar2 < 0)) break;
      iVar4 = FUN_10880f30(auStack_40);
    } while (iVar4 == 0);
    if (iVar2 < 0) {
      return iVar2;
    }
    if (iVar3 != 0) {
      iVar2 = FUN_10848924(local_28,local_24,local_20,local_1c,local_10,local_c);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_108469c0(local_28,0x5ef7,local_18,0,&local_48);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_1084c8b4(local_28,0x5ef7,local_48,local_44,0xdd79);
      iVar3 = FUN_11313a38();
      if ((iVar2 != 0) && (iVar3 - iVar1 < 20000)) {
        return 0;
      }
      FUN_10761a94(0x8010000,"soc_reg64_set_iterative: WARNING: iteration %d PLL went out of lock",
                   local_68);
    }
    local_68 = local_68 + 1;
  } while( true );
}



/* === FUN_10844d6c @ 10844d6c (size=288 depth=3 hw_refs=2) === */
/* String refs:
   "soc_reg%d_%s unit %d: %s[0x%x] data=0x%08x_%08x\n"
   "soc_reg%d_%s unit %d: %s[0x%x] data=0x%08x\n"
*/

void FUN_10844d6c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5,undefined4 param_6)

{
  undefined1 auStack_a0 [4];
  int local_9c;
  int local_98;
  undefined2 local_7c;
  undefined1 local_7a;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  
  local_20 = param_1;
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  local_10 = param_5;
  local_c = param_6;
  FUN_107659ac(param_1,auStack_a0,param_4);
  if ((local_9c == 0) || (local_98 < 0)) {
    local_7c = DAT_113c900c;
    local_7a = DAT_113c900e;
  }
  else {
    FUN_10763d18(local_20,&local_7c,auStack_a0);
  }
  if (local_10 == 0) {
    FUN_10761a94(0x20000000,"soc_reg%d_%s unit %d: %s[0x%x] data=0x%08x\n",local_1c,local_18,
                 local_20,&local_7c,local_14,local_c);
  }
  else {
    FUN_10761a94(0x20000000,"soc_reg%d_%s unit %d: %s[0x%x] data=0x%08x_%08x\n",local_1c,local_18,
                 local_20,&local_7c,local_14,local_10,local_c);
  }
  return;
}



/* === FUN_1083af9c @ 1083af9c (size=220 depth=2 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_speed_set: unit %d, port %d, speed %d\n"
*/

int FUN_1083af9c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_24[0] = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  FUN_10761a94(0x50000,"entered soc_phyctrl_speed_set: unit %d, port %d, speed %d\n",param_1,param_2
               ,param_3);
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x20) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x20))(local_18,local_14,local_10);
    }
  }
  return local_28;
}



/* === FUN_1083aa9c @ 1083aa9c (size=608 depth=1 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_enable_set: unit %d, port %d, enable %d\n"
*/

int FUN_1083aa9c(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int local_38;
  int local_34;
  
  local_38 = 0;
  local_34 = 0;
  FUN_10761a94(0x50000,"entered soc_phyctrl_enable_set: unit %d, port %d, enable %d\n",param_1,
               param_2,param_3);
  iVar1 = *(int *)(*(int *)(&DAT_12136d94 + param_1 * 4) + param_2 * 4);
  iVar2 = *(int *)(*(int *)(&DAT_12136ddc + param_1 * 4) + param_2 * 4);
  if ((iVar1 == 0) && (iVar2 == 0)) {
    local_34 = -0x11;
  }
  else {
    if (iVar1 == 0) {
      iVar1 = *(int *)(iVar2 + 0xfc);
      if (iVar1 == 0) {
        local_34 = -4;
      }
      else if (*(int *)(iVar1 + 0x10) == 0) {
        local_34 = -0x10;
      }
      else {
        local_34 = (**(code **)(iVar1 + 0x10))(param_1,param_2,param_3);
      }
    }
    else {
      if ((param_3 != 0) && (iVar2 != 0)) {
        iVar2 = *(int *)(iVar2 + 0xfc);
        if (iVar2 == 0) {
          local_34 = -4;
        }
        else if (*(int *)(iVar2 + 0x10) == 0) {
          local_34 = -0x10;
        }
        else {
          local_34 = (**(code **)(iVar2 + 0x10))(param_1,param_2,param_3);
        }
      }
      iVar1 = *(int *)(iVar1 + 0xfc);
      if (iVar1 == 0) {
        local_38 = -4;
      }
      else if (*(int *)(iVar1 + 0x10) == 0) {
        local_38 = -0x10;
      }
      else {
        local_38 = (**(code **)(iVar1 + 0x10))(param_1,param_2,param_3);
      }
    }
    if ((local_38 < 0) || (local_34 < 0)) {
      if (local_38 != 0) {
        local_34 = local_38;
      }
    }
    else {
      local_34 = 0;
    }
  }
  return local_34;
}



/* === FUN_10766a68 @ 10766a68 (size=3940 depth=3 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/common.c"
*/

void FUN_10766a68(int param_1,uint *param_2,int param_3,uint param_4,uint param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c24) & 0x2000000) == 0) {
    FUN_107659ac(param_1,param_2,param_5);
  }
  else {
    *param_2 = param_5;
    param_2[1] = 1;
    param_2[2] = 0xffffffff;
    iVar3 = *(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48);
    if (iVar3 < 1) {
      iVar3 = 1;
    }
    uVar1 = param_5 & 0xff;
    local_4c = param_5;
    if ((param_5 & 0x2000000) == 0) {
      local_4c = param_5 & 0xffffff00;
    }
    local_64 = 0xffffffff;
    for (local_68 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) +
                     local_68 * 0x10); local_68 = local_68 + 1) {
      if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) + local_68 * 0x10
                  + 0xc) == param_3) {
        local_64 = local_68;
      }
    }
    for (local_50 = 0; (int)local_50 < 0x9020; local_50 = local_50 + 1) {
      if (((((-1 < (int)local_50) && ((int)local_50 < 0x9020)) &&
           (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + local_50 * 4)
            != 0)) &&
          ((uVar4 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18
                                               ) + local_50 * 4) + 4), uVar4 != 5 && (uVar4 != 9))))
         && (uVar4 != 10)) {
        if ((int)local_64 < 0) {
          FUN_11312544("blk >= 0",
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/common.c"
                       ,0x4a0);
        }
        iVar2 = FUN_10762844(param_1,local_64,
                             **(undefined4 **)
                               (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                               local_50 * 4));
        if (((iVar2 != 0) &&
            (param_4 ==
             (*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                local_50 * 4) + 0x10) >> 0x11 & 7))) &&
           (uVar5 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18
                                               ) + local_50 * 4) + 0xc), uVar5 <= local_4c)) {
          if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                 local_50 * 4) + 0x10) & 0x200000) == 0) {
            if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                   local_50 * 4) + 0x10) & 4) == 0) {
              param_2[3] = 0xffffffff;
              local_54 = uVar5;
            }
            else {
              uVar6 = local_4c -
                      *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) +
                                                0x18) + local_50 * 4) + 0xc) >> 8;
              if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18)
                                     + local_50 * 4) + 0x10) & 0x10000) == 0) {
                param_2[3] = (int)uVar6 /
                             *(int *)(&DAT_11862bc8 +
                                     *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] +
                                                                        0x2f26f4) + 0x18) +
                                                      local_50 * 4) + 4) * 4);
                local_54 = *(int *)(&DAT_11862bc8 +
                                   *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] +
                                                                      0x2f26f4) + 0x18) +
                                                    local_50 * 4) + 4) * 4) *
                           (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4)
                                                      + 0x18) + local_50 * 4) + 8) + -1) * 0x100 +
                           uVar5;
              }
              else {
                param_2[3] = (int)uVar6 /
                             (*(int *)(&DAT_11862bc8 +
                                      *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] +
                                                                         0x2f26f4) + 0x18) +
                                                       local_50 * 4) + 4) * 4) << 1);
                local_54 = *(int *)(&DAT_11862bc8 +
                                   *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] +
                                                                      0x2f26f4) + 0x18) +
                                                    local_50 * 4) + 4) * 4) *
                           (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4)
                                                      + 0x18) + local_50 * 4) + 8) + -1) * 2 * 0x100
                           + uVar5;
              }
            }
            if ((local_4c <= local_54) &&
               (((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18)
                                    + local_50 * 4) + 0x10) & 0x10000) == 0 ||
                (((local_4c ^ uVar5) & 0x100) == 0)))) goto LAB_107672d4;
          }
          else if ((local_4c <=
                    (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18
                                               ) + local_50 * 4) + 8) + -1) *
                    **(int **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x20) +
                              local_50 * 4) + uVar5) &&
                  (uVar6 = **(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x20
                                               ) + local_50 * 4),
                  local_4c - uVar5 == ((local_4c - uVar5) / uVar6) * uVar6)) {
            param_2[3] = (local_4c - uVar5) /
                         **(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x20)
                                    + local_50 * 4);
LAB_107672d4:
            param_2[4] = local_64;
            *(char *)(param_2 + 7) = (char)param_4;
            param_2[2] = local_50;
            param_2[8] = 0xffffffff;
            param_2[6] = 0xffffffff;
            param_2[5] = 0xffffffff;
            if (uVar4 < 4) {
              if (1 < uVar4) {
                iVar2 = bcm_mirror_ingress_get
                                  (**(undefined4 **)
                                     (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18)
                                     + local_50 * 4),0x61);
                if (iVar2 == 0) {
                  if (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c38) & 0x200000) != 0) &&
                     (*(int *)**(undefined4 **)
                                (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                local_50 * 4) == 9)) {
                    param_2[5] = *(uint *)((&DAT_1212d2dc)[param_1] +
                                           (*(int *)((&DAT_1212d2dc)[param_1] + (uVar1 + 0x229c) * 4
                                                    + 4) + 0x2010) * 4 + 0xc);
                    return;
                  }
                  param_2[5] = uVar1;
                  return;
                }
                local_58 = 0;
                goto LAB_107673a4;
              }
              if (uVar4 == 1) {
                if (uVar1 == 0) {
                  return;
                }
                param_2[2] = 0xffffffff;
                return;
              }
            }
            else if (uVar4 == 4) {
              if ((int)uVar1 <= *(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x14)) {
                param_2[6] = uVar1;
                return;
              }
              param_2[2] = 0xffffffff;
              return;
            }
            FUN_11312544(&DAT_113b59a0,
                         "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/common.c"
                         ,0x54b);
            return;
          }
        }
      }
    }
  }
  return;
LAB_107673a4:
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c38) & 0x200000) == 0) {
    local_5c = local_58;
LAB_1076741c:
    if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
      iVar2 = local_58 << 3;
    }
    else {
      iVar2 = *(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_58 * 8;
    }
    local_64 = *(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) + iVar2);
    if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
      iVar2 = local_58 << 3;
    }
    else {
      iVar2 = *(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_58 * 8;
    }
    if (((int)local_64 < 0) &&
       (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) + iVar2 + 4) < 0)) {
LAB_107677a0:
      if (param_2[5] != 0xffffffff) {
        return;
      }
      param_2[2] = 0xffffffff;
      return;
    }
    if (-1 < (int)local_64) {
      for (local_68 = 0; (int)local_68 < iVar3; local_68 = local_68 + 1) {
        if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
          iVar2 = local_58 << 3;
        }
        else {
          iVar2 = (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_58 +
                  local_68) * 8;
        }
        local_64 = *(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) + iVar2)
        ;
        if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
          iVar2 = local_58 << 3;
        }
        else {
          iVar2 = (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_58 +
                  local_68) * 8;
        }
        local_60 = *(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) + iVar2
                            + 4);
        if (local_64 == param_2[4]) {
          if (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c48) & 1) != 0) && (local_50 == 0x6cac)) {
            local_60 = local_58 - 1 & 0xf;
          }
          if (local_60 == uVar1) {
            param_2[5] = local_5c;
            break;
          }
        }
      }
      if ((local_68 != iVar3) && (-1 < (int)local_64)) goto LAB_107677a0;
    }
  }
  else {
    local_5c = *(uint *)((&DAT_1212d2dc)[param_1] + (local_58 + 0x2010) * 4 + 0xc);
    if (-1 < (int)local_5c) goto LAB_1076741c;
  }
  local_58 = local_58 + 1;
  goto LAB_107673a4;
}



/* === FUN_1084bf98 @ 1084bf98 (size=1072 depth=1 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
*/

uint FUN_1084bf98(int param_1,int param_2,uint param_3,int param_4)

{
  uint uVar1;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  
  if ((((param_2 < 0) || (0x901f < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
     && (((FUN_1076193c("reg %s is invalid\n",
                        (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2]), param_2 < 0 ||
          (0x901f < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) ==
          0)))) {
    FUN_11312544("SOC_REG_IS_VALID(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x93f);
  }
  local_38 = (int *)0x0;
  local_34 = *(int **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                               param_2 * 4) + 0x18);
  local_2c = local_34;
  if ((*local_34 != param_4) &&
     (local_2c = local_34 +
                 (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                   param_2 * 4) + 0x14) + -1) * 3, *local_2c != param_4)) {
    uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                              param_2 * 4) + 0x14);
    local_30 = local_34 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    while ((((local_34 < local_2c && (local_30 < local_2c)) && (*local_34 != param_4)) &&
           (*local_30 != param_4))) {
      if (param_4 < *local_30) {
        local_2c = local_30 + -3;
      }
      else {
        if (param_4 <= *local_30) break;
        local_34 = local_30 + 3;
      }
      uVar1 = ((int)local_2c - (int)local_34 >> 2) * -0x55555555 + 1;
      local_30 = local_34 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    }
    if (*local_30 == param_4) {
      local_38 = local_30;
      local_2c = local_38;
    }
    else {
      local_2c = local_38;
      if (*local_34 == param_4) {
        local_38 = local_34;
        local_2c = local_38;
      }
    }
  }
  local_38 = local_2c;
  if (local_38 == (int *)0x0) {
    FUN_1076193c("reg %s field %s is invalid\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2],
                 (&PTR_DAT_11d34bbc)[param_4]);
    FUN_11312544("finfop",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x94c);
  }
  param_3 = param_3 >> (*(ushort *)((int)local_38 + 6) & 0x3f);
  if (*(ushort *)(local_38 + 1) < 0x20) {
    param_3 = (1 << (*(ushort *)(local_38 + 1) & 0x3f)) - 1U & param_3;
  }
  return param_3;
}



/* === FUN_1086529c @ 1086529c (size=768 depth=2 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/ser.c"
*/

undefined4
FUN_1086529c(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  int local_38;
  int local_20;
  int local_1c;
  
  if (*(int *)(&DAT_11f00a34 + param_1 * 4) == 0) {
    return 0;
  }
  if (param_2 != 0x6d31) {
    if (param_2 < 0x6d32) {
      if (param_2 != 0x2f55) {
        if (param_2 < 0x2f56) {
          if (param_2 != 0x2344) {
            if (param_2 < 0x2345) {
              if (param_2 != 0x1ad3) {
                return 0;
              }
            }
            else if (2 < param_2 - 0x2794U) {
              return 0;
            }
          }
        }
        else if (param_2 != 0x51c6) {
          if (param_2 < 0x51c7) {
            if ((param_2 != 0x2f8e) && (param_2 != 0x3ccc)) {
              return 0;
            }
          }
          else if ((param_2 != 0x5f59) && (param_2 != 0x6020)) {
            return 0;
          }
        }
      }
    }
    else if (param_2 != 0x7d1d) {
      if (param_2 < 0x7d1e) {
        if (param_2 != 0x6e6c) {
          if (param_2 < 0x6e6d) {
            if (param_2 != 0x6d33) {
              return 0;
            }
          }
          else if ((param_2 != 0x6e72) && (param_2 != 0x7d1b)) {
            return 0;
          }
        }
      }
      else if (param_2 != 0x7d29) {
        if (param_2 < 0x7d2a) {
          if ((param_2 != 0x7d1f) && (param_2 != 0x7d27)) {
            return 0;
          }
        }
        else if ((param_2 != 0x7d2b) && (param_2 != 0x8e97)) {
          return 0;
        }
      }
    }
  }
  if (0xa9 < param_3) {
    FUN_11312544("port < _SOC_MAX_PORTS_NUMS",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/ser.c"
                 ,0x16f);
  }
  if (0x4e < param_4) {
    FUN_11312544("index < _SOC_SER_REG_INDEX_MAX",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/ser.c"
                 ,0x170);
  }
  if (param_3 < 0xaa) {
    if (param_4 < 0x4f) {
      for (local_38 = 0; local_38 < 0x16; local_38 = local_38 + 1) {
        if (*(int *)(&DAT_11870b00 + local_38 * 4) == param_2) {
          local_20 = param_3;
          if (param_3 == -10) {
            local_20 = 0;
          }
          local_1c = param_4;
          if (param_4 < 0) {
            local_1c = 0;
          }
          FUN_10761a94(0x20010000,"Unit %d: Set cache: reg:%d port:%d index:%d data:0x%x%x\n",
                       param_1,param_2,local_20,local_1c,param_5,param_6);
          *(ulonglong *)
           (*(int *)(&DAT_11f00a34 + param_1 * 4) +
           (local_20 * 0x4f + local_38 * 0x3476 + local_1c) * 8) = CONCAT44(param_5,param_6);
          break;
        }
      }
      uVar1 = 0;
    }
    else {
      uVar1 = 0xfffffffc;
    }
  }
  else {
    uVar1 = 0xfffffffc;
  }
  return uVar1;
}



/* === bcm_port_interface_set @ 105c7144 (size=1116 depth=0 hw_refs=1) === */
/* String refs:
   "PHY_INTERFACE_SET failed: %s\n"
*/

int bcm_port_interface_set(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int local_78;
  uint local_6c [4];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_48;
  uint local_44;
  undefined4 local_40;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else if ((*(uint *)((&DAT_1212d2dc)[param_1] +
                      (((int)param_2 >> 5) + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0) +
                      0x1328) * 4 + 0x14) &
           1 << (param_2 + (((int)param_2 >> 5) + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0))
                           * -0x20 & 0x3f)) == 0) {
    iVar1 = -0x12;
  }
  else {
    local_48 = param_1;
    local_44 = param_2;
    local_40 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_44);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_48 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083c5b4(local_48,local_44,local_40);
      if (iVar1 < 0) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar2 = -iVar1;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10761a94(0x10000,"PHY_INTERFACE_SET failed: %s\n",(&PTR_DAT_11e45348)[iVar2]);
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
      }
      if (-1 < iVar1) {
        for (local_78 = 0; local_78 < 8; local_78 = local_78 + 1) {
          local_6c[local_78] = 0;
        }
        iVar2 = ((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0);
        local_6c[iVar2] =
             local_6c[iVar2] |
             1 << (local_44 +
                   (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                   -0x20 & 0x3f);
        local_30 = local_6c[0];
        local_2c = local_6c[1];
        local_28 = local_6c[2];
        local_24 = local_6c[3];
        local_20 = local_5c;
        local_1c = local_58;
        local_18 = local_54;
        local_14 = local_50;
        FUN_1053ae58(local_48,&local_30);
      }
    }
  }
  return iVar1;
}



/* === bcm_port_master_set @ 105c6a48 (size=1012 depth=0 hw_refs=1) === */
/* String refs:
   "PHY_MASTER_SET failed: %s\n"
*/

int bcm_port_master_set(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int local_78;
  uint local_6c [4];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_48;
  uint local_44;
  undefined4 local_40;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_48 = param_1;
    local_44 = param_2;
    local_40 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_44);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_48 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083b170(local_48,local_44,local_40);
      if (iVar1 < 0) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar2 = -iVar1;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10761a94(0x10000,"PHY_MASTER_SET failed: %s\n",(&PTR_DAT_11e45348)[iVar2]);
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
      }
      if (-1 < iVar1) {
        for (local_78 = 0; local_78 < 8; local_78 = local_78 + 1) {
          local_6c[local_78] = 0;
        }
        iVar2 = ((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0);
        local_6c[iVar2] =
             local_6c[iVar2] |
             1 << (local_44 +
                   (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                   -0x20 & 0x3f);
        local_30 = local_6c[0];
        local_2c = local_6c[1];
        local_28 = local_6c[2];
        local_24 = local_6c[3];
        local_20 = local_5c;
        local_1c = local_58;
        local_18 = local_54;
        local_14 = local_50;
        FUN_1053ae58(local_48,&local_30);
      }
    }
  }
  return iVar1;
}



/* === FUN_1083c690 @ 1083c690 (size=216 depth=1 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_interface_get: unit %d, port %d\n"
*/

int FUN_1083c690(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_24[0] = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  FUN_10761a94(0x50000,"entered soc_phyctrl_interface_get: unit %d, port %d\n",param_1,param_2);
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x50) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x50))(local_18,local_14,local_10);
    }
  }
  return local_28;
}



/* === FUN_10760d64 @ 10760d64 (size=612 depth=3 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/cm.c"
*/

void FUN_10760d64(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = (int *)(param_2 + -0x18);
  if (*piVar1 != -0x55443323) {
    FUN_11312544("SHARED_GOOD_START(p)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/cm.c"
                 ,0x161f);
  }
  uVar2 = *(int *)(param_2 + -0x10) + 3;
  if (piVar1[((int)uVar2 >> 2) + (uint)((int)uVar2 < 0 && (uVar2 & 3) != 0) + 6] != -0x22334456) {
    FUN_11312544("SHARED_GOOD_END(p)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/cm.c"
                 ,0x1620);
  }
  uVar2 = *(int *)(param_2 + -0x10) + 3;
  FUN_10761a94(0x10000,"Freeing Start:%x: Desc:%s: Size:%d: ModifiedSize:%d: End:%x:\n",*piVar1,
               *(undefined4 *)(param_2 + -0x14),*(undefined4 *)(param_2 + -0x10),
               *(undefined4 *)(param_2 + -0xc),
               piVar1[((int)uVar2 >> 2) + (uint)((int)uVar2 < 0 && (uVar2 & 3) != 0) + 6]);
  if (DAT_11efd6ac == 0) {
    DAT_11efd6ac = FUN_11312f88("cm debug");
  }
  FUN_11313094(DAT_11efd6ac);
  if (piVar1 == DAT_11efd6a4) {
    DAT_11efd6a4 = *(int **)(param_2 + -4);
    if (DAT_11efd6a4 != (int *)0x0) {
      DAT_11efd6a4[4] = 0;
    }
  }
  else {
    *(undefined4 *)(*(int *)(param_2 + -8) + 0x14) = *(undefined4 *)(param_2 + -4);
    if (*(int *)(param_2 + -4) != 0) {
      *(undefined4 *)(*(int *)(param_2 + -4) + 0x10) = *(undefined4 *)(param_2 + -8);
    }
  }
  FUN_11313158(DAT_11efd6ac);
  (**(code **)(&DAT_12125c74 + param_1 * 0x78))(&DAT_12125c2c + param_1 * 0x78,piVar1);
  return;
}



/* === FUN_1084ea88 @ 1084ea88 (size=1512 depth=1 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
*/

void FUN_1084ea88(int param_1,int param_2,uint *param_3,int param_4,uint param_5)

{
  uint uVar1;
  int *local_68;
  undefined8 local_60;
  int *local_58;
  int *local_54;
  int *local_50;
  uint local_48;
  uint local_44;
  
  if ((((param_2 < 0) || (0x901f < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
     && (((FUN_1076193c("reg %s is invalid\n",
                        (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2]), param_2 < 0 ||
          (0x901f < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) ==
          0)))) {
    FUN_11312544("SOC_REG_IS_VALID(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xb03);
  }
  local_68 = (int *)0x0;
  local_58 = *(int **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                               param_2 * 4) + 0x18);
  local_50 = local_58;
  if ((*local_58 != param_4) &&
     (local_50 = local_58 +
                 (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                   param_2 * 4) + 0x14) + -1) * 3, *local_50 != param_4)) {
    uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                              param_2 * 4) + 0x14);
    local_54 = local_58 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    while ((((local_58 < local_50 && (local_54 < local_50)) && (*local_58 != param_4)) &&
           (*local_54 != param_4))) {
      if (param_4 < *local_54) {
        local_50 = local_54 + -3;
      }
      else {
        if (param_4 <= *local_54) break;
        local_58 = local_54 + 3;
      }
      uVar1 = ((int)local_50 - (int)local_58 >> 2) * -0x55555555 + 1;
      local_54 = local_58 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    }
    if (*local_54 == param_4) {
      local_68 = local_54;
      local_50 = local_68;
    }
    else {
      local_50 = local_68;
      if (*local_58 == param_4) {
        local_68 = local_58;
        local_50 = local_68;
      }
    }
  }
  local_68 = local_50;
  if (local_68 == (int *)0x0) {
    FUN_1076193c("reg %s field %s is invalid\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2],
                 (&PTR_DAT_11d34bbc)[param_4]);
    FUN_11312544("finfop",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xb0f);
  }
  if (*(ushort *)(local_68 + 1) < 0x40) {
    uVar1 = (uint)*(ushort *)(local_68 + 1);
    local_60._4_4_ = (uint)DAT_113df880;
    if ((int)(uVar1 - 0x20) < 0) {
      local_60._0_4_ = (uint)((ulonglong)DAT_113df880 >> 0x20);
      local_60._0_4_ =
           local_60._0_4_ << (uVar1 & 0x3f) | (local_60._4_4_ >> 1) >> (0x1f - uVar1 & 0x3f);
      local_60._4_4_ = local_60._4_4_ << (uVar1 & 0x3f);
    }
    else {
      local_60._0_4_ = local_60._4_4_ << (uVar1 - 0x20 & 0x3f);
      local_60._4_4_ = 0;
    }
    local_60 = CONCAT44((local_60._0_4_ - 1) + (uint)(local_60._4_4_ != 0),local_60._4_4_ + -1);
  }
  else {
    local_60 = DAT_113df888;
  }
  uVar1 = (uint)*(ushort *)((int)local_68 + 6);
  if ((int)(uVar1 - 0x20) < 0) {
    local_60._0_4_ =
         local_60._0_4_ << (uVar1 & 0x3f) | (local_60._4_4_ >> 1) >> (0x1f - uVar1 & 0x3f);
    local_60._4_4_ = local_60._4_4_ << (uVar1 & 0x3f);
  }
  else {
    local_60._0_4_ = local_60._4_4_ << (uVar1 - 0x20 & 0x3f);
    local_60._4_4_ = 0;
  }
  *param_3 = ~local_60._0_4_ & *param_3;
  param_3[1] = ~local_60._4_4_ & param_3[1];
  if (param_5 != 0) {
    uVar1 = (uint)*(ushort *)((int)local_68 + 6);
    if ((int)(uVar1 - 0x20) < 0) {
      local_48 = 0 << (uVar1 & 0x3f) | (param_5 >> 1) >> (0x1f - uVar1 & 0x3f);
      local_44 = param_5 << (uVar1 & 0x3f);
    }
    else {
      local_48 = param_5 << (uVar1 - 0x20 & 0x3f);
      local_44 = 0;
    }
    *param_3 = local_48 | *param_3;
    param_3[1] = local_44 | param_3[1];
  }
  return;
}



/* === FUN_1079ff70 @ 1079ff70 (size=1772 depth=3 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
*/

undefined4 * FUN_1079ff70(int param_1,uint *param_2,int param_3,int param_4,undefined4 *param_5)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *local_48;
  int local_44;
  int local_40;
  uint local_3c;
  uint local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  
  local_48 = (int *)0x0;
  local_34 = (int *)param_2[0xb];
  local_2c = local_34;
  if ((*local_34 != param_4) &&
     (local_2c = local_34 + (*(ushort *)((int)param_2 + 0x2a) - 1) * 3, *local_2c != param_4)) {
    local_30 = local_34 + (uint)(*(ushort *)((int)param_2 + 0x2a) >> 1) * 3;
    while ((((local_34 < local_2c && (local_30 < local_2c)) && (*local_34 != param_4)) &&
           (*local_30 != param_4))) {
      if (param_4 < *local_30) {
        local_2c = local_30 + -3;
      }
      else {
        if (param_4 <= *local_30) break;
        local_34 = local_30 + 3;
      }
      uVar3 = ((int)local_2c - (int)local_34 >> 2) * -0x55555555 + 1;
      local_30 = local_34 + (((int)uVar3 >> 1) + (uint)((int)uVar3 < 0 && (uVar3 & 1) != 0)) * 3;
    }
    if (*local_30 == param_4) {
      local_48 = local_30;
      local_2c = local_48;
    }
    else {
      local_2c = local_48;
      if (*local_34 == param_4) {
        local_48 = local_34;
        local_2c = local_48;
      }
    }
  }
  local_48 = local_2c;
  if (local_48 == (int *)0x0) {
    FUN_1076193c("mem %s field %s is invalid\n",(&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_1],
                 (&PTR_DAT_11d34bbc)[param_4]);
    FUN_11312544("fieldinfo",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                 ,0x1aa);
  }
  uVar1 = *(ushort *)((int)local_48 + 6);
  local_3c = (uint)uVar1;
  local_38 = (uint)*(ushort *)(local_48 + 1);
  local_40 = (int)local_3c >> 5;
  if (local_38 == 1) {
    if ((*param_2 & 0x8000000) != 0) {
      local_40 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_40;
    }
    if ((*(uint *)(param_3 + local_40 * 4) & 1 << (local_3c & 0x1f)) == 0) {
      *param_5 = 0;
    }
    else {
      *param_5 = 1;
    }
  }
  else if ((*(ushort *)(local_48 + 2) & 1) == 0) {
    uVar3 = local_38 - 1;
    local_44 = ((int)uVar3 >> 5) + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0);
    while (0 < (int)local_38) {
      if (local_44 < 0) {
        FUN_11312544("i >= 0",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                     ,0x1dd);
      }
      param_5[local_44] = 0;
      do {
        if ((*param_2 & 0x8000000) == 0) {
          iVar4 = ((int)local_3c >> 5) + (uint)((int)local_3c < 0 && (local_3c & 0x1f) != 0);
        }
        else {
          iVar4 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) -
                  (((int)local_3c >> 5) + (uint)((int)local_3c < 0 && (local_3c & 0x1f) != 0));
        }
        param_5[local_44] =
             param_5[local_44] << 1 | *(uint *)(param_3 + iVar4 * 4) >> (local_3c & 0x1f) & 1;
        local_38 = local_38 - 1;
        local_3c = local_3c + 1;
      } while ((local_38 & 0x1f) != 0);
      local_44 = local_44 + -1;
    }
  }
  else {
    local_3c = local_3c & 0x1f;
    local_44 = 0;
    for (; iVar4 = local_40, 0 < (int)local_38; local_38 = local_38 - 0x20) {
      if ((uVar1 & 0x1f) == 0) {
        if ((*param_2 & 0x8000000) == 0) {
          local_40 = local_40 << 2;
        }
        else {
          local_40 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_40) * 4;
        }
        param_5[local_44] = *(undefined4 *)(param_3 + local_40);
      }
      else {
        if ((*param_2 & 0x8000000) == 0) {
          iVar2 = local_40 << 2;
        }
        else {
          iVar2 = ((((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_40) * 4;
        }
        local_40 = local_40 + 1;
        param_5[local_44] =
             *(uint *)(param_3 + iVar2) >> local_3c & (1 << (0x20 - local_3c & 0x3f)) - 1U;
        if ((int)(0x20 - local_3c) < (int)local_38) {
          if ((*param_2 & 0x8000000) != 0) {
            local_40 = (((int)(*(ushort *)(param_2 + 10) + 3) >> 2) + -1) - local_40;
          }
          param_5[local_44] =
               param_5[local_44] | *(int *)(param_3 + local_40 * 4) << (0x20 - local_3c & 0x3f);
        }
      }
      local_40 = iVar4 + 1;
      if ((int)local_38 < 0x20) {
        param_5[local_44] = param_5[local_44] & (1 << (local_38 & 0x3f)) - 1U;
      }
      local_44 = local_44 + 1;
    }
  }
  return param_5;
}



/* === FUN_1083cb84 @ 1083cb84 (size=208 depth=2 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_linkdn_evt: unit %d, port %d\n"
*/

int FUN_1083cb84(undefined4 param_1,undefined4 param_2)

{
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  FUN_10761a94(0x50000,"entered soc_phyctrl_linkdn_evt: unit %d, port %d\n",param_1,param_2);
  local_24[0] = 0;
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x5c) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x5c))(local_18,local_14);
    }
  }
  return local_28;
}



/* === bcm_port_control_phy_oam_set @ 10415744 (size=332 depth=0 hw_refs=1) === */
/* String refs:
   "bcm_port_control_phy_oam_set"
*/

undefined4
bcm_port_control_phy_oam_set
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  int iVar1;
  undefined4 local_38;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = param_2;
  local_20 = param_3;
  local_18 = param_5;
  local_14 = param_6;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_24);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11858928)[iVar1])(param_1,local_24,local_20);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_control_phy_oam_set",4,3,param_1,local_24,local_20,local_38);
  }
  return local_38;
}



/* === FUN_1084a784 @ 1084a784 (size=512 depth=1 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
*/

undefined4
FUN_1084a784(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

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
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  uVar1 = FUN_108508ac(param_1,param_2,param_3,param_4,&local_34,local_30);
  if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                         local_24 * 4) + 0x10) & 0x100001) != 0) {
    FUN_1076193c("reg %s is not 32 bit\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[local_24]);
  }
  if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                         local_24 * 4) + 0x10) & 0x100001) != 0) {
    FUN_11312544("!SOC_REG_IS_ABOVE_32(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x7cb);
  }
  if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c3c) & 0x8000) != 0) {
    FUN_1086559c(local_28,local_24,local_20,local_1c,local_18);
  }
  if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
    uVar1 = FUN_1084a384(local_28,uVar1,local_18);
  }
  else {
    uVar1 = FUN_10849218(local_28,local_34,local_30[0],uVar1,local_18);
  }
  return uVar1;
}



/* === FUN_10802e80 @ 10802e80 (size=784 depth=3 hw_refs=1) === */
/* String refs:
   "Unit:%d Mem[%s] DMA data from cache.\n"
*/

undefined4 FUN_10802e80(int param_1,int param_2,int param_3,int param_4,int param_5,void *param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_20;
  
  local_20 = param_3;
  if ((*(int *)(&DAT_1212d36c + param_1 * 4) == 1) &&
     (*(char *)((&DAT_1212d2dc)[param_1] + 0x2f186b) != '\0')) {
    if (param_3 == -1) {
      local_20 = *(int *)((&DAT_1212d2dc)[param_1] + (param_2 + 0x2724) * 4 + 0x10);
    }
    iVar2 = *(int *)((&DAT_1212d2dc)[param_1] + (param_2 * 0xaf + local_20 + 0x3a3c) * 4 + 4);
    if ((((iVar2 != 0) &&
         ((**(byte **)((&DAT_1212d2dc)[param_1] + (param_2 * 0xaf + local_20 + 0x3a74) * 4 + 0xc) &
          1) != 0)) && (param_2 != 0x7d6)) &&
       (((param_2 != 0x7e1 && (param_2 != 0x7e2)) &&
        (*(char *)((&DAT_1212d2dc)[param_1] + 0x2f1868) == '\0')))) {
      iVar3 = (int)(*(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                              param_2 * 4) + 0x28) + 3) >> 2;
      iVar4 = param_4;
      if (param_5 < param_4) {
        iVar4 = param_5;
      }
      if (param_4 < param_5) {
        param_5 = param_5 - param_4;
      }
      else {
        param_5 = param_4 - param_5;
      }
      memcpy(param_6,(void *)(iVar2 + iVar4 * iVar3 * 4),(param_5 + 1) * iVar3 * 4);
      FUN_10761a94(0x10004,"Unit:%d Mem[%s] DMA data from cache.\n",param_1,
                   (&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_2]);
      return 0;
    }
  }
  uVar1 = FUN_10803190(param_1,param_2,0,local_20,param_4,param_5,param_6);
  return uVar1;
}



/* === FUN_107a8744 @ 107a8744 (size=1804 depth=4 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
*/

int FUN_107a8744(int param_1,int param_2,uint param_3,int param_4,int param_5,byte *param_6)

{
  int iVar1;
  uint *puVar2;
  uint *local_30;
  int local_1c;
  uint local_18;
  int local_14;
  int local_10;
  byte *local_c;
  
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  local_10 = param_5;
  local_c = param_6;
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c24) & 0x2000000) == 0) {
    iVar1 = FUN_107a8020(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    if (((((param_2 < 0) || (0x10e3 < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) ==
          0)) || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                              param_2 * 4) & 2) == 0)) &&
       (((FUN_1076193c("mem %s is invalid\n",(&PTR_s_ACTIONPROFILETABLE_11ab1c04)[param_2]),
         local_1c < 0 || (0x10e3 < local_1c)) ||
        ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + local_1c * 4) ==
          0 || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                            local_1c * 4) & 2) == 0)))))) {
      FUN_11312544("SOC_MEM_IS_VALID(unit, mem)",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                   ,0x9b2);
    }
    if ((local_14 < 0) || (0x39 < local_14)) {
      FUN_11312544("block >= 0 && block < SOC_MAX_NUM_BLKS",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                   ,0x9b5);
    }
    if (local_10 < 0) {
      FUN_11312544("index >= 0",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                   ,0x9b6);
    }
    *local_c = (byte)(**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                 local_1c * 4) >> 0x16) & 7;
    if (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c24) & 0x8000000) == 0) ||
       (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) + local_14 * 0x10)
          != 0x1f &&
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) + local_14 * 0x10)
          != 0x30)) ||
        (iVar1 = FUN_10efd074(param_1,local_1c,local_10,&local_1c,&local_10), -1 < iVar1)))) {
      local_30 = *(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                           local_1c * 4);
      if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c40) & 0x1000000) != 0) {
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) +
                      local_14 * 0x10) == 0x2f) && ((*local_30 & 0x40080000) != 0)) &&
           (iVar1 = FUN_10efd074(param_1,local_1c,local_10,&local_1c,&local_10), iVar1 < 0)) {
          return iVar1;
        }
        local_30 = *(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                             local_1c * 4);
      }
      if (local_18 == 0) {
        FUN_10761a94(0x40000000,
                     "addr: %x, mip->base: %x, block: %x, index = %d, mip->gran: %d, * = %x\n",
                     local_30[8] + local_30[9] * local_10,local_30[8],
                     *(undefined4 *)
                      (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) +
                       local_14 * 0x10 + 0xc),local_10,local_30[9],local_30[9] * local_10);
        iVar1 = local_30[8] + local_30[9] * local_10;
      }
      else {
        if ((*local_30 & 0x8000) == 0) {
          FUN_11312544("mip->flags & SOC_MEM_FLAG_IS_ARRAY",
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                       ,0x9d9);
        }
        puVar2 = *(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x2c) +
                           local_1c * 4);
        if (puVar2 == (uint *)0x0) {
          FUN_11312544(&DAT_113b8568,
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                       ,0x9db);
        }
        if (*puVar2 <= local_18) {
          FUN_11312544("array_index < maip->numels",
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/drvmem.c"
                       ,0x9dc);
        }
        FUN_10761a94(0x40000000,
                     "addr: %x, mip->base: %x, block: %x, index = %d, mip->gran: %d, * = %x, arr_in = %u, skip = %u\n"
                     ,local_30[8] + puVar2[1] * local_18 + local_30[9] * local_10,local_30[8],
                     *(undefined4 *)
                      (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) +
                       local_14 * 0x10 + 0xc),local_10,local_30[9],local_30[9] * local_10,local_18,
                     puVar2[1]);
        iVar1 = local_30[8] + puVar2[1] * local_18 + local_30[9] * local_10;
      }
    }
  }
  return iVar1;
}



/* === FUN_10fa88c0 @ 10fa88c0 (size=692 depth=3 hw_refs=1) === */
/* String refs:
   "soc_fb_vlanmac_entry_del: bucket %d\n"
*/

/* WARNING: Removing unreachable block (ram,0x10fa8948) */
/* WARNING: Removing unreachable block (ram,0x10fa8954) */
/* WARNING: Removing unreachable block (ram,0x10fa8988) */
/* WARNING: Removing unreachable block (ram,0x10fa89e4) */
/* WARNING: Removing unreachable block (ram,0x10fa899c) */
/* WARNING: Removing unreachable block (ram,0x10fa89a8) */
/* WARNING: Removing unreachable block (ram,0x10fa89dc) */

int FUN_10fa88c0(int param_1,undefined4 param_2,void *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_68;
  int local_64;
  undefined1 auStack_3c [24];
  undefined4 local_24 [3];
  int local_18;
  undefined4 local_14;
  void *local_10;
  int *local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  iVar1 = FUN_10e9d58c(param_1,0,local_24);
  if (-1 < iVar1) {
    for (local_64 = 0; local_64 < 1; local_64 = local_64 + 1) {
      *local_c = -1;
      iVar1 = FUN_10fa8278(local_18,local_24[0],local_14);
      FUN_10761a94(0x10000,"soc_fb_vlanmac_entry_del: bucket %d\n",iVar1);
      for (local_68 = 0; local_68 < 4; local_68 = local_68 + 1) {
        iVar3 = iVar1 * 4 + local_68;
        iVar2 = FUN_1080290c(local_18,0x1085,0xffffffff,iVar3,auStack_3c);
        if (iVar2 < 0) {
          return iVar2;
        }
        iVar2 = FUN_107a36e4(local_18,0x1085,auStack_3c,0xe37e);
        if ((iVar2 != 0) &&
           (iVar2 = (**(code **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) +
                                                  0x24) + 0x4214) + 4))
                              (local_18,local_14,auStack_3c), iVar2 == 0)) {
          memcpy(local_10,auStack_3c,0x18);
          *local_c = iVar3;
          return 0;
        }
      }
    }
    iVar1 = -7;
  }
  return iVar1;
}



/* === FUN_10e9bdd0 @ 10e9bdd0 (size=664 depth=5 hw_refs=1) === */
/* String refs:
   "soc_fb_vlan_mac_hash: invalid hash_sel %d\n"
*/

uint FUN_10e9bdd0(int param_1,undefined4 param_2,undefined1 *param_3)

{
  uint uVar1;
  uint local_28;
  int local_24;
  
  if (*(int *)((&DAT_1212d2dc)[param_1] + 0x2f19ec) == 0) {
    uVar1 = *(int *)((&DAT_1212d324)[param_1] + 0xf6c58) >> 2;
    local_24 = 0;
    for (local_28 = 1; (local_28 != 0 && ((uVar1 & local_28) != 0)); local_28 = local_28 << 1) {
      local_24 = local_24 + 1;
    }
    *(uint *)((&DAT_1212d2dc)[param_1] + 0x2f19ec) = uVar1;
    *(int *)((&DAT_1212d2dc)[param_1] + 0x2f19f0) = local_24;
  }
  switch(param_2) {
  case 0:
    local_28 = 0;
    break;
  case 1:
    local_28 = FUN_10e9aa70(param_3,6);
    local_28 = local_28 >> (0x20U - *(int *)((&DAT_1212d2dc)[param_1] + 0x2f19f0) & 0x3f);
    break;
  case 2:
    local_28 = FUN_10e9aa70(param_3,6);
    break;
  case 3:
    local_28 = (uint)CONCAT11(param_3[1],*param_3);
    break;
  case 4:
    local_28 = FUN_10e9aacc(param_3,6);
    break;
  case 5:
    local_28 = FUN_10e9aacc(param_3,6);
    local_28 = local_28 >> (0x10U - *(int *)((&DAT_1212d2dc)[param_1] + 0x2f19f0) & 0x3f);
    break;
  default:
    FUN_10761a94(0x200000,"soc_fb_vlan_mac_hash: invalid hash_sel %d\n",param_2);
    local_28 = 0;
  }
  return *(uint *)((&DAT_1212d2dc)[param_1] + 0x2f19ec) & local_28;
}



/* === FUN_1084aebc @ 1084aebc (size=400 depth=3 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
*/

undefined4
FUN_1084aebc(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 local_34;
  undefined1 local_30 [8];
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_34 = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  uVar1 = FUN_108508ac(param_1,param_2,param_3,param_4,&local_34,local_30);
  if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                         local_24 * 4) + 0x10) & 1) == 0) {
    FUN_11312544("SOC_REG_IS_64(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x84f);
  }
  if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c3c) & 0x8000) != 0) {
    FUN_1086529c(local_28,local_24,local_20,local_1c,local_18,local_14);
  }
  if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
    uVar1 = FUN_1084a984(local_28,uVar1,local_18,local_14);
  }
  else {
    uVar1 = FUN_10848924(local_28,local_34,local_30[0],uVar1,local_18,local_14);
  }
  return uVar1;
}



/* === FUN_1083c3b4 @ 1083c3b4 (size=236 depth=1 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_loopback_get: unit %d, port %d\n"
*/

int FUN_1083c3b4(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  
  local_24[0] = 0;
  if (param_3 == 0) {
    iVar1 = -4;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    FUN_10761a94(0x50000,"entered soc_phyctrl_loopback_get: unit %d, port %d\n",param_1,param_2);
    iVar1 = FUN_1083a030(local_18,local_14,local_24);
    if (-1 < iVar1) {
      if (local_24[0] == 0) {
        iVar1 = -4;
      }
      else if (*(int *)(local_24[0] + 0x48) == 0) {
        iVar1 = -0x10;
      }
      else {
        iVar1 = (**(code **)(local_24[0] + 0x48))(local_18,local_14,local_10);
      }
    }
  }
  return iVar1;
}



/* === FUN_1083cab4 @ 1083cab4 (size=208 depth=2 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_linkup_evt: unit %d, port %d\n"
*/

int FUN_1083cab4(undefined4 param_1,undefined4 param_2)

{
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  FUN_10761a94(0x50000,"entered soc_phyctrl_linkup_evt: unit %d, port %d\n",param_1,param_2);
  local_24[0] = 0;
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x58) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x58))(local_18,local_14);
    }
  }
  return local_28;
}



/* === FUN_1083c5b4 @ 1083c5b4 (size=220 depth=1 hw_refs=1) === */
/* String refs:
   "entered soc_phyctrl_interface_set: unit %d, port %d, pif %d\n"
*/

int FUN_1083c5b4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_24[0] = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  FUN_10761a94(0x50000,"entered soc_phyctrl_interface_set: unit %d, port %d, pif %d\n",param_1,
               param_2,param_3);
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x4c) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x4c))(local_18,local_14,local_10);
    }
  }
  return local_28;
}



/* === FUN_107d864c @ 107d864c (size=1772 depth=2 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/link.c"
*/

undefined4 FUN_107d864c(int param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  undefined4 local_44;
  uint local_40 [4];
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_18;
  
  local_18 = param_1;
  puVar4 = (uint *)(&DAT_1212d2dc)[param_1];
  local_40[0] = *param_2;
  local_40[1] = param_2[1];
  local_40[2] = param_2[2];
  local_40[3] = param_2[3];
  local_30 = param_2[4];
  local_2c = param_2[5];
  local_28 = param_2[6];
  local_24 = param_2[7];
  for (local_68 = 0; local_68 < 8; local_68 = local_68 + 1) {
    local_40[local_68] = local_40[local_68] & param_3[local_68];
  }
  iVar1 = FUN_112d6d90(local_40);
  if (iVar1 == 0) {
    FUN_11312544("SOC_PBMP_IS_NULL(pbm)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/link.c"
                 ,0x2aa);
  }
  local_40[0] = *param_3;
  local_40[1] = param_3[1];
  local_40[2] = param_3[2];
  local_40[3] = param_3[3];
  local_30 = param_3[4];
  local_2c = param_3[5];
  local_28 = param_3[6];
  local_24 = param_3[7];
  for (local_64 = 0; local_64 < 8; local_64 = local_64 + 1) {
    local_40[local_64] =
         local_40[local_64] & *(uint *)((&DAT_1212d2dc)[local_18] + (local_64 + 0x88) * 4 + 0x14);
  }
  iVar1 = FUN_112d6d90(local_40);
  if (iVar1 == 0) {
    uVar5 = 0xfffffff0;
  }
  else {
    iVar1 = (&DAT_1212d2dc)[local_18];
    local_40[0] = *(uint *)(iVar1 + 0x488);
    local_40[1] = *(undefined4 *)(iVar1 + 0x48c);
    local_40[2] = *(undefined4 *)(iVar1 + 0x490);
    local_40[3] = *(undefined4 *)(iVar1 + 0x494);
    local_30 = *(undefined4 *)(iVar1 + 0x498);
    local_2c = *(undefined4 *)(iVar1 + 0x49c);
    local_28 = *(undefined4 *)(iVar1 + 0x4a0);
    local_24 = *(undefined4 *)(iVar1 + 0x4a4);
    for (local_60 = 0; local_60 < 8; local_60 = local_60 + 1) {
      local_40[local_60] = local_40[local_60] & param_2[local_60];
    }
    iVar1 = FUN_112d6d90(local_40);
    iVar6 = (&DAT_1212d2dc)[local_18];
    local_40[0] = *(uint *)(iVar6 + 0x488);
    local_40[1] = *(undefined4 *)(iVar6 + 0x48c);
    local_40[2] = *(undefined4 *)(iVar6 + 0x490);
    local_40[3] = *(undefined4 *)(iVar6 + 0x494);
    local_30 = *(undefined4 *)(iVar6 + 0x498);
    local_2c = *(undefined4 *)(iVar6 + 0x49c);
    local_28 = *(undefined4 *)(iVar6 + 0x4a0);
    local_24 = *(undefined4 *)(iVar6 + 0x4a4);
    for (local_5c = 0; local_5c < 8; local_5c = local_5c + 1) {
      local_40[local_5c] = local_40[local_5c] & param_3[local_5c];
    }
    iVar6 = FUN_112d6d90(local_40);
    if ((iVar1 == 0) && (iVar6 == 0)) {
      uVar5 = 0xfffffff0;
    }
    else {
      uVar5 = FUN_11312848();
      FUN_107d7418(local_18);
      local_40[0] = *param_2;
      local_40[1] = param_2[1];
      local_40[2] = param_2[2];
      local_40[3] = param_2[3];
      local_30 = param_2[4];
      local_2c = param_2[5];
      local_28 = param_2[6];
      local_24 = param_2[7];
      for (local_58 = 0; local_58 < 8; local_58 = local_58 + 1) {
        local_40[local_58] = local_40[local_58] | param_3[local_58];
      }
      iVar1 = FUN_112d6d90(local_40);
      if (iVar1 == 0) {
        *puVar4 = *puVar4 | 4;
      }
      else {
        *puVar4 = *puVar4 & 0xfffffffb;
      }
      iVar1 = FUN_1084bccc(local_18,0xf5e,0x77ed);
      if (iVar1 != 0) {
        if (*(int *)(&DAT_12125c5c + local_18 * 0x78) == 0) {
          local_44 = (**(code **)(&DAT_12125c60 + local_18 * 0x78))
                               (&DAT_12125c2c + local_18 * 0x78,0x10c);
        }
        else {
          local_44 = *(undefined4 *)(*(int *)(&DAT_12125c5c + local_18 * 0x78) + 0x10c);
        }
        iVar1 = FUN_112d6d90(local_40);
        FUN_1084d57c(local_18,0xf5e,&local_44,0x77ed,iVar1 == 0);
        if (*(int *)(&DAT_12125c5c + local_18 * 0x78) == 0) {
          (**(code **)(&DAT_12125c64 + local_18 * 0x78))
                    (&DAT_12125c2c + local_18 * 0x78,0x10c,local_44);
        }
        else {
          *(undefined4 *)(*(int *)(&DAT_12125c5c + local_18 * 0x78) + 0x10c) = local_44;
        }
      }
      uVar2 = param_2[1];
      uVar3 = param_2[2];
      uVar7 = param_2[3];
      puVar4[0xbc6c8] = *param_2;
      puVar4[0xbc6c9] = uVar2;
      puVar4[0xbc6ca] = uVar3;
      puVar4[0xbc6cb] = uVar7;
      uVar2 = param_2[5];
      uVar3 = param_2[6];
      uVar7 = param_2[7];
      puVar4[0xbc6cc] = param_2[4];
      puVar4[0xbc6cd] = uVar2;
      puVar4[0xbc6ce] = uVar3;
      puVar4[0xbc6cf] = uVar7;
      FUN_107d7d90(local_18);
      FUN_113127c0(uVar5);
      uVar5 = 0;
    }
  }
  return uVar5;
}



/* === FUN_1084c8b4 @ 1084c8b4 (size=1152 depth=1 hw_refs=1) === */
/* String refs:
   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
*/

uint FUN_1084c8b4(int param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  uint uVar1;
  int *local_48;
  int *local_44;
  int *local_40;
  int *local_3c;
  uint local_1c;
  
  if ((((param_2 < 0) || (0x901f < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
     && (((FUN_1076193c("reg %s is invalid\n",
                        (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2]), param_2 < 0 ||
          (0x901f < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) ==
          0)))) {
    FUN_11312544("SOC_REG_IS_VALID(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x99a);
  }
  local_48 = (int *)0x0;
  local_44 = *(int **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                               param_2 * 4) + 0x18);
  local_3c = local_44;
  if ((*local_44 != param_5) &&
     (local_3c = local_44 +
                 (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                   param_2 * 4) + 0x14) + -1) * 3, *local_3c != param_5)) {
    uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                              param_2 * 4) + 0x14);
    local_40 = local_44 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    while ((((local_44 < local_3c && (local_40 < local_3c)) && (*local_44 != param_5)) &&
           (*local_40 != param_5))) {
      if (param_5 < *local_40) {
        local_3c = local_40 + -3;
      }
      else {
        if (param_5 <= *local_40) break;
        local_44 = local_40 + 3;
      }
      uVar1 = ((int)local_3c - (int)local_44 >> 2) * -0x55555555 + 1;
      local_40 = local_44 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    }
    if (*local_40 == param_5) {
      local_48 = local_40;
      local_3c = local_48;
    }
    else {
      local_3c = local_48;
      if (*local_44 == param_5) {
        local_48 = local_44;
        local_3c = local_48;
      }
    }
  }
  local_48 = local_3c;
  if (local_48 == (int *)0x0) {
    FUN_1076193c("reg %s field %s is invalid\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2],
                 (&PTR_DAT_11d34bbc)[param_5]);
    FUN_11312544("finfop",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x9a6);
  }
  uVar1 = (uint)*(ushort *)((int)local_48 + 6);
  if ((int)(uVar1 - 0x20) < 0) {
    local_1c = param_4 >> (uVar1 & 0x3f) | (param_3 << 1) << (0x1f - uVar1 & 0x3f);
  }
  else {
    local_1c = param_3 >> (uVar1 - 0x20 & 0x3f);
  }
  if (*(ushort *)(local_48 + 1) < 0x20) {
    local_1c = (1 << (*(ushort *)(local_48 + 1) & 0x3f)) - 1U & local_1c;
  }
  return local_1c;
}



