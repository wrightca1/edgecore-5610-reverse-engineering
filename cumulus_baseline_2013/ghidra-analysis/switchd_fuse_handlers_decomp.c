/* switchd FUSE handler decompilation */

/* === FUN_1004b638 @ 0x1004b638 (size=596) === */

undefined4 FUN_1004b638(char *param_1,char param_2)

{
  undefined4 uVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  char *local_18;
  char local_14;
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_18 = param_1;
  local_14 = param_2;
  DAT_11e45f98 = strdup(param_1);
  fuse_unmount(DAT_11e45f98,0);
  fuse_opt_add_arg(&local_28,"ignore_first_arg");
  fuse_opt_add_arg(&local_28,"-oallow_other");
  fuse_opt_add_arg(&local_28,"-odirect_io");
  fuse_opt_add_arg(&local_28,"-ononempty");
  fuse_opt_add_arg(&local_28,"-odefault_permissions");
  if (local_14 != '\0') {
    fuse_opt_add_arg(&local_28,&UNK_1132262c);
  }
  DAT_11e45f9c = fuse_mount(DAT_11e45f98,&local_28);
  if (DAT_11e45f9c == 0) {
    if (-1 < DAT_11e45404) {
      uVar1 = FUN_10046f5c();
      FUN_10047040(0,"%s %s:%d CRIT filesystem mount failed\n",0x27,uVar1,
                   "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                   ,1099);
    }
    fuse_opt_free_args(&local_28);
    uVar1 = 0;
  }
  else {
    DAT_11e45fa0 = fuse_new(DAT_11e45f9c,&local_28,&DAT_11819868,0xb0,0);
    if (DAT_11e45fa0 == 0) {
      if (-1 < DAT_11e45404) {
        uVar1 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT filesystem new failed\n",0x25,uVar1,
                     "/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c"
                     ,0x453);
      }
      fuse_unmount(DAT_11e45f98,DAT_11e45f9c);
      fuse_opt_free_args(&local_28);
      uVar1 = 0;
    }
    else {
      fuse_opt_free_args(&local_28);
      uVar1 = 1;
    }
  }
  return uVar1;
}



/* === FUN_1004b924 @ 0x1004b924 (size=188) === */

void FUN_1004b924(void)

{
  int __fd;
  
  if (DAT_11e45fa0 != 0) {
    __fd = fuse_chan_fd(DAT_11e45f9c);
    close(__fd);
    fuse_unmount(DAT_11e45f98,DAT_11e45f9c);
    fuse_destroy(DAT_11e45fa0);
    DAT_11e45f9c = 0;
    DAT_11e45fa0 = 0;
  }
  FUN_1004b8c4();
  free(DAT_11e45f98);
  DAT_11e45f98 = (void *)0x0;
  return;
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



/* === FUN_1000ead4 @ 0x1000ead4 (size=472) === */

void FUN_1000ead4(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 local_50;
  char *local_4c;
  undefined4 local_48;
  int local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_18;
  
  iVar2 = DAT_11e4564c + param_1 * 0x200;
  local_18 = param_1;
  memset(&local_50,0,0x30);
  local_50 = 4;
  local_4c = "Storm Control Rate (pps)";
  local_48 = 0x1a4;
  pvVar1 = (void *)FUN_1004bc14("/config/interface/%s/storm_control/broadcast",iVar2 + 4);
  local_40 = iVar2 + 0x1c0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0xffffffff;
  FUN_1004bf0c(pvVar1,&local_50,0,FUN_1000ea38,iVar2 + 0x14);
  free(pvVar1);
  pvVar1 = (void *)FUN_1004bc14("/config/interface/%s/storm_control/multicast",iVar2 + 4);
  local_40 = iVar2 + 0x1c4;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0xffffffff;
  FUN_1004bf0c(pvVar1,&local_50,0,FUN_1000ea38,iVar2 + 0x14);
  free(pvVar1);
  pvVar1 = (void *)FUN_1004bc14("/config/interface/%s/storm_control/unknown_unicast",iVar2 + 4);
  local_40 = iVar2 + 0x1c8;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0xffffffff;
  FUN_1004bf0c(pvVar1,&local_50,0,FUN_1000ea38,iVar2 + 0x14);
  free(pvVar1);
  return;
}



/* === FUN_10009b6c @ 0x10009b6c (size=2520) === */

undefined4 FUN_10009b6c(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  undefined4 local_44 [4];
  code *local_34;
  
  memset(local_44,0,0x34);
  local_44[0] = 1;
  local_34 = FUN_100098ec;
  FUN_1004bf0c("/config/netlink/buf_size",0x11818e18,0,0,0);
  FUN_1004c478("/etc/cumulus/switchd.conf","/config/","netlink/");
  nl_debug_set(local_44);
  FUN_1004bf0c("/ctrl/netlink/resync",0x11818e78,0,FUN_100096c8,0);
  FUN_1004bf0c("/ctrl/netlink/nl_logger",&DAT_11818ea8,0,0,0);
  DAT_11e45b38 = FUN_10009200(0);
  if (DAT_11e45b38 == 0) {
    if (DAT_11e45404 < 0) {
      return 0;
    }
    uVar1 = FUN_10046f5c();
    FUN_10047040(0,"%s %s:%d CRIT Couldn\'t allocate netlink socket.\n",0x31,uVar1,"netlink.c",0x109
                );
    return 0;
  }
  DAT_11e45b40 = FUN_10009200(0x10);
  if (DAT_11e45b40 == 0) {
    if (-1 < DAT_11e45404) {
      uVar1 = FUN_10046f5c();
      FUN_10047040(0,"%s %s:%d CRIT Couldn\'t allocate netlink socket.\n",0x31,uVar1,"netlink.c",
                   0x10e);
    }
    goto LAB_1000a508;
  }
  DAT_11e45b3c = nl_socket_alloc();
  if (DAT_11e45b3c == 0) {
    if (-1 < DAT_11e45404) {
      uVar1 = FUN_10046f5c();
      FUN_10047040(0,"%s %s:%d CRIT Couldn\'t allocate manager netlink socket.\n",0x39,uVar1,
                   "netlink.c",0x114);
    }
  }
  else {
    iVar2 = nl_cache_mngr_alloc(DAT_11e45b3c,0,1,&DAT_11e45b48);
    if (iVar2 < 0) {
      if (-1 < DAT_11e45404) {
        uVar1 = FUN_10046f5c();
        uVar3 = nl_geterror(iVar2);
        FUN_10047040(0,"%s %s:%d CRIT Couldn\'t create cache manager: %s\n",0x31,uVar1,"netlink.c",
                     0x11a,uVar3);
      }
    }
    else {
      cVar4 = FUN_10009084(DAT_11e45b3c);
      if (cVar4 == '\x01') {
        iVar2 = nl_cache_alloc_name("route/link",&DAT_11e45b50);
        if (iVar2 < 0) {
          if (-1 < DAT_11e45404) {
            uVar1 = FUN_10046f5c();
            uVar3 = nl_geterror(iVar2);
            FUN_10047040(0,"%s %s:%d CRIT Couldn\'t add link cache: %s\n",0x2b,uVar1,"netlink.c",
                         0x125,uVar3);
          }
        }
        else {
          nl_cache_set_flags(DAT_11e45b50,1);
          iVar2 = nl_cache_mngr_add_cache(DAT_11e45b48,DAT_11e45b50,FUN_10009354,0);
          if (iVar2 < 0) {
            if (-1 < DAT_11e45404) {
              uVar1 = FUN_10046f5c();
              uVar3 = nl_geterror(iVar2);
              FUN_10047040(0,"%s %s:%d CRIT Couldn\'t add link cache: %s\n",0x2b,uVar1,"netlink.c",
                           0x12f,uVar3);
            }
            nl_cache_free(DAT_11e45b50);
          }
          else {
            iVar2 = nl_cache_mngr_add(DAT_11e45b48,"route/route",FUN_10009354,0,&DAT_11e45b54);
            if (iVar2 < 0) {
              if (-1 < DAT_11e45404) {
                uVar1 = FUN_10046f5c();
                uVar3 = nl_geterror(iVar2);
                FUN_10047040(0,"%s %s:%d CRIT Couldn\'t add route cache: %s\n",0x2c,uVar1,
                             "netlink.c",0x136,uVar3);
              }
            }
            else {
              iVar2 = nl_cache_mngr_add(DAT_11e45b48,"route/mdb",FUN_10009354,0,&DAT_11e45b60);
              if (-(iVar2 >> 0x1f) == 0) {
                iVar2 = nl_cache_alloc_name("route/neigh",&DAT_11e45b58);
                if (iVar2 < 0) {
                  if (-1 < DAT_11e45404) {
                    uVar1 = FUN_10046f5c();
                    uVar3 = nl_geterror(iVar2);
                    FUN_10047040(0,"%s %s:%d CRIT Couldn\'t alloc neigh cache: %s\n",0x2e,uVar1,
                                 "netlink.c",0x141,uVar3);
                  }
                }
                else {
                  nl_cache_set_flags(DAT_11e45b58,1);
                  iVar2 = nl_cache_mngr_add_cache(DAT_11e45b48,DAT_11e45b58,FUN_10009354,0);
                  if (iVar2 < 0) {
                    if (-1 < DAT_11e45404) {
                      uVar1 = FUN_10046f5c();
                      uVar3 = nl_geterror(iVar2);
                      FUN_10047040(0,"%s %s:%d CRIT Couldn\'t add neigh cache: %s\n",0x2c,uVar1,
                                   "netlink.c",0x14b,uVar3);
                    }
                    nl_cache_free(DAT_11e45b58);
                  }
                  else {
                    DAT_11e45b44 = nl_socket_alloc();
                    if (DAT_11e45b44 == 0) {
                      if (-1 < DAT_11e45404) {
                        uVar1 = FUN_10046f5c();
                        FUN_10047040(0,
                                     "%s %s:%d CRIT Couldn\'t allocate genl manager netlink socket.\n"
                                     ,0x3e,uVar1,"netlink.c",0x152);
                      }
                    }
                    else {
                      iVar2 = nl_cache_mngr_alloc(DAT_11e45b44,0x10,1,&DAT_11e45b4c);
                      if (iVar2 < 0) {
                        if (-1 < DAT_11e45404) {
                          uVar1 = FUN_10046f5c();
                          uVar3 = nl_geterror(iVar2);
                          FUN_10047040(0,"%s %s:%d CRIT Couldn\'t create cache genl manager: %s\n",
                                       0x36,uVar1,"netlink.c",0x158,uVar3);
                        }
                      }
                      else {
                        cVar4 = FUN_10009084(DAT_11e45b44);
                        if (cVar4 != '\x01') {
                          if (-1 < DAT_11e45404) {
                            uVar1 = FUN_10046f5c();
                            FUN_10047040(0,
                                         "%s %s:%d CRIT Couldn\'t set bufsize for genl manager netlink socket.\n"
                                         ,0x45,uVar1,"netlink.c",0x15e);
                          }
                          goto LAB_1000a4c0;
                        }
                        iVar2 = FUN_1003e698(DAT_11e45b4c,&DAT_11e45b5c,FUN_10009354);
                        if (iVar2 == 0) {
                          if (-1 < DAT_11e45404) {
                            uVar1 = FUN_10046f5c();
                            FUN_10047040(0,"%s %s:%d CRIT Couldn\'t initialize genl/bond cache\n",
                                         0x33,uVar1,"netlink.c",0x163);
                          }
                        }
                        else {
                          iVar2 = FUN_10040b60();
                          if (iVar2 != 0) {
                            uVar1 = nl_cache_mngr_get_fd(DAT_11e45b48);
                            FUN_10045228(uVar1,5,FUN_10009750,DAT_11e45b48);
                            uVar1 = nl_cache_mngr_get_fd(DAT_11e45b4c);
                            FUN_10045228(uVar1,5,FUN_10009750,DAT_11e45b4c);
                            return 1;
                          }
                          if (-1 < DAT_11e45404) {
                            uVar1 = FUN_10046f5c();
                            FUN_10047040(0,
                                         "%s %s:%d CRIT Couldn\'t initialize genl/port interface\n",
                                         0x37,uVar1,"netlink.c",0x168);
                          }
                        }
                        nl_cache_mngr_free(DAT_11e45b4c);
                      }
                      nl_socket_free(DAT_11e45b44);
                    }
                  }
                }
              }
              else if (-1 < DAT_11e45404) {
                uVar1 = FUN_10046f5c();
                uVar3 = nl_geterror(-(iVar2 >> 0x1f));
                FUN_10047040(0,"%s %s:%d CRIT Couldn\'t add mdb cache: %s\n",0x2a,uVar1,"netlink.c",
                             0x13c,uVar3);
              }
            }
          }
        }
      }
      else if (-1 < DAT_11e45404) {
        uVar1 = FUN_10046f5c();
        FUN_10047040(0,"%s %s:%d CRIT Couldn\'t set bufsize for manager netlink socket.\n",0x40,
                     uVar1,"netlink.c",0x120);
      }
LAB_1000a4c0:
      nl_cache_mngr_free(DAT_11e45b48);
    }
    nl_socket_free(DAT_11e45b3c);
  }
  nl_socket_free(DAT_11e45b40);
LAB_1000a508:
  nl_socket_free(DAT_11e45b38);
  return 0;
}



/* === FUN_1000fa58 @ 0x1000fa58 (size=184) === */

void FUN_1000fa58(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  void *__ptr;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  memset(&local_50,0,0x30);
  local_50 = 5;
  local_4c = local_14;
  local_48 = 0x124;
  local_44 = local_c;
  local_40 = local_10;
  __ptr = (void *)FUN_1004bc14("/run/route_info%s",local_18);
  FUN_1004bf0c(__ptr,&local_50,0,0,0);
  free(__ptr);
  return;
}



/* === FUN_1000fb10 @ 0x1000fb10 (size=156) === */

void FUN_1000fb10(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *__ptr;
  undefined1 auStack_50 [4];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  memset(auStack_50,0,0x30);
  local_4c = local_14;
  local_48 = 0x124;
  __ptr = (void *)FUN_1004bc14("/run/route_info%s",local_18);
  FUN_1004bf0c(__ptr,auStack_50,local_10,0,0);
  free(__ptr);
  return;
}



