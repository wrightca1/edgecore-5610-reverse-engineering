/* BCM SDK functions in category: encap */
/* Decompiled from switchd binary */

/* === bcm_mim_detach @ 104010b0 (size=272) === */

undefined4 bcm_mim_detach(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858160)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_detach",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mim_init @ 104011c0 (size=272) === */

undefined4 bcm_mim_init(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858168)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_init",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mim_vpn_create @ 1040229c (size=280) === */

undefined4 bcm_mim_vpn_create(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118581c8)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_vpn_create",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mim_vpn_destroy @ 104023b4 (size=300) === */

undefined4 bcm_mim_vpn_destroy(int param_1,undefined2 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118581d0)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_vpn_destroy",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mim_vpn_get @ 104025f0 (size=308) === */

undefined4 bcm_mim_vpn_get(int param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118581e0)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mim_vpn_get",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_cleanup @ 104059c8 (size=272) === */

undefined4 bcm_mpls_cleanup(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858318)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_cleanup",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_exp_map_create @ 10405ad8 (size=292) === */

undefined4 bcm_mpls_exp_map_create(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858320)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_exp_map_create",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_exp_map_destroy @ 10405bfc (size=280) === */

undefined4 bcm_mpls_exp_map_destroy(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858328)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_exp_map_destroy",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_exp_map_get @ 10405d14 (size=288) === */

undefined4 bcm_mpls_exp_map_get(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858330)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_exp_map_get",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_exp_map_set @ 10405e34 (size=288) === */

undefined4 bcm_mpls_exp_map_set(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858338)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_exp_map_set",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_init @ 10405f54 (size=272) === */

undefined4 bcm_mpls_init(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858340)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_init",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_tunnel_initiator_clear @ 1040890c (size=280) === */

undefined4 bcm_mpls_tunnel_initiator_clear(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858428)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_tunnel_initiator_clear",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_tunnel_initiator_set @ 10408d8c (size=296) === */

undefined4
bcm_mpls_tunnel_initiator_set(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858448)[iVar1])(param_1,param_2,param_3,param_4);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_tunnel_initiator_set",4,3,param_1,param_2,param_3,local_28);
  }
  return local_28;
}



/* === bcm_mpls_tunnel_switch_add @ 10408eb4 (size=632) === */

undefined4 bcm_mpls_tunnel_switch_add(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    local_34 = 0;
    local_30 = 0;
    local_2c = 0;
    local_28 = 0;
    if (param_2 != 0) {
      local_34 = *(undefined4 *)(param_2 + 100);
      FUN_1038b364(param_1,param_2 + 100);
      local_30 = *(undefined4 *)(param_2 + 0x5c);
      FUN_1038b364(param_1,param_2 + 0x5c);
      local_2c = *(undefined4 *)(param_2 + 0xc);
      FUN_1038b364(param_1,param_2 + 0xc);
      local_28 = *(undefined4 *)(param_2 + 0x58);
      FUN_1038b364(param_1,param_2 + 0x58);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11858450)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 100) = local_34;
      *(undefined4 *)(param_2 + 0x5c) = local_30;
      *(undefined4 *)(param_2 + 0xc) = local_2c;
      *(undefined4 *)(param_2 + 0x58) = local_28;
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_tunnel_switch_add",2,1,param_1,0,0,local_38);
  }
  return local_38;
}



/* === bcm_mpls_tunnel_switch_delete @ 10409344 (size=632) === */

undefined4 bcm_mpls_tunnel_switch_delete(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    local_34 = 0;
    local_30 = 0;
    local_2c = 0;
    local_28 = 0;
    if (param_2 != 0) {
      local_34 = *(undefined4 *)(param_2 + 100);
      FUN_1038b364(param_1,param_2 + 100);
      local_30 = *(undefined4 *)(param_2 + 0x5c);
      FUN_1038b364(param_1,param_2 + 0x5c);
      local_2c = *(undefined4 *)(param_2 + 0xc);
      FUN_1038b364(param_1,param_2 + 0xc);
      local_28 = *(undefined4 *)(param_2 + 0x58);
      FUN_1038b364(param_1,param_2 + 0x58);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11858460)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 100) = local_34;
      *(undefined4 *)(param_2 + 0x5c) = local_30;
      *(undefined4 *)(param_2 + 0xc) = local_2c;
      *(undefined4 *)(param_2 + 0x58) = local_28;
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_tunnel_switch_delete",2,1,param_1,0,0,local_38);
  }
  return local_38;
}



/* === bcm_mpls_vpn_id_create @ 10409a04 (size=280) === */

undefined4 bcm_mpls_vpn_id_create(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858480)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_vpn_id_create",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_vpn_id_destroy @ 10409b1c (size=300) === */

undefined4 bcm_mpls_vpn_id_destroy(int param_1,undefined2 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858488)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_vpn_id_destroy",2,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_mpls_vpn_id_get @ 10409d58 (size=308) === */

undefined4 bcm_mpls_vpn_id_get(int param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11858498)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_mpls_vpn_id_get",3,2,param_1,param_2,0,local_28);
  }
  return local_28;
}



/* === bcm_multicast_mim_encap_get @ 1040ca24 (size=348) === */

undefined4
bcm_multicast_mim_encap_get
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
    local_38 = (*(code *)(&PTR_FUN_118585a8)[iVar1])(param_1,param_2,local_20,local_1c,local_18);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_multicast_mim_encap_get",5,3,param_1,param_2,local_20,local_38);
  }
  return local_38;
}



/* === bcm_multicast_wlan_encap_get @ 1040d614 (size=348) === */

undefined4
bcm_multicast_wlan_encap_get
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
    local_38 = (*(code *)(&PTR_FUN_118585f0)[iVar1])(param_1,param_2,local_20,local_1c,local_18);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_multicast_wlan_encap_get",5,3,param_1,param_2,local_20,local_38);
  }
  return local_38;
}



/* === bcm_tr2_wlan_cli_client_print @ 101b86f4 (size=276) === */

undefined4 bcm_tr2_wlan_cli_client_print(undefined4 param_1,int param_2,undefined4 param_3)

{
  FUN_10321ae0("\n WLAN Port ID: %x",*(undefined4 *)(param_2 + 4));
  FUN_10321ae0("\n Client MAC: %02x:%02x:%02x:%02x:%02x:%02x",*(undefined1 *)(param_2 + 8),
               *(undefined1 *)(param_2 + 9),*(undefined1 *)(param_2 + 10),
               *(undefined1 *)(param_2 + 0xb),*(undefined1 *)(param_2 + 0xc),
               *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xc),param_1,param_2,param_3
              );
  FUN_10321ae0("\n Home Agent Port ID: %x",*(undefined4 *)(param_2 + 0x10));
  FUN_10321ae0("\n Access Point Port ID: %x",*(undefined4 *)(param_2 + 0x14));
  return 0;
}



/* === bcm_wlan_client_add @ 10458d38 (size=472) === */

undefined4 bcm_wlan_client_add(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_2 != 0) {
      FUN_1038b364(param_1,param_2 + 0x10);
      FUN_1038b364(param_1,param_2 + 4);
      FUN_1038b364(param_1,param_2 + 0x14);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3b8)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
    if (param_2 != 0) {
      FUN_1038b3b4(param_1,param_2 + 0x10);
      FUN_1038b3b4(param_1,param_2 + 4);
      FUN_1038b3b4(param_1,param_2 + 0x14);
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_client_add",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_client_delete @ 10458f10 (size=280) === */

undefined4 bcm_wlan_client_delete(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3c0)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_client_delete",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_client_delete_all @ 10459028 (size=272) === */

undefined4 bcm_wlan_client_delete_all(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3c8)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_client_delete_all",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_client_get @ 10459138 (size=480) === */

undefined4 bcm_wlan_client_get(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    if (param_3 != 0) {
      FUN_1038b364(param_1,param_3 + 0x10);
      FUN_1038b364(param_1,param_3 + 4);
      FUN_1038b364(param_1,param_3 + 0x14);
    }
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3d0)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
    if (param_3 != 0) {
      FUN_1038b3b4(param_1,param_3 + 0x10);
      FUN_1038b3b4(param_1,param_3 + 4);
      FUN_1038b3b4(param_1,param_3 + 0x14);
    }
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_client_get",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_client_traverse @ 10459318 (size=288) === */

undefined4 bcm_wlan_client_traverse(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3d8)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_client_traverse",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_detach @ 10459438 (size=272) === */

undefined4 bcm_wlan_detach(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3e0)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_detach",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === bcm_wlan_init @ 10459548 (size=272) === */

undefined4 bcm_wlan_init(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_1185a3e8)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_wlan_init",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



