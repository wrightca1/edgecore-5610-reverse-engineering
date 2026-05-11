/* All ioctl() callers - the BDE interface layer */
/* 7 total callers found via PLT stub xrefs */

/* === FUN_10008ae8 @ 10008ae8 (size=988) === */

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



/* === FUN_1002c62c @ 1002c62c (size=916) === */

void FUN_1002c62c(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  char *pcVar4;
  uint16_t uVar5;
  cmsghdr *pcVar6;
  int local_58;
  undefined1 auStack_38 [18];
  undefined1 auStack_26 [14];
  int *local_18;
  int local_14;
  undefined4 local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  iVar1 = socket(10,3,0x3a);
  *local_18 = iVar1;
  if (*local_18 < 0) {
    if (0 < DAT_11e46cd4) {
      uVar2 = bcm_l3_route_get();
      piVar3 = __errno_location();
      pcVar4 = strerror(*piVar3);
      FUN_10047ec4(1,"%s %s:%d ERR Failed to open IPv6 socket %s\n",0x2c,uVar2,"pkt_inj.c",0x91,
                   pcVar4);
    }
  }
  else {
    memset(auStack_38,0,0x20);
    __nldbl_snprintf(auStack_38,0x10,&DAT_1131e40c,local_10);
    iVar1 = ioctl(*local_18,0x8927,auStack_38);
    piVar3 = local_18;
    if (iVar1 < 0) {
      if (0 < DAT_11e46cd4) {
        uVar2 = bcm_l3_route_get();
        piVar3 = __errno_location();
        pcVar4 = strerror(*piVar3);
        FUN_10047ec4(1,"%s %s:%d ERR No source MAC address ifindex %d, %s",0x32,uVar2,"pkt_inj.c",
                     0x98,local_14,pcVar4);
      }
    }
    else {
      *(undefined1 *)(local_18 + 1) = 0x87;
      *(undefined1 *)((int)local_18 + 5) = 0;
      uVar5 = htons(0);
      *(uint16_t *)((int)piVar3 + 6) = uVar5;
      uVar5 = htons(0xbeef);
      *(uint16_t *)(piVar3 + 2) = uVar5;
      uVar5 = htons(0xbabe);
      *(uint16_t *)((int)piVar3 + 10) = uVar5;
      *(undefined1 *)(piVar3 + 7) = 1;
      *(undefined1 *)((int)piVar3 + 0x1d) = 1;
      for (local_58 = 0; local_58 < 6; local_58 = local_58 + 1) {
        *(undefined1 *)((int)piVar3 + local_58 + 0x1e) = auStack_26[local_58];
      }
      param_1[0x18] = 0x20;
      param_1[0x17] = (int)(local_18 + 1);
      param_1[0x12] = (int)(param_1 + 0x17);
      param_1[0x13] = 1;
      param_1[0x14] = (int)(local_18 + 0x1b);
      param_1[0x15] = 0x30;
      if ((uint)param_1[0x15] < 0xc) {
        pcVar6 = (cmsghdr *)0x0;
      }
      else {
        pcVar6 = (cmsghdr *)param_1[0x14];
      }
      pcVar6->cmsg_level = 0x29;
      pcVar6->cmsg_type = 0x34;
      pcVar6->cmsg_len = 0x10;
      pcVar6[1].cmsg_len = 0xff;
      pcVar6 = __cmsg_nxthdr((msghdr *)(param_1 + 0x10),pcVar6);
      pcVar6->cmsg_level = 0x29;
      pcVar6->cmsg_type = 0x32;
      pcVar6->cmsg_len = 0x20;
      pcVar6[2].cmsg_level = local_14;
    }
  }
  return;
}



/* === FUN_10322b10 @ 10322b10 (size=412) === */

int FUN_10322b10(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  byte local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_5d;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined4 local_50;
  byte *local_4c;
  undefined4 local_40;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  iVar1 = *(int *)(&DAT_11ebc134 + param_1 * 8);
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  memset(&local_60,0,9);
  local_60 = (byte)((local_28 & 7) << 1) | 0x61;
  local_5f = (undefined1)local_24;
  local_5e = (undefined1)((uint)local_24 >> 8);
  local_5d = (undefined1)((uint)local_24 >> 0x10);
  local_5c = (undefined1)((uint)local_24 >> 0x18);
  local_5b = (undefined1)local_20;
  local_5a = (undefined1)((uint)local_20 >> 8);
  local_59 = (undefined1)((uint)local_20 >> 0x10);
  local_58 = (undefined1)((uint)local_20 >> 0x18);
  memset(&local_50,0,0x20);
  local_4c = &local_60;
  local_50 = 0;
  local_40 = 9;
  iVar1 = ioctl(iVar1,0x80206b00,&local_50);
  if (iVar1 < 1) {
    __nldbl_printf("Can\'t send spi message: write(ret=%d)\n",iVar1);
  }
  return iVar1;
}



/* === FUN_1002c2d0 @ 1002c2d0 (size=860) === */

void FUN_1002c2d0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  char *pcVar4;
  uint16_t uVar5;
  undefined4 *puVar6;
  int local_58;
  undefined1 auStack_3c [18];
  undefined1 auStack_2a [18];
  int *local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  iVar1 = socket(2,3,1);
  *local_18 = iVar1;
  if (*local_18 < 0) {
    if (0 < DAT_11e46cd4) {
      uVar2 = bcm_l3_route_get();
      piVar3 = __errno_location();
      pcVar4 = strerror(*piVar3);
      FUN_10047ec4(1,"%s %s:%d ERR Failed to open IPv4 socket %s\n",0x2c,uVar2,"pkt_inj.c",0x57,
                   pcVar4);
    }
  }
  else {
    memset(auStack_3c,0,0x20);
    __nldbl_snprintf(auStack_3c,0x10,&DAT_1131e40c,local_10);
    iVar1 = ioctl(*local_18,0x8927,auStack_3c);
    if (iVar1 < 0) {
      if (0 < DAT_11e46cd4) {
        uVar2 = bcm_l3_route_get();
        piVar3 = __errno_location();
        pcVar4 = strerror(*piVar3);
        FUN_10047ec4(1,"%s %s:%d ERR No source MAC address ifindex %d, %s",0x32,uVar2,"pkt_inj.c",
                     0x5e,local_14,pcVar4);
      }
    }
    else {
      uVar5 = htons(1);
      *(uint16_t *)(param_1 + 1) = uVar5;
      uVar5 = htons(0x800);
      *(uint16_t *)((int)param_1 + 6) = uVar5;
      *(undefined1 *)(param_1 + 2) = 6;
      *(undefined1 *)((int)param_1 + 9) = 4;
      uVar5 = htons(1);
      *(uint16_t *)((int)param_1 + 10) = uVar5;
      for (local_58 = 0; local_58 < 6; local_58 = local_58 + 1) {
        *(undefined1 *)((int)param_1 + local_58 + 0xc) = auStack_2a[local_58];
      }
      inet_pton(2,"127.0.0.1",(void *)((int)param_1 + 0x12));
      memset((void *)((int)param_1 + 0x16),0xff,6);
      param_1[0x14] = 0x1c;
      param_1[0x13] = (int)(local_18 + 1);
      param_1[0xe] = (int)(param_1 + 0x13);
      param_1[0xf] = 1;
      param_1[0x10] = (int)(local_18 + 0x16);
      param_1[0x11] = 0x18;
      if ((uint)param_1[0x11] < 0xc) {
        puVar6 = (undefined4 *)0x0;
      }
      else {
        puVar6 = (undefined4 *)param_1[0x10];
      }
      puVar6[1] = 0;
      puVar6[2] = 8;
      *puVar6 = 0x18;
      puVar6[3] = local_14;
    }
  }
  return;
}



/* === FUN_10322934 @ 10322934 (size=476) === */

uint FUN_10322934(uint param_1,undefined4 param_2)

{
  int iVar1;
  uint local_88;
  uint local_84;
  byte local_78;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined1 local_74;
  byte abStack_70 [8];
  undefined4 local_68;
  byte *local_64;
  undefined4 local_58;
  undefined4 local_40;
  byte *local_3c;
  undefined4 local_38;
  uint local_28;
  undefined4 local_24;
  
  iVar1 = *(int *)(&DAT_11ebc134 + param_1 * 8);
  local_28 = param_1;
  local_24 = param_2;
  memset(abStack_70,0,4);
  local_78 = (byte)((local_28 & 7) << 1) | 0x60;
  local_77 = (undefined1)local_24;
  local_76 = (undefined1)((uint)local_24 >> 8);
  local_75 = (undefined1)((uint)local_24 >> 0x10);
  local_74 = (undefined1)((uint)local_24 >> 0x18);
  memset(&local_68,0,0x40);
  local_64 = &local_78;
  local_68 = 0;
  local_58 = 5;
  local_3c = abStack_70;
  local_40 = 0;
  local_38 = 4;
  iVar1 = ioctl(iVar1,0x80406b00,&local_68);
  if (iVar1 < 1) {
    __nldbl_printf("Can\'t send spi message: read(ret=%d)\n",iVar1);
  }
  local_84 = 0;
  for (local_88 = 0; local_88 < 4; local_88 = local_88 + 1) {
    local_84 = local_84 | (uint)abStack_70[local_88] << ((local_88 & 7) << 3);
  }
  return local_84;
}



/* === FUN_10322de8 @ 10322de8 (size=140) === */

undefined4 FUN_10322de8(ulong param_1,int param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_2 + 4) = 0xffffffff;
  iVar1 = ioctl(DAT_11853c08,param_1,param_2);
  if (iVar1 != 0) {
    FUN_11312544("ioctl(_devfd, command, pdevio) == 0",
                 "/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c"
                 ,0x1f7);
  }
  return *(undefined4 *)(param_2 + 4);
}



/* === FUN_10008ec4 @ 10008ec4 (size=516) === */

void FUN_10008ec4(char *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  char acStack_38 [16];
  ushort local_28;
  char *local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  if ((DAT_1181a780 < 0) && (DAT_1181a780 = socket(2,2,0), DAT_1181a780 < 0)) {
    if (DAT_11e46cd4 < 0) {
      return;
    }
    uVar1 = bcm_l3_route_get();
    FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t create tuntap ioctl socket.\n",0x34,uVar1,"tuntap.c",
                 0x71);
    return;
  }
  memset(acStack_38,0,0x20);
  strncpy(acStack_38,local_18,0x10);
  iVar2 = ioctl(DAT_1181a780,0x8913,acStack_38);
  if (iVar2 < 0) {
    if (-1 < DAT_11e46cd4) {
      uVar1 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t get netdev flags.\n",0x2a,uVar1,"tuntap.c",0x79);
    }
  }
  else {
    local_28 = (local_28 | (ushort)local_14) & ~(ushort)local_10;
    iVar2 = ioctl(DAT_1181a780,0x8914,acStack_38);
    if ((iVar2 < 0) && (-1 < DAT_11e46cd4)) {
      uVar1 = bcm_l3_route_get();
      FUN_10047ec4(0,"%s %s:%d CRIT Couldn\'t Set netdev flags.\n",0x2a,uVar1,"tuntap.c",0x81);
    }
  }
  return;
}



