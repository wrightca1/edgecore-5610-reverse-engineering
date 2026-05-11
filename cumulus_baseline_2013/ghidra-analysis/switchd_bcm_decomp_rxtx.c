/* BCM SDK functions in category: rxtx */
/* Decompiled from switchd binary */

/* === bcm_rx_unregister @ 1042d410 (size=300) === */

undefined4 bcm_rx_unregister(int param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118592a8)[iVar1])(param_1,param_2,param_3);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_rx_unregister",3,1,param_1,0,0,local_28);
  }
  return local_28;
}



