/* BCM SDK functions in category: port */
/* Decompiled from switchd binary */

/* === bcm_esw_port_vlan_member_get @ 105ce0f0 (size=1556) === */

int bcm_esw_port_vlan_member_get(int param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  int local_98;
  int local_8c;
  undefined1 auStack_88 [24];
  undefined4 local_70 [2];
  undefined4 local_68;
  undefined4 local_64;
  undefined1 auStack_60 [72];
  int local_18;
  uint local_14;
  uint *local_10;
  
  *param_3 = 0;
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_98 = -0x11;
  }
  else {
    iVar2 = (int)param_2 >> 0x1a;
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    if (((iVar2 == 0x11) || (iVar2 == 0x1c)) || (param_2 >> 0x1a == 0x23)) {
      local_98 = FUN_109e42d4(param_1,param_2,param_3);
    }
    else {
      if (iVar2 == 0x12) {
        local_98 = 0;
      }
      else {
        local_98 = FUN_105a6a18(param_1,param_2,&local_14);
      }
      if (-1 < local_98) {
        uVar1 = FUN_112b0ae8(local_18);
        if (uVar1 < 0x11) {
          if (uVar1 < 8) {
            if (uVar1 != 1) {
              return -0x10;
            }
            return 0;
          }
        }
        else if (uVar1 != 0x16) {
          return -0x10;
        }
        if ((int)local_14 >> 0x1a == 0x12) {
          if ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c34) & 0x40000) == 0) {
            local_98 = -0x12;
          }
          else {
            if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
               (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x80000) != 0 ||
                ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)))) {
              local_98 = FUN_10e2fb84(local_18,local_14,0x41a4,&local_8c);
            }
            else {
              local_98 = FUN_10ca4c64(local_18,local_14,0x41a4,&local_8c);
            }
            if (local_8c != 0) {
              *local_10 = *local_10 | 1;
            }
          }
        }
        else {
          local_98 = FUN_1080290c(local_18,0xde3,0xffffffff,local_14,auStack_60);
          if ((-1 < local_98) &&
             (iVar2 = FUN_107a36e4(local_18,0xde3,auStack_60,0x41a4), iVar2 != 0)) {
            *local_10 = *local_10 | 1;
          }
          if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x924) ==
               0) || ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                  0x924) & 2) == 0)) {
            if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
               (((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
                  ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
                 ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)) ||
                ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))) {
              if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) + 0xbd20)
                  == 0) {
                local_98 = FUN_108469c0(local_18,0x2f4a,local_14,0,&local_68);
              }
              else {
                local_98 = FUN_10847ab4(local_18,0x2f48,local_14,0,local_70);
              }
              if (-1 < local_98) {
                if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) +
                            0xbd20) == 0) {
                  iVar2 = FUN_1084c8b4(local_18,0x2f4a,local_68,local_64,0x419d);
                  if (iVar2 != 0) {
                    *local_10 = *local_10 | 2;
                  }
                }
                else {
                  iVar2 = FUN_1084bccc(local_18,0x2f48,0x419d);
                  if ((iVar2 != 0) &&
                     (iVar2 = FUN_1084bf98(local_18,0x2f48,local_70[0],0x419d), iVar2 != 0)) {
                    *local_10 = *local_10 | 2;
                  }
                }
              }
            }
          }
          else {
            local_98 = FUN_1080290c(local_18,0x249,0xffffffff,local_14,auStack_88);
            if ((-1 < local_98) &&
               (iVar2 = FUN_107a36e4(local_18,0x249,auStack_88,0x419d), iVar2 != 0)) {
              *local_10 = *local_10 | 2;
            }
          }
        }
      }
    }
  }
  return local_98;
}



/* === bcm_esw_port_vlan_member_set @ 105ce704 (size=4340) === */

int bcm_esw_port_vlan_member_set(int param_1,uint param_2,uint param_3)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_c8;
  uint local_c4;
  int local_c0;
  uint local_bc;
  int local_b8;
  undefined1 auStack_9c [24];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined1 auStack_78 [64];
  uint local_38 [8];
  int local_18;
  uint local_14;
  uint local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    return -0x11;
  }
  iVar3 = (int)param_2 >> 0x1a;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  if (((iVar3 == 0x11) || (iVar3 == 0x1c)) || (param_2 >> 0x1a == 0x23)) {
    iVar3 = FUN_109e36e0(param_1,param_2,param_3);
    return iVar3;
  }
  if (iVar3 == 0x12) {
    local_c8 = 0;
  }
  else {
    local_c8 = FUN_105a6a18(param_1,param_2,&local_14);
  }
  if (local_c8 < 0) {
    return local_c8;
  }
  local_c8 = -0x10;
  FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
  if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0) &&
      ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2)
       != 0)) &&
     ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2) !=
      0)) {
    FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
  }
  uVar2 = FUN_112b0ae8(local_18);
  if (uVar2 < 0x11) {
    if (uVar2 < 8) {
      if (uVar2 == 1) {
        if ((local_10 & 1) == 0) {
          if ((local_10 & 2) == 0) {
            local_c8 = 0;
          }
          else {
            local_c8 = -0x10;
          }
        }
        else {
          local_c8 = -0x10;
        }
      }
      goto LAB_105cf6e4;
    }
  }
  else if (uVar2 != 0x16) goto LAB_105cf6e4;
  if ((int)local_14 >> 0x1a == 0x12) {
    if ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c34) & 0x40000) == 0) {
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      return -0x12;
    }
    if ((local_10 & 1) == 0) {
      if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)))) {
        local_c8 = FUN_10e2fcf8(local_18,local_14,0x41a4,0);
      }
      else {
        local_c8 = FUN_10ca4dd8(local_18,local_14,0x41a4,0);
      }
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x80000) != 0 ||
             ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)))) {
      local_c8 = FUN_10e2fcf8(local_18,local_14,0x41a4,1);
    }
    else {
      local_c8 = FUN_10ca4dd8(local_18,local_14,0x41a4,1);
    }
    FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
    if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) == 0) {
      return local_c8;
    }
    if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2)
        == 0) {
      return local_c8;
    }
    if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2)
        == 0) {
      return local_c8;
    }
    FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
    return local_c8;
  }
  local_c8 = FUN_1080290c(local_18,0xde3,0xffffffff,local_14,auStack_78);
  if (-1 < local_c8) {
    FUN_107a37cc(local_18,0xde3,auStack_78,0x41a4,(local_10 & 1) != 0);
    local_c8 = FUN_10808e6c(local_18,0xde3,0xffffffff,local_14,auStack_78);
  }
  if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x1a10) == 0) ||
     ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x1a10) & 2) ==
      0)) {
    if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
       ((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
         ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
        (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0 ||
         ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))))) {
      if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
         ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x8000000) != 0)) {
        uVar5 = 0x2f4a;
      }
      else {
        uVar5 = 0x2f48;
      }
      local_c8 = FUN_108536e0(local_18,uVar5,local_14,0x419d,(local_10 & 2) != 0);
      if (-1 < local_c8) {
        if (((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x4202000) != 0)) &&
           (local_c8 = FUN_10847ab4(local_18,0x50cf,0xfffffff6,0,&local_84), -1 < local_c8)) {
          for (local_c0 = 0; local_c0 < 8; local_c0 = local_c0 + 1) {
            local_38[local_c0] = 0;
          }
          iVar3 = ((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0);
          local_38[iVar3] =
               local_38[iVar3] |
               1 << (local_14 +
                     (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) *
                     -0x20 & 0x3f);
          uVar2 = local_38[0];
          local_c4 = FUN_1084bf98(local_18,0x50cf,local_84,0xc9b);
          if ((local_10 & 2) == 0) {
            local_c4 = local_c4 & ~uVar2;
          }
          else {
            local_c4 = local_c4 | uVar2;
          }
          FUN_1084d57c(local_18,0x50cf,&local_84,0xc9b,local_c4);
          local_c8 = FUN_1084a784(local_18,0x50cf,0xfffffff6,0,local_84);
        }
        if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
           (((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7a4c044f) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
             (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))) &&
            (local_c8 = FUN_108469c0(local_18,0x50d0,0xfffffff6,0,&local_80), -1 < local_c8)))) {
          for (local_b8 = 0; local_b8 < 8; local_b8 = local_b8 + 1) {
            local_38[local_b8] = 0;
          }
          iVar3 = ((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0);
          local_38[iVar3] =
               local_38[iVar3] |
               1 << (local_14 +
                     (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) *
                     -0x20 & 0x3f);
          local_bc = FUN_1084c8b4(local_18,0x50d0,local_80,local_7c,0xca2);
          if (((local_10 & 2) == 0) ||
             (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38 + 0x14) != 0)) {
            local_bc = local_bc & ~local_38[0];
          }
          else {
            local_bc = local_bc | local_38[0];
          }
          FUN_1084ea88(local_18,0x50d0,&local_80,0xca2,local_bc);
          if (((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) != 0) ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 1) == 0)) &&
             ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) != 0 ||
              (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20000000) == 0 &&
               ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) == 0)))))) {
            local_bc = FUN_1084c8b4(local_18,0x50d0,local_80,local_7c,0xca1);
            if (((local_10 & 2) == 0) ||
               (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38 + 0x14) != 0)) {
              local_bc = local_bc & ~local_38[1];
            }
            else {
              local_bc = local_bc | local_38[1];
            }
            FUN_1084ea88(local_18,0x50d0,&local_80,0xca1,local_bc);
          }
          local_c8 = FUN_10849350(local_18,0x50d0,0xfffffff6,0,local_80,local_7c);
        }
      }
    }
  }
  else {
    bVar1 = (local_10 & 2) != 0;
    local_c8 = FUN_107a4778(local_18,0x249,local_14,0x419d,bVar1);
    if (-1 < local_c8) {
      local_c8 = FUN_1080290c(local_18,0x684,0xffffffff,0,auStack_9c);
    }
    if (-1 < local_c8) {
      FUN_107a6314(local_18,0x684,auStack_9c,0xc9b,local_38);
      iVar3 = (int)local_14 >> 5;
      if ((bVar1) &&
         (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38 + 0x14) == 0)) {
        iVar4 = iVar3 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0);
        local_38[iVar4] =
             local_38[iVar4] |
             1 << (local_14 + (iVar3 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20
                  & 0x3f);
      }
      else {
        iVar4 = iVar3 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0);
        local_38[iVar4] =
             local_38[iVar4] &
             ~(1 << (local_14 +
                     (iVar3 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 & 0x3f));
      }
      FUN_107a6268(local_18,0x684,auStack_9c,0xc9b,local_38);
      local_c8 = FUN_10808e6c(local_18,0x684,0xffffffff,0,auStack_9c);
    }
  }
LAB_105cf6e4:
  FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
  if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0) &&
      ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2)
       != 0)) &&
     ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2) !=
      0)) {
    FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
  }
  return local_c8;
}



/* === bcm_mim_port_add @ 104019ec (size=492) === */

undefined4 bcm_mim_port_add(int param_1,undefined2 param_2,int param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_3 != 0) {
      FUN_1038b364(param_1,param_3 + 0x48);
      FUN_1038b364(param_1,param_3);
      FUN_1038b364(param_1,param_3 + 0xc);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118581a0)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
    if (param_3 != 0) {
      FUN_1038b3b4(param_1,param_3 + 0x48);
      FUN_1038b3b4(param_1,param_3);
      FUN_1038b3b4(param_1,param_3 + 0xc);
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_port_add",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mim_port_delete @ 10401bd8 (size=332) === */

undefined4 bcm_mim_port_delete(int param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_10 [3];
  
  local_10[0] = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_10);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118581a8)[iVar1])(param_1,param_2,local_10[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_port_delete",3,3,param_1,param_2,local_10[0],local_28);
  }
  return local_28;
}



/* === bcm_mim_port_get_all @ 1040203c (size=608) === */

int bcm_mim_port_get_all(int param_1,undefined2 param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int local_38;
  int local_34;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = -3;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_118581c0)[iVar1])(param_1,param_2,param_3,param_4,param_5);
    FUN_112c5590(param_1,iVar1);
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 100 + 0x48);
        }
      }
    }
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 100);
        }
      }
    }
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 100 + 0xc);
        }
      }
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_port_get_all",5,3,param_1,param_2,param_3,local_38);
  }
  return local_38;
}



/* === bcm_mirror_port_dest_add @ 10403d88 (size=344) === */

undefined4
bcm_mirror_port_dest_add(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c [2];
  
  local_14 = param_2;
  local_10 = param_3;
  local_c[0] = param_4;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    FUN_1038b364(param_1,local_c);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858278)[iVar1])(param_1,local_14,local_10,local_c[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_port_dest_add",4,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



/* === bcm_mirror_port_dest_delete @ 10403ee0 (size=344) === */

undefined4
bcm_mirror_port_dest_delete(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c [2];
  
  local_14 = param_2;
  local_10 = param_3;
  local_c[0] = param_4;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    FUN_1038b364(param_1,local_c);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858280)[iVar1])(param_1,local_14,local_10,local_c[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_port_dest_delete",4,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



/* === bcm_mpls_port_add @ 10406ffc (size=620) === */

undefined4 bcm_mpls_port_add(int param_1,undefined2 param_2,int param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_3 != 0) {
      FUN_1038b364(param_1,param_3 + 0x60);
      FUN_1038b364(param_1,param_3);
      FUN_1038b364(param_1,param_3 + 0x80);
      FUN_1038b364(param_1,param_3 + 0x1c);
      FUN_1038b364(param_1,param_3 + 0x70);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118583a8)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
    if (param_3 != 0) {
      FUN_1038b3b4(param_1,param_3 + 0x60);
      FUN_1038b3b4(param_1,param_3);
      FUN_1038b3b4(param_1,param_3 + 0x80);
      FUN_1038b3b4(param_1,param_3 + 0x1c);
      FUN_1038b3b4(param_1,param_3 + 0x70);
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_port_add",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_port_delete @ 10407268 (size=332) === */

undefined4 bcm_mpls_port_delete(int param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_10 [3];
  
  local_10[0] = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_10);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118583b0)[iVar1])(param_1,param_2,local_10[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_port_delete",3,3,param_1,param_2,local_10[0],local_28);
  }
  return local_28;
}



/* === bcm_mpls_port_get_all @ 1040774c (size=800) === */

int bcm_mpls_port_get_all(int param_1,undefined2 param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int local_38;
  int local_34;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = -3;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_118583c8)[iVar1])(param_1,param_2,param_3,param_4,param_5);
    FUN_112c5590(param_1,iVar1);
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 0x88 + 0x60);
        }
      }
    }
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 0x88);
        }
      }
    }
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 0x88 + 0x80);
        }
      }
    }
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 0x88 + 0x1c);
        }
      }
    }
    if (-1 < local_38) {
      for (local_34 = 0; local_34 < param_3; local_34 = local_34 + 1) {
        if (param_4 != 0) {
          FUN_1038b3b4(param_1,param_4 + local_34 * 0x88 + 0x70);
        }
      }
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_port_get_all",5,3,param_1,param_2,param_3,local_38);
  }
  return local_38;
}



/* === bcm_port_ability_advert_get @ 105cad88 (size=724) === */

int bcm_port_ability_advert_get(int param_1,undefined4 param_2,void *param_3)

{
  int iVar1;
  undefined4 local_14;
  void *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      memset(local_10,0,0x28);
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083e2f4(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
      FUN_10761a94(0x800,"bcm_esw_port_ability_advert_get: u=%d p=%d rv=%d\n",param_1,local_14,iVar1
                  );
    }
  }
  return iVar1;
}



/* === bcm_port_ability_advert_set @ 105cb5c8 (size=976) === */

int bcm_port_ability_advert_set(int param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  int local_20;
  undefined4 local_1c;
  uint *local_18;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_20 = param_1;
    local_1c = param_2;
    local_18 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_1c);
    if ((-1 < iVar1) && (iVar1 = bcm_port_ability_get(local_20,local_1c,&local_54), -1 < iVar1)) {
      local_54 = local_54 & *local_18;
      local_50 = local_50 & local_18[1];
      local_4c = local_4c & local_18[2];
      local_48 = local_48 & local_18[3];
      local_44 = local_44 & local_18[4];
      local_38 = local_38 & local_18[7];
      local_40 = local_40 & local_18[5];
      local_3c = local_3c & local_18[6];
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_20 * 4),0xffffffff);
      if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_20] + 0x2f26f4) + 0x24) + 0x378c) != 0)
         && (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_20] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0 &&
             ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_20] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)))) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_20] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083e474(local_20,local_1c,&local_54);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_20 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_20] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_20] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_20] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_20] + 0x26e1a4));
      }
      FUN_10761a94(0x800,"bcm_port_ability_advert_set: u=%d p=%d rv=%d\n",local_20,local_1c,iVar1);
      FUN_10761a94(0x10800,
                   "Speed(HD=0x%08x, FD=0x%08x) Pause=0x%08x\nInterface=0x%08x Medium=0x%08x Loopback=0x%08x Flags=0x%08x\n"
                   ,local_54,local_50,local_4c,local_48,local_44,local_40,local_3c);
    }
  }
  return iVar1;
}



/* === bcm_port_ability_get @ 105cc324 (size=820) === */

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



/* === bcm_port_advert_set @ 105cb05c (size=1388) === */

int bcm_port_advert_set(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  int local_18;
  uint local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if ((((-1 < iVar1) && (iVar1 = bcm_port_ability_get(local_18,local_14,&local_4c), -1 < iVar1))
        && (iVar1 = bcm_port_ability_advert_get(local_18,local_14,&local_74), -1 < iVar1)) &&
       (iVar1 = FUN_1084264c(local_10,&local_74), -1 < iVar1)) {
      local_5c = local_5c & local_34;
      local_60 = local_60 & local_38;
      local_64 = local_64 & local_3c;
      local_58 = local_58 & local_30;
      local_6c = local_6c & local_44;
      local_70 = local_70 & local_48;
      local_74 = local_74 & local_4c;
      if (((*(uint *)((&DAT_1212d2dc)[local_18] +
                      (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) +
                      0x49c) * 4 + 0x10) &
           1 << (local_14 +
                 (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) *
                 -0x20 & 0x3f)) != 0) &&
         (*(int *)((&DAT_1212d2dc)[local_18] + (local_14 + 0x1894) * 4 + 4) != 0)) {
        if (*(int *)((&DAT_1212d2dc)[local_18] + (local_14 + 0x1894) * 4 + 4) < 16000) {
          local_70 = local_70 & 0xfffdffff;
          local_74 = local_74 & 0xfffdffff;
        }
        if (*(int *)((&DAT_1212d2dc)[local_18] + (local_14 + 0x1894) * 4 + 4) < 13000) {
          local_70 = local_70 & 0xffff7fff;
          local_74 = local_74 & 0xffff7fff;
        }
        if (*(int *)((&DAT_1212d2dc)[local_18] + (local_14 + 0x1894) * 4 + 4) < 12000) {
          local_70 = local_70 & 0xffffdfff;
          local_74 = local_74 & 0xffffdfff;
        }
        if ((local_70 & 0x2a800) == 0) {
          return -0xf;
        }
      }
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083e474(local_18,local_14,&local_74);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      FUN_10761a94(0x800,"bcm_port_advert_set: u=%d p=%d abil=0x%x rv=%d\n",local_18,local_14,
                   local_10,iVar1);
    }
  }
  return iVar1;
}



/* === bcm_port_autoneg_get @ 105c30c0 (size=928) === */

int bcm_port_autoneg_get(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int local_38;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 *local_10;
  
  local_28 = 0xffffffff;
  local_24 = 0;
  local_20 = 0;
  local_1c = -1;
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_38 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_38 = FUN_1062a874(param_1,param_2,&local_1c,&local_24,&local_28,&local_20);
    if ((-1 < local_38) &&
       ((local_1c != -1 || (local_38 = FUN_105a6a18(local_18,local_14,&local_14), -1 < local_38))))
    {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
         && (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0 &&
             ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)))) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      if (local_1c == -1) {
        local_38 = FUN_1083b550(local_18,local_14,local_10,&local_2c);
      }
      else {
        local_38 = FUN_1083b658(local_18,local_1c,local_24,local_28,local_20,local_10,&local_2c);
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      FUN_10761a94(0x800,"bcm_port_autoneg_get: u=%d p=%d an=%d done=%d rv=%d\n",local_18,local_14,
                   *local_10,local_2c,local_38);
    }
  }
  return local_38;
}



/* === bcm_port_autoneg_set @ 105c3460 (size=900) === */

int bcm_port_autoneg_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int local_38;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20 [2];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_2c = 0xffffffff;
  local_28 = 0;
  local_24 = 0;
  local_20[0] = -1;
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_38 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_38 = FUN_1062a874(param_1,param_2,local_20,&local_28,&local_2c,&local_24);
    if ((-1 < local_38) &&
       ((local_20[0] != -1 || (local_38 = FUN_105a6a18(local_18,local_14,&local_14), -1 < local_38))
       )) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
         && (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0 &&
             ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)))) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      if (local_20[0] == -1) {
        local_38 = FUN_1083b338(local_18,local_14,local_10);
      }
      else {
        local_38 = FUN_1083b414(local_18,local_20[0],local_28,local_2c,local_24,local_10);
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      FUN_10761a94(0x800,"bcm_port_autoneg_set: u=%d p=%d an=%d rv=%d\n",local_18,local_14,local_10,
                   local_38);
    }
  }
  return local_38;
}



/* === bcm_port_config_phy_oam_get @ 10414bec (size=312) === */

undefined4 bcm_port_config_phy_oam_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118588e8)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_config_phy_oam_get",3,2,param_1,local_14,0,local_28);
  }
  return local_28;
}



/* === bcm_port_config_phy_oam_set @ 10414d24 (size=312) === */

undefined4 bcm_port_config_phy_oam_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118588f0)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_config_phy_oam_set",3,2,param_1,local_14,0,local_28);
  }
  return local_28;
}



/* === bcm_port_control_phy_oam_get @ 10415600 (size=324) === */

undefined4
bcm_port_control_phy_oam_get(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858920)[iVar1])(param_1,local_14,local_10,local_c);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_control_phy_oam_get",4,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



/* === bcm_port_control_phy_oam_set @ 10415744 (size=332) === */

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



/* === bcm_port_control_phy_timesync_get @ 10415890 (size=324) === */

undefined4
bcm_port_control_phy_timesync_get
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858930)[iVar1])(param_1,local_14,local_10,local_c);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_control_phy_timesync_get",4,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



/* === bcm_port_control_phy_timesync_set @ 104159d4 (size=332) === */

undefined4
bcm_port_control_phy_timesync_set
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
    local_38 = (*(code *)(&PTR_FUN_11858938)[iVar1])(param_1,local_24,local_20);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_control_phy_timesync_set",4,3,param_1,local_24,local_20,local_38);
  }
  return local_38;
}



/* === bcm_port_discard_get @ 105cc658 (size=236) === */

int bcm_port_discard_get(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined1 auStack_e0 [16];
  undefined4 local_d0;
  int local_18;
  undefined4 local_14;
  undefined4 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if ((-1 < iVar1) &&
       (iVar1 = (**(code **)(*(int *)(&DAT_1211e4a4 + local_18 * 4) + 0x1c))
                          (local_18,local_14,auStack_e0), iVar1 == 0)) {
      *local_10 = local_d0;
    }
  }
  return iVar1;
}



/* === bcm_port_discard_set @ 105cc744 (size=820) === */

int bcm_port_discard_set(int param_1,undefined4 param_2,uint param_3)

{
  int local_e8;
  undefined1 auStack_e0 [16];
  uint local_d0;
  int local_18;
  undefined4 local_14;
  uint local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_e8 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_e8 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < local_e8) {
      if (local_10 < 4) {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
        }
        local_e8 = (**(code **)(*(int *)(&DAT_1211e4a4 + local_18 * 4) + 0x1c))
                             (local_18,local_14,auStack_e0);
        if (-1 < local_e8) {
          local_d0 = local_10;
          local_e8 = (**(code **)(*(int *)(&DAT_1211e4a4 + local_18 * 4) + 0x20))
                               (local_18,local_14,auStack_e0);
        }
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
        }
      }
      else {
        local_e8 = -4;
      }
    }
  }
  return local_e8;
}



/* === bcm_port_duplex_get @ 105c8de8 (size=788) === */

int bcm_port_duplex_get(int param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  int local_20 [2];
  int local_18;
  undefined4 local_14;
  uint *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083aec4(local_18,local_14,local_20);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      if (iVar1 < 0) {
        *local_10 = 1;
      }
      else {
        *local_10 = local_20[0] == 0 ^ 1;
      }
      FUN_10761a94(0x800,"bcm_port_duplex_get: u=%d p=%d dup=%d rv=%d\n",local_18,local_14,*local_10
                   ,iVar1);
    }
  }
  return iVar1;
}



/* === bcm_port_duplex_set @ 105c90fc (size=1512) === */

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



/* === bcm_port_enable_set @ 105aa3dc (size=4828) === */

int bcm_port_enable_set(int param_1,uint param_2,int param_3)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int local_88;
  int local_78;
  int local_74;
  uint local_70 [4];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_48;
  uint local_44;
  int local_40;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_74 = 0;
  bVar1 = false;
  iVar3 = (&DAT_1212d324)[param_1];
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_88 = -0x11;
  }
  else {
    local_48 = param_1;
    local_44 = param_2;
    local_40 = param_3;
    local_88 = FUN_105a6a18(param_1,param_2,&local_44);
    if (-1 < local_88) {
      if ((((*(int *)((&DAT_1212d2dc)[local_48] + 0x10) == 0) &&
           ((((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0x80000) != 0 ||
             ((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0x40) != 0)) &&
            ((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0x40) == 0)))) &&
          ((((*(uint *)((&DAT_1212d2dc)[local_48] +
                        (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)
                        + 0x49c) * 4 + 0x10) &
             1 << (local_44 +
                   (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                   -0x20 & 0x3f)) != 0 && (local_40 != 0)) &&
           (*(int *)(&DAT_11efcdcc + local_48 * 4) != 0)))) &&
         ((*(int *)((&DAT_1212d2dc)[local_48] + (local_44 + 0x1894) * 4 + 4) < 100000 &&
          ((*(uint *)(&DAT_1212d2dc)[local_48] & 2) != 0)))) {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_48 * 4),0xffffffff);
        if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0
            ) && (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0 &&
                  ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)))) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4),0xffffffff);
        }
        bcm_port_loopback_get(local_48,local_44,&local_74);
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
        }
        if (local_74 == 0) {
          FUN_10761a94(0x10000,"Unit %d Cleanup and enable port %d..\n",local_48,local_44);
          iVar4 = *(int *)(&DAT_11efcdcc + local_48 * 4);
          uVar2 = FUN_11313a38();
          *(undefined4 *)(iVar4 + 0xa40) = uVar2;
          FUN_105a3948(*(undefined4 *)(&DAT_11efcdcc + local_48 * 4),1,local_44);
          bVar1 = true;
        }
      }
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_48 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4),0xffffffff);
      }
      bcm_port_loopback_get(local_48,local_44,&local_74);
      if (local_40 == 0) {
        FUN_107d6928(local_48,local_70);
        iVar3 = ((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0);
        local_70[iVar3] =
             local_70[iVar3] &
             ~(1 << (local_44 +
                     (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                     -0x20 & 0x3f));
        local_30 = local_70[0];
        local_2c = local_70[1];
        local_28 = local_70[2];
        local_24 = local_70[3];
        local_20 = local_60;
        local_1c = local_5c;
        local_18 = local_58;
        local_14 = local_54;
        iVar3 = FUN_107d6888(local_48,&local_30);
        if (iVar3 < 0) {
          FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
          if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) ==
              0) {
            return iVar3;
          }
          if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) == 0) {
            return iVar3;
          }
          if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) == 0) {
            return iVar3;
          }
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
          return iVar3;
        }
        FUN_10761a94(0x10000,"Unit %d Disable and isolate port %d..\n",local_48,local_44);
        if (((*(int *)((&DAT_1212d2dc)[local_48] + 0x10) != 0) ||
            ((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0xc) == 0)) && (local_74 != 1)) {
          if ((*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) != 0) &&
             (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x5c) !=
              0)) {
            (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x5c))
                      (local_48,local_44,0,0);
          }
          FUN_10325444(100);
        }
        if ((*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) != 0) &&
           (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x5c) != 0
           )) {
          (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x5c))
                    (local_48,local_44,5,1);
        }
        if (((*(int *)((&DAT_1212d2dc)[local_48] + 0x10) == 0) &&
            ((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0xc) != 0)) && (local_74 == 1)) {
          local_88 = FUN_1083d4dc(local_48,local_44,0x61,1);
        }
        else {
          local_88 = FUN_1083aa9c(local_48,local_44,0);
        }
        if ((*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) != 0) &&
           (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x5c) != 0
           )) {
          (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 0x5c))
                    (local_48,local_44,5,0);
        }
        if ((local_74 != 1) && (-1 < local_88)) {
          if (*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) == 0) {
            local_88 = -4;
          }
          else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 8)
                   == 0) {
            local_88 = -0x10;
          }
          else {
            local_88 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) +
                                            local_44 * 0x38) + 8))(local_48,local_44,0);
          }
        }
      }
      else {
        if ((*(uint *)((&DAT_1212d2dc)[local_48] +
                       (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0) +
                       0x145c) * 4 + 0xc) &
            1 << (local_44 +
                  (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                  -0x20 & 0x3f)) != 0) {
          FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
          if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
                != 0) &&
              ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c
                           ) & 2) != 0)) &&
             ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) {
            FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
          }
          return 0;
        }
        local_88 = FUN_105cfcb4(local_48,local_44,&local_78);
        if (local_88 < 0) {
          local_78 = 0;
          local_88 = 0;
        }
        if (!bVar1) {
          if (((*(int *)((&DAT_1212d2dc)[local_48] + 0x10) == 0) &&
              ((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0xc) != 0)) &&
             ((local_74 == 1 && (iVar4 = FUN_1083d4dc(local_48,local_44,0x61,0), iVar4 < 0)))) {
            FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
            if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
                == 0) {
              return iVar4;
            }
            if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                            0x378c) & 2) == 0) {
              return iVar4;
            }
            if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                            0x378c) & 2) == 0) {
              return iVar4;
            }
            FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
            return iVar4;
          }
          local_88 = FUN_1083aa9c(local_48,local_44,1);
        }
        if ((-1 < local_88) &&
           (((local_78 != 0 || (local_74 != 0)) ||
            ((iVar4 = (int)local_44 >> 5,
             (*(uint *)(iVar3 + (iVar4 + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0) +
                                0x3f118) * 4) &
             1 << (local_44 + (iVar4 + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) * -0x20
                  & 0x3f)) != 0 ||
             ((*(uint *)(iVar3 + (iVar4 + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0) +
                                 0x3f0f0) * 4) &
              1 << (local_44 + (iVar4 + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) * -0x20
                   & 0x3f)) != 0)))))) {
          if (*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) == 0) {
            local_88 = -4;
          }
          else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38) + 8)
                   == 0) {
            local_88 = -0x10;
          }
          else {
            local_88 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) +
                                            local_44 * 0x38) + 8))(local_48,local_44,1);
          }
        }
      }
      if ((*(int *)((&DAT_1212d2dc)[local_48] + 0x10) == 0) &&
         ((*(uint *)((&DAT_1212d2dc)[local_48] + 0x14) & 0xc) != 0)) {
        *(int *)(*(int *)(&DAT_11efcd84 + local_48 * 4) + local_44 * 0x38 + 0x34) = local_40;
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
      }
      if (local_74 != 0) {
        if (local_74 == 1) {
          local_88 = FUN_1053b4ac(local_48,0,local_44,1,1);
        }
        else {
          local_88 = FUN_1053b4ac(local_48,0,local_44,1,local_40);
        }
      }
      FUN_10761a94(0x800,"bcm_port_enable_set: u=%d p=%d enable=%d rv=%d\n",local_48,local_44,
                   local_40,local_88);
      FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0xe708),0xffffffff);
      *(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x2f2bd4) = 1;
      FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0xe708));
    }
  }
  return local_88;
}



/* === bcm_port_encap_get @ 105dbe20 (size=1384) === */

int bcm_port_encap_get(int param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_44;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28 [4];
  int local_18;
  uint local_14;
  undefined4 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    return -0x11;
  }
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = (int)local_14 >> 5;
  if (((*(uint *)((&DAT_1212d2dc)[local_18] +
                  (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x120) * 4 + 8) &
       1 << (local_14 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 & 0x3f
            )) != 0) &&
     ((*(uint *)((&DAT_1212d2dc)[local_18] +
                 (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x784) * 4 + 0x14) &
      1 << (local_14 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 & 0x3f)
      ) != 0)) {
    if ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c34) & 0x2000000) == 0) {
      local_40[0] = DAT_113ab0c4;
      local_40[1] = DAT_113ab0c8;
      local_40[2] = DAT_113ab0cc;
      local_40[3] = DAT_113ab0d0;
      local_30 = DAT_113ab0d4;
      local_2c = DAT_113ab0d8;
      iVar1 = FUN_10847ab4(local_18,0x3e10,local_14,0,&local_44);
      if (iVar1 < 0) {
        return iVar1;
      }
      iVar1 = FUN_1084bccc(local_18,0x3e10,local_40[local_14]);
      if (iVar1 == 0) {
        return -0xf;
      }
      iVar1 = FUN_1084bf98(local_18,0x3e10,local_44,local_40[local_14]);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 3;
      }
      *local_10 = uVar2;
    }
    else {
      *local_10 = 0;
    }
    goto LAB_105dc33c;
  }
  if ((*(uint *)((&DAT_1212d2dc)[local_18] +
                 (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x1b4) * 4 + 0xc) &
      1 << (local_14 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 & 0x3f)
      ) == 0) {
    if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
      iVar1 = -4;
    }
    else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x58) ==
             0) {
      iVar1 = -0x10;
    }
    else {
      iVar1 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x58
                          ))(local_18,local_14,local_10);
    }
  }
  else {
    iVar1 = FUN_10847ab4(local_18,0x6db8,local_14,0,local_28);
    if (iVar1 < 0) {
      return iVar1;
    }
    iVar1 = FUN_1084bf98(local_18,0x6db8,local_28[0],0x58bb);
    if (iVar1 != 0) {
      *local_10 = 3;
      goto LAB_105dc33c;
    }
    iVar1 = FUN_1084bf98(local_18,0x6db8,local_28[0],0x58ca);
    if (iVar1 != 0) {
      *local_10 = 1;
      goto LAB_105dc33c;
    }
    if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
      iVar1 = -4;
    }
    else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x58) ==
             0) {
      iVar1 = -0x10;
    }
    else {
      iVar1 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x58
                          ))(local_18,local_14,local_10);
    }
  }
  if (iVar1 < 0) {
    return iVar1;
  }
LAB_105dc33c:
  FUN_10761a94(0x800,"bcm_esw_port_encap_get: u=%d p=%d mode=%d\n",local_18,local_14,*local_10);
  return 0;
}



/* === bcm_port_fault_get @ 105f2230 (size=672) === */

int bcm_port_fault_get(int param_1,int param_2,uint *param_3)

{
  int iVar1;
  int local_2c;
  int local_28 [4];
  int local_18;
  int local_14;
  uint *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
        iVar1 = -4;
      }
      else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x60)
               == 0) {
        iVar1 = -0x10;
      }
      else {
        iVar1 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) +
                            0x60))(local_18,local_14,0x19,&local_2c);
      }
      if (iVar1 == -0x10) {
        iVar1 = -0x12;
      }
      else {
        if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
          iVar1 = -4;
        }
        else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x60)
                 == 0) {
          iVar1 = -0x10;
        }
        else {
          iVar1 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) +
                              0x60))(local_18,local_14,0x1b,local_28);
        }
        if (-1 < iVar1) {
          *local_10 = 0;
          if (local_28[0] != 0) {
            *local_10 = *local_10 | 2;
          }
          if (local_2c != 0) {
            *local_10 = *local_10 | 1;
          }
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}



/* === bcm_port_info_get @ 105d34d0 (size=532) === */

int bcm_port_info_get(int param_1,uint param_2,uint *param_3)

{
  int iVar1;
  uint local_14;
  uint *local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
  if (-1 < iVar1) {
    if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
      iVar1 = -0x11;
    }
    else {
      FUN_112b50e4(local_10);
      if ((*(uint *)((&DAT_1212d2dc)[param_1] +
                     (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) +
                     0x784) * 4 + 0x14) &
          1 << (local_14 +
                (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20
               & 0x3f)) == 0) {
        *local_10 = 0xffffffff;
      }
      else {
        *local_10 = 0x827a03b;
        if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
           (((((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x7ffff67f) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x10) != 0)) ||
             ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)) ||
            ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x20) != 0)))) {
          *local_10 = *local_10 | 0x8c0;
        }
      }
      iVar1 = FUN_105d0a7c(param_1,local_14,local_10);
    }
  }
  return iVar1;
}



/* === bcm_port_interface_get @ 105c6e3c (size=776) === */

int bcm_port_interface_get(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  uint local_14;
  undefined4 local_10;
  
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
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083c690(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_interface_set @ 105c7144 (size=1116) === */

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



/* === bcm_port_learn_get @ 105ccde0 (size=1744) === */

int bcm_port_learn_get(int param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_d8 [12];
  int local_cc;
  undefined4 local_ac;
  int local_18;
  uint local_14;
  undefined4 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    iVar1 = (int)param_2 >> 0x1a;
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    if (iVar1 == 7) {
      if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
         ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x200000) != 0)) {
        iVar1 = -0x10;
      }
      else {
        iVar1 = FUN_10b84620(param_1,param_2,param_3);
      }
    }
    else if (iVar1 == 6) {
      iVar1 = FUN_10b70110(param_1,param_2,param_3);
    }
    else if (iVar1 == 0x10) {
      iVar1 = FUN_10c6ba88(param_1,param_2,param_3);
    }
    else if (iVar1 == 0x12) {
      if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)))) {
        iVar1 = FUN_10e27aa8(param_1,param_2,param_3);
      }
      else {
        iVar1 = FUN_10c9d5e8(param_1,param_2,param_3);
      }
    }
    else if (iVar1 == 0x1c) {
      iVar1 = FUN_1099b8b4(param_1,param_2,param_3);
    }
    else if (((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
             ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0xc) != 0)) && (param_2 >> 0x1a == 0x20)
            ) {
      iVar1 = FUN_10ac1724(param_1,param_2,param_3);
    }
    else {
      iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
      if (-1 < iVar1) {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
        }
        iVar1 = (**(code **)(*(int *)(&DAT_1211e4a4 + local_18 * 4) + 0x1c))
                          (local_18,local_14,auStack_d8);
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
        }
        if (-1 < iVar1) {
          if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
             (((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7e6c247f) != 0 ||
                ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
               ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)) ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))) {
            *local_10 = 0;
            iVar1 = FUN_10bee848(local_18,local_ac,local_10);
            if (iVar1 < 0) {
              return iVar1;
            }
          }
          else {
            switch(local_ac) {
            case 0:
              if (local_cc == 0) {
                uVar2 = 5;
              }
              else {
                uVar2 = 7;
              }
              *local_10 = uVar2;
              break;
            case 1:
              *local_10 = 2;
              break;
            case 2:
              *local_10 = 4;
              break;
            case 3:
              *local_10 = 0;
              break;
            case 4:
              *local_10 = 7;
              break;
            case 5:
              *local_10 = 6;
              break;
            default:
              return -1;
            }
          }
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}



/* === bcm_port_link_failed_clear @ 10762108 (size=152) === */

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



/* === bcm_port_link_status_get @ 105cfe1c (size=160) === */

int bcm_port_link_status_get(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_105cfcb4(param_1,param_2,param_3);
  if ((-1 < iVar1) && (iVar1 = FUN_1053b0e0(param_1,param_2,param_3), iVar1 != -0xc)) {
    iVar1 = FUN_1053b2d8(param_1,param_2,param_3);
  }
  return iVar1;
}



/* === bcm_port_linkscan_get @ 105c2fd0 (size=120) === */

undefined4 bcm_port_linkscan_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    uVar1 = 0xffffffef;
  }
  else {
    uVar1 = FUN_1053f450(param_1,param_2,param_3);
  }
  return uVar1;
}



/* === bcm_port_linkscan_set @ 105c3048 (size=120) === */

undefined4 bcm_port_linkscan_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    uVar1 = 0xffffffef;
  }
  else {
    uVar1 = FUN_1053eacc(param_1,param_2,param_3);
  }
  return uVar1;
}



/* === bcm_port_loopback_get @ 105c8904 (size=1252) === */

int bcm_port_loopback_get(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28 [4];
  int local_18;
  int local_14;
  undefined4 *local_10;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0xffffffff;
  local_30 = 0;
  local_2c = 0;
  local_28[0] = -1;
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_1062a874(param_1,param_2,local_28,&local_30,&local_34,&local_2c,&local_2c,&local_34,
                         0);
    if (-1 < iVar1) {
      if (local_28[0] == -1) {
        iVar1 = FUN_105a6a18(local_18,local_14,&local_14);
        if (iVar1 < 0) {
          return iVar1;
        }
      }
      else {
        local_14 = local_28[0];
      }
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      if (local_28[0] == -1) {
        iVar1 = FUN_1083c3b4(local_18,local_14,&local_3c);
      }
      else {
        iVar1 = FUN_1083c4a0(local_18,local_14,local_30,local_34,local_2c,&local_3c);
      }
      if (-1 < iVar1) {
        if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
          iVar1 = -4;
        }
        else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x34)
                 == 0) {
          iVar1 = -0x10;
        }
        else {
          iVar1 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) +
                              0x34))(local_18,local_14,&local_38);
        }
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      if (iVar1 < 0) {
        *local_10 = 0;
      }
      else if (local_38 == 0) {
        if (local_3c == 0) {
          *local_10 = 0;
        }
        else {
          *local_10 = 2;
        }
      }
      else {
        *local_10 = 1;
      }
      FUN_10761a94(0x800,"bcm_port_loopback_get: u=%d p=%d lb=%d rv=%d\n",local_18,local_14,
                   *local_10,iVar1);
    }
  }
  return iVar1;
}



/* === bcm_port_loopback_set @ 105c75a0 (size=4964) === */

int bcm_port_loopback_set(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int local_68;
  undefined4 local_64;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28 [4];
  int local_18;
  uint local_14;
  int local_10;
  
  local_3c = 1;
  local_38 = 0xffffffff;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0xffffffff;
  iVar2 = (&DAT_1212d324)[param_1];
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_68 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_68 = FUN_1062a874(param_1,param_2,&local_2c,&local_34,&local_38,&local_30);
    if (-1 < local_68) {
      if (local_2c == 0xffffffff) {
        iVar1 = FUN_105a6a18(local_18,local_14,&local_14);
        if (iVar1 < 0) {
          return iVar1;
        }
      }
      else {
        local_14 = local_2c;
      }
      FUN_1083acfc(local_18,local_14,&local_3c);
      if (((local_3c == 1) &&
          (iVar1 = (int)local_14 >> 5,
          (*(uint *)(iVar2 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x3f0e0)
                             * 4) &
          1 << (local_14 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 &
               0x3f)) != 0)) &&
         ((*(uint *)(iVar2 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x3f0e8)
                             * 4) &
          1 << (local_14 + (iVar1 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 &
               0x3f)) == 0)) {
        local_3c = 0;
      }
      local_68 = 0;
      if (local_10 != 0) {
        local_68 = FUN_1053b4ac(local_18,0,local_14,1,0);
      }
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      if (-1 < local_68) {
        if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
          local_68 = -4;
        }
        else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x30)
                 == 0) {
          local_68 = -0x10;
        }
        else {
          local_68 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38)
                                 + 0x30))(local_18,local_14,local_10 == 1);
        }
      }
      if (-1 < local_68) {
        if (local_2c == 0xffffffff) {
          local_68 = FUN_1083bc3c(local_18,local_14,local_10 == 2,1);
        }
        else {
          local_68 = FUN_1083bfbc(local_18,local_14,local_34,local_38,local_30,local_10 == 2,1);
        }
      }
      if (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c34) & 0x4000) != 0) && (local_10 == 1)) {
        if (local_2c == 0xffffffff) {
          local_68 = FUN_1083bc3c(local_18,local_14,1,1);
        }
        else {
          local_68 = FUN_1083bfbc(local_18,local_14,local_34,local_38,local_30,1,1);
        }
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      if ((local_10 == 0) || (local_68 < 0)) {
        FUN_1053b4ac(local_18,0,local_14,0,0);
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
        if ((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0
            ) && (((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0 &&
                  ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)))) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
        }
        if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
           ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0xc) != 0)) {
          if ((*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38 + 0x34) == 0) &&
             (local_10 == 0)) {
            iVar2 = FUN_1083d4dc(local_18,local_14,0x61,0);
            if (iVar2 < 0) {
              FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
              if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
                  == 0) {
                return iVar2;
              }
              if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                              0x378c) & 2) == 0) {
                return iVar2;
              }
              if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                              0x378c) & 2) == 0) {
                return iVar2;
              }
              FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
              return iVar2;
            }
            iVar2 = FUN_1083aa9c(local_18,local_14,0);
            if (iVar2 < 0) {
              FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
              if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
                  == 0) {
                return iVar2;
              }
              if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                              0x378c) & 2) == 0) {
                return iVar2;
              }
              if ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                              0x378c) & 2) == 0) {
                return iVar2;
              }
              FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
              return iVar2;
            }
            if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
              local_68 = -4;
            }
            else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 8
                             ) == 0) {
              local_68 = -0x10;
            }
            else {
              local_68 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) +
                                              local_14 * 0x38) + 8))(local_18,local_14,0);
            }
          }
        }
        else if ((local_3c == 0) && (local_10 == 0)) {
          if ((*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) != 0) &&
             (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x5c) !=
              0)) {
            (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x5c))
                      (local_18,local_14,0,0);
          }
          FUN_10325444(100);
          if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
            local_68 = -4;
          }
          else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 8)
                   == 0) {
            local_68 = -0x10;
          }
          else {
            local_68 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) +
                                            local_14 * 0x38) + 8))(local_18,local_14,0);
          }
        }
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
        }
      }
      else {
        if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
          local_68 = -4;
        }
        else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 8) ==
                 0) {
          local_68 = -0x10;
        }
        else {
          local_68 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38)
                                 + 8))(local_18,local_14,1);
        }
        if (local_68 < 0) {
          return local_68;
        }
        if (((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0xc) != 0)) &&
           ((local_3c == 0 && (local_10 == 1)))) {
          iVar2 = FUN_1083d4dc(local_18,local_14,0x61,1);
          if (iVar2 < 0) {
            return iVar2;
          }
          iVar2 = FUN_1083aa9c(local_18,local_14,1);
          if (iVar2 < 0) {
            return iVar2;
          }
        }
        if (-1 < local_68) {
          if (local_10 == 1) {
            local_68 = FUN_1053b4ac(local_18,0,local_14,1,1);
          }
          else {
            local_68 = FUN_1053b4ac(local_18,0,local_14,1,local_3c);
          }
        }
        if (local_68 < 0) {
          return local_68;
        }
        if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
           ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x421e000) != 0)) {
          local_68 = FUN_105a9744(local_18,local_14,1);
        }
        iVar2 = (int)local_14 >> 5;
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) + 0xfa14) !=
              0) && ((*(uint *)((&DAT_1212d2dc)[local_18] +
                                (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x81c
                                ) * 4 + 8) &
                     1 << (local_14 +
                           (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20 &
                          0x3f)) != 0)) ||
           (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) + 0x16dbc) !=
              0 || (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) +
                            0x23c78) != 0)) &&
            (((*(uint *)((&DAT_1212d2dc)[local_18] +
                         (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x8b0) * 4 +
                        0xc) &
              1 << (local_14 + (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20
                   & 0x3f)) != 0 ||
             ((*(uint *)((&DAT_1212d2dc)[local_18] +
                         (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x944) * 4 +
                        0x10) &
              1 << (local_14 + (iVar2 + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0)) * -0x20
                   & 0x3f)) != 0)))))) {
          if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) + 0x16dbc) ==
              0) {
            if (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) + 0xfa14)
                == 0) {
              local_64 = 0x8f1e;
            }
            else {
              local_64 = 0x3e85;
            }
          }
          else {
            local_64 = 0x5b6f;
          }
          iVar2 = FUN_10847ab4(local_18,local_64,local_14,0,local_28);
          if (iVar2 < 0) {
            return iVar2;
          }
          FUN_1084d57c(local_18,local_64,local_28,0x77eb,1);
          iVar2 = FUN_1084a784(local_18,local_64,local_14,0,local_28[0]);
          if (iVar2 < 0) {
            return iVar2;
          }
          FUN_1084d57c(local_18,local_64,local_28,0x77eb,0);
          iVar2 = FUN_1084a784(local_18,local_64,local_14,0,local_28[0]);
          if (iVar2 < 0) {
            return iVar2;
          }
        }
      }
      FUN_10761a94(0x800,"bcm_port_loopback_set: u=%d p=%d lb=%d rv=%d\n",local_18,local_14,local_10
                   ,local_68);
    }
  }
  return local_68;
}



/* === bcm_port_master_get @ 105c67a8 (size=672) === */

int bcm_port_master_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083b24c(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_master_set @ 105c6a48 (size=1012) === */

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



/* === bcm_port_mdix_get @ 105f04dc (size=672) === */

int bcm_port_mdix_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083ce30(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_mdix_set @ 105f023c (size=672) === */

int bcm_port_mdix_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083cd54(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_mdix_status_get @ 105f077c (size=672) === */

int bcm_port_mdix_status_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083cf1c(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_medium_get @ 105f0f6c (size=672) === */

int bcm_port_medium_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      iVar1 = FUN_1083d1f8(param_1,local_14,local_10);
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_pause_get @ 105c96e4 (size=848) === */

int bcm_port_pause_get(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      if (*(int *)(*(int *)(&DAT_11efcd84 + param_1 * 4) + local_14 * 0x38) == 0) {
        iVar1 = -4;
      }
      else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + param_1 * 4) + local_14 * 0x38) + 0x24) ==
               0) {
        iVar1 = -0x10;
      }
      else {
        iVar1 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + param_1 * 4) + local_14 * 0x38) +
                            0x24))(param_1,local_14,local_10,local_c);
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
      }
    }
  }
  return iVar1;
}



/* === bcm_port_pfm_get @ 105d0298 (size=296) === */

int bcm_port_pfm_get(int param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  int local_14;
  undefined4 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar2 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar2 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar2) {
      iVar2 = bcm_mirror_ingress_get((&DAT_1212d2dc)[param_1] + (local_14 + 0x1c84) * 4 + 4,0x66);
      if (iVar2 == 0) {
        iVar2 = -0x12;
      }
      else {
        uVar1 = FUN_112b0ae8(param_1);
        if ((uVar1 < 0x17) && ((1 << (uVar1 & 0x3f) & 0x41ff00U) != 0)) {
          *local_10 = 2;
          iVar2 = -0x10;
        }
        else {
          iVar2 = -0x10;
        }
      }
    }
  }
  return iVar2;
}



/* === bcm_port_pfm_set @ 105cffac (size=748) === */

int bcm_port_pfm_set(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < iVar1) {
      iVar1 = bcm_mirror_ingress_get((&DAT_1212d2dc)[param_1] + (local_14 + 0x1c84) * 4 + 4,0x66);
      if (iVar1 == 0) {
        iVar1 = -0x12;
      }
      else {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0
             ) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
        }
        iVar1 = FUN_105cff2c(param_1,local_14,local_10);
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0
             ) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
        }
      }
    }
  }
  return iVar1;
}



/* === bcm_port_phy_timesync_config_get @ 1041f484 (size=312) === */

undefined4 bcm_port_phy_timesync_config_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858cf8)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_phy_timesync_config_get",3,2,param_1,local_14,0,local_28);
  }
  return local_28;
}



/* === bcm_port_phy_timesync_config_set @ 1041f5bc (size=312) === */

undefined4 bcm_port_phy_timesync_config_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858d00)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_port_phy_timesync_config_set",3,2,param_1,local_14,0,local_28);
  }
  return local_28;
}



/* === bcm_port_speed_get @ 105c37e4 (size=1496) === */

int bcm_port_speed_get(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  int local_28;
  int local_20 [2];
  int local_18;
  uint local_14;
  int *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_28 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_28 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < local_28) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
      }
      if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
        local_28 = -4;
      }
      else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x34)
               == 0) {
        local_28 = -0x10;
      }
      else {
        local_28 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) +
                               0x34))(local_18,local_14,local_20);
      }
      if (-1 < local_28) {
        if (local_20[0] == 0) {
          local_28 = FUN_1083b078(local_18,local_14,local_10);
          if (local_28 == -0x10) {
            if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
              local_28 = -4;
            }
            else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) +
                             0x1c) == 0) {
              local_28 = -0x10;
            }
            else {
              local_28 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) +
                                              local_14 * 0x38) + 0x1c))(local_18,local_14,local_10);
            }
          }
          if (((*(uint *)((&DAT_1212d2dc)[local_18] +
                          (((int)local_14 >> 5) +
                           (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0) + 0x49c) * 4 + 0x10)
               & 1 << (local_14 +
                       (((int)local_14 >> 5) + (uint)((int)local_14 < 0 && (local_14 & 0x1f) != 0))
                       * -0x20 & 0x3f)) != 0) && (*local_10 < 5000)) {
            *local_10 = 0;
          }
        }
        else if (*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) == 0) {
          local_28 = -4;
        }
        else if (*(int *)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38) + 0x1c)
                 == 0) {
          local_28 = -0x10;
        }
        else {
          local_28 = (**(code **)(*(int *)(*(int *)(&DAT_11efcd84 + local_18 * 4) + local_14 * 0x38)
                                 + 0x1c))(local_18,local_14,local_10);
        }
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) & 2
          ) != 0)) {
        FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
      }
      if (local_28 < 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *local_10;
      }
      FUN_10761a94(0x800,"bcm_port_speed_get: u=%d p=%d speed=%d rv=%d\n",local_18,local_14,iVar1,
                   local_28);
    }
  }
  return local_28;
}



/* === bcm_port_speed_max @ 105c3dbc (size=2632) === */

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



/* === bcm_port_speed_set @ 105c630c (size=1180) === */

int bcm_port_speed_set(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int local_88;
  int local_84;
  int local_74;
  uint local_70 [4];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_48;
  uint local_44;
  int local_40;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar2 = -0x11;
  }
  else {
    local_48 = param_1;
    local_44 = param_2;
    local_40 = param_3;
    iVar2 = FUN_105a6a18(param_1,param_2,&local_44);
    if ((-1 < iVar2) && (iVar2 = bcm_port_speed_max(local_48,local_44,&local_74), -1 < iVar2)) {
      local_88 = param_3;
      if (((*(uint *)((&DAT_1212d2dc)[local_48] +
                      (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0) +
                      0x8b0) * 4 + 0xc) &
           1 << (local_44 +
                 (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                 -0x20 & 0x3f)) != 0) && (param_3 == 0x319c)) {
        local_88 = 13000;
      }
      if ((local_88 < 0) || (local_74 < local_88)) {
        iVar2 = -0xf;
      }
      else {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_48 * 4),0xffffffff);
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4),0xffffffff);
        }
        iVar2 = FUN_105c5398(local_48,local_44,local_88);
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_48 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_48] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_48] + 0x26e1a4));
        }
        if ((-1 < iVar2) && (uVar1 = FUN_1131262c(), (uVar1 & 0x8b0000) == 0)) {
          for (local_84 = 0; local_84 < 8; local_84 = local_84 + 1) {
            local_70[local_84] = 0;
          }
          iVar3 = ((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0);
          local_70[iVar3] =
               local_70[iVar3] |
               1 << (local_44 +
                     (((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0)) *
                     -0x20 & 0x3f);
          local_30 = local_70[0];
          local_2c = local_70[1];
          local_28 = local_70[2];
          local_24 = local_70[3];
          local_20 = local_60;
          local_1c = local_5c;
          local_18 = local_58;
          local_14 = local_54;
          FUN_1053ae58(local_48,&local_30);
        }
        FUN_10761a94(0x800,"bcm_port_speed_set: u=%d p=%d speed=%d rv=%d\n",local_48,local_44,
                     local_88,iVar2);
      }
    }
  }
  return iVar2;
}



/* === bcm_port_stp_get @ 105c186c (size=304) === */

int bcm_port_stp_get(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int local_28;
  undefined4 local_20 [2];
  int local_18;
  undefined4 local_14;
  undefined4 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_28 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_28 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < local_28) {
      local_28 = FUN_106b831c(local_18,local_20);
      if (local_28 < 0) {
        if (local_28 == -0x10) {
          *local_10 = 4;
          local_28 = 0;
        }
      }
      else {
        local_28 = FUN_106bafa4(local_18,local_20[0],local_14,local_10);
      }
      FUN_10761a94(0x800,"bcm_port_stp_get: u=%d p=%d state=%d rv=%d\n",local_18,local_14,*local_10,
                   local_28);
    }
  }
  return local_28;
}



/* === bcm_port_stp_set @ 105c1670 (size=508) === */

int bcm_port_stp_set(int param_1,undefined4 param_2,int param_3)

{
  int local_38;
  int local_34;
  int local_2c;
  int local_28 [4];
  int local_18;
  undefined4 local_14;
  int local_10;
  
  local_2c = 0;
  local_28[0] = 0;
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_34 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_34 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < local_34) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
      local_34 = FUN_106ba8cc(local_18,&local_2c,local_28);
      if (local_34 == -0x10) {
        if (local_10 == 4) {
          local_34 = 0;
        }
        else {
          local_34 = -4;
        }
      }
      else if (-1 < local_34) {
        local_38 = 0;
        while ((local_38 < local_28[0] &&
               (local_34 = FUN_106bac60(local_18,*(undefined4 *)(local_2c + local_38 * 4),local_14,
                                        local_10), -1 < local_34))) {
          local_38 = local_38 + 1;
        }
        FUN_106bab70(local_18,local_2c,local_28[0]);
      }
      FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
      FUN_10761a94(0x800,"bcm_port_stp_set: u=%d p=%d state=%d rv=%d\n",local_18,local_14,local_10,
                   local_34);
    }
  }
  return local_34;
}



/* === bcm_port_untagged_priority_get @ 105d08c0 (size=444) === */

int bcm_port_untagged_priority_get(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int local_14;
  undefined4 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    if (param_2 >> 0x1a == 0x12) {
      if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)))) {
        iVar1 = FUN_10e30120(param_1,param_2,param_3);
      }
      else {
        iVar1 = FUN_10ca51f0(param_1,param_2,param_3);
      }
    }
    else {
      iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
      if (-1 < iVar1) {
        if (local_10 != (undefined4 *)0x0) {
          *local_10 = *(undefined4 *)(*(int *)(&DAT_11efcd84 + param_1 * 4) + local_14 * 0x38 + 4);
          FUN_10761a94(0x800,"bcm_port_ut_priority_get: u=%d p=%d pri=%d\n",param_1,local_14,
                       *local_10);
        }
        iVar1 = 0;
      }
    }
  }
  return iVar1;
}



/* === bcm_port_untagged_priority_set @ 105d053c (size=900) === */

int bcm_port_untagged_priority_set(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    if (param_2 >> 0x1a == 0x12) {
      if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)))) {
        iVar1 = FUN_10e300a4(param_1,param_2,param_3);
      }
      else {
        iVar1 = FUN_10ca5174(param_1,param_2,param_3);
      }
    }
    else {
      iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
      if (-1 < iVar1) {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0
             ) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
        }
        iVar1 = FUN_105d03c0(param_1,local_14,local_10);
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0
             ) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
        }
        FUN_10761a94(0x800,"bcm_port_ut_priority_set: u=%d p=%d pri=%d rv=%d\n",param_1,local_14,
                     local_10,iVar1);
      }
    }
  }
  return iVar1;
}



/* === bcm_port_untagged_vlan_get @ 105a930c (size=1080) === */

int bcm_port_untagged_vlan_get(int param_1,uint param_2,undefined2 *param_3)

{
  int iVar1;
  undefined1 auStack_e0 [116];
  undefined2 local_6c;
  int local_18;
  uint local_14;
  undefined2 *local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    iVar1 = -0x11;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    if ((int)param_2 >> 0x1a == 0x12) {
      if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)))) {
        iVar1 = FUN_10e30024(param_1,param_2,param_3);
      }
      else {
        iVar1 = FUN_10ca50fc(param_1,param_2,param_3);
      }
    }
    else if ((int)param_2 >> 0x1a == 0x1c) {
      iVar1 = FUN_1099a600(param_1,param_2,param_3);
    }
    else if (param_2 >> 0x1a == 0x23) {
      iVar1 = FUN_10d156a0(param_1,param_2,param_3);
    }
    else {
      iVar1 = FUN_105a6a18(param_1,param_2,&local_14);
      if (-1 < iVar1) {
        FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + local_18 * 4),0xffffffff);
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4),0xffffffff);
        }
        iVar1 = (**(code **)(*(int *)(&DAT_1211e4a4 + local_18 * 4) + 0x1c))
                          (local_18,local_14,auStack_e0);
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + local_18 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) !=
              0) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) +
                                 0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0x26e1a4));
        }
        if (iVar1 < 0) {
          *local_10 = 0x1000;
        }
        else {
          *local_10 = local_6c;
        }
        FUN_10761a94(0x800,"bcm_port_untagged_vlan_get: u=%d p=%d vid=%d rv=%d\n",local_18,local_14,
                     *local_10,iVar1);
      }
    }
  }
  return iVar1;
}



/* === bcm_port_update @ 105c1234 (size=1084) === */

int bcm_port_update(int param_1,undefined4 param_2,undefined4 param_3)

{
  int local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(&DAT_11efcd84 + param_1 * 4) == 0) {
    local_28 = -0x11;
  }
  else {
    local_14 = param_2;
    local_10 = param_3;
    local_28 = FUN_105a6a18(param_1,param_2,&local_14);
    if (-1 < local_28) {
      FUN_11312da0(*(undefined4 *)(&DAT_124c3424 + param_1 * 4),0xffffffff);
      if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0)
          && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c)
              & 2) != 0)) &&
         ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) & 2)
          != 0)) {
        FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4),0xffffffff);
      }
      local_28 = FUN_105c0200(param_1,local_14,local_10);
      if (local_28 < 0) {
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0
             ) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
        }
      }
      else {
        if ((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
           ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x421e000) != 0)) {
          local_28 = FUN_105a9744(param_1,local_14,local_10);
        }
        FUN_11312efc(*(undefined4 *)(&DAT_124c3424 + param_1 * 4));
        if (((*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) != 0
             ) && ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) +
                               0x378c) & 2) != 0)) &&
           ((**(uint **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x24) + 0x378c) &
            2) != 0)) {
          FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0x26e1a4));
        }
        FUN_10761a94(0x800,"bcm_port_update: u=%d p=%d link=%d rv=%d\n",param_1,local_14,local_10,
                     local_28);
      }
    }
  }
  return local_28;
}



/* === bcm_rate_bcast_port_set @ 10634628 (size=876) === */

int bcm_rate_bcast_port_set(int param_1,undefined4 param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_28 [4];
  int local_18;
  undefined4 local_14;
  uint local_10;
  uint local_c [2];
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c[0] = param_4;
  if (((param_4 >> 0x1a == 0) || (0x29 < param_4 >> 0x1a)) ||
     (iVar2 = FUN_10619410(param_1,param_4,local_c), -1 < iVar2)) {
    uVar1 = local_14;
    if ((((int)local_c[0] < 0) || (0x81 < (int)local_c[0])) ||
       (*(int *)((&DAT_1212d2dc)[local_18] + (local_c[0] + 0x1c84) * 4 + 4) == 0)) {
      iVar2 = -0x12;
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            ((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7e6c247f) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
             (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))))) {
      iVar2 = FUN_10632870(local_18,local_c[0],0,local_10,4,local_14,0xffffffff);
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            (((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
               ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)) ||
             ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))) {
      local_28[0] = 0;
      FUN_1084d57c(local_18,0x311,local_28,0x3e95,(local_10 & 4) != 0);
      FUN_1084d57c(local_18,0x311,local_28,0xd6c1,uVar1);
      iVar2 = FUN_1084a784(local_18,0x311,local_c[0],0,local_28[0]);
      if (-1 < iVar2) {
        iVar2 = 0;
      }
    }
    else {
      iVar2 = -0x10;
    }
  }
  return iVar2;
}



/* === bcm_rate_dlfbcast_port_set @ 10634994 (size=876) === */

int bcm_rate_dlfbcast_port_set(int param_1,undefined4 param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_28 [4];
  int local_18;
  undefined4 local_14;
  uint local_10;
  uint local_c [2];
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c[0] = param_4;
  if (((param_4 >> 0x1a == 0) || (0x29 < param_4 >> 0x1a)) ||
     (iVar2 = FUN_10619410(param_1,param_4,local_c), -1 < iVar2)) {
    uVar1 = local_14;
    if ((((int)local_c[0] < 0) || (0x81 < (int)local_c[0])) ||
       (*(int *)((&DAT_1212d2dc)[local_18] + (local_c[0] + 0x1c84) * 4 + 4) == 0)) {
      iVar2 = -0x12;
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            ((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7e6c247f) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
             (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))))) {
      iVar2 = FUN_10632870(local_18,local_c[0],0,local_10,1,local_14,0xffffffff);
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            (((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
               ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)) ||
             ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))) {
      local_28[0] = 0;
      FUN_1084d57c(local_18,0x22d0,local_28,0x3e95,(local_10 & 1) != 0);
      FUN_1084d57c(local_18,0x22d0,local_28,0xd6c1,uVar1);
      iVar2 = FUN_1084a784(local_18,0x22d0,local_c[0],0,local_28[0]);
      if (-1 < iVar2) {
        iVar2 = 0;
      }
    }
    else {
      iVar2 = -0x10;
    }
  }
  return iVar2;
}



/* === bcm_rate_mcast_port_set @ 106342bc (size=876) === */

int bcm_rate_mcast_port_set(int param_1,undefined4 param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_28 [4];
  int local_18;
  undefined4 local_14;
  uint local_10;
  uint local_c [2];
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c[0] = param_4;
  if (((param_4 >> 0x1a == 0) || (0x29 < param_4 >> 0x1a)) ||
     (iVar2 = FUN_10619410(param_1,param_4,local_c), -1 < iVar2)) {
    uVar1 = local_14;
    if ((((int)local_c[0] < 0) || (0x81 < (int)local_c[0])) ||
       (*(int *)((&DAT_1212d2dc)[local_18] + (local_c[0] + 0x1c84) * 4 + 4) == 0)) {
      iVar2 = -0x12;
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            ((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7e6c247f) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
             (((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0 ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))))) {
      iVar2 = FUN_10632870(local_18,local_c[0],0,local_10,2,local_14,0xffffffff);
    }
    else if ((*(int *)((&DAT_1212d2dc)[local_18] + 0x10) == 0) &&
            (((((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
               ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x10) != 0)) ||
              ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x40) != 0)) ||
             ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x14) & 0x20) != 0)))) {
      local_28[0] = 0;
      FUN_1084d57c(local_18,0x5f6f,local_28,0x3e95,(local_10 & 2) != 0);
      FUN_1084d57c(local_18,0x5f6f,local_28,0xd6c1,uVar1);
      iVar2 = FUN_1084a784(local_18,0x5f6f,local_c[0],0,local_28[0]);
      if (-1 < iVar2) {
        iVar2 = 0;
      }
    }
    else {
      iVar2 = -0x10;
    }
  }
  return iVar2;
}



/* === bcm_tr2_wlan_cli_port_print @ 101b8550 (size=420) === */

undefined4 bcm_tr2_wlan_cli_port_print(undefined4 param_1,int param_2,undefined4 param_3)

{
  FUN_10321ae0("\n WLAN Port ID: %x",*(undefined4 *)(param_2 + 4));
  FUN_10321ae0("\n Port: %x",*(undefined4 *)(param_2 + 8));
  FUN_10321ae0("\n Interface Class: %d",*(undefined4 *)(param_2 + 0xc));
  FUN_10321ae0("\n BSSID: %02x:%02x:%02x:%02x:%02x:%02x",*(undefined1 *)(param_2 + 0x10),
               *(undefined1 *)(param_2 + 0x11),*(undefined1 *)(param_2 + 0x12),
               *(undefined1 *)(param_2 + 0x13),*(undefined1 *)(param_2 + 0x14),
               *(undefined1 *)(param_2 + 0x15),*(undefined1 *)(param_2 + 0x14),param_1,param_2,
               param_3);
  FUN_10321ae0("\n Radio ID: %d",*(undefined4 *)(param_2 + 0x18));
  FUN_10321ae0("\n Match Tunnel: %x",*(undefined4 *)(param_2 + 0x1c));
  FUN_10321ae0("\n Egress Tunnel: %x",*(undefined4 *)(param_2 + 0x20));
  FUN_10321ae0("\n Client Multicast Bitmap: %x",*(undefined2 *)(param_2 + 0x24));
  FUN_10321ae0("\n Encap ID: %d",*(undefined4 *)(param_2 + 0x28));
  return 0;
}



/* === bcm_wlan_port_add @ 10459658 (size=536) === */

undefined4 bcm_wlan_port_add(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_2 != 0) {
      FUN_1038b364(param_1,param_2 + 0x20);
      FUN_1038b364(param_1,param_2 + 0x1c);
      FUN_1038b364(param_1,param_2 + 8);
      FUN_1038b364(param_1,param_2 + 4);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3f0)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
    if (param_2 != 0) {
      FUN_1038b3b4(param_1,param_2 + 0x20);
      FUN_1038b3b4(param_1,param_2 + 0x1c);
      FUN_1038b3b4(param_1,param_2 + 8);
      FUN_1038b3b4(param_1,param_2 + 4);
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_port_add",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_port_delete @ 10459870 (size=304) === */

undefined4 bcm_wlan_port_delete(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14 [4];
  
  local_14[0] = param_2;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3f8)[iVar1])(param_1,local_14[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_port_delete",2,2,param_1,local_14[0],0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_port_delete_all @ 104599a0 (size=272) === */

undefined4 bcm_wlan_port_delete_all(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a400)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_port_delete_all",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_port_get @ 10459ab0 (size=568) === */

undefined4 bcm_wlan_port_get(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  int local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    if (local_10 != 0) {
      FUN_1038b364(param_1,local_10 + 0x20);
    }
    if (local_10 != 0) {
      FUN_1038b364(param_1,local_10 + 0x1c);
    }
    if (local_10 != 0) {
      FUN_1038b364(param_1,local_10 + 8);
    }
    if (local_10 != 0) {
      FUN_1038b364(param_1,local_10 + 4);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a408)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
    if (local_10 != 0) {
      FUN_1038b3b4(param_1,local_10 + 0x20);
    }
    if (local_10 != 0) {
      FUN_1038b3b4(param_1,local_10 + 0x1c);
    }
    if (local_10 != 0) {
      FUN_1038b3b4(param_1,local_10 + 8);
    }
    if (local_10 != 0) {
      FUN_1038b3b4(param_1,local_10 + 4);
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_port_get",3,2,param_1,local_14,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_port_traverse @ 10459ce8 (size=288) === */

undefined4 bcm_wlan_port_traverse(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a410)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_port_traverse",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



