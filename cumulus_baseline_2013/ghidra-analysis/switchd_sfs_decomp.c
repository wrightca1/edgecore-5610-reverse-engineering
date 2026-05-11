/* SFS handlers — the actual path-handler implementations */

/* === FUN_1002348c @ 0x1002348c (size=228) === */

undefined4 FUN_1002348c(undefined4 param_1)

{
  undefined4 uVar1;
  
  if (2 < DAT_11e45404) {
    uVar1 = FUN_10046f5c();
    FUN_10047040(3,"%s %s:%d %s triggered\n",0x17,uVar1,&DAT_1131c09c,0x24f,param_1);
  }
  uVar1 = FUN_10022b38();
  FUN_100483a4(DAT_11e456b8,FUN_10023444,0);
  FUN_100483a4(uVar1,FUN_100231e0,0);
  FUN_100483a4(DAT_11e456b8,FUN_10023570,0);
  FUN_100485bc(uVar1,0);
  return 0;
}



/* === FUN_1004bf0c @ 0x1004bf0c (size=120) === */

bool FUN_1004bf0c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  
  iVar1 = FUN_100493c0(param_2,param_1,param_3,param_4,param_5);
  return iVar1 != 0;
}



/* === FUN_1004aaf0 @ 0x1004aaf0 (size=196) === */

int FUN_1004aaf0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
                int param_6,int param_7)

{
  int iVar1;
  int local_50 [2];
  undefined4 local_48;
  int local_40;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  local_50[0] = param_7 + 0x18;
  if (param_5 == 0 && param_6 == 0) {
    local_48 = param_2;
    local_40 = param_3;
    local_28 = param_1;
    local_24 = param_2;
    local_20 = param_3;
    local_1c = param_7;
    local_18 = param_5;
    local_14 = param_6;
    iVar1 = FUN_1004a428(param_1,local_50);
    if (iVar1 == 0) {
      time((time_t *)(local_1c + 0x10));
      iVar1 = local_20;
    }
  }
  else {
    iVar1 = -0x1b;
  }
  return iVar1;
}



/* === FUN_10048bd0 @ 0x10048bd0 (size=148) === */

undefined4 FUN_10048bd0(char *param_1,undefined4 param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  
  sVar1 = strlen(param_1);
  if (DAT_11e45f94 == 0) {
    FUN_113113b0(&DAT_113222f8,
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                 ,0xe0);
  }
  uVar2 = FUN_100482ec(DAT_11e45f94,param_1,sVar1 + 1,param_2);
  return uVar2;
}



/* === FUN_10049d98 @ 0x10049d98 (size=1228) === */

int FUN_10049d98(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  size_t sVar4;
  int *local_58;
  undefined1 auStack_40 [40];
  undefined4 local_18;
  int *local_14;
  
  iVar1 = *param_2;
  local_18 = param_1;
  local_14 = param_2;
  if ((*(int *)(iVar1 + 0x3c) == 0) ||
     (iVar3 = (**(code **)(iVar1 + 0x3c))(param_1,param_2,*(undefined4 *)(iVar1 + 0x44)), iVar3 == 0
     )) {
    switch(*(undefined4 *)(iVar1 + 8)) {
    case 0:
      break;
    case 1:
      uVar2 = *(undefined4 *)(iVar1 + 0x18);
      sVar4 = strlen(*(char **)(iVar1 + 0x18));
      FUN_1004bcec(local_14,uVar2,sVar4);
      FUN_1004bcec(local_14,&DAT_113223dc,1);
      break;
    case 2:
      if (**(char **)(iVar1 + 0x18) == '\0') {
        FUN_1004bcec(local_14,"FALSE\n",6);
      }
      else {
        FUN_1004bcec(local_14,&UNK_113223e0,5);
      }
      break;
    case 3:
      iVar3 = __nldbl_snprintf(0,0,&UNK_113223f0,**(undefined2 **)(iVar1 + 0x18));
      __nldbl_snprintf(auStack_40,iVar3 + 1,&UNK_113223f0,**(undefined2 **)(iVar1 + 0x18));
      FUN_1004bcec(local_14,auStack_40,iVar3);
      break;
    case 4:
      iVar3 = __nldbl_snprintf(0,0,&UNK_113223f0,**(undefined4 **)(iVar1 + 0x18));
      __nldbl_snprintf(auStack_40,iVar3 + 1,&UNK_113223f0,**(undefined4 **)(iVar1 + 0x18));
      FUN_1004bcec(local_14,auStack_40,iVar3);
      break;
    case 5:
      iVar3 = __nldbl_snprintf(0,0,&UNK_113223f4,**(undefined4 **)(iVar1 + 0x18));
      __nldbl_snprintf(auStack_40,iVar3 + 1,&UNK_113223f4,**(undefined4 **)(iVar1 + 0x18));
      FUN_1004bcec(local_14,auStack_40,iVar3);
      break;
    case 6:
      if (*(int *)(iVar1 + 0x18) == 0) {
        if (*(int *)(iVar1 + 0x3c) == 0) {
          iVar3 = __nldbl_snprintf(0,0,"write \'%d\' to trigger\n",*(undefined4 *)(iVar1 + 0x1c));
          __nldbl_snprintf(auStack_40,iVar3 + 1,"write \'%d\' to trigger\n",
                           *(undefined4 *)(iVar1 + 0x1c));
          FUN_1004bcec(local_14,auStack_40,iVar3);
        }
      }
      else {
        uVar2 = *(undefined4 *)(iVar1 + 0x18);
        sVar4 = strlen(*(char **)(iVar1 + 0x18));
        FUN_1004bcec(local_14,uVar2,sVar4);
      }
      break;
    case 7:
      if (*(int *)(iVar1 + 0x20) == 0) {
        sVar4 = strlen("mapping error - mapping is missing\n");
        FUN_1004bcec(local_14,"mapping error - mapping is missing\n",sVar4);
      }
      else {
        for (local_58 = *(int **)(iVar1 + 0x20); local_58[1] != 0; local_58 = local_58 + 2) {
          if (*local_58 == **(int **)(iVar1 + 0x18)) {
            iVar1 = local_58[1];
            sVar4 = strlen((char *)local_58[1]);
            FUN_1004bcec(local_14,iVar1,sVar4);
            FUN_1004bcec(local_14,&DAT_113223dc,1);
            break;
          }
        }
        if (local_58[1] == 0) {
          sVar4 = strlen("mapping error - key not found\n");
          FUN_1004bcec(local_14,"mapping error - key not found\n",sVar4);
        }
      }
      break;
    default:
      return -2;
    }
    iVar3 = 0;
  }
  return iVar3;
}



/* === FUN_1004965c @ 0x1004965c (size=136) === */

int FUN_1004965c(int param_1)

{
  int iVar1;
  int local_28;
  
  iVar1 = fuse_get_context();
  for (local_28 = *(int *)(param_1 + 0x38);
      (local_28 != 0 && (*(int *)(local_28 + 4) != *(int *)(iVar1 + 0xc)));
      local_28 = *(int *)(local_28 + 0x1c)) {
  }
  return local_28;
}



/* === FUN_1000e958 @ 0x1000e958 (size=224) === */

void FUN_1000e958(int param_1)

{
  void *__ptr;
  int iVar1;
  undefined4 local_50;
  char *local_4c;
  undefined4 local_48;
  int local_40;
  undefined *local_38;
  int local_18;
  
  iVar1 = DAT_11e4564c + param_1 * 0x200;
  local_18 = param_1;
  memset(&local_50,0,0x30);
  local_50 = 7;
  local_4c = "Port Interface Mode";
  local_48 = 0x1a4;
  local_40 = iVar1 + 0x1cc;
  local_38 = &DAT_11819028;
  __ptr = (void *)FUN_1004bc14("/config/interface/%s/interface_mode",iVar1 + 4);
  FUN_1004bf0c(__ptr,&local_50,FUN_1000e890,FUN_1000e8f4,iVar1);
  free(__ptr);
  return;
}



/* === FUN_10005eac @ 0x10005eac (size=1052) === */

undefined4 FUN_10005eac(void)

{
  undefined4 uVar1;
  
  FUN_1004bf0c("/config/stats/poll_interval",0x11818a80,0,FUN_100057bc,&DAT_11e45674);
  FUN_1004bf0c("/config/stats/vdev_hw_poll_interval",0x11818ab0,0,FUN_100057bc,&DAT_11e45670);
  FUN_1004bf0c("/config/stats/vlan/aggregate",0x11818b10,0,FUN_10005d84,0);
  FUN_1004bf0c("/config/stats/vlan/show_internal_vlans",0x11818ae0,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/stats/vxlan/aggregate",0x11818b40,0,FUN_10005cf0,0);
  FUN_1004bf0c("/config/stats/vxlan/member",0x11818b70,0,FUN_10005e18,0);
  FUN_1004bf0c("/config/buf_util/poll_interval",0x118187e0,0,FUN_100057bc,&DAT_11e45630);
  FUN_1004bf0c("/config/buf_util/measure_interval",0x11818810,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/acl/optimize_hw",0x118188a0,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/acl/non_atomic_update_mode",0x118188d0,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/arp/next_hops",0x11818900,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/ignore_non_swps",0x11818930,0,FUN_10005814,0);
  FUN_1004bf0c("/config/disable_internal_parity_restart",0x11818840,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/disable_internal_hw_err_restart",0x11818870,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/route/table",0x11818990,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/route/host_max_percent",0x11818750,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/route/delete_dead_routes",0x11818960,0,FUN_10005868,0);
  FUN_1004bf0c("/config/coalesce/reducer",0x118189c0,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/coalesce/timeout",0x11818a20,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/coalesce/offset",0x118189f0,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/logging",0x11818a50,0,FUN_10005240,0);
  FUN_1004bf0c("/config/route/max_routes",0x11818ba0,0,FUN_1000ad30,0);
  __nldbl_sprintf(&DAT_11e45a34,&UNK_11317e7c,DAT_11e453e4,DAT_11e453e6);
  FUN_1004bf0c("/config/resv_vlan_range",0x11818bd0,0,FUN_10005664,0);
  FUN_1004bf0c("/config/vxlan/default_ttl",0x11818c00,0,FUN_100051a4,0);
  FUN_1004bf0c("/config/bridge/broadcast_frame_to_cpu",0x11818c30,0,FUN_100051a4,0);
  uVar1 = FUN_1004c478("/etc/cumulus/switchd.conf","/config/",&UNK_11317f08);
  return uVar1;
}



