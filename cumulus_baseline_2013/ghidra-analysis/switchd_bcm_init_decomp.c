/* bcm_init + soc_init + related decompilation */

/* === FUN_100a3680 @ 0x100a3680 (size=1116) === */

undefined4 FUN_100a3680(undefined4 param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined1 auStack_38 [16];
  undefined4 local_28;
  undefined4 local_24 [3];
  undefined4 local_18;
  undefined4 *local_14;
  
  local_24[0] = param_1;
  local_18 = param_1;
  local_14 = param_2;
  FUN_100c0b28(param_1,auStack_38);
  FUN_100c0970(auStack_38,&UNK_11339884,0x801,0,local_24,0);
  iVar3 = FUN_1008dfb4(local_14,auStack_38,&local_28);
  if (iVar3 != 0) {
    puVar4 = (undefined2 *)(**(code **)(DAT_11e45710 + 8))(local_24[0]);
    uVar2 = *puVar4;
    uVar1 = *(undefined1 *)(puVar4 + 1);
    iVar3 = FUN_1075eed8(uVar2,uVar1);
    if (iVar3 < 0) {
      local_28 = 0;
    }
    else {
      iVar3 = FUN_1075ef68(uVar2,uVar1,0,local_24[0]);
      if (iVar3 < 0) {
        if ((iVar3 < 1) && (-0x13 < iVar3)) {
          iVar3 = -iVar3;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10320d20("%s: soc_cm_device_create_id error : %s\n",*local_14,(&PTR_DAT_11e43a78)[iVar3]
                    );
        local_28 = 0xffffffff;
      }
      else {
        iVar3 = FUN_10109348(local_24[0]);
        if (iVar3 < 0) {
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10320d20("%s: sysconf_attach error : %s\n",*local_14,(&PTR_DAT_11e43a78)[iVar3]);
          local_28 = 0xffffffff;
        }
        else {
          iVar3 = FUN_10794970(local_24[0]);
          if (iVar3 < 0) {
            if ((iVar3 < 1) && (-0x13 < iVar3)) {
              iVar3 = -iVar3;
            }
            else {
              iVar3 = 0x13;
            }
            FUN_10320d20("%s: soc_init error : %s\n",*local_14,(&PTR_DAT_11e43a78)[iVar3]);
            local_28 = 0xffffffff;
          }
          else {
            iVar3 = FUN_10794638(local_24[0]);
            if (iVar3 < 0) {
              if ((iVar3 < 1) && (-0x13 < iVar3)) {
                iVar3 = -iVar3;
              }
              else {
                iVar3 = 0x13;
              }
              FUN_10320d20("%s: soc_misc_init error : %s\n",*local_14,(&PTR_DAT_11e43a78)[iVar3]);
              local_28 = 0xffffffff;
            }
            else {
              iVar3 = FUN_10e412f4(local_24[0]);
              if (iVar3 < 0) {
                if ((iVar3 < 1) && (-0x13 < iVar3)) {
                  iVar3 = -iVar3;
                }
                else {
                  iVar3 = 0x13;
                }
                FUN_10320d20("%s: soc_mmu_init error : %s\n",*local_14,(&PTR_DAT_11e43a78)[iVar3]);
                local_28 = 0xffffffff;
              }
              else {
                iVar3 = FUN_1038a8b4(local_24[0],&UNK_11339974,0,0);
                if (iVar3 < 0) {
                  if ((iVar3 < 1) && (-0x13 < iVar3)) {
                    iVar3 = -iVar3;
                  }
                  else {
                    iVar3 = 0x13;
                  }
                  FUN_10320d20("%s: bcm_attach error : %s\n",*local_14,(&PTR_DAT_11e43a78)[iVar3]);
                  local_28 = 0xffffffff;
                }
                else {
                  local_28 = 0;
                }
              }
            }
          }
        }
      }
    }
  }
  return local_28;
}



/* === FUN_104f0b7c @ 0x104f0b7c (size=7700) === */

int FUN_104f0b7c(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  if (((param_1 < 0) || (0x11 < param_1)) || ((&DAT_1212b9c4)[param_1] == 0)) {
    iVar2 = -3;
  }
  else {
    iVar2 = FUN_10540758(param_1);
    if ((-1 < iVar2) &&
       ((*(int *)(&DAT_1212ba54 + param_1 * 4) != 1 || (iVar2 = FUN_10644704(param_1), -1 < iVar2)))
       ) {
      if (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c30) & 0x800000) != 0) ||
         ((((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c34) & 0x8000) != 0 ||
           ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c4c) & 0x2000) != 0)) ||
          ((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) == 0 &&
           (((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x20000000) != 0 ||
            ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x20) != 0)))))))) {
        FUN_10760cd4(0x10000,"bcm_init: (%s)\n","common");
        iVar2 = FUN_113128a4();
        iVar3 = FUN_10b84db0(param_1);
        if ((iVar3 < 0) && (iVar3 != -0x10)) {
          return iVar3;
        }
        iVar3 = FUN_113128a4();
        FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","common",iVar3 - iVar2);
      }
      FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1958);
      iVar3 = FUN_113128a4();
      iVar2 = FUN_105b4b88(param_1);
      if ((-1 < iVar2) || (iVar2 == -0x10)) {
        iVar2 = FUN_113128a4();
        FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1958,iVar2 - iVar3);
        iVar2 = (&DAT_1212b9c4)[param_1];
        uVar4 = FUN_107953d0(param_1,"miim_intr_enable",1);
        *(undefined4 *)(iVar2 + 0xe6e0) = uVar4;
        uVar5 = FUN_11311498();
        if (((uVar5 & 0x400000) == 0) &&
           ((uVar5 = FUN_11311498(), (uVar5 & 0x8b0000) != 0 &&
            (iVar2 = FUN_107953d0(param_1,"skip_l2_vlan_init",0), iVar2 != 0)))) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (bVar1) {
          FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1954);
          iVar2 = FUN_113128a4();
          iVar3 = FUN_10505590(param_1);
          if ((iVar3 < 0) && (iVar3 != -0x10)) {
            return iVar3;
          }
          iVar3 = FUN_113128a4();
          FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1954,iVar3 - iVar2);
        }
        else {
          FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1954);
        }
        FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1950);
        iVar3 = FUN_113128a4();
        iVar2 = FUN_106b8b14(param_1);
        if ((-1 < iVar2) || (iVar2 == -0x10)) {
          iVar2 = FUN_113128a4();
          FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1950,iVar2 - iVar3);
          if (bVar1) {
            FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1948);
            iVar2 = FUN_113128a4();
            iVar3 = FUN_1071d5a0(param_1);
            if ((iVar3 < 0) && (iVar3 != -0x10)) {
              return iVar3;
            }
            iVar3 = FUN_113128a4();
            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1948,iVar3 - iVar2);
          }
          else {
            FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1948);
          }
          uVar5 = FUN_11311498();
          if (((uVar5 & 0x400000) == 0) && (uVar5 = FUN_11311498(), (uVar5 & 0x8b0000) != 0)) {
            bVar1 = false;
          }
          else {
            bVar1 = true;
          }
          if (bVar1) {
            FUN_10760cd4(0x10000,"bcm_init: (%s)\n","trunk");
            iVar2 = FUN_113128a4();
            iVar3 = FUN_10708038(param_1);
            if ((iVar3 < 0) && (iVar3 != -0x10)) {
              return iVar3;
            }
            iVar3 = FUN_113128a4();
            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","trunk",iVar3 - iVar2);
          }
          else {
            FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","trunk");
          }
          FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1938);
          iVar3 = FUN_113128a4();
          iVar2 = FUN_10465b54(param_1);
          if ((-1 < iVar2) || (iVar2 == -0x10)) {
            iVar2 = FUN_113128a4();
            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1938,iVar2 - iVar3);
            if (bVar1) {
              FUN_10760cd4(0x10000,"bcm_init: (%s)\n","mcast");
              iVar2 = FUN_113128a4();
              iVar3 = FUN_10540e2c(param_1);
              if ((iVar3 < 0) && (iVar3 != -0x10)) {
                return iVar3;
              }
              iVar3 = FUN_113128a4();
              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","mcast",iVar3 - iVar2);
            }
            else {
              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","mcast");
            }
            FUN_10760cd4(0x10000,"bcm_init: (%s)\n","linkscan");
            iVar3 = FUN_113128a4();
            iVar2 = FUN_1053caf8(param_1);
            if ((-1 < iVar2) || (iVar2 == -0x10)) {
              iVar2 = FUN_113128a4();
              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","linkscan",iVar2 - iVar3);
              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1a88);
              iVar3 = FUN_113128a4();
              iVar2 = FUN_10652ba0(param_1);
              if ((-1 < iVar2) || (iVar2 == -0x10)) {
                iVar2 = FUN_113128a4();
                FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1a88,iVar2 - iVar3)
                ;
                FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1a90);
                iVar3 = FUN_113128a4();
                iVar2 = FUN_1063f894(param_1);
                if ((-1 < iVar2) || (iVar2 == -0x10)) {
                  iVar2 = FUN_113128a4();
                  FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1a90,
                               iVar2 - iVar3);
                  if (bVar1) {
                    FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1a94);
                    iVar2 = FUN_113128a4();
                    iVar3 = FUN_10632e14(param_1);
                    if ((iVar3 < 0) && (iVar3 != -0x10)) {
                      return iVar3;
                    }
                    iVar3 = FUN_113128a4();
                    FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1a94,
                                 iVar3 - iVar2);
                  }
                  else {
                    FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1a94);
                  }
                  FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a18c0);
                  iVar3 = FUN_113128a4();
                  iVar2 = FUN_1071ba50(param_1);
                  if ((-1 < iVar2) || (iVar2 == -0x10)) {
                    iVar2 = FUN_113128a4();
                    FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a18c0,
                                 iVar2 - iVar3);
                    if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c28) & 0x2000000) != 0) {
                      if (bVar1) {
                        FUN_10760cd4(0x10000,"bcm_init: (%s)\n","field");
                        iVar2 = FUN_113128a4();
                        iVar3 = FUN_104b8f94(param_1);
                        if (iVar3 < 0) {
                          return iVar3;
                        }
                        iVar3 = FUN_113128a4();
                        FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","field",
                                     iVar3 - iVar2);
                      }
                      else {
                        FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","field");
                      }
                    }
                    FUN_10760cd4(0x10000,"bcm_init: (%s)\n","mirror");
                    iVar3 = FUN_113128a4();
                    iVar2 = FUN_1055f1f8(param_1);
                    if ((-1 < iVar2) || (iVar2 == -0x10)) {
                      iVar2 = FUN_113128a4();
                      FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","mirror",iVar2 - iVar3
                                  );
                      FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1a9c);
                      iVar3 = FUN_113128a4();
                      iVar2 = FUN_1071aa20(param_1);
                      if ((-1 < iVar2) || (iVar2 == -0x10)) {
                        iVar2 = FUN_113128a4();
                        FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1a9c,
                                     iVar2 - iVar3);
                        FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1904);
                        iVar3 = FUN_113128a4();
                        iVar2 = FUN_10635594(param_1);
                        if ((-1 < iVar2) || (iVar2 == -0x10)) {
                          iVar2 = FUN_113128a4();
                          FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1904,
                                       iVar2 - iVar3);
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c0c) & 0x8000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1900);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_1051dee0(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1900,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1900);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c0c) & 0x40000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a18f8);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_104ffb8c(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a18f8,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a18f8);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c14) & 0x4000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a18f0);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_10568ed0(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a18f0,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a18f0);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c30) & 0x20000000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1978);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_1054398c(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1978,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1978);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c34) & 0x40000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1970);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_1074d810(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1970,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1970);
                            }
                          }
                          if (bVar1) {
                            FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a18d4);
                            iVar2 = FUN_113128a4();
                            iVar3 = FUN_1062d918(param_1);
                            if (iVar3 < 0) {
                              return iVar3;
                            }
                            iVar3 = FUN_113128a4();
                            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a18d4,
                                         iVar3 - iVar2);
                          }
                          else {
                            FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a18d4);
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c28) & 0x40) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n","subport");
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_106ba7c8(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","subport",
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","subport");
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c38) & 8) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a197c);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_1062de60(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a197c,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a197c);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c3c) & 2) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n","trill");
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_10704a9c(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","trill",
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","trill");
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c3c) & 4) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&UNK_113a1aa8);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_10586f88(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&UNK_113a1aa8,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&UNK_113a1aa8);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c44) & 2) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&UNK_113a1aac);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_10519404(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&UNK_113a1aac,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&UNK_113a1aac);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c44) & 0x200000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&UNK_113a1ab4);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_107496d0(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&UNK_113a1ab4,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&UNK_113a1ab4);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c48) & 0x20) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n","extender");
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_104735b4(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","extender",
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","extender");
                            }
                          }
                          if (bVar1) {
                            FUN_10760cd4(0x10000,"bcm_init: (%s)\n","multicast");
                            iVar2 = FUN_113128a4();
                            iVar3 = FUN_1057a68c(param_1);
                            if (iVar3 < 0) {
                              return iVar3;
                            }
                            iVar3 = FUN_113128a4();
                            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","multicast",
                                         iVar3 - iVar2);
                          }
                          else {
                            FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","multicast");
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c28) & 0x2000000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a18c4);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_10460f38(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a18c4,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a18c4);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c34) & 0x100000) != 0) {
                            FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&UNK_113a18b8);
                            iVar2 = FUN_113128a4();
                            iVar3 = FUN_106f5e7c(param_1);
                            if (iVar3 < 0) {
                              return iVar3;
                            }
                            iVar3 = FUN_113128a4();
                            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&UNK_113a18b8,
                                         iVar3 - iVar2);
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c30) & 0x40000000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&UNK_113a1880);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_105889c0(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&UNK_113a1880,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&UNK_113a1880);
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c38) & 0x80) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n","failover");
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_104747cc(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","failover",
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n","failover");
                            }
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c40) & 0x80000) != 0) {
                            FUN_10760cd4(0x10000,"bcm_init: (%s)\n","global_meter");
                            iVar2 = FUN_113128a4();
                            iVar3 = FUN_1058e5a0(param_1);
                            if (iVar3 < 0) {
                              return iVar3;
                            }
                            iVar3 = FUN_113128a4();
                            FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n","global_meter",
                                         iVar3 - iVar2);
                          }
                          if ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x2f2c48) & 0x8000000) != 0) {
                            if (bVar1) {
                              FUN_10760cd4(0x10000,"bcm_init: (%s)\n",&DAT_113a1ad8);
                              iVar2 = FUN_113128a4();
                              iVar3 = FUN_10475fd8(param_1);
                              if (iVar3 < 0) {
                                return iVar3;
                              }
                              iVar3 = FUN_113128a4();
                              FUN_10760cd4(0x10000,"bcm_init: %8s   took %10d usec\n",&DAT_113a1ad8,
                                           iVar3 - iVar2);
                            }
                            else {
                              FUN_10760cd4(0x8000000,"bcm_init: skipped %s init\n",&DAT_113a1ad8);
                            }
                          }
                          if ((((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) != 0) ||
                               ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 4) == 0)) ||
                              ((iVar2 = FUN_10a96458(param_1), -1 < iVar2 &&
                               (iVar2 = FUN_10aa1bd8(param_1), -1 < iVar2)))) &&
                             ((((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) != 0 ||
                                ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x10000000) == 0)) &&
                               ((*(int *)((&DAT_1212b9c4)[param_1] + 0x10) != 0 ||
                                ((*(uint *)((&DAT_1212b9c4)[param_1] + 0x14) & 0x40000000) == 0))))
                              || ((*(int *)(&DAT_1212ba54 + param_1 * 4) == 1 ||
                                  (iVar2 = FUN_109630b0(param_1), -1 < iVar2)))))) {
                            if (*(int *)(&DAT_1212ba54 + param_1 * 4) == 1) {
                              *(undefined4 *)(&DAT_1212ba54 + param_1 * 4) = 0;
                            }
                            iVar2 = 0;
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
      }
    }
  }
  return iVar2;
}



/* === FUN_10e58d90 @ 0x10e58d90 (size=22724) === */

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



/* === FUN_108092ec @ 0x108092ec (size=4020) === */

int FUN_108092ec(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined *puVar8;
  int iVar9;
  int local_e8;
  uint local_e4;
  uint local_e0;
  int local_dc;
  undefined1 *local_d8;
  undefined1 auStack_c0 [80];
  undefined1 auStack_70 [88];
  int local_18;
  int local_14;
  uint local_10;
  undefined4 local_c;
  
  local_e8 = 0;
  local_dc = 0;
  local_d8 = *(undefined1 **)
              (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4
                       ) + 8);
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  memset(auStack_c0,0,0x50);
  memset(auStack_70,0,0x50);
  if ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c40) & 0x100) != 0) {
    if (local_14 == 0xcff) {
      local_14 = 0xcfe;
    }
    else if (local_14 == 0x1094) {
      local_14 = 0x1093;
    }
    else if (local_14 == 0x2e5) {
      local_14 = 0x26d;
    }
  }
  if (*(int *)((&DAT_1212ba0c)[local_18] + local_14 * 0xec + 0x31bc) -
      *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                       local_14 * 4) + 0xc) == -1) {
    local_e8 = 0;
  }
  else {
    if ((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
       (((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x7ffff67f) != 0 ||
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x10) != 0)) ||
         ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x40) != 0)) ||
        ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 0x20) != 0)))) {
      if (local_d8 == (undefined1 *)0x0) {
        local_d8 = auStack_c0;
      }
      FUN_11311c0c(*(undefined4 *)((&DAT_1212b9c4)[local_18] + local_14 * 700 + 0xe8f0),0xffffffff);
      local_e4 = (uint)*(ushort *)
                        (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                                 local_14 * 4) + 0x14);
      while( true ) {
        if ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                        local_14 * 4) & 0x10000) == 0) {
          uVar1 = *(ushort *)
                   (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                            local_14 * 4) + 0x16);
        }
        else {
          uVar1 = *(ushort *)
                   (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                            local_14 * 4) + 0x14);
        }
        if ((int)(uint)uVar1 < (int)local_e4) break;
        if ((int)local_e4 < 0x20) {
          uVar7 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24)
                                    + local_14 * 4) + 0x18) & 1 << (local_e4 & 0x3f);
        }
        else {
          uVar7 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24)
                                    + local_14 * 4) + 0x1c) & 1 << (local_e4 & 0x1f);
        }
        if (((uVar7 != 0) && (*(char *)((&DAT_1212b9c4)[local_18] + local_e4 + 0x909c) != '\0')) &&
           ((local_10 == 0xffffffff || (local_10 == local_e4)))) {
          uVar7 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24)
                                    + local_14 * 4) + 0xc);
          iVar9 = *(int *)((&DAT_1212ba0c)[local_18] + local_14 * 0xec + 0x31bc);
          local_e0 = uVar7;
          if ((*(uint *)(&DAT_1212b9c4)[local_18] & 0x100) == 0) {
LAB_10809900:
            for (; (int)local_e0 <= iVar9; local_e0 = local_e0 + 1) {
              local_e8 = FUN_108080ac(local_18,local_14,local_e4,local_e0,local_d8);
              if (local_e8 < 0) {
                if (local_e4 == 0xffffffff) {
                  puVar8 = &DAT_113c2aa4;
                }
                else {
                  puVar8 = (undefined *)
                           ((&DAT_1212b9c4)[local_18] + (local_e4 + 0x98f) * 0x10 + 0x10);
                }
                if ((local_e8 < 1) && (-0x13 < local_e8)) {
                  iVar9 = -local_e8;
                }
                else {
                  iVar9 = 0x13;
                }
                FUN_10760cd4(0x200000,"soc_mem_clear: write %s.%s[%d] failed: %s\n",
                             (&PTR_s_ACTIONPROFILETABLE_11ab46c8)[local_14],puVar8,local_e0,
                             (&PTR_DAT_11e43a78)[iVar9]);
                goto LAB_1080a184;
              }
            }
          }
          else {
            local_e8 = FUN_107fd258(local_18,local_14,local_e4,local_d8);
            if (local_e8 == -0x10) {
              iVar4 = FUN_107f59f8(local_18,local_14,local_e4);
              if (iVar4 == 0) goto LAB_10809900;
              local_e8 = FUN_107fcd80(local_18,local_14,local_e4,local_d8);
            }
          }
          iVar4 = *(int *)((&DAT_1212b9c4)[local_18] + (local_14 * 0xaf + local_e4 + 0x3a3c) * 4 + 4
                          );
          iVar2 = *(int *)((&DAT_1212b9c4)[local_18] + (local_14 * 0xaf + local_e4 + 0x3a74) * 4 +
                          0xc);
          if (((local_14 == 0x7d6) || (local_14 == 0x7e1)) || (local_14 == 0x7e2)) {
            if (local_14 == 0x7e1) {
              local_dc = *(int *)((&DAT_1212b9c4)[local_18] + (local_10 + 0x59df2) * 4 + 0xc);
            }
            else if (local_14 == 0x7e2) {
              local_dc = *(int *)((&DAT_1212b9c4)[local_18] + (local_10 + 0x59d43) * 4 + 0xc);
            }
          }
          iVar3 = (int)(*(ushort *)
                         (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                                  local_14 * 4) + 0x28) + 3) >> 2;
          if (((iVar4 != 0) && (*(char *)((&DAT_1212b9c4)[local_18] + 0x2f1868) == '\0')) &&
             (*(int *)(&DAT_1212ba54 + local_18 * 4) != 1)) {
            local_e0 = uVar7;
            if ((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c3c) & 0x100000) != 0) &&
                ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                             local_14 * 4) & 0x80000) != 0)) &&
               ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                            local_14 * 4) & 0x40000000) == 0)) {
              FUN_107fb1b8(local_18,local_14,1,local_d8,auStack_70,0);
            }
            for (; (int)local_e0 <= iVar9; local_e0 = local_e0 + 1) {
              iVar6 = (int)local_e0 >> 3;
              if ((*(int *)(&DAT_1212ba54 + local_18 * 4) == 1) ||
                 (((*(int *)(&DAT_1212ba54 + local_18 * 4) == 1 &&
                   (*(int *)((&DAT_1212b9c4)[local_18] + 0xe6d0) == 0)) ||
                  (*(int *)(&DAT_1212ba54 + local_18 * 4) == 4)))) {
                iVar5 = iVar6 + (uint)((int)local_e0 < 0 && (local_e0 & 7) != 0);
                *(byte *)(iVar2 + iVar5) =
                     *(byte *)(iVar2 + iVar5) &
                     ~(byte)(1 << (local_e0 +
                                   (iVar6 + (uint)((int)local_e0 < 0 && (local_e0 & 7) != 0)) * -8 &
                                  0x3f));
              }
              else if (local_dc == 0) {
                memcpy((void *)(iVar4 + local_e0 * iVar3 * 4),local_d8,iVar3 << 2);
                iVar5 = iVar6 + (uint)((int)local_e0 < 0 && (local_e0 & 7) != 0);
                *(byte *)(iVar2 + iVar5) =
                     *(byte *)(iVar2 + iVar5) &
                     ~(byte)(1 << (local_e0 +
                                   (iVar6 + (uint)((int)local_e0 < 0 && (local_e0 & 7) != 0)) * -8 &
                                  0x3f));
                if ((((*(uint *)((&DAT_1212b9c4)[local_18] + 0x2f2c3c) & 0x100000) != 0) &&
                    ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                                 local_14 * 4) & 0x80000) != 0)) &&
                   ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[local_18] + 0x2f26f4) + 0x24) +
                                local_14 * 4) & 0x40000000) == 0)) {
                  FUN_108257fc(local_18,local_14,local_e0,local_e0,auStack_70);
                }
              }
              else {
                iVar5 = iVar6 + (uint)((int)local_e0 < 0 && (local_e0 & 7) != 0);
                *(byte *)(iVar2 + iVar5) =
                     *(byte *)(iVar2 + iVar5) &
                     ~(byte)(1 << (local_e0 +
                                   (iVar6 + (uint)((int)local_e0 < 0 && (local_e0 & 7) != 0)) * -8 &
                                  0x3f));
                if (local_14 == 0x7e1) {
                  iVar6 = ((int)local_e0 >> 4) + (uint)((int)local_e0 < 0 && (local_e0 & 0xf) != 0);
                  uVar7 = ((int)local_e0 >> 1) + (uint)((int)local_e0 < 0 && (local_e0 & 1) != 0);
                  *(byte *)(local_dc + iVar6) =
                       *(byte *)(local_dc + iVar6) &
                       ~(byte)(1 << (uVar7 + (((int)uVar7 >> 3) +
                                             (uint)((int)uVar7 < 0 && (uVar7 & 7) != 0)) * -8 & 0x3f
                                    ));
                }
                else {
                  uVar7 = local_e0 << 1 | local_e0 >> 0x1f;
                  iVar5 = ((int)uVar7 >> 3) + (uint)((int)uVar7 < 0 && (local_e0 << 1 & 6) != 0);
                  iVar6 = local_e0 * 2;
                  *(byte *)(local_dc + iVar5) =
                       *(byte *)(local_dc + iVar5) &
                       ~(byte)(1 << (iVar6 + ((iVar6 >> 3) +
                                             (uint)(iVar6 < 0 && (local_e0 & 3) != 0)) * -8 & 0x3f))
                  ;
                  uVar7 = local_e0 * 2 + 1;
                  iVar6 = ((int)uVar7 >> 3) + (uint)((int)uVar7 < 0 && (uVar7 & 7) != 0);
                  uVar7 = local_e0 * 2 + 1;
                  *(byte *)(local_dc + iVar6) =
                       *(byte *)(local_dc + iVar6) &
                       ~(byte)(1 << (uVar7 + (((int)uVar7 >> 3) +
                                             (uint)((int)uVar7 < 0 && (uVar7 & 7) != 0)) * -8 & 0x3f
                                    ));
                }
              }
            }
          }
        }
        local_e4 = local_e4 + 1;
      }
      if (((*(int *)((&DAT_1212b9c4)[local_18] + 0x10) == 0) &&
          ((*(uint *)((&DAT_1212b9c4)[local_18] + 0x14) & 4) != 0)) &&
         (((local_14 == 0xa15 || ((local_14 == 0xa16 || (local_14 == 0xa18)))) ||
          (local_14 == 0xa19)))) {
        local_e8 = FUN_11279484(local_18,local_14);
      }
    }
    else {
      local_e8 = 0;
    }
LAB_1080a184:
    FUN_11311d68(*(undefined4 *)((&DAT_1212b9c4)[local_18] + local_14 * 700 + 0xe8f0));
    if (local_10 == 0xffffffff) {
      puVar8 = &DAT_113c2aa4;
    }
    else {
      puVar8 = (undefined *)((&DAT_1212b9c4)[local_18] + (local_10 + 0x98f) * 0x10 + 0x10);
    }
    if ((local_e8 < 1) && (-0x13 < local_e8)) {
      iVar9 = -local_e8;
    }
    else {
      iVar9 = 0x13;
    }
    FUN_10760cd4(4,"soc_mem_clear: unit %d memory %s.%s returns %s\n",local_18,
                 (&PTR_s_ACTIONPROFILETABLE_11ab46c8)[local_14],puVar8,(&PTR_DAT_11e43a78)[iVar9]);
  }
  return local_e8;
}



/* === FUN_10051be0 @ 0x10051be0 (size=15376) === */

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



/* === FUN_1008ea38 @ 0x1008ea38 (size=208) === */

void FUN_1008ea38(int param_1,undefined4 *param_2)

{
  char *pcVar1;
  
  if ((param_1 < 0) || (0x11 < param_1)) {
    FUN_113113b0("unit >= 0 && unit < SOC_MAX_NUM_DEVICES",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/appl/diag/system.c"
                 ,0x775);
  }
  if ((-1 < param_1) && (param_1 < 0x12)) {
    if (*(int *)(&DAT_11e8c5b0 + param_1 * 4) == 0) {
      pcVar1 = "/etc/bcm.d/rc.soc";
    }
    else {
      pcVar1 = *(char **)(&DAT_11e8c5b0 + param_1 * 4);
    }
    *param_2 = pcVar1;
  }
  return;
}



/* === FUN_1031f050 @ 0x1031f050 (size=1272) === */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int FUN_1031f050(void)

{
  int iVar1;
  FILE *__stream;
  size_t sVar2;
  ushort **ppuVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  int local_b8;
  undefined4 *local_b4;
  char *local_b0;
  int local_ac;
  int local_a8;
  char *local_a4;
  char local_8c [140];
  
  local_b8 = 0;
  local_ac = 0;
  pcVar7 = DAT_11eb95d8;
  if (DAT_11eb95d8 == (char *)0x0) {
    pcVar7 = "/etc/bcm.d/config.bcm";
  }
  if (*pcVar7 != '\0') {
    pcVar8 = DAT_11eb95dc;
    if (DAT_11eb95dc == (char *)0x0) {
      pcVar8 = "config.tmp";
    }
    if ((pcVar8 == (char *)0x0) || (*pcVar8 == '\0')) {
      FUN_113113b0("tname != NULL && tname[0] != 0",
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/sal/appl/config.c"
                   ,0x28f);
    }
    iVar1 = FUN_10321398(pcVar8,&DAT_11386fc8);
    if (iVar1 == 0) {
      local_b8 = -1;
    }
    else {
      __stream = (FILE *)FUN_10321398(pcVar7,&UNK_11386de4);
      for (local_a8 = 0; local_a8 < 0x400; local_a8 = local_a8 + 1) {
        for (local_b4 = *(undefined4 **)(&DAT_11eb95e0 + local_a8 * 4);
            local_b4 != (undefined4 *)0x0; local_b4 = (undefined4 *)*local_b4) {
          *(undefined2 *)(local_b4 + 3) = 0;
        }
      }
      while ((__stream != (FILE *)0x0 &&
             (pcVar6 = fgets(local_8c,0x80,__stream), pcVar6 != (char *)0x0))) {
        local_ac = local_ac + 1;
        sVar2 = strlen(local_8c);
        local_b0 = local_8c + sVar2;
        while ((local_8c < local_b0 &&
               (ppuVar3 = __ctype_b_loc(), ((*ppuVar3)[(byte)local_b0[-1]] & 0x20) != 0))) {
          local_b0 = local_b0 + -1;
        }
        *local_b0 = '\0';
        if ((local_8c[0] == '\0') ||
           ((local_8c[0] == '#' && (pcVar6 = strchr(local_8c,0x3d), pcVar6 == (char *)0x0)))) {
          __nldbl_fprintf(iVar1,&DAT_11386fcc,local_8c);
        }
        else {
          local_a4 = local_8c;
          if (local_8c[0] == '#') {
            local_a4 = local_8c + 1;
          }
          iVar4 = FUN_1031e7dc(local_a4);
          if (iVar4 == 0) {
            FUN_100733d0("sal_config_flush: format error in %s on line %d (removed)\n",pcVar7,
                         local_ac);
          }
          else {
            iVar5 = FUN_1031e26c(*(undefined4 *)(iVar4 + 4));
            if ((iVar5 == 0) || (*(short *)(iVar5 + 0xc) == 1)) {
              __nldbl_fprintf(iVar1,&DAT_1138700c,*(undefined4 *)(iVar4 + 4),
                              *(undefined4 *)(iVar4 + 8));
            }
            else {
              __nldbl_fprintf(iVar1,&DAT_11387014,*(undefined4 *)(iVar5 + 4),
                              *(undefined4 *)(iVar5 + 8));
              *(undefined2 *)(iVar5 + 0xc) = 1;
            }
            if (iVar4 != 0) {
              if (*(int *)(iVar4 + 4) != 0) {
                FUN_113110d0(*(undefined4 *)(iVar4 + 4));
              }
              if (*(int *)(iVar4 + 8) != 0) {
                FUN_113110d0(*(undefined4 *)(iVar4 + 8));
              }
              FUN_113110d0(iVar4);
            }
          }
        }
      }
      for (local_a8 = 0; local_a8 < 0x400; local_a8 = local_a8 + 1) {
        for (local_b4 = *(undefined4 **)(&DAT_11eb95e0 + local_a8 * 4);
            local_b4 != (undefined4 *)0x0; local_b4 = (undefined4 *)*local_b4) {
          if (*(short *)(local_b4 + 3) == 0) {
            __nldbl_fprintf(iVar1,&DAT_11387014,local_b4[1],local_b4[2]);
          }
        }
      }
      FUN_103213e0(iVar1);
      if (__stream != (FILE *)0x0) {
        FUN_103213e0(__stream);
      }
      local_b8 = FUN_103215d8(pcVar8,pcVar7);
      if (local_b8 != 0) {
        FUN_10321598(pcVar8);
      }
    }
    if (local_b8 < 0) {
      FUN_100733d0("sal_config_flush: variables not saved\n");
    }
  }
  return local_b8;
}



/* === FUN_10109348 @ 0x10109348 (size=876) === */

undefined4 FUN_10109348(int param_1)

{
  short *psVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_c4 [4];
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  code *local_b0;
  code *local_ac;
  code *local_a8;
  undefined4 local_a4;
  code *local_a0;
  code *local_9c;
  code *local_98;
  code *local_94;
  code *local_90;
  code *local_8c;
  code *local_88;
  code *local_84;
  code *local_80;
  code *local_7c;
  code *local_78;
  code *local_74;
  code *local_70;
  code *local_6c;
  undefined1 auStack_5c [68];
  int local_18;
  
  local_18 = param_1;
  psVar1 = (short *)(**(code **)(DAT_11e45710 + 8))(param_1);
  FUN_11310e2c(auStack_5c,"extra_unit.%d",local_18);
  iVar2 = FUN_1010844c(auStack_5c);
  if (iVar2 == 0) {
    if ((local_18 < 0) || (iVar2 = (**(code **)(DAT_11e45710 + 4))(0), iVar2 <= local_18)) {
      FUN_113113b0("unit >= 0 && unit < bde->num_devices(BDE_ALL_DEVICES)",
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/appl/diag/sysconf.c"
                   ,0x2ae);
    }
    if (*psVar1 == 0x280) {
      local_c0 = 1;
      local_bc = 0;
      local_b8 = 1;
    }
    else {
      (**(code **)(DAT_11e45710 + 0x18))(local_18,&local_c0,&local_bc,&local_b8);
    }
    local_b0 = FUN_1010848c;
    local_ac = FUN_10108968;
    local_a8 = FUN_101089d0;
    iVar2 = (**(code **)(DAT_11e45710 + 8))(local_18);
    local_a4 = *(undefined4 *)(iVar2 + 4);
    local_a0 = FUN_10108530;
    local_9c = FUN_101084d0;
    local_98 = FUN_10108ae0;
    local_94 = FUN_10108a80;
    local_90 = FUN_101085e8;
    local_8c = FUN_10108650;
    local_84 = FUN_1010872c;
    local_88 = FUN_101086a8;
    local_80 = FUN_101087b0;
    local_7c = FUN_1010882c;
    local_70 = FUN_10108908;
    local_6c = FUN_101088a8;
    local_b4 = (**(code **)(DAT_11e45710 + 0xc))(local_18);
    local_78 = FUN_10108b40;
    local_74 = FUN_10108bcc;
    iVar2 = FUN_1075f26c(local_18,auStack_c4);
    if (iVar2 < 0) {
      FUN_10320d20("sysconf_attach: bcm device init failed\n");
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    local_b0 = FUN_1010848c;
    local_ac = FUN_10108a28;
    local_a8 = FUN_10108a58;
    local_a4 = 0;
    local_a0 = FUN_101085bc;
    local_9c = FUN_10108590;
    local_98 = FUN_10108ae0;
    local_94 = FUN_10108a80;
    local_90 = FUN_101085e8;
    local_8c = FUN_10108650;
    local_84 = FUN_1010872c;
    local_88 = FUN_101086a8;
    local_80 = FUN_101087b0;
    local_7c = FUN_1010882c;
    local_b4 = 0;
    iVar2 = FUN_1075f26c(local_18,auStack_c4);
    if (iVar2 < 0) {
      FUN_10320d20("sysconf_attach: bcm device init failed\n");
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}



/* === FUN_107edc58 @ 0x107edc58 (size=852) === */

int FUN_107edc58(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint local_10;
  
  if ((((param_2 < 0) || (0x10e3 < param_2)) ||
      (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) == 0))
     || ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4)
         & 2) == 0)) {
    FUN_113113b0(&DAT_113c291c,
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x855);
  }
  iVar2 = FUN_10794b20(param_1);
  if (iVar2 == 0) {
    FUN_113113b0("soc_attached(unit)",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x856);
  }
  if ((**(uint **)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) + param_2 * 4) & 8
      ) == 0) {
    FUN_113113b0("soc_mem_is_sorted(unit,mem)",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
                 ,0x857);
  }
  local_10 = param_3;
  if (param_3 == 0xffffffff) {
    local_10 = *(uint *)((&DAT_1212b9c4)[param_1] + (param_2 + 0x2724) * 4 + 0x10);
  }
  if ((-1 < (int)local_10) && ((int)local_10 < 0x3a)) {
    if ((int)local_10 < 0x20) {
      uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 0x18) & 1 << (local_10 & 0x3f);
    }
    else {
      uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                                param_2 * 4) + 0x1c) & 1 << (local_10 & 0x1f);
    }
    if ((uVar1 != 0) && (*(char *)((&DAT_1212b9c4)[param_1] + local_10 + 0x909c) != '\0'))
    goto LAB_107edf10;
  }
  FUN_113113b0("SOC_MEM_BLOCK_VALID(unit, mem, copyno)",
               "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/src/soc/common/mem.c"
               ,0x85e);
LAB_107edf10:
  return *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                          param_2 * 4) + 0xc) +
         *(int *)((&DAT_1212ba0c)[param_1] + (param_2 * 0x3b + local_10 + 0xc34) * 4 + 4) + -1;
}



/* NO FUNCTION at 0x10cfcdc */

