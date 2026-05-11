/* L3/netlink BIG functions decompiled */

/* === FUN_100142ac @ 0x100142ac (size=8004) === */

undefined1 FUN_100142ac(uint param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  void *pvVar8;
  void *__ptr;
  char cVar9;
  uint uVar10;
  void *pvVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined8 uVar17;
  int local_280;
  int local_27c;
  int local_278;
  int local_264;
  int local_260;
  int local_25c;
  int local_258;
  int local_254;
  int local_250;
  int local_24c;
  int local_248;
  int local_244;
  int local_240;
  int local_23c;
  int local_238;
  int local_234;
  int local_230;
  uint local_22c;
  uint local_228;
  void *local_224;
  int local_220;
  int local_21c;
  int local_218;
  undefined8 local_188;
  int aiStack_180 [4];
  int aiStack_170 [6];
  undefined4 local_158;
  undefined4 local_154;
  int aiStack_150 [2];
  int local_148;
  size_t local_144;
  undefined4 local_140;
  void *local_13c;
  undefined1 auStack_138 [40];
  undefined1 auStack_110 [40];
  undefined1 auStack_e8 [52];
  uint local_b4;
  uint local_b0;
  void *local_ac;
  uint local_a8;
  uint local_a4;
  void *local_a0;
  uint local_9c;
  uint local_98;
  void *local_94;
  int local_90;
  undefined1 auStack_8c [44];
  undefined1 auStack_60 [48];
  uint local_30;
  undefined8 local_28;
  
  local_30 = param_1;
  FUN_11316588(auStack_110,0x28,FUN_100161f0,aiStack_170 + 8);
  FUN_11316588(auStack_e8,0x28,FUN_10016288,aiStack_170 + 8);
  FUN_11316588(auStack_138,0x28,FUN_10016344,aiStack_170 + 8);
  local_280 = 0;
  local_148 = 0;
  local_27c = 0;
  local_278 = 0;
  bVar2 = false;
  bVar3 = false;
  local_25c = 0;
  local_258 = 0;
  local_254 = 0;
  local_250 = 0;
  uVar17 = FUN_1000b0b4();
  iVar4 = (int)((ulonglong)uVar17 >> 0x20);
  uVar10 = (uint)uVar17;
  local_24c = 0;
  local_248 = 0;
  local_244 = 0;
  local_240 = 0;
  local_23c = 0;
  local_238 = 0;
  local_234 = 0;
  for (local_230 = 0; local_230 < 2; local_230 = local_230 + 1) {
    aiStack_170[local_230 + 6] = 0;
    aiStack_180[local_230] = 0;
    aiStack_170[local_230 + 8] = 0;
    aiStack_170[local_230] = 0;
    aiStack_170[local_230 + 2] = 0;
    aiStack_170[local_230 + 4] = 0;
    *(undefined4 *)(&DAT_11e47520 + local_230 * 4) = 0;
  }
  if ((local_30 & 1) != 0) {
    memset(auStack_60,0,0x2c);
    uVar5 = FUN_1000ac48();
    uVar6 = FUN_1000ac1c();
    local_28 = CONCAT44(local_28._0_4_,local_28._4_4_);
    if (DAT_11e46fd4 != '\0') {
      local_188 = FUN_1000b0b4();
      local_28 = local_188;
    }
    local_140 = 0;
    local_144 = 0;
    local_13c = (void *)0x0;
    nl_cache_foreach(uVar5,auStack_e8,0);
    uVar5 = rtnl_route_alloc();
    rtnl_route_set_table(uVar5,0xff);
    nl_cache_foreach_filter(uVar6,uVar5,auStack_110,1);
    rtnl_route_set_table(uVar5,DAT_11e46f14);
    nl_cache_foreach_filter(uVar6,uVar5,auStack_110,0);
    qsort(local_13c,local_144,0x2c,FUN_10028f74);
    if (DAT_11e46fd4 != '\0') {
      FUN_1004783c(&local_188,"get_and_sort_kernel_routes");
    }
    local_224 = (void *)0x0;
    for (local_22c = 0; local_22c < local_144; local_22c = local_22c + 1) {
      pvVar8 = (void *)((int)local_13c + local_22c * 0x2c);
      pvVar11 = pvVar8;
      if (local_224 != (void *)0x0) {
        cVar9 = FUN_10028d2c(pvVar8,local_224);
        if (cVar9 == '\x01') {
          if (*(int *)((int)pvVar8 + 0x1c) == *(int *)((int)local_224 + 0x1c)) {
            iVar16 = FUN_10029284(pvVar8);
            iVar12 = FUN_10029284(local_224);
            if ((*(int *)((int)pvVar8 + 0x18) < *(int *)((int)local_224 + 0x18)) ||
               ((*(int *)((int)pvVar8 + 0x18) == *(int *)((int)local_224 + 0x18) &&
                (iVar12 < iVar16)))) {
              FUN_10028a48(local_224);
              memset(local_224,0,0x2c);
            }
            else {
              FUN_10028a48(pvVar8);
              memset(pvVar8,0,0x2c);
              pvVar11 = local_224;
            }
          }
          else if (*(uint *)((int)local_224 + 0x1c) < *(uint *)((int)pvVar8 + 0x1c)) {
            FUN_10028a48(local_224);
            memset(local_224,0,0x2c);
          }
          else {
            pvVar11 = local_224;
            if (*(uint *)((int)pvVar8 + 0x1c) < *(uint *)((int)local_224 + 0x1c)) {
              FUN_10028a48(pvVar8);
              memset(pvVar8,0,0x2c);
            }
          }
        }
      }
      local_224 = pvVar11;
    }
    if (DAT_11e46fd4 != '\0') {
      FUN_1004783c(&local_188,"krib_to_fib");
    }
    local_158 = 0;
    local_154 = 0;
    local_24c = 0;
    local_248 = 0;
    local_244 = 0;
    local_240 = 0;
    local_23c = 0;
    local_238 = 0;
    local_234 = 0;
    uVar6 = FUN_10049440(local_144 << 1);
    for (local_22c = 0; local_22c < local_144; local_22c = local_22c + 1) {
      pvVar11 = (void *)((int)local_13c + local_22c * 0x2c);
      iVar16 = memcmp(pvVar11,auStack_60,0x2c);
      if (iVar16 != 0) {
        if ((*(uint *)((int)pvVar11 + 0x1c) & 0x10) == 0) {
          bVar1 = false;
          local_264 = 1;
          if (local_244 < DAT_11f1df34) {
            local_260 = FUN_1000b638(pvVar11);
            if ((*(char *)((int)pvVar11 + 0x10) == '\n') && (local_260 == 0)) {
              local_264 = 2;
            }
            if ((int)(&DAT_11f1df2c)[local_260] < aiStack_170[local_260 + 6] + local_264) {
              aiStack_170[local_260 + 4] = aiStack_170[local_260 + 4] + 1;
              bVar1 = true;
            }
            else {
              aiStack_170[local_260 + 6] = aiStack_170[local_260 + 6] + local_264;
              local_244 = local_244 + 1;
              if (*(char *)((int)pvVar11 + 0x10) == '\n') {
                local_248 = local_248 + 1;
              }
              else {
                local_24c = local_24c + 1;
              }
            }
          }
          else {
            local_258 = local_258 + 1;
            bVar1 = true;
          }
          if (!bVar1) goto LAB_10014b9c;
          if (3 < DAT_11e46cd4) {
            pvVar8 = (void *)FUN_10029758(pvVar11);
            if (3 < DAT_11e46cd4) {
              uVar7 = bcm_l3_route_get();
              FUN_10047ec4(4,"%s %s:%d Out of route table %d entries for %s.  Skipping.\n",0x3b,
                           uVar7,"sync.c",0xcdc,local_260,pvVar8);
            }
            free(pvVar8);
          }
          FUN_10028a48(pvVar11);
          memset(pvVar11,0,0x2c);
        }
        else {
          if (*(char *)((int)pvVar11 + 0x10) == '\n') {
            iVar16 = 2;
          }
          else {
            iVar16 = 1;
          }
          if (DAT_11f1df3c < local_240 + iVar16) {
            local_25c = local_25c + 1;
            if (3 < DAT_11e46cd4) {
              pvVar8 = (void *)FUN_10029758(pvVar11);
              if (3 < DAT_11e46cd4) {
                uVar7 = bcm_l3_route_get();
                FUN_10047ec4(4,"%s %s:%d Out of host table entries for %s.  Skipping.\n",0x37,uVar7,
                             "sync.c",0xcac,pvVar8);
              }
              free(pvVar8);
            }
            FUN_10028a48(pvVar11);
            memset(pvVar11,0,0x2c);
          }
          else {
            local_240 = local_240 + iVar16;
            if (*(char *)((int)pvVar11 + 0x10) == '\n') {
              local_238 = local_238 + 1;
            }
            else {
              local_23c = local_23c + 1;
            }
LAB_10014b9c:
            if (DAT_11f1df44 < *(int *)((int)pvVar11 + 0x20)) {
              local_254 = local_254 + 1;
              if (3 < DAT_11e46cd4) {
                pvVar8 = (void *)FUN_10029758(pvVar11);
                if (3 < DAT_11e46cd4) {
                  uVar7 = bcm_l3_route_get();
                  FUN_10047ec4(4,"%s %s:%d Too many ECMP NHs for %s, truncating to %d.\n",0x36,uVar7
                               ,"sync.c",0xcf3,pvVar8,DAT_11f1df44);
                }
                free(pvVar8);
              }
              *(int *)((int)pvVar11 + 0x20) = DAT_11f1df44;
            }
            if (1 < *(int *)((int)pvVar11 + 0x20)) {
              iVar16 = *(int *)((int)pvVar11 + 0x20) * 0x24;
              cVar9 = FUN_10049268(uVar6,*(undefined4 *)((int)pvVar11 + 0x24),iVar16,0);
              if (cVar9 != '\x01') {
                if (DAT_11f1df44 + local_234 < DAT_11f1df40) {
                  local_234 = local_234 + DAT_11f1df44;
                  FUN_10049208(uVar6,*(undefined4 *)((int)pvVar11 + 0x24),iVar16,1);
                }
                else {
                  FUN_10028944(auStack_8c,1);
                  FUN_10028c04(auStack_8c,pvVar11);
                  FUN_10028a48(pvVar11);
                  memcpy(pvVar11,auStack_8c,0x2c);
                  local_250 = local_250 + 1;
                  if (3 < DAT_11e46cd4) {
                    pvVar11 = (void *)FUN_10029758(pvVar11);
                    if (3 < DAT_11e46cd4) {
                      uVar7 = bcm_l3_route_get();
                      FUN_10047ec4(4,"%s %s:%d Out of ECMP NHs.  Fallback to nh %s.\n",0x2f,uVar7,
                                   "sync.c",0xd22,pvVar11);
                    }
                    free(pvVar11);
                  }
                }
              }
            }
          }
        }
      }
    }
    FUN_10049538(uVar6,0);
    if (DAT_11e46f36 != '\0') {
      if ((3 < DAT_11e46cd4) && (3 < DAT_11e46cd4)) {
        uVar6 = bcm_l3_route_get();
        FUN_10047ec4(4,"%s %s:%d Cleaning up arp cache\n",0x20,uVar6,"sync.c",0xd30);
      }
      FUN_1002c1c0();
    }
    if (DAT_11e46fd4 != '\0') {
      FUN_1004783c(&local_188,"constrain_fib");
    }
    FUN_10049320(DAT_11e46f90,FUN_100162fc,0);
    local_b0 = 0;
    local_b4 = 0;
    local_ac = (void *)0x0;
    local_a4 = 0;
    local_a8 = 0;
    local_a0 = (void *)0x0;
    local_98 = 0;
    local_9c = 0;
    local_94 = (void *)0x0;
    for (local_228 = 0; local_228 < local_144; local_228 = local_228 + 1) {
      pvVar11 = (void *)((int)local_13c + local_228 * 0x2c);
      iVar16 = memcmp(pvVar11,auStack_60,0x2c);
      if (iVar16 != 0) {
        cVar9 = FUN_10049268(DAT_11e46f90,pvVar11,0x18,&local_90);
        if (cVar9 == '\x01') {
          if ((*(uint *)((int)pvVar11 + 0x1c) & 8) == 0) {
            *(uint *)(local_90 + 0x1c) = *(uint *)(local_90 + 0x1c) | 0x80000000;
            iVar16 = FUN_10028e44(pvVar11,local_90);
            if (iVar16 == 0) {
              if (3 < DAT_11e46cd4) {
                pvVar8 = (void *)FUN_10029758(local_90);
                __ptr = (void *)FUN_10029758(pvVar11);
                if (3 < DAT_11e46cd4) {
                  uVar6 = bcm_l3_route_get();
                  FUN_10047ec4(4,"%s %s:%d Updating route %s to %s\n",0x22,uVar6,"sync.c",0xd6c,
                               pvVar8,__ptr);
                }
                free(pvVar8);
                free(__ptr);
              }
              if (*(int *)((int)pvVar11 + 0x20) == 0) {
                if (local_9c == local_98) {
                  if (local_98 == 0) {
                    local_98 = 2;
                  }
                  else {
                    local_98 = local_98 << 1;
                  }
                  local_94 = realloc(local_94,local_98 << 2);
                }
                *(void **)((int)local_94 + local_9c * 4) = pvVar11;
                local_9c = local_9c + 1;
              }
              else if (*(int *)((int)pvVar11 + 0x20) == 1) {
                if (local_9c == local_98) {
                  if (local_98 == 0) {
                    local_98 = 2;
                  }
                  else {
                    local_98 = local_98 << 1;
                  }
                  local_94 = realloc(local_94,local_98 << 2);
                }
                *(void **)((int)local_94 + local_9c * 4) = pvVar11;
                local_9c = local_9c + 1;
              }
              else {
                if (local_a8 == local_a4) {
                  if (local_a4 == 0) {
                    local_a4 = 2;
                  }
                  else {
                    local_a4 = local_a4 << 1;
                  }
                  local_a0 = realloc(local_a0,local_a4 << 2);
                }
                *(void **)((int)local_a0 + local_a8 * 4) = pvVar11;
                local_a8 = local_a8 + 1;
              }
            }
            else {
              FUN_10028a48(pvVar11);
            }
          }
          else {
            FUN_10028a48(pvVar11);
          }
        }
        else {
          if (3 < DAT_11e46cd4) {
            pvVar8 = (void *)FUN_10029758(pvVar11);
            if (3 < DAT_11e46cd4) {
              uVar6 = bcm_l3_route_get();
              FUN_10047ec4(4,"%s %s:%d Adding route: %s\n",0x1b,uVar6,"sync.c",0xd52,pvVar8);
            }
            free(pvVar8);
          }
          if (local_b4 == local_b0) {
            if (local_b0 == 0) {
              local_b0 = 2;
            }
            else {
              local_b0 = local_b0 << 1;
            }
            local_ac = realloc(local_ac,local_b0 << 2);
          }
          *(void **)((int)local_ac + local_b4 * 4) = pvVar11;
          local_b4 = local_b4 + 1;
        }
      }
    }
    if (DAT_11e46fd4 != '\0') {
      FUN_1004783c(&local_188,"build_work_queues");
    }
    FUN_10049320(DAT_11e46f90,auStack_138,0);
    for (local_22c = 0; local_22c < local_9c; local_22c = local_22c + 1) {
      iVar16 = *(int *)((int)local_94 + local_22c * 4);
      if ((*(uint *)(iVar16 + 0x1c) & 8) == 0) {
        cVar9 = FUN_1002405c(iVar16);
        if (cVar9 != '\0') {
          if ((*(uint *)(iVar16 + 0x1c) & 0x10) == 0) {
            iVar12 = FUN_1000b638(iVar16);
            aiStack_170[iVar12] = aiStack_170[iVar12] + 1;
          }
          else {
            local_27c = local_27c + 1;
          }
        }
      }
      else if ((*(uint *)(iVar16 + 0x1c) & 0x10) == 0) {
        iVar12 = FUN_1000b638(iVar16);
        aiStack_170[iVar12 + 2] = aiStack_170[iVar12 + 2] + 1;
      }
      else {
        local_278 = local_278 + 1;
      }
      FUN_10028a48(iVar16);
    }
    free(local_94);
    for (local_22c = 0; local_22c < local_a8; local_22c = local_22c + 1) {
      iVar16 = *(int *)((int)local_a0 + local_22c * 4);
      if ((*(uint *)(iVar16 + 0x1c) & 8) == 0) {
        cVar9 = FUN_1002405c(iVar16);
        if (cVar9 != '\0') {
          if ((*(uint *)(iVar16 + 0x1c) & 0x10) == 0) {
            iVar12 = FUN_1000b638(iVar16);
            aiStack_170[iVar12] = aiStack_170[iVar12] + 1;
          }
          else {
            local_27c = local_27c + 1;
          }
        }
      }
      else if ((*(uint *)(iVar16 + 0x1c) & 0x10) == 0) {
        iVar12 = FUN_1000b638(iVar16);
        aiStack_170[iVar12 + 2] = aiStack_170[iVar12 + 2] + 1;
      }
      else {
        local_278 = local_278 + 1;
      }
      FUN_10028a48(iVar16);
    }
    free(local_a0);
    for (local_22c = 0; local_22c < local_b4; local_22c = local_22c + 1) {
      iVar16 = *(int *)((int)local_ac + local_22c * 4);
      if ((*(uint *)(iVar16 + 0x1c) & 8) == 0) {
        cVar9 = FUN_10023c98(iVar16);
        if (cVar9 != '\0') {
          if ((*(uint *)(iVar16 + 0x1c) & 0x10) == 0) {
            iVar12 = FUN_1000b638(iVar16);
            aiStack_180[iVar12] = aiStack_180[iVar12] + 1;
          }
          else {
            local_280 = local_280 + 1;
          }
        }
      }
      else if ((*(uint *)(iVar16 + 0x1c) & 0x10) == 0) {
        iVar12 = FUN_1000b638(iVar16);
        aiStack_170[iVar12 + 2] = aiStack_170[iVar12 + 2] + 1;
      }
      else {
        local_278 = local_278 + 1;
      }
      FUN_10028a48(iVar16);
    }
    free(local_ac);
    free(local_13c);
    rtnl_route_put(uVar5);
    if (DAT_11e46fd4 != '\0') {
      FUN_1004783c(&local_188,"update_hw");
    }
  }
  if ((((local_280 != 0) || (local_148 != 0)) || (local_27c != 0)) &&
     (bVar3 = true, 2 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    uVar17 = FUN_1000b0b4();
    local_28._4_4_ = (uint)uVar17 - uVar10;
    local_28._0_4_ = (int)((ulonglong)uVar17 >> 0x20) - (iVar4 + (uint)((uint)uVar17 < uVar10));
    FUN_10047ec4(3,
                 "%s %s:%d Neighbor Summary : %d Added, %d Deleted, %d Updated, %d Skipped in %llu usecs\n"
                 ,0x58,uVar5,"sync.c",0xde5,local_280,local_148,local_27c,local_278,
                 CONCAT44(local_28._0_4_,local_28._4_4_));
  }
  if (((local_278 != 0) && (bVar3 = true, 3 < DAT_11e46cd4)) && (3 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    uVar17 = FUN_1000b0b4();
    local_28._4_4_ = (uint)uVar17 - uVar10;
    local_28._0_4_ = (int)((ulonglong)uVar17 >> 0x20) - (iVar4 + (uint)((uint)uVar17 < uVar10));
    FUN_10047ec4(4,"%s %s:%d Neighbor Summary : %d Skipped in %llu usecs\n",0x36,uVar5,"sync.c",
                 0xdec,local_278,uVar10,CONCAT44(local_28._0_4_,local_28._4_4_));
  }
  if (((local_25c != 0) && (DAT_11e47528 != local_25c)) && (0 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(1,"%s %s:%d ERR %d hosts were ignored due to capacity.\n",0x35,uVar5,"sync.c",0xdf1
                 ,local_25c);
  }
  if (((local_258 != 0) && (DAT_11e4752c != local_258)) && (0 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(1,"%s %s:%d ERR %d routes were ignored due to total capacity.\n",0x3c,uVar5,
                 "sync.c",0xdf5,local_258);
  }
  if (DAT_11f1df60 != local_240) {
    DAT_11f1df60 = local_240;
  }
  if (DAT_11f1df64 != local_23c) {
    DAT_11f1df64 = local_23c;
  }
  if (DAT_11f1df68 != local_238) {
    DAT_11f1df68 = local_238;
  }
  if (DAT_11f1df54 != local_24c) {
    DAT_11f1df54 = local_24c;
  }
  if (DAT_11f1df58 != local_248) {
    DAT_11f1df58 = local_248;
  }
  if (DAT_11f1df5c != local_244) {
    DAT_11f1df5c = local_244;
  }
  for (local_220 = 0; local_220 < 2; local_220 = local_220 + 1) {
    if ((&DAT_11f1df2c)[local_220 + 8] != aiStack_170[local_220 + 6]) {
      (&DAT_11f1df2c)[local_220 + 8] = aiStack_170[local_220 + 6];
    }
    if ((((aiStack_180[local_220] != 0) || (aiStack_170[local_220 + 8] != 0)) ||
        (aiStack_170[local_220] != 0)) && (bVar2 = true, 2 < DAT_11e46cd4)) {
      uVar5 = bcm_l3_route_get();
      iVar16 = DAT_11e47530;
      uVar6 = (&DAT_11e46fa8)[local_220];
      iVar12 = aiStack_180[local_220];
      iVar13 = aiStack_170[local_220 + 8];
      iVar14 = aiStack_170[local_220];
      iVar15 = aiStack_170[local_220 + 2];
      uVar17 = FUN_1000b0b4();
      local_28._4_4_ = (uint)uVar17 - uVar10;
      local_28._0_4_ = (int)((ulonglong)uVar17 >> 0x20) - (iVar4 + (uint)((uint)uVar17 < uVar10));
      FUN_10047ec4(3,
                   "%s %s:%d %s Route Summary (%d) : %d Added, %d Deleted, %d Updated, %d Skipped in %llu usecs\n"
                   ,0x5d,uVar5,"sync.c",0xe1c,uVar6,iVar16,iVar12,iVar13,iVar14,iVar15,
                   CONCAT44(local_28._0_4_,local_28._4_4_));
    }
    if (((aiStack_170[local_220 + 2] != 0) && (bVar2 = true, 3 < DAT_11e46cd4)) &&
       (3 < DAT_11e46cd4)) {
      uVar5 = bcm_l3_route_get();
      iVar16 = aiStack_170[local_220 + 2];
      uVar17 = FUN_1000b0b4();
      local_28._4_4_ = (uint)uVar17 - uVar10;
      local_28._0_4_ = (int)((ulonglong)uVar17 >> 0x20) - (iVar4 + (uint)((uint)uVar17 < uVar10));
      FUN_10047ec4(4,"%s %s:%d Route Summary : %d Skipped in %llu usecs\n",0x33,uVar5,"sync.c",0xe22
                   ,iVar16,uVar10,CONCAT44(local_28._0_4_,local_28._4_4_));
    }
    if (((aiStack_170[local_220 + 4] != 0) &&
        (*(int *)(&DAT_11e47520 + local_220 * 4) != aiStack_170[local_220 + 4])) &&
       (0 < DAT_11e46cd4)) {
      uVar5 = bcm_l3_route_get();
      FUN_10047ec4(1,"%s %s:%d ERR %d %s routes were ignored due to capacity.\n",0x39,uVar5,"sync.c"
                   ,0xe28,aiStack_170[local_220 + 4],(&DAT_11e46fa8)[local_220]);
    }
  }
  if (DAT_11f1df6c != local_234) {
    DAT_11f1df6c = local_234;
  }
  if (((local_254 != 0) && (DAT_11e47534 != local_254)) && (1 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(2,"%s %s:%d WARN %d routes exceeded %d ecmp NHs, and were truncated.\n",0x43,uVar5,
                 "sync.c",0xe32,local_254,DAT_11f1df44);
  }
  if (((local_250 != 0) && (DAT_11e47538 != local_250)) && (1 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(2,"%s %s:%d WARN %d routes reverted to non-ECMP due to NH table capacity.\n",0x48,
                 uVar5,"sync.c",0xe37,local_250);
  }
  if ((bVar2) || (bVar3)) {
    FUN_1003a34c(1);
    FUN_100115dc();
    FUN_10011258(0);
  }
  if (((DAT_11e47528 != 0) && (local_25c == 0)) && (2 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(3,"%s %s:%d # of hosts have reduced enough to fit.\n",0x31,uVar5,"sync.c",0xe4b);
  }
  if (((DAT_11e4752c != 0) && (local_258 == 0)) && (2 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(3,"%s %s:%d # of routes have reduced enough to fit.\n",0x32,uVar5,"sync.c",0xe4e);
  }
  for (local_21c = 0; local_21c < 2; local_21c = local_21c + 1) {
    if (((*(int *)(&DAT_11e47520 + local_21c * 4) != 0) && (aiStack_170[local_21c + 4] == 0)) &&
       (2 < DAT_11e46cd4)) {
      uVar5 = bcm_l3_route_get();
      FUN_10047ec4(3,"%s %s:%d # of routes in table %d have reduced enough to fit.\n",0x3e,uVar5,
                   "sync.c",0xe52,local_21c);
    }
  }
  if (((DAT_11e47534 != 0) && (local_254 == 0)) && (2 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(3,"%s %s:%d # of NHs per route have reduced enough to all fit.\n",0x3d,uVar5,
                 "sync.c",0xe56);
  }
  if (((DAT_11e47538 != 0) && (local_250 == 0)) && (2 < DAT_11e46cd4)) {
    uVar5 = bcm_l3_route_get();
    FUN_10047ec4(3,"%s %s:%d # of NHs have reduced enough to fit.\n",0x2f,uVar5,"sync.c",0xe59);
  }
  DAT_11e47528 = local_25c;
  for (local_218 = 0; local_218 < 2; local_218 = local_218 + 1) {
    *(int *)(&DAT_11e47520 + local_218 * 4) = aiStack_170[local_218 + 4];
  }
  DAT_11e47534 = local_254;
  DAT_11e47538 = local_250;
  DAT_11e47530 = DAT_11e47530 + 1;
  return 1;
}



/* === FUN_10013328 @ 0x10013328 (size=3280) === */

undefined4 FUN_10013328(undefined4 param_1,void *param_2,char param_3)

{
  bool bVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined4 uVar4;
  char cVar10;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  void *pvVar8;
  undefined1 uVar11;
  int iVar9;
  undefined4 *puVar12;
  int local_154;
  int local_150;
  undefined1 auStack_128 [256];
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  void *local_14;
  char local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  uVar4 = rtnl_route_get_dst(param_1);
  cVar10 = rtnl_route_get_type(local_18);
  uVar5 = rtnl_route_get_flags(local_18);
  local_28 = 0;
  iVar6 = rtnl_route_get_table(local_18);
  if ((iVar6 != DAT_11e46f14) && (iVar6 = rtnl_route_get_table(local_18), iVar6 != 0xff)) {
    FUN_11312544("rtnl_route_get_table(route) == route_table_num || rtnl_route_get_table(route) == RT_TABLE_LOCAL"
                 ,"sync.c",0xaba);
  }
  if ((uVar5 & 0x200) == 0) {
    iVar6 = rtnl_route_get_family(local_18);
    if ((iVar6 == 2) || (iVar6 = rtnl_route_get_family(local_18), iVar6 == 10)) {
      if ((uVar5 == 0) || (((uVar5 & 4) != 0 || ((uVar5 & 1) != 0)))) {
        if ((cVar10 == '\x01') ||
           (((cVar10 == '\x06' || (cVar10 == '\a')) ||
            ((iVar6 = rtnl_route_get_table(local_18), iVar6 == 0xff &&
             ((cVar10 == '\x02' || (cVar10 == '\x03')))))))) {
          iVar6 = rtnl_route_get_tos(local_18);
          if (iVar6 == 0) {
            iVar6 = rtnl_route_get_src(local_18);
            if (iVar6 == 0) {
              iVar6 = rtnl_route_get_iif(local_18);
              if (iVar6 == 0) {
                if (cVar10 == '\a') {
                  local_150 = 1;
                }
                else {
                  rtnl_route_foreach_nexthop(local_18,FUN_10013ff8,&local_28);
                  local_150 = DAT_11f1df44;
                  if (local_28 < DAT_11f1df44) {
                    local_150 = local_28;
                  }
                }
                FUN_10028944(local_14,local_150);
                iVar6 = rtnl_route_get_family(local_18);
                bVar1 = iVar6 != 10;
                if (bVar1) {
                  *(undefined1 *)((int)local_14 + 0x10) = 2;
                }
                else {
                  *(undefined1 *)((int)local_14 + 0x10) = 10;
                }
                iVar6 = nl_addr_get_len(uVar4);
                if (iVar6 == 0) {
                  memset(local_14,0,0x10);
                }
                else {
                  if (bVar1) {
                    iVar6 = nl_addr_get_len(uVar4);
                    if (iVar6 != 4) {
                      FUN_11312544("nl_addr_get_len(dst) == 4","sync.c",0xb18);
                    }
                    pvVar3 = local_14;
                    pvVar8 = (void *)nl_addr_get_binary_addr(uVar4);
                    memcpy(pvVar3,pvVar8,4);
                  }
                  else {
                    iVar6 = nl_addr_get_len(uVar4);
                    if (iVar6 != 0x10) {
                      FUN_11312544("nl_addr_get_len(dst) == 16","sync.c",0xb14);
                    }
                    pvVar3 = local_14;
                    pvVar8 = (void *)nl_addr_get_binary_addr(uVar4);
                    memcpy(pvVar3,pvVar8,0x10);
                  }
                  iVar6 = FUN_1002a298(local_14);
                  if (iVar6 != 0) {
                    memset(auStack_128,0,0x100);
                    if ((3 < DAT_11e46cd4) &&
                       (nl_object_dump_buf(local_18,auStack_128,0xff), 3 < DAT_11e46cd4)) {
                      uVar4 = bcm_l3_route_get();
                      FUN_10047ec4(4,"%s %s:%d Route [%s] is loopback - ignore\n",0x2a,uVar4,
                                   "sync.c",0xb23,auStack_128);
                    }
                    FUN_10028a48(local_14);
                    return 0;
                  }
                }
                uVar11 = nl_addr_get_prefixlen(uVar4);
                *(undefined1 *)((int)local_14 + 0x11) = uVar11;
                uVar4 = rtnl_route_get_priority(local_18);
                *(undefined4 *)((int)local_14 + 0x18) = uVar4;
                if ((local_10 == '\0') && (cVar10 != '\a')) {
                  local_24[0] = 0;
                  iVar6 = rtnl_route_get_nnexthops(local_18);
                  if ((uVar5 & 4) != 0) {
                    *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x20;
                  }
                  if (*(int *)((int)local_14 + 0x20) == 0) {
                    if (cVar10 != '\x06') {
                      FUN_11312544("route_type == RTN_BLACKHOLE","sync.c",0xb5b);
                    }
                  }
                  else {
                    *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 8;
                    local_154 = 0;
                    while ((local_154 < iVar6 && (local_24[0] < *(int *)((int)local_14 + 0x20)))) {
                      uVar4 = rtnl_route_nexthop_n(local_18,local_154);
                      iVar9 = *(int *)((int)local_14 + 0x24) + local_24[0] * 0x24;
                      cVar10 = FUN_10012a40(uVar4,iVar9,*(char *)((int)local_14 + 0x10) == '\n');
                      if (cVar10 != '\x01') {
                        FUN_10028a48(local_14);
                        return 0;
                      }
                      if ((*(uint *)(iVar9 + 0x20) & 1) == 0) {
                        *(uint *)((int)local_14 + 0x1c) =
                             *(uint *)((int)local_14 + 0x1c) & 0xfffffff7;
                      }
                      uVar5 = rtnl_route_nh_get_flags(uVar4);
                      if ((uVar5 & 4) != 0) {
                        *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x20;
                      }
                      iVar9 = memcmp((void *)(*(int *)((int)local_14 + 0x24) + local_24[0] * 0x24),
                                     &DAT_1181aa54,0x14);
                      if (iVar9 == 0) {
                        *(int *)((int)local_14 + 0x20) = *(int *)((int)local_14 + 0x20) + -1;
                      }
                      else {
                        local_24[0] = local_24[0] + 1;
                        if (iVar6 < local_28) {
                          FUN_1001405c(uVar4,local_14,local_28,local_150,local_24);
                        }
                      }
                      local_154 = local_154 + 1;
                    }
                    if ((local_154 < iVar6) && (3 < DAT_11e46cd4)) {
                      memset(auStack_128,0,0x100);
                      nl_object_dump_buf(local_18,auStack_128,0xff);
                      if (3 < DAT_11e46cd4) {
                        uVar4 = bcm_l3_route_get();
                        FUN_10047ec4(4,"%s %s:%d Route [%s] next-hops are truncated.\n",0x2e,uVar4,
                                     "sync.c",0xb8f,auStack_128);
                      }
                    }
                    if (*(int *)((int)local_14 + 0x20) == 0) {
                      *(undefined4 *)((int)local_14 + 0x20) = 1;
                      uVar2 = DAT_1181aa60;
                      uVar7 = DAT_1181aa5c;
                      uVar4 = DAT_1181aa58;
                      puVar12 = *(undefined4 **)((int)local_14 + 0x24);
                      *puVar12 = DAT_1181aa54;
                      puVar12[1] = uVar4;
                      puVar12[2] = uVar7;
                      puVar12[3] = uVar2;
                      puVar12[4] = DAT_1181aa64;
                      memset((void *)(*(int *)((int)local_14 + 0x24) + 0x18),0,6);
                    }
                    if (1 < *(int *)((int)local_14 + 0x20)) {
                      qsort(*(void **)((int)local_14 + 0x24),*(size_t *)((int)local_14 + 0x20),0x24,
                            FUN_10029190);
                    }
                  }
                }
                else {
                  iVar6 = rtnl_route_nexthop_n(local_18,0);
                  if ((uVar5 & 4) != 0) {
                    FUN_11312544("(route_flags & RTNH_F_ONLINK) == 0","sync.c",0xb31);
                  }
                  if ((iVar6 != 0) && (cVar10 != '\a')) {
                    uVar4 = rtnl_route_nh_get_ifindex(iVar6);
                    iVar9 = FUN_1000bd9c(uVar4);
                    if (iVar9 == 0) {
                      *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) & 0xfffffff7
                      ;
                    }
                    else {
                      *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 8;
                    }
                    if (DAT_11e46f35 != '\0') {
                      uVar4 = rtnl_route_nh_get_ifindex(iVar6);
                      iVar9 = FUN_1000c494(uVar4);
                      if (iVar9 != 0) {
                        FUN_10028a48(local_14);
                        return 0;
                      }
                    }
                  }
                  if (cVar10 != '\a') {
                    if (*(int *)((int)local_14 + 0x20) != 1) {
                      FUN_11312544("hal_route->num_next_hops == 1","sync.c",0xb47);
                    }
                    if ((bVar1) && (iVar6 = rtnl_route_nh_get_gateway(iVar6), iVar6 != 0)) {
                      FUN_11312544("ipv6 || !rtnl_route_nh_get_gateway(nh)","sync.c",0xb48);
                    }
                  }
                  if (local_10 != '\0') {
                    *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x40;
                  }
                  uVar2 = DAT_1181aa60;
                  uVar7 = DAT_1181aa5c;
                  uVar4 = DAT_1181aa58;
                  puVar12 = *(undefined4 **)((int)local_14 + 0x24);
                  *puVar12 = DAT_1181aa54;
                  puVar12[1] = uVar4;
                  puVar12[2] = uVar7;
                  puVar12[3] = uVar2;
                  puVar12[4] = DAT_1181aa64;
                  memset((void *)(*(int *)((int)local_14 + 0x24) + 0x18),0,6);
                }
                uVar4 = 1;
              }
              else {
                memset(auStack_128,0,0x100);
                nl_object_dump_buf(local_18,auStack_128,0xff);
                if (1 < DAT_11e46cd4) {
                  uVar4 = bcm_l3_route_get();
                  uVar7 = rtnl_route_get_iif(local_18);
                  FUN_10047ec4(2,"%s %s:%d WARN Route [%s] has non-zero iif: %d\n",0x2f,uVar4,
                               "sync.c",0xafe,auStack_128,uVar7);
                }
                uVar4 = 0;
              }
            }
            else {
              memset(auStack_128,0,0x100);
              nl_object_dump_buf(local_18,auStack_128,0xff);
              if (1 < DAT_11e46cd4) {
                uVar4 = bcm_l3_route_get();
                FUN_10047ec4(2,"%s %s:%d WARN Route [%s] has non-NULL src.\n",0x2c,uVar4,"sync.c",
                             0xaf7,auStack_128);
              }
              uVar4 = 0;
            }
          }
          else {
            memset(auStack_128,0,0x100);
            nl_object_dump_buf(local_18,auStack_128,0xff);
            if (1 < DAT_11e46cd4) {
              uVar4 = bcm_l3_route_get();
              uVar7 = rtnl_route_get_tos(local_18);
              FUN_10047ec4(2,"%s %s:%d WARN Route [%s] has unexpected tos: %d\n",0x31,uVar4,"sync.c"
                           ,0xaf1,auStack_128,uVar7);
            }
            uVar4 = 0;
          }
        }
        else {
          memset(auStack_128,0,0x100);
          nl_object_dump_buf(local_18,auStack_128,0xff);
          if (1 < DAT_11e46cd4) {
            uVar4 = bcm_l3_route_get();
            FUN_10047ec4(2,"%s %s:%d WARN Route [%s] has unexpected type: %d\n",0x32,uVar4,"sync.c",
                         0xaea,auStack_128,cVar10);
          }
          uVar4 = 0;
        }
      }
      else {
        memset(auStack_128,0,0x100);
        nl_object_dump_buf(local_18,auStack_128,0xff);
        if (1 < DAT_11e46cd4) {
          uVar4 = bcm_l3_route_get();
          uVar7 = rtnl_route_get_flags(local_18);
          FUN_10047ec4(2,"%s %s:%d WARN Route [%s] has unexpected flags: %d\n",0x33,uVar4,"sync.c",
                       0xadf,auStack_128,uVar7);
        }
        uVar4 = 0;
      }
    }
    else {
      memset(auStack_128,0,0x100);
      nl_object_dump_buf(local_18,auStack_128,0xff);
      if (1 < DAT_11e46cd4) {
        uVar4 = bcm_l3_route_get();
        uVar7 = rtnl_route_get_family(local_18);
        FUN_10047ec4(2,"%s %s:%d WARN Route [%s] is not IPv4 or v6, family: %d\n",0x38,uVar4,
                     "sync.c",0xad6,auStack_128,uVar7);
      }
      uVar4 = 0;
    }
  }
  else {
    if (3 < DAT_11e46cd4) {
      memset(auStack_128,0,0x100);
      nl_object_dump_buf(local_18,auStack_128,0xff);
      if (3 < DAT_11e46cd4) {
        uVar4 = bcm_l3_route_get();
        FUN_10047ec4(4,"%s %s:%d Route [%s] is from kernel cache\n",0x2a,uVar4,"sync.c",0xacd,
                     auStack_128);
      }
    }
    uVar4 = 0;
  }
  return uVar4;
}



/* === FUN_100122d4 @ 0x100122d4 (size=1900) === */

undefined4 FUN_100122d4(undefined4 param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  void *pvVar7;
  int iVar8;
  void *pvVar9;
  size_t __n;
  undefined4 *puVar10;
  bool bVar11;
  bool bVar12;
  int local_e8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  int local_b0;
  undefined1 auStack_ac [8];
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_18;
  void *local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  uVar1 = rtnl_neigh_get_dst(param_1);
  iVar2 = rtnl_neigh_get_lladdr(local_18);
  uVar3 = rtnl_neigh_get_ifindex(local_18);
  uVar4 = rtnl_neigh_get_state(local_18);
  uVar5 = FUN_1000abf0();
  local_e8 = 1;
  if ((DAT_11e46f35 == '\0') || (iVar6 = FUN_1000c494(uVar3), iVar6 == 0)) {
    FUN_1000c320(uVar3,&local_c4);
    iVar6 = rtnl_neigh_get_type(local_18);
    if (iVar6 == 1) {
      iVar6 = rtnl_neigh_get_family(local_18);
      if (iVar6 == 7) {
        uVar1 = 0;
      }
      else {
        iVar6 = rtnl_neigh_get_family(local_18);
        if ((iVar6 == 2) || (iVar6 = rtnl_neigh_get_family(local_18), iVar6 == 10)) {
          iVar6 = rtnl_neigh_get_flags(local_18);
          if ((iVar6 == 0) || (iVar6 = rtnl_neigh_get_flags(local_18), iVar6 == 0x80)) {
            if (((uVar4 & 0x20) == 0) || (DAT_11e46f30 == '\x01')) {
              if ((uVar4 & 0xde) == 0) {
                local_e8 = 0;
              }
            }
            else {
              local_c4 = DAT_1181aa54;
              local_c0 = DAT_1181aa58;
              local_bc = DAT_1181aa5c;
              local_b8 = DAT_1181aa60;
              local_b4 = DAT_1181aa64;
            }
            FUN_10028944(local_14,local_e8);
            *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x10;
            *(undefined4 *)((int)local_14 + 0x14) = 1;
            puVar10 = *(undefined4 **)((int)local_14 + 0x24);
            iVar6 = rtnl_neigh_get_family(local_18);
            pvVar9 = local_14;
            if (iVar6 == 10) {
              *(undefined1 *)((int)local_14 + 0x10) = 10;
              pvVar7 = (void *)nl_addr_get_binary_addr(uVar1);
              memcpy(pvVar9,pvVar7,0x10);
              *(undefined1 *)((int)local_14 + 0x11) = 0x80;
            }
            else {
              *(undefined1 *)((int)local_14 + 0x10) = 2;
              pvVar7 = (void *)nl_addr_get_binary_addr(uVar1);
              memcpy(pvVar9,pvVar7,4);
              *(undefined1 *)((int)local_14 + 0x11) = 0x20;
            }
            if (local_e8 != 0) {
              iVar6 = FUN_1000b894(uVar5,0,uVar3);
              if ((iVar6 == 0) || (iVar8 = FUN_1000b920(iVar6), iVar8 == 0)) {
                bVar11 = false;
              }
              else {
                bVar11 = true;
              }
              if ((iVar6 == 0) || (iVar8 = FUN_1000ba38(iVar6,&local_b0), iVar8 == 0)) {
                bVar12 = false;
              }
              else {
                bVar12 = true;
              }
              iVar8 = FUN_1000bd9c(uVar3);
              if (iVar8 == 0) {
                *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) & 0xfffffff7;
              }
              else {
                *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 8;
              }
              if (((iVar6 != 0) &&
                  (((iVar8 = FUN_1000b468(iVar6), iVar8 != 0 || (bVar11)) || (bVar12)))) &&
                 (iVar2 != 0)) {
                memset(auStack_ac,0,0x8c);
                pvVar9 = (void *)nl_addr_get_binary_addr(iVar2);
                __n = nl_addr_get_len(iVar2);
                memcpy(auStack_ac,pvVar9,__n);
                local_a4 = uVar3;
                if (bVar11) {
                  local_a0 = rtnl_link_vlan_get_id(iVar6);
                  puVar10[5] = local_a0;
                  local_a4 = rtnl_link_get_link(iVar6);
                }
                if (bVar12) {
                  iVar8 = FUN_1000b920(local_b0);
                  if (iVar8 == 0) {
                    iVar8 = FUN_1000b468(local_b0);
                    if (iVar8 != 0) {
                      local_a4 = rtnl_link_get_ifindex(local_b0);
                    }
                  }
                  else {
                    local_a4 = rtnl_link_get_link(local_b0);
                    local_a0 = rtnl_link_vlan_get_id(local_b0);
                  }
                  puVar10[5] = local_a0;
                }
                iVar8 = FUN_10025184(auStack_ac);
                if (iVar8 == 0) {
                  local_c4 = DAT_1181aa54;
                  local_c0 = DAT_1181aa58;
                  local_bc = DAT_1181aa5c;
                  local_b8 = DAT_1181aa60;
                  local_b4 = DAT_1181aa64;
                }
                else {
                  local_c4 = local_9c;
                  local_c0 = local_98;
                  local_bc = local_94;
                  local_b8 = local_90;
                  local_b4 = local_8c;
                }
              }
              if (iVar6 != 0) {
                rtnl_link_put(iVar6);
              }
              if (local_b0 != 0) {
                rtnl_link_put(local_b0);
              }
              *puVar10 = local_c4;
              puVar10[1] = local_c0;
              puVar10[2] = local_bc;
              puVar10[3] = local_b8;
              puVar10[4] = local_b4;
            }
            if (local_e8 != 0) {
              iVar6 = memcmp(&local_c4,&DAT_1181aa54,0x14);
              if (iVar6 == 0) {
                memset(puVar10 + 6,0,6);
                *puVar10 = local_c4;
                puVar10[1] = local_c0;
                puVar10[2] = local_bc;
                puVar10[3] = local_b8;
                puVar10[4] = local_b4;
              }
              else {
                iVar6 = nl_addr_get_len(iVar2);
                if (iVar6 != 6) {
                  FUN_11312544("nl_addr_get_len(mac_addr) == 6","sync.c",0x9de);
                }
                pvVar9 = (void *)nl_addr_get_binary_addr(iVar2);
                memcpy(puVar10 + 6,pvVar9,6);
                *puVar10 = local_c4;
                puVar10[1] = local_c0;
                puVar10[2] = local_bc;
                puVar10[3] = local_b8;
                puVar10[4] = local_b4;
                iVar2 = FUN_1000bd9c(uVar3);
                if (iVar2 == 0) {
                  *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) & 0xfffffff7;
                }
                else {
                  *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 8;
                }
              }
            }
            uVar1 = 1;
          }
          else {
            if (1 < DAT_11e46cd4) {
              uVar1 = bcm_l3_route_get();
              uVar3 = rtnl_neigh_get_flags(local_18);
              FUN_10047ec4(2,"%s %s:%d WARN Neighbor entry had unexpected flags %d\n",0x36,uVar1,
                           "sync.c",0x983,uVar3);
            }
            uVar1 = 0;
          }
        }
        else {
          if (1 < DAT_11e46cd4) {
            uVar1 = bcm_l3_route_get();
            uVar3 = rtnl_neigh_get_family(local_18);
            FUN_10047ec4(2,"%s %s:%d WARN Neighbor entry is not IPv4 or v6: %d!\n",0x35,uVar1,
                         "sync.c",0x97c,uVar3);
          }
          uVar1 = 0;
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_1001acd4 @ 0x1001acd4 (size=916) === */

undefined4 FUN_1001acd4(undefined4 param_1,void *param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  void *pvVar9;
  size_t sVar10;
  int iVar11;
  uint uVar12;
  
  iVar3 = rtnl_neigh_get_lladdr(param_1);
  iVar4 = rtnl_neigh_get_ifindex(param_1);
  uVar5 = rtnl_neigh_get_state(param_1);
  iVar6 = rtnl_neigh_get_vlan(param_1);
  uVar7 = FUN_1000abf0();
  iVar8 = rtnl_neigh_get_dst(param_1);
  bVar1 = false;
  bVar2 = false;
  if ((iVar3 == 0) || (iVar4 == 0)) {
    uVar7 = 0;
  }
  else {
    memset(param_2,0,0x8c);
    pvVar9 = (void *)nl_addr_get_binary_addr(iVar3);
    sVar10 = nl_addr_get_len(iVar3);
    memcpy(param_2,pvVar9,sVar10);
    if (iVar6 == -1) {
      *(undefined4 *)((int)param_2 + 0xc) = 0;
    }
    else {
      *(int *)((int)param_2 + 0xc) = iVar6;
    }
    iVar3 = FUN_1000b894(uVar7,0,iVar4);
    iVar6 = FUN_1000b894(uVar7,7,iVar4);
    if (iVar6 == 0) {
      if ((iVar3 != 0) && (iVar6 = FUN_1000b468(iVar3), iVar6 != 0)) {
        *(int *)((int)param_2 + 8) = iVar4;
        bVar2 = true;
      }
    }
    else {
      uVar7 = rtnl_link_get_master(iVar6);
      *(undefined4 *)((int)param_2 + 8) = uVar7;
      iVar11 = FUN_1000b550(iVar3);
      bVar1 = iVar11 != 0;
      rtnl_link_put(iVar6);
    }
    if (iVar3 != 0) {
      rtnl_link_put(iVar3);
    }
    FUN_1000c320(iVar4,(int)param_2 + 0x10);
    iVar3 = memcmp((void *)((int)param_2 + 0x10),&DAT_1181aa54,0x14);
    if (iVar3 == 0) {
      if ((!bVar1) && (!bVar2)) {
        return 0;
      }
      if (bVar1) {
        *(uint *)((int)param_2 + 0x7c) = *(uint *)((int)param_2 + 0x7c) | 2;
      }
    }
    if (*(int *)((int)param_2 + 0x10) == 3) {
      uVar12 = rtnl_neigh_get_flags(param_1);
      if ((uVar12 & 2) == 0) {
        return 0;
      }
      if (iVar8 != 0) {
        pvVar9 = (void *)nl_addr_get_binary_addr(iVar8);
        sVar10 = nl_addr_get_len(iVar8);
        memcpy((void *)((int)param_2 + 0x20),pvVar9,sVar10);
      }
    }
    if ((uVar5 & 0xc0) == 0) {
      *(undefined4 *)((int)param_2 + 0x78) = 2;
    }
    else if (iVar8 == 0) {
      if ((bVar1) || (bVar2)) {
        *(undefined4 *)((int)param_2 + 0x78) = 1;
      }
      else if ((uVar5 & 0x80) == 0) {
        if ((uVar5 & 0x40) != 0) {
          *(undefined4 *)((int)param_2 + 0x78) = 1;
        }
      }
      else {
        *(undefined4 *)((int)param_2 + 0x78) = 0;
      }
    }
    else {
      *(undefined4 *)((int)param_2 + 0x78) = 1;
    }
    uVar7 = 1;
  }
  return uVar7;
}



/* === FUN_1000d9d0 @ 0x1000d9d0 (size=760) === */

void FUN_1000d9d0(undefined4 param_1,undefined4 param_2)

{
  char cVar5;
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  void *__ptr;
  uint uVar4;
  int *in_r11;
  void *local_68;
  undefined1 auStack_50 [44];
  int local_24 [3];
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  cVar5 = FUN_100122d4(param_1,auStack_50);
  if (cVar5 == '\x01') {
    cVar5 = FUN_10049268(DAT_11e46f90,auStack_50,0x18,local_24);
    if (cVar5 == '\x01') {
      if (((*(uint *)(local_24[0] + 0x1c) & 4) != 0) && (in_r11[2] < in_r11[1])) {
        uVar1 = nl_object_clone(local_18);
        *(uint *)(local_24[0] + 0x1c) = *(uint *)(local_24[0] + 0x1c) & 0xfffffffb;
        uVar4 = rtnl_neigh_get_state(uVar1);
        if ((uVar4 & 0x80) != 0) {
          *in_r11 = *in_r11 + 1;
          rtnl_neigh_put(uVar1);
          return;
        }
        in_r11[2] = in_r11[2] + 1;
        rtnl_neigh_unset_state(uVar1,0xffffffff);
        rtnl_neigh_set_state(uVar1,2);
        uVar3 = FUN_1000abc8();
        rtnl_neigh_add(uVar3,uVar1,0x500);
        rtnl_neigh_put(uVar1);
      }
      FUN_10028a48(auStack_50);
    }
    else {
      if (3 < DAT_11e46cd4) {
        __ptr = (void *)FUN_10029758(auStack_50);
        if (3 < DAT_11e46cd4) {
          uVar1 = bcm_l3_route_get();
          FUN_10047ec4(4,"%s %s:%d no hal route %s found in hal_routes\n",0x2e,uVar1,"sync.c",0x408,
                       __ptr);
        }
        free(__ptr);
      }
      FUN_10028a48(auStack_50);
    }
  }
  else if (((3 < DAT_11e46cd4) &&
           ((uVar1 = rtnl_neigh_get_ifindex(param_1), DAT_11e46f35 == '\0' ||
            (iVar2 = FUN_1000c494(uVar1), iVar2 == 0)))) &&
          ((iVar2 = rtnl_neigh_get_family(param_1), iVar2 == 10 ||
           (iVar2 = rtnl_neigh_get_family(param_1), iVar2 == 2)))) {
    uVar3 = rtnl_neigh_get_dst(param_1);
    iVar2 = rtnl_neigh_get_family(param_1);
    if (iVar2 == 10) {
      uVar3 = nl_addr_get_binary_addr(uVar3);
      local_68 = (void *)FUN_100293e8(uVar3);
    }
    else {
      uVar3 = nl_addr_get_binary_addr(uVar3);
      local_68 = (void *)FUN_100295cc(uVar3);
    }
    if (3 < DAT_11e46cd4) {
      uVar3 = bcm_l3_route_get();
      FUN_10047ec4(4,"%s %s:%d no hal route found for the neighbor entry %s, dev %d\n",0x3f,uVar3,
                   "sync.c",0x3fc,local_68,uVar1);
    }
    free(local_68);
  }
  return;
}



/* === FUN_1000b7e8 @ 0x1000b7e8 (size=172) === */

int FUN_1000b7e8(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = rtnl_neigh_alloc();
  if (iVar1 == 0) {
    if (-1 < DAT_11e46cd4) {
      uVar2 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT %s: rtnl_neigh_alloc failed for family %d\n",0x39,uVar2,"sync.c"
                   ,0xf4,"build_nl_neigh_family_filter",param_1);
    }
    iVar1 = 0;
  }
  else {
    rtnl_neigh_set_family(iVar1,param_1);
  }
  return iVar1;
}



/* === FUN_10012174 @ 0x10012174 (size=352) === */

undefined4 FUN_10012174(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_68;
  undefined1 auStack_58 [64];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_68 = 0;
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  uVar1 = rtnl_neigh_alloc();
  uVar2 = nl_addr_clone(local_10);
  if (local_18 == 0) {
    FUN_11312544("neigh_cache","sync.c",0x94a);
  }
  rtnl_neigh_set_family(uVar1,2);
  rtnl_neigh_set_type(uVar1,1);
  rtnl_neigh_set_ifindex(uVar1,local_14);
  iVar3 = rtnl_neigh_set_dst(uVar1,uVar2);
  if (iVar3 == 0) {
    local_68 = nl_cache_search(local_18,uVar1);
    nl_addr_put(uVar2);
  }
  else if (3 < DAT_11e46cd4) {
    uVar4 = bcm_l3_route_get();
    uVar2 = nl_addr2str(uVar2,auStack_58,0x33);
    FUN_10047ec4(4,"%s %s:%d Failed to lookup NH in neigh cache. IF: %d, IP: %s\n",0x3d,uVar4,
                 "sync.c",0x954,local_14,uVar2);
  }
  rtnl_neigh_put(uVar1);
  return local_68;
}



/* === FUN_1001b068 @ 0x1001b068 (size=460) === */

undefined1 FUN_1001b068(int param_1,int *param_2,char param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  uint local_38;
  
  iVar1 = rtnl_neigh_alloc();
  if (iVar1 == 0) {
    uVar4 = 0;
  }
  else {
    iVar2 = nl_addr_build(0x1a,param_1,6);
    if (iVar2 == 0) {
      rtnl_neigh_put(iVar1);
      uVar4 = 0;
    }
    else {
      rtnl_neigh_set_family(iVar1,7);
      uVar3 = FUN_1000bdf8(param_1 + 0x10);
      rtnl_neigh_set_ifindex(iVar1,uVar3);
      uVar3 = rtnl_neigh_str2state("reachable");
      rtnl_neigh_set_state(iVar1,uVar3);
      if (*(int *)(param_1 + 0x10) == 3) {
        uVar3 = nl_addr_build(2,param_1 + 0x20,4);
        rtnl_neigh_set_dst(iVar1,uVar3);
        local_38 = 6;
        nl_addr_put(uVar3);
      }
      else {
        local_38 = 4;
      }
      if (param_3 != '\x01') {
        local_38 = local_38 | 1;
      }
      rtnl_neigh_set_flags(iVar1,local_38);
      rtnl_neigh_set_lladdr(iVar1,iVar2);
      if (*(int *)(param_1 + 0xc) != 0) {
        rtnl_neigh_set_vlan(iVar1,*(uint *)(param_1 + 0xc) & 0xffff);
      }
      nl_addr_put(iVar2);
      *param_2 = iVar1;
      uVar4 = 1;
    }
  }
  return uVar4;
}



/* === FUN_1000a150 @ 0x1000a150 (size=2680) === */

undefined4 FUN_1000a150(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  undefined4 local_44 [4];
  code *local_34;
  
  memset(local_44,0,0x34);
  local_44[0] = 1;
  local_34 = FUN_10009ed0;
  FUN_1004ce88("/config/netlink/buf_size",&DAT_1181a788,0,0,0);
  FUN_1004d3f4("/etc/cumulus/switchd.conf","/config/","netlink/");
  nl_debug_set(local_44);
  FUN_1004ce88("/ctrl/netlink/resync",&DAT_1181a7e8,0,FUN_10009864,0);
  FUN_1004ce88("/ctrl/netlink/nl_logger",&DAT_1181a818,0,0,0);
  DAT_11e47408 = FUN_10009244(0);
  if (DAT_11e47408 == 0) {
    if (DAT_11e46cd4 < 0) {
      return 0;
    }
    uVar1 = bcm_l3_route_get();
    FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t allocate netlink socket.\n",0x31,uVar1,"netlink.c",0x170
                );
    return 0;
  }
  DAT_11e47410 = FUN_10009244(0x10);
  if (DAT_11e47410 == 0) {
    if (-1 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t allocate netlink socket.\n",0x31,uVar1,"netlink.c",
                   0x175);
    }
    goto LAB_1000ab8c;
  }
  DAT_11e4740c = nl_socket_alloc();
  if (DAT_11e4740c == 0) {
    if (-1 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t allocate manager netlink socket.\n",0x39,uVar1,
                   "netlink.c",0x17b);
    }
  }
  else {
    iVar2 = nl_cache_mngr_alloc(DAT_11e4740c,0,1,&DAT_11e47418);
    if (iVar2 < 0) {
      if (-1 < DAT_11e46cd4) {
        uVar1 = bcm_l3_route_get();
        uVar3 = nl_geterror(iVar2);
        FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t create cache manager: %s\n",0x31,uVar1,"netlink.c",
                     0x181,uVar3);
      }
    }
    else {
      cVar4 = FUN_100090c8(DAT_11e4740c);
      if (cVar4 == '\x01') {
        iVar2 = nl_cache_alloc_name("route/link",&DAT_11e47420);
        if (iVar2 < 0) {
          if (-1 < DAT_11e46cd4) {
            uVar1 = bcm_l3_route_get();
            uVar3 = nl_geterror(iVar2);
            FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t add link cache: %s\n",0x2b,uVar1,"netlink.c",
                         0x18c,uVar3);
          }
        }
        else {
          nl_cache_set_flags(DAT_11e47420,1);
          iVar2 = nl_cache_mngr_add_cache(DAT_11e47418,DAT_11e47420,FUN_10009398,0);
          if (iVar2 < 0) {
            if (-1 < DAT_11e46cd4) {
              uVar1 = bcm_l3_route_get();
              uVar3 = nl_geterror(iVar2);
              FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t add link cache: %s\n",0x2b,uVar1,"netlink.c",
                           0x196,uVar3);
            }
            nl_cache_free(DAT_11e47420);
          }
          else {
            iVar2 = nl_cache_mngr_add(DAT_11e47418,"route/route",FUN_10009398,0,&DAT_11e47424);
            if (iVar2 < 0) {
              if (-1 < DAT_11e46cd4) {
                uVar1 = bcm_l3_route_get();
                uVar3 = nl_geterror(iVar2);
                FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t add route cache: %s\n",0x2c,uVar1,
                             "netlink.c",0x19d,uVar3);
              }
            }
            else {
              iVar2 = nl_cache_mngr_add(DAT_11e47418,"route/mdb",FUN_10009398,0,&DAT_11e47430);
              if (-(iVar2 >> 0x1f) == 0) {
                iVar2 = nl_cache_alloc_name("route/neigh",&DAT_11e47428);
                if (iVar2 < 0) {
                  if (-1 < DAT_11e46cd4) {
                    uVar1 = bcm_l3_route_get();
                    uVar3 = nl_geterror(iVar2);
                    FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t alloc neigh cache: %s\n",0x2e,uVar1,
                                 "netlink.c",0x1a8,uVar3);
                  }
                }
                else {
                  nl_cache_set_flags(DAT_11e47428,1);
                  iVar2 = nl_cache_mngr_add_cache(DAT_11e47418,DAT_11e47428,FUN_10009398,0);
                  if (iVar2 < 0) {
                    if (-1 < DAT_11e46cd4) {
                      uVar1 = bcm_l3_route_get();
                      uVar3 = nl_geterror(iVar2);
                      FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t add neigh cache: %s\n",0x2c,uVar1,
                                   "netlink.c",0x1b2,uVar3);
                    }
                    nl_cache_free(DAT_11e47428);
                  }
                  else {
                    strncpy(&DAT_11e47434,"nlroute",0x10);
                    DAT_11e47444 = DAT_11e47418;
                    DAT_11e4744c = DAT_11e47408;
                    DAT_11e47450 = FUN_1000963c;
                    DAT_11e47414 = nl_socket_alloc();
                    if (DAT_11e47414 == 0) {
                      if (-1 < DAT_11e46cd4) {
                        uVar1 = bcm_l3_route_get();
                        FUN_10047ec4(0,
                                     "%s %s:%d CRIT Couldn\'t allocate genl manager netlink socket.\n"
                                     ,0x3e,uVar1,"netlink.c",0x1c0);
                      }
                    }
                    else {
                      iVar2 = nl_cache_mngr_alloc(DAT_11e47414,0x10,1,&DAT_11e4741c);
                      if (iVar2 < 0) {
                        if (-1 < DAT_11e46cd4) {
                          uVar1 = bcm_l3_route_get();
                          uVar3 = nl_geterror(iVar2);
                          FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t create cache genl manager: %s\n",
                                       0x36,uVar1,"netlink.c",0x1c6,uVar3);
                        }
                      }
                      else {
                        cVar4 = FUN_100090c8(DAT_11e47414);
                        if (cVar4 != '\x01') {
                          if (-1 < DAT_11e46cd4) {
                            uVar1 = bcm_l3_route_get();
                            FUN_10047ec4(0,
                                         "%s %s:%d CRIT Couldn\'t set bufsize for genl manager netlink socket.\n"
                                         ,0x45,uVar1,"netlink.c",0x1cc);
                          }
                          goto LAB_1000ab44;
                        }
                        iVar2 = FUN_1003f6b8(DAT_11e4741c,&DAT_11e4742c,FUN_10009398);
                        if (iVar2 == 0) {
                          if (-1 < DAT_11e46cd4) {
                            uVar1 = bcm_l3_route_get();
                            FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t initialize genl/bond cache\n",
                                         0x33,uVar1,"netlink.c",0x1d1);
                          }
                        }
                        else {
                          strncpy(&DAT_11e47454,"nlgeneric",0x10);
                          DAT_11e47464 = DAT_11e4741c;
                          DAT_11e4746c = DAT_11e47410;
                          DAT_11e47470 = FUN_10009568;
                          iVar2 = FUN_10041b80();
                          if (iVar2 != 0) {
                            uVar1 = nl_cache_mngr_get_fd(DAT_11e47418);
                            FUN_100460ac(uVar1,5,FUN_10009cac,&DAT_11e47434);
                            uVar1 = nl_cache_mngr_get_fd(DAT_11e4741c);
                            FUN_100460ac(uVar1,5,FUN_10009cac,&DAT_11e47454);
                            return 1;
                          }
                          if (-1 < DAT_11e46cd4) {
                            uVar1 = bcm_l3_route_get();
                            FUN_10047ec4(0,
                                         "%s %s:%d CRIT Couldn\'t initialize genl/port interface\n",
                                         0x37,uVar1,"netlink.c",0x1dd);
                          }
                        }
                        nl_cache_mngr_free(DAT_11e4741c);
                      }
                      nl_socket_free(DAT_11e47414);
                    }
                  }
                }
              }
              else if (-1 < DAT_11e46cd4) {
                uVar1 = bcm_l3_route_get();
                uVar3 = nl_geterror(-(iVar2 >> 0x1f));
                FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t add mdb cache: %s\n",0x2a,uVar1,"netlink.c",
                             0x1a3,uVar3);
              }
            }
          }
        }
      }
      else if (-1 < DAT_11e46cd4) {
        uVar1 = bcm_l3_route_get();
        FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t set bufsize for manager netlink socket.\n",0x40,
                     uVar1,"netlink.c",0x187);
      }
LAB_1000ab44:
      nl_cache_mngr_free(DAT_11e47418);
    }
    nl_socket_free(DAT_11e4740c);
  }
  nl_socket_free(DAT_11e47410);
LAB_1000ab8c:
  nl_socket_free(DAT_11e47408);
  return 0;
}



/* === FUN_10041b80 @ 0x10041b80 (size=1436) === */

undefined4 FUN_10041b80(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  DAT_11e47800 = FUN_10049440(0x200);
  if (DAT_11e47800 == 0) {
    if (-1 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT Failed to allocate port hash table\n",0x32,uVar1,"genl_port.c",
                   0x2f1);
    }
    return 0;
  }
  DAT_11e46fd0 = nl_socket_alloc();
  if (DAT_11e46fd0 == 0) {
    if (-1 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT Failed to allocate port socket\n",0x2e,uVar1,"genl_port.c",0x2f7
                  );
    }
  }
  else {
    iVar2 = genl_connect(DAT_11e46fd0);
    if (iVar2 < 0) {
      if (-1 < DAT_11e46cd4) {
        uVar1 = bcm_l3_route_get();
        FUN_10047ec4(0,"%s %s:%d CRIT Failed to genl connect to port socket\n",0x35,uVar1,
                     "genl_port.c",0x2fc);
      }
    }
    else {
      DAT_11e46fcc = nl_socket_alloc();
      if (DAT_11e46fcc == 0) {
        if (-1 < DAT_11e46cd4) {
          uVar1 = bcm_l3_route_get();
          FUN_10047ec4(0,"%s %s:%d CRIT Failed to allocate port sync socket\n",0x33,uVar1,
                       "genl_port.c",0x302);
        }
        goto LAB_100420e4;
      }
      iVar2 = genl_connect(DAT_11e46fcc);
      if (iVar2 < 0) {
        if (-1 < DAT_11e46cd4) {
          uVar1 = bcm_l3_route_get();
          FUN_10047ec4(0,"%s %s:%d CRIT Failed to genl connect to port socket\n",0x35,uVar1,
                       "genl_port.c",0x307);
        }
      }
      else {
        iVar2 = nl_socket_set_nonblocking(DAT_11e46fcc);
        if (iVar2 < 0) {
          if (-1 < DAT_11e46cd4) {
            uVar1 = bcm_l3_route_get();
            FUN_10047ec4(0,"%s %s:%d CRIT Failed to set genl port sync socket to non-blocking\n",
                         0x43,uVar1,"genl_port.c",0x30c);
          }
        }
        else {
          iVar2 = genl_ops_resolve(DAT_11e46fd0,&DAT_1181ae20);
          if (iVar2 < 0) {
            if (-1 < DAT_11e46cd4) {
              uVar1 = bcm_l3_route_get();
              FUN_10047ec4(0,"%s %s:%d CRIT Failed to resolve port ops, err %d\n",0x32,uVar1,
                           "genl_port.c",0x312,iVar2);
            }
          }
          else {
            iVar2 = genl_ctrl_resolve_grp(DAT_11e46fd0,"port_family","port_mc");
            if (iVar2 < 0) {
              if (-1 < DAT_11e46cd4) {
                uVar1 = bcm_l3_route_get();
                FUN_10047ec4(0,"%s %s:%d CRIT Failed to resolve port multicast group\n",0x36,uVar1,
                             "genl_port.c",0x318);
              }
            }
            else {
              iVar3 = genl_register_family(&DAT_1181ae20);
              if (iVar3 < 0) {
                if (-1 < DAT_11e46cd4) {
                  uVar1 = bcm_l3_route_get();
                  FUN_10047ec4(0,"%s %s:%d CRIT Failed to register port ops, err %d\n",0x33,uVar1,
                               "genl_port.c",0x31e,iVar3);
                }
              }
              else {
                iVar2 = nl_socket_add_membership(DAT_11e46fd0,iVar2);
                if (iVar2 < 0) {
                  if (-1 < DAT_11e46cd4) {
                    uVar1 = bcm_l3_route_get();
                    FUN_10047ec4(0,"%s %s:%d CRIT Failed to add port group membership, err %d\n",
                                 0x3b,uVar1,"genl_port.c",0x324,iVar2);
                  }
                }
                else {
                  nl_socket_disable_auto_ack(DAT_11e46fd0);
                  nl_socket_disable_auto_ack(DAT_11e46fcc);
                  iVar2 = nl_socket_modify_cb(DAT_11e46fd0,0,3,genl_handle_msg,0);
                  if (-1 < iVar2) {
                    uVar1 = nl_socket_get_fd(DAT_11e46fd0);
                    FUN_100460ac(uVar1,5,FUN_1004102c,0);
                    return 1;
                  }
                  if (-1 < DAT_11e46cd4) {
                    uVar1 = bcm_l3_route_get();
                    FUN_10047ec4(0,"%s %s:%d CRIT Failed to modify port socket notify cb, err %d\n",
                                 0x3e,uVar1,"genl_port.c",0x32e,iVar2);
                  }
                }
                genl_unregister_family(&DAT_1181ae20);
              }
            }
          }
        }
      }
    }
    nl_socket_free(DAT_11e46fd0);
    nl_socket_free(DAT_11e46fcc);
  }
LAB_100420e4:
  FUN_10049538(DAT_11e47800,free);
  return 0;
}



/* === FUN_1004102c @ 0x1004102c (size=176) === */

void FUN_1004102c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = nl_recvmsgs_default(DAT_11e46fd0);
  if ((iVar1 < 0) && (-1 < DAT_11e46cd4)) {
    uVar2 = bcm_l3_route_get();
    uVar3 = nl_geterror(iVar1);
    FUN_10047ec4(0,"%s %s:%d CRIT Failed run recvmsg_default on port socket, err %d, %s\n",0x45,
                 uVar2,"genl_port.c",0x20a,iVar1,uVar3);
  }
  return;
}



