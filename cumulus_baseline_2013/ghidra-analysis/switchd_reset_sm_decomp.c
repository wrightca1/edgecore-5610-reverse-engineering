/* Per-port reset state machine + soc_init body decompilation */

/* === FUN_10e7153c (size=18444) === */

int FUN_10e7153c(int param_1)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint local_1e8;
  uint local_1e4;
  int local_1e0;
  uint local_1dc;
  int local_1d8;
  uint local_1d4;
  int local_1d0;
  uint local_1cc;
  int local_1c8;
  int local_1c4;
  int local_1c0;
  uint local_1bc;
  int local_1b8;
  int local_1b4;
  uint local_1b0;
  int local_1ac;
  uint local_1a4;
  short local_c0;
  undefined1 auStack_be [2];
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  uint auStack_b0 [6];
  uint auStack_98 [6];
  undefined4 local_80;
  uint auStack_7c [6];
  uint auStack_64 [6];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c [4];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_18;
  
  if ((*(uint *)(&DAT_1212b9c4)[param_1] & 0x800) != 0) {
    return 0;
  }
  local_18 = param_1;
  FUN_10797cc8(param_1);
  FUN_10798e38(local_18,0xffffffff);
  FUN_10797b20(local_18);
  FUN_1075f9c8(local_18,&local_c0,auStack_be);
  FUN_112af0e0(local_18);
  iVar3 = FUN_107953d0(local_18,"soc_skip_reset",0);
  if (iVar3 == 0) {
    uVar4 = FUN_11311498();
    if ((uVar4 & 0x80000) == 0) {
      uVar5 = FUN_113116b4();
      *(uint *)(&DAT_1212b9c4)[local_18] = *(uint *)(&DAT_1212b9c4)[local_18] | 0x80;
      FUN_1131162c(uVar5);
      if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 2) == 0) {
        if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
          pcVar1 = *(code **)(&DAT_1212434c + local_18 * 0x78);
          iVar3 = local_18 * 0x78;
          if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                              (&DAT_12124314 + local_18 * 0x78,0x10c);
          }
          else {
            uVar4 = *(uint *)(*(int *)(&DAT_12124344 + local_18 * 0x78) + 0x10c);
          }
          (*pcVar1)(&DAT_12124314 + iVar3,0x10c,uVar4 | 0x20);
        }
        else {
          iVar3 = *(int *)(&DAT_12124344 + local_18 * 0x78);
          if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
            uVar4 = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                              (&DAT_12124314 + local_18 * 0x78,0x10c);
          }
          else {
            uVar4 = *(uint *)(*(int *)(&DAT_12124344 + local_18 * 0x78) + 0x10c);
          }
          *(uint *)(iVar3 + 0x10c) = uVar4 | 0x20;
        }
      }
      else if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
        (**(code **)(&DAT_1212434c + local_18 * 0x78))(&DAT_12124314 + local_18 * 0x78,0x10220,1);
      }
      else {
        *(undefined4 *)(*(int *)(&DAT_12124344 + local_18 * 0x78) + 0x10220) = 1;
      }
      if (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c28) & 0x80) == 0) ||
         (uVar4 = FUN_11311498(), (uVar4 & 0x10000) != 0)) {
        uVar4 = FUN_11311498();
        if ((uVar4 & 0x10000) == 0) {
          FUN_1032460c(1000);
        }
        else {
          FUN_1032460c(10000);
        }
      }
      else {
        FUN_1032460c(1000000);
      }
    }
  }
  else {
    FUN_10760cd4(0x8000000,"soc_init: skipping hard reset\n");
  }
  uVar4 = FUN_11311498();
  if ((uVar4 & 0x10000) == 0) {
    FUN_1032460c(10000);
  }
  else {
    FUN_1032460c(250000);
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 2) == 0) {
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_12124348 + local_18 * 0x78))(&DAT_12124314 + local_18 * 0x78,0x10c);
    }
    FUN_1032460c(1000);
  }
  FUN_10797cc8(local_18);
  FUN_10798e38(local_18,0xffffffff);
  FUN_10797b20(local_18);
  if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 2) == 0) {
    FUN_107b9fac(local_18,0xffffffff);
  }
  else {
    iVar3 = *(int *)((&DAT_1212b9c4)[local_18] + 0xe1fc) * 0x1000 + 0x31470;
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      local_bc = (**(code **)(&DAT_12124348 + local_18 * 0x78))
                           (&DAT_12124314 + local_18 * 0x78,iVar3);
    }
    else {
      local_bc = *(undefined4 *)(iVar3 + *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    FUN_1084c7bc(local_18,0xc8f,&local_bc,0x3f53,1);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_18 * 0x78))(&DAT_12124314 + local_18 * 0x78,iVar3,local_bc)
      ;
    }
    else {
      *(undefined4 *)(iVar3 + *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_bc;
    }
    FUN_107c8968(local_18,0xffffffff);
    FUN_107c8a40(local_18,0xffffffff);
    FUN_107c8b18(local_18,0xffffffff);
  }
  uVar5 = FUN_113116b4();
  *(uint *)(&DAT_1212b9c4)[local_18] = *(uint *)(&DAT_1212b9c4)[local_18] & 0xffffff7f;
  FUN_1131162c(uVar5);
  FUN_112af178(local_18);
  if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
     ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x8000000) != 0)) {
    FUN_10e657ac(local_18);
  }
  else {
    if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) == 0) {
      if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
         (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x80000) != 0 ||
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)))) {
        iVar3 = FUN_10e6f2c4(local_18);
      }
      else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
              ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0xc) != 0)) {
        iVar3 = FUN_10f2f8b0(local_18);
      }
      else {
        if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) != 0) ||
           ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x5000000c) == 0)) {
          if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
             (((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7a4c044f) != 0 ||
                ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
               ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)) ||
              ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))) {
            FUN_10e63758(local_18);
          }
          else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
                  ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x4202000) != 0)) {
            FUN_10e67c8c(local_18);
          }
          else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
                  ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x1921200) != 0)) {
            FUN_10e62cc4(local_18);
          }
          else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
                  ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x1c000) != 0)) {
            FUN_10e632ec(local_18);
          }
          goto LAB_10e720cc;
        }
        iVar3 = FUN_10e6a728(local_18);
      }
    }
    else {
      iVar3 = FUN_10e6ce08(local_18);
    }
    if (iVar3 < 0) {
      return iVar3;
    }
  }
LAB_10e720cc:
  if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
     (((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
        ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
       ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)) ||
      ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))) {
    if (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 2) != 0) &&
       (iVar3 = FUN_107953d0(local_18,"mdio_external_master",0), iVar3 == 0)) {
      if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
        pcVar1 = *(code **)(&DAT_12124348 + local_18 * 0x78);
        iVar3 = local_18 * 0x78;
        uVar5 = FUN_1084e2b0(local_18,0x14bf,0xfffffff6,0);
        local_b8 = (*pcVar1)(&DAT_12124314 + iVar3,uVar5);
      }
      else {
        uVar4 = FUN_1084e2b0(local_18,0x14bf,0xfffffff6,0);
        local_b8 = *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78))
        ;
      }
      FUN_1084c7bc(local_18,0x14bf,&local_b8,0x937d,1);
      if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
        pcVar1 = *(code **)(&DAT_1212434c + local_18 * 0x78);
        iVar3 = local_18 * 0x78;
        uVar5 = FUN_1084e2b0(local_18,0x14bf,0xfffffff6,0);
        (*pcVar1)(&DAT_12124314 + iVar3,uVar5,local_b8);
      }
      else {
        uVar4 = FUN_1084e2b0(local_18,0x14bf,0xfffffff6,0);
        *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_b8
        ;
      }
    }
    if ((((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) != 0) ||
         ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x4202000) == 0)) &&
        ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x5000000c) == 0)))) &&
       ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 2) == 0)) {
      if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
        pcVar1 = *(code **)(&DAT_1212434c + local_18 * 0x78);
        iVar3 = local_18 * 0x78;
        uVar5 = FUN_1084e2b0(local_18,0x14a7,0xfffffff6,0);
        (*pcVar1)(&DAT_12124314 + iVar3,uVar5,
                  *(uint *)((&DAT_1212b9c4)[local_18] + 0x1280) |
                  *(uint *)((&DAT_1212b9c4)[local_18] + 0x102c));
      }
      else {
        uVar4 = FUN_1084e2b0(local_18,0x14a7,0xfffffff6,0);
        *(uint *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78)) =
             *(uint *)((&DAT_1212b9c4)[local_18] + 0x1280) |
             *(uint *)((&DAT_1212b9c4)[local_18] + 0x102c);
      }
    }
    uVar4 = FUN_11311498();
    if ((uVar4 & 0x10000) != 0) {
      for (local_1e8 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x480);
          (-1 < (int)local_1e8 && ((int)local_1e8 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x484)));
          local_1e8 = local_1e8 + 1) {
        if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                       (((int)local_1e8 >> 5) +
                        (uint)((int)local_1e8 < 0 && (local_1e8 & 0x1f) != 0) + 0x120) * 4 + 8) &
            1 << (local_1e8 +
                  (((int)local_1e8 >> 5) + (uint)((int)local_1e8 < 0 && (local_1e8 & 0x1f) != 0)) *
                  -0x20 & 0x3f)) != 0) {
          if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
             ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x200000) != 0)) {
            iVar3 = FUN_1082ecfc(local_18,(local_1e8 & 0xffff) - 0x18 & 0xffff,0,0x140);
          }
          else if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) == 0) {
            iVar3 = FUN_1082ecfc(local_18,local_1e8 & 0xffff,0,0x140);
          }
          else {
            iVar3 = FUN_1082ecfc(local_18,local_1e8 & 0xffff,0,0xffff);
          }
          if (iVar3 < 0) {
            return iVar3;
          }
        }
      }
      for (local_1e8 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x22c);
          (-1 < (int)local_1e8 && ((int)local_1e8 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x230)));
          local_1e8 = local_1e8 + 1) {
        if (((*(uint *)((&DAT_1212b9c4)[local_18] +
                        (((int)local_1e8 >> 5) +
                         (uint)((int)local_1e8 < 0 && (local_1e8 & 0x1f) != 0) + 0x88) * 4 + 0x14) &
             1 << (local_1e8 +
                   (((int)local_1e8 >> 5) + (uint)((int)local_1e8 < 0 && (local_1e8 & 0x1f) != 0)) *
                   -0x20 & 0x3f)) != 0) &&
           (iVar3 = FUN_1082ecfc(local_18,local_1e8 & 0xffff,0,0x2100), iVar3 < 0)) {
          return iVar3;
        }
      }
    }
  }
  if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
     ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x4202000) != 0)) {
    uVar4 = FUN_11311498();
    if ((uVar4 & 0x10000) == 0) {
      uVar5 = 10000;
    }
    else {
      uVar5 = 250000;
    }
    for (local_1e4 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x2070);
        (-1 < (int)local_1e4 && ((int)local_1e4 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x2074)));
        local_1e4 = local_1e4 + 1) {
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (((int)local_1e4 >> 5) + (uint)((int)local_1e4 < 0 && (local_1e4 & 0x1f) != 0)
                     + 0x81c) * 4 + 8) &
          1 << (local_1e4 +
                (((int)local_1e4 >> 5) + (uint)((int)local_1e4 < 0 && (local_1e4 & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        FUN_10e61f74(local_18,local_1e4);
        iVar3 = FUN_1079a564(local_18,local_1e4);
        if (iVar3 < 0) {
          return iVar3;
        }
        local_b4 = 0;
        FUN_1084c7bc(local_18,0x8fe9,&local_b4,0xdd08,0xf);
        iVar3 = FUN_108499c4(local_18,0x8fe9,local_1e4,0,local_b4);
        if (iVar3 < 0) {
          return iVar3;
        }
      }
    }
    iVar3 = (&DAT_1212b9c4)[local_18];
    local_3c[0] = *(uint *)(iVar3 + 0x488);
    local_3c[1] = *(undefined4 *)(iVar3 + 0x48c);
    local_3c[2] = *(undefined4 *)(iVar3 + 0x490);
    local_3c[3] = *(undefined4 *)(iVar3 + 0x494);
    local_2c = *(undefined4 *)(iVar3 + 0x498);
    local_28 = *(undefined4 *)(iVar3 + 0x49c);
    local_24 = *(undefined4 *)(iVar3 + 0x4a0);
    local_20 = *(undefined4 *)(iVar3 + 0x4a4);
    for (local_1e0 = 0; local_1e0 < 8; local_1e0 = local_1e0 + 1) {
      local_3c[local_1e0] =
           local_3c[local_1e0] & ~*(uint *)((&DAT_1212b9c4)[local_18] + (local_1e0 + 0x81c) * 4 + 8)
      ;
    }
    for (local_1e4 = 0; (int)local_1e4 < 0x100; local_1e4 = local_1e4 + 1) {
      if ((local_3c[((int)local_1e4 >> 5) + (uint)((int)local_1e4 < 0 && (local_1e4 & 0x1f) != 0)] &
          1 << (local_1e4 +
                (((int)local_1e4 >> 5) + (uint)((int)local_1e4 < 0 && (local_1e4 & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        FUN_10e61f74(local_18,local_1e4);
        iVar3 = FUN_1079a564(local_18,local_1e4);
        if (iVar3 < 0) {
          return iVar3;
        }
        break;
      }
    }
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      pcVar1 = *(code **)(&DAT_12124348 + local_18 * 0x78);
      iVar3 = local_18 * 0x78;
      uVar6 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      local_b4 = (*pcVar1)(&DAT_12124314 + iVar3,uVar6);
    }
    else {
      uVar4 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      local_b4 = *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    FUN_1084c7bc(local_18,0x17a6,&local_b4,0x1a5a,1);
    FUN_1084c7bc(local_18,0x17a6,&local_b4,0x1a70,1);
    FUN_1084c7bc(local_18,0x17a6,&local_b4,0x1a83,1);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      pcVar1 = *(code **)(&DAT_1212434c + local_18 * 0x78);
      iVar3 = local_18 * 0x78;
      uVar6 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      (*pcVar1)(&DAT_12124314 + iVar3,uVar6,local_b4);
    }
    else {
      uVar4 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_b4;
    }
    FUN_1032460c(uVar5);
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x400000) != 0)) {
    for (local_1dc = *(uint *)((&DAT_1212b9c4)[local_18] + 0x2070);
        (-1 < (int)local_1dc && ((int)local_1dc <= *(int *)((&DAT_1212b9c4)[local_18] + 0x2074)));
        local_1dc = local_1dc + 1) {
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (((int)local_1dc >> 5) + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0)
                     + 0x81c) * 4 + 8) &
          1 << (local_1dc +
                (((int)local_1dc >> 5) + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        FUN_10e61f74(local_18,local_1dc);
        iVar3 = FUN_1079a564(local_18,local_1dc);
        if (iVar3 < 0) {
          return iVar3;
        }
        local_80 = 0;
        FUN_1084c7bc(local_18,0x8fe9,&local_80,0xdd08,0xf);
        iVar3 = FUN_108499c4(local_18,0x8fe9,local_1dc,0,local_80);
        if (iVar3 < 0) {
          return iVar3;
        }
      }
    }
    for (local_1d8 = 0; local_1d8 < 6; local_1d8 = local_1d8 + 1) {
      auStack_b0[local_1d8] = 0xffffffff;
      auStack_98[local_1d8] = 0;
    }
    for (local_1dc = *(uint *)((&DAT_1212b9c4)[local_18] + 0x276c);
        (-1 < (int)local_1dc && ((int)local_1dc <= *(int *)((&DAT_1212b9c4)[local_18] + 0x2770)));
        local_1dc = local_1dc + 1) {
      iVar3 = (int)local_1dc >> 5;
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (iVar3 + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0) + 0x9d8) * 4 +
                    0x14) &
          1 << (local_1dc + (iVar3 + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0)) * -0x20
               & 0x3f)) != 0) {
        switch(*(undefined4 *)(&DAT_11404694 + local_1dc * 8)) {
        case 0x191b:
          local_1d8 = 0;
          break;
        case 0x191c:
          local_1d8 = 1;
          break;
        case 0x191d:
          local_1d8 = 2;
          break;
        case 0x191e:
          local_1d8 = 3;
          break;
        case 0x191f:
          local_1d8 = 4;
          break;
        case 0x1920:
          local_1d8 = 5;
          break;
        default:
          goto switchD_10e730c8_default;
        }
        if (auStack_b0[local_1d8] == 0xffffffff) {
          auStack_b0[local_1d8] = local_1dc;
        }
        if (((*(uint *)((&DAT_1212b9c4)[local_18] +
                        (iVar3 + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0) + 0x408) * 4
                       + 0xc) &
             1 << (local_1dc +
                   (iVar3 + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0)) * -0x20 & 0x3f))
             == 0) &&
           ((*(uint *)((&DAT_1212b9c4)[local_18] +
                       (iVar3 + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0) + 0x49c) * 4 +
                      0x10) &
            1 << (local_1dc +
                  (iVar3 + (uint)((int)local_1dc < 0 && (local_1dc & 0x1f) != 0)) * -0x20 & 0x3f))
            == 0)) {
          auStack_98[local_1d8] =
               auStack_98[local_1d8] | 1 << (*(uint *)(&DAT_11404698 + local_1dc * 8) & 0x3f);
        }
        else {
          auStack_98[local_1d8] = 0xf;
        }
      }
switchD_10e730c8_default:
    }
    for (local_1d8 = 0; local_1d8 < 6; local_1d8 = local_1d8 + 1) {
      if (auStack_b0[local_1d8] != 0xffffffff) {
        uVar4 = auStack_b0[local_1d8];
        FUN_10e61f74(local_18,uVar4);
        iVar3 = FUN_1079a564(local_18,uVar4);
        if (iVar3 < 0) {
          return iVar3;
        }
        if ((local_1d8 == 1) || (local_1d8 == 4)) {
          uVar5 = 0x8eb1;
        }
        else {
          uVar5 = 0x8eb9;
        }
        local_80 = 0;
        FUN_1084c7bc(local_18,uVar5,&local_80,0xdd08,auStack_98[local_1d8]);
        iVar3 = FUN_108499c4(local_18,uVar5,uVar4,0,local_80);
        if (iVar3 < 0) {
          return iVar3;
        }
      }
    }
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x8000000) != 0)) {
    for (local_1d4 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x2070);
        (-1 < (int)local_1d4 && ((int)local_1d4 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x2074)));
        local_1d4 = local_1d4 + 1) {
      iVar3 = (int)local_1d4 >> 5;
      if (((*(uint *)((&DAT_1212b9c4)[local_18] +
                      (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0) + 0x81c) * 4 +
                     8) &
           1 << (local_1d4 + (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0)) * -0x20
                & 0x3f)) != 0) &&
         ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0) + 0xa70) * 4 + 8
                    ) &
          1 << (local_1d4 + (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0)) * -0x20
               & 0x3f)) == 0)) {
        FUN_10e61f74(local_18,local_1d4);
        iVar3 = FUN_1079a564(local_18,local_1d4);
        if (iVar3 < 0) {
          return iVar3;
        }
        local_4c = 0;
        FUN_1084c7bc(local_18,0x8fe9,&local_4c,0xdd08,0xf);
        iVar3 = FUN_108499c4(local_18,0x8fe9,local_1d4,0,local_4c);
        if (iVar3 < 0) {
          return iVar3;
        }
      }
    }
    for (local_1d0 = 0; local_1d0 < 6; local_1d0 = local_1d0 + 1) {
      auStack_7c[local_1d0] = 0xffffffff;
      auStack_64[local_1d0] = 0;
    }
    for (local_1d4 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x29c0);
        (-1 < (int)local_1d4 && ((int)local_1d4 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x29c4)));
        local_1d4 = local_1d4 + 1) {
      iVar3 = (int)local_1d4 >> 5;
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0) + 0xa70) * 4 + 8
                    ) &
          1 << (local_1d4 + (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0)) * -0x20
               & 0x3f)) != 0) {
        uVar4 = local_1d4 - 0x1e;
        iVar8 = ((int)uVar4 >> 2) + (uint)((int)uVar4 < 0 && (uVar4 & 3) != 0);
        if (auStack_7c[iVar8] == 0xffffffff) {
          auStack_7c[iVar8] = local_1d4;
        }
        if (((*(uint *)((&DAT_1212b9c4)[local_18] +
                        (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0) + 0x408) * 4
                       + 0xc) &
             1 << (local_1d4 +
                   (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0)) * -0x20 & 0x3f))
             == 0) &&
           ((*(uint *)((&DAT_1212b9c4)[local_18] +
                       (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0) + 0x49c) * 4 +
                      0x10) &
            1 << (local_1d4 +
                  (iVar3 + (uint)((int)local_1d4 < 0 && (local_1d4 & 0x1f) != 0)) * -0x20 & 0x3f))
            == 0)) {
          auStack_64[iVar8] = auStack_64[iVar8] | 1 << (local_1d4 - 0x1e & 3);
        }
        else {
          auStack_64[iVar8] = 0xf;
        }
      }
    }
    for (local_1d0 = 0; local_1d0 < 6; local_1d0 = local_1d0 + 1) {
      if (auStack_7c[local_1d0] != 0xffffffff) {
        uVar4 = auStack_7c[local_1d0];
        FUN_10e61f74(local_18,uVar4);
        iVar3 = FUN_1079a564(local_18,uVar4);
        if (iVar3 < 0) {
          return iVar3;
        }
        local_4c = 0;
        FUN_1084c7bc(local_18,0x900c,&local_4c,0xdd08,auStack_64[local_1d0]);
        iVar3 = FUN_108499c4(local_18,0x900c,uVar4,0,local_4c);
        if (iVar3 < 0) {
          return iVar3;
        }
      }
    }
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x1c000) != 0)) {
    uVar4 = FUN_11311498();
    if ((uVar4 & 0x10000) == 0) {
      uVar5 = 10000;
    }
    else {
      uVar5 = 250000;
    }
    for (local_1cc = *(uint *)((&DAT_1212b9c4)[local_18] + 0x2070);
        (-1 < (int)local_1cc && ((int)local_1cc <= *(int *)((&DAT_1212b9c4)[local_18] + 0x2074)));
        local_1cc = local_1cc + 1) {
      if (((*(uint *)((&DAT_1212b9c4)[local_18] +
                      (((int)local_1cc >> 5) + (uint)((int)local_1cc < 0 && (local_1cc & 0x1f) != 0)
                      + 0x81c) * 4 + 8) &
           1 << (local_1cc +
                 (((int)local_1cc >> 5) + (uint)((int)local_1cc < 0 && (local_1cc & 0x1f) != 0)) *
                 -0x20 & 0x3f)) != 0) && (iVar3 = FUN_10e90300(local_18,local_1cc), iVar3 < 0)) {
        return iVar3;
      }
    }
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      pcVar1 = *(code **)(&DAT_12124348 + local_18 * 0x78);
      iVar3 = local_18 * 0x78;
      uVar6 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      local_48 = (*pcVar1)(&DAT_12124314 + iVar3,uVar6);
    }
    else {
      uVar4 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      local_48 = *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78));
    }
    FUN_1084c7bc(local_18,0x17a6,&local_48,0x1a50,1);
    FUN_1084c7bc(local_18,0x17a6,&local_48,0x1a70,1);
    FUN_1084c7bc(local_18,0x17a6,&local_48,0x1a5a,1);
    FUN_1084c7bc(local_18,0x17a6,&local_48,0x1a83,1);
    FUN_1084c7bc(local_18,0x17a6,&local_48,0x1abb,1);
    if (*(int *)(&DAT_12124344 + local_18 * 0x78) == 0) {
      pcVar1 = *(code **)(&DAT_1212434c + local_18 * 0x78);
      iVar3 = local_18 * 0x78;
      uVar6 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      (*pcVar1)(&DAT_12124314 + iVar3,uVar6,local_48);
    }
    else {
      uVar4 = FUN_1084e2b0(local_18,0x17a6,0xfffffff6,0);
      *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_18 * 0x78)) = local_48;
    }
    FUN_1032460c(uVar5);
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0xc) != 0)) {
    iVar3 = FUN_10f31794(local_18);
    if (iVar3 < 0) {
      return iVar3;
    }
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x5000000c) != 0)) {
    iVar3 = (&DAT_1212b9c4)[local_18];
    uVar5 = *(undefined4 *)(iVar3 + 0x8460);
    uVar6 = *(undefined4 *)(iVar3 + 0x7218);
    *(undefined4 *)(iVar3 + 0x7218) = 0x23;
    local_1c8 = 0;
LAB_10e74188:
    if (-1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1c8 * 0x10)) {
      if ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                   local_1c8 * 0x10) == 0x23) &&
         (*(char *)((&DAT_1212b9c4)[local_18] + local_1c8 + 0x909c) == '\0')) {
        local_1c4 = 0;
        do {
          if (*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) < 2) {
            iVar8 = local_1c4 << 3;
          }
          else {
            iVar8 = *(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) * local_1c4 * 8;
          }
          if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x34) + iVar8) ==
              local_1c8) goto LAB_10e74120;
          if (*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) < 2) {
            iVar8 = local_1c4 << 3;
          }
          else {
            iVar8 = *(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) * local_1c4 * 8;
          }
          if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x34) + iVar8) < 0)
          {
            if (*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) < 2) {
              iVar8 = local_1c4 << 3;
            }
            else {
              iVar8 = *(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) * local_1c4 *
                      8;
            }
            if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x34) + iVar8 + 4
                        ) < 0) goto code_r0x10e74100;
          }
          local_1c4 = local_1c4 + 1;
        } while( true );
      }
      goto LAB_10e7417c;
    }
LAB_10e741cc:
    local_1c8 = 0;
LAB_10e744b4:
    if (-1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1c8 * 0x10)) {
      if ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                   local_1c8 * 0x10) == 0x23) &&
         (*(char *)((&DAT_1212b9c4)[local_18] + local_1c8 + 0x909c) == '\0')) {
        local_1c4 = 0;
        do {
          if (*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) < 2) {
            iVar8 = local_1c4 << 3;
          }
          else {
            iVar8 = *(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) * local_1c4 * 8;
          }
          if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x34) + iVar8) ==
              local_1c8) goto LAB_10e7444c;
          if (*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) < 2) {
            iVar8 = local_1c4 << 3;
          }
          else {
            iVar8 = *(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) * local_1c4 * 8;
          }
          if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x34) + iVar8) < 0)
          {
            if (*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) < 2) {
              iVar8 = local_1c4 << 3;
            }
            else {
              iVar8 = *(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x48) * local_1c4 *
                      8;
            }
            if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x34) + iVar8 + 4
                        ) < 0) goto code_r0x10e7442c;
          }
          local_1c4 = local_1c4 + 1;
        } while( true );
      }
      goto LAB_10e744a8;
    }
LAB_10e744f8:
    *(undefined4 *)(iVar3 + 0x8460) = uVar5;
    *(undefined4 *)(iVar3 + 0x7218) = uVar6;
    for (local_1c8 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1c8 * 0x10); local_1c8 = local_1c8 + 1) {
      if ((*(char *)((&DAT_1212b9c4)[local_18] + local_1c8 + 0x909c) != '\0') &&
         ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                   local_1c8 * 0x10) == 0x23 ||
          (iVar8 = FUN_10761b44(local_18,local_1c8,0x23), iVar8 != 0)))) {
        uVar5 = *(undefined4 *)((&DAT_1212b9c4)[local_18] + (local_1c8 + 0x2604) * 4 + 8);
        FUN_10e61f74(local_18,uVar5);
        iVar8 = FUN_1079c130(local_18,uVar5,0);
        if (iVar8 < 0) {
          return iVar8;
        }
      }
    }
    for (local_1c8 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1c8 * 0x10); local_1c8 = local_1c8 + 1) {
      if ((*(char *)((&DAT_1212b9c4)[local_18] + local_1c8 + 0x909c) != '\0') &&
         (((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                    local_1c8 * 0x10) == 0x23 ||
           (iVar8 = FUN_10761b44(local_18,local_1c8,0x23), iVar8 != 0)) &&
          (iVar8 = FUN_1079cb8c(local_18,*(undefined4 *)
                                          ((&DAT_1212b9c4)[local_18] + (local_1c8 + 0x2604) * 4 + 8)
                                ,0), iVar8 < 0)))) {
        return iVar8;
      }
    }
    for (local_1c8 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1c8 * 0x10); local_1c8 = local_1c8 + 1) {
      if (((*(char *)((&DAT_1212b9c4)[local_18] + local_1c8 + 0x909c) != '\0') &&
          ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                    local_1c8 * 0x10) == 0x23 ||
           (iVar8 = FUN_10761b44(local_18,local_1c8,0x23), iVar8 != 0)))) &&
         (iVar8 = *(int *)((&DAT_1212b9c4)[local_18] + (local_1c8 + 0x2604) * 4 + 8),
         9999 < *(int *)(iVar3 + 4 + (iVar8 + 0x1894) * 4))) {
        iVar7 = FUN_10846cf4(local_18,0x8f58,iVar8,0,&local_44);
        if (iVar7 < 0) {
          return iVar7;
        }
        FUN_1084c7bc(local_18,0x8f58,&local_44,0xf1ad,1);
        iVar7 = FUN_108499c4(local_18,0x8f58,iVar8,0,local_44);
        if (iVar7 < 0) {
          return iVar7;
        }
        FUN_10324684(10);
        FUN_1084c7bc(local_18,0x8f58,&local_44,0xf1ad,0);
        iVar8 = FUN_108499c4(local_18,0x8f58,iVar8,0,local_44);
        if (iVar8 < 0) {
          return iVar8;
        }
      }
    }
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x80000) != 0 ||
           ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)))) {
    iVar3 = (&DAT_1212b9c4)[local_18];
    iVar8 = iVar3 + 4;
    for (local_1b4 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1b4 * 0x10); local_1b4 = local_1b4 + 1) {
      if ((*(char *)((&DAT_1212b9c4)[local_18] + local_1b4 + 0x909c) != '\0') &&
         ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                   local_1b4 * 0x10) == 0x29 ||
          (iVar7 = FUN_10761b44(local_18,local_1b4,0x29), iVar7 != 0)))) {
        local_1b0 = 0;
        bVar2 = false;
        local_1ac = -1;
        for (local_1bc = 0; (int)local_1bc < 3; local_1bc = local_1bc + 1) {
          for (local_1b8 = 0; local_1b8 < 4; local_1b8 = local_1b8 + 1) {
            local_1c0 = *(int *)(iVar8 + (*(int *)(*(int *)(iVar3 + 0xe0b4) + local_1b4 * 4) +
                                          local_1bc * 4 + local_1b8 + 0x2010) * 4 + 8);
            if (((((local_1c0 < 0) || (0x81 < local_1c0)) ||
                 (*(int *)((&DAT_1212b9c4)[local_18] + (local_1c0 + 0x1c84) * 4 + 4) == 0)) ||
                (iVar7 = local_1c0, *(int *)(iVar8 + (local_1c0 + 0x1894) * 4) < 100000)) &&
               (iVar7 = local_1ac, -1 < local_1ac)) {
              local_1c0 = local_1ac;
            }
            local_1ac = iVar7;
            if (((-1 < local_1c0) && (local_1c0 < 0x82)) &&
               (*(int *)((&DAT_1212b9c4)[local_18] + (local_1c0 + 0x1c84) * 4 + 4) != 0)) {
              iVar7 = FUN_1079c130(local_18,local_1c0,local_1bc);
              if (iVar7 < 0) {
                return iVar7;
              }
              local_1b0 = local_1b0 | 1 << (local_1bc & 0x3f);
              if (((local_1bc != 0) && (!bVar2)) &&
                 (iVar7 = FUN_1079c130(local_18,local_1c0,0), iVar7 < 0)) {
                return iVar7;
              }
              bVar2 = true;
              break;
            }
          }
        }
        if (local_1b0 != 0) {
          uVar5 = *(undefined4 *)((&DAT_1212b9c4)[local_18] + (local_1b4 + 0x2604) * 4 + 8);
          iVar7 = FUN_10846cf4(local_18,0x6e24,uVar5,0,&local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          if ((((local_c0 == -0x49c0) || (local_c0 == -0x4fbc)) || (local_c0 == -0x4abd)) &&
             (-1 < local_1ac)) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0x1a08,1);
          }
          if ((local_1b0 & 1) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,1);
          }
          if ((local_1b0 & 2) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf197,1);
          }
          if ((local_1b0 & 4) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf19a,1);
          }
          iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          FUN_10324684(10);
          if ((((local_c0 == -0x49c0) || (local_c0 == -0x4fbc)) || (local_c0 == -0x4abd)) &&
             (-1 < local_1ac)) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0x1a08,0);
          }
          if ((local_1b0 & 1) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,0);
          }
          if ((local_1b0 & 2) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf197,0);
          }
          if ((local_1b0 & 4) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf19a,0);
          }
          iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          iVar7 = FUN_10846cf4(local_18,0x6e37,uVar5,0,&local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          FUN_1084c7bc(local_18,0x6e37,&local_40,0xb95b,1);
          FUN_1084c7bc(local_18,0x6e37,&local_40,0xb95a,1);
          iVar7 = FUN_108499c4(local_18,0x6e37,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
        }
      }
    }
    for (local_1b4 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1b4 * 0x10); local_1b4 = local_1b4 + 1) {
      if ((*(char *)((&DAT_1212b9c4)[local_18] + local_1b4 + 0x909c) != '\0') &&
         ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                   local_1b4 * 0x10) == 0x2a ||
          (iVar7 = FUN_10761b44(local_18,local_1b4,0x2a), iVar7 != 0)))) {
        local_1b0 = 0;
        for (local_1bc = 0; (int)local_1bc < 3; local_1bc = local_1bc + 1) {
          for (local_1b8 = 0; local_1b8 < 4; local_1b8 = local_1b8 + 1) {
            iVar7 = *(int *)(iVar8 + (*(int *)(*(int *)(iVar3 + 0xe0b4) + local_1b4 * 4) +
                                      local_1bc * 4 + local_1b8 + 0x2010) * 4 + 8);
            if (((-1 < iVar7) && (iVar7 < 0x82)) &&
               (*(int *)((&DAT_1212b9c4)[local_18] + (iVar7 + 0x1c84) * 4 + 4) != 0)) {
              iVar7 = FUN_1079c130(local_18,iVar7,local_1bc);
              if (iVar7 < 0) {
                return iVar7;
              }
              local_1b0 = local_1b0 | 1 << (local_1bc & 0x3f);
              break;
            }
          }
        }
        if (local_1b0 != 0) {
          uVar5 = *(undefined4 *)((&DAT_1212b9c4)[local_18] + (local_1b4 + 0x2604) * 4 + 8);
          iVar7 = FUN_10846cf4(local_18,0x6e24,uVar5,0,&local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          if ((local_1b0 & 1) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,1);
          }
          if ((local_1b0 & 2) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf197,1);
          }
          if ((local_1b0 & 4) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf19a,1);
          }
          iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          FUN_10324684(10);
          if ((local_1b0 & 1) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,0);
          }
          if ((local_1b0 & 2) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf197,0);
          }
          if ((local_1b0 & 4) != 0) {
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf19a,0);
          }
          iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
        }
      }
    }
    for (local_1b4 = 0;
        -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1b4 * 0x10); local_1b4 = local_1b4 + 1) {
      if ((*(char *)((&DAT_1212b9c4)[local_18] + local_1b4 + 0x909c) != '\0') &&
         ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                   local_1b4 * 0x10) == 0x23 ||
          (iVar7 = FUN_10761b44(local_18,local_1b4,0x23), iVar7 != 0)))) {
        bVar2 = false;
        for (local_1b8 = 0; local_1b8 < 4; local_1b8 = local_1b8 + 1) {
          iVar7 = *(int *)(iVar8 + (*(int *)(*(int *)(iVar3 + 0xe0b4) + local_1b4 * 4) + local_1b8 +
                                   0x2010) * 4 + 8);
          if (((-1 < iVar7) && (iVar7 < 0x82)) &&
             (*(int *)((&DAT_1212b9c4)[local_18] + (iVar7 + 0x1c84) * 4 + 4) != 0)) {
            bVar2 = true;
            break;
          }
        }
        if (bVar2) {
          uVar5 = *(undefined4 *)((&DAT_1212b9c4)[local_18] + (local_1b4 + 0x2604) * 4 + 8);
          iVar7 = FUN_1079a564(local_18,uVar5);
          if (iVar7 < 0) {
            return iVar7;
          }
          iVar7 = FUN_10846cf4(local_18,0x6e24,uVar5,0,&local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,1);
          iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
          FUN_10324684(10);
          FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,0);
          iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
          if (iVar7 < 0) {
            return iVar7;
          }
        }
      }
    }
    if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0) {
      for (local_1b4 = 0;
          -1 < *(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                       local_1b4 * 0x10); local_1b4 = local_1b4 + 1) {
        if ((*(char *)((&DAT_1212b9c4)[local_18] + local_1b4 + 0x909c) != '\0') &&
           ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                     local_1b4 * 0x10) == 0x5f ||
            (iVar7 = FUN_10761b44(local_18,local_1b4,0x5f), iVar7 != 0)))) {
          bVar2 = false;
          for (local_1b8 = 0; local_1b8 < 4; local_1b8 = local_1b8 + 1) {
            iVar7 = *(int *)(iVar8 + (*(int *)(*(int *)(iVar3 + 0xe0b4) + local_1b4 * 4) + local_1b8
                                     + 0x2010) * 4 + 8);
            if (((-1 < iVar7) && (iVar7 < 0x82)) &&
               (*(int *)((&DAT_1212b9c4)[local_18] + (iVar7 + 0x1c84) * 4 + 4) != 0)) {
              bVar2 = true;
              break;
            }
          }
          if (bVar2) {
            uVar5 = *(undefined4 *)((&DAT_1212b9c4)[local_18] + (local_1b4 + 0x2604) * 4 + 8);
            iVar7 = FUN_1079a564(local_18,uVar5);
            if (iVar7 < 0) {
              return iVar7;
            }
            iVar7 = FUN_10846cf4(local_18,0x6e24,uVar5,0,&local_40);
            if (iVar7 < 0) {
              return iVar7;
            }
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,1);
            iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
            if (iVar7 < 0) {
              return iVar7;
            }
            FUN_10324684(10);
            FUN_1084c7bc(local_18,0x6e24,&local_40,0xf194,0);
            iVar7 = FUN_108499c4(local_18,0x6e24,uVar5,0,local_40);
            if (iVar7 < 0) {
              return iVar7;
            }
          }
        }
      }
    }
  }
  else {
    for (local_1a4 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x1278);
        (-1 < (int)local_1a4 && ((int)local_1a4 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x127c)));
        local_1a4 = local_1a4 + 1) {
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (((int)local_1a4 >> 5) + (uint)((int)local_1a4 < 0 && (local_1a4 & 0x1f) != 0)
                     + 0x49c) * 4 + 0x10) &
          1 << (local_1a4 +
                (((int)local_1a4 >> 5) + (uint)((int)local_1a4 < 0 && (local_1a4 & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        FUN_10e61f74(local_18,local_1a4);
        FUN_1088b69c(local_18,local_1a4);
      }
    }
    for (local_1a4 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x1024);
        (-1 < (int)local_1a4 && ((int)local_1a4 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x1028)));
        local_1a4 = local_1a4 + 1) {
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (((int)local_1a4 >> 5) + (uint)((int)local_1a4 < 0 && (local_1a4 & 0x1f) != 0)
                     + 0x408) * 4 + 0xc) &
          1 << (local_1a4 +
                (((int)local_1a4 >> 5) + (uint)((int)local_1a4 < 0 && (local_1a4 & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        FUN_10e61f74(local_18,local_1a4);
        FUN_1088b69c(local_18,local_1a4);
      }
    }
  }
  return 0;
code_r0x10e74100:
  local_1c4 = -1;
LAB_10e74120:
  if (-1 < local_1c4) {
    *(int *)(iVar3 + 0x8460) = local_1c4;
    iVar8 = FUN_1079c130(local_18,1,0);
    if (iVar8 < 0) goto LAB_10e741cc;
  }
LAB_10e7417c:
  local_1c8 = local_1c8 + 1;
  goto LAB_10e74188;
code_r0x10e7442c:
  local_1c4 = -1;
LAB_10e7444c:
  if (-1 < local_1c4) {
    *(int *)(iVar3 + 0x8460) = local_1c4;
    iVar8 = FUN_1079ce38(local_18,1,0);
    if (iVar8 < 0) goto LAB_10e744f8;
  }
LAB_10e744a8:
  local_1c8 = local_1c8 + 1;
  goto LAB_10e744b4;
}



/* === FUN_10e58d90 (size=22724) === */

int FUN_10e58d90(int param_1,int param_2)

{
  short sVar1;
  ushort uVar2;
  uint *puVar3;
  code *pcVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  char cVar16;
  size_t sVar11;
  int iVar12;
  undefined2 uVar15;
  int iVar13;
  int iVar14;
  int local_248;
  uint local_244;
  uint local_240;
  int local_23c;
  char local_238;
  byte local_237;
  int local_234;
  int local_230;
  int local_22c;
  int local_228;
  int local_224;
  uint local_220;
  uint local_118;
  undefined2 local_114 [2];
  undefined4 local_110;
  int local_10c;
  uint local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined1 auStack_f8 [4];
  undefined1 auStack_f4 [20];
  undefined1 auStack_e0 [4];
  uint local_dc [3];
  uint local_d0;
  uint local_cc;
  uint local_c8;
  uint local_c4;
  uint local_c0;
  int local_58;
  int local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  local_240 = 0xffffffff;
  local_110 = 0;
  local_10c = 0;
  local_108 = 0;
  local_58 = param_1;
  local_54 = param_2;
  if (((param_1 < 0) || (0x11 < param_1)) || ((&DAT_1212b9c4)[param_1] == 0)) {
    FUN_10760cd4(0x200000,"soc_init: unit %d not valid\n",param_1);
    return -3;
  }
  puVar3 = (uint *)(&DAT_1212b9c4)[param_1];
  iVar12 = (&DAT_1212ba0c)[param_1];
  if ((*puVar3 & 1) == 0) {
    FUN_10760cd4(0x200000,"soc_init: unit %d not attached\n",param_1);
    return -3;
  }
  if (*(int *)(&DAT_1212ba54 + param_1 * 4) == 1) {
    if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c40) & 2) != 0) &&
       ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c40) & 0x1000) != 0)) {
      iVar9 = *(int *)((&DAT_1212b9c4)[param_1] + 0xe1fc);
      if (*(int *)(&DAT_12124344 + param_1 * 0x78) == 0) {
        local_118 = (**(code **)(&DAT_12124348 + param_1 * 0x78))
                              (&DAT_12124314 + param_1 * 0x78,iVar9 * 0x1000 + 0x31404);
      }
      else {
        local_118 = *(uint *)((iVar9 * 0x1000 + 0x31404 >> 2) * 4 +
                             *(int *)(&DAT_12124344 + param_1 * 0x78));
      }
      iVar7 = FUN_1084b1d8(local_58,0xc81,local_118,0x968d);
      if ((iVar7 != 0) || (iVar7 = FUN_1084b1d8(local_58,0xc81,local_118,0x9696), iVar7 != 0)) {
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          pcVar4 = *(code **)(&DAT_12124348 + local_58 * 0x78);
          iVar7 = local_58 * 0x78;
          uVar10 = FUN_1084e2b0(local_58,0x14e4,0xfffffff6,0);
          local_118 = (*pcVar4)(&DAT_12124314 + iVar7,uVar10);
        }
        else {
          uVar8 = FUN_1084e2b0(local_58,0x14e4,0xfffffff6,0);
          local_118 = *(uint *)((uVar8 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_58 * 0x78));
        }
        FUN_1084c7bc(local_58,0x14e4,&local_118,0xe2aa,1);
        FUN_1084c7bc(local_58,0x14e4,&local_118,0xe2a9,1);
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          pcVar4 = *(code **)(&DAT_1212434c + local_58 * 0x78);
          iVar7 = local_58 * 0x78;
          uVar10 = FUN_1084e2b0(local_58,0x14e4,0xfffffff6,0);
          (*pcVar4)(&DAT_12124314 + iVar7,uVar10,local_118);
        }
        else {
          uVar8 = FUN_1084e2b0(local_58,0x14e4,0xfffffff6,0);
          *(uint *)((uVar8 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_58 * 0x78)) = local_118;
        }
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          local_118 = (**(code **)(&DAT_12124348 + local_58 * 0x78))
                                (&DAT_12124314 + local_58 * 0x78,iVar9 * 0x1000 + 0x31600);
        }
        else {
          local_118 = *(uint *)((iVar9 * 0x1000 + 0x31600 >> 2) * 4 +
                               *(int *)(&DAT_12124344 + local_58 * 0x78));
        }
        FUN_1084c7bc(local_58,0xc9e,&local_118,0x10,1);
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          (**(code **)(&DAT_1212434c + local_58 * 0x78))
                    (&DAT_12124314 + local_58 * 0x78,iVar9 * 0x1000 + 0x31600,local_118);
        }
        else {
          *(uint *)((iVar9 * 0x1000 + 0x31600 >> 2) * 4 + *(int *)(&DAT_12124344 + local_58 * 0x78))
               = local_118;
        }
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          local_118 = (**(code **)(&DAT_12124348 + local_58 * 0x78))
                                (&DAT_12124314 + local_58 * 0x78,iVar9 * 0x1000 + 0x31650);
        }
        else {
          local_118 = *(uint *)((iVar9 * 0x1000 + 0x31650 >> 2) * 4 +
                               *(int *)(&DAT_12124344 + local_58 * 0x78));
        }
        FUN_1084c7bc(local_58,0xc9e,&local_118,0x10,1);
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          (**(code **)(&DAT_1212434c + local_58 * 0x78))
                    (&DAT_12124314 + local_58 * 0x78,iVar9 * 0x1000 + 0x31650,local_118);
        }
        else {
          *(uint *)((iVar9 * 0x1000 + 0x31650 >> 2) * 4 + *(int *)(&DAT_12124344 + local_58 * 0x78))
               = local_118;
        }
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          local_118 = (**(code **)(&DAT_12124348 + local_58 * 0x78))
                                (&DAT_12124314 + local_58 * 0x78,iVar9 * 0x1000 + 0x316a0);
        }
        else {
          local_118 = *(uint *)((iVar9 * 0x1000 + 0x316a0 >> 2) * 4 +
                               *(int *)(&DAT_12124344 + local_58 * 0x78));
        }
        FUN_1084c7bc(local_58,0xc9e,&local_118,0x10,1);
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          (**(code **)(&DAT_1212434c + local_58 * 0x78))
                    (&DAT_12124314 + local_58 * 0x78,iVar9 * 0x1000 + 0x316a0,local_118);
        }
        else {
          *(uint *)((iVar9 * 0x1000 + 0x316a0 >> 2) * 4 + *(int *)(&DAT_12124344 + local_58 * 0x78))
               = local_118;
        }
        iVar9 = FUN_1085c36c(local_58,0);
        if (iVar9 < 0) {
          return iVar9;
        }
        iVar9 = FUN_1085c36c(local_58,1);
        if (iVar9 < 0) {
          return iVar9;
        }
        iVar9 = FUN_1085c36c(local_58,2);
        if (iVar9 < 0) {
          return iVar9;
        }
        iVar9 = FUN_1085c36c(local_58,3);
        if (iVar9 < 0) {
          return iVar9;
        }
      }
      if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
        pcVar4 = *(code **)(&DAT_12124348 + local_58 * 0x78);
        iVar9 = local_58 * 0x78;
        uVar10 = FUN_1084e2b0(local_58,0x14e2,0xfffffff6,0);
        local_118 = (*pcVar4)(&DAT_12124314 + iVar9,uVar10);
      }
      else {
        uVar8 = FUN_1084e2b0(local_58,0x14e2,0xfffffff6,0);
        local_118 = *(uint *)((uVar8 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_58 * 0x78));
      }
      if (local_118 != 0) {
        FUN_10760cd4(0x10000,"Unit %d: PCIE purge clear 0x%08x.\n",local_58,local_118);
        if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
          pcVar4 = *(code **)(&DAT_1212434c + local_58 * 0x78);
          iVar9 = local_58 * 0x78;
          uVar10 = FUN_1084e2b0(local_58,0x14e1,0xfffffff6,0);
          (*pcVar4)(&DAT_12124314 + iVar9,uVar10,0);
        }
        else {
          uVar8 = FUN_1084e2b0(local_58,0x14e1,0xfffffff6,0);
          *(undefined4 *)((uVar8 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_58 * 0x78)) = 0;
        }
      }
    }
    if ((((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) &&
        (iVar9 = FUN_1078bf64(local_58), iVar9 < 0)) &&
       (iVar9 = FUN_10799c5c(local_58,10,0,0,0), iVar9 < 0)) {
      return iVar9;
    }
    *puVar3 = *puVar3 | 4;
    for (local_23c = 0; local_23c < 8; local_23c = local_23c + 1) {
      local_dc[local_23c] = 0;
    }
    local_50 = local_dc[0];
    local_4c = local_dc[1];
    local_48 = local_dc[2];
    local_44 = local_d0;
    local_40 = local_cc;
    local_3c = local_c8;
    local_38 = local_c4;
    local_34 = local_c0;
    local_30 = local_dc[0];
    local_2c = local_dc[1];
    local_28 = local_dc[2];
    local_24 = local_d0;
    local_20 = local_cc;
    local_1c = local_c8;
    local_18 = local_c4;
    local_14 = local_c0;
    iVar9 = FUN_107d788c(local_58,&local_50,&local_30);
    if (iVar9 < 0) {
      return iVar9;
    }
  }
  if ((*puVar3 & 2) != 0) {
    if (((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) &&
       (iVar9 = FUN_1078bf64(local_58), iVar9 < 0)) {
      return iVar9;
    }
    iVar9 = FUN_107873e8(local_58);
    if (iVar9 < 0) {
      return iVar9;
    }
    iVar9 = FUN_10825c94(local_58);
    if (iVar9 < 0) {
      return iVar9;
    }
    iVar9 = FUN_112fae7c(local_58);
    if (iVar9 < 0) {
      return iVar9;
    }
    if (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c08) & 2) != 0) &&
       (iVar9 = FUN_10eb8ddc(local_58), iVar9 < 0)) {
      return iVar9;
    }
    if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
       ((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x80000) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)) &&
        (iVar9 = FUN_112184c4(local_58), iVar9 < 0)))) {
      return iVar9;
    }
    if (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
        ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 4) != 0)) &&
       (iVar9 = FUN_1127f978(local_58), iVar9 < 0)) {
      return iVar9;
    }
    if (puVar3[0xbc649] != 0) {
      FUN_11311c0c(puVar3[0xbc64c],0xffffffff);
      FUN_112cef24(puVar3[0xbc649]);
      FUN_11311d68(puVar3[0xbc64c]);
    }
    if (puVar3[0xbc9c5] != 0) {
      FUN_11311b9c(puVar3[0xbc9c5]);
      puVar3[0xbc9c5] = 0;
    }
    if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 2) != 0) {
      FUN_10877b8c(local_58);
    }
    *puVar3 = *puVar3 & 0xfffffffd;
  }
  if (*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) {
    iVar9 = FUN_1085f110(local_58);
    if (iVar9 < 0) {
      iVar9 = FUN_1085fef8(local_58,0);
      if (iVar9 < 0) {
        return iVar9;
      }
      iVar9 = FUN_1085fd40(local_58,0,0);
      if (iVar9 < 0) {
        return iVar9;
      }
      uVar10 = FUN_10860354(local_58);
      iVar9 = FUN_10799c5c(local_58,9,1,uVar10,0);
      if (iVar9 < 0) {
        return iVar9;
      }
      FUN_10760cd4(0x8000000,"Unit %d: Corrupt stable cache.\n",local_58);
    }
    else {
      iVar9 = FUN_107f3ae4(local_58);
      if (iVar9 < 0) {
        return iVar9;
      }
    }
  }
  iVar9 = FUN_10e414f4(local_58,puVar3);
  if (iVar9 < 0) {
    return iVar9;
  }
  if ((*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) && (iVar9 = FUN_10e57ad4(local_58), iVar9 < 0))
  {
    return iVar9;
  }
  FUN_107b34b4(local_58);
  FUN_112ade30(local_58);
  if ((*(int *)(&DAT_1212ba54 + local_58 * 4) != 1) &&
     ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0)) {
    FUN_10797cc8(local_58);
    FUN_10798e38(local_58,0xffffffff);
  }
  if ((((local_54 != 0) && (*(int *)(&DAT_1212ba54 + local_58 * 4) != 1)) &&
      ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0)) &&
     ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 2) != 0)) {
    iVar9 = *(int *)((&DAT_1212b9c4)[local_58] + 0xe1fc) * 0x1000 + 0x31470;
    if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
      local_104 = (**(code **)(&DAT_12124348 + local_58 * 0x78))
                            (&DAT_12124314 + local_58 * 0x78,iVar9);
    }
    else {
      local_104 = *(undefined4 *)(iVar9 + *(int *)(&DAT_12124344 + local_58 * 0x78));
    }
    FUN_1084c7bc(local_58,0xc8f,&local_104,0x3f53,1);
    if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
      (**(code **)(&DAT_1212434c + local_58 * 0x78))
                (&DAT_12124314 + local_58 * 0x78,iVar9,local_104);
    }
    else {
      *(undefined4 *)(iVar9 + *(int *)(&DAT_12124344 + local_58 * 0x78)) = local_104;
    }
  }
  if ((((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) && ((*puVar3 & 2) == 0)) &&
     ((uVar8 = FUN_10760950(local_58), (uVar8 & 1) != 0 &&
      ((uVar8 = FUN_11311498(), (uVar8 & 0xa0000) == 0 &&
       (uVar8 = FUN_11311498(), (uVar8 & 0x400000) == 0)))))) {
    local_238 = '\0';
    sVar1 = *(short *)((&DAT_1212b9c4)[local_58] + 0x5b68);
    if (sVar1 != 0) {
      if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x20) == 0) {
        iVar9 = FUN_10e580fc(local_58,sVar1);
      }
      else {
        iVar9 = FUN_10e5830c(local_58,sVar1);
      }
      if (iVar9 < 0) {
        s_mem_nocache__114041ac[0] = SUB41(s_mem_nocache__114041ac._0_4_,3);
        s_mem_nocache__114041ac[1] = SUB41(s_mem_nocache__114041ac._0_4_,2);
        s_mem_nocache__114041ac[2] = SUB41(s_mem_nocache__114041ac._0_4_,1);
        s_mem_nocache__114041ac[3] = (char)s_mem_nocache__114041ac._0_4_;
        s_mem_nocache__114041ac[4] = SUB41(s_mem_nocache__114041ac._4_4_,3);
        s_mem_nocache__114041ac[5] = SUB41(s_mem_nocache__114041ac._4_4_,2);
        s_mem_nocache__114041ac[6] = SUB41(s_mem_nocache__114041ac._4_4_,1);
        s_mem_nocache__114041ac[7] = (char)s_mem_nocache__114041ac._4_4_;
        s_mem_nocache__114041ac[8] = SUB41(s_mem_nocache__114041ac._8_4_,3);
        s_mem_nocache__114041ac[9] = SUB41(s_mem_nocache__114041ac._8_4_,2);
        s_mem_nocache__114041ac[10] = SUB41(s_mem_nocache__114041ac._8_4_,1);
        s_mem_nocache__114041ac[0xb] = (char)s_mem_nocache__114041ac._8_4_;
        return iVar9;
      }
    }
    local_237 = (**(code **)(&DAT_12124350 + local_58 * 0x78))(&DAT_12124314 + local_58 * 0x78,0x34)
    ;
    while ((0x3f < local_237 && (local_237 != 0xff))) {
      uVar8 = (**(code **)(&DAT_12124350 + local_58 * 0x78))
                        (&DAT_12124314 + local_58 * 0x78,local_237);
      local_238 = (char)uVar8;
      if ((uVar8 & 0xff) == 0x10) break;
      local_237 = (byte)(uVar8 >> 8);
    }
    if ((((local_238 == '\x10') &&
         (uVar8 = (**(code **)(&DAT_12124350 + local_58 * 0x78))
                            (&DAT_12124314 + local_58 * 0x78,local_237 + 0x10),
         (uVar8 & 0xf0000) == 0x20000)) &&
        (uVar8 = (**(code **)(&DAT_12124350 + local_58 * 0x78))
                           (&DAT_12124314 + local_58 * 0x78,local_237 + 0x30),
        (uVar8 & 0x10000) != 0)) && (sVar1 != 0)) {
      if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x20) == 0) {
        if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 2) == 0) {
          iVar9 = FUN_10e581dc(local_58,sVar1);
        }
        else {
          iVar9 = FUN_10e57b4c(local_58,sVar1);
        }
      }
      else {
        iVar9 = FUN_10e585ec(local_58,sVar1);
      }
      if (iVar9 < 0) {
        s_mem_nocache__114041ac[0] = SUB41(s_mem_nocache__114041ac._0_4_,3);
        s_mem_nocache__114041ac[1] = SUB41(s_mem_nocache__114041ac._0_4_,2);
        s_mem_nocache__114041ac[2] = SUB41(s_mem_nocache__114041ac._0_4_,1);
        s_mem_nocache__114041ac[3] = (char)s_mem_nocache__114041ac._0_4_;
        s_mem_nocache__114041ac[4] = SUB41(s_mem_nocache__114041ac._4_4_,3);
        s_mem_nocache__114041ac[5] = SUB41(s_mem_nocache__114041ac._4_4_,2);
        s_mem_nocache__114041ac[6] = SUB41(s_mem_nocache__114041ac._4_4_,1);
        s_mem_nocache__114041ac[7] = (char)s_mem_nocache__114041ac._4_4_;
        s_mem_nocache__114041ac[8] = SUB41(s_mem_nocache__114041ac._8_4_,3);
        s_mem_nocache__114041ac[9] = SUB41(s_mem_nocache__114041ac._8_4_,2);
        s_mem_nocache__114041ac[10] = SUB41(s_mem_nocache__114041ac._8_4_,1);
        s_mem_nocache__114041ac[0xb] = (char)s_mem_nocache__114041ac._8_4_;
        return iVar9;
      }
    }
  }
  if ((*(int *)(&DAT_1212ba54 + local_58 * 4) != 1) &&
     ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0)) {
    FUN_10797b20(local_58);
  }
  if (((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) &&
     (iVar9 = FUN_107920d8(local_58,local_54), iVar9 < 0)) {
    return -1;
  }
  iVar9 = FUN_10837850(local_58);
  if (iVar9 < 0) {
    return iVar9;
  }
  if (((local_54 != 0) && (*(int *)(&DAT_1212ba54 + local_58 * 4) != 1)) &&
     ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0)) {
    iVar9 = FUN_10e7153c(local_58);
    if (iVar9 < 0) {
      return iVar9;
    }
    if (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 2) != 0) &&
       ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x1000) != 0)) {
      if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
        pcVar4 = *(code **)(&DAT_12124348 + local_58 * 0x78);
        iVar9 = local_58 * 0x78;
        uVar10 = FUN_1084e2b0(local_58,0x14e1,0xfffffff6,0);
        local_118 = (*pcVar4)(&DAT_12124314 + iVar9,uVar10);
      }
      else {
        uVar8 = FUN_1084e2b0(local_58,0x14e1,0xfffffff6,0);
        local_118 = *(uint *)((uVar8 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_58 * 0x78));
      }
      FUN_1084c7bc(local_58,0x14e1,&local_118,0x3f6b,1);
      FUN_1084c7bc(local_58,0x14e1,&local_118,0x3f6a,1);
      FUN_1084c7bc(local_58,0x14e1,&local_118,0x3f62,1);
      if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
        pcVar4 = *(code **)(&DAT_1212434c + local_58 * 0x78);
        iVar9 = local_58 * 0x78;
        uVar10 = FUN_1084e2b0(local_58,0x14e1,0xfffffff6,0);
        (*pcVar4)(&DAT_12124314 + iVar9,uVar10,local_118);
      }
      else {
        uVar8 = FUN_1084e2b0(local_58,0x14e1,0xfffffff6,0);
        *(uint *)((uVar8 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_58 * 0x78)) = local_118;
      }
    }
  }
  if (((*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) &&
      ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c24) & 0x8000000) != 0)) &&
     (iVar9 = FUN_10f56bfc(local_58), iVar9 < 0)) {
    return iVar9;
  }
  if ((*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) &&
     ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)) {
    iVar9 = FUN_10846cf4(local_58,0x8716,0xfffffff6,0,&local_108);
    if (iVar9 < 0) {
      return iVar9;
    }
    if ((local_108 & 8) == 0) {
      *(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c14) =
           *(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c14) & 0xffffbfff;
    }
  }
  if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
     (((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x7ffff6ff) != 0 ||
        ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x10) != 0)) ||
       ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)) ||
      ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x20) != 0)))) {
    *(uint *)(&DAT_1212b9c4)[local_58] = *(uint *)(&DAT_1212b9c4)[local_58] | 0x20000;
  }
  *puVar3 = *puVar3 & 0x8813;
  *(undefined4 *)(iVar12 + 4) = 0;
  puVar3[0x3870] = 0;
  puVar3[0x3871] = 0;
  puVar3[0x3a2f] = 0;
  puVar3[0x3a30] = 0;
  puVar3[0x3a31] = 0;
  puVar3[0x3a32] = 0;
  puVar3[0x3a33] = 0;
  puVar3[0x3a34] = 0;
  puVar3[0x3a35] = 0;
  puVar3[0x3a36] = 0;
  puVar3[0x3a37] = 0;
  puVar3[0x3a38] = 0;
  puVar3[0x3a39] = 0;
  puVar3[0x3a3a] = 0;
  puVar3[0x3a3b] = 0;
  if (((*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) &&
      ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c38) & 0x800) != 0)) &&
     (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c14) & 0x2000000) != 0 ||
      ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c3c) & 0x80) != 0)))) {
    iVar9 = FUN_10846cf4(local_58,0x5b17,0xfffffff6,0,&local_118);
    if (iVar9 < 0) {
      return iVar9;
    }
    iVar9 = FUN_1084b1d8(local_58,0x5b17,local_118,0x2ed5);
    if (iVar9 != 0) {
      *(undefined1 *)((&DAT_1212b9c4)[local_58] + 0x2f1888) = 1;
    }
  }
  if (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c48) & 0x4000000) != 0) &&
     ((((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
        ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 4) != 0)) ||
       ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
        (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x80000) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)))))) &&
      (iVar9 = FUN_107f4070(local_58), iVar9 < 0)))) {
    return iVar9;
  }
  if ((((*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) &&
       ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c48) & 0x4000000) != 0)) &&
      (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
        ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 4) != 0)) ||
       ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
        (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x80000) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)))))))) &&
     ((iVar9 = FUN_107f43f8(local_58,&local_10c), -1 < iVar9 &&
      (((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x2060) != 0 &&
        ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x2060) & 2)
         != 0)) && (*(int *)((&DAT_1212b9c4)[local_58] + 0x2f189c) != local_10c)))))) {
    FUN_10823280(local_58,local_10c);
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c3c) & 0x4000) != 0) {
    uVar8 = FUN_11311498();
    if (((uVar8 & 0x80000) == 0) && (uVar8 = FUN_11311498(), (uVar8 & 0x800000) == 0)) {
      uVar10 = 1;
    }
    else {
      uVar10 = 0;
    }
    iVar9 = FUN_107953d0(local_58,"mem_cache_enable",uVar10);
    if (iVar9 != 0) {
      bVar5 = true;
      goto LAB_10e5b120;
    }
  }
  bVar5 = false;
LAB_10e5b120:
  cVar16 = FUN_107953d0(local_58,"mem_check_nocache_override",0);
  puVar3[0x3a2b] = 0;
  puVar3[0x3a2c] = 0;
  puVar3[0x3a2d] = 0;
  puVar3[0x3a2e] = 0;
  local_248 = 0;
  do {
    if (0x10e3 < local_248) {
      if (((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c3c) & 0x8000) == 0) ||
           (iVar12 = FUN_107953d0(local_58,"parity_enable",1), iVar12 == 0)) ||
          (iVar12 = FUN_108643b4(local_58), -1 < iVar12)) &&
         (((uVar8 = FUN_11311498(), (uVar8 & 0xa0000) != 0 ||
           (*(int *)(&DAT_1212ba54 + local_58 * 4) == 1)) ||
          ((*(int *)((&DAT_1212b9c4)[local_58] + 0xe1dc) != 0 ||
           (iVar12 = FUN_10835f24(local_58), -1 < iVar12)))))) {
        if ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) {
          if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 2) == 0) {
            if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
              local_118 = (**(code **)(&DAT_12124348 + local_58 * 0x78))
                                    (&DAT_12124314 + local_58 * 0x78,0x10c);
            }
            else {
              local_118 = *(uint *)(*(int *)(&DAT_12124344 + local_58 * 0x78) + 0x10c);
            }
            local_118 = local_118 | 0xc2003;
            uVar8 = FUN_11311498();
            if ((uVar8 & 0xa0000) != 0) {
              local_118 = local_118 & 0xffffffbf;
            }
            if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
               (((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x7ffff67f) != 0 ||
                  ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x10) != 0)) ||
                 (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0 ||
                  ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x20) != 0)))) &&
                (iVar12 = FUN_107953d0(local_58,"mdio_external_master",0), iVar12 == 0)))) {
              local_118 = local_118 | 0x4000000;
            }
            if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
              (**(code **)(&DAT_1212434c + local_58 * 0x78))
                        (&DAT_12124314 + local_58 * 0x78,0x10c,local_118);
            }
            else {
              *(uint *)(*(int *)(&DAT_12124344 + local_58 * 0x78) + 0x10c) = local_118;
            }
          }
          else {
            FUN_11311498();
          }
          iVar12 = FUN_10791be0(local_58);
          if (iVar12 != 0) {
            FUN_10760cd4(0x200000,"soc_init: unit %d DMA initialization failed\n",local_58);
            return -1;
          }
        }
        if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 2) == 0) {
          if ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) {
            FUN_107b9e0c(local_58,0x18000);
            FUN_107b9e0c(local_58,0x20000);
            if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
              (**(code **)(&DAT_1212434c + local_58 * 0x78))(&DAT_12124314 + local_58 * 0x78,0x50,1)
              ;
            }
            else {
              *(undefined4 *)(*(int *)(&DAT_12124344 + local_58 * 0x78) + 0x50) = 1;
            }
            if (*(int *)(&DAT_12124344 + local_58 * 0x78) == 0) {
              (**(code **)(&DAT_1212434c + local_58 * 0x78))
                        (&DAT_12124314 + local_58 * 0x78,0x50,0x12);
            }
            else {
              *(undefined4 *)(*(int *)(&DAT_12124344 + local_58 * 0x78) + 0x50) = 0x12;
            }
            FUN_107b9e0c(local_58,0x10);
          }
        }
        else {
          local_224 = 0;
          if ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) {
            FUN_107c89d4(local_58,8);
          }
          FUN_10877954(local_58);
          for (local_228 = 0; local_228 < *(int *)((&DAT_1212b9c4)[local_58] + 0xe210);
              local_228 = local_228 + 1) {
            FUN_112d0f90((&DAT_1212b9c4)[local_58] + (local_228 + 0x1c4e) * 8 + 8,0,
                         *(undefined4 *)((&DAT_1212b9c4)[local_58] + 0xe0ec));
            if (*(int *)((&DAT_1212b9c4)[local_58] + 0xe1fc) == local_228) {
              iVar12 = (&DAT_1212b9c4)[local_58];
              uVar10 = FUN_10796734(local_58,0,"num_queues",
                                    *(undefined4 *)((&DAT_1212b9c4)[local_58] + 0xe0ec));
              *(undefined4 *)(iVar12 + (local_228 + 0x38b0) * 4 + 8) = uVar10;
            }
            else {
              iVar12 = local_228;
              if (local_228 < *(int *)((&DAT_1212b9c4)[local_58] + 0xe1fc)) {
                iVar12 = local_228 + 1;
              }
              iVar9 = (&DAT_1212b9c4)[local_58];
              uVar10 = FUN_10796734(local_58,iVar12,"num_queues",0);
              *(undefined4 *)(iVar9 + (local_228 + 0x38b0) * 4 + 8) = uVar10;
            }
            iVar12 = *(int *)((&DAT_1212b9c4)[local_58] + (local_228 + 0x38b0) * 4 + 8);
            FUN_112d1134((&DAT_1212b9c4)[local_58] + (local_228 + 0x1c4e) * 8 + 8,local_224,iVar12);
            local_224 = local_224 + iVar12;
            if (*(int *)((&DAT_1212b9c4)[local_58] + 0xe0ec) < local_224) {
              FUN_10760cd4(0x8000000,"soc_do_init: total cpu and arm cosq %04x unexpected\n",
                           local_224);
            }
          }
        }
        *puVar3 = *puVar3 | 2;
        if ((*(uint *)(&DAT_1212b9c4)[local_58] & 0x800) == 0) {
          if ((((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
               ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x400000) != 0)) ||
              ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
               ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x8000000) != 0)))) &&
             (iVar12 = FUN_10852920(local_58,0x10f,0xfffffff6,0x44e2,0), iVar12 < 0)) {
            return iVar12;
          }
          if (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
              ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x8000000) != 0)) ||
             (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
               ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 1) != 0)) ||
              ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
               ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x20000000) != 0)))))) {
            for (local_220 = *(uint *)((&DAT_1212b9c4)[local_58] + 0x4cac);
                (-1 < (int)local_220 &&
                ((int)local_220 <= *(int *)((&DAT_1212b9c4)[local_58] + 0x4cb0)));
                local_220 = local_220 + 1) {
              iVar12 = (int)local_220 >> 5;
              if (((*(uint *)((&DAT_1212b9c4)[local_58] +
                              (iVar12 + (uint)((int)local_220 < 0 && (local_220 & 0x1f) != 0) +
                              0x1328) * 4 + 0x14) &
                   1 << (local_220 +
                         (iVar12 + (uint)((int)local_220 < 0 && (local_220 & 0x1f) != 0)) * -0x20 &
                        0x3f)) != 0) &&
                 (((*(uint *)((&DAT_1212b9c4)[local_58] +
                              (iVar12 + (uint)((int)local_220 < 0 && (local_220 & 0x1f) != 0) +
                              0x49c) * 4 + 0x10) &
                   1 << (local_220 +
                         (iVar12 + (uint)((int)local_220 < 0 && (local_220 & 0x1f) != 0)) * -0x20 &
                        0x3f)) != 0 ||
                  ((*(uint *)((&DAT_1212b9c4)[local_58] +
                              (iVar12 + (uint)((int)local_220 < 0 && (local_220 & 0x1f) != 0) +
                              0x408) * 4 + 0xc) &
                   1 << (local_220 +
                         (iVar12 + (uint)((int)local_220 < 0 && (local_220 & 0x1f) != 0)) * -0x20 &
                        0x3f)) != 0)))) {
                iVar12 = FUN_10845c00(local_58,0x5eb5,local_220,0,&local_100);
                if (iVar12 < 0) {
                  return iVar12;
                }
                FUN_1084dcc8(local_58,0x5eb5,&local_100,0xddad,0);
                FUN_1084dcc8(local_58,0x5eb5,&local_100,0xbb31,0);
                iVar12 = FUN_10848590(local_58,0x5eb5,local_220,0,local_100,local_fc);
                if (iVar12 < 0) {
                  return iVar12;
                }
              }
            }
          }
        }
        iVar12 = FUN_107953d0(local_58,"l2xmsg_shadow_hit_bits",1);
        if (iVar12 == 0) {
          *(undefined1 *)(puVar3 + 0xbc670) = 0;
        }
        else {
          *(byte *)(puVar3 + 0xbc670) = *(byte *)(puVar3 + 0xbc670) | 1;
        }
        iVar12 = FUN_107953d0(local_58,"l2xmsg_shadow_hit_src",0);
        if (iVar12 != 0) {
          *(byte *)(puVar3 + 0xbc670) = *(byte *)(puVar3 + 0xbc670) | 2;
        }
        iVar12 = FUN_107953d0(local_58,"l2xmsg_shadow_hit_dst",0);
        if (iVar12 != 0) {
          *(byte *)(puVar3 + 0xbc670) = *(byte *)(puVar3 + 0xbc670) | 4;
        }
        if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c20) & 0x800000) != 0) {
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth",0);
          *(undefined4 *)(iVar12 + 0x2f1a64) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e99144(local_58,0x7d6);
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth_l2x",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1a68) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e99144(local_58,0xcfe);
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth_mpls",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1a6c) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e99144(local_58,0x1093);
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth_vlan",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1a70) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e99144(local_58,0x26d);
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth_egress_vlan",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1a74) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e99144(local_58,0x83c);
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth_l3x",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1a78) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e99144(local_58,0x680);
          uVar10 = FUN_107953d0(local_58,"dual_hash_recurse_depth_dnat_pool",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1a94) = uVar10;
        }
        if (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x100) != 0) ||
           ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x200) != 0)) {
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_107953d0(local_58,"multi_hash_recurse_depth",0);
          *(undefined4 *)(iVar12 + 0x2f1aa0) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e998a0(local_58,0x7e1);
          uVar10 = FUN_107953d0(local_58,"multi_hash_recurse_depth_l2",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1aa4) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e998a0(local_58,0xcfe);
          uVar10 = FUN_107953d0(local_58,"multi_hash_recurse_depth_mpls",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1aac) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e998a0(local_58,0x1093);
          uVar10 = FUN_107953d0(local_58,"multi_hash_recurse_depth_vlan",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1ab0) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e998a0(local_58,0x26d);
          uVar10 = FUN_107953d0(local_58,"multi_hash_recurse_depth_egress_vlan",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1ab4) = uVar10;
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_10e998a0(local_58,0x822);
          uVar10 = FUN_107953d0(local_58,"multi_hash_recurse_depth_l3",uVar10);
          *(undefined4 *)(iVar12 + 0x2f1aa8) = uVar10;
        }
        if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x200) != 0) {
          iVar12 = (&DAT_1212b9c4)[local_58];
          uVar10 = FUN_107953d0(local_58,"multi_hash_move_algorithm",1);
          *(undefined4 *)(iVar12 + 0x2f1ab8) = uVar10;
        }
        *(undefined4 *)((&DAT_1212b9c4)[local_58] + 0x2f1ad0) = 1;
        if ((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c08) & 2) == 0) ||
            (iVar12 = FUN_10eb295c(local_58), -1 < iVar12)) &&
           (iVar12 = FUN_10e56114(local_58,local_114), -1 < iVar12)) {
          *(undefined2 *)((&DAT_1212b9c4)[local_58] + 0x2f2708) = local_114[0];
          iVar12 = FUN_10e564d0(local_58,local_114);
          if (-1 < iVar12) {
            *(undefined2 *)((&DAT_1212b9c4)[local_58] + 0x2f270a) = local_114[0];
            if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c4c) & 1) != 0) {
              iVar12 = FUN_10e566a0(local_58,local_114);
              if (iVar12 < 0) {
                return iVar12;
              }
              *(undefined2 *)((&DAT_1212b9c4)[local_58] + 0x2f270c) = local_114[0];
            }
            if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
               (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x80000) != 0 ||
                ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)))) {
              iVar12 = FUN_10e5678c(local_58,local_114);
              if (iVar12 < 0) {
                return iVar12;
              }
              *(undefined2 *)((&DAT_1212b9c4)[local_58] + 0x2f270e) = local_114[0];
            }
            if (*(int *)((&DAT_1212b9c4)[local_58] + 0x2f2c1c) < 0) {
              *(undefined4 *)((&DAT_1212b9c4)[local_58] + 0x2f19cc) = 1;
            }
            else {
              *(undefined4 *)((&DAT_1212b9c4)[local_58] + 0x2f19cc) = 0;
            }
            iVar12 = FUN_10e56834(local_58,local_114);
            if (-1 < iVar12) {
              *(undefined2 *)((&DAT_1212b9c4)[local_58] + 0x2f2710) = local_114[0];
              uVar8 = FUN_11311b5c("port_rate_egress_lock");
              puVar3[0xbc9c5] = uVar8;
              if (puVar3[0xbc9c5] == 0) {
                iVar12 = -2;
              }
              else {
                iVar12 = FUN_107953d0(local_58,"mem_clear_hw_acceleration",1);
                if (iVar12 != 0) {
                  *(uint *)(&DAT_1212b9c4)[local_58] = *(uint *)(&DAT_1212b9c4)[local_58] | 0x100;
                }
                uVar15 = FUN_107953d0(local_58,"mem_clear_chunk_size",0x1000);
                *(undefined2 *)((&DAT_1212b9c4)[local_58] + 0x2f2712) = uVar15;
                iVar12 = FUN_107953d0(local_58,"bcm_use_gport",0);
                if (iVar12 != 0) {
                  *(uint *)(&DAT_1212b9c4)[local_58] = *(uint *)(&DAT_1212b9c4)[local_58] | 0x200;
                }
                if ((*(int *)(&DAT_1212ba54 + local_58 * 4) == 1) &&
                   ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x100) != 0)) {
                  iVar12 = FUN_107d0048(local_58,1,auStack_f8);
                  iVar9 = FUN_107d0048(local_58,2,auStack_f8);
                  iVar7 = FUN_107d0048(local_58,3,auStack_f8);
                  iVar13 = FUN_107d0048(local_58,4,auStack_f8);
                  iVar14 = FUN_107d0048(local_58,5,auStack_f8);
                  if ((((iVar12 != 0 || iVar9 != 0) || iVar7 != 0) || iVar13 != 0) || iVar14 != 0) {
                    FUN_10760cd4(0x200000,"Error retreiving ISM hash zero_lsb(s) !!\n");
                    return -1;
                  }
                  iVar12 = FUN_107cfc5c(local_58,1,auStack_f4,auStack_e0);
                  iVar9 = FUN_107cfc5c(local_58,2,auStack_f4,auStack_e0);
                  iVar7 = FUN_107cfc5c(local_58,3,auStack_f4,auStack_e0);
                  iVar13 = FUN_107cfc5c(local_58,4,auStack_f4,auStack_e0);
                  iVar14 = FUN_107cfc5c(local_58,5,auStack_f4,auStack_e0);
                  if ((((iVar12 != 0 || iVar9 != 0) || iVar7 != 0) || iVar13 != 0) || iVar14 != 0) {
                    FUN_10760cd4(0x200000,"Error retreiving ISM hash offset(s) !!\n");
                    return -1;
                  }
                }
                if ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c44) & 8) != 0) {
                  iVar12 = (&DAT_1212b9c4)[local_58];
                  local_30 = *(uint *)(iVar12 + 0x515c);
                  local_2c = *(undefined4 *)(iVar12 + 0x5160);
                  local_28 = *(undefined4 *)(iVar12 + 0x5164);
                  local_24 = *(undefined4 *)(iVar12 + 0x5168);
                  local_20 = *(undefined4 *)(iVar12 + 0x516c);
                  local_1c = *(undefined4 *)(iVar12 + 0x5170);
                  local_18 = *(undefined4 *)(iVar12 + 0x5174);
                  local_14 = *(undefined4 *)(iVar12 + 0x5178);
                  FUN_1079573c(&local_50,local_58,"replication_eligible_pbmp",&local_30);
                  puVar3[0xbc6b5] = local_50;
                  puVar3[0xbc6b6] = local_4c;
                  puVar3[0xbc6b7] = local_48;
                  puVar3[0xbc6b8] = local_44;
                  puVar3[0xbc6b9] = local_40;
                  puVar3[0xbc6ba] = local_3c;
                  puVar3[0xbc6bb] = local_38;
                  puVar3[0xbc6bc] = local_34;
                }
                iVar12 = 0;
              }
            }
          }
        }
      }
      return iVar12;
    }
    bVar6 = false;
    local_234 = local_248;
    if (((-1 < local_248) && (local_248 < 0x10e4)) &&
       ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + local_248 * 4)
         != 0 && (((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                               local_248 * 4) & 2) != 0 &&
                  (*(int *)((&DAT_1212ba0c)[local_58] + local_248 * 0xec + 0x31bc) -
                   *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24)
                                    + local_248 * 4) + 0xc) != -1)))))) {
      memset((void *)(iVar12 + local_248 * 0xec + 0x30d4),0,0xe8);
      if (local_248 == 0xcff) {
        local_234 = 0xcfe;
      }
      else if (local_248 < 0xd00) {
        if ((local_248 != 0x269) && (local_248 == 0x2e5)) {
          local_234 = 0x26d;
        }
      }
      else if (local_248 == 0x1085) {
        if (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
            (((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x7e6c247f) != 0 ||
               ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x10) != 0)) ||
              ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)) ||
             ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x20) != 0)))) &&
           ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x100) == 0)) {
          local_234 = 0x1093;
        }
      }
      else if (local_248 == 0x1094) {
        local_234 = 0x1093;
      }
      local_230 = local_234;
      if (((local_234 - 0x82fU < 0xe) && ((1 << (local_234 - 0x82fU & 0x3f) & 0x2111U) != 0)) &&
         ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c40) & 0x200) != 0)) {
        local_230 = 0x82b;
      }
      if (local_230 < 0) {
        FUN_113113b0("lock_mem >= 0",
                     "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/esw/drv.c"
                     ,0x1759);
      }
      if (local_234 == local_248) {
        local_244 = (uint)*(ushort *)
                           (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24)
                                    + local_248 * 4) + 0x14);
        while( true ) {
          if ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x10000) == 0) {
            uVar2 = *(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                              local_248 * 4) + 0x16);
          }
          else {
            uVar2 = *(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                              local_248 * 4) + 0x14);
          }
          if ((int)(uint)uVar2 < (int)local_244) goto LAB_10e5b6fc;
          if ((int)local_244 < 0x20) {
            uVar8 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) +
                                               0x24) + local_248 * 4) + 0x18) &
                    1 << (local_244 & 0x3f);
          }
          else {
            uVar8 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) +
                                               0x24) + local_248 * 4) + 0x1c) &
                    1 << (local_244 & 0x1f);
          }
          if ((uVar8 != 0) && (*(char *)((&DAT_1212b9c4)[local_58] + local_244 + 0x909c) != '\0'))
          break;
          local_244 = local_244 + 1;
        }
        local_240 = local_244;
LAB_10e5b6fc:
        if ((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x30) +
                     local_240 * 0x10) == 0x30) ||
           (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x30) +
                    local_240 * 0x10) == 0x1f)) {
          **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                     local_248 * 4) =
               **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0xffffffdf;
          bVar6 = true;
        }
        else if (((((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x30) +
                             local_240 * 0x10) == 0xd) &&
                   (*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0)) &&
                  (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x80000) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)))) &&
                 (*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24)
                                    + local_248 * 4) + 0x20) >> 0x1a == 9)) &&
                (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x2f2c24) & 0x8000000) == 0 ||
                 (uVar8 = FUN_11311498(), (uVar8 & 0x10000) != 0)))) {
          **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                     local_248 * 4) =
               **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0xffffffdf;
          bVar6 = true;
        }
        if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
           (((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x80000) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)))) {
          if ((local_248 == 0x7e1) || (local_248 == 0x7e2)) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) | 0x400;
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xfffffdff;
          }
          if ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x400) != 0) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) | 0x20;
          }
          if ((local_248 == 0x2f7) || (local_248 == 0x2f6)) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xffffffdf;
            bVar6 = true;
          }
          if ((((local_248 == 0xcf4) || (local_248 == 0xcf5)) || (local_248 == 0xcf6)) ||
             (local_248 == 0xcf7)) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xffffffdf;
            bVar6 = true;
          }
        }
        if (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
            ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x5000000c) != 0)) ||
           ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0 &&
            ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0xc) != 0)))) {
          for (local_22c = 0; local_22c < 4; local_22c = local_22c + 1) {
            if (*(int *)(&DAT_11877190 + local_22c * 4) == local_248) {
              **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                         local_248 * 4) =
                   **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                              local_248 * 4) & 0xffffffdf;
              bVar6 = true;
              break;
            }
          }
          if (local_248 == 0x7d6) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x1f58) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x1f58) | 0x400;
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x1f58) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x1f58) & 0xffffffbf;
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x1f58) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x1f58) & 0xfffffdff;
          }
          if ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x400) != 0) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) | 0x20;
          }
          if (((local_248 == 0x6eb) || (local_248 == 0x6e7)) ||
             ((((local_248 == 0x4a6 ||
                (((local_248 == 0x4a7 || (local_248 == 0x4a8)) || (local_248 == 0x7e5)))) ||
               (((local_248 == 0x83b || (local_248 == 0x1099)) || (local_248 == 0x26f)))) ||
              (local_248 == 0x1090)))) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xffffffdf;
            bVar6 = true;
          }
          if (((local_248 == 0xcf4) || (local_248 == 0xcf5)) ||
             ((local_248 == 0xcf6 || (local_248 == 0xcf7)))) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xffffffdf;
            bVar6 = true;
          }
        }
        if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
           ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0xc) != 0)) {
          if (((local_248 == 0x80a) ||
              (((local_248 == 0x80b || (local_248 == 0x80c)) || (local_248 == 0x80e)))) ||
             (((local_248 == 0x80d || (local_248 == 0x818)) || (local_248 == 0x7fe)))) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xfffffbff;
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) | 0x80;
            bVar6 = true;
          }
          if (local_248 == 0x812) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x2048) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x2048) & 0xffffffdf;
            bVar6 = true;
          }
          if (((local_248 == 0x9e5) || (local_248 == 0x9e6)) ||
             ((local_248 == 0x9e2 ||
              (((local_248 == 0x9e3 || (local_248 == 0x9e7)) || (local_248 == 0x9e8)))))) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) | 0x40;
            bVar6 = true;
          }
        }
        if (((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
            ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 4) != 0)) &&
           (((local_248 == 0xa15 || ((local_248 == 0xa16 || (local_248 == 0xa18)))) ||
            (local_248 == 0xa19)))) {
          **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                     local_248 * 4) =
               **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0xffffffdf;
          bVar6 = true;
        }
        if ((*(int *)((&DAT_1212b9c4)[local_58] + 0x10) == 0) &&
           (((((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x7e6c247f) != 0 ||
              ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x10) != 0)) ||
             ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x40) != 0)) ||
            ((*(uint *)((&DAT_1212b9c4)[local_58] + 0x14) & 0x20) != 0)))) {
          if (local_248 == 0x7d6) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x1f58) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x1f58) | 0x400;
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x1f58) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x1f58) & 0xffffffbf;
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) + 0x1f58) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            0x1f58) & 0xfffffdff;
          }
          if ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x400) != 0) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) | 0x20;
          }
          if ((((local_248 == 0xd0a) || (local_248 == 0x7fa)) ||
              ((local_248 == 0x813 || ((local_248 == 0x819 || (local_248 == 0x800)))))) ||
             ((local_248 == 0x804 ||
              ((((local_248 == 0x817 || (local_248 == 0x81d)) || (local_248 == 0x83c)) ||
               (local_248 == 0xcfa)))))) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xffffffdf;
            bVar6 = true;
          }
        }
        if (cVar16 != '\0') {
          local_dc[0]._0_1_ = s_mem_nocache__114041ac[0];
          local_dc[0]._1_1_ = s_mem_nocache__114041ac[1];
          local_dc[0]._2_1_ = s_mem_nocache__114041ac[2];
          local_dc[0]._3_1_ = s_mem_nocache__114041ac[3];
          local_dc[1]._0_1_ = s_mem_nocache__114041ac[4];
          local_dc[1]._1_1_ = s_mem_nocache__114041ac[5];
          local_dc[1]._2_1_ = s_mem_nocache__114041ac[6];
          local_dc[1]._3_1_ = s_mem_nocache__114041ac[7];
          local_dc[2]._0_1_ = s_mem_nocache__114041ac[8];
          local_dc[2]._1_1_ = s_mem_nocache__114041ac[9];
          local_dc[2]._2_1_ = s_mem_nocache__114041ac[10];
          local_dc[2]._3_1_ = s_mem_nocache__114041ac[0xb];
          local_d0 = CONCAT13(s_mem_nocache__114041ac[0xc],local_d0._1_3_);
          sVar11 = strlen((char *)local_dc);
          strcpy((char *)((int)local_dc + sVar11),(&PTR_s_ACTIONPROFILETABLE_11ab0334)[local_248]);
          iVar9 = FUN_107953d0(local_58,local_dc,0);
          if (iVar9 != 0) {
            **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                       local_248 * 4) =
                 **(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                            local_248 * 4) & 0xffffffdf;
            bVar6 = true;
          }
        }
        if (((!bVar5) || (bVar6)) ||
           ((((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x80) == 0 &&
             ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x400) == 0)) &&
            (((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                          local_248 * 4) & 0x20) == 0 ||
             (((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                           local_248 * 4) & 0x100) == 0 &&
              ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_58] + 0x2f26f4) + 0x24) +
                           local_248 * 4) & 0x200) == 0)))))))) {
          iVar9 = FUN_107f05b4(local_58,local_248,0xffffffff,0);
        }
        else {
          iVar9 = FUN_107f05b4(local_58,local_248,0xffffffff,1);
          if (iVar9 < 0) {
            return iVar9;
          }
          iVar9 = FUN_107f3b0c(local_58,local_248,&local_110);
        }
        if (iVar9 < 0) {
          s_mem_nocache__114041ac[0] = SUB41(s_mem_nocache__114041ac._0_4_,3);
          s_mem_nocache__114041ac[1] = SUB41(s_mem_nocache__114041ac._0_4_,2);
          s_mem_nocache__114041ac[2] = SUB41(s_mem_nocache__114041ac._0_4_,1);
          s_mem_nocache__114041ac[3] = (char)s_mem_nocache__114041ac._0_4_;
          s_mem_nocache__114041ac[4] = SUB41(s_mem_nocache__114041ac._4_4_,3);
          s_mem_nocache__114041ac[5] = SUB41(s_mem_nocache__114041ac._4_4_,2);
          s_mem_nocache__114041ac[6] = SUB41(s_mem_nocache__114041ac._4_4_,1);
          s_mem_nocache__114041ac[7] = (char)s_mem_nocache__114041ac._4_4_;
          s_mem_nocache__114041ac[8] = SUB41(s_mem_nocache__114041ac._8_4_,3);
          s_mem_nocache__114041ac[9] = SUB41(s_mem_nocache__114041ac._8_4_,2);
          s_mem_nocache__114041ac[10] = SUB41(s_mem_nocache__114041ac._8_4_,1);
          s_mem_nocache__114041ac[0xb] = (char)s_mem_nocache__114041ac._8_4_;
          return iVar9;
        }
      }
    }
    local_248 = local_248 + 1;
  } while( true );
}



/* === FUN_10e412f4 (size=204) === */

undefined4 FUN_10e412f4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_10760cd4(0x10000,"soc_mmu_init\n");
  iVar1 = FUN_10794b20(param_1);
  if (iVar1 == 0) {
    uVar2 = 0xffffffef;
  }
  else if ((*(uint *)(&DAT_1212b9c4)[param_1] & 0x800) == 0) {
    uVar2 = (**(code **)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f8) + 4))(param_1);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_10794970 (size=112) === */

undefined4 FUN_10794970(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_10794fc4(param_1,"soc_family");
  *(undefined4 *)(&DAT_11efe654 + param_1 * 4) = uVar1;
  uVar1 = FUN_10e58d90(param_1,0);
  return uVar1;
}



/* === FUN_10794638 (size=824) === */

undefined4 FUN_10794638(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  local_28 = 0xfffffff0;
  FUN_10760cd4(0x10000,"soc_misc_init\n");
  iVar1 = FUN_10794b20(param_1);
  if (iVar1 == 0) {
    local_28 = 0xffffffef;
  }
  else if ((*(uint *)(&DAT_1212b9c4)[param_1] & 0x800) == 0) {
    if ((*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f8) != 0) &&
       (**(int **)((&DAT_1212b9c4)[param_1] + 0x2f26f8) != 0)) {
      if ((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) == 0) &&
         (((((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x7ffff6ff) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x10) != 0)) ||
           ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x40) != 0)) ||
          ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x20) != 0)))) {
        *(uint *)(&DAT_1212b9c4)[param_1] = *(uint *)(&DAT_1212b9c4)[param_1] | 0x20000;
      }
      local_28 = (*(code *)**(undefined4 **)((&DAT_1212b9c4)[param_1] + 0x2f26f8))(param_1);
      if ((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) == 0) &&
         ((((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x7ffff6ff) != 0 ||
           ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x10) != 0)) ||
          (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x40) != 0 ||
           ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x20) != 0)))))) {
        *(uint *)(&DAT_1212b9c4)[param_1] = *(uint *)(&DAT_1212b9c4)[param_1] & 0xfffdffff;
      }
    }
  }
  else {
    local_28 = 0;
  }
  return local_28;
}



/* === FUN_10ef3080 (size=108) === */

undefined4
FUN_10ef3080(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  
  uVar1 = FUN_10ef2a58(param_1,param_2,param_3,0,0,0,param_4,param_5);
  return uVar1;
}



/* === FUN_10801b4c (size=208) === */

undefined4
FUN_10801b4c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int local_24;
  
  local_24 = param_2;
  if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c40) & 0x100) != 0) {
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
  uVar1 = FUN_10801d70(param_1,local_24,0,param_3,param_4,param_5);
  return uVar1;
}



/* === FUN_10801d70 (size=848) === */

int FUN_10801d70(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6)

{
  int iVar1;
  int local_c8;
  int local_c4;
  undefined1 auStack_b8 [80];
  uint auStack_68 [8];
  uint auStack_48 [8];
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  if ((((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) == 0) &&
       ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x10000000) != 0)) ||
      ((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) == 0 &&
       ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x40000000) != 0)))) && (param_2 == 0x269)) {
    FUN_10f0bc94(param_1,1,1);
    iVar1 = FUN_107fe254(local_28,0,local_24,local_20,local_1c,local_18,auStack_b8);
    if (-1 < iVar1) {
      FUN_10f0bc94(local_28,1,0);
      iVar1 = FUN_107fe254(local_28,0,local_24,local_20,local_1c,local_18,local_14);
      if (-1 < iVar1) {
        FUN_107a5554(local_28,local_24,local_14,0xa0fe,auStack_48);
        FUN_107a5554(local_28,local_24,auStack_b8,0xa0fe,auStack_68);
        for (local_c8 = 0; local_c8 < 8; local_c8 = local_c8 + 1) {
          auStack_48[local_c8] = auStack_48[local_c8] | auStack_68[local_c8];
        }
        FUN_107a54a8(local_28,local_24,local_14,0xa0fe,auStack_48);
        FUN_107a5554(local_28,local_24,local_14,0xe33f,auStack_48);
        FUN_107a5554(local_28,local_24,auStack_b8,0xe33f,auStack_68);
        for (local_c4 = 0; local_c4 < 8; local_c4 = local_c4 + 1) {
          auStack_48[local_c4] = auStack_48[local_c4] | auStack_68[local_c4];
        }
        FUN_107a54a8(local_28,local_24,local_14,0xe33f,auStack_48);
        iVar1 = 0;
      }
    }
  }
  else {
    iVar1 = FUN_107fe254(param_1,0,param_2,param_3,param_4,param_5,param_6);
  }
  return iVar1;
}



