/* RX callback + related packet-handling functions */

/* === FUN_101b8f54 @ 0x101b8f54 (size=332) === */

undefined4 FUN_101b8f54(undefined4 param_1,void *param_2,int param_3)

{
  int iVar1;
  int *__dest;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(param_3 + 0x909c);
  if (*(int *)(param_3 + 0x90b0) == 0) {
    uVar3 = 1;
  }
  else {
    __dest = (int *)(*(int *)(param_3 + 0x90a4) + *(int *)(param_3 + 0x90b4) * 0x1f8);
    memcpy(__dest,param_2,0x1f8);
    *__dest = (int)(__dest + 0x42);
    iVar2 = *(int *)(param_3 + 0x90b4) + 1;
    *(int *)(param_3 + 0x90b4) = iVar2;
    if ((iVar1 <= iVar2) && (*(undefined4 *)(param_3 + 0x90b0) = 0, *(int *)(param_3 + 0x908c) == 0)
       ) {
      *(undefined4 *)(param_3 + 0x908c) = 1;
      iVar1 = FUN_103256c4(*(undefined4 *)(param_3 + 37000));
      if (iVar1 != 0) {
        FUN_10321ae0("Warning: LB RX done give failed\n");
      }
    }
    uVar3 = 3;
  }
  return uVar3;
}



/* === FUN_1042cce4 @ 0x1042cce4 (size=280) === */

undefined4 FUN_1042cce4(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_28;
  
  if (((param_1 < 0) || (0x7f < param_1)) || ((&DAT_11ebec60)[param_1] == 0)) {
    local_28 = 0xfffffffd;
  }
  else {
    iVar1 = *(int *)((&DAT_11ebec60)[param_1] + 8);
    local_28 = (*(code *)(&PTR_FUN_11859278)[iVar1])(param_1,param_2);
    FUN_112c5590(param_1,iVar1);
  }
  iVar1 = bcm_port_link_failed_clear(&PTR_DAT_1185a4d8,0x10000);
  if (iVar1 != 0) {
    FUN_10461a0c("bcm_rx_stop",2,1,param_1,0,0,local_28);
  }
  return local_28;
}



/* === FUN_1002b48c @ 0x1002b48c (size=1088) === */

void FUN_1002b48c(undefined4 param_1,uint *param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  char *pcVar6;
  __pid_t _Var7;
  ssize_t sVar8;
  size_t __n;
  size_t *__s;
  size_t local_40;
  sockaddr *local_3c;
  timeval local_38;
  sockaddr local_30;
  undefined4 local_18;
  uint *local_14;
  
  local_30.sa_data[2] = '\0';
  local_30.sa_data[3] = '\0';
  local_30.sa_data[4] = '\0';
  local_30.sa_data[5] = '\0';
  local_30.sa_data[6] = '\0';
  local_30.sa_data[7] = '\0';
  local_30.sa_data[8] = '\0';
  local_30.sa_data[9] = '\0';
  local_30.sa_family = 0x10;
  local_30.sa_data[0] = '\0';
  local_30.sa_data[1] = '\0';
  local_18 = param_1;
  local_14 = param_2;
  local_30.sa_data._2_4_ = getpid();
  if (DAT_1181aac8 < 0) {
    DAT_1181aac8 = socket(0x10,3,5);
    local_30.sa_data[6] = '\0';
    local_30.sa_data[7] = '\0';
    local_30.sa_data[8] = '\0';
    local_30.sa_data[9] = '\0';
    iVar3 = bind(DAT_1181aac8,&local_30,0xc);
    if ((iVar3 == -1) && (0 < DAT_11e46cd4)) {
      uVar4 = bcm_l3_route_get();
      piVar5 = __errno_location();
      pcVar6 = strerror(*piVar5);
      FUN_10047ec4(1,"%s %s:%d ERR ULOG bind failed: %s",0x22,uVar4,"nic.c",0x143,pcVar6);
    }
    FUN_1002a8b0(DAT_1181aac8);
  }
  __n = local_14[1] + 0xb8;
  uVar1 = local_14[1] + 0xd6 >> 4;
  *(BADSPACEBASE **)(&stack0xffffffb0 + uVar1 * -0x10) = register0x00000004;
  __s = &local_40 + uVar1 * -4;
  memset(__s,0,__n);
  local_3c = &local_30 + -uVar1;
  *__s = __n;
  DAT_11e477e0 = DAT_11e477e0 + 1;
  (&local_38)[uVar1 * -2].tv_sec = DAT_11e477e0;
  _Var7 = getpid();
  *(__pid_t *)((&local_30)[-1 - uVar1].sa_data + 10) = _Var7;
  gettimeofday(&local_38,(__timezone_ptr_t)0x0);
  *(__time_t *)(local_3c->sa_data + 2) = local_38.tv_sec;
  *(__suseconds_t *)(local_3c->sa_data + 6) = local_38.tv_usec;
  if ((*local_14 & 8) != 0) {
    local_3c->sa_data[10] = '\0';
    local_3c->sa_data[0xb] = '\0';
    local_3c->sa_data[0xc] = '\0';
    local_3c->sa_data[0xd] = '\x01';
  }
  cVar2 = s_INTERNAL_1131e1ac[8];
  uVar4 = s_INTERNAL_1131e1ac._4_4_;
  if (local_14[4] == 0xffffffff) {
    *(undefined4 *)(local_3c + 1) = s_INTERNAL_1131e1ac._0_4_;
    *(undefined4 *)(local_3c[1].sa_data + 2) = uVar4;
    local_3c[1].sa_data[6] = cVar2;
  }
  else {
    strcpy((char *)(local_3c + 1),(char *)(DAT_11e46f24 + local_14[4] * 0x200 + 4));
  }
  cVar2 = s_INTERNAL_1131e1ac[8];
  uVar4 = s_INTERNAL_1131e1ac._4_4_;
  if (local_14[5] == 0xffffffff) {
    *(undefined4 *)(local_3c + 2) = s_INTERNAL_1131e1ac._0_4_;
    *(undefined4 *)(local_3c[2].sa_data + 2) = uVar4;
    local_3c[2].sa_data[6] = cVar2;
  }
  else {
    strcpy((char *)(local_3c + 2),(char *)(DAT_11e46f24 + local_14[5] * 0x200 + 4));
  }
  *(uint *)(local_3c + 3) = local_14[1] - 0xe;
  local_3c[5].sa_data[2] = '\x0e';
  memcpy(local_3c[5].sa_data + 3,(void *)local_14[2],0xe);
  memcpy(local_3c[10].sa_data + 3,(void *)(local_14[2] + 0xe),local_14[1] - 0xe);
  local_30.sa_data._6_4_ = 1 << (DAT_11e47784 - 1 & 0x3f);
  sVar8 = sendto(DAT_1181aac8,__s,__n,0,&local_30,0xc);
  if (((sVar8 < 0) && (piVar5 = __errno_location(), *piVar5 != 0xb)) && (1 < DAT_11e46cd4)) {
    uVar4 = bcm_l3_route_get();
    piVar5 = __errno_location();
    pcVar6 = strerror(*piVar5);
    FUN_10047ec4(2,"%s %s:%d WARN ULOG sendto failed: %s\n",0x26,uVar4,"nic.c",0x16f,pcVar6);
  }
  return;
}



/* === FUN_1002a910 @ 0x1002a910 (size=64) === */

int FUN_1002a910(int param_1)

{
  if (param_1 == 0x7f) {
    param_1 = 0;
  }
  else {
    param_1 = param_1 + 1;
  }
  return param_1;
}



/* === FUN_100461bc @ 0x100461bc (size=164) === */

void FUN_100461bc(undefined4 param_1)

{
  int unaff_r2;
  int iVar1;
  
  iVar1 = FUN_10045b04(param_1);
  if (iVar1 < 0) {
    FUN_11312544("idx >= 0",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/poll/poll.c"
                 ,0xb0);
  }
  *(undefined4 *)(*(int *)(unaff_r2 + -0x6bec) + iVar1 * 0x10) = 0xffffffff;
  if (*(int *)(unaff_r2 + -0x6bd0) == 1) {
    *(undefined1 *)(unaff_r2 + -0x6bcc) = 1;
  }
  return;
}



/* NO FUNCTION AT 0x101b8b00 */

/* === bcm_rx_unregister @ 0x1042d410 (size=300) === */

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



