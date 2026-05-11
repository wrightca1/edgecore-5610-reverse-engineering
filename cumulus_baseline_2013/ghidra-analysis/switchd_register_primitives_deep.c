/* Even deeper register/ioctl primitives */

/* === FUN_108508ac @ 0x108508ac (size=8596) === */

uint FUN_108508ac(int param_1,int param_2,uint param_3,uint param_4,undefined4 *param_5,
                 byte *param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint local_58;
  int local_54;
  uint local_50;
  int local_4c;
  uint local_48;
  int local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_20;
  uint local_1c;
  
  local_54 = -1;
  local_50 = 0xffffffff;
  local_3c = 0;
  if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c24) & 0x2000000) == 0) {
    uVar1 = FUN_1084f070(param_1,param_2,param_3,param_4);
    return uVar1;
  }
  if ((((param_2 < 0) || (0x901f < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) == 0))
     && (((FUN_1076193c("reg %s is invalid\n",
                        (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14)[param_2]), param_2 < 0 ||
          (0x901f < param_2)) ||
         (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) ==
          0)))) {
    FUN_11312544("SOC_REG_IS_VALID(unit, reg)",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xd3d);
  }
  *param_6 = (byte)(*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18
                                               ) + param_2 * 4) + 0x10) >> 0x11) & 7;
  iVar3 = *(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48);
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  *param_5 = 0;
  local_20 = param_3;
  if (param_3 != 0xfffffff6) {
    local_3c = param_3 & 0x80000000;
    local_20 = param_3 & 0x7fffffff;
  }
  piVar4 = (int *)**(undefined4 **)
                    (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4);
  if ((local_3c == 0) && (-1 < (int)local_20)) {
    iVar2 = bcm_mirror_ingress_get(piVar4,0x61);
    if (iVar2 == 0) {
      local_50 = 0xffffffff;
      local_54 = -1;
    }
    else {
      if ((((int)local_20 < 0) || (0x81 < (int)local_20)) ||
         (*(int *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x1c84) * 4 + 4) == 0)) {
        FUN_11312544("SOC_PORT_VALID(unit, port)",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                     ,0xd5d);
      }
      if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c38) & 0x200000) == 0) {
        local_48 = local_20;
      }
      else {
        local_48 = *(uint *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x2114) * 4 + 0xc);
      }
      for (local_44 = 0; local_44 < iVar3; local_44 = local_44 + 1) {
        if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
          iVar2 = local_48 << 3;
        }
        else {
          iVar2 = (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_48 +
                  local_44) * 8;
        }
        local_54 = *(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) + iVar2);
        if (local_54 < 0) break;
        iVar2 = bcm_mirror_ingress_get
                          (piVar4,*(undefined4 *)
                                   (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) +
                                   local_54 * 0x10));
        if (iVar2 != 0) {
          if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
            iVar3 = local_48 << 3;
          }
          else {
            iVar3 = (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_48 +
                    local_44) * 8;
          }
          local_50 = *(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) +
                               iVar3 + 4);
          break;
        }
      }
    }
  }
  else if (local_20 == 0xfffffff6) {
    local_50 = 0xffffffff;
    local_54 = -1;
    iVar2 = bcm_mirror_ingress_get(piVar4,0x61);
    if (iVar2 == 0) {
      local_20 = *(uint *)((&DAT_1212d2dc)[param_1] + 0x5154);
      while (((-1 < (int)local_20 && ((int)local_20 <= *(int *)((&DAT_1212d2dc)[param_1] + 0x5158)))
             && ((*(uint *)((&DAT_1212d2dc)[param_1] +
                            (((int)local_20 >> 5) +
                             (uint)((int)local_20 < 0 && (local_20 & 0x1f) != 0) + 0x1454) * 4 + 0xc
                           ) &
                 1 << (local_20 +
                       (((int)local_20 >> 5) + (uint)((int)local_20 < 0 && (local_20 & 0x1f) != 0))
                       * -0x20 & 0x3f)) == 0))) {
        local_20 = local_20 + 1;
      }
    }
    else {
      for (local_20 = *(uint *)((&DAT_1212d2dc)[param_1] + 0x5154);
          (-1 < (int)local_20 && ((int)local_20 <= *(int *)((&DAT_1212d2dc)[param_1] + 0x5158)));
          local_20 = local_20 + 1) {
        if ((*(uint *)((&DAT_1212d2dc)[param_1] +
                       (((int)local_20 >> 5) + (uint)((int)local_20 < 0 && (local_20 & 0x1f) != 0) +
                       0x1454) * 4 + 0xc) &
            1 << (local_20 +
                  (((int)local_20 >> 5) + (uint)((int)local_20 < 0 && (local_20 & 0x1f) != 0)) *
                  -0x20 & 0x3f)) != 0) {
          if ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c38) & 0x200000) == 0) {
            local_48 = local_20;
          }
          else {
            local_48 = *(uint *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x2114) * 4 + 0xc);
          }
          for (local_44 = 0; local_44 < iVar3; local_44 = local_44 + 1) {
            if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
              iVar2 = local_48 << 3;
            }
            else {
              iVar2 = (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_48 +
                      local_44) * 8;
            }
            local_54 = *(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) +
                               iVar2);
            if (local_54 < 0) break;
            iVar2 = bcm_mirror_ingress_get
                              (piVar4,*(undefined4 *)
                                       (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) +
                                                0x30) + local_54 * 0x10));
            if (iVar2 != 0) {
              if (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) < 2) {
                iVar2 = local_48 << 3;
              }
              else {
                iVar2 = (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x48) * local_48 +
                        local_44) * 8;
              }
              local_50 = *(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x34) +
                                   iVar2 + 4);
              break;
            }
          }
          if ((local_44 != iVar3) && (-1 < local_54)) break;
        }
      }
      if (local_54 < 0) {
        FUN_11312544("SOC_REG_ADDR_INVALID_PORT",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                     ,0xda2);
      }
    }
  }
  else {
    local_20 = local_20 & 0x7fffffff;
    local_50 = 0xffffffff;
    local_54 = -1;
  }
  if (((local_20 == 0xfffffff6) || (local_3c != 0)) ||
     (iVar3 = bcm_mirror_ingress_get(piVar4,0x61), iVar3 == 0)) {
    local_38 = local_20;
    if (local_20 == 0xfffffff6) {
      local_38 = 0;
    }
    iVar3 = *piVar4;
    if (iVar3 != 0x59) {
      if (iVar3 < 0x5a) {
        if (iVar3 == 0x2e) {
          local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c4c);
          goto LAB_10852370;
        }
        if (iVar3 < 0x2f) {
          if (iVar3 == 0x13) {
            local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bcc);
            goto LAB_10852370;
          }
          if (iVar3 < 0x14) {
            if (iVar3 == 0xd) {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bb4);
              goto LAB_10852370;
            }
            if (iVar3 < 0xe) {
              if (iVar3 == 8) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ba8);
                goto LAB_10852370;
              }
              if (iVar3 < 9) {
                if (iVar3 == 6) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ba4);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 9) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bac);
                  goto LAB_10852370;
                }
                if (iVar3 == 10) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bb0);
                  goto LAB_10852370;
                }
              }
            }
            else {
              if (iVar3 == 0x10) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bc0);
                goto LAB_10852370;
              }
              if (iVar3 < 0x11) {
                if (iVar3 == 0xe) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bb8);
                  goto LAB_10852370;
                }
                if (iVar3 == 0xf) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bbc);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x11) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bc4);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x12) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bc8);
                  goto LAB_10852370;
                }
              }
            }
          }
          else {
            if (iVar3 == 0x20) {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bdc);
              goto LAB_10852370;
            }
            if (iVar3 < 0x21) {
              if (iVar3 == 0x16) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bd8);
                goto LAB_10852370;
              }
              if (iVar3 < 0x17) {
                if (iVar3 == 0x14) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bd0);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x15) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5bd4);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x1a) goto LAB_10852370;
                if (iVar3 == 0x1f) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5be0);
                  goto LAB_10852370;
                }
              }
            }
            else {
              if (iVar3 == 0x27) {
                if (local_3c == 0) {
                  local_40 = *(uint *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x1914) * 4 + 0xc);
                }
                else {
                  local_40 = local_20;
                }
                if (((int)local_40 < 0) || (7 < (int)local_40)) {
                  local_54 = -1;
                }
                else {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_40 + 0x16f8) * 4 + 4);
                }
                goto LAB_10852370;
              }
              if (iVar3 < 0x28) {
                if (iVar3 == 0x25) {
                  if (((int)local_20 < 0) || (1 < (int)local_20)) {
                    local_54 = -1;
                  }
                  else {
                    local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x1700) * 4 + 4);
                  }
                  goto LAB_10852370;
                }
                if (iVar3 == 0x26) {
                  if (((int)local_20 < 0) || (1 < (int)local_20)) {
                    local_54 = -1;
                  }
                  else {
                    local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x1700) * 4 + 0xc);
                  }
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x2c) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c44);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2d) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c48);
                  goto LAB_10852370;
                }
              }
            }
          }
        }
        else {
          if (iVar3 == 0x4d) goto LAB_10852370;
          if (iVar3 < 0x4e) {
            if (iVar3 == 0x33) {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c64);
              goto LAB_10852370;
            }
            if (iVar3 < 0x34) {
              if (iVar3 == 0x30) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c54);
                goto LAB_10852370;
              }
              if (iVar3 < 0x30) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c50);
                goto LAB_10852370;
              }
              if (iVar3 == 0x31) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c5c);
                goto LAB_10852370;
              }
              if (iVar3 == 0x32) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c60);
                goto LAB_10852370;
              }
            }
            else {
              if (iVar3 == 0x38) goto LAB_10852370;
              if (iVar3 < 0x39) {
                if ((iVar3 == 0x34) || (iVar3 == 0x37)) goto LAB_10852370;
              }
              else if ((iVar3 == 0x39) || (iVar3 == 0x4c)) goto LAB_10852370;
            }
          }
          else {
            if (iVar3 == 0x53) goto LAB_10852370;
            if (iVar3 < 0x54) {
              if (iVar3 == 0x50) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c58);
                goto LAB_10852370;
              }
              if (iVar3 < 0x51) {
                if ((iVar3 == 0x4e) || (iVar3 == 0x4f)) goto LAB_10852370;
              }
              else if ((iVar3 == 0x51) || (iVar3 == 0x52)) goto LAB_10852370;
            }
            else {
              if (iVar3 == 0x56) goto LAB_10852370;
              if (iVar3 < 0x57) {
                if ((iVar3 == 0x54) || (iVar3 == 0x55)) goto LAB_10852370;
              }
              else if ((iVar3 == 0x57) || (iVar3 == 0x58)) goto LAB_10852370;
            }
          }
        }
      }
      else {
        if (iVar3 == 0x2722) {
          local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5e10);
          goto LAB_10852370;
        }
        if (iVar3 < 0x2723) {
          if (iVar3 == 0x2716) {
            local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5de0);
            goto LAB_10852370;
          }
          if (iVar3 < 0x2717) {
            if (iVar3 == 0x5e) goto LAB_10852370;
            if (iVar3 < 0x5f) {
              if ((((iVar3 == 0x5b) || (iVar3 < 0x5b)) || (iVar3 == 0x5c)) || (iVar3 == 0x5d))
              goto LAB_10852370;
            }
            else {
              if (iVar3 == 0x2713) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5dd8);
                goto LAB_10852370;
              }
              if (iVar3 < 0x2714) {
                if (iVar3 == 0x60) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5c6c);
                  goto LAB_10852370;
                }
                if (iVar3 == 10000) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5dcc);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x2714) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ddc);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2715) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5edc);
                  goto LAB_10852370;
                }
              }
            }
          }
          else {
            if (iVar3 == 0x271c) {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5df8);
              goto LAB_10852370;
            }
            if (iVar3 < 0x271d) {
              if (iVar3 == 0x2719) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5dec);
                goto LAB_10852370;
              }
              if (iVar3 < 0x271a) {
                if (iVar3 == 0x2717) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5de4);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2718) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5de8);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x271a) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5df0);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x271b) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5df4);
                  goto LAB_10852370;
                }
              }
            }
            else {
              if (iVar3 == 0x271f) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5e04);
                goto LAB_10852370;
              }
              if (iVar3 < 0x2720) {
                if (iVar3 == 0x271d) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5dfc);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x271e) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5e00);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x2720) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5e08);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2721) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5e0c);
                  goto LAB_10852370;
                }
              }
            }
          }
        }
        else {
          if (iVar3 == 0x2735) {
            if (((int)local_38 < 0) || (7 < (int)local_38)) {
              local_54 = -1;
            }
            else {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_38 + 0x17ac) * 4 + 4);
            }
            goto LAB_10852370;
          }
          if (iVar3 < 0x2736) {
            if (iVar3 == 0x272f) {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5dd4);
              goto LAB_10852370;
            }
            if (iVar3 < 0x2730) {
              if (iVar3 == 0x272c) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ed4);
                goto LAB_10852370;
              }
              if (iVar3 < 0x272d) {
                if (iVar3 == 0x2727) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ea4);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x272a) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5eb0);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x272d) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ed8);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x272e) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5dd0);
                  goto LAB_10852370;
                }
              }
            }
            else {
              if (iVar3 == 0x2732) {
                if (((int)local_38 < 0) || (1 < (int)local_38)) {
                  local_54 = -1;
                }
                else {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_38 + 0x17a4) * 4 + 0xc);
                }
                goto LAB_10852370;
              }
              if (iVar3 < 0x2733) {
                if (iVar3 == 0x2730) {
                  if (((int)local_38 < 0) || (0x1f < (int)local_38)) {
                    local_54 = -1;
                  }
                  else {
                    local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_38 + 0x1784) * 4 + 4);
                  }
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2731) {
                  if (((int)local_38 < 0) || (1 < (int)local_38)) {
                    local_54 = -1;
                  }
                  else {
                    local_54 = *(int *)((&DAT_1212d2dc)[param_1] + (local_38 + 0x17a4) * 4 + 4);
                  }
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x2733) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ea8);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2734) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5eac);
                  goto LAB_10852370;
                }
              }
            }
          }
          else {
            if (iVar3 == 0x273b) {
              local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ef4);
              goto LAB_10852370;
            }
            if (iVar3 < 0x273c) {
              if (iVar3 == 0x2738) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ee8);
                goto LAB_10852370;
              }
              if (iVar3 < 0x2739) {
                if (iVar3 == 0x2736) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ee0);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2737) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ee4);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x2739) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5eec);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x273a) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ef0);
                  goto LAB_10852370;
                }
              }
            }
            else {
              if (iVar3 == 0x273e) {
                local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5f50);
                goto LAB_10852370;
              }
              if (iVar3 < 0x273f) {
                if (iVar3 == 0x273c) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5ef8);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x273d) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5efc);
                  goto LAB_10852370;
                }
              }
              else {
                if (iVar3 == 0x273f) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5f4c);
                  goto LAB_10852370;
                }
                if (iVar3 == 0x2740) {
                  local_54 = *(int *)((&DAT_1212d2dc)[param_1] + 0x5f00);
                  goto LAB_10852370;
                }
              }
            }
          }
        }
      }
      local_54 = -1;
    }
  }
LAB_10852370:
  if (local_54 < 0) {
    FUN_11312544("block >= 0",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xf5f);
  }
  local_4c = 0;
  local_1c = param_4;
  switch(*(undefined4 *)
          (*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) + param_2 * 4) +
          4)) {
  default:
    FUN_11312544(&DAT_113c9740,
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                 ,0xf96);
    break;
  case 1:
    local_4c = 8;
    local_50 = 0;
    break;
  case 2:
  case 3:
    iVar3 = bcm_mirror_ingress_get(piVar4,0x61);
    if ((((iVar3 == 0) && (iVar3 = bcm_mirror_ingress_get(piVar4,0x38), iVar3 == 0)) &&
        (iVar3 = bcm_mirror_ingress_get(piVar4,0x39), iVar3 == 0)) &&
       ((iVar3 = bcm_mirror_ingress_get(piVar4,0x35), iVar3 == 0 &&
        (iVar3 = bcm_mirror_ingress_get(piVar4,0x36), iVar3 == 0)))) {
      if (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c38) & 0x200000) == 0) ||
         (*(int *)((&DAT_1212d2dc)[param_1] + 0x5bac) != local_54)) {
        local_50 = local_20;
      }
      else {
        iVar3 = *(int *)((&DAT_1212d2dc)[param_1] + (local_20 + 0x2114) * 4 + 0xc);
        local_50 = *(uint *)((&DAT_1212d2dc)[param_1] + (iVar3 + 0x2198) * 4 + 4);
        if ((int)local_50 < 0) {
          local_50 = *(uint *)((&DAT_1212d2dc)[param_1] + (iVar3 + 0x2218) * 4 + 0xc);
        }
        if ((int)local_50 < 0) {
          FUN_11312544("pindex >= 0",
                       "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                       ,0xf79);
        }
        if (((*(int *)((&DAT_1212d2dc)[param_1] + 0x10) == 0) &&
            (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x80000) != 0 ||
             ((*(uint *)((&DAT_1212d2dc)[param_1] + 0x14) & 0x40) != 0)))) && (param_2 == 0x616c)) {
          local_50 = local_20;
        }
      }
      local_4c = 8;
    }
    break;
  case 4:
    if (((int)param_4 < 0) ||
       (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x14) <= (int)param_4)) {
      FUN_11312544("index >= 0 && index < NUM_COS(unit)",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                   ,0xf8d);
    }
    local_1c = 0;
    local_50 = param_4;
    break;
  case 5:
  case 9:
  case 10:
    local_54 = -1;
    local_50 = 0;
    local_4c = 2;
  }
  local_58 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                               param_2 * 4) + 0xc);
  FUN_10761a94(0x20010000,"base: %x ",local_58);
  if (-1 < local_54) {
    *param_5 = *(undefined4 *)
                (*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) + local_54 * 0x10 +
                0xc);
  }
  if (local_50 != 0) {
    local_58 = local_58 | local_50;
  }
  if ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                         param_2 * 4) + 0x10) & 0x200000) == 0) {
    if ((local_1c != 0) &&
       ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                           param_2 * 4) + 0x10) & 4) != 0)) {
      if (((int)local_1c < 0) ||
         (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                           param_2 * 4) + 8) <= (int)local_1c)) {
        FUN_11312544("index >= 0 && index < SOC_REG_NUMELS(unit, reg)",
                     "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                     ,0xfaa);
      }
      if ((local_1c == 0) ||
         ((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                             param_2 * 4) + 0x10) & 0x10000) == 0)) {
        local_58 = local_58 + (local_1c << local_4c);
      }
      else {
        local_58 = local_58 + ((local_1c << 1) << local_4c);
      }
    }
  }
  else {
    if (((int)local_1c < 0) ||
       (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x18) +
                         param_2 * 4) + 8) <= (int)local_1c)) {
      FUN_11312544("index >= 0 && index < SOC_REG_NUMELS(unit, reg)",
                   "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/reg.c"
                   ,0xfa7);
    }
    local_58 = local_58 +
               **(int **)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x20) +
                         param_2 * 4) * local_1c;
  }
  FUN_10761a94(0x20010000,"addr new: %x, block: %d, index: %d, pindex: %d, gransh: %d\n",local_58,
               *param_5,local_1c,local_50,local_4c);
  return local_58;
}



/* === FUN_10847350 @ 0x10847350 (size=1892) === */

int FUN_10847350(int param_1,uint param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
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
  
  iVar1 = *(int *)((&DAT_1212d2dc)[param_1] + 0xe1fc);
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  if (((*(uint *)((&DAT_1212d2dc)[param_1] + 0x2f2c40) & 2) == 0) ||
     (*(int *)((&DAT_1212d2dc)[param_1] + 0xe1e8) == 0)) {
    local_9c = (param_2 >> 0x14 & 0xf | (param_2 >> 0x1e) << 4) << 0x14 |
               (*(uint *)(*(int *)(*(int *)((&DAT_1212d2dc)[param_1] + 0x2f26f4) + 0x30) +
                          *(int *)((&DAT_1212d2dc)[param_1] + 0x5ba4) * 0x10 + 8) & 0x3f) << 0xe |
               0x2c000200;
    local_98 = param_2;
    local_b8 = FUN_108623e4(param_1,&local_9c,2,2,0);
    if (local_b8 < 0) {
      local_b4 = 0;
      if ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c3c) & 0x400) == 0) {
        return local_b8;
      }
      FUN_107659ac(local_18,auStack_44,local_14);
      if (local_3c == -1) {
        return local_b8;
      }
      if ((((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) +
                               local_3c * 4) + 0x10) & 2) == 0) ||
          (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) +
                            local_3c * 4) + 4) == 5)) ||
         (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) +
                           local_3c * 4) + 4) == 10)) {
        if ((*(uint *)((&DAT_1212d2dc)[local_18] + 0x2f2c3c) & 0x8000) != 0) {
          if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18) +
                               local_3c * 4) + 4) == 2) {
            local_b4 = local_30;
          }
          else if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_18] + 0x2f26f4) + 0x18)
                                    + local_3c * 4) + 4) == 4) {
            local_b4 = local_2c;
          }
          if (local_38 == -1) {
            local_38 = 0;
          }
          iVar1 = FUN_1086594c(local_18,local_3c,local_b4,local_38,local_10);
          if (iVar1 != 0) {
            iVar1 = FUN_10865a10(local_18,local_3c);
            if (iVar1 == 0) {
              return local_b8;
            }
            *local_10 = 0;
          }
          if (*(char *)((&DAT_1212d2dc)[local_18] + 0x2f186f) == '\0') {
            local_b8 = 0;
          }
        }
      }
      else {
        *local_10 = 0;
        if (*(char *)((&DAT_1212d2dc)[local_18] + 0x2f186f) == '\0') {
          local_b8 = 0;
        }
      }
    }
    if ((-1 < local_b8) && (((local_9c & 0xfc000000) != 0x30000000 || ((local_9c & 0x40) != 0)))) {
      FUN_10761a94(0x200000,"soc_reg32_read: invalid S-Channel reply, expected READ_REG_ACK:\n");
      FUN_10861dbc(local_18,&local_9c,2);
      return -1;
    }
    *local_10 = local_98;
  }
  else {
    FUN_11312da0(*(undefined4 *)((&DAT_1212d2dc)[param_1] + 0xe1e8),0xffffffff);
    if (*(int *)(&DAT_12125c5c + local_18 * 0x78) == 0) {
      (**(code **)(&DAT_12125c64 + local_18 * 0x78))
                (&DAT_12125c2c + local_18 * 0x78,iVar1 * 0x1000 + 0x31070,local_14);
    }
    else {
      *(uint *)((iVar1 * 0x1000 + 0x31070 >> 2) * 4 + *(int *)(&DAT_12125c5c + local_18 * 0x78)) =
           local_14;
    }
    if (*(int *)(&DAT_12125c5c + local_18 * 0x78) == 0) {
      uVar2 = (**(code **)(&DAT_12125c60 + local_18 * 0x78))
                        (&DAT_12125c2c + local_18 * 0x78,iVar1 * 0x1000 + 0x31074);
    }
    else {
      uVar2 = *(uint *)((iVar1 * 0x1000 + 0x31074 >> 2) * 4 +
                       *(int *)(&DAT_12125c5c + local_18 * 0x78));
    }
    FUN_11312efc(*(undefined4 *)((&DAT_1212d2dc)[local_18] + 0xe1e8));
    *local_10 = uVar2;
  }
  iVar1 = FUN_10761b70(0x20000000);
  if (iVar1 != 0) {
    FUN_10844d6c(local_18,0x20,&DAT_113c91d0,local_14,0,*local_10);
  }
  FUN_10844bc8(local_18,0,0,local_14,2,0,*local_10);
  return 0;
}



/* === FUN_10846528 @ 0x10846528 (size=1176) === */

int FUN_10846528(int param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 *param_5)

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
  iVar1 = FUN_108623e4(param_1,&local_a4,2,2,0);
  if (iVar1 < 0) {
    local_b8 = 0;
    if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c3c) & 0x400) == 0) {
      return iVar1;
    }
    FUN_10766a68(local_28,auStack_4c,local_24,local_20,local_1c);
    if (local_44 == -1) {
      return iVar1;
    }
    if ((((*(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                             local_44 * 4) + 0x10) & 2) == 0) ||
        (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                          local_44 * 4) + 4) == 5)) ||
       (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                         local_44 * 4) + 4) == 10)) {
      if ((*(uint *)((&DAT_1212d2dc)[local_28] + 0x2f2c3c) & 0x8000) != 0) {
        if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                             local_44 * 4) + 4) == 2) {
          local_b8 = local_38;
        }
        else if (*(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212d2dc)[local_28] + 0x2f26f4) + 0x18) +
                                  local_44 * 4) + 4) == 4) {
          local_b8 = local_34;
        }
        if (local_40 == -1) {
          local_40 = 0;
        }
        iVar2 = FUN_1086594c(local_28,local_44,local_b8,local_40,local_18);
        if (iVar2 != 0) {
          iVar2 = FUN_10865a10(local_28,local_44);
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
    iVar1 = FUN_10761b70(0x20000000);
    if (iVar1 != 0) {
      FUN_10844e8c(local_28,0x20,&DAT_113c91d0,local_24,local_20,local_1c,0,*local_18);
    }
    FUN_10844bc8(local_28,local_24,local_20,local_1c,2,0,*local_18);
    iVar1 = 0;
  }
  else {
    FUN_10761a94(0x200000,"_soc_reg32_get: invalid S-Channel reply, expected READ_REG_ACK:\n");
    FUN_10861dbc(local_28,&local_a4,2);
    iVar1 = -1;
  }
  return iVar1;
}



/* === FUN_113128a8 @ 0x113128a8 (size=56) === */

undefined4 FUN_113128a8(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_10324124();
  return uVar1;
}



/* === FUN_10322de8 @ 0x10322de8 (size=140) === */

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



