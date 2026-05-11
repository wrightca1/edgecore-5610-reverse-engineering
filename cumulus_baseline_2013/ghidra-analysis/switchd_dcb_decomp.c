/* DCB/DMA Vector management decompilation */

/* === FUN_10051be0 (size=15376) === */

/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_10051be0(int param_1,undefined4 param_2,char param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char cVar8;
  uint uVar5;
  undefined2 uVar7;
  undefined4 uVar6;
  void *__ptr;
  uint local_610;
  uint local_60c;
  int local_608;
  uint local_604;
  int local_600;
  int local_5fc;
  int local_5f8;
  int local_5f4;
  undefined4 local_5f0;
  undefined4 local_5ec;
  uint local_5e8;
  int local_5e4;
  int local_5e0;
  int local_5dc;
  int local_5d8;
  int local_5d4;
  uint local_5d0;
  undefined1 auStack_5a4 [4];
  int local_5a0;
  undefined4 local_59c;
  uint auStack_594 [168];
  undefined1 auStack_2f4 [16];
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  int local_2d4;
  undefined4 local_288 [3];
  undefined4 local_27c;
  uint local_260;
  uint local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  uint local_24c;
  uint local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  int local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined1 auStack_214 [4];
  uint local_210 [2];
  undefined2 local_208;
  undefined4 local_206;
  undefined2 local_202;
  undefined4 local_200;
  undefined4 local_1f0;
  uint auStack_170 [32];
  uint local_f0 [4];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  int local_d0;
  undefined4 local_cc;
  char local_c8;
  undefined8 local_c0 [2];
  uint local_b0;
  uint local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  uint local_90;
  uint local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  
  local_608 = 0;
  local_d0 = param_1;
  local_cc = param_2;
  local_c8 = param_3;
  FUN_1131136c(FUN_10050ea8);
  FUN_112b0180(auStack_5a4);
  FUN_103e17d0(*(undefined4 *)(param_1 + 4),auStack_5a4);
  if (-2 < DAT_11e45404) {
    uVar2 = FUN_10046f5c();
    FUN_10047040(0xffffffff,"%s %s:%d Attached to device: %04x.%d\n",0x26,uVar2,&DAT_11322924,0x2f1,
                 local_5a0,local_59c);
  }
  FUN_10436bb0(*(undefined4 *)(param_1 + 4),FUN_100514b8,0);
  FUN_112b3fa0(auStack_594);
  iVar3 = FUN_10413a78(*(undefined4 *)(param_1 + 4),auStack_594);
  if (iVar3 < 0) {
    if (-1 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      if ((iVar3 < 1) && (-0x13 < iVar3)) {
        iVar3 = -iVar3;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(0,"%s %s:%d CRIT bcm_port_config_get failed: %s\n",0x2e,uVar2,&DAT_11322924,0x2fc
                   ,(&PTR_DAT_11e43a78)[iVar3]);
    }
    uVar2 = 0;
  }
  else {
    iVar3 = *(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0xe0cc);
    if (iVar3 - (iVar3 / (iVar3 + 1)) * (iVar3 + 1) != iVar3) {
      FUN_113113b0("modport_max % (modport_max + 1) == modport_max",&DAT_11322924,0x31c);
    }
    DAT_11e45718 = 0;
    for (local_5f8 = iVar3; 0 < local_5f8; local_5f8 = local_5f8 >> 1) {
      DAT_11e45718 = DAT_11e45718 + 1;
    }
    DAT_11e4571c = iVar3;
    for (local_610 = 0; (int)local_610 < 0x100; local_610 = local_610 + 1) {
      iVar3 = (int)local_610 >> 5;
      if ((auStack_594[iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0) + 0x28] &
          1 << (local_610 + (iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) * -0x20
               & 0x3f)) != 0) {
        iVar4 = FUN_10416c84(*(undefined4 *)(param_1 + 4),local_610,0);
        if (iVar4 < 0) {
          if (-1 < DAT_11e45404) {
            uVar2 = FUN_10046f5c();
            if ((iVar4 < 1) && (-0x13 < iVar4)) {
              iVar4 = -iVar4;
            }
            else {
              iVar4 = 0x13;
            }
            FUN_10047040(0,"%s %s:%d CRIT bcm_port_encap_set failed: %s\n",0x2d,uVar2,&DAT_11322924,
                         0x32a,(&PTR_DAT_11e43a78)[iVar4]);
          }
          return 0;
        }
        iVar4 = iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0);
        auStack_594[iVar4 + 0x28] =
             auStack_594[iVar4 + 0x28] &
             ~(1 << (local_610 +
                     (iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) * -0x20 & 0x3f)
              );
        iVar4 = iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0);
        auStack_594[iVar4 + 0x20] =
             auStack_594[iVar4 + 0x20] |
             1 << (local_610 +
                   (iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) * -0x20 & 0x3f);
        iVar4 = iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0);
        auStack_594[iVar4 + 0x10] =
             auStack_594[iVar4 + 0x10] |
             1 << (local_610 +
                   (iVar3 + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) * -0x20 & 0x3f);
      }
    }
    if (local_5a0 != 0xb845) {
      for (local_610 = 0; (int)local_610 < 0x100; local_610 = local_610 + 1) {
        if ((((auStack_594
               [((int)local_610 >> 5) + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0) + 0x60
               ] & 1 << (local_610 +
                         (((int)local_610 >> 5) +
                         (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) * -0x20 & 0x3f)) !=
              0) && (iVar3 = FUN_10422ca4(*(undefined4 *)(param_1 + 4),local_610,local_210),
                    -1 < iVar3)) &&
           (FUN_104146fc(*(undefined4 *)(param_1 + 4),local_610,0x37,&local_238), local_238 != 1)) {
          if (local_238 != 4) {
            FUN_113113b0("val == 4",&DAT_11322924,0x347);
          }
          for (local_5e8 = 0; (int)local_5e8 < 0x100; local_5e8 = local_5e8 + 1) {
            iVar3 = (int)local_5e8 >> 5;
            if (((local_210[iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0)] &
                 1 << (local_5e8 +
                       (iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0)) * -0x20 &
                      0x3f)) != 0) && (local_5e8 != local_610)) {
              iVar4 = FUN_1041652c(*(undefined4 *)(param_1 + 4),local_5e8,0);
              if (iVar4 < 0) {
                if (-1 < DAT_11e45404) {
                  uVar2 = FUN_10046f5c();
                  if ((iVar4 < 1) && (-0x13 < iVar4)) {
                    iVar4 = -iVar4;
                  }
                  else {
                    iVar4 = 0x13;
                  }
                  FUN_10047040(0,"%s %s:%d CRIT bcm_port_enable failed: %s\n",0x2a,uVar2,
                               &DAT_11322924,0x34e,(&PTR_DAT_11e43a78)[iVar4]);
                }
                return 0;
              }
              iVar4 = iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0);
              auStack_594[iVar4 + 0x20] =
                   auStack_594[iVar4 + 0x20] &
                   ~(1 << (local_5e8 +
                           (iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0)) * -0x20 &
                          0x3f));
              iVar4 = iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0);
              auStack_594[iVar4] =
                   auStack_594[iVar4] &
                   ~(1 << (local_5e8 +
                           (iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0)) * -0x20 &
                          0x3f));
              iVar4 = iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0);
              auStack_594[iVar4 + 8] =
                   auStack_594[iVar4 + 8] &
                   ~(1 << (local_5e8 +
                           (iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0)) * -0x20 &
                          0x3f));
              iVar4 = iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0);
              auStack_594[iVar4 + 0x10] =
                   auStack_594[iVar4 + 0x10] &
                   ~(1 << (local_5e8 +
                           (iVar3 + (uint)((int)local_5e8 < 0 && (local_5e8 & 0x1f) != 0)) * -0x20 &
                          0x3f));
            }
          }
        }
      }
    }
    *(undefined4 *)(param_1 + 8) = 0;
    for (local_5e4 = 0; local_5e4 < 8; local_5e4 = local_5e4 + 1) {
      iVar3 = *(int *)(param_1 + 8);
      iVar4 = FUN_112e9dec(auStack_594[local_5e4 + 0x20]);
      *(int *)(param_1 + 8) = iVar3 + iVar4;
    }
    uVar2 = FUN_1004f6a0(0x100,4,&DAT_11322924,0x35f);
    *(undefined4 *)(param_1 + 0xc) = uVar2;
    uVar2 = FUN_1004f6a0(*(undefined4 *)(param_1 + 8),4,&DAT_11322924,0x361);
    *(undefined4 *)(param_1 + 0x10) = uVar2;
    for (local_610 = 0; (int)local_610 < 0x100; local_610 = local_610 + 1) {
      if ((auStack_594
           [((int)local_610 >> 5) + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0) + 0x20] &
          1 << (local_610 +
                (((int)local_610 >> 5) + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        *(int *)(*(int *)(param_1 + 0xc) + local_610 * 4) = local_608;
        *(uint *)(*(int *)(param_1 + 0x10) + local_608 * 4) = local_610;
        local_608 = local_608 + 1;
      }
    }
    local_610 = 0;
    for (local_5e0 = 0; local_5e0 < 8; local_5e0 = local_5e0 + 1) {
      iVar3 = FUN_112e9dec(auStack_594[local_5e0 + 0x58]);
      local_610 = local_610 + iVar3;
    }
    if (local_610 != 1) {
      FUN_113113b0(&DAT_11322f68,&DAT_11322924,0x368);
    }
    for (local_610 = 0; (int)local_610 < 0x100; local_610 = local_610 + 1) {
      if ((auStack_594
           [((int)local_610 >> 5) + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0) + 0x58] &
          1 << (local_610 +
                (((int)local_610 >> 5) + (uint)((int)local_610 < 0 && (local_610 & 0x1f) != 0)) *
                -0x20 & 0x3f)) != 0) {
        *(uint *)(param_1 + 0x14) = local_610;
      }
    }
    if (2 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      FUN_10047040(3,"%s %s:%d HAL portmap: cpu->%d\n ",0x20,uVar2,&DAT_11322924,0x36c,
                   *(undefined4 *)(param_1 + 0x14));
    }
    for (local_60c = 0; local_60c < *(uint *)(param_1 + 8); local_60c = local_60c + 1) {
      uVar2 = FUN_1004fe9c(param_1,local_60c);
      FUN_1004ff94(uVar2,&local_230,&local_234);
      if (2 < DAT_11e45404) {
        uVar6 = FUN_10046f5c();
        FUN_10047040(3,"%s %s:%d hal:%d->(hw:%d mod:%d phyport:%d),\n ",0x2e,uVar6,&DAT_11322924,
                     0x373,local_60c,uVar2,local_230,local_234);
      }
    }
    if (2 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      FUN_10047040(3,"%s %s:%d \n",0xb,uVar2,&DAT_11322924,0x375);
    }
    FUN_103fe480(*(undefined4 *)(param_1 + 4),FUN_1005b000);
    DAT_11e47fc4 = FUN_10058874();
    iVar3 = FUN_103f67d0(*(undefined4 *)(param_1 + 4),0,3,&DAT_11e47fc8);
    if ((iVar3 == 0) || (iVar3 == -0x10)) {
      FUN_112b0fec(auStack_2f4);
      iVar3 = FUN_103f501c(*(undefined4 *)(param_1 + 4),auStack_2f4);
      if (iVar3 < 0) {
        if (-1 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(0,"%s %s:%d CRIT bcm_l3_info failed: %s\n",0x26,uVar2,&DAT_11322924,0x397,
                       (&PTR_DAT_11e43a78)[iVar3]);
        }
        uVar2 = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0x28) = local_2e0;
        *(undefined4 *)(param_1 + 0x2c) = local_2d8;
        *(undefined4 *)(param_1 + 0x30) = local_2dc;
        *(undefined4 *)(param_1 + 0x34) = local_2e4;
        if (*(int *)(param_1 + 8) < local_2d4) {
          local_2d4 = *(int *)(param_1 + 8);
        }
        *(int *)(param_1 + 0x3c) = local_2d4;
        if ((((((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) != 0) ||
               ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x10000000) == 0)) &&
              ((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) != 0 ||
               ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 4) == 0)))) &&
             ((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) != 0 ||
              ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x200000) == 0)))) &&
            ((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) != 0 ||
             ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x8000000) == 0)))) &&
           ((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) != 0 ||
            (((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x80000) == 0 &&
             ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x40) == 0)))))) {
          FUN_113113b0("SOC_IS_TRIDENT(backend->unit) || SOC_IS_TRIDENT2(backend->unit) || SOC_IS_SCORPION(backend->unit) || SOC_IS_TRIUMPH2(backend->unit) || SOC_IS_TRIUMPH3(backend->unit)"
                       ,&DAT_11322924,0x3a5);
        }
        *(int *)(param_1 + 0x38) =
             *(int *)(&DAT_1211c184 + *(int *)(param_1 + 4) * 0x90) - *(int *)(param_1 + 0x3c);
        iVar3 = FUN_107953d0(*(undefined4 *)(param_1 + 4),"l3_alpm_enable",0);
        if (iVar3 == 2) {
          local_5f4 = 0x8000;
          local_5f0 = 0x4000;
        }
        else if (iVar3 == 1) {
          local_5f4 = 0x8000;
          local_5f0 = 0x1400;
        }
        if (iVar3 < 1) {
          local_5ec = 1;
        }
        else {
          local_5ec = 2;
          *(undefined4 *)(param_1 + 0x30) = 0x80;
          if (local_5f4 < *(int *)(param_1 + 0x28)) {
            *(int *)(param_1 + 0x28) = local_5f4;
            *(undefined4 *)(param_1 + 0x2c) = local_5f0;
          }
        }
        FUN_10027188(local_5ec);
        if ((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) == 0) &&
           (((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x80000) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x40) != 0)))) {
          local_600 = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] +
                                                         0x2f26f4) + 0x24) + 0x1f84) + 0xc);
          local_5fc = *(int *)((&DAT_1212ba0c)[*(int *)(param_1 + 4)] + 0x77528);
        }
        else {
          local_600 = *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] +
                                                         0x2f26f4) + 0x24) + 0x1f58) + 0xc);
          local_5fc = *(int *)((&DAT_1212ba0c)[*(int *)(param_1 + 4)] + 0x76b04);
        }
        *(int *)(param_1 + 0x54) = (local_5fc - local_600) + 1;
        iVar3 = FUN_103f9094(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 0x3c));
        if (iVar3 < 0) {
          if (-1 < DAT_11e45404) {
            uVar2 = FUN_10046f5c();
            if ((iVar3 < 1) && (-0x13 < iVar3)) {
              iVar3 = -iVar3;
            }
            else {
              iVar3 = 0x13;
            }
            FUN_10047040(0,"%s %s:%d CRIT bcm_l3_route_max_ecmp_set failed: %s\n",0x34,uVar2,
                         &DAT_11322924,0x3d4,(&PTR_DAT_11e43a78)[iVar3]);
          }
          uVar2 = 0;
        }
        else {
          uVar2 = FUN_100484c4(*(undefined4 *)(param_1 + 0x34));
          *(undefined4 *)(param_1 + 0x5c) = uVar2;
          uVar2 = FUN_100484c4(*(undefined4 *)(param_1 + 0x34));
          *(undefined4 *)(param_1 + 0x60) = uVar2;
          FUN_1004f9f4(local_c0,0x1000);
          *(undefined8 *)(param_1 + 100) = local_c0[0];
          FUN_1004f9f4(local_c0,0x1000);
          *(undefined8 *)(param_1 + 0x6c) = local_c0[0];
          for (local_604 = DAT_11e45408; local_604 <= DAT_11e4540c; local_604 = local_604 + 1) {
            local_c0[0] = *(undefined8 *)(param_1 + 100);
            FUN_1004faa0(local_c0,local_604);
          }
          for (local_604 = 1; local_604 <= DAT_11e4540c; local_604 = local_604 + 1) {
            local_c0[0] = *(undefined8 *)(param_1 + 0x6c);
            FUN_1004faa0(local_c0,local_604);
          }
          *(uint *)(param_1 + 0x44) = (DAT_11e4540c - DAT_11e45408) + 1;
          uVar2 = FUN_100484c4(*(undefined4 *)(param_1 + 0x44));
          *(undefined4 *)(param_1 + 0x7c) = uVar2;
          uVar2 = FUN_100484c4(*(undefined4 *)(param_1 + 0x44));
          *(undefined4 *)(param_1 + 0x80) = uVar2;
          uVar2 = FUN_100484c4(*(int *)(param_1 + 8) << 7);
          *(undefined4 *)(param_1 + 0x94) = uVar2;
          FUN_1042f28c(*(undefined4 *)(param_1 + 4));
          FUN_1042ebfc(*(undefined4 *)(param_1 + 4),param_1 + 0x40);
          uVar2 = FUN_100484c4(*(undefined4 *)(param_1 + 0x40));
          *(undefined4 *)(param_1 + 0x74) = uVar2;
          uVar2 = FUN_1004f6a0(0x1000,4,&DAT_11322924,0x3f3);
          *(undefined4 *)(param_1 + 0x78) = uVar2;
          uVar2 = FUN_1004f6a0(0x1000,4,&DAT_11322924,0x3f4);
          *(undefined4 *)(param_1 + 0x88) = uVar2;
          uVar2 = FUN_1004f6a0(0x1000,4,&DAT_11322924,0x3f5);
          *(undefined4 *)(param_1 + 0x8c) = uVar2;
          uVar2 = FUN_100484c4(*(undefined4 *)(param_1 + 8));
          *(undefined4 *)(param_1 + 0x90) = uVar2;
          DAT_11e45fb4 = 0;
          DAT_11e45fb8 = 0;
          for (local_5dc = 0; local_5dc < 0x800; local_5dc = local_5dc + 1) {
            uVar2 = FUN_1004f6a0(1,0x54,&DAT_11322924,0x3fd);
            *(undefined4 *)(&DAT_11e45fbc + local_5dc * 4) = uVar2;
          }
          iVar3 = FUN_1043d08c(*(undefined4 *)(param_1 + 4));
          if (iVar3 < 0) {
            if (-1 < DAT_11e45404) {
              uVar2 = FUN_10046f5c();
              if ((iVar3 < 1) && (-0x13 < iVar3)) {
                iVar3 = -iVar3;
              }
              else {
                iVar3 = 0x13;
              }
              FUN_10047040(0,"%s %s:%d CRIT bcm_trunk_init failed: %s\n",0x29,uVar2,&DAT_11322924,
                           0x403,(&PTR_DAT_11e43a78)[iVar3]);
            }
            uVar2 = 0;
          }
          else {
            FUN_112c5274(local_288);
            iVar3 = FUN_1043c034(*(undefined4 *)(param_1 + 4),local_288);
            if (iVar3 < 0) {
              if (-1 < DAT_11e45404) {
                uVar2 = FUN_10046f5c();
                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                  iVar3 = -iVar3;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_10047040(0,"%s %s:%d CRIT bcm_trunk_chip_info_get failed: %s\n",0x32,uVar2,
                             &DAT_11322924,0x40a,(&PTR_DAT_11e43a78)[iVar3]);
              }
              uVar2 = 0;
            }
            else {
              *(undefined4 *)(param_1 + 0x48) = local_288[0];
              *(undefined4 *)(param_1 + 0x4c) = local_27c;
              uVar2 = FUN_100484c4(*(int *)(param_1 + 0x48) << 1);
              *(undefined4 *)(param_1 + 0x84) = uVar2;
              uVar2 = FUN_100484c4(0x2000);
              *(undefined4 *)(param_1 + 0xb8) = uVar2;
              FUN_1004f1e4(param_1 + 0x250,1,0xff);
              cVar8 = FUN_1008d168(param_1);
              if (cVar8 == '\x01') {
                if (local_c8 != '\0') {
                  for (local_60c = 0; local_60c < *(uint *)(param_1 + 8); local_60c = local_60c + 1)
                  {
                    uVar5 = FUN_1004fe9c(param_1,local_60c);
                    uVar7 = FUN_100503ec(uVar5);
                    iVar3 = FUN_1005025c(param_1,uVar7);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT hal_bcm_vlan_create failed for %d: %s\n",0x35,
                                     uVar2,&DAT_11322924,0x42b,local_60c,(&PTR_DAT_11e43a78)[iVar3])
                        ;
                      }
                      return 0;
                    }
                    FUN_112cd824(local_210);
                    local_200 = 1;
                    uVar2 = *(undefined4 *)(param_1 + 4);
                    uVar7 = FUN_100503ec(uVar5);
                    memcpy(&local_b0,local_210,0xa0);
                    iVar3 = FUN_10443b70(uVar2,uVar7,&local_b0);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        uVar6 = FUN_100503ec(uVar5);
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_vlan_set failed %d: %d\n",
                                     0x37,uVar2,&DAT_11322924,0x435,uVar6,iVar3);
                      }
                      return 0;
                    }
                    uVar2 = *(undefined4 *)(param_1 + 4);
                    uVar7 = FUN_100503ec(uVar5);
                    iVar3 = FUN_10424374(uVar2,uVar5,uVar7);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,
                                     "%s %s:%d CRIT bcm_port_untagged_vlan_set failed for %d: %s\n",
                                     0x3c,uVar2,&DAT_11322924,0x43c,local_60c,
                                     (&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    for (local_5d8 = 0; local_5d8 < 8; local_5d8 = local_5d8 + 1) {
                      local_f0[local_5d8] = 0;
                    }
                    iVar3 = ((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0);
                    local_f0[iVar3] =
                         local_f0[iVar3] |
                         1 << (uVar5 + (((int)uVar5 >> 5) +
                                       (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) * -0x20 & 0x3f
                              );
                    uVar1 = *(uint *)(param_1 + 0x14);
                    iVar3 = ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0);
                    uVar1 = *(uint *)(param_1 + 0x14);
                    local_f0[iVar3] =
                         local_f0[iVar3] |
                         1 << (uVar1 + (((int)uVar1 >> 5) +
                                       (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * -0x20 & 0x3f
                              );
                    uVar2 = *(undefined4 *)(param_1 + 4);
                    uVar7 = FUN_100503ec(uVar5);
                    local_b0 = local_f0[0];
                    local_ac = local_f0[1];
                    local_a8 = local_f0[2];
                    local_a4 = local_f0[3];
                    local_a0 = local_e0;
                    local_9c = local_dc;
                    local_98 = local_d8;
                    local_94 = local_d4;
                    local_90 = local_f0[0];
                    local_8c = local_f0[1];
                    local_88 = local_f0[2];
                    local_84 = local_f0[3];
                    local_80 = local_e0;
                    local_7c = local_dc;
                    local_78 = local_d8;
                    local_74 = local_d4;
                    iVar3 = FUN_10447c20(uVar2,uVar7,&local_b0,&local_90);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_port_add failed for %d: %s\n",0x33,
                                     uVar2,&DAT_11322924,0x445,local_60c,(&PTR_DAT_11e43a78)[iVar3])
                        ;
                      }
                      return 0;
                    }
                    memset(auStack_170,0,0x80);
                    uVar1 = *(uint *)(param_1 + 0x14);
                    iVar3 = ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0);
                    uVar1 = *(uint *)(param_1 + 0x14);
                    auStack_170[iVar3 + 0x10] =
                         auStack_170[iVar3 + 0x10] |
                         1 << (uVar1 + (((int)uVar1 >> 5) +
                                       (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * -0x20 & 0x3f
                              );
                    if (((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) == 0) &&
                        ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 0x10000000) !=
                         0)) || ((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x10) == 0 &&
                                 ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] + 0x14) & 4) !=
                                  0)))) {
                      uVar1 = *(uint *)(param_1 + 0x14);
                      iVar3 = ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0);
                      uVar1 = *(uint *)(param_1 + 0x14);
                      auStack_170[iVar3 + 8] =
                           auStack_170[iVar3 + 8] |
                           1 << (uVar1 + (((int)uVar1 >> 5) +
                                         (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * -0x20 &
                                0x3f);
                    }
                    uVar2 = *(undefined4 *)(param_1 + 4);
                    uVar7 = FUN_100503ec(uVar5);
                    FUN_10442eb0(uVar2,uVar7,auStack_170);
                    iVar3 = FUN_1041a53c(*(undefined4 *)(param_1 + 4),uVar5,4);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_port_learn_set failed for %d: %s\n",0x34,
                                     uVar2,&DAT_11322924,0x45d,local_60c,(&PTR_DAT_11e43a78)[iVar3])
                        ;
                      }
                      return 0;
                    }
                    iVar3 = FUN_10414d60(*(undefined4 *)(param_1 + 4),uVar5,0x15,1);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,
                                     "%s %s:%d CRIT bcmPortControlLearnClassEnable failed %d (%s)\n"
                                     ,0x3d,uVar2,&DAT_11322924,0x466,uVar5,
                                     (&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    for (local_5d4 = 0; local_5d4 < 4; local_5d4 = local_5d4 + 1) {
                      iVar3 = FUN_103ea270(*(undefined4 *)(param_1 + 4),local_5d4,local_5d4,1);
                      if (iVar3 < 0) {
                        if (-1 < DAT_11e45404) {
                          uVar2 = FUN_10046f5c();
                          if ((iVar3 < 1) && (-0x13 < iVar3)) {
                            iVar3 = -iVar3;
                          }
                          else {
                            iVar3 = 0x13;
                          }
                          FUN_10047040(0,"%s %s:%d CRIT failed to set L2 learn class (%s)\n",0x31,
                                       uVar2,&DAT_11322924,0x470,(&PTR_DAT_11e43a78)[iVar3]);
                        }
                        return 0;
                      }
                    }
                    iVar3 = FUN_10414d60(*(undefined4 *)(param_1 + 4),uVar5,0x47,1);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,
                                     "%s %s:%d CRIT bcmPortControlForwardStaticL2MovePkt failed %d (%s)\n"
                                     ,0x43,uVar2,&DAT_11322924,0x47c,uVar5,
                                     (&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_1041d288(*(undefined4 *)(param_1 + 4),uVar5,0,0);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_port_pause_set failed for %d: %s\n",0x34,
                                     uVar2,&DAT_11322924,0x484,local_60c,(&PTR_DAT_11e43a78)[iVar3])
                        ;
                      }
                      return 0;
                    }
                    iVar3 = FUN_10419ca4(*(undefined4 *)(param_1 + 4),uVar5,1);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_port_l3_enable_set failed for %d: %s\n",
                                     0x38,uVar2,&DAT_11322924,0x48e,local_60c,
                                     (&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10424c7c(*(undefined4 *)(param_1 + 4),uVar5,3);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_port_vlan_member_set failed: %s\n",0x33,
                                     uVar2,&DAT_11322924,0x496,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10414d60(*(undefined4 *)(param_1 + 4),uVar5,0x16,1);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_port_control_set failed: %s\n",0x2f,uVar2,
                                     &DAT_11322924,0x49c,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10443554(*(undefined4 *)(param_1 + 4),uVar5,2,1);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_port_set failed:%s\n",0x33,
                                     uVar2,&DAT_11322924,0x4a5,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10443554(*(undefined4 *)(param_1 + 4),uVar5,4,0);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_port_set failed:%s\n",0x33,
                                     uVar2,&DAT_11322924,0x4ab,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10443554(*(undefined4 *)(param_1 + 4),uVar5,5,1);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_port_set failed:%s\n",0x33,
                                     uVar2,&DAT_11322924,0x4b1,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10443554(*(undefined4 *)(param_1 + 4),uVar5,6,0);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_port_set failed:%s\n",0x33,
                                     uVar2,&DAT_11322924,0x4ba,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10443554(*(undefined4 *)(param_1 + 4),uVar5,0x10,0);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_port_set failed:%s\n",0x33,
                                     uVar2,&DAT_11322924,0x4c6,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    iVar3 = FUN_10443554(*(undefined4 *)(param_1 + 4),uVar5,0xe,8);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_vlan_control_port_set failed:%s\n",0x33,
                                     uVar2,&DAT_11322924,0x4cd,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      return 0;
                    }
                    cVar8 = FUN_1007fa64(param_1,uVar5);
                    if (cVar8 != '\x01') {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        FUN_10047040(0,"%s %s:%d CRIT vxlan port init failed\n",0x26,uVar2,
                                     &DAT_11322924,0x4d2);
                      }
                      return 0;
                    }
                  }
                }
                FUN_103e7eb4(*(undefined4 *)(param_1 + 4),FUN_10060268,0);
                FUN_103e831c(0,0);
                iVar3 = FUN_10440ff8(*(undefined4 *)(param_1 + 4));
                if (iVar3 < 0) {
                  if (-1 < DAT_11e45404) {
                    uVar2 = FUN_10046f5c();
                    if ((iVar3 < 1) && (-0x13 < iVar3)) {
                      iVar3 = -iVar3;
                    }
                    else {
                      iVar3 = 0x13;
                    }
                    FUN_10047040(0,"%s %s:%d CRIT bcm_tx_init failed: %s\n",0x26,uVar2,&DAT_11322924
                                 ,0x4e1,(&PTR_DAT_11e43a78)[iVar3]);
                  }
                  uVar2 = 0;
                }
                else {
                  iVar3 = FUN_1042be0c(*(undefined4 *)(param_1 + 4),0);
                  if (iVar3 < 0) {
                    if (-1 < DAT_11e45404) {
                      uVar2 = FUN_10046f5c();
                      if ((iVar3 < 1) && (-0x13 < iVar3)) {
                        iVar3 = -iVar3;
                      }
                      else {
                        iVar3 = 0x13;
                      }
                      FUN_10047040(0,"%s %s:%d CRIT bcm_rx_start failed: %s\n",0x27,uVar2,
                                   &DAT_11322924,0x4e7,(&PTR_DAT_11e43a78)[iVar3]);
                    }
                    uVar2 = 0;
                  }
                  else {
                    iVar3 = FUN_1042b380(*(undefined4 *)(param_1 + 4),"switchd_rx",FUN_1005b90c,1,0,
                                         0x40000000);
                    if (iVar3 < 0) {
                      if (-1 < DAT_11e45404) {
                        uVar2 = FUN_10046f5c();
                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                          iVar3 = -iVar3;
                        }
                        else {
                          iVar3 = 0x13;
                        }
                        FUN_10047040(0,"%s %s:%d CRIT bcm_rx_register failed: %s\n",0x2a,uVar2,
                                     &DAT_11322924,0x4ee,(&PTR_DAT_11e43a78)[iVar3]);
                      }
                      uVar2 = 0;
                    }
                    else {
                      iVar3 = FUN_104290c4(*(undefined4 *)(param_1 + 4),1,1);
                      if (iVar3 < 0) {
                        if (-1 < DAT_11e45404) {
                          uVar2 = FUN_10046f5c();
                          if ((iVar3 < 1) && (-0x13 < iVar3)) {
                            iVar3 = -iVar3;
                          }
                          else {
                            iVar3 = 0x13;
                          }
                          FUN_10047040(0,
                                       "%s %s:%d CRIT bcm_rx_control_set of VTAG_STRIP failed: %s\n"
                                       ,0x3b,uVar2,&DAT_11322924,0x4f5,(&PTR_DAT_11e43a78)[iVar3]);
                        }
                        uVar2 = 0;
                      }
                      else {
                        iVar3 = FUN_104290c4(*(undefined4 *)(param_1 + 4),0,1);
                        if (iVar3 < 0) {
                          if (-1 < DAT_11e45404) {
                            uVar2 = FUN_10046f5c();
                            if ((iVar3 < 1) && (-0x13 < iVar3)) {
                              iVar3 = -iVar3;
                            }
                            else {
                              iVar3 = 0x13;
                            }
                            FUN_10047040(0,
                                         "%s %s:%d CRIT bcm_rx_control_set of CRC_STRIP failed: %s\n"
                                         ,0x3a,uVar2,&DAT_11322924,0x4fb,(&PTR_DAT_11e43a78)[iVar3])
                            ;
                          }
                          uVar2 = 0;
                        }
                        else {
                          FUN_112d0f90(&local_260,0,0x9a);
                          FUN_112d0f90(&local_24c,0,0x9a);
                          local_25c = local_25c | 0x20;
                          local_248 = local_248 | 0x20;
                          local_b0 = local_260;
                          local_a8 = local_258;
                          local_a4 = local_254;
                          local_a0 = local_250;
                          local_90 = local_24c;
                          local_88 = local_244;
                          local_84 = local_240;
                          local_80 = local_23c;
                          local_ac = local_25c;
                          local_8c = local_248;
                          iVar3 = FUN_10429c28(*(undefined4 *)(param_1 + 4),0x77,&local_b0,&local_90
                                               ,0,0,0,0,0x20);
                          if (iVar3 < 0) {
                            if (-1 < DAT_11e45404) {
                              uVar2 = FUN_10046f5c();
                              if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                iVar3 = -iVar3;
                              }
                              else {
                                iVar3 = 0x13;
                              }
                              FUN_10047040(0,"%s %s:%d CRIT bcm_rx_cosq_mapping_set failed: %s\n",
                                           0x32,uVar2,&DAT_11322924,0x509,(&PTR_DAT_11e43a78)[iVar3]
                                          );
                            }
                            uVar2 = 0;
                          }
                          else {
                            FUN_112d0f90(&local_260,0,0x9a);
                            FUN_112d0f90(&local_24c,0,0x9a);
                            local_25c = local_25c | 8;
                            local_248 = local_248 | 8;
                            local_b0 = local_260;
                            local_a8 = local_258;
                            local_a4 = local_254;
                            local_a0 = local_250;
                            local_90 = local_24c;
                            local_88 = local_244;
                            local_84 = local_240;
                            local_80 = local_23c;
                            local_ac = local_25c;
                            local_8c = local_248;
                            iVar3 = FUN_10429c28(*(undefined4 *)(param_1 + 4),0x76,&local_b0,
                                                 &local_90,0,0,0,0,0x21);
                            if (iVar3 < 0) {
                              if (-1 < DAT_11e45404) {
                                uVar2 = FUN_10046f5c();
                                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                  iVar3 = -iVar3;
                                }
                                else {
                                  iVar3 = 0x13;
                                }
                                FUN_10047040(0,"%s %s:%d CRIT bcm_rx_cosq_mapping_set failed: %s\n",
                                             0x32,uVar2,&DAT_11322924,0x514,
                                             (&PTR_DAT_11e43a78)[iVar3]);
                              }
                              uVar2 = 0;
                            }
                            else {
                              FUN_112d0f90(&local_260,0,0x9a);
                              FUN_112d0f90(&local_24c,0,0x9a);
                              local_25c = local_25c | 0x18000000;
                              local_248 = local_248 | 0x18000000;
                              local_b0 = local_260;
                              local_a8 = local_258;
                              local_a4 = local_254;
                              local_a0 = local_250;
                              local_90 = local_24c;
                              local_88 = local_244;
                              local_84 = local_240;
                              local_80 = local_23c;
                              local_ac = local_25c;
                              local_8c = local_248;
                              iVar3 = FUN_10429c28(*(undefined4 *)(param_1 + 4),0x75,&local_b0,
                                                   &local_90,0,0,0,0,0x22);
                              if (iVar3 < 0) {
                                if (-1 < DAT_11e45404) {
                                  uVar2 = FUN_10046f5c();
                                  if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                    iVar3 = -iVar3;
                                  }
                                  else {
                                    iVar3 = 0x13;
                                  }
                                  FUN_10047040(0,
                                               "%s %s:%d CRIT bcm_rx_cosq_mapping_set failed: %s\n",
                                               0x32,uVar2,&DAT_11322924,0x521,
                                               (&PTR_DAT_11e43a78)[iVar3]);
                                }
                                uVar2 = 0;
                              }
                              else {
                                iVar3 = FUN_1006f798(param_1,0x20,1,1);
                                if (iVar3 == 0) {
                                  iVar3 = FUN_1006f798(param_1,0x21,1,1);
                                  if (iVar3 == 0) {
                                    iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),0xe6,1);
                                    if (iVar3 < 0) {
                                      if (-1 < DAT_11e45404) {
                                        uVar2 = FUN_10046f5c();
                                        if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                          iVar3 = -iVar3;
                                        }
                                        else {
                                          iVar3 = 0x13;
                                        }
                                        FUN_10047040(0,
                                                  "%s %s:%d CRIT Setting bcmSwitchL3EgressMode failed: %s\n"
                                                  ,0x38,uVar2,&DAT_11322924,0x53f,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                      }
                                      uVar2 = 0;
                                    }
                                    else {
                                      iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),0xf9,1);
                                      if (iVar3 < 0) {
                                        if (-1 < DAT_11e45404) {
                                          uVar2 = FUN_10046f5c();
                                          if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                            iVar3 = -iVar3;
                                          }
                                          else {
                                            iVar3 = 0x13;
                                          }
                                          FUN_10047040(0,
                                                  "%s %s:%d CRIT Setting bcmSwitchIpmcTtl1ToCpu failed: %s\n"
                                                  ,0x39,uVar2,&DAT_11322924,0x548,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                        }
                                        uVar2 = 0;
                                      }
                                      else {
                                        iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),0xfa,1);
                                        if (iVar3 < 0) {
                                          if (-1 < DAT_11e45404) {
                                            uVar2 = FUN_10046f5c();
                                            if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                              iVar3 = -iVar3;
                                            }
                                            else {
                                              iVar3 = 0x13;
                                            }
                                            FUN_10047040(0,
                                                  "%s %s:%d CRIT Setting bcmSwitchL3UcastTtl1ToCpu failed: %s\n"
                                                  ,0x3c,uVar2,&DAT_11322924,0x54e,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                          }
                                          uVar2 = 0;
                                        }
                                        else if (((*(int *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)] +
                                                           0x10) == 0) &&
                                                 ((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)]
                                                            + 0x14) & 0x8000000) != 0)) &&
                                                (iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),
                                                                      0x16,1), iVar3 < 0)) {
                                          if (3 < DAT_11e45404) {
                                            uVar2 = FUN_10046f5c();
                                            if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                              iVar3 = -iVar3;
                                            }
                                            else {
                                              iVar3 = 0x13;
                                            }
                                            FUN_10047040(4,
                                                  "%s %s:%d Setting bcmSwitchNonIpL3ErrToCpu failed: %s\n"
                                                  ,0x36,uVar2,&DAT_11322924,0x558,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                          }
                                          uVar2 = 0;
                                        }
                                        else if (((*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)]
                                                            + 0x2f2c40) & 0x200) == 0) ||
                                                (iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),
                                                                      0x115,1), -1 < iVar3)) {
                                          cVar8 = FUN_1007f660(param_1);
                                          if (cVar8 == '\x01') {
                                            cVar8 = FUN_10051674(param_1);
                                            if (cVar8 == '\x01') {
                                              local_22c = DAT_113238a2;
                                              local_228 = DAT_113238a6;
                                              local_224 = DAT_113238aa;
                                              local_220 = DAT_113238ae;
                                              local_21c = DAT_113238b2;
                                              local_218 = DAT_113238b6;
                                              FUN_112b07dc(local_210);
                                              local_210[0] = 0x4111;
                                              local_206 = DAT_11e454e8;
                                              local_202 = DAT_11e454ec;
                                              local_1f0 = *(undefined4 *)
                                                           ((&DAT_1212b9c4)[*(int *)(param_1 + 4)] +
                                                           0x5ba0);
                                              for (local_5d0 = 0; local_5d0 < 4;
                                                  local_5d0 = local_5d0 + 1) {
                                                local_210[1] = *(undefined4 *)
                                                                ((int)&local_22c + local_5d0 * 6);
                                                local_208 = *(undefined2 *)
                                                             ((int)&local_228 + local_5d0 * 6);
                                                iVar3 = FUN_103e8f14(*(undefined4 *)(param_1 + 4),
                                                                     0xffffffff,local_210,
                                                                     auStack_214);
                                                if (iVar3 < 0) {
                                                  __ptr = (void *)FUN_10028640(local_210 + 1);
                                                  if (-1 < DAT_11e45404) {
                                                    uVar2 = FUN_10046f5c();
                                                    if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                                      iVar3 = -iVar3;
                                                    }
                                                    else {
                                                      iVar3 = 0x13;
                                                    }
                                                    FUN_10047040(0,
                                                  "%s %s:%d CRIT Could not add %s to l2cache: %s\n",
                                                  0x2f,uVar2,&DAT_11322924,0x58c,__ptr,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                                  }
                                                  free(__ptr);
                                                  return 0;
                                                }
                                              }
                                              *(bool *)(param_1 + 0x260) =
                                                   (*(uint *)((&DAT_1212b9c4)[*(int *)(param_1 + 4)]
                                                             + 0x2f2c1c) & 4) != 0;
                                              FUN_10073720(local_d0);
                                              FUN_100878d0(*(undefined4 *)(param_1 + 4));
                                              iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),
                                                                   0x36f,0xf);
                                              if (((iVar3 < 0) && (iVar3 != -0x10)) &&
                                                 (-2 < DAT_11e45404)) {
                                                uVar2 = FUN_10046f5c();
                                                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                                  iVar3 = -iVar3;
                                                }
                                                else {
                                                  iVar3 = 0x13;
                                                }
                                                FUN_10047040(0xffffffff,
                                                                                                                          
                                                  "%s %s:%d Setting bcmSwitchSymmetricHashControl failed: %s\n"
                                                  ,0x3b,uVar2,&DAT_11322924,0x5a6,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                              }
                                              iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),
                                                                   0x10e,2);
                                              if (((iVar3 < 0) && (iVar3 != -0x10)) &&
                                                 (-2 < DAT_11e45404)) {
                                                uVar2 = FUN_10046f5c();
                                                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                                  iVar3 = -iVar3;
                                                }
                                                else {
                                                  iVar3 = 0x13;
                                                }
                                                FUN_10047040(0xffffffff,
                                                                                                                          
                                                  "%s %s:%d Setting bcmSwitchHashDualMoveDepthL3 failed: %s\n"
                                                  ,0x3a,uVar2,&DAT_11322924,0x5ac,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                              }
                                              iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),0x85
                                                                   ,5);
                                              if ((iVar3 < 0) && (iVar3 != -0x10)) {
                                                if (0 < DAT_11e45404) {
                                                  uVar2 = FUN_10046f5c();
                                                  if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                                    iVar3 = -iVar3;
                                                  }
                                                  else {
                                                    iVar3 = 0x13;
                                                  }
                                                  FUN_10047040(1,
                                                  "%s %s:%d ERR Setting bcmSwitchHashL2 failed: %s\n"
                                                  ,0x31,uVar2,&DAT_11322924,0x5b3,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                                }
                                                uVar2 = 0;
                                              }
                                              else {
                                                iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),
                                                                     0x10a,6);
                                                if ((iVar3 < 0) && (iVar3 != -0x10)) {
                                                  if (0 < DAT_11e45404) {
                                                    uVar2 = FUN_10046f5c();
                                                    if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                                      iVar3 = -iVar3;
                                                    }
                                                    else {
                                                      iVar3 = 0x13;
                                                    }
                                                    FUN_10047040(1,
                                                  "%s %s:%d ERR Setting bcmSwitchHashL2Dual failed: %s\n"
                                                  ,0x35,uVar2,&DAT_11322924,0x5b9,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                                  }
                                                  uVar2 = 0;
                                                }
                                                else {
                                                  iVar3 = FUN_104367fc(*(undefined4 *)(param_1 + 4),
                                                                       0x10d,0);
                                                  if ((iVar3 < 0) && (iVar3 != -0x10)) {
                                                    if (0 < DAT_11e45404) {
                                                      uVar2 = FUN_10046f5c();
                                                      if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                                        iVar3 = -iVar3;
                                                      }
                                                      else {
                                                        iVar3 = 0x13;
                                                      }
                                                      FUN_10047040(1,
                                                  "%s %s:%d ERR Setting bcmSwitchHashDualMoveDepthL2 failed: %s\n"
                                                  ,0x3e,uVar2,&DAT_11322924,0x5bf,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                                  }
                                                  uVar2 = 0;
                                                  }
                                                  else {
                                                    FUN_1008dba0(local_d0,local_cc);
                                                    if (((*(uint *)((&DAT_1212b9c4)
                                                                    [*(int *)(param_1 + 4)] +
                                                                   0x2f2c44) & 0x200000) == 0) ||
                                                       (cVar8 = FUN_1007dec0(param_1),
                                                       cVar8 == '\x01')) {
                                                      FUN_1007e870(local_d0);
                                                      uVar2 = 1;
                                                    }
                                                    else {
                                                      uVar2 = 0;
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                            else {
                                              if (-1 < DAT_11e45404) {
                                                uVar2 = FUN_10046f5c();
                                                FUN_10047040(0,
                                                  "%s %s:%d CRIT failed to initialize l2mc\n",0x29,
                                                  uVar2,&DAT_11322924,0x56d);
                                              }
                                              uVar2 = 0;
                                            }
                                          }
                                          else {
                                            if (-1 < DAT_11e45404) {
                                              uVar2 = FUN_10046f5c();
                                              FUN_10047040(0,
                                                  "%s %s:%d CRIT failed to initialize vxlan\n",0x2a,
                                                  uVar2,&DAT_11322924,0x568);
                                            }
                                            uVar2 = 0;
                                          }
                                        }
                                        else {
                                          if (0 < DAT_11e45404) {
                                            uVar2 = FUN_10046f5c();
                                            if ((iVar3 < 1) && (-0x13 < iVar3)) {
                                              iVar3 = -iVar3;
                                            }
                                            else {
                                              iVar3 = 0x13;
                                            }
                                            FUN_10047040(1,
                                                  "%s %s:%d ERR Setting bcmSwitchHashMultiMoveDepthL2 failed: %s\n"
                                                  ,0x3f,uVar2,&DAT_11322924,0x561,
                                                  (&PTR_DAT_11e43a78)[iVar3]);
                                          }
                                          uVar2 = 0;
                                        }
                                      }
                                    }
                                  }
                                  else {
                                    uVar2 = 0;
                                  }
                                }
                                else {
                                  uVar2 = 0;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              else {
                if (-1 < DAT_11e45404) {
                  uVar2 = FUN_10046f5c();
                  FUN_10047040(0,"%s %s:%d CRIT hal_bcm_stat_init failed\n",0x28,uVar2,&DAT_11322924
                               ,0x419);
                }
                uVar2 = 0;
              }
            }
          }
        }
      }
    }
    else {
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        if ((iVar3 < 1) && (-0x13 < iVar3)) {
          iVar3 = -iVar3;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(0,"%s %s:%d CRIT bcm_l3_ip4_options_profile_create failed: %s\n",0x3c,uVar2,
                     &DAT_11322924,0x38c,(&PTR_DAT_11e43a78)[iVar3]);
      }
      uVar2 = 0;
    }
  }
  return uVar2;
}



/* === FUN_1006f798 (size=420) === */

int FUN_1006f798(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_10429788(*(undefined4 *)(param_1 + 4),param_2,param_3);
  if (iVar1 < 0) {
    if (-1 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar3 = -iVar1;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(0,"%s %s:%d CRIT bcm_rx_cos_rate_set failed: %s\n",0x2e,uVar2,&DAT_11322924,
                   0x1f94,(&PTR_DAT_11e43a78)[iVar3]);
    }
  }
  else {
    iVar1 = FUN_10429308(*(undefined4 *)(param_1 + 4),param_2,param_4);
    if ((iVar1 < 0) && (-1 < DAT_11e45404)) {
      uVar2 = FUN_10046f5c();
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar3 = -iVar1;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(0,"%s %s:%d CRIT bcm_rx_cos_burst_set failed: %s\n",0x2f,uVar2,&DAT_11322924,
                   0x1f9a,(&PTR_DAT_11e43a78)[iVar3]);
    }
  }
  return iVar1;
}



/* === FUN_1012fa28 (size=232) === */

undefined4 FUN_1012fa28(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int local_28;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0xffffffff;
  }
  else {
    if (*(int *)(param_2 + 0x2008) < *(int *)(param_2 + 0x2004)) {
      local_28 = *(int *)(param_2 + *(int *)(param_2 + 0x2008) * 4 + 4);
      *(int *)(param_2 + 0x2008) = *(int *)(param_2 + 0x2008) + 1;
    }
    else {
      local_28 = 0;
    }
    if ((local_28 == 0) && (local_28 = FUN_100a01d8("dma_dcb_count"), local_28 == 0)) {
      return 0xffffffff;
    }
    uVar1 = FUN_1009067c(local_28);
    *param_3 = uVar1;
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_1012fbf8 (size=228) === */

void FUN_1012fbf8(int param_1,undefined4 param_2)

{
  undefined1 auStack_38 [32];
  int local_18;
  undefined4 local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  FUN_11310e2c(auStack_38,&UNK_11353ef4,param_1);
  FUN_1009f7d8("dma_dv_laddr",auStack_38,1,0);
  FUN_11310e2c(auStack_38,&UNK_11353ef4,*(undefined4 *)(local_18 + 0xc4));
  FUN_1009f7d8("dma_dcb_laddr",auStack_38,1,0);
  FUN_1009f8b4("dma_dcb_count",*(undefined4 *)(local_18 + 0x18),1,0);
  FUN_1009f8b4("dma_dcb_size",local_14,1,0);
  return;
}



/* === FUN_10130b18 (size=572) === */

undefined4 FUN_10130b18(int param_1,undefined4 *param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  undefined1 local_28;
  undefined4 local_1c;
  int local_18;
  undefined4 *local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  iVar2 = FUN_100ec9fc(*param_2,param_1);
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  if ((int)local_14[0x802] < (int)local_14[0x801]) {
    pbVar3 = (byte *)local_14[local_14[0x802] + 1];
    local_14[0x802] = local_14[0x802] + 1;
  }
  else {
    pbVar3 = (byte *)0x0;
  }
  if (pbVar3 == (byte *)0x0) {
    FUN_10320d20("DMA Vector (DV) type is not specified.\n");
    return 0xfffffffe;
  }
  bVar1 = *pbVar3;
  if (bVar1 == 0x54) {
LAB_10130c14:
    local_28 = 1;
LAB_10130c3c:
    iVar2 = FUN_1012fa28(local_18,local_14,&local_1c);
    if (iVar2 == 0) {
      iVar2 = FUN_1078dc60(local_18,local_28,local_1c);
      if (iVar2 == 0) {
        FUN_10320d20("Failed to allocate a DMA Vector (DV) with %d DCBs\n",local_1c);
        uVar4 = 0xffffffff;
      }
      else {
        FUN_10320d20("Allocated DMA Vector (DV) at %p. %d DCBs (start %p, %d bytes)\n",iVar2,
                     *(undefined4 *)(iVar2 + 0x18),*(undefined4 *)(iVar2 + 0xc4),
                     *(undefined4 *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f1bf4) + 4));
        FUN_1012fbf8(iVar2,*(undefined4 *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f1bf4) + 4));
        uVar4 = 0;
      }
    }
    else {
      uVar4 = 0xfffffffe;
    }
  }
  else {
    if (bVar1 < 0x55) {
      if (bVar1 == 0x52) {
LAB_10130c08:
        local_28 = 2;
        goto LAB_10130c3c;
      }
    }
    else {
      if (bVar1 == 0x72) goto LAB_10130c08;
      if (bVar1 == 0x74) goto LAB_10130c14;
    }
    FUN_10320d20("Incorrect DV type <%s>. [r|t] expected.\n",pbVar3);
    uVar4 = 0xfffffffe;
  }
  return uVar4;
}



/* === FUN_10130d54 (size=496) === */

undefined4 FUN_10130d54(int param_1,undefined4 *param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  char local_28;
  undefined4 local_20 [2];
  int local_18;
  undefined4 *local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  iVar2 = FUN_100ec9fc(*param_2,param_1);
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  if ((int)local_14[0x802] < (int)local_14[0x801]) {
    pbVar3 = (byte *)local_14[local_14[0x802] + 1];
    local_14[0x802] = local_14[0x802] + 1;
  }
  else {
    pbVar3 = (byte *)0x0;
  }
  if (pbVar3 == (byte *)0x0) {
    FUN_10320d20("DCB type is not specified.\n");
    return 0xfffffffe;
  }
  bVar1 = *pbVar3;
  if (bVar1 == 0x54) {
LAB_10130e50:
    local_28 = '\x01';
LAB_10130e78:
    iVar2 = FUN_1012f78c(local_18,local_14,local_20);
    if (iVar2 == 0) {
      FUN_10320d20("Dumping DCB at address %p:\n",local_20[0]);
      (**(code **)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f1bf4) + 0x15c))
                (local_18,local_20[0],&UNK_1135432c,local_28 == '\x01');
      uVar4 = 0;
    }
    else {
      FUN_10320d20("Cannot get DCB address\n");
      uVar4 = 0xffffffff;
    }
  }
  else {
    if (bVar1 < 0x55) {
      if (bVar1 == 0x52) {
LAB_10130e44:
        local_28 = '\x02';
        goto LAB_10130e78;
      }
    }
    else {
      if (bVar1 == 0x72) goto LAB_10130e44;
      if (bVar1 == 0x74) goto LAB_10130e50;
    }
    FUN_10320d20("Incorrect DCB type <%s>. [r|t] expected.\n",pbVar3);
    uVar4 = 0xfffffffe;
  }
  return uVar4;
}



/* === FUN_10130fe0 (size=368) === */

undefined4 FUN_10130fe0(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 *local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  iVar1 = FUN_100ec9fc(*param_2,param_1);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = FUN_1012fb10(local_18,local_14,&local_20);
    if (iVar1 == 0) {
      iVar1 = FUN_1012f78c(local_18,local_14,&local_24);
      if (iVar1 == 0) {
        iVar1 = FUN_1012f538(local_18,local_14,&local_1c);
        if (iVar1 == 0) {
          uVar2 = (**(code **)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f1bf4) + 0x1c))
                            (local_20,local_24,local_1c,0);
          FUN_10320d20("Added DCB to RX DV. %d DCB remaining\n",uVar2);
          uVar2 = 0;
        }
        else {
          FUN_10320d20("Cannot get buffer size\n");
          uVar2 = 0xffffffff;
        }
      }
      else {
        FUN_10320d20("Cannot get buffer address\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      FUN_10320d20("Cannot get DV address\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}



/* === FUN_10135e2c (size=540) === */

undefined4 FUN_10135e2c(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  char *__s1;
  undefined4 uVar2;
  
  if ((int)param_2[0x802] < (int)param_2[0x801]) {
    __s1 = (char *)param_2[param_2[0x802] + 1];
    param_2[0x802] = param_2[0x802] + 1;
  }
  else {
    __s1 = (char *)0x0;
  }
  if (__s1 == (char *)0x0) {
    uVar2 = 0xfffffffe;
  }
  else {
    iVar1 = strcasecmp(__s1,"start");
    if (iVar1 == 0) {
      FUN_1042be0c(param_1,0);
      iVar1 = FUN_1042b380(param_1,&UNK_113550a8,FUN_10135d04,0x65,0,0x40000000);
      if (iVar1 < 0) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar1 = -iVar1;
        }
        else {
          iVar1 = 0x13;
        }
        FUN_10320d20("%s: bcm_rx_register failed: %s\n",*param_2,(&PTR_DAT_11e43a78)[iVar1]);
        return 0xffffffff;
      }
    }
    iVar1 = strcasecmp(__s1,"stop");
    if (iVar1 == 0) {
      FUN_1042bf24(param_1,0);
      iVar1 = FUN_1042c650(param_1,FUN_10135d04,0x65);
      if (iVar1 < 0) {
        if ((iVar1 < 1) && (-0x13 < iVar1)) {
          iVar1 = -iVar1;
        }
        else {
          iVar1 = 0x13;
        }
        FUN_10320d20("%s: bcm_rx_unregister failed: %s\n",*param_2,(&PTR_DAT_11e43a78)[iVar1]);
        return 0xffffffff;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_100ec17c (size=1348) === */

void FUN_100ec17c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char *local_38;
  char *local_34;
  undefined1 auStack_30 [16];
  short local_20;
  undefined1 local_1e [2];
  undefined2 local_1c;
  undefined1 local_1a [2];
  int local_18;
  
  local_18 = param_1;
  if (param_1 != DAT_1183f318) {
    if (-1 < DAT_1183f318) {
      FUN_11310e2c(auStack_30,&UNK_11345910,DAT_1183f318);
      if ((&DAT_1212b9c4)[DAT_1183f318] != 0) {
        FUN_1009fa28(*(undefined4 *)(*(int *)((&DAT_1212b9c4)[DAT_1183f318] + 0x2f26f4) + 4),0,1,0);
        uVar1 = FUN_10794ac4(DAT_1183f318);
        FUN_1009fa28(uVar1,0,1,0);
      }
      FUN_1009fa28(auStack_30,0,1,0);
      FUN_1009fa28("devname",0,1,0);
      FUN_1009fa28("drivername",0,1,0);
      FUN_1009fa28(&DAT_1134592c,0,1,0);
      FUN_1009fa28(&DAT_11345934,0,1,0);
      FUN_1009fa28("rcpu_only",0,1,0);
      FUN_1009fa28("ihost_mode",0,1,0);
    }
    if (-1 < local_18) {
      local_34 = "UNKNOWN";
      local_38 = *(char **)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 4);
      iVar2 = FUN_1075f9c8(local_18,&local_20,local_1e);
      if (-1 < iVar2) {
        FUN_11310e2c(auStack_30,&UNK_1134595c,local_20);
        FUN_1009f7d8(&DAT_1134592c,auStack_30,0,0);
        FUN_11310e2c(auStack_30,&UNK_11345964,local_1e[0]);
        FUN_1009f7d8(&DAT_11345934,auStack_30,0,0);
        if (local_20 == -0x49e0) {
          local_38 = "triumph";
        }
        if (local_20 == -0x49d0) {
          local_38 = "triumph2";
        }
        if (local_20 == -0x4ada) {
          local_38 = "apollo";
        }
        if (local_20 == -0x4ac8) {
          local_38 = "firebolt3";
        }
        if (local_20 == -0x4acc) {
          local_38 = "firebolt3";
        }
      }
      iVar2 = FUN_1075fa70(local_20,local_1e[0],&local_1c,local_1a);
      if (-1 < iVar2) {
        local_34 = (char *)FUN_1075ee54(local_1c,local_1a[0]);
      }
      FUN_1009f8b4(local_38,1,0,0);
      uVar1 = FUN_10794ac4(local_18);
      FUN_1009f8b4(uVar1,1,0,0);
      FUN_11310e2c(auStack_30,&UNK_11345910,local_18);
      FUN_1009f8b4(auStack_30,1,0,0);
      uVar1 = FUN_10794ac4(local_18);
      FUN_1009f7d8("devname",uVar1,0,0);
      FUN_1009f7d8("drivername",local_34,0,0);
      if ((*(uint *)(&DAT_1212b9c4)[local_18] & 0x800) != 0) {
        FUN_1009f8b4("rcpu_only",1,0,0);
      }
      if (((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 0x20) != 0) &&
         (uVar3 = FUN_10760950(local_18), (uVar3 & 0x80) != 0)) {
        FUN_1009f8b4("ihost_mode",1,0,0);
      }
    }
    if (local_18 < 0) {
      FUN_1009fa28(&DAT_11345994,0,1,0);
    }
    else {
      FUN_1009f8b4(&DAT_11345994,local_18,0,0);
      FUN_100a0e1c(1);
    }
    DAT_1183f318 = local_18;
  }
  DAT_11e45414 = local_18;
  DAT_11e45418 = local_18;
  return;
}



/* NO FUNCTION at 0x101b8f54 */

