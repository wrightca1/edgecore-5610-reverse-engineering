/* BCM SDK functions in category: l3 */
/* Decompiled from switchd binary */

/* === bcm_fb_l3_intf_ip_options_profile_id_set @ 10909d1c (size=220) === */

int bcm_fb_l3_intf_ip_options_profile_id_set(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined1 auStack_164 [148];
  undefined4 local_d0;
  undefined4 local_b8;
  int local_b4;
  undefined1 auStack_b0 [168];
  
  local_b8 = param_1;
  local_b4 = param_2;
  memset(auStack_164,0,0xa0);
  iVar2 = FUN_10737450(local_b8,*(undefined2 *)(local_b4 + 0x12),auStack_164);
  if (-1 < iVar2) {
    local_d0 = *(undefined4 *)(local_b4 + 0x5c);
    uVar1 = *(undefined2 *)(local_b4 + 0x12);
    memcpy(auStack_b0,auStack_164,0xa0);
    iVar2 = FUN_107371ac(local_b8,uVar1,auStack_b0);
  }
  return iVar2;
}



