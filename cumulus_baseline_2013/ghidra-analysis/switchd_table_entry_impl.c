/* L3_ENTRY hash insert/delete/lookup + L2 management decomp */

/* === FUN_10ebbb38 (size=1768) === */

int FUN_10ebbb38(int param_1,byte param_2,void *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int local_98;
  uint local_94;
  uint local_78;
  uint auStack_74 [21];
  int local_20;
  undefined1 auStack_1c [4];
  int local_18;
  byte local_14;
  void *local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_98 = FUN_10ebae30(param_1,0x82f,param_3,&local_20,auStack_1c);
  if (-1 < local_98) {
    if (local_20 == -1) {
      local_98 = -4;
    }
    else if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c24) & 0x20) == 0) {
      uVar1 = (int)(*(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                              local_20 * 4) + 0x28) + 3) >> 2;
      local_78 = (uVar1 & 0x1f) << 9 |
                 (local_14 & 3) << 1 |
                 (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                            *(int *)((&DAT_1212b9c4)[local_18] + 0x5bb4) * 0x10 + 8) & 0x3f) << 0x14
                 | (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                              *(int *)((&DAT_1212b9c4)[local_18] + 0x5ba4) * 0x10 + 8) & 0x3f) <<
                   0xe | 0x68000000;
      memcpy(auStack_74,local_10,uVar1 << 2);
      local_98 = FUN_10861634(local_18,&local_78,uVar1 + 1,uVar1 + 2,1);
      if ((local_78 & 0xfc000000) == 0x6c000000) {
        if (((local_78 & 1) != 0) || (local_98 == -0xb)) {
          if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c14) & 0x800000) != 0) {
            iVar4 = uVar1 - 1;
            iVar2 = FUN_112e9dec(*(undefined4 *)
                                  (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4)
                                                    + 0x24) + local_20 * 4) + 0x10));
            iVar3 = FUN_107a95f4(local_18,local_20);
            uVar5 = iVar2 + iVar3;
            uVar5 = uVar5 + (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) *
                            -0x20;
            if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
               (((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7a4c044f) != 0 ||
                  ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
                 ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)) ||
                ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))) {
              uVar6 = 0xf;
            }
            else {
              uVar6 = 7;
            }
            if ((auStack_74[iVar4] >> (uVar5 & 0x3f) & uVar6) != 0) {
              local_94 = FUN_107a95f4(local_18,local_20);
              local_94 = local_94 +
                         (((int)local_94 >> 5) + (uint)((int)local_94 < 0 && (local_94 & 0x1f) != 0)
                         ) * -0x20;
              if (local_94 == 0) {
                local_94 = 0x20;
              }
              if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
                 ((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7a4c044f) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
                  (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))))) {
                uVar6 = 0xf;
              }
              else {
                uVar6 = 7;
              }
              FUN_10760cd4(0x200000,
                           "Insert table[L3_ENTRY_XXX]: Parity Error Index %d Bucket Bitmap 0x%08x\n"
                           ,auStack_74[iVar4] >> (local_94 & 0x3f) &
                            (1 << (0x20 - local_94 & 0x3f)) - 1U |
                            auStack_74[uVar1] << (0x20 - local_94 & 0x3f) &
                            *(uint *)((&DAT_1212ba0c)[local_18] + local_20 * 0xec + 0x31bc),
                           auStack_74[iVar4] >> (uVar5 & 0x3f) & uVar6);
              return -1;
            }
          }
          FUN_10760cd4(4,"Insert table[L3_ENTRY_XXX]: hash bucket full\n");
          local_98 = -6;
        }
      }
      else {
        FUN_10760cd4(0x200000,
                     "soc_fb_l3x_insert: invalid S-Channel reply, expected L3_INSERT_DONE_MSG:\n");
        FUN_1086100c(local_18,&local_78,1);
        local_98 = -1;
      }
    }
    else {
      local_98 = FUN_1081053c(local_18,local_20,0xffffffff,local_14,local_10,0,0);
    }
  }
  return local_98;
}



/* === FUN_10ebc220 (size=1744) === */

int FUN_10ebc220(int param_1,byte param_2,void *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int local_98;
  uint local_94;
  uint local_78;
  uint auStack_74 [21];
  int local_20;
  undefined1 auStack_1c [4];
  int local_18;
  byte local_14;
  void *local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_98 = FUN_10ebae30(param_1,0x82f,param_3,&local_20,auStack_1c);
  if (-1 < local_98) {
    if (local_20 == -1) {
      local_98 = -4;
    }
    else {
      uVar1 = (int)(*(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                              local_20 * 4) + 0x28) + 3) >> 2;
      iVar2 = FUN_10760db0(4);
      if (iVar2 != 0) {
        FUN_10760cd4(4,"Delete table[L3_ENTRY_XXXm]: ");
        FUN_107ee71c(local_18,local_20,local_10);
        FUN_10760cd4(4,&UNK_1141061c);
      }
      local_78 = (uVar1 & 0x1f) << 9 |
                 (local_14 & 3) << 1 |
                 (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                            *(int *)((&DAT_1212b9c4)[local_18] + 0x5bb4) * 0x10 + 8) & 0x3f) << 0x14
                 | (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x30) +
                              *(int *)((&DAT_1212b9c4)[local_18] + 0x5ba4) * 0x10 + 8) & 0x3f) <<
                   0xe | 0x70000000;
      memcpy(auStack_74,local_10,uVar1 << 2);
      local_98 = FUN_10861634(local_18,&local_78,uVar1 + 1,uVar1 + 2,1);
      if ((local_78 & 0xfc000000) == 0x74000000) {
        if (((local_78 & 1) != 0) || (local_98 == -0xb)) {
          if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c14) & 0x800000) != 0) {
            iVar4 = uVar1 - 1;
            iVar2 = FUN_112e9dec(*(undefined4 *)
                                  (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4)
                                                    + 0x24) + local_20 * 4) + 0x10));
            iVar3 = FUN_107a95f4(local_18,local_20);
            uVar5 = iVar2 + iVar3;
            uVar5 = uVar5 + (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) *
                            -0x20;
            if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
               (((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7a4c044f) != 0 ||
                  ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
                 ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)) ||
                ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))) {
              uVar6 = 0xf;
            }
            else {
              uVar6 = 7;
            }
            if ((auStack_74[iVar4] >> (uVar5 & 0x3f) & uVar6) != 0) {
              local_94 = FUN_107a95f4(local_18,local_20);
              local_94 = local_94 +
                         (((int)local_94 >> 5) + (uint)((int)local_94 < 0 && (local_94 & 0x1f) != 0)
                         ) * -0x20;
              if (local_94 == 0) {
                local_94 = 0x20;
              }
              if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
                 ((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7a4c044f) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
                  (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))))) {
                uVar6 = 0xf;
              }
              else {
                uVar6 = 7;
              }
              FUN_10760cd4(0x200000,
                           "Delete table[L3_ENTRYm]: Parity Error Index %d Bucket Bitmap 0x%08x\n",
                           auStack_74[iVar4] >> (local_94 & 0x3f) &
                           (1 << (0x20 - local_94 & 0x3f)) - 1U |
                           auStack_74[uVar1] << (0x20 - local_94 & 0x3f) &
                           *(uint *)((&DAT_1212ba0c)[local_18] + local_20 * 0xec + 0x31bc),
                           auStack_74[iVar4] >> (uVar5 & 0x3f) & uVar6);
              local_98 = -1;
            }
          }
          FUN_10760cd4(4,"Delete table[L3_ENTRYm]: Not found\n");
        }
      }
      else {
        FUN_10760cd4(0x200000,
                     "soc_fb_l3x_delete: invalid S-Channel reply, expected L3_DELETE_DONE_MSG:\n");
        FUN_1086100c(local_18,&local_78,1);
        local_98 = -1;
      }
    }
  }
  return local_98;
}



/* === FUN_10ebb2fc (size=2108) === */

int FUN_10ebb2fc(int param_1,byte param_2,void *param_3,int param_4,uint *param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int local_b8;
  uint local_b4;
  uint local_94;
  uint auStack_90 [21];
  int local_3c;
  undefined1 auStack_38 [16];
  int local_28;
  byte local_24;
  void *local_20;
  int local_1c;
  uint *local_18;
  
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  iVar2 = FUN_10ebae30(param_1,0x82f,param_3,&local_3c,auStack_38);
  if (-1 < iVar2) {
    if (local_3c == -1) {
      iVar2 = -4;
    }
    else {
      local_b4 = FUN_107a95f4(local_28,local_3c);
      local_b4 = local_b4 +
                 (((int)local_b4 >> 5) + (uint)((int)local_b4 < 0 && (local_b4 & 0x1f) != 0)) *
                 -0x20;
      if (local_b4 == 0) {
        local_b4 = 0x20;
      }
      uVar1 = (int)(*(ushort *)
                     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                              local_3c * 4) + 0x28) + 3) >> 2;
      local_94 = (uVar1 & 0x1f) << 9 |
                 (local_24 & 3) << 1 |
                 (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x30) +
                            *(int *)((&DAT_1212b9c4)[local_28] + 0x5bb4) * 0x10 + 8) & 0x3f) << 0x14
                 | (*(uint *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x30) +
                              *(int *)((&DAT_1212b9c4)[local_28] + 0x5ba4) * 0x10 + 8) & 0x3f) <<
                   0xe | 0x88000000;
      memcpy(auStack_90,local_20,uVar1 << 2);
      iVar2 = FUN_10861634(local_28,&local_94,uVar1 + 1,uVar1 + 2,1);
      if ((local_94 & 0xfc000000) == 0x8c000000) {
        if (((local_94 & 1) == 0) && (iVar2 != -0xb)) {
          for (local_b8 = 0; local_b8 < (int)(uVar1 - 1); local_b8 = local_b8 + 1) {
            *(uint *)(local_1c + local_b8 * 4) = auStack_90[local_b8];
          }
          *(uint *)(local_1c + local_b8 * 4) = auStack_90[local_b8] & (1 << (local_b4 & 0x3f)) - 1U;
          *local_18 = auStack_90[local_b8] >> (local_b4 & 0x3f) &
                      (1 << (0x20 - local_b4 & 0x3f)) - 1U;
          *local_18 = *local_18 |
                      auStack_90[local_b8 + 1] << (0x20 - local_b4 & 0x3f) &
                      *(uint *)((&DAT_1212ba0c)[local_28] + local_3c * 0xec + 0x31bc);
          iVar2 = FUN_10760db0(4);
          if (iVar2 != 0) {
            FUN_10760cd4(4,"L3 entry lookup: ");
            FUN_107ee71c(local_28,local_3c,local_1c);
            FUN_10760cd4(4," (index=%d)\n",*local_18);
          }
          iVar2 = 0;
        }
        else {
          *local_18 = 0xffffffff;
          if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c14) & 0x800000) != 0) {
            iVar4 = uVar1 - 1;
            iVar2 = FUN_112e9dec(*(undefined4 *)
                                  (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4)
                                                    + 0x24) + local_3c * 4) + 0x10));
            iVar3 = FUN_107a95f4(local_28,local_3c);
            uVar5 = iVar2 + iVar3;
            uVar5 = uVar5 + (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) *
                            -0x20;
            if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
               (((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7a4c044f) != 0 ||
                  ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
                 ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0)) ||
                ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))) {
              uVar6 = 0xf;
            }
            else {
              uVar6 = 7;
            }
            if ((auStack_90[iVar4] >> (uVar5 & 0x3f) & uVar6) != 0) {
              if ((*(int *)((&DAT_1212b9c4)[local_28] + 0x10) == 0) &&
                 ((((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x7a4c044f) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x10) != 0)) ||
                  (((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x40) != 0 ||
                   ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x14) & 0x20) != 0)))))) {
                uVar6 = 0xf;
              }
              else {
                uVar6 = 7;
              }
              FUN_10760cd4(0x200000,
                           "Lookup table[L3_ENTRY_XXX]: Parity Error Index %d Bucket Bitmap 0x%08x\n"
                           ,auStack_90[iVar4] >> (local_b4 & 0x3f) &
                            (1 << (0x20 - local_b4 & 0x3f)) - 1U |
                            auStack_90[uVar1] << (0x20 - local_b4 & 0x3f) &
                            *(uint *)((&DAT_1212ba0c)[local_28] + local_3c * 0xec + 0x31bc),
                           auStack_90[iVar4] >> (uVar5 & 0x3f) & uVar6);
              return -1;
            }
          }
          iVar2 = -7;
        }
      }
      else {
        FUN_10760cd4(0x200000,
                     "soc_fb_l3x_lookup: invalid S-Channel reply, expected L3X2_LOOKUP_ACK_MSG:\n");
        FUN_1086100c(local_28,&local_94,uVar1 + 2);
        iVar2 = -1;
      }
    }
  }
  return iVar2;
}



/* === FUN_10b33efc (size=1036) === */

int FUN_10b33efc(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *__dest;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  
  iVar1 = (&DAT_1212b9c4)[param_1];
  local_40 = 0;
  local_3c = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                              0x1f98) + 0xc);
  iVar2 = *(int *)((&DAT_1212ba0c)[param_1] + 0x779c4);
  iVar3 = FUN_1075fcd4(param_1,0x400,"L2_ENTRY_ONLY_delete");
  if (iVar3 == 0) {
    local_40 = -2;
  }
  else {
    FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x165618),0xffffffff);
    for (; local_3c < iVar2; local_3c = local_3c + 0x40) {
      local_48 = local_3c + 0x3f;
      if (iVar2 < local_3c + 0x3f) {
        local_48 = iVar2;
      }
      iVar4 = FUN_108020c0(param_1,0x7e6,0xffffffff,local_3c,local_48,iVar3);
      if (iVar4 < 0) {
        FUN_1075ffa4(param_1,iVar3);
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x165618));
        return iVar4;
      }
      for (local_44 = 0; local_44 < 0x40; local_44 = local_44 + 1) {
        __dest = (void *)(iVar3 + ((int)(*(ushort *)
                                          (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] +
                                                                     0x2f26f4) + 0x24) + 0x1f98) +
                                          0x28) + 3) >> 2) * local_44 * 4);
        iVar4 = FUN_107a2924(param_1,0x7e6,__dest,0xe37e);
        if ((iVar4 != 0) &&
           ((iVar4 = FUN_107a2924(param_1,0x7e6,__dest,0x70c7), iVar4 == 1 ||
            (iVar4 = FUN_107a2924(param_1,0x7e6,__dest,0x70c7), iVar4 == 2)))) {
          memcpy(__dest,*(void **)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) +
                                                    0x24) + 0x1f98) + 8),0x10);
        }
      }
      local_40 = FUN_10808740(param_1,0x7e6,0xffffffff,local_3c,local_48,iVar3);
      if (local_40 < 0) {
        FUN_1075ffa4(param_1,iVar3);
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x165618));
        return local_40;
      }
    }
    if (*(int *)(iVar1 + 0x2f1924) != 0) {
      FUN_11311c0c(*(undefined4 *)(iVar1 + 0x2f1930),0xffffffff);
      FUN_112cef24(*(undefined4 *)(iVar1 + 0x2f1924));
      FUN_11311d68(*(undefined4 *)(iVar1 + 0x2f1930));
    }
    FUN_1075ffa4(param_1,iVar3);
    FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x165618));
  }
  return local_40;
}



/* === FUN_10b31dd4 (size=1988) === */

int FUN_10b31dd4(int param_1)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  void *__dest;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [24];
  int local_18;
  
  iVar6 = (&DAT_1212b9c4)[param_1];
  local_70 = 0;
  local_18 = param_1;
  if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c38) & 0x800000) == 0) {
    local_6c = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                                0x1f98) + 0xc);
    iVar1 = *(int *)((&DAT_1212ba0c)[param_1] + 0x779c4);
    iVar4 = FUN_1075fcd4(param_1,0x400,"L2_ENTRY_ONLY_delete");
    if (iVar4 == 0) {
      return -2;
    }
    FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618),0xffffffff);
    for (; local_6c < iVar1; local_6c = local_6c + 0x40) {
      local_78 = local_6c + 0x3f;
      if (iVar1 < local_6c + 0x3f) {
        local_78 = iVar1;
      }
      local_70 = FUN_108020c0(local_18,0x7e6,0xffffffff,local_6c,local_78,iVar4);
      if (local_70 < 0) {
        FUN_1075ffa4(local_18,iVar4);
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618));
        return local_70;
      }
      bVar2 = false;
      for (local_74 = 0; local_74 < 0x40; local_74 = local_74 + 1) {
        __dest = (void *)(iVar4 + ((int)(*(ushort *)
                                          (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] +
                                                                     0x2f26f4) + 0x24) + 0x1f98) +
                                          0x28) + 3) >> 2) * local_74 * 4);
        iVar5 = FUN_107a2924(local_18,0x7e6,__dest,0xe37e);
        if ((iVar5 != 0) &&
           ((iVar5 = FUN_107a2924(local_18,0x7e6,__dest,0x70c7), iVar5 == 0 || (iVar5 == 3)))) {
          memcpy(__dest,*(void **)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4)
                                                    + 0x24) + 0x1f98) + 8),0x10);
          bVar2 = true;
        }
      }
      if ((bVar2) &&
         (local_70 = FUN_10808740(local_18,0x7e6,0xffffffff,local_6c,local_78,iVar4), local_70 < 0))
      {
        FUN_1075ffa4(local_18,iVar4);
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618));
        return local_70;
      }
    }
    FUN_1075ffa4(local_18,iVar4);
  }
  else {
    memset(auStack_40,0,0x10);
    memset(auStack_30,0,0x10);
    FUN_107a2a0c(local_18,0x7db,auStack_40,0xe37e,1);
    FUN_107a2a0c(local_18,0x7da,auStack_30,0xe37e,1);
    uVar3 = FUN_1079dce4(local_18,0x7db,0x70c7);
    FUN_107a2a0c(local_18,0x7db,auStack_40,0x70c7,(1 << (uVar3 & 0x3f)) + -1);
    FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618),0xffffffff);
    local_70 = FUN_10852920(local_18,0x5a65,0xfffffff6,0xa1,1);
    if (-1 < local_70) {
      local_70 = FUN_108080ac(local_18,0x7db,0xffffffff,0,auStack_40);
    }
    if ((-1 < local_70) &&
       (local_70 = FUN_108080ac(local_18,0x7da,0xffffffff,0,auStack_30), -1 < local_70)) {
      local_70 = FUN_10eb2cfc(local_18,0x5a65,0xffffffff);
    }
    if (-1 < local_70) {
      FUN_107a2a0c(local_18,0x7da,auStack_30,0x70c7,3);
      local_70 = FUN_108080ac(local_18,0x7da,0xffffffff,0,auStack_30);
      if (-1 < local_70) {
        local_70 = FUN_10eb2cfc(local_18,0x5a65,0xffffffff);
      }
    }
    if (local_70 < 0) {
      return local_70;
    }
  }
  if (*(int *)(iVar6 + 0x2f1924) != 0) {
    FUN_11311c0c(*(undefined4 *)(iVar6 + 0x2f1930),0xffffffff);
    FUN_112cef24(*(undefined4 *)(iVar6 + 0x2f1924));
    FUN_11311d68(*(undefined4 *)(iVar6 + 0x2f1930));
  }
  if ((((*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) + 0xfe0) != 0) &&
       ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) + 0xfe0) & 2)
        != 0)) &&
      ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) + 0xfe0) & 2) !=
       0)) && (*(int *)((&DAT_1212ba0c)[local_18] + 0x3da5c) -
               *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                                0xfe0) + 0xc) != -1)) {
    iVar6 = FUN_108092ec(local_18,0x3fe,0xffffffff,1);
    if (iVar6 < 0) {
      FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618));
      return iVar6;
    }
    local_70 = FUN_108092ec(local_18,0x3fb,0xffffffff,1);
    if (local_70 < 0) {
      FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618));
      return local_70;
    }
  }
  FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x165618));
  return local_70;
}



/* === FUN_10da71b8 (size=1432) === */

int FUN_10da71b8(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  void *__dest;
  int local_68;
  int local_64;
  int local_58;
  
  local_58 = 0;
  iVar6 = FUN_107953d0(param_1,"mem_clear_hw_acceleration",1);
  if ((iVar6 == 0) || (uVar7 = FUN_11311498(), (uVar7 & 0x8b0000) != 0)) {
    iVar8 = FUN_107953d0(param_1,"l2delete_chunks",100);
    local_68 = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                                0x1f84) + 0xc);
    iVar6 = *(int *)((&DAT_1212ba0c)[param_1] + 0x77528);
    iVar9 = FUN_1075fcd4(param_1,iVar8 << 4,"L2_ENTRY_1_delete");
    if (iVar9 == 0) {
      local_58 = -2;
    }
    else {
      uVar1 = *(undefined4 *)(&DAT_11f15d68 + param_1 * 0x10);
      iVar2 = *(int *)(&DAT_11f15d68 + param_1 * 0x10);
      FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x16742c),0xffffffff);
      for (; local_68 <= iVar6; local_68 = local_68 + iVar8) {
        iVar11 = iVar6;
        if (local_68 + iVar8 < iVar6) {
          iVar11 = local_68 + iVar8 + -1;
        }
        local_58 = FUN_108020c0(param_1,0x7e1,0xffffffff,local_68,iVar11,iVar9);
        if (local_58 < 0) break;
        bVar5 = false;
        bVar3 = false;
        for (local_64 = 0; local_64 <= iVar11 - local_68; local_64 = local_64 + 1) {
          __dest = (void *)(iVar9 + ((int)(*(ushort *)
                                            (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] +
                                                                       0x2f26f4) + 0x24) + 0x1f84) +
                                            0x28) + 3) >> 2) * local_64 * 4);
          if (bVar3) {
            memcpy(__dest,*(void **)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4)
                                                      + 0x24) + 0x1f84) + 8),0x10);
            bVar3 = false;
          }
          else {
            iVar10 = FUN_1079e718(uVar1,__dest);
            if (iVar10 != 0) {
              iVar10 = FUN_1079e718(iVar2 + 0x18,__dest);
              bVar4 = false;
              if ((iVar10 == 0) || (iVar10 == 2)) {
                bVar4 = true;
              }
              if ((iVar10 == 1) || (iVar10 == 3)) {
                bVar4 = true;
                bVar3 = true;
              }
              if (bVar4) {
                memcpy(__dest,*(void **)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] +
                                                                   0x2f26f4) + 0x24) + 0x1f84) + 8),
                       0x10);
                bVar5 = true;
              }
            }
          }
        }
        if ((bVar5) &&
           (local_58 = FUN_10808740(param_1,0x7e1,0xffffffff,local_68,iVar11,iVar9), local_58 < 0))
        break;
      }
      FUN_1075ffa4(param_1,iVar9);
      FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x16742c));
      if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c24) & 0x8000000) != 0) {
        if (-1 < local_58) {
          local_58 = FUN_108092ec(param_1,0x3f9,0xffffffff,0);
        }
        if (-1 < local_58) {
          local_58 = FUN_108092ec(param_1,0x3fa,0xffffffff,0);
        }
      }
      if (*(int *)((&DAT_1212b9c4)[param_1] + 0x2f1924) != 0) {
        FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x2f1930),0xffffffff);
        FUN_112cef24(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x2f1924));
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[param_1] + 0x2f1930));
      }
    }
  }
  else {
    local_58 = FUN_10da2480(param_1,0xffffffff);
  }
  return local_58;
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



/* === FUN_1125af5c (size=2544) === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1125af5c(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int *param_5,
                undefined4 *param_6,undefined4 *param_7,int param_8)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined1 uVar8;
  int local_280;
  int local_27c;
  int local_274;
  int local_270;
  undefined4 local_26c;
  int local_234;
  undefined1 auStack_230 [28];
  undefined4 local_214;
  int local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined1 auStack_1fc [204];
  uint local_130 [12];
  undefined1 auStack_100 [208];
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  int local_14;
  
  local_234 = 0;
  local_20c = DAT_117f8264;
  local_208 = DAT_117f8268;
  local_204 = DAT_117f826c;
  local_200 = _DAT_117f8270;
  local_30 = param_1;
  local_2c = param_2;
  local_28 = param_3;
  local_24 = param_4;
  local_20 = param_5;
  local_1c = param_6;
  local_18 = param_7;
  local_14 = param_8;
  memset(auStack_1fc,0,0xcc);
  local_270 = -1;
  local_26c = 0;
  uVar2 = FUN_107a2924(local_30,0x818,local_2c,0x5595);
  uVar3 = FUN_107a2924(local_30,0x818,local_2c,0xea67);
  if (local_24 == -2) {
    pcVar7 = "Global";
  }
  else {
    pcVar7 = "VRF";
  }
  FUN_10760cd4(0x10000,
               "Prefare AUX Scratch for searching TCAM in %s region, Key data: v6 %d global %d vrf %d\n"
               ,pcVar7,2,uVar2,uVar3);
  if (local_24 == -2) {
    uVar8 = local_14 != 0;
    local_274 = FUN_11234c2c(local_30);
    if (local_274 != 0) {
      if ((*(uint *)(&DAT_1212b9c4)[local_30] & 0x20) == 0) {
        local_274 = 0;
      }
      else {
        local_274 = 3;
      }
    }
    FUN_107a2a0c(local_30,0x818,local_2c,0x5595,1);
    FUN_107a2a0c(local_30,0x818,local_2c,0xea67,0);
  }
  else {
    if (local_14 == 0) {
      uVar8 = 2;
    }
    else {
      uVar8 = 3;
    }
    local_274 = FUN_11234c2c(local_30);
    if (local_274 != 0) {
      if ((*(uint *)(&DAT_1212b9c4)[local_30] & 0x20) == 0) {
        local_274 = 0;
      }
      else {
        local_274 = 0xc;
      }
    }
  }
  memset(auStack_230,0,0x1c);
  iVar4 = FUN_11261d8c(local_30,local_2c,2,uVar8,0,auStack_230);
  if (-1 < iVar4) {
    if (local_24 == -2) {
      FUN_107a2a0c(local_30,0x818,local_2c,0x5595,uVar2);
      FUN_107a2a0c(local_30,0x818,local_2c,0xea67,uVar3);
    }
    iVar4 = FUN_1124d1ec(local_30,2,auStack_230,1,&local_234,local_20,local_1c);
    puVar1 = PTR_s_L3_DEFIP_PAIR_128_11ab2394;
    if (-1 < iVar4) {
      if (local_234 == 0) {
        FUN_10760cd4(0x10000,"Could not find bucket\n");
        iVar4 = -7;
      }
      else {
        uVar2 = FUN_11234f04(local_30,0x818,
                             (*local_20 >> 1 & 0x3ffU) + (*local_20 >> 2 & 0xfffffc00U),1);
        FUN_10760cd4(0x10000,"Hit in memory %s, index %d, bucket_index %d\n",puVar1,uVar2,*local_1c)
        ;
        iVar4 = FUN_112528bc(local_30,local_2c,&local_210);
        if (-1 < iVar4) {
          iVar4 = FUN_11234c2c(local_30);
          if ((iVar4 == 0) && ((*(uint *)(&DAT_1212b9c4)[local_30] & 0x20) == 0)) {
            iVar4 = 0x10;
          }
          else {
            iVar4 = 8;
          }
          FUN_10760cd4(0x10000,"Start searching mem %s bucket %d(count %d) for Length %d\n",
                       PTR_s_L3_DEFIP_ALPM_IPV6_128_11ab2368,*local_1c,iVar4,local_210);
          for (local_280 = 0; local_280 < iVar4; local_280 = local_280 + 1) {
            memset(auStack_100,0,0xcc);
            local_130[0] = 0;
            local_130[1] = 0;
            local_130[2] = 0;
            local_130[3] = 0;
            local_130[4] = 0;
            local_130[5] = 0;
            local_130[6] = 0;
            local_130[7] = 0;
            local_130[8] = 0;
            local_130[9] = 0;
            local_130[10] = 0;
            local_130[0xb] = 0;
            iVar5 = FUN_11236d54(local_30,0x80d,*local_1c,local_280,local_274,&local_214);
            if (iVar5 != -6) {
              iVar5 = FUN_10801b4c(local_30,0x80d,0xffffffff,local_214,auStack_100);
              if (iVar5 < 0) {
                return iVar5;
              }
              iVar5 = FUN_107a2924(local_30,0x80d,auStack_100,0xe37e);
              iVar6 = FUN_107a2924(local_30,0x80d,auStack_100,0x76e0);
              FUN_10760cd4(0x10000,"Bucket %5d Index %6d: Valid %d, Length %d\n",*local_1c,local_214
                           ,iVar5,iVar6);
              if ((iVar5 != 0) && (iVar6 <= local_210)) {
                FUN_112d1134(local_130,0x80 - iVar6,iVar6);
                FUN_107a20f0(local_30,0x80d,auStack_100,0x7034,local_130 + 4);
                local_130[0xb] = FUN_107a2924(local_30,0x818,local_2c,local_200);
                local_130[10] = FUN_107a2924(local_30,0x818,local_2c,local_204);
                local_130[9] = FUN_107a2924(local_30,0x818,local_2c,local_208);
                local_130[8] = FUN_107a2924(local_30,0x818,local_2c,local_20c);
                FUN_10760cd4(0x10000,
                             "\tmask %08x %08x %08x %08x \n\t key %08x %08x %08x %08x \n\thost %08x %08x %08x %08x \n"
                             ,local_130[3],local_130[2],local_130[1],local_130[0],local_130[7],
                             local_130[6],local_130[5],local_130[4],local_130[0xb],local_130[10],
                             local_130[9],local_130[8]);
                for (local_27c = 3;
                    (-1 < local_27c &&
                    (((local_130[local_27c + 8] ^ local_130[local_27c + 4]) & local_130[local_27c])
                     == 0)); local_27c = local_27c + -1) {
                }
                if ((local_27c < 0) &&
                   ((FUN_10760cd4(0x10000,"Found a match in mem %s bucket %d, index %d\n",
                                  PTR_s_L3_DEFIP_ALPM_IPV6_128_11ab2368,*local_1c,local_214),
                    local_270 == -1 || (local_270 < iVar6)))) {
                  local_26c = local_214;
                  memcpy(auStack_1fc,auStack_100,0xcc);
                  local_270 = iVar6;
                }
              }
            }
          }
          if (local_270 == -1) {
            uVar2 = FUN_11234f04(local_30,0x818,
                                 (*local_20 >> 1 & 0x3ffU) + (*local_20 >> 2 & 0xfffffc00U),1);
            *local_18 = uVar2;
            iVar4 = FUN_10801b4c(local_30,0x818,0xffffffff,*local_18,local_28);
            if (-1 < iVar4) {
              iVar4 = 0;
            }
          }
          else {
            iVar4 = FUN_112626e8(local_30,auStack_1fc,0x80d,2,local_24,*local_1c,local_26c,local_28)
            ;
            if (-1 < iVar4) {
              *local_18 = local_26c;
              FUN_10760cd4(0x10000,"Hit mem %s bucket %d, index %d\n",
                           PTR_s_L3_DEFIP_ALPM_IPV6_128_11ab2368,*local_1c,local_26c);
            }
          }
        }
      }
    }
  }
  return iVar4;
}



/* === FUN_10e0f094 (size=1140) === */

int FUN_10e0f094(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint local_88;
  undefined1 auStack_74 [80];
  undefined1 auStack_24 [12];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  iVar1 = FUN_10e01238(param_1,auStack_24);
  if (-1 < iVar1) {
    iVar1 = *(int *)((&DAT_1212ba0c)[local_18] + 0x7b114);
    iVar3 = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                             0x2088) + 0xc);
    memset(auStack_74,0,0x50);
    for (local_88 = 0; local_88 < (iVar1 - iVar3) + 1U; local_88 = local_88 + 1) {
      iVar2 = FUN_10801b4c(local_18,0x822,0xffffffff,local_88,auStack_74);
      if (iVar2 < 0) {
        iVar1 = FUN_10761348(&DAT_11858c08,0x800101);
        if (iVar1 == 0) {
          return iVar2;
        }
        if (PTR_FUN_11e454ac == (undefined *)0x0) {
          return iVar2;
        }
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar1 = -iVar2;
        }
        else {
          iVar1 = 0x13;
        }
        (*(code *)PTR_FUN_11e454ac)
                  ("OAM(unit %d) Error: L3_ENTRY (index=%d) read failed  - %s.\n",local_18,local_88,
                   (&PTR_DAT_11e43a78)[iVar1]);
        return iVar2;
      }
      iVar2 = FUN_107a2924(local_18,0x822,auStack_74,0xe37e);
      if (iVar2 != 0) {
        iVar2 = FUN_107a2924(local_18,0x822,auStack_74,0x70c7);
        if (iVar2 == 8) {
          iVar2 = FUN_10e0d528(local_18,local_88,auStack_74);
          if (iVar2 < 0) {
            iVar1 = FUN_10761348(&DAT_11858c08,0x800101);
            if (iVar1 == 0) {
              return iVar2;
            }
            if (PTR_FUN_11e454ac == (undefined *)0x0) {
              return iVar2;
            }
            if ((iVar2 < 1) && (-0x13 < iVar2)) {
              iVar1 = -iVar2;
            }
            else {
              iVar1 = 0x13;
            }
            (*(code *)PTR_FUN_11e454ac)
                      ("OAM(unit %d) Error: Local endpoint (index=%d) reconstruct failed  - %s.\n",
                       local_18,local_88,(&PTR_DAT_11e43a78)[iVar1]);
            return iVar2;
          }
        }
        else if ((iVar2 == 9) && (iVar2 = FUN_10e0c94c(local_18,local_88,auStack_74), iVar2 < 0)) {
          iVar1 = FUN_10761348(&DAT_11858c08,0x800101);
          if (iVar1 == 0) {
            return iVar2;
          }
          if (PTR_FUN_11e454ac == (undefined *)0x0) {
            return iVar2;
          }
          if ((iVar2 < 1) && (-0x13 < iVar2)) {
            iVar1 = -iVar2;
          }
          else {
            iVar1 = 0x13;
          }
          (*(code *)PTR_FUN_11e454ac)
                    ("OAM(unit %d) Error: Remote endpoint (index=%d) reconstruct failed  - %s.\n",
                     local_18,local_88,(&PTR_DAT_11e43a78)[iVar1]);
          return iVar2;
        }
      }
    }
    iVar1 = FUN_10e0e120(local_18);
    if (iVar1 < 0) {
      iVar3 = FUN_10761348(&DAT_11858c08,0x800101);
      if ((iVar3 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar3 = -iVar1;
        }
        else {
          iVar3 = 0x13;
        }
        (*(code *)PTR_FUN_11e454ac)
                  ("OAM(unit %d) Error: Endpoint Tx config recovery failed  - %s.\n",local_18,
                   (&PTR_DAT_11e43a78)[iVar3]);
      }
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
}



/* === FUN_10e04a74 (size=2248) === */

int FUN_10e04a74(int param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined1 auStack_90 [8];
  undefined4 local_88;
  undefined4 *local_84;
  undefined4 local_80;
  undefined1 auStack_7c [80];
  undefined4 local_2c;
  int local_28 [4];
  int local_18;
  uint *local_14;
  
  local_88 = 0;
  local_2c = 0xffffffff;
  if (param_2 == (uint *)0x0) {
    iVar1 = -1;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    iVar1 = FUN_10e01238(param_1,local_28);
    if (-1 < iVar1) {
      iVar2 = *(int *)(local_28[0] + 0x3c) + param_2[4] * 0x84;
      if ((param_2[2] & 0x1ffff) == 0) {
        iVar1 = FUN_10e00dd0(local_18,&local_88);
        if (iVar1 < 0) {
          iVar2 = FUN_10761348(&DAT_11858c08,0x800101);
          if (iVar2 == 0) {
            return iVar1;
          }
          if (PTR_FUN_11e454ac == (undefined *)0x0) {
            return iVar1;
          }
          if ((iVar1 < 1) && (-0x13 < iVar1)) {
            iVar2 = -iVar1;
          }
          else {
            iVar2 = 0x13;
          }
          (*(code *)PTR_FUN_11e454ac)
                    ("OAM(unit %d) Error: Opcode profile init failed for EP=%d  %s.\n",local_18,
                     param_2[4],(&PTR_DAT_11e43a78)[iVar2]);
          return iVar1;
        }
      }
      else {
        iVar1 = FUN_10e00ab8(local_18,param_2[2],&local_88);
        if (iVar1 < 0) {
          iVar2 = FUN_10761348(&DAT_11858c08,0x800101);
          if (iVar2 == 0) {
            return iVar1;
          }
          if (PTR_FUN_11e454ac == (undefined *)0x0) {
            return iVar1;
          }
          if ((iVar1 < 1) && (-0x13 < iVar1)) {
            iVar2 = -iVar1;
          }
          else {
            iVar2 = 0x13;
          }
          (*(code *)PTR_FUN_11e454ac)
                    ("OAM(unit %d) Error: Opcode profile set failed for EP=%d  %s.\n",local_18,
                     param_2[4],(&PTR_DAT_11e43a78)[iVar2]);
          return iVar1;
        }
      }
      local_84 = &local_88;
      FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x25733c),0xffffffff);
      iVar1 = FUN_10ef40b4(local_18,local_28[0] + 0x4c,&local_84,1,&local_80);
      if (iVar1 < 0) {
        iVar2 = FUN_10761348(&DAT_11858c08,0x800101);
        if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
          if ((iVar1 < 1) && (-0x13 < iVar1)) {
            iVar2 = -iVar1;
          }
          else {
            iVar2 = 0x13;
          }
          (*(code *)PTR_FUN_11e454ac)
                    ("OAM(unit %d) Error: Opcode profile add failed for EP=%d  %s.\n",local_18,
                     param_2[4],(&PTR_DAT_11e43a78)[iVar2]);
        }
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x25733c));
      }
      else {
        FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + 0x25733c));
        *(undefined4 *)(iVar2 + 0x38) = local_80;
        memset(auStack_90,0,8);
        FUN_107a2a0c(local_18,0x916,auStack_90,0x8160,param_2[6]);
        FUN_107a2a0c(local_18,0x916,auStack_90,0x8f27,*(undefined4 *)(iVar2 + 0x38));
        if ((param_2[2] & 2) != 0) {
          FUN_107a2a0c(local_18,0x916,auStack_90,0x6524,*(undefined1 *)(param_2 + 0x1e));
        }
        iVar1 = FUN_108080ac(local_18,0x916,0xffffffff,*(undefined4 *)(iVar2 + 0x40),auStack_90);
        if (iVar1 < 0) {
          iVar2 = FUN_10761348(&DAT_11858c08,0x800101);
          if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
            if ((iVar1 < 1) && (-0x13 < iVar1)) {
              iVar2 = -iVar1;
            }
            else {
              iVar2 = 0x13;
            }
            (*(code *)PTR_FUN_11e454ac)
                      ("OAM(unit %d) Error: MA_INDEX table write failed for EP=%d  %s.\n",local_18,
                       param_2[4],(&PTR_DAT_11e43a78)[iVar2]);
          }
        }
        else {
          FUN_10ebaa88(local_18);
          memset(auStack_7c,0,0x50);
          iVar1 = FUN_10e043e0(local_18,iVar2,&local_2c,auStack_7c);
          if (iVar1 < 0) {
            memset(auStack_7c,0,0x50);
            FUN_107a2a0c(local_18,0x822,auStack_7c,0x78aa,1 << (param_2[9] & 0x3f));
            FUN_107a2a0c(local_18,0x822,auStack_7c,0x78a9,*(int *)(iVar2 + 0x40) >> 3);
            if ((*param_2 & 0x400000) == 0) {
              FUN_107a2a0c(local_18,0x822,auStack_7c,0x78a2,2);
              FUN_107a2a0c(local_18,0x822,auStack_7c,0x78a3,3);
            }
            else {
              FUN_107a2a0c(local_18,0x822,auStack_7c,0x78a2,1);
              FUN_107a2a0c(local_18,0x822,auStack_7c,0x78a3,1);
            }
            FUN_10e00f8c(local_18,iVar2,auStack_7c);
            FUN_107a2a0c(local_18,0x822,auStack_7c,0xe37e,1);
            iVar1 = FUN_10819de8(local_18,0x822,0xffffffff,auStack_7c);
            if (iVar1 < 0) {
              iVar2 = FUN_10761348(&DAT_11858c08,0x800101);
              if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                if ((iVar1 < 1) && (-0x13 < iVar1)) {
                  iVar2 = -iVar1;
                }
                else {
                  iVar2 = 0x13;
                }
                (*(code *)PTR_FUN_11e454ac)
                          ("OAM(unit %d) Error: L3_ENTRY table insert failed for EP=%d  %s.\n",
                           local_18,param_2[4],(&PTR_DAT_11e43a78)[iVar2]);
              }
              FUN_10ebab1c(local_18);
              return iVar1;
            }
          }
          else {
            bVar3 = FUN_107a2924(local_18,0x822,auStack_7c,0x78aa);
            iVar1 = FUN_107a39b8(local_18,0x822,local_2c,0x78aa,
                                 (byte)(1 << (param_2[9] & 0x3f)) | bVar3);
            if (iVar1 < 0) {
              iVar2 = FUN_10761348(&DAT_11858c08,0x800101);
              if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                if ((iVar1 < 1) && (-0x13 < iVar1)) {
                  iVar2 = -iVar1;
                }
                else {
                  iVar2 = 0x13;
                }
                (*(code *)PTR_FUN_11e454ac)
                          ("OAM(unit %d) Error: L3_ENTRY table update failed for EP=%d  %s.\n",
                           local_18,param_2[4],(&PTR_DAT_11e43a78)[iVar2]);
              }
              FUN_10ebab1c(local_18);
              return iVar1;
            }
          }
          FUN_10ebab1c(local_18);
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}



