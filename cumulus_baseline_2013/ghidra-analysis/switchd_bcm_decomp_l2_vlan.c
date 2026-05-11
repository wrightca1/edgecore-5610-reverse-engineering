/* BCM SDK functions in category: l2_vlan */
/* Decompiled from switchd binary */

/* === bcm_l2_addr_delete @ 103e7c8c (size=300) === */

undefined4 bcm_l2_addr_delete(int param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118577e0)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_l2_addr_delete",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_l2_conflict_get @ 103ea140 (size=596) === */

int bcm_l2_conflict_get(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int local_58;
  int local_54;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_58 = -3;
  }
  else {
    if (param_2 != 0) {
      local_4c = *(undefined4 *)(param_2 + 0x24);
      local_48 = *(undefined4 *)(param_2 + 0x28);
      local_44 = *(undefined4 *)(param_2 + 0x2c);
      local_40 = *(undefined4 *)(param_2 + 0x30);
      local_3c = *(undefined4 *)(param_2 + 0x34);
      local_38 = *(undefined4 *)(param_2 + 0x38);
      local_34 = *(undefined4 *)(param_2 + 0x3c);
      local_30 = *(undefined4 *)(param_2 + 0x40);
      FUN_1038b404(param_1,param_2 + 0x24);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_58 = (*(code *)(&PTR_FUN_118578d0)[iVar1])(param_1,param_2,param_3,param_4,param_5);
    FUN_112c5590(param_1,iVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 0x24) = local_4c;
      *(undefined4 *)(param_2 + 0x28) = local_48;
      *(undefined4 *)(param_2 + 0x2c) = local_44;
      *(undefined4 *)(param_2 + 0x30) = local_40;
      *(undefined4 *)(param_2 + 0x34) = local_3c;
      *(undefined4 *)(param_2 + 0x38) = local_38;
      *(undefined4 *)(param_2 + 0x3c) = local_34;
      *(undefined4 *)(param_2 + 0x40) = local_30;
    }
    if (-1 < local_58) {
      for (local_54 = 0; local_54 < param_4; local_54 = local_54 + 1) {
        if (param_3 != 0) {
          FUN_1038b454(param_1,param_3 + local_54 * 0x54 + 0x24);
        }
      }
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_l2_conflict_get",5,1,param_1,0,0,local_58);
  }
  return local_58;
}



/* === bcm_l2_tunnel_add @ 103edfb4 (size=300) === */

undefined4 bcm_l2_tunnel_add(int param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11857a18)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_l2_tunnel_add",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mirror_vlan_set @ 10405868 (size=352) === */

undefined4 bcm_mirror_vlan_set(int param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined2 local_10;
  undefined2 local_e;
  
  local_14 = param_2;
  local_10 = param_3;
  local_e = param_4;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858310)[iVar1])(param_1,local_14,local_10,local_e);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_vlan_set",4,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



