/* BCM SDK functions in category: mirror */
/* Decompiled from switchd binary */

/* === bcm_mirror_destination_destroy @ 10403168 (size=304) === */

undefined4 bcm_mirror_destination_destroy(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14 [4];
  
  local_14[0] = param_2;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858228)[iVar1])(param_1,local_14[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_destination_destroy",2,2,param_1,local_14[0],0,local_28);
  }
  return local_28;
}



/* === bcm_mirror_destination_traverse @ 10403448 (size=288) === */

undefined4 bcm_mirror_destination_traverse(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858238)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_destination_traverse",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mirror_egress_set @ 104036a0 (size=312) === */

undefined4 bcm_mirror_egress_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858248)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_egress_set",3,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



/* === bcm_mirror_ingress_get @ 10762a98 (size=512) === */

undefined4 bcm_mirror_ingress_get(int param_1,int param_2)

{
  bool bVar1;
  int local_28;
  undefined *local_24;
  int local_20;
  
  local_28 = 0;
  local_24 = (undefined *)0x0;
  while( true ) {
    if (*(int *)(param_1 + local_28 * 4) == -1) {
      return 0;
    }
    local_20 = 0;
    bVar1 = true;
    switch(param_2) {
    case 0x61:
      local_24 = &DAT_11862a44;
      break;
    case 0x62:
      local_24 = &DAT_11862ab0;
      break;
    case 99:
      local_24 = &DAT_11862abc;
      break;
    case 100:
      local_24 = &DAT_11862b00;
      break;
    case 0x65:
      local_24 = &DAT_11862b38;
      break;
    case 0x66:
      local_24 = &DAT_11862b48;
      break;
    case 0x67:
      local_24 = &DAT_11e46d9c;
      break;
    case 0x68:
      local_24 = &DAT_11862bb0;
      break;
    default:
      bVar1 = false;
    }
    if (bVar1) break;
    if (*(int *)(param_1 + local_28 * 4) == param_2) {
      return 1;
    }
    local_28 = local_28 + 1;
  }
  if (local_24 == (undefined *)0x0) {
    return 0;
  }
  while( true ) {
    if (*(int *)(local_24 + local_20 * 4) == -1) {
      return 0;
    }
    if (*(int *)(param_1 + local_28 * 4) == *(int *)(local_24 + local_20 * 4)) break;
    local_20 = local_20 + 1;
  }
  return 1;
}



/* === bcm_mirror_ingress_set @ 10403910 (size=312) === */

undefined4 bcm_mirror_ingress_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14;
  undefined4 local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,&local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858258)[iVar1])(param_1,local_14,local_10);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_ingress_set",3,3,param_1,local_14,local_10,local_28);
  }
  return local_28;
}



/* === bcm_mirror_mode_get @ 10403b58 (size=280) === */

undefined4 bcm_mirror_mode_get(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858268)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_mode_get",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mirror_mode_set @ 10403c70 (size=280) === */

undefined4 bcm_mirror_mode_set(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858270)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_mode_set",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mirror_to_get @ 10405180 (size=292) === */

undefined4 bcm_mirror_to_get(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118582e8)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
    FUN_1038b3b4(param_1,param_2);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_to_get",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mirror_to_set @ 104055f8 (size=304) === */

undefined4 bcm_mirror_to_set(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_14 [4];
  
  local_14[0] = param_2;
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    FUN_1038b364(param_1,local_14);
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858300)[iVar1])(param_1,local_14[0]);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mirror_to_set",2,2,param_1,local_14[0],0,local_28);
  }
  return local_28;
}



