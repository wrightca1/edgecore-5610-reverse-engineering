/* Wrapper-function decompilation */

/* === FUN_10ef2a58 (size=1576) === */

int FUN_10ef2a58(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
                ,int *param_8)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  int local_48;
  int local_44;
  
  if (param_8 == (int *)0x0) {
    iVar2 = -0x11;
  }
  else if (((param_2 == 0) || (param_3 == 0)) || (param_7 == 0)) {
    iVar2 = -4;
  }
  else {
    if (*param_8 != 0) {
      FUN_10ef2950(param_8);
    }
    iVar2 = FUN_11310fbc(param_7 * 0x1c,"Profile Mem Tables");
    *param_8 = iVar2;
    if (*param_8 == 0) {
      iVar2 = -2;
    }
    else {
      memset((void *)*param_8,0,param_7 * 0x1c);
      param_8[1] = param_7;
      for (local_48 = 0; local_48 < param_7; local_48 = local_48 + 1) {
        piVar5 = (int *)(*param_8 + local_48 * 0x1c);
        *piVar5 = *(int *)(param_2 + local_48 * 4);
        if (param_4 == 0) {
          piVar5[1] = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) +
                                                0x24) + *piVar5 * 4) + 0xc);
        }
        else {
          piVar5[1] = *(int *)(param_4 + local_48 * 4);
        }
        if (param_5 == 0) {
          piVar5[2] = *(int *)((&DAT_1212ba0c)[param_1] + *piVar5 * 0xec + 0x31bc);
        }
        else {
          piVar5[2] = *(int *)(param_5 + local_48 * 4);
        }
        if (piVar5[2] <= piVar5[1]) {
          FUN_10ef2950(param_8);
          return -4;
        }
        piVar5[3] = *(int *)(param_3 + local_48 * 4);
        if ((param_6 != 0) && (*(int *)(param_6 + local_48 * 4) != 0)) {
          iVar2 = piVar5[3];
          iVar3 = FUN_11310fbc(iVar2 << 2,"Profile Mem Data Mask");
          piVar5[4] = iVar3;
          if (piVar5[4] == 0) {
            FUN_10ef2950(param_8);
            return -2;
          }
          memset((void *)piVar5[4],0,iVar2 << 2);
          iVar2 = *(int *)(param_6 + local_48 * 4);
          for (local_44 = 0; local_44 < piVar5[3]; local_44 = local_44 + 1) {
            *(undefined4 *)(piVar5[4] + local_44 * 4) = *(undefined4 *)(iVar2 + local_44 * 4);
          }
        }
        iVar3 = (piVar5[2] - piVar5[1]) + 1;
        sVar1 = iVar3 * 8;
        iVar2 = FUN_11310fbc(sVar1,"Profile Mem Entries");
        piVar5[5] = iVar2;
        if (piVar5[5] == 0) {
          FUN_10ef2950(param_8);
          return -2;
        }
        memset((void *)piVar5[5],0,sVar1);
        sVar1 = piVar5[3] * iVar3 * 4;
        iVar2 = FUN_11310fbc(sVar1,"Profile Mem Cache");
        piVar5[6] = iVar2;
        if (piVar5[6] == 0) {
          FUN_10ef2950(param_8);
          return -2;
        }
        memset((void *)piVar5[6],0,sVar1);
      }
      if (*(int *)(&DAT_1212ba54 + param_1 * 4) == 1) {
        for (local_48 = 0; local_48 < param_8[1]; local_48 = local_48 + 1) {
          puVar6 = (undefined4 *)(*param_8 + local_48 * 0x1c);
          iVar2 = puVar6[2];
          iVar3 = puVar6[1];
          for (local_44 = 0; local_44 < (iVar2 - iVar3) + 1; local_44 = local_44 + 1) {
            iVar4 = FUN_10801b4c(param_1,*puVar6,0xffffffff,puVar6[1] + local_44,
                                 puVar6[6] + puVar6[3] * local_44 * 4);
            if (iVar4 < 0) {
              FUN_10ef2950(param_8);
              return iVar4;
            }
          }
        }
      }
      else {
        for (local_48 = 0; local_48 < param_8[1]; local_48 = local_48 + 1) {
          iVar2 = FUN_108092ec(param_1,*(undefined4 *)(*param_8 + local_48 * 0x1c),0xffffffff,1);
          if (iVar2 < 0) {
            FUN_10ef2950(param_8);
            return iVar2;
          }
        }
      }
      iVar2 = 0;
    }
  }
  return iVar2;
}



/* === FUN_10ef40b4 (size=3820) === */

int FUN_10ef40b4(int param_1,int *param_2,int param_3,int param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  void *__s;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  size_t __n;
  void *__dest;
  int *piVar10;
  int local_138;
  int local_134;
  int local_130;
  int local_12c;
  int local_128;
  int local_124;
  void *local_120;
  void *local_11c;
  uint auStack_d4 [20];
  undefined1 auStack_84 [92];
  int local_28;
  int *local_24;
  int local_20;
  int local_1c;
  int *local_18;
  
  local_124 = 0;
  if ((((param_2 == (int *)0x0) || (param_3 == 0)) || (param_4 < 1)) || (param_5 == (int *)0x0)) {
    iVar4 = -4;
  }
  else if ((*param_2 == 0) || (param_2[1] == 0)) {
    iVar4 = -0x11;
  }
  else {
    iVar4 = (*(int *)(*param_2 + 8) - *(int *)(*param_2 + 4)) + 1;
    if (iVar4 == (iVar4 / param_4) * param_4) {
      iVar4 = iVar4 / param_4;
      for (local_134 = 0; local_134 < param_2[1]; local_134 = local_134 + 1) {
        iVar5 = *param_2 + local_134 * 0x1c;
        iVar5 = (*(int *)(iVar5 + 8) - *(int *)(iVar5 + 4)) + 1;
        if (*(int *)(param_3 + local_134 * 4) == 0) {
          return -4;
        }
        if (iVar5 != (iVar5 / iVar4) * iVar4) {
          return -4;
        }
      }
      local_28 = param_1;
      local_24 = param_2;
      local_20 = param_3;
      local_1c = param_4;
      local_18 = param_5;
      memset(auStack_84,0xff,0x50);
      local_128 = -1;
      for (local_138 = 0; local_138 < iVar4; local_138 = local_138 + 1) {
        iVar5 = local_138 * local_1c;
        if (*(int *)(*(int *)(*local_24 + 0x14) + iVar5 * 8) == 0) {
          if ((local_128 == -1) && ((local_128 = local_138, local_24[1] != 1 || (local_1c != 1)))) {
            for (local_134 = 0; local_134 < local_24[1]; local_134 = local_134 + 1) {
              iVar2 = *local_24 + local_134 * 0x1c;
              iVar5 = ((*(int *)(iVar2 + 8) - *(int *)(iVar2 + 4)) + 1) / iVar4;
              for (local_130 = 0; local_130 < iVar5; local_130 = local_130 + 1) {
                if (*(int *)(*(int *)(iVar2 + 0x14) + (local_138 * iVar5 + local_130) * 8) != 0) {
                  local_128 = -1;
                  break;
                }
              }
              if (local_128 == -1) break;
            }
            if (((local_24[2] & 1U) != 0) && (-1 < local_128)) break;
          }
        }
        else if (((local_24[2] & 1U) == 0) &&
                (*(int *)(*(int *)(*local_24 + 0x14) + iVar5 * 8 + 4) == local_1c)) {
          for (local_134 = 0; local_134 < local_24[1]; local_134 = local_134 + 1) {
            piVar8 = (int *)(*local_24 + local_134 * 0x1c);
            iVar2 = ((piVar8[2] - piVar8[1]) + 1) / iVar4;
            iVar7 = piVar8[3];
            iVar1 = (int)(*(ushort *)
                           (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24)
                                    + *piVar8 * 4) + 0x28) + 3) >> 2;
            local_11c = *(void **)(local_20 + local_134 * 4);
            local_120 = (void *)(piVar8[6] + local_138 * iVar2 * iVar7 * 4);
            if (piVar8[4] == 0) {
              puVar6 = auStack_84;
            }
            else {
              puVar6 = (undefined1 *)piVar8[4];
            }
            for (local_130 = 0; local_130 < iVar2; local_130 = local_130 + 1) {
              local_12c = 0;
              while ((local_12c < iVar1 &&
                     (((*(uint *)((int)local_120 + local_12c * 4) ^
                       *(uint *)((int)local_11c + local_12c * 4)) &
                      *(uint *)(puVar6 + local_12c * 4)) == 0))) {
                local_12c = local_12c + 1;
              }
              if (local_12c < iVar1) break;
              local_11c = (void *)((int)local_11c + iVar7 * 4);
              local_120 = (void *)((int)local_120 + iVar7 * 4);
            }
            if (local_130 != iVar2) break;
          }
          if (local_24[1] == local_134) {
            iVar2 = FUN_10ef3144(local_28,local_24,iVar5);
            if (iVar2 < 0) {
              return iVar2;
            }
            for (local_134 = 0; local_134 < local_24[1]; local_134 = local_134 + 1) {
              iVar7 = *local_24 + local_134 * 0x1c;
              iVar2 = ((*(int *)(iVar7 + 8) - *(int *)(iVar7 + 4)) + 1) / iVar4;
              for (local_130 = 0; local_130 < iVar2; local_130 = local_130 + 1) {
                piVar8 = (int *)(*(int *)(iVar7 + 0x14) + (local_138 * iVar2 + local_130) * 8);
                *piVar8 = *piVar8 + 1;
              }
            }
            *local_18 = *(int *)(*local_24 + 4) + iVar5;
            return 0;
          }
        }
      }
      if (local_128 == -1) {
        iVar4 = -0xe;
      }
      else {
        for (local_134 = 0; local_134 < local_24[1]; local_134 = local_134 + 1) {
          piVar8 = (int *)(*local_24 + local_134 * 0x1c);
          iVar2 = piVar8[1];
          iVar5 = ((piVar8[2] - piVar8[1]) + 1) / iVar4;
          iVar9 = local_128 * iVar5;
          iVar7 = piVar8[3];
          iVar1 = (int)(*(ushort *)
                         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x24) +
                                  *piVar8 * 4) + 0x28) + 3) >> 2;
          local_11c = *(void **)(local_20 + local_134 * 4);
          local_120 = (void *)(piVar8[6] + iVar9 * iVar7 * 4);
          if (iVar5 < 8) {
            for (local_130 = 0; local_130 < iVar5; local_130 = local_130 + 1) {
              if (piVar8[4] == 0) {
                iVar3 = FUN_108080ac(local_28,*piVar8,0xffffffff,iVar2 + iVar9 + local_130,local_11c
                                    );
              }
              else {
                iVar3 = FUN_10801b4c(local_28,*piVar8,0xffffffff,iVar2 + iVar9 + local_130,
                                     auStack_d4);
                if (iVar3 < 0) {
                  return iVar3;
                }
                for (local_12c = 0; local_12c < iVar1; local_12c = local_12c + 1) {
                  auStack_d4[local_12c] =
                       auStack_d4[local_12c] & ~*(uint *)(piVar8[4] + local_12c * 4);
                  auStack_d4[local_12c] =
                       auStack_d4[local_12c] |
                       *(uint *)((int)local_11c + local_12c * 4) &
                       *(uint *)(piVar8[4] + local_12c * 4);
                }
                iVar3 = FUN_108080ac(local_28,*piVar8,0xffffffff,iVar2 + iVar9 + local_130,
                                     auStack_d4);
              }
              if (iVar3 < 0) {
                return iVar3;
              }
              memcpy(local_120,local_11c,iVar1 << 2);
              local_11c = (void *)((int)local_11c + iVar7 * 4);
              local_120 = (void *)((int)local_120 + iVar7 * 4);
              piVar10 = (int *)(piVar8[5] + (iVar9 + local_130) * 8);
              *piVar10 = *piVar10 + 1;
              *(int *)(piVar8[5] + (iVar9 + local_130) * 8 + 4) = iVar5;
            }
          }
          else {
            __n = iVar7 * 4 * iVar5;
            __s = (void *)FUN_1075fcd4(local_28,__n,"profile update");
            if (__s == (void *)0x0) {
              return -2;
            }
            memset(__s,0,__n);
            if (piVar8[4] != 0) {
              local_124 = FUN_108020c0(local_28,*piVar8,0xffffffff,iVar2 + iVar9,
                                       iVar2 + iVar9 + iVar5 + -1,__s);
            }
            if (-1 < local_124) {
              for (local_130 = 0; local_130 < iVar5; local_130 = local_130 + 1) {
                __dest = (void *)((int)__s +
                                 ((int)(*(ushort *)
                                         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] +
                                                                    0x2f26f4) + 0x24) + *piVar8 * 4)
                                         + 0x28) + 3) >> 2) * local_130 * 4);
                if (piVar8[4] == 0) {
                  memcpy(__dest,local_11c,iVar1 << 2);
                }
                else {
                  for (local_12c = 0; local_12c < iVar1; local_12c = local_12c + 1) {
                    *(uint *)((int)__dest + local_12c * 4) =
                         *(uint *)((int)__dest + local_12c * 4) &
                         ~*(uint *)(piVar8[4] + local_12c * 4);
                    *(uint *)((int)__dest + local_12c * 4) =
                         *(uint *)((int)__dest + local_12c * 4) |
                         *(uint *)((int)local_11c + local_12c * 4) &
                         *(uint *)(piVar8[4] + local_12c * 4);
                  }
                }
                local_11c = (void *)((int)local_11c + iVar7 * 4);
              }
            }
            if (-1 < local_124) {
              local_124 = FUN_10808740(local_28,*piVar8,0xffffffff,iVar2 + iVar9,
                                       iVar2 + iVar9 + iVar5 + -1,__s);
            }
            if (-1 < local_124) {
              local_11c = *(void **)(local_20 + local_134 * 4);
              for (local_130 = 0; local_130 < iVar5; local_130 = local_130 + 1) {
                memcpy(local_120,local_11c,iVar1 << 2);
                local_11c = (void *)((int)local_11c + iVar7 * 4);
                local_120 = (void *)((int)local_120 + iVar7 * 4);
                piVar10 = (int *)(piVar8[5] + (iVar9 + local_130) * 8);
                *piVar10 = *piVar10 + 1;
                *(int *)(piVar8[5] + (iVar9 + local_130) * 8 + 4) = iVar5;
              }
            }
            FUN_1075ffa4(local_28,__s);
            if (local_124 < 0) {
              return local_124;
            }
          }
        }
        *local_18 = local_128 * local_1c + *(int *)(*local_24 + 4);
        iVar4 = 0;
      }
    }
    else {
      iVar4 = -4;
    }
  }
  return iVar4;
}



/* === FUN_10ef6af4 (size=1224) === */

int FUN_10ef6af4(int param_1,int *param_2,int param_3,int *param_4)

{
  undefined8 uVar1;
  int iVar2;
  size_t __n;
  int iVar3;
  int local_48;
  int local_44;
  int local_40;
  undefined4 local_28;
  undefined4 uStack_24;
  
  if (param_4 == (int *)0x0) {
    iVar3 = -0x11;
  }
  else if ((param_2 == (int *)0x0) || (param_3 == 0)) {
    iVar3 = -4;
  }
  else {
    iVar3 = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                             *param_2 * 4) + 8);
    if (iVar3 < 1) {
      iVar3 = -0xd;
    }
    else {
      for (local_48 = 1; local_48 < param_3; local_48 = local_48 + 1) {
        if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                             *param_2 * 4) + 8) != iVar3) {
          return -4;
        }
      }
      __n = (param_3 * 8 + 0xc) * iVar3 + param_3 * 4;
      if (*param_4 == 0) {
        iVar2 = FUN_11310fbc(__n,"Profile Reg Entries");
        param_4[2] = iVar2;
        if (param_4[2] == 0) {
          return -2;
        }
      }
      else if (param_4[2] == 0) {
        return -1;
      }
      memset((void *)param_4[2],0,__n);
      local_40 = param_4[2] + iVar3 * 0xc;
      for (local_44 = 0; local_44 < iVar3; local_44 = local_44 + 1) {
        *(int *)(param_4[2] + local_44 * 0xc + 8) = local_40;
        local_40 = local_40 + param_3 * 8;
      }
      *param_4 = local_40;
      for (local_48 = 0; local_48 < param_3; local_48 = local_48 + 1) {
        *(int *)(*param_4 + local_48 * 4) = param_2[local_48];
      }
      param_4[1] = param_3;
      uVar1 = DAT_11413488;
      if (*(int *)(&DAT_1212ba54 + param_1 * 4) == 1) {
        for (local_44 = 0; local_44 < iVar3; local_44 = local_44 + 1) {
          local_40 = *(int *)(param_4[2] + local_44 * 0xc + 8);
          for (local_48 = 0; local_48 < param_4[1]; local_48 = local_48 + 1) {
            iVar2 = FUN_10845c00(param_1,*(undefined4 *)(*param_4 + local_48 * 4),0xfffffff6,
                                 local_44,local_40);
            if (iVar2 < 0) {
              FUN_11310ee4(param_4[2]);
              *param_4 = 0;
              param_4[2] = 0;
              return iVar2;
            }
            local_40 = local_40 + 8;
          }
        }
      }
      else {
        for (local_44 = 0; local_44 < iVar3; local_44 = local_44 + 1) {
          for (local_48 = 0; local_48 < param_4[1]; local_48 = local_48 + 1) {
            local_28 = (undefined4)((ulonglong)uVar1 >> 0x20);
            uStack_24 = (undefined4)uVar1;
            iVar2 = FUN_10848590(param_1,*(undefined4 *)(*param_4 + local_48 * 4),0xfffffff6,
                                 local_44,local_28,uStack_24);
            if (iVar2 < 0) {
              FUN_11310ee4(param_4[2]);
              *param_4 = 0;
              param_4[2] = 0;
              return iVar2;
            }
          }
        }
      }
      iVar3 = 0;
    }
  }
  return iVar3;
}



/* === FUN_10846cf4 (size=544) === */
/* Referenced strings: */
/*   !SOC_REG_IS_ABOVE_32(unit, reg) */
/*   DMA CH2 */


undefined4
FUN_10846cf4(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

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
     (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
  {
    uVar1 = 0xfffffffc;
  }
  else {
    local_28 = param_1;
    local_24 = param_2;
    local_20 = param_3;
    local_1c = param_4;
    local_18 = param_5;
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                           param_2 * 4) + 0x10) & 0x100001) != 0) {
      FUN_10760b7c("reg %s is > 32 bit , but called with soc_reg32_get\n",
                   (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[param_2]);
    }
    if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                           local_24 * 4) + 0x10) & 0x100001) != 0) {
      FUN_113113b0("!SOC_REG_IS_ABOVE_32(unit, reg)",
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                   ,0x4a4);
    }
    uVar1 = FUN_1084faec(local_28,local_24,local_20,local_1c,&local_34,local_30);
    if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
      uVar1 = FUN_10846590(local_28,uVar1,local_18);
    }
    else {
      uVar1 = FUN_10845768(local_28,local_34,local_30[0],uVar1,local_18);
    }
  }
  return uVar1;
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



/* === FUN_1084c7bc (size=1264) === */
/* Referenced strings: */
/*   !VALUE_TOO_BIG_FOR_FIELD */
/*   DATA_RAM97 */
/*   DMA CH2 */
/*   SOC_REG_IS_VALID(unit, reg) */
/*   finfop */


void FUN_1084c7bc(int param_1,int param_2,uint *param_3,int param_4,uint param_5)

{
  uint uVar1;
  int *local_48;
  uint local_44;
  int *local_40;
  int *local_3c;
  int *local_38;
  
  if ((((param_2 < 0) || (0x901f < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
     && (((FUN_10760b7c("reg %s is invalid\n",
                        (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[param_2]), param_2 < 0 ||
          (0x901f < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) ==
          0)))) {
    FUN_113113b0("SOC_REG_IS_VALID(unit, reg)",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xa28);
  }
  local_48 = (int *)0x0;
  local_40 = *(int **)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                               param_2 * 4) + 0x18);
  local_38 = local_40;
  if ((*local_40 != param_4) &&
     (local_38 = local_40 +
                 (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
                                   param_2 * 4) + 0x14) + -1) * 3, *local_38 != param_4)) {
    uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x18) +
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
    FUN_10760b7c("reg %s field %s is invalid\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[param_2],
                 (&PTR_DAT_11d332ec)[param_4]);
    FUN_113113b0("finfop",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xa34);
  }
  if (*(ushort *)(local_48 + 1) < 0x20) {
    local_44 = (1 << (*(ushort *)(local_48 + 1) & 0x3f)) - 1;
    if (((~local_44 & param_5) != 0) &&
       (FUN_10760b7c("reg %s field %s is too big\n",
                     (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[param_2],
                     (&PTR_DAT_11d332ec)[param_4]), (~local_44 & param_5) != 0)) {
      FUN_113113b0("!VALUE_TOO_BIG_FOR_FIELD",
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
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



/* === FUN_108499c4 (size=512) === */
/* Referenced strings: */
/*   !SOC_REG_IS_ABOVE_32(unit, reg) */
/*   DATA_RAM97 */
/*   DMA CH2 */


undefined4
FUN_108499c4(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

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
  uVar1 = FUN_1084faec(param_1,param_2,param_3,param_4,&local_34,local_30);
  if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                         local_24 * 4) + 0x10) & 0x100001) != 0) {
    FUN_10760b7c("reg %s is not 32 bit\n",
                 (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[local_24]);
  }
  if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_28] + 0x2f26f4) + 0x18) +
                         local_24 * 4) + 0x10) & 0x100001) != 0) {
    FUN_113113b0("!SOC_REG_IS_ABOVE_32(unit, reg)",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0x7cb);
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c3c) & 0x8000) != 0) {
    FUN_108647ec(local_28,local_24,local_20,local_1c,local_18);
  }
  if ((*(uint *)((&DAT_1212b9c4)[local_28] + 0x2f2c24) & 0x2000000) == 0) {
    uVar1 = FUN_108495c4(local_28,uVar1,local_18);
  }
  else {
    uVar1 = FUN_10848458(local_28,local_34,local_30[0],uVar1,local_18);
  }
  return uVar1;
}



/* === FUN_10c764e4 (size=432) === */

int FUN_10c764e4(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int local_78;
  uint local_74;
  undefined1 auStack_68 [64];
  undefined1 auStack_28 [4];
  int local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  int local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_18 = param_1;
  local_14 = param_2;
  memset(auStack_68,0,0x40);
  memset(auStack_28,0,4);
  for (local_74 = 0; (int)local_74 < 2; local_74 = local_74 + 1) {
    for (local_78 = 0; local_78 < 8; local_78 = local_78 + 1) {
      uVar2 = local_78 << 1 | local_74;
      FUN_107a2a0c(local_18,0x6d7,auStack_68 + uVar2 * 4,0xa50d,local_78);
      FUN_107a2a0c(local_18,0x6d7,auStack_68 + uVar2 * 4,0x1b18,local_74);
    }
  }
  local_20 = auStack_68;
  local_1c = auStack_28;
  iVar1 = FUN_10ef40b4(local_18,local_14,&local_20,0x10,&local_24);
  if (-1 < iVar1) {
    if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) + 0x1b5c)
                + 0xc) == local_24) {
      iVar1 = 0;
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
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



