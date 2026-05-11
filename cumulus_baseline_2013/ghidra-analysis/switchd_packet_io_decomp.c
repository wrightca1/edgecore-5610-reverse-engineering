/* Packet I/O functions in switchd */

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



/* === read @ 0x11317b30 (size=16) === */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ssize_t read(int __fd,void *__buf,size_t __nbytes)

{
  ssize_t sVar1;
  
  sVar1 = (*(code *)PTR_read_11819644)();
  return sVar1;
}



/* === write @ 0x11316d30 (size=16) === */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ssize_t write(int __fd,void *__buf,size_t __n)

{
  ssize_t sVar1;
  
  sVar1 = (*(code *)PTR_write_118192c4)();
  return sVar1;
}



/* === writev @ 0x11317000 (size=16) === */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ssize_t writev(int __fd,iovec *__iovec,int __count)

{
  ssize_t sVar1;
  
  sVar1 = (*(code *)PTR_writev_11819378)();
  return sVar1;
}



/* === ioctl @ 0x11317c50 (size=16) === */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ioctl(int __fd,ulong __request,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_ioctl_1181968c)();
  return iVar1;
}



/* === TUN creator (FUN_10008ae8) and callers === */

int FUN_10008ae8(char *param_1,void *param_2)

{
  int __fd;
  undefined4 uVar1;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  char acStack_40 [16];
  undefined2 local_30;
  undefined1 auStack_2e [14];
  undefined4 local_20;
  undefined2 local_1c;
  char *local_18;
  void *local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = param_1;
  local_14 = param_2;
  __fd = open64("/dev/net/tun",2);
  if (__fd < 0) {
    if (-1 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      piVar2 = __errno_location();
      pcVar3 = strerror(*piVar2);
      FUN_10047ec4(0,"%s %s:%d CRIT Open of /dev/net/tun failed: %s\n",0x2f,uVar1,"tuntap.c",0x22,
                   pcVar3);
    }
  }
  else {
    memset(acStack_40,0,0x20);
    if (*local_18 != '\0') {
      strncpy(acStack_40,local_18,0x10);
    }
    local_30 = 0x300e;
    iVar4 = ioctl(__fd,0x800454ca,acStack_40);
    if (iVar4 < 0) {
      if (-1 < DAT_11e46cd4) {
        uVar1 = bcm_l3_route_get();
        piVar2 = __errno_location();
        pcVar3 = strerror(*piVar2);
        FUN_10047ec4(0,"%s %s:%d CRIT TUNSETIFF failed: %s\n",0x24,uVar1,"tuntap.c",0x3e,pcVar3);
      }
      close(__fd);
      __fd = iVar4;
    }
    else {
      iVar4 = memcmp(local_14,&local_20,6);
      if (iVar4 != 0) {
        iVar4 = ioctl(__fd,0x8927,acStack_40);
        if (iVar4 < 0) {
          if (-1 < DAT_11e46cd4) {
            uVar1 = bcm_l3_route_get();
            piVar2 = __errno_location();
            pcVar3 = strerror(*piVar2);
            FUN_10047ec4(0,"%s %s:%d CRIT SIOCGIFHWADDR failed: %s\n",0x28,uVar1,"tuntap.c",0x4b,
                         pcVar3);
          }
          close(__fd);
          return iVar4;
        }
        iVar4 = memcmp(local_14,auStack_2e,6);
        if (iVar4 != 0) {
          local_30 = 1;
          memcpy(auStack_2e,local_14,6);
          iVar4 = ioctl(__fd,0x8924,acStack_40);
          if (iVar4 < 0) {
            if (-1 < DAT_11e46cd4) {
              uVar1 = bcm_l3_route_get();
              piVar2 = __errno_location();
              pcVar3 = strerror(*piVar2);
              FUN_10047ec4(0,"%s %s:%d CRIT SIOCSIFHWADDR failed: %s\n",0x28,uVar1,"tuntap.c",0x55,
                           pcVar3);
            }
            close(__fd);
            return iVar4;
          }
        }
      }
      iVar4 = ioctl(__fd,0x800454cb,1);
      if (iVar4 < 0) {
        if (-1 < DAT_11e46cd4) {
          uVar1 = bcm_l3_route_get();
          piVar2 = __errno_location();
          pcVar3 = strerror(*piVar2);
          FUN_10047ec4(0,"%s %s:%d CRIT TUNSETPERSIST failed: %s\n",0x28,uVar1,"tuntap.c",0x5d,
                       pcVar3);
        }
        close(__fd);
        __fd = iVar4;
      }
      else {
        strcpy(local_18,acStack_40);
      }
    }
  }
  return __fd;
}



/* 1 callers of TUN creator */
/* --- caller: FUN_1002ada4 @ 0x1002ada4 (size=280) --- */

undefined4 FUN_1002ada4(int param_1)

{
  int *__ptr;
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined2 local_20;
  int local_18;
  
  local_24 = 0;
  local_20 = 0;
  local_18 = param_1;
  __ptr = (int *)FUN_1002a758(4,"nic.c",0xb2);
  iVar1 = FUN_10008ae8(local_18 + 4,&local_24);
  *__ptr = iVar1;
  if (*__ptr < 0) {
    free(__ptr);
    uVar2 = 0;
  }
  else {
    *(int *)(PTR_DAT_11e46cb8 + 0xc) = *(int *)(PTR_DAT_11e46cb8 + 0xc) + 1;
    FUN_100467f8(DAT_11e47788,FUN_1002ad18,local_18,__ptr);
    if (DAT_11e477e4 != '\x01') {
      FUN_100238bc(FUN_1002b8cc);
      FUN_100238e8(FUN_1002bbb4);
      DAT_11e477e4 = '\x01';
    }
    uVar2 = 1;
  }
  return uVar2;
}



