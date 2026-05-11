/* BCM SDK functions in category: other */
/* Decompiled from switchd binary */

/* === bcm_eav_bandwidth_get @ 10399814 (size=332) === */

undefined4
bcm_eav_bandwidth_get
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

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
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_24);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11855770)[iVar1])(param_1,local_24,local_20,local_1c,local_18);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_eav_bandwidth_get",5,3,param_1,local_24,local_20,local_38);
  }
  return local_38;
}



/* === bcm_eav_bandwidth_set @ 10399960 (size=332) === */

undefined4
bcm_eav_bandwidth_set
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

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
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_24);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11855778)[iVar1])(param_1,local_24,local_20,local_1c,local_18);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_eav_bandwidth_set",5,3,param_1,local_24,local_20,local_38);
  }
  return local_38;
}



/* === bcm_eav_pcp_mapping_get @ 1039a088 (size=300) === */

undefined4
bcm_eav_pcp_mapping_get(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118557a8)[iVar1])(param_1,param_2,param_3,param_4);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_eav_pcp_mapping_get",4,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_eav_pcp_mapping_set @ 1039a1b4 (size=300) === */

undefined4
bcm_eav_pcp_mapping_set(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118557b0)[iVar1])(param_1,param_2,param_3,param_4);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_eav_pcp_mapping_set",4,3,param_1,param_2,param_3,local_28);
  }
  return local_28;
}



/* === bcm_eav_srp_mac_ethertype_get @ 1039a550 (size=288) === */

undefined4 bcm_eav_srp_mac_ethertype_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118557c8)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_eav_srp_mac_ethertype_get",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_eav_srp_mac_ethertype_set @ 1039a670 (size=300) === */

undefined4 bcm_eav_srp_mac_ethertype_set(int param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118557d0)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_eav_srp_mac_ethertype_set",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mcast_addr_remove @ 103ffba0 (size=300) === */

undefined4 bcm_mcast_addr_remove(int param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858100)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mcast_addr_remove",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mcast_bitmap_del @ 103fff6c (size=536) === */

undefined4
bcm_mcast_bitmap_del(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 local_78;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_40[0] = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_78 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_40);
    uVar2 = *param_4;
    uVar4 = param_4[1];
    uVar8 = param_4[2];
    uVar6 = param_4[3];
    uVar3 = param_4[4];
    uVar5 = param_4[5];
    uVar9 = param_4[6];
    uVar7 = param_4[7];
    FUN_1038b404(param_1,param_4);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_30 = *param_4;
    local_2c = param_4[1];
    local_28 = param_4[2];
    local_24 = param_4[3];
    local_20 = param_4[4];
    local_1c = param_4[5];
    local_18 = param_4[6];
    local_14 = param_4[7];
    local_78 = (*(code *)(&PTR_FUN_11858110)[iVar1])(param_1,param_2,local_40[0],&local_30);
    FUN_112c5590(param_1,iVar1);
    *param_4 = uVar2;
    param_4[1] = uVar4;
    param_4[2] = uVar8;
    param_4[3] = uVar6;
    param_4[4] = uVar3;
    param_4[5] = uVar5;
    param_4[6] = uVar9;
    param_4[7] = uVar7;
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mcast_bitmap_del",4,3,param_1,param_2,local_40[0],local_78);
  }
  return local_78;
}



/* === bcm_mcast_bitmap_get @ 10400184 (size=332) === */

undefined4
bcm_mcast_bitmap_get(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = param_3;
  local_c = param_4;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_10);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858118)[iVar1])(param_1,param_2,local_10,local_c);
    FUN_112c5590(param_1,iVar1);
    FUN_1038b454(param_1,local_c);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mcast_bitmap_get",4,3,param_1,param_2,local_10,local_28);
  }
  return local_28;
}



/* === bcm_mcast_bitmap_max_set @ 104002d0 (size=280) === */

undefined4 bcm_mcast_bitmap_max_set(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858120)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mcast_bitmap_max_get",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mcast_bitmap_set @ 104003e8 (size=536) === */

undefined4
bcm_mcast_bitmap_set(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 local_78;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_40[0] = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_78 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_40);
    uVar2 = *param_4;
    uVar4 = param_4[1];
    uVar8 = param_4[2];
    uVar6 = param_4[3];
    uVar3 = param_4[4];
    uVar5 = param_4[5];
    uVar9 = param_4[6];
    uVar7 = param_4[7];
    FUN_1038b404(param_1,param_4);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_30 = *param_4;
    local_2c = param_4[1];
    local_28 = param_4[2];
    local_24 = param_4[3];
    local_20 = param_4[4];
    local_1c = param_4[5];
    local_18 = param_4[6];
    local_14 = param_4[7];
    local_78 = (*(code *)(&PTR_FUN_11858128)[iVar1])(param_1,param_2,local_40[0],&local_30);
    FUN_112c5590(param_1,iVar1);
    *param_4 = uVar2;
    param_4[1] = uVar4;
    param_4[2] = uVar8;
    param_4[3] = uVar6;
    param_4[4] = uVar3;
    param_4[5] = uVar5;
    param_4[6] = uVar9;
    param_4[7] = uVar7;
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mcast_bitmap_set",4,3,param_1,param_2,local_40[0],local_78);
  }
  return local_78;
}



/* === bcm_multicast_create @ 1040a204 (size=292) === */

undefined4 bcm_multicast_create(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118584b8)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_multicast_create",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_multicast_destroy @ 1040a328 (size=280) === */

undefined4 bcm_multicast_destroy(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118584c0)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_multicast_destroy",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_multicast_vpls_encap_get @ 1040d35c (size=348) === */

undefined4
bcm_multicast_vpls_encap_get
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 local_38;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_20);
    FUN_1038b364(param_1,&local_1c);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_118585e0)[iVar1])(param_1,param_2,local_20,local_1c,local_18);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_multicast_vpls_encap_get",5,3,param_1,param_2,local_20,local_38);
  }
  return local_38;
}



