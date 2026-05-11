/* Packet flow decomp */

/* NO FUNCTION at 0x101b8f54 */

/* NO FUNCTION at 0x1002b8cc */

/* NO FUNCTION at 0x1002b044 */

/* NO FUNCTION at 0x10008ae8 */

/* NO FUNCTION at 0x1042b9b0 */

/* === FUN_1042b380 (size=324) === */

undefined4
FUN_1042b380(int param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4,undefined4 param_5
            ,undefined4 param_6)

{
  int iVar1;
  undefined4 local_38;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_38 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_38 = (*(code *)(&PTR_FUN_11857958)[iVar1])
                         (param_1,param_2,param_3,param_4,param_5,param_6);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_rx_register",6,1,param_1,0,0,local_38);
  }
  return local_38;
}



/* === FUN_104290c4 (size=292) === */

undefined4 FUN_104290c4(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11857868)[iVar1])(param_1,param_2,param_3);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_rx_control_set",3,3,param_1,param_2,param_3,local_28);
  }
  return local_28;
}



/* === FUN_1042be0c (size=280) === */

undefined4 FUN_1042be0c(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebd360)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebd360)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_118579a0)[iVar1])(param_1,param_2);
    FUN_112c43fc(param_1,iVar1);
  }
  iVar1 = FUN_10761348(&DAT_11858c08,0x10000);
  if (iVar1 != 0) {
    FUN_10460c4c("bcm_rx_start",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* NO FUNCTION at 0x1042b310 */

