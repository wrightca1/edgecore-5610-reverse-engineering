/* Top-N called BCM SDK helper functions, decompiled */

/* === bcm_port_link_failed_clear @ 10762108 (size=152) === */
/* Called by 79 BCM APIs */

bool bcm_port_link_failed_clear(int param_1,uint param_2)

{
  uint local_14;
  
  local_14 = param_2;
  if ((param_2 & 0xff00) == 0) {
    local_14 = param_2 | 0x400;
  }
  return (*(uint *)(param_1 + ((param_2 & 7) + 4) * 4 + 4) & local_14 & 0xffffff00) ==
         (local_14 & 0xffffff00);
}



/* === FUN_10461a0c @ 10461a0c (size=748) === */
/* Called by 78 BCM APIs */

void FUN_10461a0c(undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,int param_7)

{
  int iVar1;
  undefined *puVar2;
  undefined *local_38;
  
  if (param_7 < 0) {
    if ((param_7 < 1) && (-0x13 < param_7)) {
      iVar1 = -param_7;
    }
    else {
      iVar1 = 0x13;
    }
    local_38 = (&PTR_DAT_11e45348)[iVar1];
  }
  else {
    local_38 = PTR_DAT_11e45348;
  }
  if (param_3 == 1) {
    iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
    if ((iVar1 != 0) && (PTR_FUN_11e46d80 != (undefined *)0x0)) {
      if (param_2 < 2) {
        puVar2 = &DAT_1139bdbc;
      }
      else {
        puVar2 = &DAT_1139bdd8;
      }
      (*(code *)PTR_FUN_11e46d80)
                ("API: %s(%d%s) -> %d %s\n",param_1,param_4,puVar2,param_7,local_38);
    }
  }
  else if (param_3 == 2) {
    iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
    if ((iVar1 != 0) && (PTR_FUN_11e46d80 != (undefined *)0x0)) {
      if (param_2 < 3) {
        puVar2 = &DAT_1139bdbc;
      }
      else {
        puVar2 = &DAT_1139bdd8;
      }
      (*(code *)PTR_FUN_11e46d80)
                ("API: %s(%d,%d%s) -> %d %s\n",param_1,param_4,param_5,puVar2,param_7,local_38);
    }
  }
  else if (param_3 == 0) {
    iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
    if ((iVar1 != 0) && (PTR_FUN_11e46d80 != (undefined *)0x0)) {
      if (param_2 < 1) {
        puVar2 = &DAT_1139bdbc;
      }
      else {
        puVar2 = &DAT_1139bdb8;
      }
      (*(code *)PTR_FUN_11e46d80)("API: %s(%s) -> %d %s\n",param_1,puVar2,param_7,local_38);
    }
  }
  else {
    iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
    if ((iVar1 != 0) && (PTR_FUN_11e46d80 != (undefined *)0x0)) {
      if (param_2 < 4) {
        puVar2 = &DAT_1139bdbc;
      }
      else {
        puVar2 = &DAT_1139bdd8;
      }
      (*(code *)PTR_FUN_11e46d80)
                ("API: %s(%d,%d,%d%s) -> %d %s\n",param_1,param_4,param_5,param_6,puVar2,param_7,
                 local_38);
    }
  }
  return;
}



/* === FUN_112c5590 @ 112c5590 (size=288) === */
/* Called by 78 BCM APIs */

int FUN_112c5590(int param_1,int param_2)

{
  int local_28;
  int local_24 [3];
  int local_18;
  int local_14;
  
  local_28 = -3;
  if (((-1 < param_1) && (param_1 < 0x12)) && ((&DAT_1212d2dc)[param_1] != 0)) {
    local_18 = param_1;
    local_14 = param_2;
    local_28 = (*(code *)(&PTR_FUN_11e45240)[param_2])(param_1,0xf4,local_24);
    if (((-1 < local_28) && (local_24[0] != 0)) &&
       (*(int *)((&DAT_1212d2dc)[local_18] + 0x2f2bd4) != 0)) {
      local_28 = (*(code *)(&PTR_FUN_11e45238)[local_14])(local_18,0xf3,1);
    }
  }
  return local_28;
}



/* === FUN_10761a94 @ 10761a94 (size=220) === */
/* Called by 52 BCM APIs */

undefined4
FUN_10761a94(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  byte in_cr1;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 *local_70;
  undefined4 *local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_48 = param_1;
    local_40 = param_2;
    local_38 = param_3;
    local_30 = param_4;
    local_28 = param_5;
    local_20 = param_6;
    local_18 = param_7;
    local_10 = param_8;
  }
  if (DAT_11efd698 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    local_74 = 2;
    local_73 = 0;
    local_70 = &stack0x00000008;
    local_6c = &local_68;
    local_68 = param_9;
    local_64 = param_10;
    local_60 = param_11;
    local_5c = param_12;
    local_58 = param_13;
    local_54 = param_14;
    local_50 = param_15;
    local_4c = param_16;
    uVar1 = (*DAT_11efd698)(param_9,param_10,&local_74);
  }
  return uVar1;
}



/* === FUN_105a6a18 @ 105a6a18 (size=284) === */
/* Called by 43 BCM APIs */

int FUN_105a6a18(int param_1,uint param_2,uint *param_3)

{
  int iVar1;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    if ((param_2 >> 0x1a == 0) || (0x29 < param_2 >> 0x1a)) {
      if (((int)param_2 < 0) ||
         ((0x81 < (int)param_2 ||
          (*(int *)((&DAT_1212d2dc)[param_1] + (param_2 + 0x1c84) * 4 + 4) == 0)))) {
        return -0x12;
      }
      *param_3 = param_2;
    }
    else {
      iVar1 = FUN_10619410(param_1,param_2,param_3);
      if (iVar1 < 0) {
        return iVar1;
      }
    }
    iVar1 = 0;
  }
  return iVar1;
}



/* === FUN_11312da0 @ 11312da0 (size=348) === */
/* Called by 42 BCM APIs */

undefined4 FUN_11312da0(pthread_mutex_t *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int local_28;
  timespec tStack_20;
  pthread_mutex_t *local_18;
  int local_14;
  
  local_28 = 0;
  local_18 = param_1;
  local_14 = param_2;
  if (param_1 == (pthread_mutex_t *)0x0) {
    FUN_11312544(&DAT_11808920,
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/sal/core/unix/sync.c"
                 ,0x23c);
  }
  FUN_11312904();
  if (local_14 == -1) {
    do {
      local_28 = pthread_mutex_lock(param_1);
      if (local_28 == 0) break;
      piVar1 = __errno_location();
    } while (*piVar1 == 4);
  }
  else {
    iVar2 = FUN_11312a54(&tStack_20,local_14);
    if (iVar2 != 0) {
      do {
        iVar2 = pthread_mutex_timedlock(param_1,&tStack_20);
        if (iVar2 == 0) {
          local_28 = 0;
          goto LAB_11312ec4;
        }
        piVar1 = __errno_location();
      } while ((*piVar1 == 0xb) || (piVar1 = __errno_location(), *piVar1 == 4));
      piVar1 = __errno_location();
      local_28 = *piVar1;
    }
  }
LAB_11312ec4:
  if (local_28 == 0) {
    uVar3 = 0;
  }
  else {
    FUN_1131299c();
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



/* === FUN_11312efc @ 11312efc (size=140) === */
/* Called by 42 BCM APIs */

undefined4 FUN_11312efc(pthread_mutex_t *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == (pthread_mutex_t *)0x0) {
    FUN_11312544(&DAT_11808920,
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/sal/core/unix/sync.c"
                 ,0x2a2);
  }
  iVar1 = pthread_mutex_unlock(param_1);
  FUN_1131299c();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



/* === FUN_1038b364 @ 1038b364 (size=80) === */
/* Called by 34 BCM APIs */

undefined4 FUN_1038b364(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1038a488(param_1,param_2,1,2);
  return uVar1;
}



/* === FUN_107a36e4 @ 107a36e4 (size=96) === */
/* Called by 15 BCM APIs */

undefined4 FUN_107a36e4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_28 [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_107a2eb0(param_1,param_2,param_3,param_4,local_28);
  return local_28[0];
}



/* === FUN_1080290c @ 1080290c (size=208) === */
/* Called by 15 BCM APIs */

undefined4
FUN_1080290c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int local_24;
  
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
  uVar1 = FUN_10802b30(param_1,local_24,0,param_3,param_4,param_5);
  return uVar1;
}



/* === memset @ 113179b0 (size=16) === */
/* Called by 14 BCM APIs */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_memset_118195e4)();
  return pvVar1;
}



/* === FUN_10839f58 @ 10839f58 (size=216) === */
/* Called by 10 BCM APIs */

undefined4 FUN_10839f58(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(*(int *)(&DAT_12136d94 + param_1 * 4) + param_2 * 4);
  iVar2 = *(int *)(*(int *)(&DAT_12136ddc + param_1 * 4) + param_2 * 4);
  if ((iVar1 == 0) && (iVar2 == 0)) {
    uVar3 = 0xffffffef;
  }
  else {
    if (iVar1 == 0) {
      *param_3 = *(undefined4 *)(iVar2 + 0xfc);
    }
    else {
      *param_3 = *(undefined4 *)(iVar1 + 0xfc);
    }
    uVar3 = 0;
  }
  return uVar3;
}



/* === FUN_11312544 @ 11312544 (size=84) === */
/* Called by 9 BCM APIs */

void FUN_11312544(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)PTR_FUN_11e46c48)(param_1,param_2,param_3);
  return;
}



/* === bcm_mirror_ingress_get @ 10762a98 (size=512) === */
/* Called by 9 BCM APIs */

undefined4 bcm_mirror_ingress_get(int param_1,int param_2)

{
  bool bVar1;
  int local_28;
  undefined *local_24;
  int local_20;
  
  local_28 = 0;
  local_24 = (undefined *)0x0;
  while( true ) {
    if (*(int *)(param_1 + local_28 * 4) == -1) {
      return 0;
    }
    local_20 = 0;
    bVar1 = true;
    switch(param_2) {
    case 0x61:
      local_24 = &DAT_11862a44;
      break;
    case 0x62:
      local_24 = &DAT_11862ab0;
      break;
    case 99:
      local_24 = &DAT_11862abc;
      break;
    case 100:
      local_24 = &DAT_11862b00;
      break;
    case 0x65:
      local_24 = &DAT_11862b38;
      break;
    case 0x66:
      local_24 = &DAT_11862b48;
      break;
    case 0x67:
      local_24 = &DAT_11e46d9c;
      break;
    case 0x68:
      local_24 = &DAT_11862bb0;
      break;
    default:
      bVar1 = false;
    }
    if (bVar1) break;
    if (*(int *)(param_1 + local_28 * 4) == param_2) {
      return 1;
    }
    local_28 = local_28 + 1;
  }
  if (local_24 == (undefined *)0x0) {
    return 0;
  }
  while( true ) {
    if (*(int *)(local_24 + local_20 * 4) == -1) {
      return 0;
    }
    if (*(int *)(param_1 + local_28 * 4) == *(int *)(local_24 + local_20 * 4)) break;
    local_20 = local_20 + 1;
  }
  return 1;
}



/* === FUN_1038b3b4 @ 1038b3b4 (size=80) === */
/* Called by 9 BCM APIs */

undefined4 FUN_1038b3b4(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1038a488(param_1,param_2,0,2);
  return uVar1;
}



/* === FUN_10bf748c @ 10bf748c (size=3156) === */
/* Called by 8 BCM APIs */

uint FUN_10bf748c(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  uint local_28;
  
  local_28 = 0;
  iVar1 = (int)param_2 >> 5;
  switch(param_3) {
  case 0:
    if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
        *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10) +
                0xc)) + 1 < (int)param_2) {
      local_28 = 0xffffffff;
    }
    else {
      local_28 = *(uint *)(*(int *)(&DAT_11f095c8 + param_1 * 0x44) +
                          (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                 1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20
                      & 0x3f);
    }
    break;
  case 1:
    if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
        *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10) +
                0xc)) + 1 < (int)param_2) {
      local_28 = 0xffffffff;
    }
    else {
      local_28 = *(uint *)(*(int *)(&DAT_11f095d0 + param_1 * 0x44) +
                          (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                 1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20
                      & 0x3f);
    }
    break;
  case 2:
    if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
        *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10) +
                0xc)) + 1 < (int)param_2) {
      local_28 = 0xffffffff;
    }
    else {
      local_28 = *(uint *)(*(int *)(&DAT_11f095e4 + param_1 * 0x44) +
                          (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                 1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20
                      & 0x3f);
    }
    break;
  case 3:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c34) & 0x40000) != 0) {
      if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x4358) == 0)
         || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x4358) &
             2) == 0)) {
        if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d18) == 0)
           || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d18)
               & 2) == 0)) {
          return 0xffffffff;
        }
        if ((*(int *)((&DAT_1212d324)[param_1] + 0xe4644) -
            *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                             0x3d18) + 0xc)) + 1 < (int)param_2) {
          return 0xffffffff;
        }
      }
      else if ((*(int *)((&DAT_1212d324)[param_1] + 0xfb704) -
               *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                                0x4358) + 0xc)) + 1 < (int)param_2) {
        return 0xffffffff;
      }
      local_28 = *(uint *)(*(int *)(&DAT_11f095e8 + param_1 * 0x44) +
                          (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                 1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20
                      & 0x3f);
    }
    break;
  case 4:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c3c) & 2) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095ec + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  case 5:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c3c) & 0x1000000) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095f0 + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  case 6:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c3c) & 4) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095f4 + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  case 7:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c44) & 2) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095d8 + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  case 8:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c44) & 0x200000) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095e0 + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  case 9:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c48) & 0x20) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095f8 + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  case 10:
    if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c48) & 0x1000) != 0) {
      if ((*(int *)((&DAT_1212d324)[param_1] + 0xe446c) -
          *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x3d10)
                  + 0xc)) + 1 < (int)param_2) {
        local_28 = 0xffffffff;
      }
      else {
        local_28 = *(uint *)(*(int *)(&DAT_11f095fc + param_1 * 0x44) +
                            (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
                   1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f);
      }
    }
    break;
  default:
    local_28 = *(uint *)(*(int *)(&DAT_11f095c0 + param_1 * 0x44) +
                        (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * 4) &
               1 << (param_2 + (iVar1 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20 &
                    0x3f);
  }
  return local_28;
}



/* === FUN_1083a030 @ 1083a030 (size=320) === */
/* Called by 8 BCM APIs */

undefined4 FUN_1083a030(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(*(int *)(&DAT_12136d94 + param_1 * 4) + param_2 * 4);
  iVar2 = *(int *)(*(int *)(&DAT_12136ddc + param_1 * 4) + param_2 * 4);
  if ((iVar1 == 0) && (iVar2 == 0)) {
    uVar3 = 0xffffffef;
  }
  else {
    if ((*(uint *)(*(int *)(&DAT_12136e24 + param_1 * 4) + param_2 * 0x18 + 0xc) & 4) == 0) {
      if (iVar1 == 0) {
        *param_3 = *(undefined4 *)(iVar2 + 0xfc);
      }
      else {
        *param_3 = *(undefined4 *)(iVar1 + 0xfc);
      }
    }
    else if (iVar2 == 0) {
      *param_3 = *(undefined4 *)(iVar1 + 0xfc);
    }
    else {
      *param_3 = *(undefined4 *)(iVar2 + 0xfc);
    }
    uVar3 = 0;
  }
  return uVar3;
}



/* === FUN_1076193c @ 1076193c (size=220) === */
/* Called by 8 BCM APIs */

undefined4
FUN_1076193c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  byte in_cr1;
  undefined1 local_84;
  undefined1 local_83;
  undefined1 *local_80;
  undefined1 *local_7c;
  undefined1 auStack_78 [4];
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_58 = param_1;
    local_50 = param_2;
    local_48 = param_3;
    local_40 = param_4;
    local_38 = param_5;
    local_30 = param_6;
    local_28 = param_7;
    local_20 = param_8;
  }
  if (DAT_11efd698 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    local_84 = 1;
    local_83 = 0;
    local_80 = &stack0x00000008;
    local_7c = auStack_78;
    local_74 = param_10;
    local_70 = param_11;
    local_6c = param_12;
    local_68 = param_13;
    local_64 = param_14;
    local_60 = param_15;
    local_5c = param_16;
    local_18 = param_9;
    uVar1 = (*DAT_11efd698)(0,param_9,&local_84);
  }
  return uVar1;
}



/* === FUN_1084a784 @ 1084a784 (size=512) === */
/* Called by 7 BCM APIs */

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



/* === FUN_1084d57c @ 1084d57c (size=1264) === */
/* Called by 7 BCM APIs */

void FUN_1084d57c(int param_1,int param_2,uint *param_3,int param_4,uint param_5)

{
  uint uVar1;
  int *local_48;
  uint local_44;
  int *local_40;
  int *local_3c;
  int *local_38;
  
  if ((((param_2 < 0) || (0x901f < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
     && (((FUN_1076193c("reg %s is invalid\n",
                        (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2]), param_2 < 0 ||
          (0x901f < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) ==
          0)))) {
    FUN_11312544("SOC_REG_IS_VALID(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xa28);
  }
  local_48 = (int *)0x0;
  local_40 = *(int **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                               param_2 * 4) + 0x18);
  local_38 = local_40;
  if ((*local_40 != param_4) &&
     (local_38 = local_40 +
                 (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                   param_2 * 4) + 0x14) + -1) * 3, *local_38 != param_4)) {
    uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                              param_2 * 4) + 0x14);
    local_3c = local_40 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    while ((((local_40 < local_38 && (local_3c < local_38)) && (*local_40 != param_4)) &&
           (*local_3c != param_4))) {
      if (param_4 < *local_3c) {
        local_38 = local_3c + -3;
      }
      else {
        if (param_4 <= *local_3c) break;
        local_40 = local_3c + 3;
      }
      uVar1 = ((int)local_38 - (int)local_40 >> 2) * -0x55555555 + 1;
      local_3c = local_40 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
    }
    if (*local_3c == param_4) {
      local_48 = local_3c;
      local_38 = local_48;
    }
    else {
      local_38 = local_48;
      if (*local_40 == param_4) {
        local_48 = local_40;
        local_38 = local_48;
      }
    }
  }
  local_48 = local_38;
  if (local_48 == (int *)0x0) {
    FUN_1076193c("reg %s field %s is invalid\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2],
                 (&PTR_DAT_11d34bbc)[param_4]);
    FUN_11312544("finfop",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xa34);
  }
  if (*(ushort *)(local_48 + 1) < 0x20) {
    local_44 = (1 << (*(ushort *)(local_48 + 1) & 0x3f)) - 1;
    if (((~local_44 & param_5) != 0) &&
       (FUN_1076193c("reg %s field %s is too big\n",
                     (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2],
                     (&PTR_DAT_11d34bbc)[param_4]), (~local_44 & param_5) != 0)) {
      FUN_11312544("!VALUE_TOO_BIG_FOR_FIELD",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                   ,0xa3e);
    }
  }
  else {
    local_44 = 0xffffffff;
  }
  *param_3 = *param_3 & ~(local_44 << (*(ushort *)((int)local_48 + 6) & 0x3f)) |
             param_5 << (*(ushort *)((int)local_48 + 6) & 0x3f);
  return;
}



/* === FUN_10847ab4 @ 10847ab4 (size=544) === */
/* Called by 6 BCM APIs */

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



/* === FUN_10619410 @ 10619410 (size=984) === */
/* Called by 6 BCM APIs */

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



/* === FUN_107a37cc @ 107a37cc (size=92) === */
/* Called by 6 BCM APIs */

void FUN_107a37cc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 local_18 [5];
  
  local_18[0] = param_5;
  FUN_107a30bc(param_1,param_2,param_3,param_4,local_18);
  return;
}



/* === FUN_107a2bf8 @ 107a2bf8 (size=696) === */
/* Called by 5 BCM APIs */

bool FUN_107a2bf8(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  
  if ((((param_2 < 0) || (0x10e3 < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) == 0))
     || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4)
         & 2) == 0)) {
    bVar3 = false;
  }
  else {
    iVar1 = *(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4);
    local_38 = (int *)0x0;
    local_34 = *(int **)(iVar1 + 0x2c);
    local_2c = local_34;
    if ((*local_34 != param_3) &&
       (local_2c = local_34 + (*(ushort *)(iVar1 + 0x2a) - 1) * 3, *local_2c != param_3)) {
      local_30 = local_34 + (uint)(*(ushort *)(iVar1 + 0x2a) >> 1) * 3;
      while (((local_34 < local_2c && (local_30 < local_2c)) &&
             ((*local_34 != param_3 && (*local_30 != param_3))))) {
        if (param_3 < *local_30) {
          local_2c = local_30 + -3;
        }
        else {
          if (param_3 <= *local_30) break;
          local_34 = local_30 + 3;
        }
        uVar2 = ((int)local_2c - (int)local_34 >> 2) * -0x55555555 + 1;
        local_30 = local_34 + (((int)uVar2 >> 1) + (uint)((int)uVar2 < 0 && (uVar2 & 1) != 0)) * 3;
      }
      if (*local_30 == param_3) {
        local_38 = local_30;
        local_2c = local_38;
      }
      else {
        local_2c = local_38;
        if (*local_34 == param_3) {
          local_38 = local_34;
          local_2c = local_38;
        }
      }
    }
    local_38 = local_2c;
    bVar3 = local_38 != (int *)0x0;
  }
  return bVar3;
}



/* === FUN_1062a874 @ 1062a874 (size=1232) === */
/* Called by 4 BCM APIs */

undefined4
FUN_1062a874(int param_1,uint param_2,uint *param_3,uint *param_4,uint *param_5,undefined4 *param_6)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if ((((param_3 == (uint *)0x0) || (param_5 == (uint *)0x0)) || (param_4 == (uint *)0x0)) ||
     (param_6 == (undefined4 *)0x0)) {
    uVar1 = 0xfffffffc;
  }
  else {
    uVar4 = (int)param_2 >> 0x11;
    uVar2 = (int)param_2 >> 0x14;
    if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 2)) {
      if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 2)) {
        uVar3 = param_2 & 0x3ff;
      }
      else {
        uVar3 = 0xffffffff;
      }
      *param_3 = uVar3;
      if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 2)) {
        uVar4 = uVar4 & 7;
      }
      else {
        uVar4 = 0xffffffff;
      }
      *param_4 = uVar4;
      *param_5 = 0xffffffff;
    }
    else {
      uVar3 = (int)param_2 >> 10;
      if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 3)) {
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 3)) {
          uVar5 = param_2 & 0x3ff;
        }
        else {
          uVar5 = 0xffffffff;
        }
        *param_3 = uVar5;
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 3)) {
          uVar4 = uVar4 & 7;
        }
        else {
          uVar4 = 0xffffffff;
        }
        *param_4 = uVar4;
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 3)) {
          uVar3 = uVar3 & 0xef;
        }
        else {
          uVar3 = 0xffffffff;
        }
        *param_5 = uVar3;
      }
      else if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 4)) {
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 4)) {
          uVar3 = param_2 & 0x3ff;
        }
        else {
          uVar3 = 0xffffffff;
        }
        *param_3 = uVar3;
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 4)) {
          uVar4 = uVar4 & 7;
        }
        else {
          uVar4 = 0xffffffff;
        }
        *param_4 = uVar4;
        *param_6 = 1;
        *param_5 = 0xffffffff;
      }
      else if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 5)) {
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 5)) {
          uVar5 = param_2 & 0x3ff;
        }
        else {
          uVar5 = 0xffffffff;
        }
        *param_3 = uVar5;
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 5)) {
          uVar4 = uVar4 & 7;
        }
        else {
          uVar4 = 0xffffffff;
        }
        *param_4 = uVar4;
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 5)) {
          uVar3 = uVar3 & 0xef;
        }
        else {
          uVar3 = 0xffffffff;
        }
        *param_5 = uVar3;
        *param_6 = 1;
      }
      else {
        if ((param_2 >> 0x1a != 0x22) || ((uVar2 & 0x3f) != 1)) {
          *param_3 = 0xffffffff;
          return 0;
        }
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 1)) {
          uVar4 = param_2 & 0x3ff;
        }
        else {
          uVar4 = 0xffffffff;
        }
        *param_3 = uVar4;
        if ((param_2 >> 0x1a == 0x22) && ((uVar2 & 0x3f) == 1)) {
          uVar3 = uVar3 & 0x3ff;
        }
        else {
          uVar3 = 0xffffffff;
        }
        *param_5 = uVar3;
      }
    }
    if ((((int)*param_3 < 0) || (0x81 < (int)*param_3)) ||
       (*(int *)((&DAT_1212d2dc)[param_1] + (*param_3 + 0x1c84) * 4 + 4) == 0)) {
      uVar1 = 0xffffffee;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



/* === FUN_1053ae58 @ 1053ae58 (size=648) === */
/* Called by 4 BCM APIs */

undefined4 FUN_1053ae58(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_28;
  int local_24;
  
  iVar1 = (&DAT_1212d324)[param_1];
  iVar2 = *(int *)(&DAT_1211e45c + param_1 * 4);
  if (*(int *)(&DAT_1211e45c + param_1 * 4) == 0) {
    uVar3 = 0xffffffef;
  }
  else if (*(int *)(iVar2 + 0xd8) == 0) {
    for (local_28 = 0; local_28 < 8; local_28 = local_28 + 1) {
      *(uint *)(param_2 + local_28 * 4) =
           *(uint *)(param_2 + local_28 * 4) &
           *(uint *)((&DAT_1212d2dc)[param_1] + (local_28 + 0x1328) * 4 + 0x14);
    }
    FUN_11312da0(*(undefined4 *)(*(int *)(&DAT_1211e45c + param_1 * 4) + 0x10),0xffffffff);
    for (local_24 = 0; local_24 < 8; local_24 = local_24 + 1) {
      *(uint *)(iVar1 + (local_24 + 0x3f0d8) * 4) =
           *(uint *)(iVar1 + (local_24 + 0x3f0d8) * 4) | *(uint *)(param_2 + local_24 * 4);
    }
    FUN_11312efc(*(undefined4 *)(*(int *)(&DAT_1211e45c + param_1 * 4) + 0x10));
    if (*(int *)(iVar2 + 0xe8) != 0) {
      FUN_103256c4(*(undefined4 *)(iVar2 + 0xe8));
    }
    FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0xe708),0xffffffff);
    *(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x2f2bd4) = 1;
    FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0xe708));
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



/* === FUN_1083a2a0 @ 1083a2a0 (size=852) === */
/* Called by 4 BCM APIs */

int FUN_1083a2a0(int param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_38;
  
  iVar1 = *(int *)(*(int *)(&DAT_12136d94 + param_1 * 4) + param_2 * 4);
  iVar2 = *(int *)(*(int *)(&DAT_12136ddc + param_1 * 4) + param_2 * 4);
  if ((iVar1 == 0) && (iVar2 == 0)) {
    iVar1 = -0x11;
  }
  else {
    iVar3 = iVar1;
    if (iVar2 != 0) {
      iVar3 = iVar2;
    }
    *param_4 = iVar3;
    *param_5 = *param_4;
    if (param_3 < 8) {
      if (param_3 == 0) {
        iVar1 = FUN_1083a170(param_1,param_2,param_4);
        if (-1 < iVar1) {
          *param_5 = *param_4;
          iVar1 = 0;
        }
      }
      else {
        for (local_38 = 1; local_38 <= param_3; local_38 = local_38 + 1) {
          if (local_38 == param_3) {
            if (((*param_5 != iVar2) && (*param_5 != iVar1)) && (*param_5 != 0)) {
              *(uint *)(*param_5 + 0xf0) = *(uint *)(*param_5 + 0xf0) | 0x80;
            }
            return 0;
          }
          if (*param_4 == iVar2) {
            if ((*(uint *)(*(int *)(&DAT_12136e24 + param_1 * 4) + param_2 * 0x18 + 0xc) & 0x8000000
                ) == 0) {
              iVar3 = iVar2;
              if (iVar1 != 0) {
                iVar3 = iVar1;
              }
              *param_4 = iVar3;
              *param_5 = *param_4;
            }
            else {
              *param_5 = *(int *)(*param_5 + 0x108);
              if (*param_5 != 0) goto LAB_1083a534;
              if (iVar1 == 0) {
                *param_5 = *param_4;
                return 0;
              }
              *param_4 = iVar1;
              *param_5 = *param_4;
            }
          }
          else {
LAB_1083a534:
            if (((*param_4 == iVar1) &&
                ((*(uint *)(*(int *)(&DAT_12136e24 + param_1 * 4) + param_2 * 0x18 + 0xc) &
                 0x8000000) != 0)) && (*param_5 = *(int *)(*param_5 + 0x108), *param_5 == 0)) {
              *param_5 = *param_4;
              return 0;
            }
          }
        }
        iVar1 = 0;
      }
    }
    else {
      iVar1 = -4;
    }
  }
  return iVar1;
}



/* === FUN_10808e6c @ 10808e6c (size=208) === */
/* Called by 4 BCM APIs */

undefined4
FUN_10808e6c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int local_24;
  
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
  uVar1 = FUN_10809014(param_1,local_24,0,param_3,param_4,param_5);
  return uVar1;
}



/* === bcm_port_ability_get @ 105cc324 (size=820) === */
/* Called by 4 BCM APIs */

int bcm_port_ability_get(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 local_1c;
  undefined4 *local_18;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_1c = param_2;
    local_18 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_1c);
    if (-1 < iVar1) {
      memset(local_18,0,0x28);
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_105a70e4(param_1,local_1c,local_18);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
      FUN_10761a94(0x800,"bcm_port_ability_local_get: u=%d p=%d rv=%d\n",param_1,local_1c,iVar1);
      FUN_10761a94(0x10800,
                   "Speed(HD=0x%08x, FD=0x%08x) Pause=0x%08x\nInterface=0x%08x Medium=0x%08x EEE=0x%08x Loopback=0x%08x Flags=0x%08x\n"
                   ,*local_18,local_18[1],local_18[2],local_18[3],local_18[4],local_18[7],
                   local_18[5],local_18[6]);
    }
  }
  return iVar1;
}



/* === FUN_10b89ddc @ 10b89ddc (size=192) === */
/* Called by 4 BCM APIs */

undefined4 FUN_10b89ddc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_11312da0(*(undefined4 *)(&DAT_11f08c64 + param_1 * 4),0xffffffff);
  uVar1 = FUN_10ef6b88(param_1,*(undefined4 *)(&DAT_11f07e5c + param_1 * 0xcc),param_2,param_3,
                       param_4);
  FUN_11312efc(*(undefined4 *)(&DAT_11f08c64 + param_1 * 4));
  return uVar1;
}



/* === FUN_112b0ae8 @ 112b0ae8 (size=60) === */
/* Called by 4 BCM APIs */

undefined4 FUN_112b0ae8(int param_1)

{
  return *(undefined4 *)(&DAT_11f1bd50 + param_1 * 4);
}



/* === FUN_1083aa9c @ 1083aa9c (size=608) === */
/* Called by 3 BCM APIs */

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



/* === FUN_10632870 @ 10632870 (size=1232) === */
/* Called by 3 BCM APIs */

int FUN_10632870(int param_1,int param_2,undefined4 param_3,undefined4 param_4,uint param_5,
                undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  uint local_24;
  
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c20) & 1) == 0) {
    iVar1 = -0x10;
  }
  else if ((param_2 == -1) ||
          (((-1 < param_2 && (param_2 < 0x82)) &&
           (*(int *)((&DAT_1212d2dc)[param_1] + (param_2 + 0x1c84) * 4 + 4) != 0)))) {
    if ((param_5 & 0xff) == 0) {
      iVar1 = -4;
    }
    else {
      if (param_2 == -1) {
        for (local_24 = *(uint *)((&DAT_1212d2dc)[param_1] + 0x5154);
            (-1 < (int)local_24 && ((int)local_24 <= *(int *)((&DAT_1212d2dc)[param_1] + 0x5158)));
            local_24 = local_24 + 1) {
          iVar1 = (int)local_24 >> 5;
          if (((((*(uint *)((&DAT_1212d2dc)[param_1] +
                            (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0) + 0x1454) *
                            4 + 0xc) &
                 1 << (local_24 +
                       (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0)) * -0x20 & 0x3f)
                 ) != 0) &&
               (((*(uint *)((&DAT_1212d2dc)[param_1] +
                            (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0) + 0x1654) *
                            4 + 8) &
                 1 << (local_24 +
                       (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0)) * -0x20 & 0x3f)
                 ) == 0 && (-1 < (int)local_24)))) && ((int)local_24 < 0x82)) &&
             ((*(int *)((&DAT_1212d2dc)[param_1] + (local_24 + 0x1c84) * 4 + 4) != 0 &&
              (iVar1 = FUN_106311f4(param_1,local_24,param_3), iVar1 < 0)))) {
            return iVar1;
          }
        }
        for (local_24 = *(uint *)((&DAT_1212d2dc)[param_1] + 0x5154);
            (-1 < (int)local_24 && ((int)local_24 <= *(int *)((&DAT_1212d2dc)[param_1] + 0x5158)));
            local_24 = local_24 + 1) {
          iVar1 = (int)local_24 >> 5;
          if (((*(uint *)((&DAT_1212d2dc)[param_1] +
                          (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0) + 0x1454) * 4
                         + 0xc) &
               1 << (local_24 +
                     (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0)) * -0x20 & 0x3f))
               != 0) &&
             (((((*(uint *)((&DAT_1212d2dc)[param_1] +
                            (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0) + 0x1654) *
                            4 + 8) &
                 1 << (local_24 +
                       (iVar1 + (uint)((int)local_24 < 0 && (local_24 & 0x1f) != 0)) * -0x20 & 0x3f)
                 ) == 0 && (-1 < (int)local_24)) && ((int)local_24 < 0x82)) &&
              ((*(int *)((&DAT_1212d2dc)[param_1] + (local_24 + 0x1c84) * 4 + 4) != 0 &&
               (iVar1 = FUN_10631808(param_1,local_24,param_3,param_4,param_5,param_6,param_7),
               iVar1 < 0)))))) {
            return iVar1;
          }
        }
      }
      else {
        iVar1 = FUN_106311f4(param_1,param_2,param_3);
        if (iVar1 < 0) {
          return iVar1;
        }
        iVar1 = FUN_10631808(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
        if (iVar1 < 0) {
          return iVar1;
        }
      }
      iVar1 = 0;
    }
  }
  else {
    iVar1 = -0x12;
  }
  return iVar1;
}



/* === FUN_1038b404 @ 1038b404 (size=80) === */
/* Called by 3 BCM APIs */

undefined4 FUN_1038b404(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1038a6e0(param_1,param_2,1,2);
  return uVar1;
}



/* === FUN_1083e8a8 @ 1083e8a8 (size=508) === */
/* Called by 3 BCM APIs */

int FUN_1083e8a8(int param_1,int param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int local_78;
  uint local_6c;
  uint local_68;
  uint local_44;
  uint local_40;
  
  if (param_3 == (uint *)0x0) {
    local_78 = -4;
  }
  else {
    FUN_10761a94(0x50000,"entered soc_phyctrl_ability_local_get: unit %d, port %d\n",param_1,param_2
                );
    iVar1 = *(int *)(*(int *)(&DAT_12136d94 + param_1 * 4) + param_2 * 4);
    iVar2 = *(int *)(*(int *)(&DAT_12136ddc + param_1 * 4) + param_2 * 4);
    if ((iVar1 == 0) && (iVar2 == 0)) {
      local_78 = -0x11;
    }
    else {
      local_44 = 0xbfffffff;
      local_6c = 0xbfffffff;
      local_40 = 0xbfffffff;
      local_68 = 0xbfffffff;
      local_78 = 0;
      if (iVar2 != 0) {
        local_78 = FUN_1083e764(param_1,param_2,*(undefined4 *)(iVar2 + 0xfc),param_3);
        local_68 = param_3[1];
        local_6c = *param_3;
      }
      if ((-1 < local_78) && (iVar1 != 0)) {
        param_3[1] = 0;
        *param_3 = param_3[1];
        local_78 = FUN_1083e764(param_1,param_2,*(undefined4 *)(iVar1 + 0xfc),param_3);
        local_40 = param_3[1];
        local_44 = *param_3;
      }
      if (-1 < local_78) {
        *param_3 = local_6c & local_44;
        param_3[1] = local_68 & local_40;
      }
    }
  }
  return local_78;
}



/* === FUN_1053b0e0 @ 1053b0e0 (size=504) === */
/* Called by 3 BCM APIs */

int FUN_1053b0e0(int param_1,uint param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = (&DAT_1212d324)[param_1];
  iVar2 = (int)param_2 >> 5;
  if ((*(uint *)(iVar1 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0) + 0x3f0e0) * 4)
      & 1 << (param_2 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20 & 0x3f))
      == 0) {
    iVar3 = FUN_10534758(param_1,param_2);
    if (-1 < iVar3) {
      if ((*(uint *)(iVar1 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0) + 0x3f108) *
                             4) &
          1 << (param_2 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20 & 0x3f
               )) == 0) {
        *param_3 = (*(uint *)(iVar1 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0) +
                                      0x3f0d0) * 4) &
                   1 << (param_2 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) *
                                   -0x20 & 0x3f)) == 0 ^ 1;
      }
      else {
        *param_3 = 2;
      }
      iVar3 = 0;
    }
  }
  else {
    *param_3 = (*(uint *)(iVar1 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0) +
                                  0x3f0e8) * 4) &
               1 << (param_2 + (iVar2 + (uint)((int)param_2 < 0 && (param_2 & 0x1f) != 0)) * -0x20 &
                    0x3f)) == 0 ^ 1;
    iVar3 = 0;
  }
  return iVar3;
}



/* === FUN_10ca4c64 @ 10ca4c64 (size=372) === */
/* Called by 3 BCM APIs */

int FUN_10ca4c64(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_84 [8];
  undefined1 auStack_7c [64];
  undefined1 auStack_3c [28];
  undefined1 *local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  undefined4 *local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  iVar1 = FUN_107a2bf8(param_1,0x8f1,param_3);
  if (iVar1 == 0) {
    iVar1 = -0x10;
  }
  else {
    if ((int)local_14 >> 0x1a == 0x12) {
      uVar3 = local_14 & 0xffffff;
    }
    else {
      uVar3 = 0xffffffff;
    }
    iVar1 = FUN_10bf748c(local_18,uVar3,3);
    if (iVar1 == 0) {
      iVar1 = -0xd;
    }
    else {
      iVar1 = FUN_1080290c(local_18,0x10d6,0xffffffff,uVar3,auStack_84);
      if (-1 < iVar1) {
        uVar2 = FUN_107a36e4(local_18,0x10d6,auStack_84,0x7a5d);
        local_20 = auStack_7c;
        local_1c = auStack_3c;
        iVar1 = FUN_10b89ddc(local_18,uVar2,1,&local_20);
        if (-1 < iVar1) {
          uVar2 = FUN_107a36e4(local_18,0x8f1,auStack_7c,local_10);
          *local_c = uVar2;
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}



/* === FUN_1053b4ac @ 1053b4ac (size=1460) === */
/* Called by 3 BCM APIs */

undefined4 FUN_1053b4ac(int param_1,undefined4 param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int local_78;
  uint local_6c [4];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_48;
  undefined4 local_44;
  uint local_40;
  int local_3c;
  int local_38;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar2 = (&DAT_1212d324)[param_1];
  iVar3 = *(int *)(&DAT_1211e45c + param_1 * 4);
  if (*(int *)(&DAT_1211e45c + param_1 * 4) == 0) {
    uVar4 = 0xffffffef;
  }
  else if (((((int)param_3 < 0) || (0x81 < (int)param_3)) ||
           (*(int *)((&DAT_1212d2dc)[param_1] + (param_3 + 0x1c84) * 4 + 4) == 0)) ||
          (local_48 = param_1, local_44 = param_2, local_40 = param_3, local_3c = param_4,
          local_38 = param_5,
          iVar1 = bcm_mirror_ingress_get((&DAT_1212d2dc)[param_1] + (param_3 + 0x1c84) * 4 + 4,0x66)
          , iVar1 == 0)) {
    uVar4 = 0xffffffee;
  }
  else {
    FUN_11312da0(*(undefined4 *)(*(int *)(&DAT_1211e45c + local_48 * 4) + 0x10),0xffffffff);
    iVar1 = (int)local_40 >> 5;
    if (local_3c == 0) {
      iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
      *(uint *)(iVar2 + (iVar5 + 0x3f0e0) * 4) =
           *(uint *)(iVar2 + (iVar5 + 0x3f0e0) * 4) &
           ~(1 << (local_40 + (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20
                  & 0x3f));
      iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
      *(uint *)(iVar2 + (iVar5 + 0x3f0e8) * 4) =
           *(uint *)(iVar2 + (iVar5 + 0x3f0e8) * 4) &
           ~(1 << (local_40 + (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20
                  & 0x3f));
      iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
      *(uint *)(iVar2 + (iVar5 + 0x3f0d8) * 4) =
           *(uint *)(iVar2 + (iVar5 + 0x3f0d8) * 4) |
           1 << (local_40 + (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20 &
                0x3f);
    }
    else {
      iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
      *(uint *)(iVar2 + (iVar5 + 0x3f0e8) * 4) =
           *(uint *)(iVar2 + (iVar5 + 0x3f0e8) * 4) &
           ~(1 << (local_40 + (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20
                  & 0x3f));
      if (local_38 != 0) {
        if (*(int *)(iVar3 + 0xd8) != 0) {
          iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
          *(uint *)(iVar2 + (iVar5 + 0x3f0d0) * 4) =
               *(uint *)(iVar2 + (iVar5 + 0x3f0d0) * 4) |
               1 << (local_40 +
                     (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20 & 0x3f);
          iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
          *(uint *)(iVar2 + (iVar5 + 0x3f0d8) * 4) =
               *(uint *)(iVar2 + (iVar5 + 0x3f0d8) * 4) &
               ~(1 << (local_40 +
                       (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20 & 0x3f)
                );
        }
        iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
        *(uint *)(iVar2 + (iVar5 + 0x3f0e8) * 4) =
             *(uint *)(iVar2 + (iVar5 + 0x3f0e8) * 4) |
             1 << (local_40 + (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20
                  & 0x3f);
      }
      iVar5 = iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
      *(uint *)(iVar2 + (iVar5 + 0x3f0e0) * 4) =
           *(uint *)(iVar2 + (iVar5 + 0x3f0e0) * 4) |
           1 << (local_40 + (iVar1 + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20 &
                0x3f);
    }
    for (local_78 = 0; local_78 < 8; local_78 = local_78 + 1) {
      local_6c[local_78] = 0;
    }
    iVar2 = ((int)local_40 >> 5) + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0);
    local_6c[iVar2] =
         local_6c[iVar2] |
         1 << (local_40 +
               (((int)local_40 >> 5) + (uint)((int)local_40 < 0 && (local_40 & 0x1f) != 0)) * -0x20
              & 0x3f);
    local_30 = local_6c[0];
    local_2c = local_6c[1];
    local_28 = local_6c[2];
    local_24 = local_6c[3];
    local_20 = local_5c;
    local_1c = local_58;
    local_18 = local_54;
    local_14 = local_50;
    FUN_1053a904(local_48,local_44,&local_30);
    FUN_11312efc(*(undefined4 *)(*(int *)(&DAT_1211e45c + local_48 * 4) + 0x10));
    if (*(int *)(iVar3 + 0xe8) != 0) {
      FUN_103256c4(*(undefined4 *)(iVar3 + 0xe8));
    }
    uVar4 = 0;
  }
  return uVar4;
}



/* === FUN_103256c4 @ 103256c4 (size=92) === */
/* Called by 3 BCM APIs */

undefined4 FUN_103256c4(undefined4 param_1)

{
  undefined1 auStack_78 [4];
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_60;
  undefined4 local_18;
  
  local_70 = 4;
  local_60 = param_1;
  local_18 = param_1;
  FUN_10322de8(0x20004c0a,auStack_78);
  return local_74;
}



/* === FUN_1084bf98 @ 1084bf98 (size=1072) === */
/* Called by 3 BCM APIs */

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



/* === FUN_10e2fb84 @ 10e2fb84 (size=372) === */
/* Called by 3 BCM APIs */

int FUN_10e2fb84(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_84 [4];
  undefined1 auStack_80 [64];
  undefined1 auStack_40 [28];
  undefined1 *local_24;
  undefined1 *local_20;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  undefined4 *local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  iVar1 = FUN_107a2bf8(param_1,0x8f1,param_3);
  if (iVar1 == 0) {
    iVar1 = -0x10;
  }
  else {
    if ((int)local_14 >> 0x1a == 0x12) {
      uVar3 = local_14 & 0xffffff;
    }
    else {
      uVar3 = 0xffffffff;
    }
    iVar1 = FUN_10bf748c(local_18,uVar3,3);
    if (iVar1 == 0) {
      iVar1 = -0xd;
    }
    else {
      iVar1 = FUN_1080290c(local_18,0xf46,0xffffffff,uVar3,auStack_84);
      if (-1 < iVar1) {
        uVar2 = FUN_107a36e4(local_18,0xf46,auStack_84,0x7a5e);
        local_24 = auStack_80;
        local_20 = auStack_40;
        iVar1 = FUN_10b89ddc(local_18,uVar2,1,&local_24);
        if (-1 < iVar1) {
          uVar2 = FUN_107a36e4(local_18,0x8f1,auStack_80,local_10);
          *local_c = uVar2;
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}



/* === FUN_1083b338 @ 1083b338 (size=220) === */
/* Called by 3 BCM APIs */

int FUN_1083b338(undefined4 param_1,undefined4 param_2,undefined4 param_3)

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
  FUN_10761a94(0x50000,"entered soc_phyctrl_auto_negotiate_set: unit %d, port %d, an %d\n",param_1,
               param_2,param_3);
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x30) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x30))(local_18,local_14,local_10);
    }
  }
  return local_28;
}



/* === bcm_port_speed_max @ 105c3dbc (size=2632) === */
/* Called by 3 BCM APIs */

int bcm_port_speed_max(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int local_78;
  uint local_6c;
  uint local_68;
  uint local_44;
  uint local_40;
  int local_18;
  uint local_14;
  int *local_10;
  
  if (param_3 == (int *)0x0) {
    local_78 = -4;
  }
  else if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_78 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_78 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < local_78) {
      local_78 = bcm_port_ability_get(local_18,local_14,&local_6c);
      if (local_78 < 0) {
        *local_10 = 0;
      }
      else {
        if (((local_68 | local_6c) & 0x10000000) == 0) {
          if (((local_68 | local_6c) & 0x8000000) == 0) {
            if (((local_68 | local_6c) & 0x20000000) == 0) {
              if (((local_68 | local_6c) & 0x4000000) == 0) {
                if (((local_68 | local_6c) & 0x2000000) == 0) {
                  if (((local_68 | local_6c) & 0x1000000) == 0) {
                    if ((int)(local_68 | local_6c) < 0) {
                      iVar1 = 32000;
                    }
                    else if (((local_68 | local_6c) & 0x800000) == 0) {
                      if (((local_68 | local_6c) & 0x400000) == 0) {
                        if (((local_68 | local_6c) & 0x200000) == 0) {
                          if (((local_68 | local_6c) & 0x100000) == 0) {
                            if (((local_68 | local_6c) & 0x80000) == 0) {
                              if (((local_68 | local_6c) & 0x40000) == 0) {
                                if (((local_68 | local_6c) & 0x20000) == 0) {
                                  if (((local_68 | local_6c) & 0x10000) == 0) {
                                    if (((local_68 | local_6c) & 0x8000) == 0) {
                                      if (((local_68 | local_6c) & 0x4000) == 0) {
                                        if (((local_68 | local_6c) & 0x2000) == 0) {
                                          if (((local_68 | local_6c) & 0x1000) == 0) {
                                            if (((local_68 | local_6c) & 0x800) == 0) {
                                              if (((local_68 | local_6c) & 0x400) == 0) {
                                                if (((local_68 | local_6c) & 0x200) == 0) {
                                                  if (((local_68 | local_6c) & 0x100) == 0) {
                                                    if (((local_68 | local_6c) & 0x80) == 0) {
                                                      if (((local_68 | local_6c) & 0x40) == 0) {
                                                        if (((local_68 | local_6c) & 0x20) == 0) {
                                                          if (((local_68 | local_6c) & 0x10) == 0) {
                                                            if (((local_68 | local_6c) & 8) == 0) {
                                                              if (((local_68 | local_6c) & 4) == 0)
                                                              {
                                                                if (((local_68 | local_6c) & 2) == 0
                                                                   ) {
                                                                  if (((local_68 | local_6c) & 1) ==
                                                                      0) {
                                                                    iVar1 = 0;
                                                                  }
                                                                  else {
                                                                    iVar1 = 10;
                                                                  }
                                                                }
                                                                else {
                                                                  iVar1 = 0x14;
                                                                }
                                                              }
                                                              else {
                                                                iVar1 = 0x19;
                                                              }
                                                            }
                                                            else {
                                                              iVar1 = 0x21;
                                                            }
                                                          }
                                                          else {
                                                            iVar1 = 0x32;
                                                          }
                                                        }
                                                        else {
                                                          iVar1 = 100;
                                                        }
                                                      }
                                                      else {
                                                        iVar1 = 1000;
                                                      }
                                                    }
                                                    else {
                                                      iVar1 = 0x9c4;
                                                    }
                                                  }
                                                  else {
                                                    iVar1 = 3000;
                                                  }
                                                }
                                                else {
                                                  iVar1 = 5000;
                                                }
                                              }
                                              else {
                                                iVar1 = 6000;
                                              }
                                            }
                                            else {
                                              iVar1 = 10000;
                                            }
                                          }
                                          else {
                                            iVar1 = 11000;
                                          }
                                        }
                                        else {
                                          iVar1 = 12000;
                                        }
                                      }
                                      else {
                                        iVar1 = 0x30d4;
                                      }
                                    }
                                    else {
                                      iVar1 = 13000;
                                    }
                                  }
                                  else {
                                    iVar1 = 15000;
                                  }
                                }
                                else {
                                  iVar1 = 16000;
                                }
                              }
                              else {
                                iVar1 = 20000;
                              }
                            }
                            else {
                              iVar1 = 21000;
                            }
                          }
                          else {
                            iVar1 = 23000;
                          }
                        }
                        else {
                          iVar1 = 24000;
                        }
                      }
                      else {
                        iVar1 = 25000;
                      }
                    }
                    else {
                      iVar1 = 30000;
                    }
                  }
                  else {
                    iVar1 = 40000;
                  }
                }
                else {
                  iVar1 = 42000;
                }
              }
              else {
                iVar1 = 100000;
              }
            }
            else {
              iVar1 = 0x19e10;
            }
          }
          else {
            iVar1 = 120000;
          }
        }
        else {
          iVar1 = 0x1f018;
        }
        *local_10 = iVar1;
        if (((*local_10 == 10000) &&
            ((*(uint *)((&DAT_1212d2dc)[local_18] +
                        (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)
                        + 0x49c) * 4 + 0x10) &
             1 << (local_14 +
                   (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) *
                   -0x20 & 0x3f)) != 0)) &&
           (*(int *)((&DAT_1212d2dc)[local_18] + (local_14 + 0x1894) * 4 + 4) != 0)) {
          *local_10 = *(int *)((&DAT_1212d2dc)[local_18] + (local_14 + 0x1894) * 4 + 4);
          local_78 = FUN_1083e8a8(local_18,local_14,&local_44);
          if (local_78 < 0) {
            *local_10 = 0;
          }
          else {
            if (((local_40 | local_44) & 0x10000000) == 0) {
              if (((local_40 | local_44) & 0x8000000) == 0) {
                if (((local_40 | local_44) & 0x20000000) == 0) {
                  if (((local_40 | local_44) & 0x4000000) == 0) {
                    if (((local_40 | local_44) & 0x2000000) == 0) {
                      if (((local_40 | local_44) & 0x1000000) == 0) {
                        if ((int)(local_40 | local_44) < 0) {
                          iVar1 = 32000;
                        }
                        else if (((local_40 | local_44) & 0x800000) == 0) {
                          if (((local_40 | local_44) & 0x400000) == 0) {
                            if (((local_40 | local_44) & 0x200000) == 0) {
                              if (((local_40 | local_44) & 0x100000) == 0) {
                                if (((local_40 | local_44) & 0x80000) == 0) {
                                  if (((local_40 | local_44) & 0x40000) == 0) {
                                    if (((local_40 | local_44) & 0x20000) == 0) {
                                      if (((local_40 | local_44) & 0x10000) == 0) {
                                        if (((local_40 | local_44) & 0x8000) == 0) {
                                          if (((local_40 | local_44) & 0x4000) == 0) {
                                            if (((local_40 | local_44) & 0x2000) == 0) {
                                              if (((local_40 | local_44) & 0x1000) == 0) {
                                                if (((local_40 | local_44) & 0x800) == 0) {
                                                  if (((local_40 | local_44) & 0x400) == 0) {
                                                    if (((local_40 | local_44) & 0x200) == 0) {
                                                      if (((local_40 | local_44) & 0x100) == 0) {
                                                        if (((local_40 | local_44) & 0x80) == 0) {
                                                          if (((local_40 | local_44) & 0x40) == 0) {
                                                            if (((local_40 | local_44) & 0x20) == 0)
                                                            {
                                                              if (((local_40 | local_44) & 0x10) ==
                                                                  0) {
                                                                if (((local_40 | local_44) & 8) == 0
                                                                   ) {
                                                                  if (((local_40 | local_44) & 4) ==
                                                                      0) {
                                                                    if (((local_40 | local_44) & 2)
                                                                        == 0) {
                                                                      if (((local_40 | local_44) & 1
                                                                          ) == 0) {
                                                                        iVar1 = 0;
                                                                      }
                                                                      else {
                                                                        iVar1 = 10;
                                                                      }
                                                                    }
                                                                    else {
                                                                      iVar1 = 0x14;
                                                                    }
                                                                  }
                                                                  else {
                                                                    iVar1 = 0x19;
                                                                  }
                                                                }
                                                                else {
                                                                  iVar1 = 0x21;
                                                                }
                                                              }
                                                              else {
                                                                iVar1 = 0x32;
                                                              }
                                                            }
                                                            else {
                                                              iVar1 = 100;
                                                            }
                                                          }
                                                          else {
                                                            iVar1 = 1000;
                                                          }
                                                        }
                                                        else {
                                                          iVar1 = 0x9c4;
                                                        }
                                                      }
                                                      else {
                                                        iVar1 = 3000;
                                                      }
                                                    }
                                                    else {
                                                      iVar1 = 5000;
                                                    }
                                                  }
                                                  else {
                                                    iVar1 = 6000;
                                                  }
                                                }
                                                else {
                                                  iVar1 = 10000;
                                                }
                                              }
                                              else {
                                                iVar1 = 11000;
                                              }
                                            }
                                            else {
                                              iVar1 = 12000;
                                            }
                                          }
                                          else {
                                            iVar1 = 0x30d4;
                                          }
                                        }
                                        else {
                                          iVar1 = 13000;
                                        }
                                      }
                                      else {
                                        iVar1 = 15000;
                                      }
                                    }
                                    else {
                                      iVar1 = 16000;
                                    }
                                  }
                                  else {
                                    iVar1 = 20000;
                                  }
                                }
                                else {
                                  iVar1 = 21000;
                                }
                              }
                              else {
                                iVar1 = 23000;
                              }
                            }
                            else {
                              iVar1 = 24000;
                            }
                          }
                          else {
                            iVar1 = 25000;
                          }
                        }
                        else {
                          iVar1 = 30000;
                        }
                      }
                      else {
                        iVar1 = 40000;
                      }
                    }
                    else {
                      iVar1 = 42000;
                    }
                  }
                  else {
                    iVar1 = 100000;
                  }
                }
                else {
                  iVar1 = 0x19e10;
                }
              }
              else {
                iVar1 = 120000;
              }
            }
            else {
              iVar1 = 0x1f018;
            }
            iVar2 = *local_10;
            if (iVar1 < *local_10) {
              iVar2 = iVar1;
            }
            *local_10 = iVar2;
          }
        }
      }
      FUN_10761a94(0x800,"bcm_port_speed_max: u=%d p=%d speed=%d rv=%d\n",local_18,local_14,
                   *local_10,local_78);
    }
  }
  return local_78;
}



/* === FUN_10e2fcf8 @ 10e2fcf8 (size=172) === */
/* Called by 2 BCM APIs */

undefined4 FUN_10e2fcf8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_11312da0(*(undefined4 *)(&DAT_11f18088 + param_1 * 4),0xffffffff);
  uVar1 = FUN_10e2f92c(param_1,param_2,param_3,param_4);
  FUN_11312efc(*(undefined4 *)(&DAT_11f18088 + param_1 * 4));
  return uVar1;
}



/* === FUN_1083c690 @ 1083c690 (size=216) === */
/* Called by 2 BCM APIs */

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



/* === FUN_1053f450 @ 1053f450 (size=688) === */
/* Called by 2 BCM APIs */

int FUN_1053f450(int param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  uint local_14;
  undefined4 *local_10;
  
  iVar1 = *(int *)(&DAT_1211e45c + param_1 * 4);
  if (*(int *)(&DAT_1211e45c + param_1 * 4) == 0) {
    iVar2 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    if (((param_2 >> 0x1a == 0) || (0x29 < param_2 >> 0x1a)) ||
       (iVar2 = FUN_10619410(param_1,param_2,&local_14), -1 < iVar2)) {
      if ((((int)local_14 < 0) || (0x81 < (int)local_14)) ||
         ((*(int *)((&DAT_1212d2dc)[param_1] + (local_14 + 0x1c84) * 4 + 4) == 0 ||
          (iVar2 = bcm_mirror_ingress_get
                             ((&DAT_1212d2dc)[param_1] + (local_14 + 0x1c84) * 4 + 4,0x66),
          iVar2 == 0)))) {
        iVar2 = -0x12;
      }
      else {
        iVar2 = (int)local_14 >> 5;
        if ((*(uint *)((&DAT_1212d2dc)[param_1] +
                       (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x1328) * 4 +
                      0x14) &
            1 << (local_14 + (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 &
                 0x3f)) == 0) {
          iVar2 = -0x12;
        }
        else if (local_10 == (undefined4 *)0x0) {
          iVar2 = -4;
        }
        else {
          if ((*(uint *)(iVar1 + (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 4) *
                                 4 + 4) &
              1 << (local_14 + (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20
                   & 0x3f)) == 0) {
            if ((*(uint *)(iVar1 + (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) +
                                   0xc) * 4 + 4) &
                1 << (local_14 +
                      (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 & 0x3f))
                == 0) {
              *local_10 = 0;
            }
            else {
              *local_10 = 1;
            }
          }
          else {
            *local_10 = 2;
          }
          iVar2 = 0;
        }
      }
    }
  }
  return iVar2;
}



/* === FUN_1084c8b4 @ 1084c8b4 (size=1152) === */
/* Called by 2 BCM APIs */

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



/* === FUN_108158a4 @ 108158a4 (size=1820) === */
/* Called by 2 BCM APIs */

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



/* === FUN_1083d4dc @ 1083d4dc (size=232) === */
/* Called by 2 BCM APIs */

int FUN_1083d4dc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_24[0] = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_10761a94(0x50000,"entered soc_phyctrl_control_set: unit %d, port %d, phy_ctrl %d, value %u\n",
               param_1,param_2,param_3,param_4);
  local_28 = FUN_1083a030(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x80) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x80))(local_18,local_14,local_10,local_c);
    }
  }
  return local_28;
}



/* === FUN_10880ed8 @ 10880ed8 (size=88) === */
/* Called by 2 BCM APIs */

void FUN_10880ed8(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 8) = param_3;
  *(undefined4 *)(param_1 + 4) = param_2;
  *(undefined4 *)(param_1 + 0xc) = 1;
  *(undefined4 *)(param_1 + 0x10) = 1;
  return;
}



/* === FUN_1084bccc @ 1084bccc (size=716) === */
/* Called by 2 BCM APIs */

bool FUN_1084bccc(int param_1,int param_2,int param_3)

{
  uint uVar1;
  bool bVar2;
  int *local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  
  if (((param_2 < 0) || (0x901f < param_2)) ||
     (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
  {
    bVar2 = false;
  }
  else {
    local_28 = (int *)0x0;
    local_24 = *(int **)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                 param_2 * 4) + 0x18);
    local_1c = local_24;
    if ((*local_24 != param_3) &&
       (local_1c = local_24 +
                   (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18)
                                     + param_2 * 4) + 0x14) + -1) * 3, *local_1c != param_3)) {
      uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                                param_2 * 4) + 0x14);
      local_20 = local_24 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
      while (((local_24 < local_1c && (local_20 < local_1c)) &&
             ((*local_24 != param_3 && (*local_20 != param_3))))) {
        if (param_3 < *local_20) {
          local_1c = local_20 + -3;
        }
        else {
          if (param_3 <= *local_20) break;
          local_24 = local_20 + 3;
        }
        uVar1 = ((int)local_1c - (int)local_24 >> 2) * -0x55555555 + 1;
        local_20 = local_24 + (((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0)) * 3;
      }
      if (*local_20 == param_3) {
        local_28 = local_20;
        local_1c = local_28;
      }
      else {
        local_1c = local_28;
        if (*local_24 == param_3) {
          local_28 = local_24;
          local_1c = local_28;
        }
      }
    }
    local_28 = local_1c;
    bVar2 = local_28 != (int *)0x0;
  }
  return bVar2;
}



/* === FUN_1083aec4 @ 1083aec4 (size=216) === */
/* Called by 2 BCM APIs */

int FUN_1083aec4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

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
  FUN_10761a94(0x50000,"entered soc_phyctrl_duplex_get: unit %d, port %d\n",param_1,param_2);
  local_28 = FUN_10839f58(local_18,local_14,local_24);
  if (-1 < local_28) {
    if (local_24[0] == 0) {
      local_28 = -4;
    }
    else if (*(int *)(local_24[0] + 0x1c) == 0) {
      local_28 = -0x10;
    }
    else {
      local_28 = (**(code **)(local_24[0] + 0x1c))(local_18,local_14,local_10);
    }
  }
  return local_28;
}



/* === bcm_port_link_status_get @ 105cfe1c (size=160) === */
/* Called by 2 BCM APIs */

int bcm_port_link_status_get(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_105cfcb4(param_1,param_2,param_3);
  if ((-1 < iVar1) && (iVar1 = FUN_1053b0e0(param_1,param_2,param_3), iVar1 != -0xc)) {
    iVar1 = FUN_1053b2d8(param_1,param_2,param_3);
  }
  return iVar1;
}



/* === FUN_1083acfc @ 1083acfc (size=236) === */
/* Called by 2 BCM APIs */

int FUN_1083acfc(undefined4 param_1,undefined4 param_2,int param_3)

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
    FUN_10761a94(0x50000,"entered soc_phyctrl_enable_get: unit %d, port %d\n",param_1,param_2);
    iVar1 = FUN_1083a030(local_18,local_14,local_24);
    if (-1 < iVar1) {
      if (local_24[0] == 0) {
        iVar1 = -4;
      }
      else if (*(int *)(local_24[0] + 0x14) == 0) {
        iVar1 = -0x10;
      }
      else {
        iVar1 = (**(code **)(local_24[0] + 0x14))(local_18,local_14,local_10);
      }
    }
  }
  return iVar1;
}



/* === FUN_1083e2f4 @ 1083e2f4 (size=384) === */
/* Called by 2 BCM APIs */

int FUN_1083e2f4(undefined4 param_1,undefined4 param_2,void *param_3)

{
  int local_28;
  int local_24;
  undefined4 local_20 [2];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  
  local_24 = 0;
  if (param_3 == (void *)0x0) {
    local_28 = -4;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    FUN_10761a94(0x50000,"entered soc_phyctrl_ability_advert_get: unit %d, port %d\n",param_1,
                 param_2);
    local_28 = FUN_1083a030(local_18,local_14,&local_24);
    if (-1 < local_28) {
      if (local_24 == 0) {
        local_28 = -4;
      }
      else if (*(int *)(local_24 + 0xa0) == 0) {
        local_28 = -0x10;
      }
      else {
        local_28 = (**(code **)(local_24 + 0xa0))(local_18,local_14,local_10);
      }
    }
    if (local_28 == -0x10) {
      if (local_24 == 0) {
        local_28 = -4;
      }
      else if (*(int *)(local_24 + 0x3c) == 0) {
        local_28 = -0x10;
      }
      else {
        local_28 = (**(code **)(local_24 + 0x3c))(local_18,local_14,local_20);
      }
      if (-1 < local_28) {
        memset(local_10,0,0x28);
        local_28 = FUN_1084264c(local_20[0],local_10);
      }
    }
  }
  return local_28;
}



/* === FUN_10325444 @ 10325444 (size=92) === */
/* Called by 2 BCM APIs */

void FUN_10325444(undefined4 param_1)

{
  undefined1 auStack_78 [8];
  undefined4 local_70;
  undefined4 local_18;
  
  if (-1 < DAT_11853c08) {
    local_70 = param_1;
    local_18 = param_1;
    FUN_10322de8(0x20004c0b,auStack_78);
  }
  return;
}



/* === FUN_1038b454 @ 1038b454 (size=80) === */
/* Called by 2 BCM APIs */

undefined4 FUN_1038b454(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1038a6e0(param_1,param_2,0,2);
  return uVar1;
}



/* === FUN_11312150 @ 11312150 (size=276) === */
/* Called by 2 BCM APIs */

uint * FUN_11312150(uint param_1)

{
  uint uVar1;
  size_t __size;
  uint *puVar2;
  
  uVar1 = param_1 + 3;
  __size = (uVar1 & 0xfffffffc) + 0xc;
  if (__size < param_1) {
    puVar2 = (uint *)0x0;
  }
  else {
    DAT_11f1dd1c = DAT_11f1dd1c + 1;
    puVar2 = malloc(__size);
    if (puVar2 == (uint *)0x0) {
      puVar2 = (uint *)0x0;
    }
    else {
      DAT_11f1dd18 = DAT_11f1dd18 + (uVar1 & 0xfffffffc);
      *puVar2 = uVar1 >> 2;
      puVar2[1] = 0xaaaaaaaa;
      puVar2[(uVar1 >> 2) + 2] = 0xbbbbbbbb;
      puVar2 = puVar2 + 2;
    }
  }
  return puVar2;
}



/* === FUN_10849218 @ 10849218 (size=312) === */
/* Called by 2 BCM APIs */

undefined4
FUN_10849218(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 param_5)

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
  iVar1 = FUN_10761b70(0x20000000);
  if (iVar1 != 0) {
    FUN_10844e8c(local_28,0x20,"write",local_24,local_20,local_1c,0,local_18);
  }
  FUN_10844bc8(local_28,local_24,local_20,local_1c,1,0,local_18);
  uVar2 = FUN_108623e4(local_28,&local_84,3,0,0);
  return uVar2;
}



/* === FUN_1083bc3c @ 1083bc3c (size=896) === */
/* Called by 2 BCM APIs */

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



