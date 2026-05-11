/* FP TCAM + MMU + Mirror decomp */

/* === FUN_1013df90 (size=4060) === */

undefined4 FUN_1013df90(undefined4 param_1,int param_2,void *param_3)

{
  undefined *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  char *pcVar8;
  int local_2c8;
  int local_2c4;
  int local_2c0;
  int local_2bc;
  undefined1 auStack_2ac [256];
  undefined4 local_1ac;
  uint local_1a8 [4];
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  uint local_188;
  uint local_184;
  undefined1 auStack_180 [76];
  undefined4 local_134;
  int local_130;
  uint local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_c8;
  int local_c4;
  void *local_c0;
  uint local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined1 auStack_60 [96];
  
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    iVar5 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    iVar5 = 0;
  }
  if (iVar5 == 0) {
    uVar4 = 0xfffffffe;
  }
  else {
    local_c8 = param_1;
    local_c4 = param_2;
    local_c0 = param_3;
    uVar4 = FUN_1009067c(iVar5);
    if (*(int *)(local_c4 + 0x2008) < *(int *)(local_c4 + 0x2004)) {
      iVar5 = *(int *)(local_c4 + *(int *)(local_c4 + 0x2008) * 4 + 4);
      *(int *)(local_c4 + 0x2008) = *(int *)(local_c4 + 0x2008) + 1;
    }
    else {
      iVar5 = 0;
    }
    if (iVar5 == 0) {
      iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)("FP(unit %d) verb: _group_create pri=%d\n",local_c8,uVar4);
      }
      memcpy(&local_b0,local_c0,0x4c);
      iVar5 = FUN_103ab670(local_c8,&local_b0,uVar4,&local_1ac);
      if (iVar5 < 0) {
        if ((iVar5 < 1) && (-0x13 < iVar5)) {
          iVar5 = -iVar5;
        }
        else {
          iVar5 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_c8,"bcm_field_group_create",
                     (&PTR_DAT_11e43a78)[iVar5]);
        return 0xffffffff;
      }
      iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_c8,"bcm_field_group_create");
      }
    }
    else {
      local_1ac = FUN_1009067c(iVar5);
      if (*(int *)(local_c4 + 0x2008) < *(int *)(local_c4 + 0x2004)) {
        iVar5 = *(int *)(local_c4 + *(int *)(local_c4 + 0x2008) * 4 + 4);
        *(int *)(local_c4 + 0x2008) = *(int *)(local_c4 + 0x2008) + 1;
      }
      else {
        iVar5 = 0;
      }
      if (iVar5 == 0) {
        iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
        if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
          (*(code *)PTR_FUN_11e454ac)
                    ("FP(unit %d) verb: _group_create_id pri=%d gid=%d\n",local_c8,uVar4,local_1ac);
        }
        uVar2 = local_1ac;
        memcpy(&local_b0,local_c0,0x4c);
        iVar5 = FUN_103ab7c0(local_c8,&local_b0,uVar4,uVar2);
        if (iVar5 < 0) {
          if ((iVar5 < 1) && (-0x13 < iVar5)) {
            iVar5 = -iVar5;
          }
          else {
            iVar5 = 0x13;
          }
          FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_c8,"bcm_field_group_create_id",
                       (&PTR_DAT_11e43a78)[iVar5]);
          return 0xffffffff;
        }
        iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
        if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
          (*(code *)PTR_FUN_11e454ac)
                    ("FP(unit %d) verb: %s() success \n",local_c8,"bcm_field_group_create_id");
        }
      }
      else {
        iVar6 = FUN_100904b4(iVar5);
        if (iVar6 == 0) {
          local_2c8 = FUN_1009cda0(iVar5);
          if (local_2c8 == 9) {
            iVar6 = FUN_10761348(&DAT_11858c08,0x2000100);
            if ((iVar6 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
              (*(code *)PTR_FUN_11e454ac)("FP(unit %d) Error: Unknown mode: %s\n",local_c8,iVar5);
            }
            return 0xffffffff;
          }
        }
        else {
          local_2c8 = FUN_1009067c(iVar5);
        }
        if (*(int *)(local_c4 + 0x2008) < *(int *)(local_c4 + 0x2004)) {
          iVar5 = *(int *)(local_c4 + *(int *)(local_c4 + 0x2008) * 4 + 4);
          *(int *)(local_c4 + 0x2008) = *(int *)(local_c4 + 0x2008) + 1;
        }
        else {
          iVar5 = 0;
        }
        if (iVar5 == 0) {
          iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
          if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
            (*(code *)PTR_FUN_11e454ac)
                      ("FP(unit %d) verb: _group_create_id pri=%d gid=%d, mode=%d\n",local_c8,uVar4,
                       local_1ac,local_2c8);
          }
          uVar2 = local_1ac;
          memcpy(&local_b0,local_c0,0x4c);
          iVar5 = FUN_103aba68(local_c8,&local_b0,uVar4,local_2c8,uVar2);
          if (iVar5 < 0) {
            if ((iVar5 < 1) && (-0x13 < iVar5)) {
              iVar5 = -iVar5;
            }
            else {
              iVar5 = 0x13;
            }
            FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_c8,
                         "bcm_field_group_create_mode_id",(&PTR_DAT_11e43a78)[iVar5]);
            return 0xffffffff;
          }
          iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
          if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
            (*(code *)PTR_FUN_11e454ac)
                      ("FP(unit %d) verb: %s() success \n",local_c8,"bcm_field_group_create_mode_id"
                      );
          }
        }
        else {
          iVar6 = FUN_10094d64(local_c8,iVar5,local_1a8);
          if (iVar6 < 0) {
            iVar6 = FUN_10761348(&DAT_11858c08,0x2000100);
            if ((iVar6 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
              (*(code *)PTR_FUN_11e454ac)
                        ("FP(unit %d) Error: Unrecognized port bitmap: %s\n",local_c8,iVar5);
            }
            return 0xffffffff;
          }
          local_2c0 = 0;
          for (local_2bc = 0; local_2bc < 8; local_2bc = local_2bc + 1) {
            iVar5 = FUN_112e9dec(local_1a8[local_2bc]);
            local_2c0 = local_2c0 + iVar5;
          }
          if (*(int *)(local_c4 + 0x2008) < *(int *)(local_c4 + 0x2004)) {
            pcVar8 = *(char **)(local_c4 + *(int *)(local_c4 + 0x2008) * 4 + 4);
            *(int *)(local_c4 + 0x2008) = *(int *)(local_c4 + 0x2008) + 1;
          }
          else {
            pcVar8 = (char *)0x0;
          }
          if (pcVar8 == (char *)0x0) {
            if (local_2c0 == 1) {
              local_188 = 0xffffffff;
              for (local_2c4 = 0; local_2c4 < 0x148; local_2c4 = local_2c4 + 1) {
                local_188 = FUN_10793a50(local_c8,local_2c4);
                if (((-1 < (int)local_188) &&
                    (iVar5 = FUN_1038a5f4(local_c8,&local_188), iVar5 == 0)) &&
                   ((local_1a8[((int)local_188 >> 5) +
                               (uint)((int)local_188 < 0 && (local_188 & 0x1f) != 0)] &
                    1 << (local_188 +
                          (((int)local_188 >> 5) +
                          (uint)((int)local_188 < 0 && (local_188 & 0x1f) != 0)) * -0x20 & 0x3f)) !=
                    0)) {
                  iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
                  uVar2 = local_1ac;
                  puVar1 = PTR_FUN_11e454ac;
                  if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                    local_b0 = local_1a8[0];
                    local_ac = local_1a8[1];
                    local_a8 = local_1a8[2];
                    local_a4 = local_1a8[3];
                    local_a0 = local_198;
                    local_9c = local_194;
                    local_98 = local_190;
                    local_94 = local_18c;
                    uVar7 = FUN_10098b58(local_c8,auStack_2ac,0x100,&local_b0);
                    (*(code *)puVar1)("FP(unit %d) verb: _group_port_create_id pri=%d gid=%d, mode=%d port=%s\n"
                                      ,local_c8,uVar4,uVar2,local_2c8,uVar7);
                  }
                  uVar3 = local_188;
                  uVar2 = local_1ac;
                  memcpy(&local_b0,local_c0,0x4c);
                  iVar5 = FUN_103ac868(local_c8,uVar3,&local_b0,uVar4,local_2c8,uVar2);
                  if (iVar5 < 0) {
                    if ((iVar5 < 1) && (-0x13 < iVar5)) {
                      iVar5 = -iVar5;
                    }
                    else {
                      iVar5 = 0x13;
                    }
                    FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_c8,
                                 "bcm_field_group_ports_create_mode_id",(&PTR_DAT_11e43a78)[iVar5]);
                    return 0xffffffff;
                  }
                  iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
                  if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                    (*(code *)PTR_FUN_11e454ac)
                              ("FP(unit %d) verb: %s() success \n",local_c8,
                               "bcm_field_group_ports_create_mode_id");
                  }
                }
              }
            }
            else {
              iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
              uVar2 = local_1ac;
              puVar1 = PTR_FUN_11e454ac;
              if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                local_b0 = local_1a8[0];
                local_ac = local_1a8[1];
                local_a8 = local_1a8[2];
                local_a4 = local_1a8[3];
                local_a0 = local_198;
                local_9c = local_194;
                local_98 = local_190;
                local_94 = local_18c;
                uVar7 = FUN_10098b58(local_c8,auStack_2ac,0x100,&local_b0);
                (*(code *)puVar1)("FP(unit %d) verb: _group_ports_create_mode_id pri=%d gid=%d, mode=%d pbmp=%s\n"
                                  ,local_c8,uVar4,uVar2,local_2c8,uVar7);
              }
              uVar2 = local_1ac;
              local_b0 = local_1a8[0];
              local_ac = local_1a8[1];
              local_a8 = local_1a8[2];
              local_a4 = local_1a8[3];
              local_a0 = local_198;
              local_9c = local_194;
              local_98 = local_190;
              local_94 = local_18c;
              memcpy(auStack_60,local_c0,0x4c);
              iVar5 = FUN_103acc30(local_c8,&local_b0,auStack_60,uVar4,local_2c8,uVar2);
              if (iVar5 < 0) {
                if ((iVar5 < 1) && (-0x13 < iVar5)) {
                  iVar5 = -iVar5;
                }
                else {
                  iVar5 = 0x13;
                }
                FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_c8,
                             "bcm_field_group_ports_create_mode_id",(&PTR_DAT_11e43a78)[iVar5]);
                return 0xffffffff;
              }
              iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
              if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                (*(code *)PTR_FUN_11e454ac)
                          ("FP(unit %d) verb: %s() success \n",local_c8,
                           "bcm_field_group_ports_create_mode_id");
              }
            }
          }
          else {
            FUN_112affe4(&local_184);
            iVar5 = strncasecmp(pcVar8,"small",5);
            if (iVar5 == 0) {
              local_184 = local_184 | 8;
            }
            else {
              iVar5 = strncasecmp(pcVar8,"large",5);
              if (iVar5 != 0) {
                iVar5 = FUN_10761348(&DAT_11858c08,0x2000100);
                if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                  (*(code *)PTR_FUN_11e454ac)
                            ("FP(unit %d) Error: Unknown size: %s.  size = [large | small]\n",
                             local_c8,pcVar8);
                }
                return 0xffffffff;
              }
              local_184 = local_184 | 0x10;
            }
            memcpy(auStack_180,local_c0,0x4c);
            local_10c = local_1ac;
            local_130 = local_2c8;
            local_184 = local_184 | 7;
            local_12c = local_1a8[0];
            local_128 = local_1a8[1];
            local_124 = local_1a8[2];
            local_120 = local_1a8[3];
            local_11c = local_198;
            local_118 = local_194;
            local_114 = local_190;
            local_110 = local_18c;
            local_134 = uVar4;
            iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
            uVar2 = local_1ac;
            puVar1 = PTR_FUN_11e454ac;
            if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
              local_b0 = local_1a8[0];
              local_ac = local_1a8[1];
              local_a8 = local_1a8[2];
              local_a4 = local_1a8[3];
              local_a0 = local_198;
              local_9c = local_194;
              local_98 = local_190;
              local_94 = local_18c;
              uVar7 = FUN_10098b58(local_c8,auStack_2ac,0x100,&local_b0);
              if ((local_184 & 0x10) == 0) {
                pcVar8 = "small";
              }
              else {
                pcVar8 = "large";
              }
              (*(code *)puVar1)("FP(unit %d) verb: _group_config_create pri=%d gid=%d, mode=%d pbmp=%s size=%s\n"
                                ,local_c8,uVar4,uVar2,local_2c8,uVar7,pcVar8);
            }
            iVar5 = FUN_103ab518(local_c8,&local_184);
            if (iVar5 < 0) {
              if ((iVar5 < 1) && (-0x13 < iVar5)) {
                iVar5 = -iVar5;
              }
              else {
                iVar5 = 0x13;
              }
              FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_c8,
                           "bcm_field_group_config_create",(&PTR_DAT_11e43a78)[iVar5]);
              return 0xffffffff;
            }
            iVar5 = FUN_10761348(&DAT_11858c08,0x2000800);
            if ((iVar5 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
              (*(code *)PTR_FUN_11e454ac)
                        ("FP(unit %d) verb: %s() success \n",local_c8,
                         "bcm_field_group_config_create");
            }
          }
        }
      }
    }
    uVar4 = 0;
  }
  return uVar4;
}



/* === FUN_1013c260 (size=928) === */

undefined4 FUN_1013c260(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    iVar2 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    uVar1 = 0xfffffffe;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    uVar1 = FUN_1009067c(iVar2);
    if (*(int *)(local_14 + 0x2008) < *(int *)(local_14 + 0x2004)) {
      iVar2 = *(int *)(local_14 + *(int *)(local_14 + 0x2008) * 4 + 4);
      *(int *)(local_14 + 0x2008) = *(int *)(local_14 + 0x2008) + 1;
    }
    else {
      iVar2 = 0;
    }
    if (iVar2 == 0) {
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)("FP(unit %d) verb: _entry_create gid=%d\n",local_18,uVar1);
      }
      iVar2 = FUN_103a9a20(local_18,uVar1,&local_1c);
      if (iVar2 < 0) {
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar2 = -iVar2;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_18,"bcm_field_entry_create",
                     (&PTR_DAT_11e43a78)[iVar2]);
        return 0xffffffff;
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_18,"bcm_field_entry_create");
      }
    }
    else {
      local_1c = FUN_1009067c(iVar2);
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: _entry_create gid=%d, eid=%d\n",local_18,uVar1,local_1c);
      }
      iVar2 = FUN_103a9b40(local_18,uVar1,local_1c);
      if (iVar2 < 0) {
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar2 = -iVar2;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_18,"bcm_field_entry_create_id",
                     (&PTR_DAT_11e43a78)[iVar2]);
        return 0xffffffff;
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_18,"bcm_field_entry_create_id");
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_1013c600 (size=936) === */

undefined4 FUN_1013c600(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  local_1c = 0xffffff91;
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    iVar2 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    uVar1 = 0xfffffffe;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    uVar1 = FUN_1009067c(iVar2);
    if (*(int *)(local_14 + 0x2008) < *(int *)(local_14 + 0x2004)) {
      iVar2 = *(int *)(local_14 + *(int *)(local_14 + 0x2008) * 4 + 4);
      *(int *)(local_14 + 0x2008) = *(int *)(local_14 + 0x2008) + 1;
    }
    else {
      iVar2 = 0;
    }
    if (iVar2 == 0) {
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: bcm_field_entry_copy(src_eid=%d)\n",local_18,uVar1);
      }
      iVar2 = FUN_103a97e0(local_18,uVar1,&local_1c);
      if (iVar2 < 0) {
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar2 = -iVar2;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_18,"bcm_field_entry_copy",
                     (&PTR_DAT_11e43a78)[iVar2]);
        return 0xffffffff;
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_18,"bcm_field_entry_copy");
      }
    }
    else {
      local_1c = FUN_1009067c(iVar2);
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb:  bcm_field_entry_copy_id(src_eid=%d, dst_eid=%d)\n",local_18,
                   uVar1,local_1c);
      }
      iVar2 = FUN_103a9900(local_18,uVar1,local_1c);
      if (iVar2 < 0) {
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar2 = -iVar2;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_18,"bcm_field_entry_copy_id",
                     (&PTR_DAT_11e43a78)[iVar2]);
        return 0xffffffff;
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_18,"bcm_field_entry_copy_id");
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_1013cc7c (size=788) === */

undefined4 FUN_1013cc7c(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    iVar1 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 == 0) {
    iVar1 = FUN_10761348(&DAT_11858c08,0x2000800);
    if ((iVar1 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
      (*(code *)PTR_FUN_11e454ac)("FP(unit %d) verb: bcm_field_entry_destroy_all()\n",param_1);
    }
    iVar1 = FUN_103a9d78(param_1);
    if (iVar1 < 0) {
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar1 = -iVar1;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",param_1,"bcm_field_entry_destroy_all",
                   (&PTR_DAT_11e43a78)[iVar1]);
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar1 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",param_1,"bcm_field_entry_destroy_all");
      }
      uVar2 = 0;
    }
  }
  else {
    uVar2 = FUN_1009067c(iVar1);
    iVar1 = FUN_10761348(&DAT_11858c08,0x2000800);
    if ((iVar1 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
      (*(code *)PTR_FUN_11e454ac)
                ("FP(unit %d) verb: bcm_field_entry_destroy(eid=%d)\n",param_1,uVar2);
    }
    iVar1 = FUN_103a9c60(param_1,uVar2);
    if (iVar1 < 0) {
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar1 = -iVar1;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",param_1,"bcm_field_entry_destroy",
                   (&PTR_DAT_11e43a78)[iVar1]);
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar1 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",param_1,"bcm_field_entry_destroy");
      }
      uVar2 = 0;
    }
  }
  return uVar2;
}



/* === FUN_1013d8e0 (size=1152) === */

undefined4 FUN_1013d8e0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *__s1;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    iVar2 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    uVar1 = 0xfffffffe;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    uVar1 = FUN_1009067c(iVar2);
    if (*(int *)(local_14 + 0x2008) < *(int *)(local_14 + 0x2004)) {
      __s1 = *(char **)(local_14 + *(int *)(local_14 + 0x2008) * 4 + 4);
      *(int *)(local_14 + 0x2008) = *(int *)(local_14 + 0x2008) + 1;
    }
    else {
      __s1 = (char *)0x0;
    }
    if (__s1 == (char *)0x0) {
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: bcm_field_entry_prio_get(eid=%d)\n",local_18,uVar1);
      }
      iVar2 = FUN_103aa9c8(local_18,uVar1,&local_1c);
      if (iVar2 < 0) {
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar2 = -iVar2;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_18,"bcm_field_entry_prio_get",
                     (&PTR_DAT_11e43a78)[iVar2]);
        return 0xffffffff;
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_18,"bcm_field_entry_prio_get");
      }
      FUN_10320d20("FP entry=%d: prio=%d\n",uVar1,local_1c);
    }
    else {
      iVar2 = FUN_100904b4(__s1);
      if (iVar2 == 0) {
        iVar2 = strcasecmp(__s1,"highest");
        if (iVar2 == 0) {
          local_1c = 0x7fffffff;
        }
        else {
          iVar2 = strcasecmp(__s1,"lowest");
          if (iVar2 == 0) {
            local_1c = 0;
          }
          else {
            iVar2 = strcasecmp(__s1,"dontcare");
            if (iVar2 == 0) {
              local_1c = 0;
            }
            else {
              iVar2 = strcasecmp(__s1,"default");
              if (iVar2 != 0) {
                return 0xfffffffe;
              }
              local_1c = 0;
            }
          }
        }
      }
      else {
        local_1c = FUN_1009067c(__s1);
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: bcm_field_entry_prio_set(eid=%d, prio=%d)\n",local_18,uVar1,
                   local_1c);
      }
      iVar2 = FUN_103aaae8(local_18,uVar1,local_1c);
      if (iVar2 < 0) {
        if ((iVar2 < 1) && (-0x13 < iVar2)) {
          iVar2 = -iVar2;
        }
        else {
          iVar2 = 0x13;
        }
        FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",local_18,"bcm_field_entry_prio_set",
                     (&PTR_DAT_11e43a78)[iVar2]);
        return 0xffffffff;
      }
      iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
      if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
        (*(code *)PTR_FUN_11e454ac)
                  ("FP(unit %d) verb: %s() success \n",local_18,"bcm_field_entry_prio_set");
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_10079718 (size=1488) === */

int FUN_10079718(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  short local_34;
  int local_2c;
  short local_24;
  undefined1 auStack_22 [2];
  int local_20 [2];
  int local_18;
  undefined4 local_14;
  int local_10;
  
  uVar4 = 0;
  iVar3 = *(int *)(param_3 + 0x1f8);
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  iVar1 = FUN_103a9fa0(*(undefined4 *)(param_1 + 4),*(undefined4 *)(iVar3 + 4),local_20);
  if (iVar1 < 0) {
    if (0 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar3 = -iVar1;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(1,"%s %s:%d ERR bcm_field_entry_enable_get failed %s\n",0x33,uVar2,
                   "hal_acl_bcm.c",0x688,(&PTR_DAT_11e43a78)[iVar3],"TranslationValueSet",uVar4);
    }
  }
  else {
    iVar1 = FUN_103d2938(*(undefined4 *)(local_18 + 4),*(undefined4 *)(iVar3 + 4),&local_24,
                         auStack_22);
    if (iVar1 < 0) {
      if (0 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar3 = -iVar1;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_OuterVlanId_get failed %s\n",0x3a,uVar2,
                     "hal_acl_bcm.c",0x68f,(&PTR_DAT_11e43a78)[iVar3],"TranslationValueSet",uVar4);
      }
    }
    else {
      if (*(int *)(local_10 + 0x1c0) == 1) {
        local_2c = FUN_10028b24(local_10 + 0x30);
        piVar5 = (int *)**(undefined4 **)(local_10 + 0x1bc);
      }
      else {
        local_2c = FUN_10028b24(local_10 + 0x10);
        piVar5 = (int *)**(undefined4 **)(local_10 + 0x1ac);
      }
      if (local_2c != 0) {
        FUN_1000bc9c(local_2c,piVar5);
        if (*piVar5 == 3) {
          return iVar1;
        }
        if (*(int *)(local_10 + 0x1c0) == 1) {
          local_34 = (short)piVar5[2];
        }
        else {
          local_34 = FUN_1006f430(local_18,piVar5);
        }
      }
      if ((local_2c == 0) || (local_34 == -1)) {
        if ((local_20[0] != 0) &&
           ((iVar1 = FUN_103aa0c0(*(undefined4 *)(local_18 + 4),*(undefined4 *)(iVar3 + 4),0),
            iVar1 < 0 && (0 < DAT_11e45404)))) {
          uVar4 = FUN_10046f5c();
          if ((iVar1 < 1) && (-0x13 < iVar1)) {
            iVar3 = -iVar1;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_entry_enable_set failed %s\n",0x33,uVar4,
                       "hal_acl_bcm.c",0x6c6,(&PTR_DAT_11e43a78)[iVar3]);
        }
      }
      else if ((local_20[0] == 0) || (local_34 != local_24)) {
        iVar1 = FUN_103aa0c0(*(undefined4 *)(local_18 + 4),*(undefined4 *)(iVar3 + 4),1);
        if (iVar1 < 0) {
          if (0 < DAT_11e45404) {
            uVar4 = FUN_10046f5c();
            if ((iVar1 < 1) && (-0x13 < iVar1)) {
              iVar3 = -iVar1;
            }
            else {
              iVar3 = 0x13;
            }
            FUN_10047040(1,"%s %s:%d ERR bcm_field_entry_enable_set failed %s\n",0x33,uVar4,
                         "hal_acl_bcm.c",0x6b3,(&PTR_DAT_11e43a78)[iVar3]);
          }
        }
        else {
          iVar1 = FUN_10075e78(local_18,local_10,*(undefined4 *)(iVar3 + 4));
          if (iVar1 < 0) {
            if (0 < DAT_11e45404) {
              uVar4 = FUN_10046f5c();
              if ((iVar1 < 1) && (-0x13 < iVar1)) {
                iVar3 = -iVar1;
              }
              else {
                iVar3 = 0x13;
              }
              FUN_10047040(1,"%s %s:%d ERR hal_bcm_acl_entry_match_if_add failed %s\n",0x37,uVar4,
                           "hal_acl_bcm.c",0x6b9,(&PTR_DAT_11e43a78)[iVar3]);
            }
          }
          else {
            iVar1 = FUN_103aac08(*(undefined4 *)(local_18 + 4),*(undefined4 *)(iVar3 + 4));
            if ((iVar1 < 0) && (0 < DAT_11e45404)) {
              uVar4 = FUN_10046f5c();
              if ((iVar1 < 1) && (-0x13 < iVar1)) {
                iVar3 = -iVar1;
              }
              else {
                iVar3 = 0x13;
              }
              FUN_10047040(1,"%s %s:%d ERR bcm_field_entry_reinstall failed %s\n",0x32,uVar4,
                           "hal_acl_bcm.c",0x6be,(&PTR_DAT_11e43a78)[iVar3]);
            }
          }
        }
      }
    }
  }
  return iVar1;
}



/* === FUN_10216970 (size=4192) === */

undefined4 FUN_10216970(int param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  void *__s;
  undefined4 uVar6;
  int local_148;
  uint local_144;
  uint local_140;
  int local_13c;
  int local_138;
  int local_134;
  int local_130;
  int local_12c;
  uint local_118 [4];
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  uint local_f8 [4];
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 auStack_d0 [4];
  undefined2 local_c0;
  undefined2 local_be;
  uint local_bc [21];
  int local_68;
  int local_64;
  undefined1 auStack_60 [96];
  
  local_68 = param_1;
  local_64 = param_2;
  local_144 = 0xfffffff0;
  local_d8 = 0;
  *(int *)(param_2 + 0x2d8) = param_1;
  local_148 = 0;
  iVar4 = (&DAT_1212b9c4)[param_1];
  local_118[0] = *(uint *)(iVar4 + 0x488);
  local_118[1] = *(undefined4 *)(iVar4 + 0x48c);
  local_118[2] = *(undefined4 *)(iVar4 + 0x490);
  local_118[3] = *(undefined4 *)(iVar4 + 0x494);
  local_108 = *(undefined4 *)(iVar4 + 0x498);
  local_104 = *(undefined4 *)(iVar4 + 0x49c);
  local_100 = *(undefined4 *)(iVar4 + 0x4a0);
  local_fc = *(undefined4 *)(iVar4 + 0x4a4);
  for (local_138 = 0; local_138 < 8; local_138 = local_138 + 1) {
    local_118[local_138] =
         local_118[local_138] | *(uint *)((&DAT_1212b9c4)[local_68] + (local_138 + 0x408) * 4 + 0xc)
    ;
  }
  local_13c = 0;
  for (local_140 = 0; (int)local_140 < 0x100; local_140 = local_140 + 1) {
    iVar4 = (int)local_140 >> 5;
    if (((local_118[iVar4 + (uint)((int)local_140 < 0 && (local_140 & 0x1f) != 0)] &
         1 << (local_140 + (iVar4 + (uint)((int)local_140 < 0 && (local_140 & 0x1f) != 0)) * -0x20 &
              0x3f)) != 0) &&
       ((*(uint *)((&DAT_1212b9c4)[local_68] +
                   (iVar4 + (uint)((int)local_140 < 0 && (local_140 & 0x1f) != 0) + 0x784) * 4 +
                  0x14) &
        1 << (local_140 + (iVar4 + (uint)((int)local_140 < 0 && (local_140 & 0x1f) != 0)) * -0x20 &
             0x3f)) == 0)) {
      local_144 = FUN_10418a10(local_68,local_140,local_64 + local_13c * 0x114 + 0x14);
      if ((int)local_144 < 0) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_info_save",0x1b2,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
      if ((-1 < (int)local_144) &&
         (local_144 = FUN_1041ab5c(local_68,local_140,0), (int)local_144 < 0)) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_linkscan_set",0x1b6,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
      if ((-1 < (int)local_144) &&
         (local_144 = FUN_104210e4(local_68,local_140,&local_d8), (int)local_144 < 0)) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_speed_max",0x1be,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
      if ((-1 < (int)local_144) &&
         (local_144 = FUN_1042121c(local_68,local_140,local_d8), (int)local_144 < 0)) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_speed_set",0x1c2,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
      if ((-1 < (int)local_144) &&
         (local_144 = FUN_1041af10(local_68,local_140,1), (int)local_144 < 0)) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_loopback_set",0x1cf,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
      if ((-1 < (int)local_144) &&
         (local_144 = FUN_1041d288(local_68,local_140,0,0), (int)local_144 < 0)) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_pause_set",0x1d3,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
      local_148 = -((int)~local_144 >> 0x1f);
      if (local_148 != 0) {
        *(uint *)(local_64 + local_13c * 4 + 4) = local_140;
        local_13c = local_13c + 1;
        if (0 < local_13c) break;
        local_148 = -7;
      }
    }
  }
  if (local_148 == 0) {
    FUN_101120a0(local_68,"Unable to find suitable XE/GE port.\n");
    uVar6 = 0xffffffff;
  }
  else {
    iVar4 = (&DAT_1212b9c4)[local_68];
    local_f8[0] = *(uint *)(iVar4 + 0x4f08);
    local_f8[1] = *(undefined4 *)(iVar4 + 0x4f0c);
    local_f8[2] = *(undefined4 *)(iVar4 + 0x4f10);
    local_f8[3] = *(undefined4 *)(iVar4 + 0x4f14);
    local_e8 = *(undefined4 *)(iVar4 + 0x4f18);
    local_e4 = *(undefined4 *)(iVar4 + 0x4f1c);
    local_e0 = *(undefined4 *)(iVar4 + 0x4f20);
    local_dc = *(undefined4 *)(iVar4 + 0x4f24);
    for (local_13c = 0; local_13c < 1; local_13c = local_13c + 1) {
      uVar2 = *(uint *)(local_64 + local_13c * 4 + 4);
      iVar4 = ((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
      uVar2 = *(uint *)(local_64 + local_13c * 4 + 4);
      local_f8[iVar4] =
           local_f8[iVar4] &
           ~(1 << (uVar2 + (((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) *
                           -0x20 & 0x3f));
    }
    for (local_140 = 0; (int)local_140 < 0x100; local_140 = local_140 + 1) {
      if (((local_f8[((int)local_140 >> 5) + (uint)((int)local_140 < 0 && (local_140 & 0x1f) != 0)]
           & 1 << (local_140 +
                   (((int)local_140 >> 5) + (uint)((int)local_140 < 0 && (local_140 & 0x1f) != 0)) *
                   -0x20 & 0x3f)) != 0) &&
         (local_144 = FUN_1041652c(local_68,local_140,0), (int)local_144 < 0)) {
        if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
          iVar4 = -local_144;
        }
        else {
          iVar4 = 0x13;
        }
        FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_port_enable_set",0x22c,local_144,
                     (&PTR_DAT_11e43a78)[iVar4]);
      }
    }
    if ((*(uint *)((&DAT_1212b9c4)[local_68] + 0x2f2c28) & 0x2000000) != 0) {
      auStack_d0[2] = 0xffffffff;
      auStack_d0[3] = 1;
      memset(local_bc,0,0x4c);
      local_bc[0] = local_bc[0] | 0x1000;
      memcpy(auStack_60,local_bc,0x4c);
      local_144 = FUN_103ab670(local_68,auStack_60,0x80000001,&local_d4);
      for (local_13c = 0; local_13c < 1; local_13c = local_13c + 1) {
        if (-1 < (int)local_144) {
          local_144 = FUN_103a9a20(local_68,local_d4,auStack_d0 + local_13c);
        }
        if (-1 < (int)local_144) {
          *(undefined4 *)(local_64 + (local_13c + 0x94) * 4 + 8) = auStack_d0[local_13c];
          local_144 = FUN_103bd46c(local_68,auStack_d0[local_13c],
                                   *(undefined4 *)(local_64 + local_13c * 4 + 4),0xffffffff);
        }
      }
      if (-1 < (int)local_144) {
        for (local_13c = 0; local_13c < 1; local_13c = local_13c + 1) {
          iVar4 = FUN_103e02c0(local_68,local_d4,1,auStack_d0 + 3,auStack_d0 + 2);
          if (iVar4 < 0) {
            if ((iVar4 < 1) && (-0x13 < iVar4)) {
              iVar5 = -iVar4;
            }
            else {
              iVar5 = 0x13;
            }
            FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_field_stat_create",0x265,iVar4,
                         (&PTR_DAT_11e43a78)[iVar5]);
          }
          local_144 = FUN_103aae38(local_68,auStack_d0[local_13c],auStack_d0[2]);
          if ((int)local_144 < 0) {
            if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
              iVar4 = -local_144;
            }
            else {
              iVar4 = 0x13;
            }
            FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_field_entry_stat_attach",0x268,
                         local_144,(&PTR_DAT_11e43a78)[iVar4]);
          }
          auStack_d0[2] = 0xffffffff;
        }
      }
      for (local_13c = 0; local_13c < 1; local_13c = local_13c + 1) {
        if ((-1 < (int)local_144) &&
           (local_144 = FUN_103a7a5c(local_68,auStack_d0[local_13c],0x17,0,0), (int)local_144 < 0))
        {
          if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
            iVar4 = -local_144;
          }
          else {
            iVar4 = 0x13;
          }
          FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_field_action_add",0x273,local_144,
                       (&PTR_DAT_11e43a78)[iVar4]);
        }
        if ((-1 < (int)local_144) &&
           (local_144 = FUN_103a7a5c(local_68,auStack_d0[local_13c],0x1d,0,
                                     *(undefined4 *)(local_64 + local_13c * 4 + 4)),
           (int)local_144 < 0)) {
          if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
            iVar4 = -local_144;
          }
          else {
            iVar4 = 0x13;
          }
          FUN_10320d20("call to %s line %d failed:%d %s\n","bcm_field_action_add",0x281,local_144,
                       (&PTR_DAT_11e43a78)[iVar4]);
        }
      }
    }
    if ((int)local_144 < 0) {
      if (((int)local_144 < 1) && (-0x13 < (int)local_144)) {
        iVar4 = -local_144;
      }
      else {
        iVar4 = 0x13;
      }
      FUN_101120a0(local_68,"Unable to configure filter: %s\n",(&PTR_DAT_11e43a78)[iVar4]);
      uVar6 = 0xffffffff;
    }
    else {
      for (local_13c = 0; local_13c < 1; local_13c = local_13c + 1) {
        FUN_1041a53c(local_68,*(undefined4 *)(local_64 + local_13c * 4 + 4),4);
      }
      FUN_112b3778(*(undefined4 *)(local_64 + 0x2d8),*(undefined4 *)(local_64 + 0x268),0,
                   local_64 + 0x274);
      uVar3 = DAT_11850768;
      if (*(int *)(local_64 + 0x274) == 0) {
        FUN_101120a0(local_68,"Failed to allocate Tx packet\n");
        uVar6 = 0xffffffff;
      }
      else {
        puVar1 = *(undefined4 **)(*(int *)(local_64 + 0x274) + 0x108);
        *puVar1 = DAT_11850764;
        *(undefined2 *)(puVar1 + 1) = uVar3;
        uVar3 = DAT_11850770;
        iVar4 = *(int *)(*(int *)(local_64 + 0x274) + 0x108);
        *(undefined4 *)(iVar4 + 6) = DAT_1185076c;
        *(undefined2 *)(iVar4 + 10) = uVar3;
        local_c0 = 0x8100;
        *(undefined2 *)(*(int *)(*(int *)(local_64 + 0x274) + 0x108) + 0xc) = 0x8100;
        local_be = 1;
        *(undefined2 *)(*(int *)(*(int *)(local_64 + 0x274) + 0x108) + 0xe) = 1;
        __s = (void *)(*(int *)**(undefined4 **)(local_64 + 0x274) + 0x10);
        memset(__s,0xff,*(int *)(local_64 + 0x268) +
                        (*(int *)**(undefined4 **)(local_64 + 0x274) - (int)__s));
        for (local_134 = 0; local_134 < 8; local_134 = local_134 + 1) {
          *(undefined4 *)(*(int *)(local_64 + 0x274) + (local_134 + 0x14) * 4) = 0;
        }
        uVar2 = *(uint *)(local_64 + 4);
        iVar4 = ((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
        uVar2 = *(uint *)(local_64 + 4);
        *(uint *)(*(int *)(local_64 + 0x274) + (iVar4 + 0x14) * 4) =
             *(uint *)(*(int *)(local_64 + 0x274) + (iVar4 + 0x14) * 4) |
             1 << (uVar2 + (((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) *
                           -0x20 & 0x3f);
        for (local_130 = 0; local_130 < 8; local_130 = local_130 + 1) {
          *(undefined4 *)(*(int *)(local_64 + 0x274) + (local_130 + 0x1c) * 4) = 0;
        }
        for (local_12c = 0; local_12c < 8; local_12c = local_12c + 1) {
          *(undefined4 *)(*(int *)(local_64 + 0x274) + (local_12c + 0x24) * 4) = 0;
        }
        *(undefined2 *)(*(int *)(local_64 + 0x274) + 0x20) = 0;
        *(undefined4 *)(*(int *)(local_64 + 0x274) + 0xfc) = 0x20;
        *(undefined1 *)(*(int *)(local_64 + 0x274) + 0x22) = 1;
        iVar4 = FUN_10216670(*(undefined4 *)(local_64 + 0x2d8),local_64);
        if (iVar4 < 0) {
          FUN_101120a0(local_68,"Could not setup receiver\n");
          uVar6 = 0xffffffff;
        }
        else {
          uVar6 = 0;
        }
      }
    }
  }
  return uVar6;
}



/* NO FUNCTION at 0x10144bb0 */

/* === FUN_10145c7c (size=8912) === */

int FUN_10145c7c(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  char *__s1;
  char *__s1_00;
  int local_28;
  
  if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
    iVar2 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
    *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    local_28 = -2;
  }
  else {
    uVar1 = FUN_1009067c(iVar2);
    if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
      __s1 = *(char **)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
      *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
    }
    else {
      __s1 = (char *)0x0;
    }
    if (__s1 == (char *)0x0) {
      local_28 = -2;
    }
    else {
      iVar2 = strcasecmp(__s1,"clear");
      if (iVar2 == 0) {
        iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
        if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
          (*(code *)PTR_FUN_11e454ac)("FP(unit %d) verb:fp_qual_clear \'eid=%d\'\n",param_1,uVar1);
        }
        local_28 = FUN_103de864(param_1,uVar1);
        if (local_28 < 0) {
          if ((local_28 < 1) && (-0x13 < local_28)) {
            local_28 = -local_28;
          }
          else {
            local_28 = 0x13;
          }
          FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",param_1,"bcm_field_qualify_clear",
                       (&PTR_DAT_11e43a78)[local_28]);
          local_28 = -1;
        }
        else {
          iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
          if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
            (*(code *)PTR_FUN_11e454ac)
                      ("FP(unit %d) verb: %s() success \n",param_1,"bcm_field_qualify_clear");
          }
        }
      }
      else {
        iVar2 = strcasecmp(__s1,"delete");
        if (iVar2 == 0) {
          if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
            iVar2 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
            *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
          }
          else {
            iVar2 = 0;
          }
          if (iVar2 == 0) {
            local_28 = -2;
          }
          else {
            iVar3 = FUN_10761348(&DAT_11858c08,0x2000800);
            if ((iVar3 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
              (*(code *)PTR_FUN_11e454ac)
                        ("FP(unit %d) verb:fp_qual_delete  \'eid=%d qual=%s\'\n",param_1,uVar1,iVar2
                        );
            }
            uVar4 = FUN_1009c678(iVar2);
            local_28 = FUN_103ae5f8(param_1,uVar1,uVar4);
            if (local_28 < 0) {
              if ((local_28 < 1) && (-0x13 < local_28)) {
                local_28 = -local_28;
              }
              else {
                local_28 = 0x13;
              }
              FUN_10320d20("FP(unit %d) Error: %s() failed: %s\n",param_1,
                           "bcm_field_qualifier_delete",(&PTR_DAT_11e43a78)[local_28]);
              local_28 = -1;
            }
            else {
              iVar2 = FUN_10761348(&DAT_11858c08,0x2000800);
              if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                (*(code *)PTR_FUN_11e454ac)
                          ("FP(unit %d) verb: %s() success \n",param_1,"bcm_field_qualifier_delete")
                ;
              }
            }
          }
        }
        else {
          iVar2 = strcasecmp(__s1,"Data");
          if (iVar2 == 0) {
            local_28 = FUN_1014ac78(param_1,uVar1,param_2);
          }
          else {
            if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
              __s1_00 = *(char **)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
              *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
            }
            else {
              __s1_00 = (char *)0x0;
            }
            if (__s1_00 != (char *)0x0) {
              iVar2 = strcasecmp(__s1_00,"show");
              if ((iVar2 == 0) || (iVar2 = strcasecmp(__s1_00,"?"), iVar2 == 0)) {
                uVar1 = FUN_1009c678(__s1);
                switch(uVar1) {
                case 6:
                  iVar2 = FUN_1014a388("fp qual <eid> ",&DAT_11359328,0);
                  return iVar2;
                case 7:
                  iVar2 = FUN_1014a388("fp qual <eid> ","DstMac",0);
                  return iVar2;
                default:
                  iVar2 = FUN_101418b8(param_1,param_2);
                  return iVar2;
                case 0x23:
                  iVar2 = FUN_10148ce4("fp qual <eid> ","SrcPort",0);
                  return iVar2;
                case 0x28:
                  iVar2 = FUN_10148ce4("fp qual <eid> ","DstPort",0);
                  return iVar2;
                case 0x2b:
                  iVar2 = FUN_1014bf48("fp qual <eid> ",0);
                  return iVar2;
                case 0x33:
                  iVar2 = FUN_1014bcc4("fp qual <eid> ",0);
                  return iVar2;
                case 0x3a:
                  iVar2 = FUN_1014cd34("fp qual <eid> ",0);
                  return iVar2;
                case 0x3b:
                  iVar2 = FUN_1014caa4("fp qual <eid> ",0);
                  return iVar2;
                case 0x3e:
                  iVar2 = FUN_1014c34c("fp qual <eid> ",0);
                  return iVar2;
                case 0x53:
                  iVar2 = FUN_1014c814("fp qual <eid> ",0);
                  return iVar2;
                }
              }
              *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + -1;
            }
            uVar4 = FUN_1009c678(__s1);
            switch(uVar4) {
            case 0:
              local_28 = FUN_10149d68(param_1,uVar1,param_2,FUN_103d6af8,&DAT_11359b1c);
              break;
            case 1:
              local_28 = FUN_10149d68(param_1,uVar1,param_2,FUN_103b18b0,&DAT_11359b3c);
              break;
            case 2:
              local_28 = FUN_10149d68(param_1,uVar1,param_2,FUN_103d6c20,&DAT_11359b24);
              break;
            case 3:
              local_28 = FUN_10149d68(param_1,uVar1,param_2,FUN_103b19d8,"DstIp6High");
              break;
            case 4:
              local_28 = FUN_10149d68(param_1,uVar1,param_2,FUN_103d6e70,&DAT_11359b30);
              break;
            case 5:
              local_28 = FUN_10149d68(param_1,uVar1,param_2,FUN_103b1c28,"DstIp6Low");
              break;
            case 6:
              local_28 = FUN_1014a028(param_1,uVar1,param_2,FUN_103d7554,&DAT_11359328);
              break;
            case 7:
              local_28 = FUN_1014a028(param_1,uVar1,param_2,FUN_103b27cc,"DstMac");
              break;
            default:
              FUN_101418b8(param_1,param_2);
              iVar2 = FUN_10761348(&DAT_11858c08,0x2000100);
              if ((iVar2 != 0) && (PTR_FUN_11e454ac != (undefined *)0x0)) {
                (*(code *)PTR_FUN_11e454ac)
                          ("FP(unit %d) Error: Unknown qualifier: %s\n",param_1,__s1);
              }
              local_28 = -1;
              break;
            case 9:
              local_28 = FUN_10149a08(param_1,uVar1,param_2,FUN_103d69cc,&DAT_11359990);
              break;
            case 10:
              local_28 = FUN_10149a08(param_1,uVar1,param_2,FUN_103b1784,"DstIp");
              break;
            case 0xc:
              local_28 = FUN_1014871c(param_1,uVar1,param_2,FUN_103bd46c,"InPort");
              break;
            case 0xd:
              local_28 = FUN_10147f4c(param_1,uVar1,param_2);
              break;
            case 0xe:
              local_28 = FUN_10148334(param_1,uVar1,param_2);
              break;
            case 0xf:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b0944,&DAT_11359874);
              break;
            case 0x10:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103c3978,"Ip6FlowLabel");
              break;
            case 0x11:
              local_28 = FUN_10149554(param_1,uVar1,param_2,FUN_103d2438,"OuterVlan");
              break;
            case 0x12:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103d27f0,"OuterVlanId");
              break;
            case 0x13:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d2a60,"OuterVlanPri");
              break;
            case 0x14:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d2580,"OuterVlanCfi");
              break;
            case 0x15:
              local_28 = FUN_10149554(param_1,uVar1,param_2,FUN_103c2198,"InnerVlan");
              break;
            case 0x16:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103c2550,"InnerVlanId");
              break;
            case 0x17:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c27c0,"InnerVlanPri");
              break;
            case 0x18:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c22e0,"InnerVlanCfi");
              break;
            case 0x1a:
              local_28 = FUN_101492b4(param_1,uVar1,param_2,FUN_103d3ea8,"RangeCheck");
              break;
            case 0x1b:
              local_28 = FUN_10149018(param_1,uVar1,param_2,FUN_103c9e4c,"L4SrcPort");
              break;
            case 0x1c:
              local_28 = FUN_10149018(param_1,uVar1,param_2,FUN_103c9728,"L4DstPort");
              break;
            case 0x1d:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b59f4,"EtherType");
              break;
            case 0x1e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c4f04,"IpProtocol");
              break;
            case 0x1f:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b00d0,&DAT_113599a0);
              break;
            case 0x20:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103dc238,&DAT_11359b0c);
              break;
            case 0x23:
              local_28 = FUN_10148a28(param_1,uVar1,param_2,FUN_103d8398,"SrcPort");
              break;
            case 0x24:
              local_28 = FUN_10148d7c(param_1,uVar1,param_2,FUN_103d8628,"SrcTrunk");
              break;
            case 0x25:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d8750,"SrcTrunkMemberGport");
              break;
            case 0x28:
              local_28 = FUN_10148a28(param_1,uVar1,param_2,FUN_103b35ec,"DstPort");
              break;
            case 0x29:
              local_28 = FUN_10148d7c(param_1,uVar1,param_2,FUN_103b3ae0,"DstTrunk");
              break;
            case 0x2a:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d992c,"TcpControl");
              break;
            case 0x2b:
              local_28 = FUN_1014bd3c(param_1,uVar1,param_2);
              break;
            case 0x2d:
              local_28 = FUN_1014a420(param_1,uVar1,param_2,FUN_103d62c0,"SrcClassL2");
              break;
            case 0x2e:
              local_28 = FUN_1014a420(param_1,uVar1,param_2,FUN_103d6514,"SrcClassL3");
              break;
            case 0x2f:
              local_28 = FUN_1014a420(param_1,uVar1,param_2,FUN_103d606c,"SrcClassField");
              break;
            case 0x30:
              local_28 = FUN_1014a6a0(param_1,uVar1,param_2,FUN_103b0e08,"DstClassL2");
              break;
            case 0x31:
              local_28 = FUN_1014a6a0(param_1,uVar1,param_2,FUN_103b105c,"DstClassL3");
              break;
            case 0x32:
              local_28 = FUN_1014a6a0(param_1,uVar1,param_2,FUN_103b0bb4,"DstClassField");
              break;
            case 0x33:
              local_28 = FUN_1014b97c(param_1,uVar1,param_2);
              break;
            case 0x34:
              local_28 = FUN_1014d6ac(param_1,uVar1,param_2);
              break;
            case 0x35:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cb15c,"MHOpcode");
              break;
            case 0x36:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c47fc,"IpFlags");
              break;
            case 0x37:
              local_28 = FUN_101497ec(param_1,uVar1,param_2,FUN_103c1cd4,"InnerTpid");
              break;
            case 0x38:
              local_28 = FUN_101497ec(param_1,uVar1,param_2,FUN_103d21e4,"OuterTpid");
              break;
            case 0x3a:
              local_28 = FUN_1014cb38(param_1,uVar1,param_2);
              break;
            case 0x3b:
              local_28 = FUN_1014c8a8(param_1,uVar1,param_2);
              break;
            case 0x3c:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103caca8,"Loopback");
              break;
            case 0x3d:
              local_28 = FUN_1014d25c(param_1,uVar1,param_2);
              break;
            case 0x3e:
              local_28 = FUN_1014c3e0(param_1,uVar1,param_2);
              break;
            case 0x3f:
              local_28 = FUN_1014b754(param_1,uVar1,param_2);
              break;
            case 0x40:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103bc5e8,&DAT_11359bc8);
              break;
            case 0x42:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b1514,"DstHiGig");
              break;
            case 0x4e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d9b9c,"TcpHeaderSize");
              break;
            case 0x4f:
              local_28 = FUN_1014cdc8(param_1,uVar1,param_2,FUN_103c2dc8,"InterfaceClassL2");
              break;
            case 0x50:
              local_28 = FUN_1014cdc8(param_1,uVar1,param_2,FUN_103c301c,"InterfaceClassL3");
              break;
            case 0x51:
              local_28 = FUN_1014cdc8(param_1,uVar1,param_2,FUN_103c3270,"InterfaceClassPort");
              break;
            case 0x52:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c8b08,"L3Routable");
              break;
            case 0x53:
              local_28 = FUN_1014c618(param_1,uVar1,param_2);
              break;
            case 0x54:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103de14c,&DAT_1135994c);
              break;
            case 0x55:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103c88b4,"L3Ingress");
              break;
            case 0x56:
              local_28 = FUN_1014871c(param_1,uVar1,param_2,FUN_103d1694,"OutPort");
              break;
            case 0x59:
              local_28 = FUN_1014d484(param_1,uVar1,param_2);
              break;
            case 0x5a:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103dd2e4,"VlanFormat");
              break;
            case 0x5b:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103db640,"TranslatedVlanFormat");
              break;
            case 0x5c:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b6144,"ExtensionHeaderType");
              break;
            case 0x5d:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b5ed4,"ExtensionHeaderSubCode");
              break;
            case 0x5f:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c9bdc,&DAT_1135995c);
              break;
            case 0x60:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cbb1c,"MirrorCopy");
              break;
            case 0x61:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103dc6fc,"TunnelTerminated");
              break;
            case 0x62:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d0324,"TunnelTerminated");
              break;
            case 99:
              local_28 = FUN_10149a08(param_1,uVar1,param_2,FUN_103c1120,"InnerSrcIp");
              break;
            case 100:
              local_28 = FUN_10149a08(param_1,uVar1,param_2,FUN_103bf05c,"InnerDstIp");
              break;
            case 0x6d:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103dd554,"VlanTranslationHit");
              break;
            case 0x6e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103bbc78,"ForwardingVlanValid");
              break;
            case 0x6f:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103be90c,"IngressStpState");
              break;
            case 0x70:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c77c4,"L2SrcHit");
              break;
            case 0x71:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c7a34,"L2SrcStatic");
              break;
            case 0x72:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c66ec,"L2DestHit");
              break;
            case 0x73:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c7f04,"L2StationMove");
              break;
            case 0x74:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c647c,"L2CacheHit");
              break;
            case 0x75:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c8fe8,"L3SrcHostHit");
              break;
            case 0x76:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c8174,"L3DestHostHit");
              break;
            case 0x77:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c83e4,"L3DestRouteHit");
              break;
            case 0x78:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c5d3c,"IpmcStarGroupHit");
              break;
            case 0x79:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b06d4,"DosAttack");
              break;
            case 0x7d:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103bcf8c,"IcmpTypeCode");
              break;
            case 0x83:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b2338,"DstL3Egress");
              break;
            case 0x84:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b2ee4,"DstMulticastGroup");
              break;
            case 0x85:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d7ed0,"SrcMplsGport");
              break;
            case 0x86:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b2c80,"DstMplsGport");
              break;
            case 0x87:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d77a4,"SrcMimGport");
              break;
            case 0x88:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b2a1c,"DstMimGport");
              break;
            case 0x89:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d9214,"SrcWlanGport");
              break;
            case 0x8a:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b41f8,"DstWlanGport");
              break;
            case 0x8d:
              local_28 = FUN_1014bfdc(param_1,uVar1,param_2);
              break;
            case 0x8e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c2b58,"IntPriority");
              break;
            case 0x8f:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103bba08,"ForwardingVlanId");
              break;
            case 0x96:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103dda24,&DAT_11359cb8);
              break;
            case 0x97:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103af9b8,&DAT_11359cc0);
              break;
            case 0x98:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103b76f4,"FabricQueueTag");
              break;
            case 0x99:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d0a64,"MyStationHit");
              break;
            case 0x9d:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103b2458,"DstL3EgressNextHops");
              break;
            case 0x9e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d410c,"RecoverableDrop");
              break;
            case 0x9f:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d437c,"RepCopy");
              break;
            case 0xa0:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c53b8,"IpTunnelHit");
              break;
            case 0xa1:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cdb88,"MplsLabel1Hit");
              break;
            case 0xa2:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103db9dc,"TrillEgressRbridgeHit");
              break;
            case 0xa3:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c6e00,"L2GreSrcIpHit");
              break;
            case 0xa4:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cb63c,"MimSrcGportHit");
              break;
            case 0xa5:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103ce9f0,"MplsLabel2Hit");
              break;
            case 0xa6:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103dbd74,"TrillIngressRbridgeHit");
              break;
            case 0xa7:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c7070,"L2GreVfiHit");
              break;
            case 0xa8:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cb8ac,&DAT_11359d78);
              break;
            case 0xa9:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103bbee8,
                                      "GenericAssociatedChannelLabelValid");
              break;
            case 0xaa:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d4acc,"RouterAlertLabelValid");
              break;
            case 0xab:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b1fa0,"DstIpLocal");
              break;
            case 0xae:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103c431c,"IpAddrsNormalized");
              break;
            case 0xaf:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cb3cc,"MacAddrsNormalized");
              break;
            case 0xb0:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103cc4c0,"MplsForwardingLabel");
              break;
            case 0xb1:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cd1e4,"MplsForwardingLabelTtl");
              break;
            case 0xb2:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103ccab0,"MplsForwardingLabelBos");
              break;
            case 0xb3:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103ccd20,"MplsForwardingLabelExp");
              break;
            case 0xb4:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103ccf90,"MplsForwardingLabelId");
              break;
            case 0xb5:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103cbffc,"MplsControlWord");
              break;
            case 0xb6:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103d4fac,"Rtag7AHashUpper");
              break;
            case 0xb7:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103d4d3c,"Rtag7AHashLower");
              break;
            case 0xb8:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103d548c,"Rtag7BHashUpper");
              break;
            case 0xb9:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103d521c,"Rtag7BHashLower");
              break;
            case 0xba:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cc5ec,"MplsForwardingLabelAction"
                                     );
              break;
            case 0xbb:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cc128,"MplsControlWordValid");
              break;
            case 0xbc:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b4b80,"EgressClass");
              break;
            case 0xbd:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b4f38,"EgressClassL3Interface");
              break;
            case 0xbe:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b51a8,"EgressClassTrill");
              break;
            case 0xbf:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b5418,"EgressClassWlan");
              break;
            case 0xc0:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b4cc8,"EgressClassL2Gre");
              break;
            case 0xc2:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103afe60,"CpuQueue");
              break;
            case 0xc4:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d6768,&DAT_11359f54);
              break;
            case 0xdb:
              local_28 = FUN_1014cdc8(param_1,uVar1,param_2,FUN_103c3724,"InterfaceClassVPort");
              break;
            case 0x10b:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103cfe44,"MplsOuterLabelPop");
              break;
            case 0x10c:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d00b4,
                                      "MplsStationHitTunnelUnterminated");
              break;
            case 0x10d:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103bdfbc,"IngressClassField");
              break;
            case 0x10e:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103be464,"IngressInterfaceClassPort"
                                     );
              break;
            case 0x11a:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d0f44,"NatNeeded");
              break;
            case 0x11b:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d0cd4,"NatDstRealmId");
              break;
            case 0x11c:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d11b4,"NatSrcRealmId");
              break;
            case 0x11d:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103bcd1c,"IcmpError");
              break;
            case 300:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b90ec,"FibreChanRCtl");
              break;
            case 0x12d:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103b8a10,"FibreChanFCtl");
              break;
            case 0x12e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b82dc,"FibreChanCSCtl");
              break;
            case 0x12f:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b854c,"FibreChanDFCtl");
              break;
            case 0x130:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b9a90,"FibreChanType");
              break;
            case 0x131:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103b983c,"FibreChanSrcId");
              break;
            case 0x132:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103b87bc,"FibreChanDstId");
              break;
            case 0x133:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103bae10,"FibreChanZoneCheck");
              break;
            case 0x134:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b95cc,"FibreChanSrcFpmaCheck");
              break;
            case 0x135:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b935c,"FibreChanSrcBindCheck");
              break;
            case 0x136:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103ba6c0,"FibreChanVFTVersion");
              break;
            case 0x137:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103ba1e0,"FibreChanVFTPri");
              break;
            case 0x138:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103b9d00,"FibreChanVFTFabricId");
              break;
            case 0x139:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b9f70,"FibreChanVFTHopCount");
              break;
            case 0x13a:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103ba930,"FibreChanVFTVsanId");
              break;
            case 0x13b:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103baba0,"FibreChanVFTVsanPri");
              break;
            case 0x13c:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103ba450,"FibreChanVFTValid");
              break;
            case 0x13d:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b7948,"FcoeSOF");
              break;
            case 0x13e:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103b7bb8,"FcoeVersionIsZero");
              break;
            case 0x14a:
              local_28 = FUN_1014b23c(param_1,uVar1,param_2,FUN_103d96bc,"SubportPktTag");
              break;
            case 0x14b:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d8fb0,"SrcVxlanGport");
              break;
            case 0x14c:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b3f94,"DstVxlanGport");
              break;
            case 0x14d:
              local_28 = FUN_1014afa4(param_1,uVar1,param_2,FUN_103d1424,&DAT_1135a1f0);
              break;
            case 0x14f:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d8134,"SrcNivGport");
              break;
            case 0x150:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b3388,"DstNivGport");
              break;
            case 0x151:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b12b0,"DstGport");
              break;
            case 0x183:
              local_28 = FUN_1014b4d4(param_1,uVar1,param_2,FUN_103be6b8,
                                      "IngressInterfaceClassVPort");
              break;
            case 0x184:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103d8d4c,"SrcVlanGport");
              break;
            case 0x185:
              local_28 = FUN_1014d048(param_1,uVar1,param_2,FUN_103b3d30,"DstVlanGport");
            }
            if (((local_28 != 0) && (iVar2 = FUN_10761348(&DAT_11858c08,0x2000100), iVar2 != 0)) &&
               (PTR_FUN_11e454ac != (undefined *)0x0)) {
              (*(code *)PTR_FUN_11e454ac)
                        ("FP(unit %d) Error: Qualifier installation error: %s\n",param_1,__s1);
            }
          }
        }
      }
    }
  }
  return local_28;
}



/* === FUN_10075880 (size=640) === */

int FUN_10075880(int param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint local_38;
  int local_34;
  undefined4 local_28;
  undefined4 local_24 [3];
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  uVar1 = FUN_1007358c(param_1,*(undefined4 *)(param_4 + 4));
  FUN_10073628(uVar1,local_24,&local_28);
  if (*(int *)(local_14 + 0x1c0) == 1) {
    local_38 = *(uint *)(local_c + 8);
    local_34 = FUN_103d1694(*(undefined4 *)(local_18 + 4),local_10,local_28,0xffffffff);
  }
  else {
    if (*(int *)(local_c + 8) == 0) {
      local_38 = 0;
    }
    else {
      local_38 = FUN_1006f430(local_18,local_c);
    }
    local_34 = FUN_103b35ec(*(undefined4 *)(local_18 + 4),local_10,local_24[0],0xffffffff,local_28,
                            0xffffffff);
  }
  if (local_34 < 0) {
    if (0 < DAT_11e45404) {
      uVar1 = FUN_10046f5c();
      if ((local_34 < 1) && (-0x13 < local_34)) {
        iVar2 = -local_34;
      }
      else {
        iVar2 = 0x13;
      }
      FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_OutPort failed %s\n",0x32,uVar1,"hal_acl_bcm.c"
                   ,0x2dd,(&PTR_DAT_11e43a78)[iVar2]);
    }
  }
  else if (((local_38 != 0) &&
           (local_34 = FUN_103d27f0(*(undefined4 *)(local_18 + 4),local_10,local_38 & 0xffff,0xffff)
           , local_34 < 0)) && (0 < DAT_11e45404)) {
    uVar1 = FUN_10046f5c();
    if ((local_34 < 1) && (-0x13 < local_34)) {
      iVar2 = -local_34;
    }
    else {
      iVar2 = 0x13;
    }
    FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_Vlan failed %s\n",0x2f,uVar1,"hal_acl_bcm.c",
                 0x2e7,(&PTR_DAT_11e43a78)[iVar2]);
  }
  return local_34;
}



/* === FUN_100769bc (size=5792) === */

int FUN_100769bc(int param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int local_118;
  int local_114;
  undefined4 local_fc;
  int local_f8;
  int local_f4;
  int local_f0;
  int local_ec;
  undefined1 auStack_e8 [16];
  int local_d8;
  undefined2 local_d4;
  undefined4 local_d0;
  undefined2 local_cc;
  undefined8 local_c8;
  undefined8 local_c0;
  int local_b8;
  undefined4 local_b4;
  int *local_b0;
  undefined4 local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  undefined4 local_8c;
  uint local_88;
  undefined4 local_84;
  uint local_80;
  undefined4 local_7c;
  uint local_78;
  undefined4 local_74;
  undefined4 local_70;
  uint local_6c;
  undefined4 local_68;
  uint local_64;
  undefined4 local_60;
  uint local_5c;
  undefined4 local_58;
  uint local_54;
  undefined4 local_50;
  uint local_4c;
  
  uVar4 = *(undefined4 *)(param_3[0x7e] + 4);
  local_b8 = param_1;
  local_b4 = param_2;
  local_b0 = param_3;
  local_ac = param_4;
  if ((-2 < DAT_11e45404) && (DAT_11e456e8 == 4)) {
    uVar1 = FUN_10046f5c();
    FUN_10047040(0xffffffff,"%s %s:%d %s key mask 0x%llx, type %d\n",0x26,uVar1,"hal_acl_bcm.c",
                 0x3ea,"hal_bcm_acl_entry_match_add",uVar1,*(undefined8 *)(local_b0 + 2),local_ac);
  }
  local_118 = FUN_10075e78(local_b8,local_b0,uVar4);
  if (-1 < local_118) {
    switch(local_ac) {
    case 0:
    case 2:
    case 3:
      local_80 = local_b0[2] & 1;
      local_7c = 0;
      if (local_80 != 0) {
        FUN_1007352c(&local_fc,param_3 + 0x32);
        uVar1 = FUN_112b0be0(param_3[0x36]);
        if ((-2 < DAT_11e45404) && (DAT_11e456e8 == 4)) {
          uVar2 = FUN_10046f5c();
          FUN_10047040(0xffffffff,"%s %s:%d %s src ip 0x%x\n",0x19,uVar2,"hal_acl_bcm.c",0x42e,
                       "hal_bcm_acl_entry_match_add",local_fc);
        }
        local_118 = FUN_103d69cc(*(undefined4 *)(local_b8 + 4),uVar4,local_fc,uVar1);
        if (local_118 < 0) {
          if (DAT_11e45404 < 1) {
            return local_118;
          }
          uVar4 = FUN_10046f5c();
          if ((local_118 < 1) && (-0x13 < local_118)) {
            iVar3 = -local_118;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_SrcIp failed %s\n",0x30,uVar4,
                       "hal_acl_bcm.c",0x431,(&PTR_DAT_11e43a78)[iVar3]);
          return local_118;
        }
      }
      local_78 = local_b0[2] & 2;
      local_74 = 0;
      if (local_78 != 0) {
        FUN_1007352c(&local_fc,param_3 + 0x37);
        uVar1 = FUN_112b0be0(param_3[0x3b]);
        if ((-2 < DAT_11e45404) && (DAT_11e456e8 == 4)) {
          uVar2 = FUN_10046f5c();
          FUN_10047040(0xffffffff,"%s %s:%d %s dst ip 0x%x\n",0x19,uVar2,"hal_acl_bcm.c",0x43a,
                       "hal_bcm_acl_entry_match_add",local_fc);
        }
        local_118 = FUN_103b1784(*(undefined4 *)(local_b8 + 4),uVar4,local_fc,uVar1);
        if (local_118 < 0) {
          if (DAT_11e45404 < 1) {
            return local_118;
          }
          uVar4 = FUN_10046f5c();
          if ((local_118 < 1) && (-0x13 < local_118)) {
            iVar3 = -local_118;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_DstIp failed %s\n",0x30,uVar4,
                       "hal_acl_bcm.c",0x43d,(&PTR_DAT_11e43a78)[iVar3]);
          return local_118;
        }
      }
      iVar3 = FUN_10076944(local_b0);
      if (((iVar3 != 0) && (*(char *)((int)local_b0 + 0x1b2) == '\0')) &&
         (local_118 = FUN_103c5888(*(undefined4 *)(local_b8 + 4),uVar4,5), local_118 < 0)) {
        if (DAT_11e45404 < 1) {
          return local_118;
        }
        uVar4 = FUN_10046f5c();
        if ((local_118 < 1) && (-0x13 < local_118)) {
          iVar3 = -local_118;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_IpType failed %s\n",0x31,uVar4,
                     "hal_acl_bcm.c",0x44e,(&PTR_DAT_11e43a78)[iVar3]);
        return local_118;
      }
      if (local_b0[0x65] == 0) {
        local_70 = 0;
        local_6c = local_b0[3] & 0x400;
        if ((local_6c != 0) &&
           (local_118 = FUN_103b59f4(*(undefined4 *)(local_b8 + 4),uVar4,
                                     *(undefined2 *)(param_3 + 0x1a),0xffff), local_118 < 0)) {
          if (DAT_11e45404 < 1) {
            return local_118;
          }
          uVar4 = FUN_10046f5c();
          if ((local_118 < 1) && (-0x13 < local_118)) {
            iVar3 = -local_118;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_Ethertype failed %s\n",0x34,uVar4,
                       "hal_acl_bcm.c",0x45c,(&PTR_DAT_11e43a78)[iVar3]);
          return local_118;
        }
      }
      break;
    case 1:
      local_90 = local_b0[2] & 1;
      local_8c = 0;
      if (local_90 != 0) {
        local_f8 = param_3[0x32];
        local_f4 = param_3[0x33];
        local_f0 = param_3[0x34];
        local_ec = param_3[0x35];
        FUN_112b0b58(auStack_e8,param_3[0x36]);
        local_118 = FUN_103d6af8(*(undefined4 *)(local_b8 + 4),uVar4,&local_f8,auStack_e8);
        if (local_118 < 0) {
          if (DAT_11e45404 < 1) {
            return local_118;
          }
          uVar4 = FUN_10046f5c();
          if ((local_118 < 1) && (-0x13 < local_118)) {
            iVar3 = -local_118;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_SrcIp6 failed %s\n",0x31,uVar4,
                       "hal_acl_bcm.c",0x40d,(&PTR_DAT_11e43a78)[iVar3]);
          return local_118;
        }
      }
      local_88 = local_b0[2] & 2;
      local_84 = 0;
      if (local_88 != 0) {
        local_f8 = param_3[0x37];
        local_f4 = param_3[0x38];
        local_f0 = param_3[0x39];
        local_ec = param_3[0x3a];
        FUN_112b0b58(auStack_e8,param_3[0x3b]);
        local_118 = FUN_103b18b0(*(undefined4 *)(local_b8 + 4),uVar4,&local_f8,auStack_e8);
        if (local_118 < 0) {
          if (DAT_11e45404 < 1) {
            return local_118;
          }
          uVar4 = FUN_10046f5c();
          if ((local_118 < 1) && (-0x13 < local_118)) {
            iVar3 = -local_118;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_DstIp6 failed %s\n",0x31,uVar4,
                       "hal_acl_bcm.c",0x418,(&PTR_DAT_11e43a78)[iVar3]);
          return local_118;
        }
      }
      if ((*(char *)((int)local_b0 + 0x1b2) == '\0') &&
         (local_118 = FUN_103c5888(*(undefined4 *)(local_b8 + 4),uVar4,10), local_118 < 0)) {
        if (DAT_11e45404 < 1) {
          return local_118;
        }
        uVar4 = FUN_10046f5c();
        if ((local_118 < 1) && (-0x13 < local_118)) {
          iVar3 = -local_118;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_IpType failed %s\n",0x31,uVar4,
                     "hal_acl_bcm.c",0x421,(&PTR_DAT_11e43a78)[iVar3]);
        return local_118;
      }
      break;
    case 4:
      local_c8 = DAT_11329750;
      FUN_1002d608(&local_c8,0);
      FUN_1002d608(&local_c8,1);
      FUN_1002d608(&local_c8,3);
      FUN_1002d608(&local_c8,0xb);
      local_a8 = ~local_c8._0_4_;
      local_a4 = ~local_c8._4_4_;
      local_a0 = local_b0[2] & local_a8;
      local_9c = local_b0[3] & local_a4;
      if (local_a0 != 0 || local_9c != 0) {
        if (0 < DAT_11e45404) {
          uVar4 = FUN_10046f5c();
          FUN_10047040(1,"%s %s:%d ERR Only support interface based SPAN\n",0x30,uVar4,
                       "hal_acl_bcm.c",0x3f9);
        }
        return -4;
      }
      local_98 = local_b0[2] & local_c8._0_4_;
      local_94 = local_b0[3] & local_c8._4_4_;
      if (local_98 != 0 || local_94 != 0) {
        return local_118;
      }
      if (0 < DAT_11e45404) {
        uVar4 = FUN_10046f5c();
        FUN_10047040(1,"%s %s:%d ERR SPAN not bound to any interfaces\n",0x2f,uVar4,"hal_acl_bcm.c",
                     0x3fe);
      }
      return -4;
    }
    local_cc = 0xffff;
    local_d0 = 0xffffffff;
    local_68 = 0;
    local_64 = local_b0[3] & 0x100;
    if (local_64 != 0) {
      local_d8 = param_3[0x14];
      local_d4 = *(undefined2 *)(param_3 + 0x15);
      local_d0 = *(undefined4 *)((int)param_3 + 0x56);
      local_cc = *(undefined2 *)((int)param_3 + 0x5a);
      local_118 = FUN_103d7554(*(undefined4 *)(local_b8 + 4),uVar4,&local_d8,&local_d0);
      if (local_118 < 0) {
        if (DAT_11e45404 < 1) {
          return local_118;
        }
        uVar4 = FUN_10046f5c();
        if ((local_118 < 1) && (-0x13 < local_118)) {
          iVar3 = -local_118;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_SrcMac failed %s\n",0x31,uVar4,
                     "hal_acl_bcm.c",0x46f,(&PTR_DAT_11e43a78)[iVar3]);
        return local_118;
      }
    }
    local_60 = 0;
    local_5c = local_b0[3] & 0x200;
    if (local_5c != 0) {
      local_d8 = param_3[0x17];
      local_d4 = *(undefined2 *)(param_3 + 0x18);
      local_d0 = *(undefined4 *)((int)param_3 + 0x62);
      local_cc = *(undefined2 *)((int)param_3 + 0x66);
      local_118 = FUN_103b27cc(*(undefined4 *)(local_b8 + 4),uVar4,&local_d8,&local_d0);
      if (local_118 < 0) {
        if (DAT_11e45404 < 1) {
          return local_118;
        }
        uVar4 = FUN_10046f5c();
        if ((local_118 < 1) && (-0x13 < local_118)) {
          iVar3 = -local_118;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_DstMac failed %s\n",0x31,uVar4,
                     "hal_acl_bcm.c",0x479,(&PTR_DAT_11e43a78)[iVar3]);
        return local_118;
      }
    }
    local_58 = 0;
    local_54 = local_b0[3] & 0x80000000;
    if ((local_54 == 0) ||
       (local_118 = FUN_103c4f04(*(undefined4 *)(local_b8 + 4),uVar4,
                                 *(ushort *)(param_3 + 0x3c) & 0xff,0xff), -1 < local_118)) {
      local_50 = 0;
      local_4c = local_b0[3] & 0x4000000;
      if ((local_4c == 0) ||
         (local_118 = FUN_103da050(*(undefined4 *)(local_b8 + 4),uVar4,
                                   *(undefined1 *)((int)param_3 + 0xf9),
                                   *(undefined1 *)((int)param_3 + 0xfa)), -1 < local_118)) {
        if (((local_b0[3] & 0x40000000U) == 0) ||
           (local_118 = FUN_103dc238(*(undefined4 *)(local_b8 + 4),uVar4,
                                     *(undefined1 *)(param_3 + 0x3e),0xff), -1 < local_118)) {
          if (((local_b0[3] & 0x8000000U) == 0) ||
             (local_118 = FUN_103b00d0(*(undefined4 *)(local_b8 + 4),uVar4,
                                       (param_3[0x41] & 0x3fU) << 2,0xfc), -1 < local_118)) {
            if ((local_b0[2] & 8U) != 0) {
              local_118 = FUN_103b105c(*(undefined4 *)(local_b8 + 4),uVar4,
                                       *(undefined1 *)(param_3 + 0x42),
                                       *(undefined1 *)((int)param_3 + 0x109));
              if (local_118 < 0) {
                if (DAT_11e45404 < 1) {
                  return local_118;
                }
                uVar4 = FUN_10046f5c();
                if ((local_118 < 1) && (-0x13 < local_118)) {
                  iVar3 = -local_118;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_DstClassL3 failed %s\n",0x35,uVar4,
                             "hal_acl_bcm.c",0x4af,(&PTR_DAT_11e43a78)[iVar3]);
                return local_118;
              }
              if ((*(char *)(param_3 + 0x42) == '\0') &&
                 (local_118 = FUN_103c647c(*(undefined4 *)(local_b8 + 4),uVar4,1,1), local_118 < 0))
              {
                if (DAT_11e45404 < 1) {
                  return local_118;
                }
                uVar4 = FUN_10046f5c();
                if ((local_118 < 1) && (-0x13 < local_118)) {
                  iVar3 = -local_118;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_L2CacheHit failed %s\n",0x35,uVar4,
                             "hal_acl_bcm.c",0x4b9,(&PTR_DAT_11e43a78)[iVar3]);
                return local_118;
              }
            }
            if ((local_b0[3] & 0x20000000U) != 0) {
              local_114 = 0;
              if ((param_3[0x3d] & 4U) == 0) {
                if (((param_3[0x3d] & 1U) == 0) || ((param_3[0x3d] & 2U) == 0)) {
                  if ((param_3[0x3d] & 2U) == 0) {
                    if ((param_3[0x3d] & 1U) != 0) {
                      local_114 = 0;
                    }
                  }
                  else {
                    local_114 = 1;
                  }
                }
                else {
                  local_114 = 2;
                }
              }
              else {
                local_114 = 3;
              }
              if ((local_114 != 0) &&
                 (local_118 = FUN_103c4a6c(*(undefined4 *)(local_b8 + 4),uVar4,local_114),
                 local_118 < 0)) {
                if (DAT_11e45404 < 1) {
                  return local_118;
                }
                uVar4 = FUN_10046f5c();
                if ((local_118 < 1) && (-0x13 < local_118)) {
                  iVar3 = -local_118;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_ipfrag failed %s\n",0x31,uVar4,
                             "hal_acl_bcm.c",0x4d0,(&PTR_DAT_11e43a78)[iVar3]);
                return local_118;
              }
            }
            if (((((((local_b0[2] & 0x20U) == 0) && ((local_b0[2] & 0x40U) == 0)) &&
                  ((local_b0[2] & 0x100U) == 0)) && ((local_b0[2] & 0x800U) == 0)) ||
                (local_118 = FUN_100752c4(local_b8,local_b4,local_b0,uVar4), -1 < local_118)) &&
               ((*local_b0 == 0 && (local_b0[0x65] == 0)))) {
              local_c0 = DAT_11329750;
              FUN_1002d608(&local_c0,0);
              FUN_1002d608(&local_c0,3);
              if (((local_b0[2] == local_c0._0_4_) &&
                  ((local_b0[3] == local_c0._4_4_ &&
                   (local_118 = FUN_103c647c(*(undefined4 *)(local_b8 + 4),uVar4,1,1), local_118 < 0
                   )))) && (0 < DAT_11e45404)) {
                uVar4 = FUN_10046f5c();
                if ((local_118 < 1) && (-0x13 < local_118)) {
                  iVar3 = -local_118;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_L2CacheHit failed %s\n",0x35,uVar4,
                             "hal_acl_bcm.c",0x4ee,(&PTR_DAT_11e43a78)[iVar3]);
              }
            }
          }
          else if (0 < DAT_11e45404) {
            uVar4 = FUN_10046f5c();
            if ((local_118 < 1) && (-0x13 < local_118)) {
              iVar3 = -local_118;
            }
            else {
              iVar3 = 0x13;
            }
            FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_DSCP failed %s\n",0x2f,uVar4,
                         "hal_acl_bcm.c",0x4a1,(&PTR_DAT_11e43a78)[iVar3]);
          }
        }
        else if (0 < DAT_11e45404) {
          uVar4 = FUN_10046f5c();
          if ((local_118 < 1) && (-0x13 < local_118)) {
            iVar3 = -local_118;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_Ttl failed %s\n",0x2e,uVar4,"hal_acl_bcm.c"
                       ,0x497,(&PTR_DAT_11e43a78)[iVar3]);
        }
      }
      else if (0 < DAT_11e45404) {
        uVar4 = FUN_10046f5c();
        if ((local_118 < 1) && (-0x13 < local_118)) {
          iVar3 = -local_118;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_Tos failed %s\n",0x2e,uVar4,"hal_acl_bcm.c",
                     0x48e,(&PTR_DAT_11e43a78)[iVar3]);
      }
    }
    else if (0 < DAT_11e45404) {
      uVar4 = FUN_10046f5c();
      if ((local_118 < 1) && (-0x13 < local_118)) {
        iVar3 = -local_118;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_IpProtocol failed %s\n",0x35,uVar4,
                   "hal_acl_bcm.c",0x484,(&PTR_DAT_11e43a78)[iVar3]);
    }
  }
  return local_118;
}



/* === FUN_100752c4 (size=1468) === */

int FUN_100752c4(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint *puVar2;
  int iVar3;
  int local_48;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  int local_38;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  
  local_48 = 0;
  puVar2 = (uint *)(param_3 + 0x10c);
  local_38 = param_1;
  local_34 = param_2;
  local_30 = param_3;
  local_2c = param_4;
  if ((*(uint *)(param_3 + 8) & 0x20) != 0) {
    if (*puVar2 < *(uint *)(param_3 + 0x110)) {
      local_3e = (undefined2)*puVar2;
      local_3c = (undefined2)*(undefined4 *)(param_3 + 0x110);
      local_40 = 1;
      local_48 = FUN_1007482c(param_1,param_3,param_2,&local_40,param_4,0);
    }
    else if ((*puVar2 == *(uint *)(param_3 + 0x110)) &&
            (local_48 = FUN_103c9e4c(*(undefined4 *)(param_1 + 4),param_4,*puVar2,0xffff),
            local_48 < 0)) {
      if (DAT_11e45404 < 1) {
        return local_48;
      }
      uVar1 = FUN_10046f5c();
      if ((local_48 < 1) && (-0x13 < local_48)) {
        iVar3 = -local_48;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_L4SrcPort failed %s\n",0x34,uVar1,
                   "hal_acl_bcm.c",0x287,(&PTR_DAT_11e43a78)[iVar3]);
      return local_48;
    }
  }
  if ((*(uint *)(local_30 + 8) & 0x40) != 0) {
    if (*(uint *)(param_3 + 0x114) < *(uint *)(param_3 + 0x118)) {
      local_3e = (undefined2)*(undefined4 *)(param_3 + 0x114);
      local_3c = (undefined2)*(undefined4 *)(param_3 + 0x118);
      local_40 = 2;
      local_48 = FUN_1007482c(local_38,local_30,local_34,&local_40,local_2c,0);
    }
    else if ((*(int *)(param_3 + 0x114) == *(int *)(param_3 + 0x118)) &&
            (local_48 = FUN_103c9728(*(undefined4 *)(local_38 + 4),local_2c,
                                     *(undefined4 *)(param_3 + 0x114),0xffff), local_48 < 0)) {
      if (DAT_11e45404 < 1) {
        return local_48;
      }
      uVar1 = FUN_10046f5c();
      if ((local_48 < 1) && (-0x13 < local_48)) {
        iVar3 = -local_48;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_L4DstPort failed %s\n",0x34,uVar1,
                   "hal_acl_bcm.c",0x29a,(&PTR_DAT_11e43a78)[iVar3]);
      return local_48;
    }
  }
  if (((*(uint *)(local_30 + 8) & 0x100) == 0) ||
     (local_48 = FUN_103d992c(*(undefined4 *)(local_38 + 4),local_2c,
                              *(undefined1 *)(param_3 + 0x11c),*(undefined1 *)(param_3 + 0x11d)),
     -1 < local_48)) {
    if ((*(uint *)(local_30 + 8) & 0x800) != 0) {
      if ((*(uint *)(local_30 + 8) & 0x1000) == 0) {
        local_48 = FUN_103bcf8c(*(undefined4 *)(local_38 + 4),local_2c,
                                (uint)*(byte *)(param_3 + 0x124) << 8,0xff00);
      }
      else {
        local_48 = FUN_103bcf8c(*(undefined4 *)(local_38 + 4),local_2c,
                                *(undefined2 *)(param_3 + 0x124),0xffff);
      }
      if ((local_48 < 0) && (0 < DAT_11e45404)) {
        uVar1 = FUN_10046f5c();
        if ((local_48 < 1) && (-0x13 < local_48)) {
          iVar3 = -local_48;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_IcmpTypeCode failed %s\n",0x37,uVar1,
                     "hal_acl_bcm.c",0x2b6,(&PTR_DAT_11e43a78)[iVar3]);
      }
    }
  }
  else if (0 < DAT_11e45404) {
    uVar1 = FUN_10046f5c();
    if ((local_48 < 1) && (-0x13 < local_48)) {
      iVar3 = -local_48;
    }
    else {
      iVar3 = 0x13;
    }
    FUN_10047040(1,"%s %s:%d ERR bcm_field_qualify_TcpControl failed %s\n",0x35,uVar1,
                 "hal_acl_bcm.c",0x2a6,(&PTR_DAT_11e43a78)[iVar3]);
  }
  return local_48;
}



/* === FUN_1038e6b0 (size=280) === */

undefined4 FUN_1038e6b0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11853ac0)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_cosq_config_set",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === FUN_1038e7c8 (size=328) === */

undefined4
FUN_1038e7c8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined4 local_38;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    FUN_1038a5a4(param_1,&local_24);
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11853ac8)[iVar1])(param_1,local_24,local_20,local_1c,local_18);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_cosq_control_get",5,3,param_1,local_24,local_20,local_38);
  }
  return local_38;
}



/* === FUN_1038e910 (size=328) === */

undefined4
FUN_1038e910(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined4 local_38;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    FUN_1038a5a4(param_1,&local_24);
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11853ad0)[iVar1])(param_1,local_24,local_20,local_1c,local_18);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_cosq_control_set",5,3,param_1,local_24,local_20,local_38);
  }
  return local_38;
}



/* === FUN_10eedbdc (size=4172) === */

undefined4 FUN_10eedbdc(int param_1,undefined4 *param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  int *piVar7;
  int iVar8;
  undefined4 uVar9;
  uint local_98;
  uint local_94;
  int aiStack_60 [4];
  int aiStack_50 [4];
  int aiStack_40 [4];
  int aiStack_30 [6];
  int local_18;
  undefined4 *local_14;
  uint *local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  for (local_94 = 0; (int)local_94 < 4; local_94 = local_94 + 1) {
    aiStack_40[local_94] = 0;
    aiStack_50[local_94] = 0;
    aiStack_60[local_94] = 0;
    aiStack_30[local_94] = 0;
  }
  iVar5 = (&DAT_1212b9c4)[local_18] + 4;
  uVar1 = local_10[5];
  for (local_94 = 0; local_94 < local_10[8]; local_94 = local_94 + 1) {
    puVar6 = local_14 + local_94 * 10 + 1;
    if ((((*puVar6 & 0xbfffffff) != 0) && ((*puVar6 & 0x40000000) != 0)) &&
       (local_14[local_94 * 10 + 4] = (int)((*puVar6 & 0xbfffffff) * uVar1) / 10000,
       (*local_10 & 8) != 0)) {
      local_14[local_94 * 10 + 9] =
           (int)(((longlong)(int)(*puVar6 & 0xbfffffff) * (longlong)(int)local_10[9] & 0xffffffffU)
                / 10000);
    }
  }
  for (local_98 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x5154);
      (-1 < (int)local_98 && ((int)local_98 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x5158)));
      local_98 = local_98 + 1) {
    if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                   (((int)local_98 >> 5) + (uint)((int)local_98 < 0 && (local_98 & 0x1f) != 0) +
                   0x1454) * 4 + 0xc) &
        1 << (local_98 +
              (((int)local_98 >> 5) + (uint)((int)local_98 < 0 && (local_98 & 0x1f) != 0)) * -0x20 &
             0x3f)) != 0) {
      for (local_94 = 0; local_94 < local_10[7]; local_94 = local_94 + 1) {
        if ((local_14[local_98 * 0x91 + local_94 * 0xe + 0x30] != -1) &&
           (local_14[local_98 * 0x91 + local_94 * 0xe + 0x31] != -1)) {
          local_14[local_98 * 0x91 + local_94 * 0xe + 0x2f] =
               local_14[local_98 * 0x91 + local_94 * 0xe + 0x32] +
               (*(int *)(iVar5 + (local_98 + 0x1894) * 4) *
                (local_14[local_98 * 0x91 + local_94 * 0xe + 0x30] +
                local_14[local_98 * 0x91 + local_94 * 0xe + 0x31]) * 2) / 0x142440;
        }
      }
    }
  }
  for (local_98 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x5154);
      (puVar3 = local_14, -1 < (int)local_98 &&
      ((int)local_98 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x5158))); local_98 = local_98 + 1) {
    if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                   (((int)local_98 >> 5) + (uint)((int)local_98 < 0 && (local_98 & 0x1f) != 0) +
                   0x1454) * 4 + 0xc) &
        1 << (local_98 +
              (((int)local_98 >> 5) + (uint)((int)local_98 < 0 && (local_98 & 0x1f) != 0)) * -0x20 &
             0x3f)) != 0) {
      for (local_94 = 0; local_94 < local_10[7]; local_94 = local_94 + 1) {
        piVar7 = puVar3 + local_98 * 0x91 + local_94 * 0xe + 0x2d;
        aiStack_60[*piVar7] = aiStack_60[*piVar7] + piVar7[2];
        aiStack_50[*piVar7] = aiStack_50[*piVar7] + piVar7[1];
      }
      for (local_94 = 0; local_94 < local_10[8]; local_94 = local_94 + 1) {
        aiStack_50[local_94] = aiStack_50[local_94] + puVar3[local_98 * 0x91 + local_94 * 3 + 0xae];
      }
      for (local_94 = 0; (int)local_94 < *(int *)(iVar5 + (local_98 + 0x1d04) * 4 + 8);
          local_94 = local_94 + 1) {
        iVar4 = puVar3[local_98 * 0x91 + 0x9d] + local_94 * 0x40;
        if ((*(int *)(iVar4 + 0x30) == -1) || (*(int *)(iVar4 + 0x34) == 0)) {
          aiStack_40[*(int *)(iVar4 + 4)] = aiStack_40[*(int *)(iVar4 + 4)] + *(int *)(iVar4 + 8);
        }
        aiStack_30[*(int *)(iVar4 + 4)] = aiStack_30[*(int *)(iVar4 + 4)] + *(int *)(iVar4 + 0x38);
      }
      for (local_94 = 0; (int)local_94 < *(int *)(iVar5 + (local_98 + 0x1e08) * 4 + 8);
          local_94 = local_94 + 1) {
        iVar4 = puVar3[local_98 * 0x91 + 0x9d] +
                (*(int *)(iVar5 + (local_98 + 0x1d04) * 4 + 8) + local_94) * 0x40;
        if ((*(int *)(iVar4 + 0x30) == -1) || (*(int *)(iVar4 + 0x34) == 0)) {
          aiStack_40[*(int *)(iVar4 + 4)] = aiStack_40[*(int *)(iVar4 + 4)] + *(int *)(iVar4 + 8);
        }
      }
    }
  }
  if ((*local_10 & 4) != 0) {
    for (local_94 = 0; (int)local_94 < 0xb; local_94 = local_94 + 1) {
      aiStack_40[local_14[local_94 * 7 + 0x51a9]] =
           aiStack_40[local_14[local_94 * 7 + 0x51a9]] + local_14[local_94 * 7 + 0x51aa];
    }
  }
  iVar4 = FUN_11310fbc(0x100,&DAT_11412708);
  if (iVar4 == 0) {
    uVar9 = 0xfffffffe;
  }
  else {
    for (local_94 = 0; (int)local_94 < 0x100; local_94 = local_94 + 1) {
      *(undefined1 *)(iVar4 + local_94) = 0;
    }
    for (local_98 = *(uint *)((&DAT_1212b9c4)[local_18] + 0x5154);
        (puVar3 = local_14, -1 < (int)local_98 &&
        ((int)local_98 <= *(int *)((&DAT_1212b9c4)[local_18] + 0x5158))); local_98 = local_98 + 1) {
      if ((*(uint *)((&DAT_1212b9c4)[local_18] +
                     (((int)local_98 >> 5) + (uint)((int)local_98 < 0 && (local_98 & 0x1f) != 0) +
                     0x1454) * 4 + 0xc) &
          1 << (local_98 +
                (((int)local_98 >> 5) + (uint)((int)local_98 < 0 && (local_98 & 0x1f) != 0)) * -0x20
               & 0x3f)) != 0) {
        for (local_94 = 0; (int)local_94 < *(int *)(iVar5 + (local_98 + 0x1d04) * 4 + 8);
            local_94 = local_94 + 1) {
          iVar8 = puVar3[local_98 * 0x91 + 0x9d] + local_94 * 0x40;
          if (*(int *)(iVar8 + 0x30) != -1) {
            iVar2 = *(int *)(iVar8 + 0x30);
            if (*(char *)(iVar4 + iVar2) == '\0') {
              aiStack_40[*(int *)(iVar8 + 4)] =
                   aiStack_40[*(int *)(iVar8 + 4)] + local_14[iVar2 * 9 + 0x48a9];
            }
            *(byte *)(iVar4 + iVar2) =
                 *(byte *)(iVar4 + iVar2) | (byte)(1 << (*(uint *)(iVar8 + 4) & 0x3f));
          }
        }
        for (local_94 = 0; (int)local_94 < *(int *)(iVar5 + (local_98 + 0x1e08) * 4 + 8);
            local_94 = local_94 + 1) {
          iVar8 = puVar3[local_98 * 0x91 + 0x9d] +
                  (*(int *)(iVar5 + (local_98 + 0x1d04) * 4 + 8) + local_94) * 0x40;
          if (*(int *)(iVar8 + 0x30) != -1) {
            iVar2 = *(int *)(iVar8 + 0x30);
            if (*(char *)(iVar4 + iVar2) == '\0') {
              aiStack_40[*(int *)(iVar8 + 4)] =
                   aiStack_40[*(int *)(iVar8 + 4)] + local_14[iVar2 * 9 + 0x48a9];
            }
            *(byte *)(iVar4 + iVar2) =
                 *(byte *)(iVar4 + iVar2) | (byte)(1 << (*(uint *)(iVar8 + 4) & 0x3f));
          }
        }
      }
    }
    for (local_94 = 0; puVar3 = local_14, (int)local_94 < 0x200; local_94 = local_94 + 1) {
      if (0 < (int)local_14[local_94 * 0x10 + 0x51f6]) {
        if (local_14[local_94 * 0x10 + 0x5202] == -1) {
          aiStack_40[local_14[local_94 * 0x10 + 0x51f7]] =
               aiStack_40[local_14[local_94 * 0x10 + 0x51f7]] +
               local_14[local_94 * 0x10 + 0x51f8] * local_14[local_94 * 0x10 + 0x51f6];
        }
        else {
          iVar5 = local_14[local_94 * 0x10 + 0x5202];
          if (*(char *)(iVar4 + iVar5) == '\0') {
            aiStack_40[local_14[local_94 * 0x10 + 0x51f7]] =
                 aiStack_40[local_14[local_94 * 0x10 + 0x51f7]] + local_14[iVar5 * 9 + 0x48a9];
          }
          *(byte *)(iVar4 + iVar5) =
               *(byte *)(iVar4 + iVar5) | (byte)(1 << (puVar3[local_94 * 0x10 + 0x51f7] & 0x3f));
        }
      }
    }
    for (local_94 = 0; (int)local_94 < 0x100; local_94 = local_94 + 1) {
      if ((*(byte *)(iVar4 + local_94) & *(char *)(iVar4 + local_94) - 1U) != 0) {
        FUN_10760b7c("Queue belonging to same group use different Pools !!");
        FUN_11310ee4(iVar4);
        return 0xfffffffc;
      }
    }
    FUN_11310ee4(iVar4);
    for (local_94 = 0; local_94 < local_10[8]; local_94 = local_94 + 1) {
      local_14[local_94 * 10 + 7] = aiStack_40[local_94];
      local_14[local_94 * 10 + 6] = aiStack_60[local_94];
      local_14[local_94 * 10 + 5] = aiStack_50[local_94];
      local_14[local_94 * 10 + 8] = aiStack_30[local_94];
    }
    iVar5 = FUN_10760db0(0x10000);
    if (iVar5 != 0) {
      FUN_10760b7c("MMU buffer usage:\n");
      FUN_10760b7c("  Global headroom: %d\n",*local_14);
      for (local_94 = 0; puVar3 = local_14, local_94 < local_10[8]; local_94 = local_94 + 1) {
        if ((local_14[local_94 * 10 + 1] & 0xbfffffff) != 0) {
          FUN_10760b7c("  Pool %d total prigroup guarantee: %d\n",local_94,
                       local_14[local_94 * 10 + 5]);
          FUN_10760b7c("  Pool %d total prigroup headroom: %d\n",local_94,puVar3[local_94 * 10 + 6])
          ;
          FUN_10760b7c("  Pool %d total queue guarantee: %d\n",local_94,puVar3[local_94 * 10 + 7]);
          FUN_10760b7c("  Pool %d total mcq entry reserved: %d\n",local_94,puVar3[local_94 * 10 + 8]
                      );
        }
      }
    }
    uVar9 = 0;
  }
  return uVar9;
}



/* NO FUNCTION at 0x103f4ddc */

