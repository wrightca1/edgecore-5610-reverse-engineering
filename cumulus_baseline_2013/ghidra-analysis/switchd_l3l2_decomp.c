/* L3, L2, ECMP, Linkscan, KNET stubs decompilation */

/* === FUN_1005f1b4 (size=1480) === */

undefined4 FUN_1005f1b4(int param_1,int param_2,char param_3)

{
  char cVar4;
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_e0 [8];
  int local_c0;
  int local_b0;
  uint local_80 [2];
  undefined4 local_78;
  int local_60;
  int local_50;
  int local_18;
  int local_14;
  char local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  if ((*(uint *)(param_2 + 0x1c) & 0x10) == 0) {
    cVar4 = FUN_1005ec04(param_1,param_2,local_e0);
    if (cVar4 != '\x01') {
      pvVar1 = (void *)FUN_10028710(local_14);
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT %s: hal_route_to_hw_route failed for hal route %s\n",0x41,
                     uVar2,&DAT_11322924,0xf52,"add_update_route",pvVar1);
      }
      free(pvVar1);
      return 0;
    }
    if (local_10 != '\0') {
      local_e0[0] = local_e0[0] | 0x100;
      FUN_1005ed68(local_14,local_80);
      iVar3 = FUN_103f8e24(*(undefined4 *)(local_18 + 4),local_80);
      if (iVar3 < 0) {
        pvVar1 = (void *)FUN_10028710(local_14);
        if (-1 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(0,"%s %s:%d CRIT bcm_l3_route_get failed for hal route %s: %s\n",0x3c,uVar2,
                       &DAT_11322924,0xf5f,pvVar1,(&PTR_DAT_11e43a78)[iVar3]);
        }
        free(pvVar1);
        FUN_1005ee54(local_18,local_b0,(local_e0[0] & 0x4000) != 0);
        return 0;
      }
    }
    iVar3 = FUN_103f85a0(*(undefined4 *)(local_18 + 4),local_e0);
    if (iVar3 < 0) {
      pvVar1 = (void *)FUN_10028710(local_14);
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        if ((iVar3 < 1) && (-0x13 < iVar3)) {
          iVar3 = -iVar3;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(0,"%s %s:%d CRIT bcm_l3_route_add failed for hal route %s: %s\n",0x3c,uVar2,
                     &DAT_11322924,0xf6c,pvVar1,(&PTR_DAT_11e43a78)[iVar3]);
      }
      free(pvVar1);
      FUN_1005ee54(local_18,local_b0,(local_e0[0] & 0x4000) != 0);
      return 0;
    }
    if ((local_10 != '\0') && (local_50 != local_b0)) {
      FUN_1005ee54(local_18,local_50,(local_80[0] & 0x4000) != 0);
    }
  }
  else {
    cVar4 = FUN_1005ea18(param_1,param_2,local_e0);
    if (cVar4 != '\x01') {
      pvVar1 = (void *)FUN_10028710(local_14);
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT %s: hal_route_to_hw_host failed for hal route %s\n",0x40,uVar2
                     ,&DAT_11322924,0xf30,"add_update_route",pvVar1);
      }
      free(pvVar1);
      return 0;
    }
    if (local_10 != '\0') {
      local_e0[0] = local_e0[0] | 0x100;
      FUN_1005eb3c(local_14,local_80);
      iVar3 = FUN_103f3ab4(*(undefined4 *)(local_18 + 4),local_80);
      if (iVar3 < 0) {
        if (-1 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(0,"%s %s:%d CRIT bcm_l3_host_find %x failed: %s\n",0x2e,uVar2,&DAT_11322924,
                       0xf3b,local_78,(&PTR_DAT_11e43a78)[iVar3]);
        }
        return 0;
      }
    }
    iVar3 = FUN_103f3128(*(undefined4 *)(local_18 + 4),local_e0);
    if (iVar3 < 0) {
      pvVar1 = (void *)FUN_10028710(local_14);
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        if ((iVar3 < 1) && (-0x13 < iVar3)) {
          iVar3 = -iVar3;
        }
        else {
          iVar3 = 0x13;
        }
        FUN_10047040(0,"%s %s:%d CRIT bcm_l3_host_add failed for hal route %s: %s\n",0x3b,uVar2,
                     &DAT_11322924,0xf42,pvVar1,(&PTR_DAT_11e43a78)[iVar3]);
      }
      free(pvVar1);
      return 0;
    }
    if ((local_10 != '\0') && (local_60 != local_c0)) {
      FUN_1005ee54(local_18,local_60,0);
    }
  }
  return 1;
}



/* === FUN_1005f7d0 (size=872) === */

void FUN_1005f7d0(int param_1,int param_2)

{
  char cVar4;
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_80 [8];
  undefined4 local_60;
  undefined4 local_50;
  int local_18;
  int local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  if ((*(uint *)(param_2 + 0x1c) & 0x10) == 0) {
    cVar4 = FUN_1005ec04(param_1,param_2,local_80);
    if (cVar4 == '\x01') {
      iVar3 = FUN_103f883c(*(undefined4 *)(param_1 + 4),local_80);
      if (iVar3 < 0) {
        pvVar1 = (void *)FUN_10028710(local_14);
        if (-1 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(0,"%s %s:%d CRIT bcm_l3_route_delete hal route %s failed: %s\n",0x3b,uVar2,
                       &DAT_11322924,0xfae,pvVar1,(&PTR_DAT_11e43a78)[iVar3]);
        }
        free(pvVar1);
        FUN_1005ee54(param_1,local_50,(local_80[0] & 0x4000) != 0);
      }
      else {
        FUN_1005ee54(param_1,local_50,(local_80[0] & 0x4000) != 0);
      }
    }
    else {
      pvVar1 = (void *)FUN_10028710(local_14);
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT %s: HW route not found for HAL route %s\n",0x37,uVar2,
                     &DAT_11322924,0xfa5,"hal_bcm_remove_route",pvVar1);
      }
      free(pvVar1);
    }
  }
  else {
    cVar4 = FUN_1005ea18(param_1,param_2,local_80);
    if (cVar4 == '\x01') {
      iVar3 = FUN_103f34f4(*(undefined4 *)(param_1 + 4),local_80);
      if (iVar3 < 0) {
        pvVar1 = (void *)FUN_10028710(local_14);
        if (-1 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(0,"%s %s:%d CRIT bcm_l3_host_delete for HAL route %s failed: %s\n",0x3e,uVar2
                       ,&DAT_11322924,0xf98,pvVar1,(&PTR_DAT_11e43a78)[iVar3]);
        }
        free(pvVar1);
      }
      else {
        FUN_1005ee54(param_1,local_60,0);
      }
    }
    else {
      pvVar1 = (void *)FUN_10028710(local_14);
      if (-1 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT %s: HW host not found for HAL route %s\n",0x36,uVar2,
                     &DAT_11322924,0xf8e,"hal_bcm_remove_route",pvVar1);
      }
      free(pvVar1);
    }
  }
  return;
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



/* === FUN_100124d0 (size=3280) === */

undefined4 FUN_100124d0(undefined4 param_1,void *param_2,char param_3)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  void *pvVar4;
  undefined4 uVar5;
  char cVar11;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  void *pvVar9;
  undefined1 uVar12;
  int iVar10;
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
  uVar5 = rtnl_route_get_dst(param_1);
  cVar11 = rtnl_route_get_type(local_18);
  uVar6 = rtnl_route_get_flags(local_18);
  local_28 = 0;
  iVar7 = rtnl_route_get_table(local_18);
  if ((iVar7 != DAT_11e4563c) && (iVar7 = rtnl_route_get_table(local_18), iVar7 != 0xff)) {
    FUN_113113b0("rtnl_route_get_table(route) == route_table_num || rtnl_route_get_table(route) == RT_TABLE_LOCAL"
                 ,&DAT_1131932c,0xa5b);
  }
  if ((uVar6 & 0x200) == 0) {
    iVar7 = rtnl_route_get_family(local_18);
    if ((iVar7 == 2) || (iVar7 = rtnl_route_get_family(local_18), iVar7 == 10)) {
      if ((uVar6 == 0) || (((uVar6 & 4) != 0 || ((uVar6 & 1) != 0)))) {
        if ((cVar11 == '\x01') ||
           (((cVar11 == '\x06' || (cVar11 == '\a')) ||
            ((iVar7 = rtnl_route_get_table(local_18), iVar7 == 0xff &&
             ((cVar11 == '\x02' || (cVar11 == '\x03')))))))) {
          iVar7 = rtnl_route_get_tos(local_18);
          if (iVar7 == 0) {
            iVar7 = rtnl_route_get_src(local_18);
            if (iVar7 == 0) {
              iVar7 = rtnl_route_get_iif(local_18);
              if (iVar7 == 0) {
                if (cVar11 == '\a') {
                  local_150 = 1;
                }
                else {
                  rtnl_route_foreach_nexthop(local_18,FUN_100131a0,&local_28);
                  local_150 = DAT_11f1c62c;
                  if (local_28 < DAT_11f1c62c) {
                    local_150 = local_28;
                  }
                }
                FUN_100278fc(local_14,local_150);
                iVar7 = rtnl_route_get_family(local_18);
                bVar1 = iVar7 != 10;
                if (bVar1) {
                  *(undefined1 *)((int)local_14 + 0x10) = 2;
                }
                else {
                  *(undefined1 *)((int)local_14 + 0x10) = 10;
                }
                iVar7 = nl_addr_get_len(uVar5);
                if (iVar7 == 0) {
                  memset(local_14,0,0x10);
                }
                else {
                  if (bVar1) {
                    iVar7 = nl_addr_get_len(uVar5);
                    if (iVar7 != 4) {
                      FUN_113113b0("nl_addr_get_len(dst) == 4",&DAT_1131932c,0xab9);
                    }
                    pvVar4 = local_14;
                    pvVar9 = (void *)nl_addr_get_binary_addr(uVar5);
                    memcpy(pvVar4,pvVar9,4);
                  }
                  else {
                    iVar7 = nl_addr_get_len(uVar5);
                    if (iVar7 != 0x10) {
                      FUN_113113b0("nl_addr_get_len(dst) == 16",&DAT_1131932c,0xab5);
                    }
                    pvVar4 = local_14;
                    pvVar9 = (void *)nl_addr_get_binary_addr(uVar5);
                    memcpy(pvVar4,pvVar9,0x10);
                  }
                  iVar7 = FUN_10029278(local_14);
                  if (iVar7 != 0) {
                    memset(auStack_128,0,0x100);
                    if ((3 < DAT_11e45404) &&
                       (nl_object_dump_buf(local_18,auStack_128,0xff), 3 < DAT_11e45404)) {
                      uVar5 = FUN_10046f5c();
                      FUN_10047040(4,"%s %s:%d Route [%s] is loopback - ignore\n",0x2a,uVar5,
                                   &DAT_1131932c,0xac4,auStack_128);
                    }
                    FUN_10027a00(local_14);
                    return 0;
                  }
                }
                uVar12 = nl_addr_get_prefixlen(uVar5);
                *(undefined1 *)((int)local_14 + 0x11) = uVar12;
                uVar5 = rtnl_route_get_priority(local_18);
                *(undefined4 *)((int)local_14 + 0x18) = uVar5;
                if ((local_10 == '\0') && (cVar11 != '\a')) {
                  local_24[0] = 0;
                  iVar7 = rtnl_route_get_nnexthops(local_18);
                  if ((uVar6 & 4) != 0) {
                    *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x20;
                  }
                  if (*(int *)((int)local_14 + 0x20) == 0) {
                    if (cVar11 != '\x06') {
                      FUN_113113b0("route_type == RTN_BLACKHOLE",&DAT_1131932c,0xafc);
                    }
                  }
                  else {
                    *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 8;
                    local_154 = 0;
                    while ((local_154 < iVar7 && (local_24[0] < *(int *)((int)local_14 + 0x20)))) {
                      uVar5 = rtnl_route_nexthop_n(local_18,local_154);
                      iVar10 = *(int *)((int)local_14 + 0x24) + local_24[0] * 0x24;
                      cVar11 = FUN_10011be8(uVar5,iVar10,*(char *)((int)local_14 + 0x10) == '\n');
                      if (cVar11 != '\x01') {
                        FUN_10027a00(local_14);
                        return 0;
                      }
                      if ((*(uint *)(iVar10 + 0x20) & 1) == 0) {
                        *(uint *)((int)local_14 + 0x1c) =
                             *(uint *)((int)local_14 + 0x1c) & 0xfffffff7;
                      }
                      uVar6 = rtnl_route_nh_get_flags(uVar5);
                      if ((uVar6 & 4) != 0) {
                        *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x20;
                      }
                      iVar10 = memcmp((void *)(*(int *)((int)local_14 + 0x24) + local_24[0] * 0x24),
                                      &DAT_118190e4,0x14);
                      if (iVar10 == 0) {
                        *(int *)((int)local_14 + 0x20) = *(int *)((int)local_14 + 0x20) + -1;
                      }
                      else {
                        local_24[0] = local_24[0] + 1;
                        if (iVar7 < local_28) {
                          FUN_10013204(uVar5,local_14,local_28,local_150,local_24);
                        }
                      }
                      local_154 = local_154 + 1;
                    }
                    if ((local_154 < iVar7) && (3 < DAT_11e45404)) {
                      memset(auStack_128,0,0x100);
                      nl_object_dump_buf(local_18,auStack_128,0xff);
                      if (3 < DAT_11e45404) {
                        uVar5 = FUN_10046f5c();
                        FUN_10047040(4,"%s %s:%d Route [%s] next-hops are truncated.\n",0x2e,uVar5,
                                     &DAT_1131932c,0xb30,auStack_128);
                      }
                    }
                    if (*(int *)((int)local_14 + 0x20) == 0) {
                      *(undefined4 *)((int)local_14 + 0x20) = 1;
                      uVar3 = DAT_118190f0;
                      uVar8 = DAT_118190ec;
                      uVar5 = DAT_118190e8;
                      puVar2 = *(undefined4 **)((int)local_14 + 0x24);
                      *puVar2 = DAT_118190e4;
                      puVar2[1] = uVar5;
                      puVar2[2] = uVar8;
                      puVar2[3] = uVar3;
                      puVar2[4] = DAT_118190f4;
                      memset((void *)(*(int *)((int)local_14 + 0x24) + 0x18),0,6);
                    }
                    if (1 < *(int *)((int)local_14 + 0x20)) {
                      qsort(*(void **)((int)local_14 + 0x24),*(size_t *)((int)local_14 + 0x20),0x24,
                            FUN_10028148);
                    }
                  }
                }
                else {
                  iVar7 = rtnl_route_nexthop_n(local_18,0);
                  if ((uVar6 & 4) != 0) {
                    FUN_113113b0("(route_flags & RTNH_F_ONLINK) == 0",&DAT_1131932c,0xad2);
                  }
                  if ((iVar7 != 0) && (cVar11 != '\a')) {
                    uVar5 = rtnl_route_nh_get_ifindex(iVar7);
                    iVar10 = FUN_1000b718(uVar5);
                    if (iVar10 == 0) {
                      *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) & 0xfffffff7
                      ;
                    }
                    else {
                      *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 8;
                    }
                    if (DAT_11e4565b != '\0') {
                      uVar5 = rtnl_route_nh_get_ifindex(iVar7);
                      iVar10 = FUN_1000be10(uVar5);
                      if (iVar10 != 0) {
                        FUN_10027a00(local_14);
                        return 0;
                      }
                    }
                  }
                  if (cVar11 != '\a') {
                    if (*(int *)((int)local_14 + 0x20) != 1) {
                      FUN_113113b0("hal_route->num_next_hops == 1",&DAT_1131932c,0xae8);
                    }
                    if ((bVar1) && (iVar7 = rtnl_route_nh_get_gateway(iVar7), iVar7 != 0)) {
                      FUN_113113b0("ipv6 || !rtnl_route_nh_get_gateway(nh)",&DAT_1131932c,0xae9);
                    }
                  }
                  if (local_10 != '\0') {
                    *(uint *)((int)local_14 + 0x1c) = *(uint *)((int)local_14 + 0x1c) | 0x40;
                  }
                  uVar3 = DAT_118190f0;
                  uVar8 = DAT_118190ec;
                  uVar5 = DAT_118190e8;
                  puVar2 = *(undefined4 **)((int)local_14 + 0x24);
                  *puVar2 = DAT_118190e4;
                  puVar2[1] = uVar5;
                  puVar2[2] = uVar8;
                  puVar2[3] = uVar3;
                  puVar2[4] = DAT_118190f4;
                  memset((void *)(*(int *)((int)local_14 + 0x24) + 0x18),0,6);
                }
                uVar5 = 1;
              }
              else {
                memset(auStack_128,0,0x100);
                nl_object_dump_buf(local_18,auStack_128,0xff);
                if (1 < DAT_11e45404) {
                  uVar5 = FUN_10046f5c();
                  uVar8 = rtnl_route_get_iif(local_18);
                  FUN_10047040(2,"%s %s:%d WARN Route [%s] has non-zero iif: %d\n",0x2f,uVar5,
                               &DAT_1131932c,0xa9f,auStack_128,uVar8);
                }
                uVar5 = 0;
              }
            }
            else {
              memset(auStack_128,0,0x100);
              nl_object_dump_buf(local_18,auStack_128,0xff);
              if (1 < DAT_11e45404) {
                uVar5 = FUN_10046f5c();
                FUN_10047040(2,"%s %s:%d WARN Route [%s] has non-NULL src.\n",0x2c,uVar5,
                             &DAT_1131932c,0xa98,auStack_128);
              }
              uVar5 = 0;
            }
          }
          else {
            memset(auStack_128,0,0x100);
            nl_object_dump_buf(local_18,auStack_128,0xff);
            if (1 < DAT_11e45404) {
              uVar5 = FUN_10046f5c();
              uVar8 = rtnl_route_get_tos(local_18);
              FUN_10047040(2,"%s %s:%d WARN Route [%s] has unexpected tos: %d\n",0x31,uVar5,
                           &DAT_1131932c,0xa92,auStack_128,uVar8);
            }
            uVar5 = 0;
          }
        }
        else {
          memset(auStack_128,0,0x100);
          nl_object_dump_buf(local_18,auStack_128,0xff);
          if (1 < DAT_11e45404) {
            uVar5 = FUN_10046f5c();
            FUN_10047040(2,"%s %s:%d WARN Route [%s] has unexpected type: %d\n",0x32,uVar5,
                         &DAT_1131932c,0xa8b,auStack_128,cVar11);
          }
          uVar5 = 0;
        }
      }
      else {
        memset(auStack_128,0,0x100);
        nl_object_dump_buf(local_18,auStack_128,0xff);
        if (1 < DAT_11e45404) {
          uVar5 = FUN_10046f5c();
          uVar8 = rtnl_route_get_flags(local_18);
          FUN_10047040(2,"%s %s:%d WARN Route [%s] has unexpected flags: %d\n",0x33,uVar5,
                       &DAT_1131932c,0xa80,auStack_128,uVar8);
        }
        uVar5 = 0;
      }
    }
    else {
      memset(auStack_128,0,0x100);
      nl_object_dump_buf(local_18,auStack_128,0xff);
      if (1 < DAT_11e45404) {
        uVar5 = FUN_10046f5c();
        uVar8 = rtnl_route_get_family(local_18);
        FUN_10047040(2,"%s %s:%d WARN Route [%s] is not IPv4 or v6, family: %d\n",0x38,uVar5,
                     &DAT_1131932c,0xa77,auStack_128,uVar8);
      }
      uVar5 = 0;
    }
  }
  else {
    if (3 < DAT_11e45404) {
      memset(auStack_128,0,0x100);
      nl_object_dump_buf(local_18,auStack_128,0xff);
      if (3 < DAT_11e45404) {
        uVar5 = FUN_10046f5c();
        FUN_10047040(4,"%s %s:%d Route [%s] is from kernel cache\n",0x2a,uVar5,&DAT_1131932c,0xa6e,
                     auStack_128);
      }
    }
    uVar5 = 0;
  }
  return uVar5;
}



/* === FUN_103f85a0 (size=368) === */

undefined4 FUN_103f85a0(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    local_24 = 0;
    if (param_2 != 0) {
      local_24 = *(undefined4 *)(param_2 + 0x48);
      FUN_1038a5a4(param_1,param_2 + 0x48);
    }
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118565c8)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 0x48) = local_24;
    }
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l3_route_add",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103f3128 (size=368) === */

undefined4 FUN_103f3128(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    local_24 = 0;
    if (param_2 != 0) {
      local_24 = *(undefined4 *)(param_2 + 0x34);
      FUN_1038a5a4(param_1,param_2 + 0x34);
    }
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118563a0)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 0x34) = local_24;
    }
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l3_host_add",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103f5ef8 (size=280) === */

undefined4 FUN_103f5ef8(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118564b8)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l3_intf_create",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103f054c (size=300) === */

undefined4 FUN_103f054c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11856270)[iVar1])(param_1,param_2,param_3,param_4);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l3_egress_create",4,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === FUN_10060c7c (size=1028) === */

undefined4 FUN_10060c7c(int param_1,int param_2)

{
  char cVar4;
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar5;
  short local_188;
  undefined4 local_184;
  uint local_16c [3];
  undefined4 local_160;
  undefined1 auStack_15c [4];
  undefined4 local_158;
  undefined1 auStack_118 [256];
  int local_18;
  int local_14;
  
  local_188 = (short)*(undefined4 *)(param_2 + 0xc);
  local_18 = param_1;
  local_14 = param_2;
  if ((local_188 == 0) &&
     (local_188 = FUN_1005fb90(param_1,*(undefined4 *)(param_2 + 8)), local_188 == 0)) {
    return 0;
  }
  FUN_112b0700(local_16c,local_14,local_188);
  cVar4 = FUN_100506d0(local_188);
  if (*(int *)(local_14 + 0x10) == 0) {
    if ((cVar4 == '\0') || (*(int *)(local_14 + 0x14) == -1)) {
      uVar2 = FUN_1004fe9c(param_1,*(undefined4 *)(local_14 + 0x14));
      FUN_1004ff94(uVar2,auStack_15c,&local_160);
    }
    else {
      iVar1 = FUN_10062100(param_1,local_14 + 0x10);
      if (iVar1 == 0) {
        if (0 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          uVar3 = FUN_10028b64(local_14 + 0x10,auStack_118);
          FUN_10047040(1,"%s %s:%d ERR Cannot get vlan_if %s\n",0x24,uVar2,&DAT_11322924,0x10e6,
                       uVar3);
        }
        return 0;
      }
      local_160 = *(undefined4 *)(iVar1 + 0x454);
    }
  }
  else if (*(int *)(local_14 + 0x10) == 2) {
    local_160 = *(undefined4 *)(param_1 + 0x14);
  }
  else if (*(int *)(local_14 + 0x10) == 1) {
    if (cVar4 == '\0') {
      local_16c[0] = local_16c[0] | 0x80;
      local_158 = *(undefined4 *)(local_14 + 0x14);
    }
    else {
      iVar1 = FUN_10062100(param_1,local_14 + 0x10);
      if (iVar1 == 0) {
        if (0 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          uVar3 = FUN_10028b64(local_14 + 0x10,auStack_118);
          FUN_10047040(1,"%s %s:%d ERR Cannot get vlan_if %s\n",0x24,uVar2,&DAT_11322924,0x10f9,
                       uVar3);
        }
        return 0;
      }
      local_160 = *(undefined4 *)(iVar1 + 0x454);
    }
  }
  else {
    if (*(int *)(local_14 + 0x10) != 3) {
      return 1;
    }
    if (*(int *)(local_14 + 100) == 0) {
      local_184 = *(undefined4 *)(param_1 + 0x14);
      local_16c[0] = local_16c[0] | 4;
    }
    else {
      local_184 = *(undefined4 *)(local_14 + 100);
    }
    local_160 = local_184;
  }
  if (*(int *)(local_14 + 0x78) == 1) {
    uVar5 = 0x20;
  }
  else {
    uVar5 = 0;
  }
  local_16c[0] = local_16c[0] | uVar5;
  iVar1 = FUN_103e6cf0(*(undefined4 *)(param_1 + 4),local_16c);
  if (iVar1 < 0) {
    if (-1 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar1 = -iVar1;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10047040(0,"%s %s:%d CRIT bcm_l2_addr_add failed %s\n",0x29,uVar2,&DAT_11322924,0x1112,
                   (&PTR_DAT_11e43a78)[iVar1]);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



/* === FUN_10061404 (size=532) === */

undefined4 FUN_10061404(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  short local_88;
  uint local_78 [3];
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_18;
  int local_14;
  
  local_88 = (short)*(undefined4 *)(param_2 + 0xc);
  local_18 = param_1;
  local_14 = param_2;
  if ((local_88 == 0) &&
     (local_88 = FUN_1005fb90(param_1,*(undefined4 *)(param_2 + 8)), local_88 == 0)) {
    return 0;
  }
  FUN_112b0700(local_78,local_14,local_88);
  if (*(int *)(local_14 + 0x10) == 0) {
    uVar1 = FUN_1004fe9c(param_1,*(undefined4 *)(local_14 + 0x14));
    FUN_1004ff94(uVar1,&local_68,&local_6c);
  }
  else if (*(int *)(local_14 + 0x10) == 1) {
    local_78[0] = local_78[0] | 0x80;
    local_64 = *(undefined4 *)(local_14 + 0x14);
  }
  else {
    if (*(int *)(local_14 + 0x10) != 3) {
      return 1;
    }
    local_68 = 0;
    local_6c = *(undefined4 *)(local_14 + 100);
  }
  iVar2 = FUN_103e6cf0(*(undefined4 *)(param_1 + 4),local_78);
  if (iVar2 < 0) {
    if (-1 < DAT_11e45404) {
      uVar1 = FUN_10046f5c();
      if ((iVar2 < 1) && (-0x13 < iVar2)) {
        iVar2 = -iVar2;
      }
      else {
        iVar2 = 0x13;
      }
      FUN_10047040(0,"%s %s:%d CRIT bcm_l2_addr_add failed %s\n",0x29,uVar1,&DAT_11322924,0x1175,
                   (&PTR_DAT_11e43a78)[iVar2]);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* === FUN_10061080 (size=376) === */

undefined4 FUN_10061080(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  short local_28;
  
  local_28 = (short)*(undefined4 *)(param_2 + 0xc);
  if ((local_28 == 0) &&
     ((local_28 = FUN_1005fb90(param_1,*(undefined4 *)(param_2 + 8)), local_28 == 0 ||
      (local_28 == -1)))) {
    return 0;
  }
  iVar1 = FUN_103e6ecc(*(undefined4 *)(param_1 + 4),param_2,local_28);
  if ((iVar1 < 0) && (iVar1 != -7)) {
    if (2 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      if ((iVar1 < 1) && (-0x13 < iVar1)) {
        iVar1 = -iVar1;
      }
      else {
        iVar1 = 0x13;
      }
      FUN_10047040(3,"%s %s:%d bcm_l2_addr_delete: %s\n",0x21,uVar2,&DAT_11322924,0x1128,
                   (&PTR_DAT_11e43a78)[iVar1]);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
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



/* === FUN_10eaf31c (size=932) === */

void FUN_10eaf31c(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint local_48;
  int local_24 [3];
  int local_18;
  
  iVar1 = (&DAT_1212b9c4)[param_1];
  iVar6 = (int)(*(ushort *)
                 (*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) + 0x1fc8)
                 + 0x28) + 3) >> 2;
  local_24[0] = (*(int *)((&DAT_1212ba0c)[param_1] + 0x784d4) -
                *(int *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) +
                                 0x1fc8) + 0xc)) + 1;
  uVar2 = *(uint *)(*(int *)(*(int *)(*(int *)((&DAT_1212b9c4)[param_1] + 0x2f26f4) + 0x24) + 0x1fc8
                            ) + 0xc);
  uVar3 = *(undefined4 *)((&DAT_1212ba0c)[param_1] + 0x784d4);
  local_18 = param_1;
  iVar4 = FUN_1075fcd4(param_1,iVar6 * 4 * local_24[0],"L2_MOD_FIFOm");
  if (iVar4 == 0) {
    *(undefined4 *)(iVar1 + 0x2f194c) = 0xffffffff;
    FUN_10799c5c(param_1,3,4,0x2d8,0xfffffffe);
    FUN_1131263c(0);
  }
  else {
    while (*(int *)(iVar1 + 0x2f1964) != 0) {
      FUN_10324874(*(undefined4 *)(iVar1 + 0x2f18f4),*(int *)(iVar1 + 0x2f1964));
      FUN_10eadac8(param_1,1);
      FUN_10eadc58(param_1,local_24);
      if (local_24[0] == 0) {
        FUN_10eadac8(param_1,0);
      }
      else {
        iVar5 = FUN_108020c0(param_1,0x7f2,0xffffffff,uVar2,uVar3,iVar4);
        if (iVar5 < 0) {
          if ((iVar5 < 1) && (-0x13 < iVar5)) {
            iVar6 = -iVar5;
          }
          else {
            iVar6 = 0x13;
          }
          FUN_10760cd4(0x200000,"AbnormalThreadExit:soc_l2mod_fifo_thread,DMA failed: %s\n",
                       (&PTR_DAT_11e43a78)[iVar6]);
          FUN_10799c5c(param_1,3,4,0x2f6,iVar5);
          break;
        }
        FUN_10eadac8(param_1,0);
        for (local_48 = uVar2; local_48 < local_24[0] + uVar2; local_48 = local_48 + 1) {
          if (*(int *)(iVar1 + 0x2f1964) == 0) goto LAB_10eaf684;
          FUN_10eaf214(param_1,*(undefined4 *)(iVar1 + 0x2f19a8),iVar4 + iVar6 * local_48 * 4);
        }
        *(undefined4 *)(iVar1 + 0x2f18fc) = 0;
        FUN_107b9e0c(param_1,0x20);
      }
    }
LAB_10eaf684:
    FUN_1075ffa4(param_1,iVar4);
    *(undefined4 *)(iVar1 + 0x2f194c) = 0xffffffff;
    FUN_1131263c(0);
  }
  return;
}



/* === FUN_103f0790 (size=288) === */

undefined4 FUN_103f0790(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11856280)[iVar1])(param_1,param_2,param_3);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l3_egress_ecmp_add",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103f08b0 (size=296) === */

undefined4 FUN_103f08b0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11856288)[iVar1])(param_1,param_2,param_3,param_4);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_l3_egress_ecmp_create",4,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103fdc98 (size=272) === */

undefined4 FUN_103fdc98(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118567d8)[iVar1])(param_1);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_linkscan_init",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103fe480 (size=280) === */

undefined4 FUN_103fe480(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11856808)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_linkscan_register",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_1038e598 (size=280) === */

undefined4 FUN_1038e598(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11853ab8)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_cosq_config_get",2,1,param_1,0,0,local_28);
  }
  return local_28;
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



/* === FUN_103e6710 (size=272) === */

undefined4 FUN_103e6710(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11855ee0)[iVar1])(param_1);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_knet_init",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103e6820 (size=344) === */

undefined4 FUN_103e6820(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_2 != 0) {
      FUN_1038a5a4(param_1,param_2 + 0x14);
    }
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11855ee8)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
    if (param_2 != 0) {
      FUN_1038a5f4(param_1,param_2 + 0x14);
    }
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_knet_netif_create",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_103e6240 (size=344) === */

undefined4 FUN_103e6240(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_2 != 0) {
      FUN_1038a5a4(param_1,param_2 + 0x50);
    }
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11855ec0)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
    if (param_2 != 0) {
      FUN_1038a5f4(param_1,param_2 + 0x50);
    }
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_knet_filter_create",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



