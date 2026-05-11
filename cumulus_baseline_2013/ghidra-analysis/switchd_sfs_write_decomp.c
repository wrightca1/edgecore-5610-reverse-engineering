/* SFS write-side handlers + resync workers */

/* === FUN_1004a428 @ 0x1004a428 (size=1736) === */

int FUN_1004a428(undefined4 param_1,int *param_2)

{
  char *__s2;
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  undefined4 *local_68;
  ushort local_64;
  uint local_60;
  int local_5c;
  uint local_28 [4];
  undefined4 local_18;
  int *local_14;
  
  iVar4 = *param_2;
  local_18 = param_1;
  local_14 = param_2;
  switch(*(int *)(iVar4 + 8)) {
  case 0:
    break;
  case 1:
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    if (*(int *)(iVar4 + 0x1c) - 1U < local_28[0]) {
      local_28[0] = *(int *)(iVar4 + 0x1c) - 1;
    }
    strncpy(*(char **)(iVar4 + 0x18),pcVar1,local_28[0]);
    *(undefined1 *)(*(int *)(iVar4 + 0x18) + *(int *)(iVar4 + 0x1c) + -1) = 0;
    break;
  case 2:
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    iVar3 = strcmp(pcVar1,"TRUE");
    if (iVar3 != 0) {
      pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
      iVar3 = strcmp(pcVar1,"TRUE\n");
      if (iVar3 != 0) {
        pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
        iVar3 = strcmp(pcVar1,"true");
        if (iVar3 != 0) {
          pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
          iVar3 = strcmp(pcVar1,"true\n");
          if (iVar3 != 0) {
            pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
            iVar3 = strcmp(pcVar1,"FALSE");
            if (iVar3 != 0) {
              pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
              iVar3 = strcmp(pcVar1,"false");
              if (iVar3 != 0) {
                pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
                iVar3 = strcmp(pcVar1,"false\n");
                if (iVar3 != 0) {
                  pcVar1 = (char *)FUN_1004bec0(local_14,local_28);
                  iVar3 = strcmp(pcVar1,"FALSE\n");
                  if (iVar3 != 0) break;
                }
              }
            }
            **(undefined1 **)(iVar4 + 0x18) = 0;
            break;
          }
        }
      }
    }
    **(undefined1 **)(iVar4 + 0x18) = 1;
    break;
  case 3:
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    iVar3 = atoi(pcVar1);
    local_64 = (ushort)iVar3;
    if ((*(short *)(iVar4 + 0x1e) != 0) || (*(short *)(iVar4 + 0x20) != 0)) {
      if (local_64 < *(ushort *)(iVar4 + 0x1e)) {
        local_64 = *(ushort *)(iVar4 + 0x1e);
      }
      if (*(ushort *)(iVar4 + 0x20) < local_64) {
        local_64 = *(ushort *)(iVar4 + 0x20);
      }
    }
    **(ushort **)(iVar4 + 0x18) = local_64;
    break;
  case 4:
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    local_60 = atol(pcVar1);
    if ((*(int *)(iVar4 + 0x20) != 0) || (*(int *)(iVar4 + 0x24) != 0)) {
      if (local_60 < *(uint *)(iVar4 + 0x20)) {
        local_60 = *(uint *)(iVar4 + 0x20);
      }
      if (*(uint *)(iVar4 + 0x24) < local_60) {
        local_60 = *(uint *)(iVar4 + 0x24);
      }
    }
    **(uint **)(iVar4 + 0x18) = local_60;
    break;
  case 5:
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    local_5c = atoi(pcVar1);
    if ((*(int *)(iVar4 + 0x20) != 0) || (*(int *)(iVar4 + 0x24) != 0)) {
      if (local_5c < *(int *)(iVar4 + 0x20)) {
        local_5c = *(int *)(iVar4 + 0x20);
      }
      if (*(int *)(iVar4 + 0x24) < local_5c) {
        local_5c = *(int *)(iVar4 + 0x24);
      }
    }
    **(int **)(iVar4 + 0x18) = local_5c;
    break;
  case 6:
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    iVar3 = atoi(pcVar1);
    if (((*(int *)(iVar4 + 0x1c) == iVar3) && (*(int *)(iVar4 + 0x40) != 0)) &&
       (iVar3 = (**(code **)(iVar4 + 0x40))(local_18,local_14,*(undefined4 *)(iVar4 + 0x44)),
       iVar3 != 0)) {
      return iVar3;
    }
    break;
  case 7:
    if (*(int *)(iVar4 + 0x20) == 0) {
      return -0x16;
    }
    pcVar1 = (char *)FUN_1004bec0(param_2,local_28);
    sVar2 = strlen(pcVar1);
    if (pcVar1[sVar2 - 1] == '\n') {
      sVar2 = strlen(pcVar1);
      pcVar1[sVar2 - 1] = '\0';
    }
    for (local_68 = *(undefined4 **)(iVar4 + 0x20); local_68[1] != 0; local_68 = local_68 + 2) {
      __s2 = (char *)local_68[1];
      sVar2 = strlen(pcVar1);
      iVar3 = strncmp(pcVar1,__s2,sVar2);
      if (iVar3 == 0) {
        **(undefined4 **)(iVar4 + 0x18) = *local_68;
        break;
      }
    }
    if (local_68[1] == 0) {
      return -0x16;
    }
    break;
  default:
    return -2;
  }
  if (((*(int *)(iVar4 + 0x40) == 0) || (*(int *)(iVar4 + 8) == 6)) ||
     (iVar4 = (**(code **)(iVar4 + 0x40))(local_18,local_14,*(undefined4 *)(iVar4 + 0x44)),
     iVar4 == 0)) {
    iVar4 = 0;
  }
  return iVar4;
}



/* === FUN_1000e890 @ 0x1000e890 (size=100) === */

undefined4 FUN_1000e890(undefined4 param_1,undefined4 param_2,int param_3)

{
  FUN_10022284(*(undefined4 *)(param_3 + 0x18),param_3 + 0x1cc);
  return 0;
}



/* === FUN_1000e8f4 @ 0x1000e8f4 (size=100) === */

undefined4 FUN_1000e8f4(undefined4 param_1,undefined4 param_2,int param_3)

{
  FUN_10022308(*(undefined4 *)(param_3 + 0x18),*(undefined4 *)(param_3 + 0x1cc));
  return 0;
}



/* === FUN_10022b38 @ 0x10022b38 (size=108) === */

undefined4 FUN_10022b38(void)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*(int *)*DAT_11e45c50 + 0x58))(*DAT_11e45c50);
  return uVar1;
}



/* === FUN_10023444 @ 0x10023444 (size=72) === */

undefined4 FUN_10023444(int param_1)

{
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0x7fffffff;
  return 0;
}



/* === FUN_100231e0 @ 0x100231e0 (size=612) === */

undefined4 FUN_100231e0(void *param_1,undefined4 param_2)

{
  char cVar3;
  void *pvVar1;
  undefined4 uVar2;
  void *__ptr;
  void *local_28 [4];
  void *local_18;
  undefined4 local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  cVar3 = FUN_100482ec(DAT_11e456b8,param_1,0x18,local_28);
  if (cVar3 == '\x01') {
    cVar3 = FUN_10027dfc(local_28[0],param_1);
    if (cVar3 != '\x01') {
      pvVar1 = (void *)FUN_10028710(param_1);
      __ptr = (void *)FUN_10028710(local_28[0]);
      if (0 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        FUN_10047040(1,"%s %s:%d ERR HW route %s doesn\'t match HAL route %s.  Updating.\n",0x41,
                     uVar2,&DAT_1131c09c,0x21a,pvVar1,__ptr);
      }
      free(pvVar1);
      free(__ptr);
      FUN_100279a4(local_28[0],*(undefined4 *)((int)param_1 + 0x20));
      FUN_10027a64(local_28[0],param_1);
      FUN_10027a00(param_1);
    }
  }
  else {
    pvVar1 = (void *)FUN_10028710(param_1);
    if (0 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      FUN_10047040(1,"%s %s:%d ERR Route %s in HW, but not in HAL cache.  Adding.\n",0x3d,uVar2,
                   &DAT_1131c09c,0x209,pvVar1);
    }
    free(pvVar1);
    local_28[0] = (void *)FUN_1002148c(1,0x2c,&DAT_1131c09c,0x20c);
    FUN_100278fc(local_28[0],*(undefined4 *)((int)param_1 + 0x20));
    FUN_10027a64(local_28[0],param_1);
    cVar3 = FUN_1004828c(DAT_11e456b8,local_28[0],0x18,local_28[0]);
    if (cVar3 != '\x01') {
      FUN_10027a00(local_28[0]);
      free(local_28[0]);
      return 0;
    }
  }
  *(uint *)((int)local_28[0] + 0x1c) = *(uint *)((int)local_28[0] + 0x1c) | 0x80000000;
  FUN_10027a00(param_1);
  free(param_1);
  return 1;
}



/* === FUN_10023570 @ 0x10023570 (size=304) === */

undefined4 FUN_10023570(void *param_1,undefined4 param_2)

{
  void *__ptr;
  undefined4 uVar1;
  int iVar2;
  void *local_24 [3];
  void *local_18;
  undefined4 local_14;
  
  if (*(int *)((int)param_1 + 0x1c) < 0) {
    uVar1 = 0;
  }
  else {
    local_24[0] = param_1;
    local_18 = param_1;
    local_14 = param_2;
    __ptr = (void *)FUN_10028710(param_1);
    if (0 < DAT_11e45404) {
      uVar1 = FUN_10046f5c();
      FUN_10047040(1,"%s %s:%d ERR Route %s in HAL cache, but not in HW.  Deleting.\n",0x3f,uVar1,
                   &DAT_1131c09c,0x23d,__ptr);
    }
    free(__ptr);
    if (((*(uint *)((int)local_24[0] + 0x1c) & 0x10) != 0) &&
       (iVar2 = FUN_10048348(DAT_11e456bc,local_24[0],0x18,local_24), iVar2 == 0)) {
      FUN_113113b0("hash_table_delete(hal_neighbors, HAL_ROUTE_KEY(hal_route), HAL_ROUTE_KEYSIZE, (void**)&hal_route)"
                   ,&DAT_1131c09c,0x247);
    }
    FUN_10027a00(local_24[0]);
    free(local_24[0]);
    uVar1 = 1;
  }
  return uVar1;
}



/* === FUN_100483a4 @ 0x100483a4 (size=288) === */

void FUN_100483a4(int *param_1,code *param_2,undefined4 param_3)

{
  void *pvVar1;
  int iVar2;
  void *local_38;
  undefined4 *local_34;
  int local_30;
  
  for (local_30 = 0; local_30 < *param_1; local_30 = local_30 + 1) {
    local_34 = (undefined4 *)(param_1[2] + local_30 * 4);
    local_38 = *(void **)(param_1[2] + local_30 * 4);
    while (local_38 != (void *)0x0) {
      pvVar1 = *(void **)((int)local_38 + 0xc);
      iVar2 = (*param_2)(*(undefined4 *)((int)local_38 + 8),param_3);
      if (iVar2 == 1) {
        *local_34 = pvVar1;
        free(local_38);
        param_1[1] = param_1[1] + -1;
        local_38 = pvVar1;
      }
      else {
        local_34 = (undefined4 *)((int)local_38 + 0xc);
        local_38 = pvVar1;
      }
    }
  }
  return;
}



/* === FUN_100485bc @ 0x100485bc (size=136) === */

void FUN_100485bc(void *param_1,undefined4 param_2)

{
  undefined4 local_48;
  undefined1 auStack_44 [44];
  void *local_18;
  undefined4 local_14;
  
  local_48 = param_2;
  local_18 = param_1;
  local_14 = param_2;
  FUN_113153f4(auStack_44,0x28,FUN_10048560,&local_48);
  FUN_100483a4(local_18,auStack_44,0);
  free(*(void **)((int)local_18 + 8));
  free(local_18);
  return;
}



/* === FUN_100493c0 @ 0x100493c0 (size=668) === */

int FUN_100493c0(void *param_1,char *param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  uint uVar1;
  size_t sVar2;
  undefined4 uVar3;
  int iVar4;
  int *local_2c;
  void *local_28;
  char *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  sVar2 = strlen(param_2);
  uVar1 = *(uint *)((int)local_28 + 0xc);
  if ((((int)(sVar2 + 1) < 3) || (*local_24 != '/')) || (local_24[1] == '/')) {
    if (-1 < DAT_11e45404) {
      uVar3 = FUN_10046f5c();
      FUN_10047040(0,&UNK_11322324,0x29,uVar3,
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                   ,0x156,local_24);
    }
    iVar4 = 0;
  }
  else if (local_28 == (void *)0x0) {
    if (-1 < DAT_11e45404) {
      uVar3 = FUN_10046f5c();
      FUN_10047040(0,"%s %s:%d CRIT Need file spec\n",0x1e,uVar3,
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                   ,0x15b);
    }
    iVar4 = 0;
  }
  else {
    iVar4 = FUN_10048bd0(local_24,&local_2c);
    if (iVar4 != 0) {
      if (*local_2c != 1) {
        if (-1 < DAT_11e45404) {
          uVar3 = FUN_10046f5c();
          FUN_10047040(0,"%s %s:%d CRIT can\'t replace existing directory with file: %s\n",0x3e,
                       uVar3,
                       "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                       ,0x164,local_24);
        }
        return 0;
      }
      FUN_10049020(local_24);
    }
    iVar4 = FUN_10048a74(1,local_24,*(undefined4 *)((int)local_28 + 8));
    memcpy((void *)(iVar4 + 0x20),local_28,0x30);
    *(undefined4 *)(iVar4 + 0x54) = local_20;
    *(undefined4 *)(iVar4 + 0x58) = local_1c;
    *(undefined4 *)(iVar4 + 0x5c) = local_18;
    FUN_10049224(iVar4);
    FUN_10048c64(iVar4);
    FUN_10048d98(local_24,1,(uVar1 & 1) != 0);
    if (3 < DAT_11e45404) {
      uVar3 = FUN_10046f5c();
      FUN_10047040(4,"%s %s:%d added filesystem path %s\n",0x23,uVar3,
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                   ,0x176,local_24);
    }
    iVar4 = iVar4 + 0x18;
  }
  return iVar4;
}



