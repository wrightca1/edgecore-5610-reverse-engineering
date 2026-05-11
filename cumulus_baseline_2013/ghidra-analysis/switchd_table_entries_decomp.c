/* Table entry implementation decomp */

/* === FUN_101d8854 (size=12256) === */

undefined4 FUN_101d8854(int param_1,undefined4 param_2,void *param_3)

{
  uint uVar1;
  code *pcVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  void *__s;
  undefined4 uVar8;
  size_t __n;
  int iVar9;
  undefined4 local_278;
  int local_274;
  int local_270;
  int local_26c;
  int local_268;
  int local_264;
  int local_260;
  int local_25c;
  undefined4 local_258;
  int local_254;
  int local_250;
  int local_24c;
  int local_248;
  code *local_244;
  code *local_240;
  code *local_23c;
  int local_238;
  int local_234;
  uint local_230;
  undefined2 local_208 [2];
  undefined4 local_204;
  undefined1 auStack_200 [80];
  undefined4 local_1b0;
  undefined2 local_1ac;
  undefined4 local_1a8;
  undefined2 local_1a4;
  undefined1 auStack_1a0 [4];
  undefined1 auStack_19c [16];
  undefined1 auStack_18c [16];
  undefined1 auStack_17c [4];
  undefined4 local_178;
  undefined2 local_174;
  undefined4 local_170 [2];
  undefined4 local_168;
  undefined4 local_164;
  undefined2 local_160;
  undefined2 local_15e;
  undefined1 auStack_100 [20];
  int local_ec;
  undefined1 auStack_94 [4];
  int local_90;
  int local_8c;
  undefined4 local_78;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 auStack_5c [52];
  int local_28;
  undefined4 local_24;
  void *local_20;
  
  local_278 = 0;
  local_204 = 0;
  local_1b0 = DAT_11374e0c;
  local_1ac = DAT_11374e10;
  local_1a8 = DAT_11374e14;
  local_1a4 = DAT_11374e18;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  uVar4 = FUN_11311498();
  bVar3 = (uVar4 & 0x10000) == 0;
  if (bVar3) {
    if (*(int *)((&DAT_1212b9c4)[local_28] + 0xe1e0) == 0) {
      local_274 = 10;
      local_270 = 5000;
      local_26c = 5000;
      local_260 = 100;
      local_25c = 50000;
    }
    else {
      local_274 = 10;
      local_270 = 5000;
      local_26c = 0;
      local_260 = 0;
      local_25c = 0;
    }
  }
  else {
    local_274 = 100;
    local_270 = 200;
    local_26c = 200;
    local_260 = 1;
    local_25c = 2000;
  }
  *(undefined1 *)((&DAT_1212b9c4)[local_28] + 0x2f1868) = 1;
  uVar4 = *(uint *)((int)param_3 + 8);
  iVar5 = FUN_101d8368(param_3,"memset sys mem",&DAT_11374b9c,
                       (((int)uVar4 >> 0x14) + (uint)((int)uVar4 < 0 && (uVar4 & 0xfffff) != 0)) *
                       local_274);
  if (iVar5 != 0) {
    for (local_268 = 0; local_268 < local_274; local_268 = local_268 + 1) {
      memset(*(void **)((int)param_3 + 0xc),0,*(size_t *)((int)param_3 + 8));
    }
  }
  FUN_101d8434(param_3);
  uVar4 = *(uint *)((int)param_3 + 8);
  iVar5 = FUN_101d8368(param_3,"memcpy sys mem",&DAT_11374b9c,
                       (local_274 >> 1) *
                       (((int)uVar4 >> 0x14) + (uint)((int)uVar4 < 0 && (uVar4 & 0xfffff) != 0)));
  if (iVar5 != 0) {
    for (local_268 = 0; local_268 < local_274; local_268 = local_268 + 1) {
      uVar4 = *(uint *)((int)param_3 + 8);
      uVar1 = *(uint *)((int)param_3 + 8);
      memcpy((void *)(*(int *)((int)param_3 + 0xc) +
                     ((int)uVar4 >> 1) + (uint)((int)uVar4 < 0 && (uVar4 & 1) != 0)),
             *(void **)((int)param_3 + 0xc),
             ((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0));
    }
  }
  FUN_101d8434(param_3);
  uVar4 = *(uint *)((int)param_3 + 0x10);
  iVar5 = FUN_101d8368(param_3,"memset dma mem",&DAT_11374b9c,
                       (((int)uVar4 >> 0x14) + (uint)((int)uVar4 < 0 && (uVar4 & 0xfffff) != 0)) *
                       local_274);
  if (iVar5 != 0) {
    for (local_268 = 0; local_268 < local_274; local_268 = local_268 + 1) {
      memset(*(void **)((int)param_3 + 0x14),0,*(size_t *)((int)param_3 + 0x10));
    }
  }
  FUN_101d8434(param_3);
  uVar4 = *(uint *)((int)param_3 + 0x10);
  iVar5 = FUN_101d8368(param_3,"memcpy dma mem",&DAT_11374b9c,
                       (local_274 >> 1) *
                       (((int)uVar4 >> 0x14) + (uint)((int)uVar4 < 0 && (uVar4 & 0xfffff) != 0)));
  if (iVar5 != 0) {
    for (local_268 = 0; local_268 < local_274; local_268 = local_268 + 1) {
      uVar4 = *(uint *)((int)param_3 + 0x10);
      uVar1 = *(uint *)((int)param_3 + 0x10);
      memcpy((void *)(*(int *)((int)param_3 + 0x14) +
                     ((int)uVar4 >> 1) + (uint)((int)uVar4 < 0 && (uVar4 & 1) != 0)),
             *(void **)((int)param_3 + 0x14),
             ((int)uVar1 >> 1) + (uint)((int)uVar1 < 0 && (uVar1 & 1) != 0));
    }
  }
  FUN_101d8434(param_3);
  if (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) + 0x3df0) == 0) {
    uVar8 = 0xfdc;
  }
  else {
    uVar8 = 0xf7c;
  }
  iVar5 = FUN_101d8368(param_3,"read pci reg",&DAT_11374be0,local_25c);
  if (iVar5 != 0) {
    for (local_268 = 0; local_268 < local_25c; local_268 = local_268 + 1) {
      if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
        pcVar2 = *(code **)(&DAT_12124348 + local_28 * 0x78);
        iVar5 = local_28 * 0x78;
        uVar6 = FUN_1084e2b0(local_28,uVar8,0xfffffff6,0);
        local_204 = (*pcVar2)(&DAT_12124314 + iVar5,uVar6);
      }
      else {
        uVar4 = FUN_1084e2b0(local_28,uVar8,0xfffffff6,0);
        local_204 = *(undefined4 *)
                     ((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_28 * 0x78));
      }
    }
  }
  FUN_101d8434(param_3);
  iVar5 = FUN_101d8368(param_3,"write pci reg","write",local_25c);
  if (iVar5 != 0) {
    for (local_268 = 0; local_268 < local_25c; local_268 = local_268 + 1) {
      if (*(int *)(&DAT_12124344 + local_28 * 0x78) == 0) {
        pcVar2 = *(code **)(&DAT_1212434c + local_28 * 0x78);
        iVar5 = local_28 * 0x78;
        uVar6 = FUN_1084e2b0(local_28,uVar8,0xfffffff6,0);
        (*pcVar2)(&DAT_12124314 + iVar5,uVar6,local_204);
      }
      else {
        uVar4 = FUN_1084e2b0(local_28,uVar8,0xfffffff6,0);
        *(undefined4 *)((uVar4 & 0xfffffffc) + *(int *)(&DAT_12124344 + local_28 * 0x78)) =
             local_204;
      }
    }
  }
  FUN_101d8434(param_3);
  if (*(int *)((&DAT_1212b9c4)[local_28] + 0x228) < 1) {
    if (*(int *)((&DAT_1212b9c4)[local_28] + 0x47c) < 1) {
      if (*(int *)((&DAT_1212b9c4)[local_28] + 0x1020) < 1) {
        local_254 = *(int *)((&DAT_1212b9c4)[local_28] + 0x106c);
      }
      else {
        local_254 = *(int *)((&DAT_1212b9c4)[local_28] + 0xe18);
      }
    }
    else {
      local_254 = *(int *)((&DAT_1212b9c4)[local_28] + 0x274);
    }
  }
  else {
    local_254 = *(int *)((&DAT_1212b9c4)[local_28] + 0x20);
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c38) & 0x200000) == 0) {
    local_250 = local_254;
  }
  else {
    local_250 = *(int *)((&DAT_1212b9c4)[local_28] + (local_254 + 0x2114) * 4 + 0xc);
  }
  if (*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x48) < 2) {
    local_250 = local_250 << 3;
  }
  else {
    local_250 = *(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x48) * local_250 * 8;
  }
  local_258 = *(undefined4 *)
               (*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x34) + local_250);
  iVar5 = FUN_101d8368(param_3,"read soc reg",&DAT_11374be0,local_270);
  if (iVar5 != 0) {
    if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
       (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7e6c247f) != 0 ||
          ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
         ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
        ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_10846cf4(local_28,0x2db3,0xfffffff6,0,&local_204);
      }
    }
    else if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
            ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7ffff67f) != 0 ||
              ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
             (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
              ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_10846cf4(local_28,0x306e,local_254,0,&local_204);
      }
    }
  }
  FUN_101d8434(param_3);
  iVar5 = FUN_101d8368(param_3,"write soc reg","write",local_270);
  if (iVar5 != 0) {
    if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
       ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7e6c247f) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
        (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_108499c4(local_28,0x2db3,0xfffffff6,0,local_204);
      }
    }
    else if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
            (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7ffff67f) != 0 ||
               ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
              ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
             ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_108499c4(local_28,0x306e,local_254,0,local_204);
      }
    }
  }
  FUN_101d8434(param_3);
  if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
     ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x44008008) != 0)) {
    local_258 = *(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xbbf4);
    iVar5 = FUN_101d8368(param_3,"read l2mc table entry",&DAT_11374be0,local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_10801b4c(local_28,0x7d5,local_258,10,auStack_200);
      }
    }
    FUN_101d8434(param_3);
    iVar5 = FUN_101d8368(param_3,"write l2mc table entry","write",local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_108080ac(local_28,0x7d5,local_258,10,auStack_200);
      }
    }
    FUN_101d8434(param_3);
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
          ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7e6c247f) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
           (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
    local_258 = *(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xaf64);
    iVar5 = FUN_101d8368(param_3,"read FP Policy table entry",&DAT_11374be0,local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_10801b4c(local_28,0x4b1,local_258,10,auStack_200);
      }
    }
    FUN_101d8434(param_3);
    if ((*(uint *)(&DAT_1212b9c4)[local_28] & 0x800) != 0) {
      *(undefined1 *)((&DAT_1212b9c4)[local_28] + 0x2f1868) = 0;
      return 0;
    }
    if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 0x100) == 0) {
      iVar5 = FUN_101d8368(param_3,"Clear L2X table","clear",local_274);
      if (iVar5 != 0) {
        for (local_268 = 0; local_268 < local_274; local_268 = local_268 + 1) {
          FUN_108092ec(local_28,0x7d6,0xffffffff,1);
        }
      }
      FUN_101d8434(param_3);
    }
    else {
      iVar5 = FUN_101d8368(param_3,"Clear L2_ENTRY_1 table","clear",local_274);
      if (iVar5 != 0) {
        for (local_268 = 0; local_268 < local_274; local_268 = local_268 + 1) {
          FUN_108092ec(local_28,0x7e1,0xffffffff,1);
        }
      }
      FUN_101d8434(param_3);
    }
    iVar5 = FUN_101d8368(param_3,"write FP Policy table entry","write",local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_108080ac(local_28,0x4b1,local_258,10,auStack_200);
      }
    }
    FUN_101d8434(param_3);
  }
  else if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
          (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7ffff67f) != 0 ||
             ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
           ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
    local_258 = *(undefined4 *)((&DAT_1212b9c4)[local_28] + 0xafa0);
    iVar5 = FUN_101d8368(param_3,"read FP Policy table entry",&DAT_11374be0,local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_10801b4c(local_28,0x4c0,local_258,10,auStack_200);
      }
    }
    FUN_101d8434(param_3);
    iVar5 = FUN_101d8368(param_3,"write FP Policy table entry","write",local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_108080ac(local_28,0x4c0,local_258,10,auStack_200);
      }
    }
    FUN_101d8434(param_3);
  }
  local_264 = 2;
  if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x4f08) & 4) == 0) {
    local_264 = 0;
  }
  if (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x4f08) & 1 << local_264) != 0) && (bVar3)) {
    iVar5 = FUN_101d8368(param_3,"read phy reg",&DAT_11374be0,local_26c);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_26c; local_268 = local_268 + 1) {
        FUN_1082fdb8(local_28,*(undefined2 *)
                               (*(int *)(&DAT_1213550c + local_28 * 4) + local_264 * 0x18 + 4),2,
                     local_208);
      }
    }
    FUN_101d8434(param_3);
    iVar5 = FUN_101d8368(param_3,"write phy reg","write",local_26c);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_26c; local_268 = local_268 + 1) {
        FUN_1082ecfc(local_28,*(undefined2 *)
                               (*(int *)(&DAT_1213550c + local_28 * 4) + local_264 * 0x18 + 4),2,
                     local_208[0]);
      }
    }
    FUN_101d8434(param_3);
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c40) & 0x100) == 0) {
    if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
       ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7ffff67f) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
        (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
         ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
      if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x20) == 0) {
        if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
           (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7ffff67f) != 0 ||
              ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
             ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
          local_244 = FUN_10eb68f4;
          local_240 = FUN_10eb69b0;
          local_23c = FUN_10eb69fc;
        }
        else {
          local_244 = (code *)0x0;
          local_240 = (code *)0x0;
          local_23c = (code *)0x0;
        }
      }
      else {
        local_244 = FUN_101d8640;
        local_240 = FUN_101d8690;
        local_23c = FUN_101d86e0;
      }
      memset(auStack_19c,0,0x10);
      FUN_107a3b80(local_28,0x7d6,auStack_19c,0x7e22,&local_1b0);
      FUN_107a2a0c(local_28,0x7d6,auStack_19c,0xe88e,1);
      iVar5 = FUN_101d8368(param_3,"L2 insert/delete",&DAT_11374cf0,local_270);
      if (iVar5 != 0) {
        for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
          (*local_244)(local_28,auStack_19c);
          (*local_240)(local_28,auStack_19c);
        }
      }
      FUN_101d8434(param_3);
      memset(auStack_19c,0,0x10);
      FUN_107a3b80(local_28,0x7d6,auStack_19c,0x7e22,&local_1a8);
      FUN_107a2a0c(local_28,0x7d6,auStack_19c,0xe88e,1);
      iVar5 = FUN_101d8368(param_3,"L2 lookup",&DAT_11374d04,local_270);
      if (iVar5 != 0) {
        for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
          (*local_23c)(local_28,auStack_19c,auStack_18c,auStack_17c);
        }
      }
      FUN_101d8434(param_3);
      iVar5 = FUN_101d8368(param_3,"DMA L2 table",&DAT_11374d20,local_260);
      if (iVar5 != 0) {
        for (local_268 = 0; local_268 < local_260; local_268 = local_268 + 1) {
          iVar9 = (*(uint *)((int)param_3 + 0x10) >> 0xe) * 0x400;
          iVar5 = *(int *)((&DAT_1212ba0c)[local_28] + 0x76b04);
          for (local_238 = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4)
                                                     + 0x24) + 0x1f58) + 0xc); local_238 < iVar5;
              local_238 = local_238 + iVar9) {
            iVar7 = local_238 + iVar9 + -1;
            if (iVar5 < iVar7) {
              iVar7 = iVar5;
            }
            iVar7 = FUN_108020c0(local_28,0x7d6,0xffffffff,local_238,iVar7,
                                 *(undefined4 *)((int)param_3 + 0x14));
            if (iVar7 < 0) {
              local_278 = 0xffffffff;
              break;
            }
          }
        }
      }
      FUN_101d8434(param_3);
      if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
         (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7ffff67f) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
           (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) &&
          (((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) + 0x20f0) != 0
            && ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                            0x20f0) & 2) != 0)) &&
           (0 < (*(int *)((&DAT_1212ba0c)[local_28] + 0x7c90c) -
                *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                                 0x20f0) + 0xc)) + 1)))))) {
        iVar5 = FUN_101d8368(param_3,"Read L3_ENTRY_V4 table ",&DAT_11374d20,local_270);
        if (iVar5 != 0) {
          for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
            FUN_10801b4c(local_28,0x83c,local_258,10,auStack_200);
          }
        }
        FUN_101d8434(param_3);
        if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
           (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7a4c044f) != 0 ||
              ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
             ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
            ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
          iVar5 = 8;
        }
        else {
          iVar5 = 4;
        }
        __n = iVar5 * ((int)(*(ushort *)
                              (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) +
                                                0x24) + 0x20f0) + 0x28) + 3) >> 2) * 4;
        __s = (void *)FUN_1075fcd4(local_28,__n,"L3 bucket dma");
        if (__s == (void *)0x0) {
          local_278 = 0xffffffff;
        }
        else {
          memset(__s,0,__n);
          iVar5 = FUN_101d8368(param_3,"Dma read L3_ENTRY bucket",&DAT_11374d20,local_270);
          if (iVar5 != 0) {
            for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
              if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
                 ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7a4c044f) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
                  (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
                uVar8 = 0xa0;
              }
              else {
                uVar8 = 0x50;
              }
              if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
                 ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7a4c044f) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
                  (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
                iVar5 = 0xa0;
              }
              else {
                iVar5 = 0x50;
              }
              if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
                 (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7a4c044f) != 0 ||
                    ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
                  ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
                iVar9 = 8;
              }
              else {
                iVar9 = 4;
              }
              iVar5 = FUN_108020c0(local_28,0x83c,0xffffffff,uVar8,iVar5 + iVar9 + -1,__s);
              if (iVar5 < 0) {
                local_278 = 0xffffffff;
                break;
              }
            }
          }
          FUN_101d8434(param_3);
          FUN_1075ffa4(local_28,__s);
        }
      }
      *(undefined1 *)((&DAT_1212b9c4)[local_28] + 0x2f1868) = 0;
    }
    uVar8 = FUN_11311b5c("bench");
    iVar5 = FUN_101d8368(param_3,"mutex lock/unlock",&DAT_11374dc8,local_270);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
        FUN_11311c0c(uVar8,0xffffffff);
        FUN_11311d68(uVar8);
      }
    }
    FUN_101d8434(param_3);
    FUN_11311b9c(uVar8);
    if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
       ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10000000) != 0)) {
      local_234 = 0;
      local_178 = 0xbb0000;
      local_174 = 0;
      FUN_112b0fec(auStack_100);
      FUN_103f501c(local_28,auStack_100);
      FUN_112b0c60(local_170);
      local_15e = 1;
      local_170[0] = 0x60;
      local_164 = local_178;
      local_160 = local_174;
      FUN_103f5ef8(local_28,local_170);
      FUN_112b0d18(auStack_94);
      local_90 = 10;
      local_8c = 0;
      local_78 = 0xffff0000;
      local_60 = 0xb0b0b0b;
      local_64 = local_168;
      memcpy(auStack_5c,param_3,6);
      iVar5 = FUN_101d8368(param_3,"L3 DEFIP IPV4 Routes Add",&DAT_11374cf0,local_ec);
      if (iVar5 != 0) {
        for (local_230 = 1; (int)local_230 <= local_ec; local_230 = local_230 + 1) {
          local_8c = local_230 * 0x10000 + 10;
          iVar5 = FUN_103f85a0(local_28,auStack_94);
          if (iVar5 < 0) {
            if ((iVar5 < 1) && (-0x13 < iVar5)) {
              iVar5 = -iVar5;
            }
            else {
              iVar5 = 0x13;
            }
            FUN_10320d20("bcm_l3_route_add: c = %d %s\n",local_230,(&PTR_DAT_11e43a78)[iVar5]);
            break;
          }
          if ((local_230 & 0xfff) == 0) {
            local_78 = 0xfffff000;
            local_8c = local_230 * 0x10000 + -0x4ffffff6;
            local_234 = local_234 + 1;
            if (local_234 == 2) {
              local_78 = 0xffffff00;
              local_8c = local_230 * 0x10000 + -0x3ffffff6;
            }
            if (local_234 == 3) {
              local_78 = 0xfffffff0;
              local_8c = local_230 * 0x10000 + -0x2ffffff6;
            }
            if (local_234 == 4) {
              local_78 = 0xffffffff;
              local_8c = local_230 * 0x10000 + -0x1ffffff6;
            }
            local_90 = local_90 + (int)local_230 % 10;
          }
        }
      }
      FUN_101d8434(param_3);
    }
    *(undefined1 *)((&DAT_1212b9c4)[local_28] + 0x2f1868) = 0;
  }
  else {
    for (local_248 = 0; local_248 < 4; local_248 = local_248 + 1) {
      if (local_248 == 1) {
        local_24c = 0x7e2;
LAB_101d9f94:
        if (0 < (*(int *)((&DAT_1212ba0c)[local_28] + local_24c * 0xec + 0x31bc) -
                *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                                 local_24c * 4) + 0xc)) + 1) {
          memset(auStack_94,0,
                 ((int)(*(ushort *)
                         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                                  local_24c * 4) + 0x28) + 3) >> 2) << 2);
          FUN_107a3b80(local_28,local_24c,auStack_94,0x7e22,&local_1b0);
          FUN_107a2a0c(local_28,local_24c,auStack_94,0xe88e,1);
          if (local_248 == 0) {
            FUN_107a2a0c(local_28,local_24c,auStack_94,0xe37e,1);
            FUN_107a2a0c(local_28,local_24c,auStack_94,0x70c7,0);
          }
          else if (local_248 == 1) {
            FUN_107a2a0c(local_28,local_24c,auStack_94,0x70c8,1);
            FUN_107a2a0c(local_28,local_24c,auStack_94,0x70c9,1);
            FUN_107a2a0c(local_28,local_24c,auStack_94,0xedac,1);
            FUN_107a2a0c(local_28,local_24c,auStack_94,0xedad,1);
            FUN_107a2a0c(local_28,local_24c,auStack_94,0xe387,1);
            FUN_107a2a0c(local_28,local_24c,auStack_94,0xe388,1);
          }
          else {
            FUN_107a2a0c(local_28,local_24c,auStack_94,0x70c7,0);
          }
          memcpy(auStack_100,auStack_94,
                 ((int)(*(ushort *)
                         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                                  local_24c * 4) + 0x28) + 3) >> 2) << 2);
          FUN_11310e2c(local_170,"ISM %s insert/delete",
                       (&PTR_s_ACTIONPROFILETABLE_11ab0334)[local_24c]);
          iVar5 = FUN_101d8368(param_3,local_170,&DAT_11374cf0,local_270);
          if (iVar5 != 0) {
            for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
              FUN_101d8744(local_28,local_24c,auStack_94);
              FUN_101d8798(local_28,local_24c,auStack_94);
            }
          }
          FUN_101d8434(param_3);
          memcpy(auStack_94,auStack_100,
                 ((int)(*(ushort *)
                         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                                  local_24c * 4) + 0x28) + 3) >> 2) << 2);
          FUN_107a3b80(local_28,local_24c,auStack_94,0x7e22,&local_1a8);
          FUN_11310e2c(local_170,"ISM %s lookup",(&PTR_s_ACTIONPROFILETABLE_11ab0334)[local_24c]);
          iVar5 = FUN_101d8368(param_3,local_170,&DAT_11374d04,local_270);
          if (iVar5 != 0) {
            for (local_268 = 0; local_268 < local_270; local_268 = local_268 + 1) {
              FUN_101d87ec(local_28,local_24c,auStack_94,auStack_100,auStack_1a0);
            }
          }
          FUN_101d8434(param_3);
          FUN_11310e2c(local_170,"DMA ISM %s table",(&PTR_s_ACTIONPROFILETABLE_11ab0334)[local_24c])
          ;
          iVar5 = FUN_101d8368(param_3,local_170,&DAT_11374d20,local_260);
          if (iVar5 != 0) {
            for (local_268 = 0; local_268 < local_260; local_268 = local_268 + 1) {
              iVar5 = FUN_108020c0(local_28,local_24c,0xffffffff,
                                   *(undefined4 *)
                                    (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4
                                                               ) + 0x24) + local_24c * 4) + 0xc),
                                   *(undefined4 *)
                                    ((&DAT_1212ba0c)[local_28] + local_24c * 0xec + 0x31bc),
                                   *(undefined4 *)((int)param_3 + 0x14));
              if (iVar5 < 0) {
                local_278 = 0xffffffff;
                break;
              }
            }
          }
          FUN_101d8434(param_3);
        }
      }
      else {
        if (local_248 < 2) {
          if (local_248 != 0) {
LAB_101d9f60:
            *(undefined1 *)((&DAT_1212b9c4)[local_28] + 0x2f1868) = 0;
            return 0xffffffff;
          }
          local_24c = 0x7e1;
          goto LAB_101d9f94;
        }
        if (local_248 == 2) {
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x8000000) != 0) {
            local_24c = 0x3f9;
            goto LAB_101d9f94;
          }
        }
        else {
          if (local_248 != 3) goto LAB_101d9f60;
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x8000000) != 0) {
            local_24c = 0x3fa;
            goto LAB_101d9f94;
          }
        }
      }
    }
    FUN_11310e2c(local_170,"DMA %s table",PTR_s_PORT_TAB_11ab3ac0);
    iVar5 = FUN_101d8368(param_3,local_170,&DAT_11374d20,local_260);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_260; local_268 = local_268 + 1) {
        iVar5 = FUN_108020c0(local_28,0xde3,0xffffffff,
                             *(undefined4 *)
                              (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) +
                                                0x24) + 0x378c) + 0xc),
                             *(undefined4 *)((&DAT_1212ba0c)[local_28] + 0xcff00),
                             *(undefined4 *)((int)param_3 + 0x14));
        if (iVar5 < 0) {
          local_278 = 0xffffffff;
          break;
        }
      }
    }
    FUN_101d8434(param_3);
    if (*(int *)((&DAT_1212ba0c)[local_28] + 0xf8f60) == -1) {
      local_24c = 0x108e;
    }
    else {
      local_24c = 0x10ab;
    }
    FUN_11310e2c(local_170,"DMA %s table",(&PTR_s_ACTIONPROFILETABLE_11ab0334)[local_24c]);
    iVar5 = FUN_101d8368(param_3,local_170,&DAT_11374d20,local_260);
    if (iVar5 != 0) {
      for (local_268 = 0; local_268 < local_260; local_268 = local_268 + 1) {
        iVar5 = FUN_108020c0(local_28,local_24c,0xffffffff,
                             *(undefined4 *)
                              (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) +
                                                0x24) + local_24c * 4) + 0xc),
                             *(undefined4 *)((&DAT_1212ba0c)[local_28] + local_24c * 0xec + 0x31bc),
                             *(undefined4 *)((int)param_3 + 0x14));
        if (iVar5 < 0) {
          local_278 = 0xffffffff;
          break;
        }
      }
    }
    FUN_101d8434(param_3);
    *(undefined1 *)((&DAT_1212b9c4)[local_28] + 0x2f1868) = 0;
  }
  return local_278;
}



/* === FUN_10166948 (size=1416) === */

undefined4 FUN_10166948(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  uint local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined2 local_9c;
  undefined4 local_98;
  uint local_94;
  undefined4 local_88;
  undefined4 local_7c;
  undefined4 local_78;
  undefined2 local_74;
  undefined1 auStack_70 [16];
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  int local_4c;
  uint local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  int local_10;
  
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0xffffffff;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  FUN_112b0cbc(&local_c4);
  memset(&local_78,0,6);
  FUN_100c0b28(local_18,auStack_70);
  FUN_100c0970(auStack_70,&UNK_1135e158,0xc05,0,&local_78,0);
  FUN_100c0970(auStack_70,&DAT_1135d3ac,0x801,0,&local_30,0);
  FUN_100c0970(auStack_70,&DAT_1135eabc,0x801,0,&local_34,0);
  FUN_100c0970(auStack_70,&UNK_1135eac0,0x803,0,&local_38,0);
  FUN_100c0970(auStack_70,"Group",0x801,0,&local_2c,0);
  if (local_10 == 0) {
    FUN_100c0970(auStack_70,&DAT_1135ea14,0x806,0,&local_58,0);
  }
  else {
    FUN_100c0970(auStack_70,&DAT_1135ea14,0xc0c,0,&local_28,0);
  }
  FUN_100c0970(auStack_70,"Replace",0x803,0,&local_40,0);
  FUN_100c0970(auStack_70,&UNK_1135d6c4,0x80a,0,&local_48,0);
  FUN_100c0970(auStack_70,&UNK_1135e144,0x801,0,&local_5c,0);
  FUN_100c0970(auStack_70,&UNK_1135eaac,0x803,0,&local_44,0);
  FUN_100c0970(auStack_70,"MOdule",0x801,0,&local_54,0);
  FUN_100c0970(auStack_70,"Trunk",0x801,0,&local_50,0);
  FUN_100c0970(auStack_70,"Untag",0x803,0,&local_4c,0);
  FUN_100c0970(auStack_70,"HOST_AS_ROUTE",0x803,0,&local_60,0);
  FUN_100c0970(auStack_70,&UNK_1135e644,0x803,0,&local_3c,0);
  iVar1 = FUN_1008dfb4(local_14,auStack_70,&local_7c);
  if (iVar1 != 0) {
    local_c0 = local_30;
    local_a8 = local_34;
    local_88 = local_2c;
    if (local_38 != 0) {
      local_c4 = local_c4 | 0x400;
    }
    if (local_10 == 0) {
      local_bc = local_58;
    }
    else {
      local_b8 = local_28;
      local_b4 = local_24;
      local_b0 = local_20;
      local_ac = local_1c;
      local_c4 = local_c4 | 0x20000;
    }
    if (local_60 != 0) {
      local_c4 = local_c4 | 0x10000;
    }
    local_a4 = local_5c;
    local_a0 = local_78;
    local_9c = local_74;
    if ((local_48 >> 0x1a == 0) || (0x29 < local_48 >> 0x1a)) {
      local_98 = local_54;
      if ((int)local_50 < 0) {
        local_94 = local_48;
      }
      else {
        local_c4 = local_c4 | 0x200;
        local_94 = local_50;
      }
    }
    else {
      local_94 = local_48;
    }
    if (local_44 != 0) {
      local_c4 = local_c4 | 0xc;
    }
    if (local_4c != 0) {
      local_c4 = local_c4 | 2;
    }
    if (local_40 != 0) {
      local_c4 = local_c4 | 0x100;
    }
    if (local_3c != 0) {
      local_c4 = local_c4 | 0x1000;
    }
    iVar1 = FUN_103f3128(local_18,&local_c4);
    if (iVar1 < 0) {
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar1 = -iVar1;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10320d20("%s: Error creating entry in L3 host table: %s\n",*local_14,
                   (&PTR_DAT_11e43a78)[iVar1]);
      local_7c = 0xffffffff;
    }
    else {
      local_7c = 0;
    }
  }
  return local_7c;
}



/* === FUN_1075cff0 (size=1008) === */

void FUN_1075cff0(uint *param_1)

{
  uint local_28;
  
  if (param_1 != (uint *)0x0) {
    FUN_10760cd4(0x8000,"flags: 0x%x  vrf: %d\n",*param_1,param_1[1]);
    if ((*param_1 & 0x20000) == 0) {
      FUN_10760cd4(0x8000,"defip_ip_addr: 0x%x\n",param_1[2]);
    }
    else {
      FUN_10760cd4(0x8000,"defip_ip6_addr - ");
      for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
        FUN_10760cd4(0x8000,&UNK_113b268c,*(undefined1 *)((int)param_1 + local_28 + 0xc));
      }
      FUN_10760cd4(0x8000,&DAT_113b2694);
    }
    FUN_10760cd4(0x8000,"defip_sub_len: %d defip_index: %d\n",param_1[7],param_1[8]);
    for (local_28 = 0; local_28 < 6; local_28 = local_28 + 1) {
      FUN_10760cd4(0x8000,"defip_mac_addr - ");
      FUN_10760cd4(0x8000,&UNK_113b268c,*(undefined1 *)((int)param_1 + local_28 + 0x24));
    }
    if ((*param_1 & 0x20000) == 0) {
      FUN_10760cd4(0x8000,"defip_nexthop_ip: 0x%x\n",param_1[0xb]);
    }
    else {
      FUN_10760cd4(0x8000,"\ndefip_nexthop_ip6 - ");
      for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
        FUN_10760cd4(0x8000,&UNK_113b268c,*(undefined1 *)((int)param_1 + local_28 + 0x30));
      }
      FUN_10760cd4(0x8000,&DAT_113b2694);
    }
    FUN_10760cd4(0x8000,"defip_tunnel: %d defip_prio: %d\n",param_1[0x10],param_1[0x11]);
    FUN_10760cd4(0x8000,"defip_intf: %d defip_port_tgid: %d\n",param_1[0x12],param_1[0x13]);
    FUN_10760cd4(0x8000,"defip_stack_port: %d defip_modid: %d\n",param_1[0x14],param_1[0x15]);
    FUN_10760cd4(0x8000,"defip_vid: %d defip_ecmp: %d\n",*(undefined2 *)(param_1 + 0x16),
                 param_1[0x17]);
    FUN_10760cd4(0x8000,"defip_ecmp_count: %d defip_ecmp_index: %d\n",param_1[0x18],param_1[0x19]);
    FUN_10760cd4(0x8000,"defip_l3hw_index: %d defip_tunnel_option: %d\n",param_1[0x1a],param_1[0x1b]
                );
    FUN_10760cd4(0x8000,"defip_mpls_label: %d defip_lookup_class: %d\n",param_1[0x1c],param_1[0x1d])
    ;
  }
  return;
}



/* === FUN_10133e74 (size=2272) === */

undefined4 FUN_10133e74(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  char *__s1;
  undefined4 uVar3;
  
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    __s1 = *(char **)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    __s1 = (char *)0x0;
  }
  if (__s1 == (char *)0x0) {
    uVar3 = 0xfffffffe;
  }
  else {
    iVar2 = strcasecmp(__s1,"all");
    bVar1 = iVar2 == 0;
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"cosq"), iVar2 == 0)) {
      FUN_10472fc0(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"port"), iVar2 == 0)) {
      FUN_10628d2c(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"stack"), iVar2 == 0)) {
      FUN_10650af4(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"trunk"), iVar2 == 0)) {
      FUN_10718134(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"time"), iVar2 == 0)) {
      FUN_106fc880(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"vlan"), iVar2 == 0)) {
      FUN_10748d78(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l2"), iVar2 == 0)) {
      FUN_105148a0(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"mcast"), iVar2 == 0)) {
      FUN_1054351c(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"mirror"), iVar2 == 0)) {
      FUN_10567f58(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"stat"), iVar2 == 0)) {
      FUN_1065d38c(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"stg"), iVar2 == 0)) {
      FUN_106ba510(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"link"), iVar2 == 0)) {
      FUN_1053fd8c(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"qos"), iVar2 == 0)) {
      FUN_106301d4(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"fcoe"), iVar2 == 0)) {
      FUN_10478840(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3"), iVar2 == 0)) {
      FUN_10913638(param_1,0xffffffff);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-defip"), iVar2 == 0)) {
      FUN_10913638(param_1,2);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-intf"), iVar2 == 0)) {
      FUN_10913638(param_1,1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-ecmp"), iVar2 == 0)) {
      FUN_10913638(param_1,4);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-host"), iVar2 == 0)) {
      FUN_10913638(param_1,8);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-lpm"), iVar2 == 0)) {
      FUN_10913638(param_1,0x10);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-tunnel"), iVar2 == 0)) {
      FUN_10913638(param_1,0x20);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"l3-nh"), iVar2 == 0)) {
      FUN_10913638(param_1,0x40);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"ipmc"), iVar2 == 0)) {
      FUN_105037f4(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"extlpm"), iVar2 == 0)) {
      FUN_10af2e18(param_1);
    }
    if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c38) & 0x80) != 0) &&
       ((bVar1 || (iVar2 = strcasecmp(__s1,"failover"), iVar2 == 0)))) {
      FUN_10c21c34(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"multicast"), iVar2 == 0)) {
      FUN_1057f2f4(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"mpls"), iVar2 == 0)) {
      FUN_10b6f8c4(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"common"), iVar2 == 0)) {
      FUN_10b9855c(param_1);
    }
    if (*(int *)((&DAT_1212b9c4)[param_1] + 0x2f2c34) < 0) {
      if ((bVar1) || (iVar2 = strcasecmp(__s1,"subport"), iVar2 == 0)) {
        FUN_10c8d758(param_1);
      }
    }
    else if ((bVar1) || (iVar2 = strcasecmp(__s1,"subport"), iVar2 == 0)) {
      FUN_10b839d8(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"niv"), iVar2 == 0)) {
      FUN_10588840(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"extender"), iVar2 == 0)) {
      FUN_10474764(param_1);
    }
    if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c3c) & 2) != 0) &&
       ((bVar1 || (iVar2 = strcasecmp(__s1,"trill"), iVar2 == 0)))) {
      FUN_109b65b8(param_1);
    }
    if ((bVar1) || (iVar2 = strcasecmp(__s1,"ipfix"), iVar2 == 0)) {
      FUN_104fde94(param_1);
    }
    if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c30) & 0x40000000) != 0) &&
       ((bVar1 || (iVar2 = strcasecmp(__s1,"oam"), iVar2 == 0)))) {
      FUN_10589eac(param_1);
    }
    if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c44) & 2) != 0) &&
       ((bVar1 || (iVar2 = strcasecmp(__s1,"l2gre"), iVar2 == 0)))) {
      FUN_1051c6d0(param_1);
    }
    if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c44) & 0x200000) != 0) &&
       ((bVar1 || (iVar2 = strcasecmp(__s1,"vxlan"), iVar2 == 0)))) {
      FUN_1074d410(param_1);
    }
    uVar3 = 0;
  }
  return uVar3;
}



/* === FUN_101418b8 (size=8744) === */

undefined4 FUN_101418b8(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_68;
  undefined4 local_64;
  char *local_60;
  undefined1 auStack_4c [52];
  undefined4 local_18;
  int local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  piVar1 = (int *)FUN_11310fbc(0x618,"Qualifier Space");
  for (local_68 = 0; local_68 < 0x186; local_68 = local_68 + 1) {
    iVar2 = FUN_11310fbc(8,"Qual Desc/Mask");
    piVar1[local_68] = iVar2;
  }
  if (*(int *)(local_14 + 0x2008) < *(int *)(local_14 + 0x2004)) {
    local_60 = *(char **)(local_14 + *(int *)(local_14 + 0x2008) * 4 + 4);
    *(int *)(local_14 + 0x2008) = *(int *)(local_14 + 0x2008) + 1;
  }
  else {
    local_60 = (char *)0x0;
  }
  if (local_60 == (char *)0x0) {
    local_60 = "All";
    local_64 = 0xffffffff;
  }
  else {
    iVar2 = strcasecmp(local_60,"lookup");
    if ((iVar2 == 0) || (iVar2 = strcasecmp(local_60,"vfp"), iVar2 == 0)) {
      local_64 = 1;
    }
    else {
      iVar2 = strcasecmp(local_60,"ingress");
      if ((iVar2 == 0) || (iVar2 = strcasecmp(local_60,"ifp"), iVar2 == 0)) {
        local_64 = 0;
      }
      else {
        iVar2 = strcasecmp(local_60,"egress");
        if ((iVar2 == 0) || (iVar2 = strcasecmp(local_60,"efp"), iVar2 == 0)) {
          local_64 = 2;
        }
        else {
          iVar2 = strcasecmp(local_60,"external");
          if ((iVar2 == 0) || (iVar2 = strcasecmp(local_60,"ext"), iVar2 == 0)) {
            local_64 = 3;
          }
          else {
            local_60 = "All";
            local_64 = 0xffffffff;
          }
        }
      }
    }
  }
  for (local_68 = 0; local_68 < 0x186; local_68 = local_68 + 1) {
    *(undefined **)piVar1[local_68] = &DAT_11357ad4;
    *(undefined **)(piVar1[local_68] + 4) = &DAT_11357ad4;
  }
  *(char **)*piVar1 = "Source IPv6 Address";
  *(char **)(*piVar1 + 4) = "IPv6 Address mask";
  *(char **)piVar1[1] = "Destination IPv6 Address";
  *(char **)(piVar1[1] + 4) = "IPv6 Address mask";
  *(char **)piVar1[2] = "Top 64-bits of Source IPv6 Address";
  *(char **)(piVar1[2] + 4) = "64-bits of IPv6 Address mask";
  *(char **)piVar1[3] = "Top 64-bits of Destination IPv6 Address";
  *(char **)(piVar1[3] + 4) = "64-bits of IPv6 Address mask";
  *(char **)piVar1[4] = "Lower 64-bits of Source IPv6 Address";
  *(char **)(piVar1[4] + 4) = "64-bits of IPv6 Address mask";
  *(char **)piVar1[5] = "Lower 64-bits of Destination IPv6 Address";
  *(char **)(piVar1[5] + 4) = "64-bits of IPv6 Address mask";
  *(char **)piVar1[9] = "Source IPv4 Address";
  *(char **)(piVar1[9] + 4) = "IPv4 Address mask";
  *(char **)piVar1[10] = "Destination IPv4 Address";
  *(char **)(piVar1[10] + 4) = "IPv4 Address";
  *(char **)piVar1[0xc] = "Single Input Port";
  *(char **)(piVar1[0xc] + 4) = "Port Mask";
  *(char **)piVar1[0x56] = "Single Output Port";
  *(char **)(piVar1[0x56] + 4) = "Port Mask";
  *(char **)piVar1[0xd] = "Input Port Bitmap";
  *(char **)(piVar1[0xd] + 4) = "Port Bitmap Mask";
  *(char **)piVar1[0xe] = "Output Port Bitmap";
  *(char **)(piVar1[0xe] + 4) = "Port Bitmap Mask";
  *(char **)piVar1[0xf] = "0 or 1";
  *(char **)(piVar1[0xf] + 4) = "0 or 1";
  *(char **)piVar1[0x3c] = "0 or 1";
  *(char **)(piVar1[0x3c] + 4) = "0 or 1";
  *(char **)piVar1[0x10] = "20-bit IPv6 Flow Label";
  *(char **)(piVar1[0x10] + 4) = "20-bit mask";
  *(char **)piVar1[0x20] = "8-bit IPv6 Hop Limit";
  *(char **)(piVar1[0x20] + 4) = "8-bit mask";
  *(char **)piVar1[0x11] = "Outer VLAN tag";
  *(char **)(piVar1[0x11] + 4) = "16-bit mask";
  *(char **)piVar1[0x13] = "Outer VLAN priority";
  *(char **)(piVar1[0x13] + 4) = "3-bit mask";
  *(char **)piVar1[0x14] = "Outer VLAN CFI";
  *(char **)(piVar1[0x14] + 4) = "1-bit mask";
  *(char **)piVar1[0x12] = "Outer VLAN id";
  *(char **)(piVar1[0x12] + 4) = "12-bit mask";
  *(char **)piVar1[0x15] = "Inner VLAN tag";
  *(char **)(piVar1[0x15] + 4) = "16-bit mask";
  *(char **)piVar1[0x17] = "Inner VLAN priority";
  *(char **)(piVar1[0x17] + 4) = "3-bit mask";
  *(char **)piVar1[0x18] = "Inner VLAN CFI";
  *(char **)(piVar1[0x18] + 4) = "1-bit mask";
  *(char **)piVar1[0x16] = "Inner VLAN id";
  *(char **)(piVar1[0x16] + 4) = "12-bit mask";
  *(char **)piVar1[0x1a] = "Range ID";
  *(char **)(piVar1[0x1a] + 4) = "Normal=0, Invert=1";
  *(char **)piVar1[0x1b] = "TCP/UDP Source port";
  *(char **)(piVar1[0x1b] + 4) = "16-bit mask";
  *(char **)piVar1[0x1c] = "TCP/UDP Destination port";
  *(char **)(piVar1[0x1c] + 4) = "16-bit mask";
  *(char **)piVar1[0x1d] = "Ethernet Type";
  *(char **)(piVar1[0x1d] + 4) = "16-bit mask";
  *(char **)piVar1[0x5f] = "L4 ports valid bit";
  *(char **)(piVar1[0x5f] + 4) = "L4 ports valid bit mask";
  *(char **)piVar1[0x60] = "Mirrored only";
  *(char **)(piVar1[0x60] + 4) = "Mirrored only mask";
  *(char **)piVar1[0x61] = "Tunnel terminated";
  *(char **)(piVar1[0x61] + 4) = "Tunnel terminated mask";
  *(char **)piVar1[0x62] = "Mpls terminated";
  *(char **)(piVar1[0x62] + 4) = "Mpls terminated mask";
  *(char **)piVar1[0x1e] = "IP protocol field";
  *(char **)(piVar1[0x1e] + 4) = "8-bit mask";
  *(char **)piVar1[0x1f] = "Differential Code Point";
  *(char **)(piVar1[0x1f] + 4) = "8-bit mask";
  *(char **)piVar1[0x5a] = "Vlan tag format";
  *(char **)(piVar1[0x5a] + 4) = "8-bit mask";
  *(char **)piVar1[0x5b] = "Vlan tag format";
  *(char **)(piVar1[0x5b] + 4) = "8-bit mask";
  *(char **)piVar1[0x8e] = "Internal priority";
  *(char **)(piVar1[0x8e] + 4) = "8-bit mask";
  *(char **)piVar1[0x20] = "Time to live";
  *(char **)(piVar1[0x20] + 4) = "8-bit mask";
  *(char **)piVar1[0x1e] = "IPv6 Next Header";
  *(char **)(piVar1[0x1e] + 4) = "8-bit mask";
  *(char **)piVar1[0x1f] = "IPv6 Next Header";
  *(char **)(piVar1[0x1f] + 4) = "8-bit mask";
  *(char **)piVar1[0x20] = "IPv6 Hop Limit";
  *(char **)(piVar1[0x20] + 4) = "8-bit mask";
  *(char **)piVar1[0x24] = "Source Trunk Group ID";
  *(char **)(piVar1[0x24] + 4) = "8-bit mask";
  *(char **)piVar1[0x29] = "Destination Trunk Group ID";
  *(char **)(piVar1[0x29] + 4) = "8-bit mask";
  *(char **)piVar1[0x2a] = "TCP control flags";
  *(char **)(piVar1[0x2a] + 4) = "8-bit mask";
  *(char **)piVar1[0x2d] = "Source L2 class";
  *(char **)(piVar1[0x2d] + 4) = "Source L2 class mask";
  *(char **)piVar1[0x2e] = "Source L3 class";
  *(char **)(piVar1[0x2e] + 4) = "Source L3 class mask";
  *(char **)piVar1[0x2f] = "Source Field class";
  *(char **)(piVar1[0x2f] + 4) = "Source Field class mask";
  *(char **)piVar1[0x30] = "Destination L2 class";
  *(char **)(piVar1[0x30] + 4) = "Destination L2 class mask";
  *(char **)piVar1[0x31] = "Destination L3 class";
  *(char **)(piVar1[0x31] + 4) = "Destination L3 class mask";
  *(char **)piVar1[0x32] = "Destination Field class";
  *(char **)(piVar1[0x32] + 4) = "Destination Field class mask";
  *(char **)piVar1[0x35] = "Module Header opcodes";
  *(char **)(piVar1[0x35] + 4) = "3-bit mask";
  *(char **)piVar1[0x36] = "IPv4 Flags";
  *(char **)(piVar1[0x36] + 4) = "3-bit mask";
  *(char **)piVar1[0x3d] = "bcm_field_IpType_t";
  *(char **)piVar1[0x59] = "bcm_field_L2Format_t";
  *(char **)piVar1[0x3f] = "bcm_field_decap_t";
  *(char **)piVar1[0x40] = "HiGig=1, non-HiGig=0";
  *(undefined **)(piVar1[0x40] + 4) = &DAT_11358528;
  *(char **)piVar1[0x42] = "HiGig=1, non-HiGig=0";
  *(undefined **)(piVar1[0x42] + 4) = &DAT_11358528;
  *(char **)piVar1[0x37] = "Inner vlan tag tpid";
  *(char **)piVar1[0x38] = "Outer vlan tag tpid";
  *(char **)piVar1[0x43] = "bcm_field_stage_t";
  *(char **)piVar1[0x44] = "Ingress FP pipeline stage";
  *(char **)piVar1[0x47] = "Lookup FP pipeline stage";
  *(char **)piVar1[0x48] = "Egress FP pipeline stage";
  *(char **)piVar1[0x4b] = "1 if SrcIp==DstIp, 0 otherwise";
  *(char **)piVar1[0x4c] = "1 if L4 Src.==Dst., 0 otherwise";
  *(char **)piVar1[0x4d] = "1 if TCP Sequence#==0, 0 if !=";
  *(char **)piVar1[0x4d] = "1 if TCP Sequence#==0, 0 if !=";
  *(char **)piVar1[0x83] = "Destination L3 Egress id.";
  *(char **)piVar1[0x86] = "Destination mpls gport.";
  *(char **)piVar1[0x88] = "Destination mim gport.";
  *(char **)piVar1[0x8a] = "Destination wlan gport.";
  *(char **)piVar1[0x84] = "Destination multicast group.";
  *(char **)piVar1[0x85] = "Source mpls gport.";
  *(char **)piVar1[0x87] = "Source mim gport.";
  *(char **)piVar1[0x89] = "Source wlan gport.";
  *(char **)piVar1[0x8b] = "Source mod port gport.";
  *(char **)piVar1[0x25] = "Source Trunk Member mod port gport.";
  *(char **)piVar1[0x4f] = "Interface Class L2.";
  *(char **)(piVar1[0x4f] + 4) = "Interface Class L2.";
  *(char **)piVar1[0x50] = "Interface Class L3.";
  *(char **)(piVar1[0x50] + 4) = "Interface Class L3.";
  *(char **)piVar1[0x51] = "Interface Class Port.";
  *(char **)(piVar1[0x51] + 4) = "Interface Class Port.";
  *(char **)piVar1[0xdb] = "Interface Class Virtual Port.";
  *(char **)(piVar1[0xdb] + 4) = "Interface Class Virtual Port.";
  *(char **)piVar1[0x4e] = "TCP Size";
  *(char **)(piVar1[0x4e] + 4) = "8-bit mask";
  *(char **)piVar1[0x54] = "VRF id";
  *(char **)(piVar1[0x54] + 4) = "VRF id mask";
  *(char **)piVar1[0x55] = "L3 ingress interface";
  *(char **)(piVar1[0x55] + 4) = "L3 ingress interface mask";
  *(char **)piVar1[0x5c] = "Next Header In Ext Hdr";
  *(char **)(piVar1[0x5c] + 4) = "Next Header byte mask";
  *(char **)piVar1[0x5d] = "Next Header Sub Code";
  *(char **)(piVar1[0x5d] + 4) = "Next Header Sub Code mask";
  *(char **)piVar1[0x52] = "1 should be L3 routed 0 otherwise";
  *(char **)(piVar1[0x52] + 4) = "Routed mask";
  *(char **)piVar1[0x79] = "1 DOS attac 0 otherwise";
  *(char **)(piVar1[0x79] + 4) = "Dos attack mask";
  *(char **)piVar1[0x78] = "1 Star, G hit 0 otherwise";
  *(char **)(piVar1[0x78] + 4) = "Star, G entry hit mask";
  *(char **)piVar1[0x99] = "1 My Station table hit, 0 otherwise";
  *(char **)(piVar1[0x99] + 4) = "My Station table hit mask";
  *(char **)piVar1[0x77] = "1 L3 dest route table hit, 0 otherwise";
  *(char **)(piVar1[0x77] + 4) = "L3 dest route table hit mask";
  *(char **)piVar1[0x76] = "1 L3 dest host table hit, 0 otherwise";
  *(char **)(piVar1[0x76] + 4) = "L3 dest host table hit mask";
  *(char **)piVar1[0x75] = "1 L3 source host table hit , 0 otherwise";
  *(char **)(piVar1[0x75] + 4) = "L3 source host table hit mask";
  *(char **)piVar1[0x74] = "1 L2 dest cache hit, 0 otherwise";
  *(char **)(piVar1[0x74] + 4) = "L2 dest cache hit mask";
  *(char **)piVar1[0x73] = "1 L2 src station move, 0 otherwise";
  *(char **)(piVar1[0x73] + 4) = "L2 src station move mask";
  *(char **)piVar1[0x70] = "1 L2 src lookup success, 0 otherwise";
  *(char **)(piVar1[0x70] + 4) = "L2 src lookup mask";
  *(char **)piVar1[0x72] = "1 L2 dest lookup success, 0 otherwise";
  *(char **)(piVar1[0x72] + 4) = "L2 dest lookup mask";
  *(char **)piVar1[0x71] = "1 L2 src static, 0 otherwise";
  *(char **)(piVar1[0x71] + 4) = "L2 src static mask";
  *(char **)piVar1[0x6f] = "BCM_STG_STP_XXX";
  *(char **)(piVar1[0x6f] + 4) = "STG Stp state mask";
  *(char **)piVar1[0x6e] = "Forwarding vlan id valid.";
  *(char **)(piVar1[0x6e] + 4) = "Forwarding vlan id valid mask";
  *(char **)piVar1[0x6d] = "Vlan Translation table hit.";
  *(char **)(piVar1[0x6d] + 4) = "Vlan Translation table hit mask";
  *(char **)piVar1[0x96] = "VNTAG data";
  *(char **)(piVar1[0x96] + 4) = "VNTAG mask";
  *(char **)piVar1[0x97] = "CNTAG data";
  *(char **)(piVar1[0x97] + 4) = "CNTAG mask";
  *(char **)piVar1[0x98] = "Fabric queue tag data";
  *(char **)(piVar1[0x98] + 4) = "Fabric queue tag mask";
  *(char **)piVar1[0x9d] = "NextHops data";
  *(char **)(piVar1[0x9d] + 4) = "NextHops mask";
  *(char **)piVar1[0xc2] = "CPU CosQ data";
  *(char **)(piVar1[0xc2] + 4) = "6-bit mask";
  *(char **)piVar1[0xc4] = "Src (mod/port)/MPLS/MiM/WLAN/Niv/Vlan gport";
  *(char **)piVar1[99] = "Source IPv4 Address";
  *(char **)(piVar1[99] + 4) = "IPv4 Address mask";
  *(char **)piVar1[100] = "Destination IPv4 Address";
  *(char **)(piVar1[100] + 4) = "IPv4 Address mask";
  *(char **)piVar1[0x10b] = "MPLS outer label popped data (1bit)";
  *(char **)(piVar1[0x10b] + 4) = "MPLS outer label popped mask";
  *(char **)piVar1[0x10c] = "MPLS Station hit unterminated data (1bit)";
  *(char **)(piVar1[0x10c] + 4) = "MPLS Station hit unterminated mask";
  *(char **)piVar1[0x10d] = "Class Id value";
  *(char **)(piVar1[0x10d] + 4) = "Mask for Class Id value";
  *(char **)piVar1[0x10e] = "Class Id value";
  *(char **)(piVar1[0x10e] + 4) = "Mask for Class Id value";
  *(char **)piVar1[0x11a] = "Packets for NAT to happen";
  *(char **)(piVar1[0x11a] + 4) = "Mask for Nat Needed value";
  *(char **)piVar1[0x11b] = "NAT Dest Realm Id";
  *(char **)(piVar1[0x11b] + 4) = "Mask for Nat Dest Realm Id";
  *(char **)piVar1[0x11c] = "NAT Src Realm Id";
  *(char **)(piVar1[0x11c] + 4) = "Mask for Nat Src Realm Id";
  *(char **)piVar1[0x11d] = "Packets with Icmp Error";
  *(char **)(piVar1[0x11d] + 4) = "Mask for Icmp Error value";
  *(char **)piVar1[0x7d] = "ICMP Type value";
  *(char **)(piVar1[0x7d] + 4) = "Mask for Icmp Type";
  *(char **)piVar1[0x96] = "VN-Tag";
  *(char **)(piVar1[0x96] + 4) = "VN-Tag mask";
  *(char **)piVar1[0x97] = "CN-Tag";
  *(char **)(piVar1[0x97] + 4) = "CN-Tag mask";
  *(char **)piVar1[0x8f] = "VLAN id";
  *(char **)(piVar1[0x8f] + 4) = "12-bit mask";
  *(char **)piVar1[0x3e] = "bcm_field_ForwardingType_t";
  *(char **)piVar1[300] = "FibreChan RCtl";
  *(char **)(piVar1[300] + 4) = "Mask for FibreChan RCtl";
  *(char **)piVar1[0x12d] = "FibreChan FCtl";
  *(char **)(piVar1[0x12d] + 4) = "Mask for FibreChan FCtl";
  *(char **)piVar1[0x12e] = "FibreChan CSCtl";
  *(char **)(piVar1[0x12e] + 4) = "Mask for FibreChan CSCtl";
  *(char **)piVar1[0x12f] = "FibreChan DFCtl";
  *(char **)(piVar1[0x12f] + 4) = "Mask for FibreChan DFCtl";
  *(char **)piVar1[0x130] = "FibreChan Type";
  *(char **)(piVar1[0x130] + 4) = "Mask for FibreChan Type";
  *(char **)piVar1[0x131] = "FibreChan SrcId";
  *(char **)(piVar1[0x131] + 4) = "Mask for FibreChan SrcId";
  *(char **)piVar1[0x132] = "FibreChan DstId";
  *(char **)(piVar1[0x132] + 4) = "Mask for FibreChan DstId";
  *(char **)piVar1[0x133] = "FibreChan Zone Check";
  *(char **)(piVar1[0x133] + 4) = "Mask for FibreChan Zone Check";
  *(char **)piVar1[0x134] = "FibreChan Src Fpma Check";
  *(char **)(piVar1[0x134] + 4) = "Mask for FibreChan Src Fpma Check";
  *(char **)piVar1[0x135] = "FibreChan Src Bind Check";
  *(char **)(piVar1[0x135] + 4) = "Mask for FibreChan Src Bind Check";
  *(char **)piVar1[0x136] = "FibreChan VFT Version";
  *(char **)(piVar1[0x136] + 4) = "Mask for FibreChan VFT Version";
  *(char **)piVar1[0x137] = "FibreChan VFT Pri";
  *(char **)(piVar1[0x137] + 4) = "Mask for FibreChan VFT Pri";
  *(char **)piVar1[0x138] = "FibreChan VFT Fabric Id";
  *(char **)(piVar1[0x138] + 4) = "Mask for FibreChan VFT Fabric Id";
  *(char **)piVar1[0x139] = "FibreChan VFT Hop Count";
  *(char **)(piVar1[0x139] + 4) = "Mask for FibreChan VFT Hop Count";
  *(char **)piVar1[0x13a] = "FibreChan VFT Vsan Id";
  *(char **)(piVar1[0x13a] + 4) = "Mask for FibreChan VFT Vsan Id";
  *(char **)piVar1[0x13b] = "FibreChan VFT Vsan Pri";
  *(char **)(piVar1[0x13b] + 4) = "Mask for FibreChan VFT Vsan Pri";
  *(char **)piVar1[0x13c] = "FibreChan VFT Valid";
  *(char **)(piVar1[0x13c] + 4) = "Mask for FibreChan VFT Valid";
  *(char **)piVar1[0x13d] = "FibreChan Fcoe SOF";
  *(char **)(piVar1[0x13d] + 4) = "Mask for FibreChan Fcoe SOF";
  *(char **)piVar1[0x13e] = "FibreChan Fcoe Version is Zero";
  *(char **)(piVar1[0x13e] + 4) = "Mask for FibreChan Fcoe Version is Zero";
  *(char **)piVar1[0x14a] = "SubportPktTag";
  *(char **)(piVar1[0x14a] + 4) = "SubportPktTag mask";
  *(char **)piVar1[0x14b] = "Source vxlan gport";
  *(char **)piVar1[0x14c] = "Destination vxlan gport";
  *(char **)piVar1[0x14d] = "OAM MDL Value";
  *(char **)(piVar1[0x14a] + 4) = "OAM MDL Mask";
  *(char **)piVar1[0x14f] = "Source niv gport";
  *(char **)piVar1[0x150] = "Destination niv gport";
  *(char **)piVar1[0x151] = "Dst Niv gport";
  *(char **)piVar1[0x184] = "Source vlan gport";
  *(char **)piVar1[0x185] = "Destination vlan gport";
  *(char **)piVar1[0x183] = "Class Id value";
  *(char **)(piVar1[0x183] + 4) = "Mask for Class Id value";
  FUN_10320d20("------------------------ FP STAGE: %s ----------------------\n",local_60);
  FUN_10320d20(&DAT_11357ea8,0x14,"QUALIFIER",0x28,&DAT_11359318,0x14,&UNK_11359320);
  for (local_68 = 0; local_68 < 0x186; local_68 = local_68 + 1) {
    iVar2 = FUN_10141648(local_18,local_64,local_68);
    if (((((((iVar2 != 0) && (local_68 != 0x23)) && (local_68 != 0x28)) &&
          ((local_68 != 6 && (local_68 != 7)))) &&
         ((local_68 != 0x2b && ((local_68 != 0x53 && (local_68 != 0x3b)))))) && (local_68 != 0x3a))
       && ((((local_68 != 0x19 && (local_68 != 0x26)) && (local_68 != 0x27)) &&
           (((local_68 != 0x2c && (local_68 != 0x21)) &&
            ((local_68 != 0x22 && ((local_68 != 0x33 && (local_68 != 0x34)))))))))) {
      uVar3 = FUN_1009c7f8(auStack_4c,local_68,1);
      FUN_10320d20(&DAT_11357ea8,0x14,uVar3,0x28,*(undefined4 *)piVar1[local_68],0x14,
                   *(undefined4 *)(piVar1[local_68] + 4));
    }
  }
  iVar2 = FUN_10141648(local_18,local_64,6);
  if (iVar2 != 0) {
    FUN_1014a388(&DAT_11357860,&DAT_11359328,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,7);
  if (iVar2 != 0) {
    FUN_1014a388(&DAT_11357860,"DstMac",0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x2b);
  if (iVar2 != 0) {
    FUN_1014bf48(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x53);
  if (iVar2 != 0) {
    FUN_1014c814(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x3b);
  if (iVar2 != 0) {
    FUN_1014caa4(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x3a);
  if (iVar2 != 0) {
    FUN_1014cd34(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x23);
  if (iVar2 != 0) {
    FUN_10148ce4(&DAT_11357860,"SrcPort",0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x28);
  if (iVar2 != 0) {
    FUN_10148ce4(&DAT_11357860,"DstPort",0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x33);
  if (iVar2 != 0) {
    FUN_1014bcc4(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x8d);
  if (iVar2 != 0) {
    FUN_1014c2b8(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x34);
  if (iVar2 != 0) {
    FUN_1014c224(&DAT_11357860,0x14);
  }
  iVar2 = FUN_10141648(local_18,local_64,0x3e);
  if (iVar2 != 0) {
    FUN_1014c34c(&DAT_11357860,0x14);
  }
  for (local_68 = 0; local_68 < 0x186; local_68 = local_68 + 1) {
    FUN_11310ee4(piVar1[local_68]);
  }
  FUN_11310ee4(piVar1);
  return 0;
}



/* === FUN_107575ec (size=688) === */

int FUN_107575ec(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  if ((*(int *)(&DAT_121242cc + param_1 * 4) == 0) || (iVar2 = FUN_10756a58(param_1), -1 < iVar2)) {
    uVar3 = FUN_11310fbc(0xc,"td2_l3_defip_pair128");
    *(undefined4 *)(&DAT_121242cc + param_1 * 4) = uVar3;
    if (*(int *)(&DAT_121242cc + param_1 * 4) == 0) {
      iVar2 = -2;
    }
    else {
      memset(*(void **)(&DAT_121242cc + param_1 * 4),0,0xc);
      iVar2 = *(int *)((&DAT_1212b9c4)[param_1] + 0x2f189c);
      *(short *)(*(int *)(&DAT_121242cc + param_1 * 4) + 8) = (short)iVar2;
      *(undefined2 *)(*(int *)(&DAT_121242cc + param_1 * 4) + 10) = 0;
      *(short *)(*(int *)(&DAT_121242cc + param_1 * 4) + 4) = (short)iVar2 + -1;
      if (iVar2 != 0) {
        puVar1 = *(undefined4 **)(&DAT_121242cc + param_1 * 4);
        uVar3 = FUN_11310fbc(iVar2 << 2,"td2_l3_defip_pair128_entry_array");
        *puVar1 = uVar3;
        if (**(int **)(&DAT_121242cc + param_1 * 4) == 0) {
          iVar2 = FUN_10756a58(param_1);
          if (iVar2 < 0) {
            return iVar2;
          }
          return -2;
        }
        memset((void *)**(undefined4 **)(&DAT_121242cc + param_1 * 4),0,iVar2 << 2);
      }
      iVar2 = FUN_10756bb8(param_1);
      if (iVar2 < 0) {
        iVar4 = FUN_10756a58(param_1);
        if (iVar4 < 0) {
          iVar2 = iVar4;
        }
      }
      else {
        iVar2 = 0;
      }
    }
  }
  return iVar2;
}



/* === FUN_1123f2f8 (size=2572) === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1123f2f8(int param_1,undefined4 param_2,undefined4 param_3,int param_4,uint *param_5,
                undefined4 *param_6,undefined4 *param_7,int param_8)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined1 uVar9;
  int iVar8;
  int local_258;
  uint local_254;
  int local_24c;
  int local_248;
  int local_244;
  undefined4 local_240;
  int local_20c;
  undefined1 auStack_208 [28];
  undefined4 local_1ec;
  int local_1e8;
  undefined1 auStack_1e4 [204];
  undefined8 local_118;
  undefined8 local_110;
  undefined8 local_108;
  undefined8 local_100;
  undefined1 auStack_f8 [208];
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  uint *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  int local_c;
  
  local_20c = 0;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  local_10 = param_7;
  local_c = param_8;
  memset(auStack_1e4,0,0xcc);
  local_244 = -1;
  local_240 = 0;
  local_118 = _DAT_117f6460;
  iVar2 = FUN_107a2924(local_28,0x7fe,local_24,0x87b0);
  uVar3 = FUN_107a2924(local_28,0x7fe,local_24,0x5596);
  uVar4 = FUN_107a2924(local_28,0x7fe,local_24,0xea66);
  if (local_1c == -2) {
    pcVar7 = "Global";
  }
  else {
    pcVar7 = "VRF";
  }
  FUN_10760cd4(0x10000,
               "Prefare AUX Scratch for searching TCAM in %s region, Key data: v6 %d global %d vrf %d:\n"
               ,pcVar7,iVar2,uVar3,uVar4);
  if (local_1c == -2) {
    uVar9 = local_c != 0;
    local_24c = FUN_11234c2c(local_28);
    if (local_24c != 0) {
      if ((*(uint *)(&DAT_1212b9c4)[local_28] & 0x20) == 0) {
        local_24c = 0;
      }
      else {
        local_24c = 3;
      }
    }
    FUN_107a2a0c(local_28,0x7fe,local_24,0x5596,1);
    FUN_107a2a0c(local_28,0x7fe,local_24,0xea66,0);
  }
  else {
    if (local_c == 0) {
      uVar9 = 2;
    }
    else {
      uVar9 = 3;
    }
    local_24c = FUN_11234c2c(local_28);
    if (local_24c != 0) {
      if ((*(uint *)(&DAT_1212b9c4)[local_28] & 0x20) == 0) {
        local_24c = 0;
      }
      else {
        local_24c = 0xc;
      }
    }
  }
  memset(auStack_208,0,0x1c);
  iVar5 = FUN_1124cd28(local_28,local_24,iVar2,uVar9,0,auStack_208);
  if (-1 < iVar5) {
    if (local_1c == -2) {
      FUN_107a2a0c(local_28,0x7fe,local_24,0x5596,uVar3);
      FUN_107a2a0c(local_28,0x7fe,local_24,0xea66,uVar4);
    }
    iVar5 = FUN_1124d1ec(local_28,2,auStack_208,1,&local_20c,local_18,local_14);
    puVar1 = PTR_s_L3_DEFIP_11ab232c;
    if (-1 < iVar5) {
      if (local_20c == 0) {
        FUN_10760cd4(0x10000,"Could not find bucket\n");
        iVar5 = -7;
      }
      else {
        uVar3 = FUN_11234f04(local_28,0x7fe,(int)*local_18 >> 1,1);
        FUN_10760cd4(0x10000,"Hit in memory %s, index %d, bucket_index %d\n",puVar1,uVar3,*local_14)
        ;
        if (iVar2 == 0) {
          iVar8 = 0x80a;
        }
        else {
          iVar8 = 0x80c;
        }
        iVar5 = FUN_11234c80(local_28,local_24,&local_1e8);
        if (-1 < iVar5) {
          local_248 = 0x18;
          if (iVar2 != 0) {
            if (((iVar2 == 0) || (iVar5 = FUN_11234c2c(local_28), iVar5 != 0)) ||
               ((*(uint *)(&DAT_1212b9c4)[local_28] & 0x20) != 0)) {
              local_248 = 0x10;
            }
            else {
              local_248 = 0x20;
            }
          }
          FUN_10760cd4(0x10000,"Start searching mem %s bucket %d(count %d) for Length %d\n",
                       (&PTR_s_ACTIONPROFILETABLE_11ab0334)[iVar8],*local_14,local_248,local_1e8);
          for (local_258 = 0; local_258 < local_248; local_258 = local_258 + 1) {
            memset(auStack_f8,0,0xcc);
            local_110 = DAT_117f7208;
            local_108 = DAT_117f7208;
            local_100 = DAT_117f7208;
            iVar5 = FUN_11236d54(local_28,iVar8,*local_14,local_258,local_24c,&local_1ec);
            if (iVar5 != -6) {
              iVar5 = FUN_10801b4c(local_28,iVar8,0xffffffff,local_1ec,auStack_f8);
              if (iVar5 < 0) {
                return iVar5;
              }
              iVar5 = FUN_107a2924(local_28,iVar8,auStack_f8,0xe37e);
              iVar6 = FUN_107a2924(local_28,iVar8,auStack_f8,0x76e0);
              FUN_10760cd4(0x10000,"Bucket %5d Index %6d: Valid %d, Length %d\n",*local_14,local_1ec
                           ,iVar5,iVar6);
              if ((iVar5 != 0) && (iVar6 <= local_1e8)) {
                if (iVar2 == 0) {
                  iVar5 = 0x20;
                }
                else {
                  iVar5 = 0x40;
                }
                FUN_112d1134(&local_110,iVar5 - iVar6,iVar6);
                FUN_107a20f0(local_28,iVar8,auStack_f8,0x7034,&local_108);
                uVar3 = FUN_107a2924(local_28,0x7fe,local_24,local_118._4_4_);
                local_100 = CONCAT44(local_100._0_4_,uVar3);
                uVar3 = FUN_107a2924(local_28,0x7fe,local_24,local_118._0_4_);
                local_100 = CONCAT44(uVar3,local_100._4_4_);
                FUN_10760cd4(0x10000,"\tmask %08x %08x\n\t key %08x %08x\n\thost %08x %08x\n",
                             local_110._4_4_,local_110._0_4_,local_108._4_4_,local_108._0_4_,
                             local_100._4_4_,uVar3);
                local_254 = iVar2 == 0 ^ 1;
                while ((-1 < (int)local_254 &&
                       (((*(uint *)(auStack_f8 + local_254 * 4 + -8) ^
                         *(uint *)((int)&local_108 + local_254 * 4)) &
                        *(uint *)((int)&local_110 + local_254 * 4)) == 0))) {
                  local_254 = local_254 - 1;
                }
                if (((int)local_254 < 0) &&
                   ((FUN_10760cd4(0x10000,"Found a match in mem %s bucket %d, index %d\n",
                                  (&PTR_s_ACTIONPROFILETABLE_11ab0334)[iVar8],*local_14,local_1ec),
                    local_244 == -1 || (local_244 < iVar6)))) {
                  local_240 = local_1ec;
                  memcpy(auStack_1e4,auStack_f8,0xcc);
                  local_244 = iVar6;
                }
              }
            }
          }
          if (local_244 == -1) {
            uVar3 = FUN_11234f04(local_28,0x7fe,(int)*local_18 >> 1,1);
            *local_10 = uVar3;
            FUN_10760cd4(0x10000,
                         "Miss in mem %s bucket %d, use associate data in mem %s LOG index %d\n",
                         (&PTR_s_ACTIONPROFILETABLE_11ab0334)[iVar8],*local_14,
                         PTR_s_L3_DEFIP_11ab232c,*local_10);
            iVar5 = FUN_10801b4c(local_28,0x7fe,0xffffffff,*local_10,local_20);
            if (-1 < iVar5) {
              if ((iVar2 == 0) && ((*local_18 & 1) != 0)) {
                FUN_11246354(local_28,local_20,local_20,1);
              }
              iVar5 = 0;
            }
          }
          else {
            iVar5 = FUN_1124dd24(local_28,auStack_1e4,iVar8,iVar2,local_1c,*local_14,local_240,
                                 local_20);
            if (-1 < iVar5) {
              *local_10 = local_240;
              FUN_10760cd4(0x10000,"Hit mem %s bucket %d, index %d\n",
                           (&PTR_s_ACTIONPROFILETABLE_11ab0334)[iVar8],*local_14,local_240);
            }
          }
        }
      }
    }
  }
  return iVar5;
}



/* === FUN_103e6cf0 (size=476) === */

undefined4 FUN_103e6cf0(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_48 = 0xfffffffd;
  }
  else {
    if (param_2 != 0) {
      local_40 = *(undefined4 *)(param_2 + 0x24);
      local_3c = *(undefined4 *)(param_2 + 0x28);
      local_38 = *(undefined4 *)(param_2 + 0x2c);
      local_34 = *(undefined4 *)(param_2 + 0x30);
      local_30 = *(undefined4 *)(param_2 + 0x34);
      local_2c = *(undefined4 *)(param_2 + 0x38);
      local_28 = *(undefined4 *)(param_2 + 0x3c);
      local_24 = *(undefined4 *)(param_2 + 0x40);
      FUN_1038a644(param_1,param_2 + 0x24);
    }
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_48 = (*(code *)(&PTR_FUN_11855f08)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 0x24) = local_40;
      *(undefined4 *)(param_2 + 0x28) = local_3c;
      *(undefined4 *)(param_2 + 0x2c) = local_38;
      *(undefined4 *)(param_2 + 0x30) = local_34;
      *(undefined4 *)(param_2 + 0x34) = local_30;
      *(undefined4 *)(param_2 + 0x38) = local_2c;
      *(undefined4 *)(param_2 + 0x3c) = local_28;
      *(undefined4 *)(param_2 + 0x40) = local_24;
    }
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l2_addr_add",2,1,param_1,0,0,local_48);
  }
  return local_48;
}



/* === FUN_101c86e4 (size=2824) === */

undefined4 FUN_101c86e4(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  int *local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  undefined1 auStack_d4 [16];
  undefined1 auStack_c4 [88];
  uint local_6c [21];
  int local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  
  local_e8 = *(int **)(&DAT_11eb8790 + param_1 * 4);
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  if (local_e8 == (int *)0x0) {
    local_e8 = (int *)FUN_11310fbc(0xa4,"tpacket");
    if (local_e8 == (int *)0x0) {
      FUN_101120a0(local_18,"ERROR: cannot allocate memory\n");
      return 0xffffffff;
    }
    memset(local_e8,0,0xa4);
    *(int **)(&DAT_11eb8790 + local_18 * 4) = local_e8;
  }
  if (*local_e8 == 0) {
    local_e8[0x1f] = 0x40;
    local_e8[0x20] = 0x40;
    local_e8[0x21] = 0x40;
    *local_e8 = 1;
    local_e8[0xb] = 1000;
    local_e8[10] = 1;
    local_e8[4] = 1;
    local_e8[9] = 1;
    local_e8[0x22] = 1;
    local_e8[3] = 1;
    local_e8[1] = 5;
    local_e8[5] = 0x8100;
    for (local_e4 = 0; local_e4 < 8; local_e4 = local_e4 + 1) {
      local_e8[local_e4 + 0xf] = 0;
    }
    for (local_e0 = 0; local_e0 < 8; local_e0 = local_e0 + 1) {
      local_e8[local_e0 + 0x17] = 0;
    }
    for (local_dc = 0; local_dc < 8; local_dc = local_dc + 1) {
      local_e8[local_dc + 0xf] =
           local_e8[local_dc + 0xf] |
           *(uint *)((&DAT_1212b9c4)[local_18] + (local_dc + 0x1328) * 4 + 0x14);
    }
  }
  FUN_100c0b28(local_18,auStack_d4);
  FUN_100c0970(auStack_d4,"FastPath",0x803,0,local_e8 + 2,0);
  FUN_100c0970(auStack_d4,"DestMac",0x808,0,local_e8 + 1,&PTR_s_UCHit_11850604);
  FUN_100c0970(auStack_d4,"PortBitMap",0xc07,0,local_e8 + 0xf,0);
  FUN_100c0970(auStack_d4,"UntagPortBitMap",0xc07,0,local_e8 + 0x17,0);
  FUN_100c0970(auStack_d4,"Tagged",0x803,0,local_e8 + 3,0);
  FUN_100c0970(auStack_d4,"VlanId",0x801,0,local_e8 + 4,0);
  FUN_100c0970(auStack_d4,&UNK_11372dbc,0x801,0,local_e8 + 5,0);
  FUN_100c0970(auStack_d4,"LengthStart",0x801,0,local_e8 + 0x1f,0);
  FUN_100c0970(auStack_d4,"LengthEnd",0x801,0,local_e8 + 0x20,0);
  FUN_100c0970(auStack_d4,"LengthInc",0x801,0,local_e8 + 0x21,0);
  FUN_100c0970(auStack_d4,"PortBitMap",0xc07,0,local_e8 + 0xf,0);
  FUN_100c0970(auStack_d4,"UntagPortBitMap",0xc07,0,local_e8 + 0x17,0);
  FUN_100c0970(auStack_d4,"PktsPerChain",0x801,0,local_e8 + 10,0);
  FUN_100c0970(auStack_d4,"Chains",0x801,0,local_e8 + 0xb,0);
  FUN_100c0970(auStack_d4,"Array",0x803,0,local_e8 + 9,0);
  FUN_100c0970(auStack_d4,"Operations",0x801,0,local_e8 + 0x22,0);
  iVar3 = FUN_100bfda8(local_14,auStack_d4);
  if ((iVar3 < 0) || (local_14[0x801] != local_14[0x802])) {
    if (((int)local_14[0x802] < (int)local_14[0x801]) && (local_14[local_14[0x802] + 1] != 0)) {
      if ((int)local_14[0x802] < (int)local_14[0x801]) {
        puVar4 = (undefined *)local_14[local_14[0x802] + 1];
      }
      else {
        puVar4 = (undefined *)0x0;
      }
    }
    else {
      puVar4 = &DAT_11372e14;
    }
    FUN_101120a0(local_18,"%s: Invalid option: %s\n",*local_14,puVar4);
    FUN_100c01a8(auStack_d4);
    uVar5 = 0xffffffff;
  }
  else {
    FUN_100c01a8(auStack_d4);
    if (local_e8[0x22] < 0x3e9) {
      if (local_e8[1] == 5) {
        if (local_e8[0x20] < 0x4001) {
          iVar3 = FUN_101c79a8(local_18,local_e8);
          uVar2 = DAT_11850600;
          uVar1 = DAT_118505f0;
          if (iVar3 < 0) {
            FUN_101c84e4(local_18,local_e8);
            uVar5 = 0xffffffff;
          }
          else {
            switch(local_e8[1]) {
            case 0:
              FUN_112b0700(local_6c,&DAT_118505dc,local_e8[4] & 0xffff);
              local_6c[0] = local_6c[0] | 0x20;
              iVar3 = FUN_103e6cf0(local_18,local_6c);
              uVar1 = DAT_118505e0;
              if (iVar3 < 0) {
                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                  iVar3 = -iVar3;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_101120a0(local_18,"bcm_l2_addr_add failed: %s\n",(&PTR_DAT_11e43a78)[iVar3]);
                return 0xffffffff;
              }
              local_e8[6] = DAT_118505dc;
              *(undefined2 *)(local_e8 + 7) = uVar1;
              break;
            case 1:
              iVar3 = FUN_103e6ecc(local_18,&DAT_118505dc,local_e8[4] & 0xffff);
              uVar1 = DAT_118505e0;
              if (iVar3 < 0) {
                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                  iVar3 = -iVar3;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_101120a0(local_18,"bcm_l2_addr_delete failed: %s\n",(&PTR_DAT_11e43a78)[iVar3]);
                return 0xffffffff;
              }
              local_e8[6] = DAT_118505dc;
              *(undefined2 *)(local_e8 + 7) = uVar1;
              break;
            case 2:
              FUN_112b2730(auStack_c4,&DAT_118505e4,local_e8[4] & 0xffff);
              iVar3 = FUN_103fe8a0(local_18,auStack_c4);
              uVar1 = DAT_118505e8;
              if (iVar3 < 0) {
                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                  iVar3 = -iVar3;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_101120a0(local_18,"bcm_mcast_addr_add failed: %s\n",(&PTR_DAT_11e43a78)[iVar3]);
                return 0xffffffff;
              }
              local_e8[6] = DAT_118505e4;
              *(undefined2 *)(local_e8 + 7) = uVar1;
              break;
            case 3:
              iVar3 = FUN_103fede0(local_18,&DAT_118505e4,local_e8[4] & 0xffff);
              uVar1 = DAT_118505e8;
              if ((iVar3 < 0) && (iVar3 != -7)) {
                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                  iVar3 = -iVar3;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_101120a0(local_18,"bcm_mcast_addr_remove failed: %s\n",
                             (&PTR_DAT_11e43a78)[iVar3]);
                return 0xffffffff;
              }
              local_e8[6] = DAT_118505e4;
              *(undefined2 *)(local_e8 + 7) = uVar1;
              break;
            case 4:
              local_e8[6] = DAT_118505ec;
              *(undefined2 *)(local_e8 + 7) = uVar1;
              break;
            case 5:
              local_e8[6] = DAT_118505ec;
              *(undefined2 *)(local_e8 + 7) = uVar1;
              break;
            case 6:
              local_e8[6] = DAT_118505fc;
              *(undefined2 *)(local_e8 + 7) = uVar2;
              uVar1 = DAT_118505f8;
              *(undefined4 *)((int)local_e8 + 0x1e) = DAT_118505f4;
              *(undefined2 *)((int)local_e8 + 0x22) = uVar1;
              break;
            default:
              return 0xffffffff;
            }
            *local_10 = local_e8;
            uVar5 = 0;
          }
        }
        else {
          FUN_101120a0(local_18,"Max supported pkt size is %d\n",0x4000);
          local_e8[0x20] = 0x4000;
          uVar5 = 0xffffffff;
        }
      }
      else {
        FUN_101120a0(local_18,"Only PortBitMap option supported for bcm_tx\n");
        uVar5 = 0xffffffff;
      }
    }
    else {
      FUN_101120a0(local_18,"Operations must be 1 <= # <= 1000\n");
      uVar5 = 0xffffffff;
    }
  }
  return uVar5;
}



