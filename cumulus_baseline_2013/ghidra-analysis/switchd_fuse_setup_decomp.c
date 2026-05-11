/* Functions that call into libfuse (the FUSE setup site) */

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



