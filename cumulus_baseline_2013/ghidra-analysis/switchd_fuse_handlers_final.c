/* Decompiled FUSE handlers (fuse_operations callbacks) + /ctrl/hal/resync */

/* === FUN_100496e4 @ 0x100496e4 (size=376) === */

undefined4 FUN_100496e4(undefined4 param_1,void *param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *local_28 [4];
  undefined4 local_18;
  void *local_14;
  
  local_18 = param_1;
  local_14 = param_2;
  cVar1 = FUN_10048bd0(param_1,local_28);
  if (cVar1 == '\x01') {
    memset(local_14,0,0x68);
    if (*local_28[0] == 0) {
      *(uint *)((int)local_14 + 0x10) = local_28[0][2] | 0x4000;
      *(int *)((int)local_14 + 0x14) = local_28[0][7] + 2;
      *(undefined8 *)((int)local_14 + 0x30) = DAT_11322708;
      *(int *)((int)local_14 + 0x48) = local_28[0][3];
      *(int *)((int)local_14 + 0x50) = local_28[0][4];
      *(int *)((int)local_14 + 0x58) = local_28[0][5];
    }
    else {
      if (*local_28[0] != 1) {
        return 0xfffffffe;
      }
      *(uint *)((int)local_14 + 0x10) = local_28[0][2] | 0x8000;
      *(undefined4 *)((int)local_14 + 0x14) = 1;
      *(int *)((int)local_14 + 0x48) = local_28[0][3];
      *(int *)((int)local_14 + 0x50) = local_28[0][4];
      *(int *)((int)local_14 + 0x58) = local_28[0][5];
      *(undefined8 *)((int)local_14 + 0x30) = DAT_11322708;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 0xfffffffe;
  }
  return uVar2;
}



/* === FUN_1004996c @ 0x1004996c (size=52) === */

undefined4 FUN_1004996c(void)

{
  return 0xffffffa1;
}



/* === FUN_100499a0 @ 0x100499a0 (size=44) === */

undefined4 FUN_100499a0(void)

{
  return 0xffffffa1;
}



/* === FUN_100499cc @ 0x100499cc (size=40) === */

undefined4 FUN_100499cc(void)

{
  return 0xffffffa1;
}



/* === FUN_100499f4 @ 0x100499f4 (size=40) === */

undefined4 FUN_100499f4(void)

{
  return 0xffffffa1;
}



/* === FUN_10049a1c @ 0x10049a1c (size=44) === */

undefined4 FUN_10049a1c(void)

{
  return 0xffffffa1;
}



/* === FUN_10049a48 @ 0x10049a48 (size=44) === */

undefined4 FUN_10049a48(void)

{
  return 0xffffffa1;
}



/* === FUN_10049a74 @ 0x10049a74 (size=44) === */

undefined4 FUN_10049a74(void)

{
  return 0xffffffa1;
}



/* === FUN_10049aa0 @ 0x10049aa0 (size=44) === */

undefined4 FUN_10049aa0(void)

{
  return 0xffffffa1;
}



/* === FUN_10049acc @ 0x10049acc (size=48) === */

undefined4 FUN_10049acc(void)

{
  return 0xffffffa1;
}



/* === FUN_1004acec @ 0x1004acec (size=48) === */

undefined4 FUN_1004acec(void)

{
  undefined4 in__r6;
  
  return in__r6;
}



/* === FUN_10049afc @ 0x10049afc (size=44) === */

undefined4 FUN_10049afc(void)

{
  return 0xffffffa1;
}



/* === FUN_10049b88 @ 0x10049b88 (size=332) === */

undefined4 FUN_10049b88(undefined4 param_1,uint *param_2)

{
  bool bVar1;
  char cVar4;
  int iVar2;
  undefined4 uVar3;
  int *piVar5;
  uint local_1c;
  undefined4 local_18;
  uint *local_14;
  
  bVar1 = (*param_2 & 1) == 0;
  local_18 = param_1;
  local_14 = param_2;
  cVar4 = FUN_10048bd0(param_1,&local_1c);
  if (cVar4 == '\x01') {
    if ((bVar1) || ((*(uint *)(local_1c + 8) & 0x80) != 0)) {
      local_14[4] = 0;
      local_14[5] = local_1c;
      piVar5 = (int *)(local_1c + 0x18);
      *piVar5 = *piVar5 + 1;
      if (bVar1) {
        iVar2 = fuse_get_context();
        uVar3 = FUN_10048874(piVar5,*(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(local_1c + 0x50));
        *(undefined4 *)(local_1c + 0x50) = uVar3;
        uVar3 = 0;
      }
      else {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = 0xfffffff3;
    }
  }
  else {
    uVar3 = 0xfffffffe;
  }
  return uVar3;
}



/* === FUN_1004a264 @ 0x1004a264 (size=452) === */

size_t FUN_1004a264(undefined4 param_1,void *param_2,uint param_3,undefined4 param_4,int param_5,
                   uint param_6,int param_7)

{
  int iVar1;
  int iVar2;
  size_t local_30;
  
  iVar1 = *(int *)(param_7 + 0x14);
  iVar2 = FUN_1004965c(iVar1 + 0x18);
  if (iVar2 == 0) {
    FUN_113113b0("backing",
                 "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                 ,0x29c);
  }
  if ((*(int *)(iVar2 + 8) != 0) || (local_30 = FUN_10049d98(param_1,iVar2), local_30 == 0)) {
    if ((param_5 < 0) || ((param_5 == 0 && (param_6 < *(uint *)(iVar2 + 0x10))))) {
      param_5 = param_5 + (uint)CARRY8((ulonglong)param_6,(ulonglong)param_3);
      if ((0 < param_5) ||
         ((local_30 = param_3, param_5 == 0 &&
          ((ulonglong)*(uint *)(iVar2 + 0x10) <
           ((ulonglong)param_6 + (ulonglong)param_3 & 0xffffffff))))) {
        local_30 = *(int *)(iVar2 + 0x10) - param_6;
      }
      memcpy(param_2,(void *)(*(int *)(iVar2 + 8) + param_6),local_30);
    }
    else {
      local_30 = 0;
    }
    time((time_t *)(iVar1 + 0xc));
  }
  return local_30;
}



/* === FUN_1004abb4 @ 0x1004abb4 (size=124) === */

undefined4
FUN_1004abb4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,int param_7)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1004aaf0(param_1,param_2,param_3,param_4,param_5,param_6,
                       *(undefined4 *)(param_7 + 0x14));
  return uVar1;
}



/* === FUN_1004ac30 @ 0x1004ac30 (size=188) === */

undefined4 FUN_1004ac30(undefined4 param_1,uint *param_2)

{
  int iVar1;
  
  if (((*param_2 & 1) == 0) && (iVar1 = FUN_1004965c(param_2[5] + 0x18), iVar1 != 0)) {
    FUN_100488f4(iVar1);
  }
  return 0;
}



/* === FUN_10049cd4 @ 0x10049cd4 (size=196) === */

undefined4 FUN_10049cd4(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 local_28;
  
  iVar1 = *(int *)(param_2 + 0x14);
  piVar3 = (int *)(iVar1 + 0x18);
  *piVar3 = *piVar3 + -1;
  if (*piVar3 == 0) {
    local_28 = *(int *)(iVar1 + 0x50);
    while (local_28 != 0) {
      iVar2 = *(int *)(local_28 + 0x1c);
      FUN_10048958(local_28);
      local_28 = iVar2;
    }
    *(undefined4 *)(iVar1 + 0x50) = 0;
  }
  return 0;
}



/* === FUN_10049b28 @ 0x10049b28 (size=48) === */

undefined4 FUN_10049b28(void)

{
  return 0xffffffa1;
}



/* === FUN_1004985c @ 0x1004985c (size=272) === */

undefined4
FUN_1004985c(undefined4 param_1,undefined4 param_2,code *param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *local_38;
  int local_34 [3];
  undefined4 local_28;
  undefined4 local_24;
  code *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_7;
  local_18 = param_5;
  local_14 = param_6;
  (*param_3)(param_2,&UNK_113223d4,0,param_4,0,0);
  (*local_20)(local_24,&UNK_113223d8,0,param_4,0,0);
  cVar1 = FUN_10048bd0(local_28,local_34);
  if (cVar1 == '\x01') {
    for (local_38 = *(undefined4 **)(local_34[0] + 0x18); local_38 != (undefined4 *)0x0;
        local_38 = (undefined4 *)local_38[2]) {
      (*local_20)(local_24,*local_38,0,param_4,0,0);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 0xfffffffe;
  }
  return uVar2;
}



/* === FUN_10049b58 @ 0x10049b58 (size=48) === */

undefined4 FUN_10049b58(void)

{
  return 0xffffffa1;
}



/* === FUN_1004ad1c @ 0x1004ad1c (size=264) === */

undefined4 FUN_1004ad1c(undefined4 param_1,int param_2,int param_3,uint *param_4)

{
  int iVar1;
  
  iVar1 = FUN_1004965c(*(int *)(param_2 + 0x14) + 0x18);
  if (iVar1 != 0) {
    if (param_3 != 0) {
      if (*(int *)(iVar1 + 0x14) != 0) {
        fuse_pollhandle_destroy(*(undefined4 *)(iVar1 + 0x14));
      }
      *(int *)(iVar1 + 0x14) = param_3;
    }
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      FUN_100488f4(iVar1);
      *param_4 = *param_4 | 1;
      *(undefined1 *)(iVar1 + 0x18) = 0;
    }
  }
  return 0;
}



/* === FUN_10021884 @ 0x10021884 (size=1592) === */

undefined4 FUN_10021884(undefined1 param_1)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  uint local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_70;
  int aiStack_6c [4];
  int local_5c;
  undefined4 local_28 [4];
  undefined1 local_18;
  
  local_18 = param_1;
  if (DAT_118190e0 != -1) {
    FUN_113113b0("ports_per_be == -1",&DAT_1131c09c,0x88);
  }
  DAT_11e45c4c = 0;
  DAT_11e45c48 = 0;
  DAT_11e45c50 = (void *)0x0;
  FUN_10042b54(local_28);
  local_98 = 0;
  do {
    if (1 < local_98) {
      if (DAT_118190e0 != -1) {
        FUN_100228e0(aiStack_6c);
        local_8c = 0;
        for (local_88 = 0; local_88 < 2; local_88 = local_88 + 1) {
          local_8c = local_8c + aiStack_6c[local_88];
        }
        DAT_11e456b8 = FUN_100484c4(local_5c + local_8c);
        DAT_11e456bc = FUN_100484c4(local_5c);
        uVar4 = FUN_10027030();
        DAT_11e456c0 = FUN_100484c4(uVar4);
        DAT_11e456c4 = FUN_100484c4(0x2000);
        DAT_11e456c8 = FUN_100484c4(0x28000);
        DAT_11e456cc = FUN_100484c4(0x28000);
        FUN_1004bf0c("/ctrl/hal/resync",0x118190f8,0,FUN_1002348c,0);
        DAT_11e45c64 = FUN_1002148c(DAT_11e45c48 * DAT_118190e0,0x1c,&DAT_1131c09c,0xc2);
        local_90 = 0;
        for (local_98 = 0; local_98 < DAT_11e45c48; local_98 = local_98 + 1) {
          piVar5 = *(int **)((int)DAT_11e45c50 + local_98 * 4);
          for (local_94 = 0; local_94 < DAT_118190e0; local_94 = local_94 + 1) {
            pcVar1 = *(code **)(*piVar5 + 8);
            uVar4 = FUN_10021588(local_90);
            (*pcVar1)(piVar5,uVar4,DAT_11e45c64 + local_90 * 0x1c);
            local_90 = local_90 + 1;
          }
        }
        DAT_11e45c68 = FUN_100484c4(64000);
        return 1;
      }
      if (-1 < DAT_11e45404) {
        uVar4 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT No backends found.\n",0x22,uVar4,&DAT_1131c09c,0xae);
      }
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    iVar2 = (*(code *)(&PTR_FUN_118190d8)[local_98])(&local_70,local_18);
    if (iVar2 != 0) {
      for (local_94 = 0; local_94 < local_70; local_94 = local_94 + 1) {
        piVar5 = (int *)(iVar2 + local_94 * 4);
        (**(code **)(*piVar5 + 0x134))(piVar5,DAT_11e453e4,DAT_11e453e6);
        iVar3 = (**(code **)*piVar5)(piVar5,local_28[0],local_18);
        if (iVar3 == 0) {
          return 0;
        }
        if (DAT_11e45c48 == DAT_11e45c4c) {
          if (DAT_11e45c4c == 0) {
            DAT_11e45c4c = 2;
          }
          else {
            DAT_11e45c4c = DAT_11e45c4c << 1;
          }
          DAT_11e45c50 = realloc(DAT_11e45c50,DAT_11e45c4c << 2);
        }
        iVar3 = DAT_11e45c48 * 4;
        DAT_11e45c48 = DAT_11e45c48 + 1;
        *(int **)((int)DAT_11e45c50 + iVar3) = piVar5;
        iVar3 = (**(code **)(*piVar5 + 4))(piVar5);
        if ((DAT_118190e0 != -1) && (DAT_118190e0 != iVar3)) {
          FUN_113113b0("ports_per_be == -1 || ports_per_be == num_ports",&DAT_1131c09c,0xa0);
        }
        DAT_118190e0 = iVar3;
        (**(code **)(*piVar5 + 0x3c))(piVar5,FUN_10021694);
        (**(code **)(*piVar5 + 0x48))(piVar5,FUN_10021744);
        (**(code **)(*piVar5 + 0x4c))(piVar5,FUN_100217bc);
        (**(code **)(*piVar5 + 0x74))(piVar5,FUN_1002181c);
      }
    }
    local_98 = local_98 + 1;
  } while( true );
}



/* === FUN_10007af8 @ 0x10007af8 (size=4012) === */

undefined4 FUN_10007af8(int param_1,undefined4 *param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar9;
  FILE *pFVar3;
  int iVar4;
  undefined4 uVar5;
  __pid_t _Var6;
  int *piVar7;
  char *pcVar8;
  int local_644;
  void *local_634;
  char local_630 [4];
  undefined4 local_62c;
  undefined4 local_628;
  char local_624 [512];
  char acStack_424 [512];
  char acStack_224 [511];
  undefined1 local_25;
  int local_18;
  undefined4 *local_14;
  
  bVar1 = false;
  bVar2 = false;
  local_18 = param_1;
  local_14 = param_2;
  for (local_644 = 1; local_644 < local_18; local_644 = local_644 + 1) {
    iVar4 = strcmp((char *)local_14[local_644],"-V");
    if (iVar4 == 0) {
      __nldbl_fprintf(stderr," Cumulus Networks switchd version %s\n",0x11817db0);
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    iVar4 = strcmp((char *)local_14[local_644],"-h");
    if ((iVar4 == 0) || (iVar4 = strcmp((char *)local_14[local_644],"--help"), iVar4 == 0)) {
      FUN_10007a04(*local_14);
    }
    else {
      iVar4 = strcmp((char *)local_14[local_644],"-d");
      if (iVar4 == 0) {
        bVar1 = true;
      }
      else {
        iVar4 = strcmp((char *)local_14[local_644],"-do");
        if (iVar4 == 0) {
          bVar2 = true;
        }
        else {
          iVar4 = strcmp((char *)local_14[local_644],"-lic");
          if (iVar4 == 0) {
            if (local_18 + -1 == local_644) {
              fwrite("-lic requires a parameter\n",1,0x1a,stderr);
              FUN_10007a04(*local_14);
            }
            local_644 = local_644 + 1;
            PTR_s__etc_cumulus__license_txt_11e453dc = (undefined *)local_14[local_644];
            _edata = '\x01';
          }
          else {
            __nldbl_fprintf(stderr,"Unexpected argument \'%s\'\n",local_14[local_644]);
            FUN_10007a04(*local_14);
          }
        }
      }
    }
  }
  if (_edata != '\0') {
    cVar9 = FUN_1002c264(PTR_s__etc_cumulus__license_txt_11e453dc,local_630,0);
    if (cVar9 == '\0') {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    if (local_630[0] != '\0') {
                    /* WARNING: Subroutine does not return */
      exit(99);
    }
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  DAT_11e45634 = local_18 + 1;
  DAT_11e4562c = FUN_10004f78(DAT_11e45634,4,"switchd.c",0x4b5);
  for (local_644 = 0; local_644 < local_18; local_644 = local_644 + 1) {
    *(undefined4 *)(DAT_11e4562c + local_644 * 4) = local_14[local_644];
  }
  *(undefined4 *)(DAT_11e4562c + (DAT_11e45634 + -1) * 4) = 0;
  DAT_11e45644 = pthread_self();
  pFVar3 = fopen64("/var/run/switchd.pid","r");
  if (pFVar3 != (FILE *)0x0) {
    iVar4 = __nldbl_fscanf(pFVar3,&DAT_11318398,&local_62c);
    if (iVar4 == 1) {
      memset(acStack_424,0,0x200);
      memset(local_624,0,0x200);
      __nldbl_snprintf(acStack_224,0x1ff,"/proc/%d/exe",local_62c);
      local_25 = 0;
      readlink(acStack_224,acStack_424,0x200);
      readlink("/proc/self/exe",local_624,0x200);
      if (local_624[0] == '\0') {
        FUN_113113b0("strlen(us_exe) > 0","switchd.c",0x4ce);
      }
      iVar4 = strcmp(local_624,acStack_424);
      if (iVar4 == 0) {
        __nldbl_fprintf(stderr,"switchd (%d) is already running, aborting.\n",local_62c);
        return 1;
      }
    }
    fclose(pFVar3);
  }
  FUN_1004c584("/etc/cumulus/switchd.conf","logging",&local_634);
  if (local_634 == (void *)0x0) {
    fwrite("sfs_config_get failed, exiting.\n",1,0x20,stderr);
                    /* WARNING: Subroutine does not return */
    exit(10);
  }
  iVar4 = FUN_10005028(local_634);
  free(local_634);
  if (iVar4 != 0) {
    fwrite("Init of logging backend failed, exiting.\n",1,0x29,stderr);
                    /* WARNING: Subroutine does not return */
    exit(10);
  }
  FUN_11315540(FUN_10007948);
  cVar9 = FUN_100073c4();
  if (cVar9 == '\x01') {
    cVar9 = FUN_1002c264(PTR_s__etc_cumulus__license_txt_11e453dc,0,1);
    if (cVar9 == '\x01') {
      unlink("/var/run/switchd.ready");
      if (bVar1) {
        daemon(0,0);
      }
      pFVar3 = fopen64("/var/run/switchd.pid","w");
      if (pFVar3 == (FILE *)0x0) {
        if (-1 < DAT_11e45404) {
          uVar5 = FUN_10046f5c();
          FUN_10047040(0,"%s %s:%d CRIT Couldn\'t write pid file %s\n",0x2a,uVar5,"switchd.c",0x50d,
                       "/var/run/switchd.pid");
        }
      }
      else {
        _Var6 = getpid();
        __nldbl_fprintf(pFVar3,&DAT_11318398,_Var6);
        fclose(pFVar3);
      }
      if (-2 < DAT_11e45404) {
        uVar5 = FUN_10046f5c();
        FUN_10047040(0xffffffff,"%s %s:%d switchd version %s\n",0x1d,uVar5,"switchd.c",0x513,
                     0x11817db0);
      }
      if (-2 < DAT_11e45404) {
        uVar5 = FUN_10046f5c();
        FUN_10047040(0xffffffff,"%s %s:%d switchd cmdline:",0x1a,uVar5,"switchd.c",0x514);
      }
      for (local_644 = 1; local_644 < local_18; local_644 = local_644 + 1) {
        if (-2 < DAT_11e45404) {
          uVar5 = FUN_10046f5c();
          FUN_10047040(0xffffffff,"%s %s:%d  %s",0xd,uVar5,"switchd.c",0x516,local_14[local_644]);
        }
      }
      if (-2 < DAT_11e45404) {
        uVar5 = FUN_10046f5c();
        FUN_10047040(0xffffffff,"%s %s:%d \n",0xb,uVar5,"switchd.c",0x518);
      }
      FUN_10044f5c(0);
      FUN_10005bcc();
      cVar9 = FUN_1004b51c();
      if (cVar9 == '\x01') {
        FUN_1004bf0c("/version",0x11818780,0,0,0);
        FUN_1004bf0c("/easter",0x118187b0,0,0,0);
        FUN_1004bf0c("/ctrl/logger",0x11818d50,FUN_100062c8,FUN_100062c8,0);
        FUN_1004bf0c("/ctrl/debug",&DAT_11818d80,0,FUN_100063c4,0);
        iVar4 = FUN_10005eac();
        if (iVar4 == 0) {
          if (-1 < DAT_11e45404) {
            uVar5 = FUN_10046f5c();
            FUN_10047040(0,"%s %s:%d CRIT Switchd config failed.\n",0x26,uVar5,"switchd.c",0x529);
          }
          uVar5 = 1;
        }
        else if ((bVar2) || (cVar9 = FUN_10009b6c(), cVar9 == '\x01')) {
          cVar9 = FUN_10021884(1);
          if (cVar9 == '\x01') {
            FUN_100253dc(FUN_100076fc);
            if (!bVar2) {
              cVar9 = FUN_10029984();
              if (cVar9 != '\x01') {
                if (-1 < DAT_11e45404) {
                  uVar5 = FUN_10046f5c();
                  FUN_10047040(0,"%s %s:%d CRIT NIC init failed.\n",0x20,uVar5,"switchd.c",0x53c);
                }
                return 1;
              }
              cVar9 = FUN_10006b94();
              if (cVar9 != '\x01') {
                if (-1 < DAT_11e45404) {
                  uVar5 = FUN_10046f5c();
                  FUN_10047040(0,"%s %s:%d CRIT Port init failed.\n",0x21,uVar5,"switchd.c",0x541);
                }
                return 1;
              }
              cVar9 = FUN_10006e54();
              if (cVar9 != '\x01') {
                if (-1 < DAT_11e45404) {
                  uVar5 = FUN_10046f5c();
                  FUN_10047040(0,"%s %s:%d CRIT Bridges init failed.\n",0x24,uVar5,"switchd.c",0x546
                              );
                }
                return 1;
              }
              cVar9 = FUN_10006e78();
              if (cVar9 != '\x01') {
                if (-1 < DAT_11e45404) {
                  uVar5 = FUN_10046f5c();
                  FUN_10047040(0,"%s %s:%d CRIT Bonds init failed.\n",0x22,uVar5,"switchd.c",0x54b);
                }
                return 1;
              }
              cVar9 = FUN_10006ec8();
              if (cVar9 != '\x01') {
                if (-1 < DAT_11e45404) {
                  uVar5 = FUN_10046f5c();
                  FUN_10047040(0,"%s %s:%d CRIT Logical networks init failed.\n",0x2d,uVar5,
                               "switchd.c",0x550);
                }
                return 1;
              }
              do {
                iVar4 = FUN_10045cc8(0,0);
              } while (0 < iVar4);
              FUN_1000ff00(1);
            }
            FUN_10006a1c();
            FUN_10006b20();
            pFVar3 = fopen64("/var/run/switchd.restart","r");
            if (pFVar3 != (FILE *)0x0) {
              __nldbl_fscanf(pFVar3,&DAT_11318398,&local_628);
              if (-2 < DAT_11e45404) {
                uVar5 = FUN_10046f5c();
                FUN_10047040(0xffffffff,"%s %s:%d switchd starting after internal error %d\n",0x33,
                             uVar5,"switchd.c",0x563,local_628);
              }
              FUN_1002548c(local_628);
              fclose(pFVar3);
              __nldbl_sprintf(local_624,&UNK_113189d8,"/var/run/switchd.restart");
              system(local_624);
            }
            FUN_10045c84(FUN_100075e4,0);
            FUN_100455e8(0,30000000,FUN_10007544,0);
            cVar9 = FUN_1004b638("/cumulus/switchd",0);
            if (cVar9 == '\x01') {
              if (2 < DAT_11e45404) {
                uVar5 = FUN_10046f5c();
                FUN_10047040(3,"%s %s:%d FUSE mounted on %s\n",0x1d,uVar5,"switchd.c",0x57c,
                             "/cumulus/switchd");
              }
              uVar5 = FUN_1004ae84();
              FUN_10045228(uVar5,1,FUN_100079c8,0);
              FUN_100463c4();
              iVar4 = unlink("/var/run/switchd.pid");
              if ((iVar4 < 0) && (0 < DAT_11e45404)) {
                uVar5 = FUN_10046f5c();
                piVar7 = __errno_location();
                pcVar8 = strerror(*piVar7);
                FUN_10047040(1,"%s %s:%d ERR Couldn\'t delete pid file %s, %s\n",0x2e,uVar5,
                             "switchd.c",0x583,"/var/run/switchd.pid",pcVar8);
              }
              uVar5 = 0;
            }
            else {
              if (-1 < DAT_11e45404) {
                uVar5 = FUN_10046f5c();
                FUN_10047040(0,"%s %s:%d CRIT Switchd fs mount failed.\n",0x28,uVar5,"switchd.c",
                             0x579);
              }
              uVar5 = 1;
            }
          }
          else {
            if (-1 < DAT_11e45404) {
              uVar5 = FUN_10046f5c();
              FUN_10047040(0,"%s %s:%d CRIT HAL init failed.\n",0x20,uVar5,"switchd.c",0x535);
            }
            uVar5 = 1;
          }
        }
        else {
          if (-1 < DAT_11e45404) {
            uVar5 = FUN_10046f5c();
            FUN_10047040(0,"%s %s:%d CRIT Netlink init failed.\n",0x24,uVar5,"switchd.c",0x52f);
          }
          uVar5 = 1;
        }
      }
      else {
        if (-1 < DAT_11e45404) {
          uVar5 = FUN_10046f5c();
          FUN_10047040(0,"%s %s:%d CRIT Switchd fs init failed.\n",0x27,uVar5,"switchd.c",0x51f);
        }
        uVar5 = 1;
      }
    }
    else {
      if (-1 < DAT_11e45404) {
        uVar5 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT No license to run switchd!\n",0x2a,uVar5,"switchd.c",0x4f9);
      }
      uVar5 = 10;
    }
  }
  else {
    if (-1 < DAT_11e45404) {
      uVar5 = FUN_10046f5c();
      FUN_10047040(0,"%s %s:%d CRIT Error setting signal handlers.\n",0x2e,uVar5,"switchd.c",0x4f0);
    }
    uVar5 = 1;
  }
  return uVar5;
}



