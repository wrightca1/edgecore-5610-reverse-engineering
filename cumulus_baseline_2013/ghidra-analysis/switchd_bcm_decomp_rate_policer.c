/* BCM SDK functions in category: rate_policer */
/* Decompiled from switchd binary */

/* === bcm_policer_destroy_all @ 104120f0 (size=272) === */

undefined4 bcm_policer_destroy_all(int param_1)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118587d8)[iVar1])(param_1);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_policer_destroy_all",1,1,param_1,0,0,local_28);
  }
  return local_28;
}



