/* ioctl() callers in switchd (BDE wrappers) */
/* === ioctl @ 11317c50 (size=16) === */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ioctl(int __fd,ulong __request,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_ioctl_1181968c)();
  return iVar1;
}



