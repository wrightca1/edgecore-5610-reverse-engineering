/* Packet flow round-2 decomp */

/* === FUN_101f2fac (size=628) === */

undefined4 FUN_101f2fac(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_98;
  undefined4 local_8c [4];
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  int local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar1 = **(int **)(param_1 + 0x96cc);
  local_68 = param_1;
  local_64 = param_2;
  local_60 = param_3;
  local_5c = param_4;
  FUN_107909b8(2,iVar1);
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 3;
  *(undefined4 *)(iVar1 + 0x38) = 0;
  for (local_98 = 0; local_98 < 8; local_98 = local_98 + 1) {
    local_8c[local_98] = 0;
  }
  local_50 = local_8c[0];
  local_4c = local_8c[1];
  local_48 = local_8c[2];
  local_44 = local_8c[3];
  local_40 = local_7c;
  local_3c = local_78;
  local_38 = local_74;
  local_34 = local_70;
  local_30 = local_8c[0];
  local_2c = local_8c[1];
  local_28 = local_8c[2];
  local_24 = local_8c[3];
  local_20 = local_7c;
  local_1c = local_78;
  local_18 = local_74;
  local_14 = local_70;
  FUN_101f1460(*(undefined4 *)(local_68 + 0x97f8),iVar1,local_64 + 4,local_60,&local_50,&local_30,0,
               local_5c,0,0,0);
  FUN_101f2f08(local_68,*(undefined4 *)(local_68 + 0x97f8),local_60,local_64 + 4);
  *(int *)(local_68 + 0x96c8) = iVar1;
  *(undefined4 *)(local_68 + 0x96c0) = 0;
  iVar1 = FUN_1078dbdc(*(undefined4 *)(local_68 + 0x83c),0xffffffff,iVar1);
  if (iVar1 < 0) {
    if ((iVar1 < 1) && (-0x13 < iVar1)) {
      iVar1 = -iVar1;
    }
    else {
      iVar1 = 0x13;
    }
    FUN_101120a0(*(undefined4 *)(local_68 + 0x83c),"Failed to start RX DMA: %s\n",
                 (&PTR_DAT_11e43a78)[iVar1]);
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_101f33f8 (size=1152) === */

undefined4
FUN_101f33f8(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int local_c8;
  int local_c4;
  undefined4 local_ac;
  undefined2 local_a8;
  undefined4 local_a4;
  undefined2 local_a0;
  uint local_9c [4];
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined1 auStack_7c [16];
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar4 = **(int **)(param_1 + 0x96d0);
  iVar1 = *(int *)(param_1 + 0x838);
  local_68 = param_1;
  local_64 = param_2;
  local_60 = param_3;
  local_5c = param_4;
  local_58 = param_5;
  local_54 = param_6;
  FUN_107909b8(1,iVar4);
  iVar5 = local_64;
  *(uint *)(iVar4 + 0x14) = *(uint *)(iVar4 + 0x14) | 2;
  *(uint *)(iVar4 + 0x14) = *(uint *)(iVar4 + 0x14) & 0xfffffffe;
  *(undefined4 *)(iVar4 + 0x38) = 0;
  if (((*(int *)(iVar1 + 0x90) != 0) || (*(int *)(local_68 + 0x9730) != local_60)) ||
     (*(int *)(local_68 + 0x9734) != local_64)) {
    *(int *)(local_68 + 0x9730) = local_60;
    *(int *)(local_68 + 0x9734) = local_64;
    local_ac = *(undefined4 *)(local_68 + 0x9718);
    local_a8 = *(undefined2 *)(local_68 + 0x971c);
    local_a4 = *(undefined4 *)(local_68 + 0x970c);
    local_a0 = *(undefined2 *)(local_68 + 0x9710);
    for (local_c8 = 0; local_c8 < local_60; local_c8 = local_c8 + 1) {
      local_6c = iVar5;
      FUN_101f3220(local_68,iVar1,*(undefined4 *)(*(int *)(local_68 + 0x97f4) + local_c8 * 4),
                   &local_6c,&local_ac,&local_a4);
      FUN_10091c98(&local_ac,*(undefined4 *)(iVar1 + 0x120));
      FUN_10091c98(&local_a4,*(undefined4 *)(iVar1 + 0x114));
      *(int *)(local_68 + 0x9734) = local_6c;
      local_64 = *(int *)(local_68 + 0x9734);
    }
  }
  *(int *)(local_68 + 0x96c4) = iVar4;
  for (local_c4 = 0; local_c4 < 8; local_c4 = local_c4 + 1) {
    local_9c[local_c4] = 0;
  }
  uVar2 = *(uint *)(iVar1 + 0x60);
  iVar5 = ((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
  uVar2 = *(uint *)(iVar1 + 0x60);
  local_9c[iVar5] =
       local_9c[iVar5] |
       1 << (uVar2 + (((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * -0x20 &
            0x3f);
  FUN_101f1184(local_68,local_5c,local_54,*(undefined4 *)(iVar1 + 0x60),
               *(undefined4 *)(iVar1 + 0x94),auStack_7c);
  uVar6 = *(undefined4 *)(local_68 + 0x97f4);
  uVar3 = FUN_101ed844(*(undefined4 *)(iVar1 + 0xf8));
  local_50 = local_9c[0];
  local_4c = local_9c[1];
  local_48 = local_9c[2];
  local_44 = local_9c[3];
  local_40 = local_8c;
  local_3c = local_88;
  local_38 = local_84;
  local_34 = local_80;
  local_30 = *(undefined4 *)(iVar1 + 0x6c);
  local_2c = *(undefined4 *)(iVar1 + 0x70);
  local_28 = *(undefined4 *)(iVar1 + 0x74);
  local_24 = *(undefined4 *)(iVar1 + 0x78);
  local_20 = *(undefined4 *)(iVar1 + 0x7c);
  local_1c = *(undefined4 *)(iVar1 + 0x80);
  local_18 = *(undefined4 *)(iVar1 + 0x84);
  local_14 = *(undefined4 *)(iVar1 + 0x88);
  FUN_101f1460(uVar6,iVar4,local_64,local_60,&local_50,&local_30,uVar3,local_5c,local_58,local_54,
               auStack_7c);
  *(undefined4 *)(local_68 + 0x96bc) = 0;
  iVar4 = FUN_1078dbdc(*(undefined4 *)(local_68 + 0x83c),0xffffffff,iVar4);
  if (iVar4 < 0) {
    if ((iVar4 < 1) && (-0x13 < iVar4)) {
      iVar4 = -iVar4;
    }
    else {
      iVar4 = 0x13;
    }
    FUN_101120a0(*(undefined4 *)(local_68 + 0x83c),"Failed to start TX DMA: %s\n",
                 (&PTR_DAT_11e43a78)[iVar4]);
    uVar6 = 0xffffffff;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}



/* === FUN_100c1f60 (size=708) === */

undefined4 FUN_100c1f60(int param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  char local_28;
  char local_27;
  int local_24;
  
  local_24 = 0;
  if (*(int *)(param_1 * 0xf8 + 0x11f1c8d8) == 0) {
    uVar3 = 0;
  }
  else {
    local_28 = -1;
    for (local_27 = '\0'; local_27 < '\x04'; local_27 = local_27 + '\x01') {
      if ((*(int *)(param_1 * 0xf8 + 0x11f1c8d8) >> ((int)local_27 & 0x3fU) & 1U) == 0) {
        if (local_28 == -1) {
          local_28 = local_27;
        }
      }
      else {
        local_24 = FUN_10790aa0(param_1,(int)local_27,2,0);
        if (local_24 < 0) {
          if ((local_24 < 1) && (-0x13 < local_24)) {
            iVar1 = -local_24;
          }
          else {
            iVar1 = 0x13;
          }
          FUN_10320d20("%s: DMA channel configuration failed: %s\n",param_1 * 0x10 + 0x11e8cef1,
                       (&PTR_DAT_11e43a78)[iVar1]);
        }
      }
    }
    if ((local_28 != -1) && (local_24 = FUN_10790aa0(param_1,(int)local_28,1,0x10), -1 < local_24))
    {
      return 0;
    }
    if (local_28 == -1) {
      pcVar2 = "No remaining channels";
    }
    else {
      if ((local_24 < 1) && (-0x13 < local_24)) {
        local_24 = -local_24;
      }
      else {
        local_24 = 0x13;
      }
      pcVar2 = (&PTR_DAT_11e43a78)[local_24];
    }
    FUN_10320d20("%s: Unable to configure TX DMA channel: %s\n",param_1 * 0x10 + 0x11e8cef1,pcVar2);
    iVar1 = FUN_10791be0(param_1);
    if ((iVar1 < 1) && (-0x13 < iVar1)) {
      iVar1 = -iVar1;
    }
    else {
      iVar1 = 0x13;
    }
    FUN_10320d20("%s: Unable to re-initialize DMA: %s\n",param_1 * 0x10 + 0x11e8cef1,
                 (&PTR_DAT_11e43a78)[iVar1]);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



/* === FUN_1005b3e4 (size=1104) === */

undefined4 FUN_1005b3e4(int param_1,undefined4 param_2,int param_3,int *param_4)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int local_48;
  int *local_44;
  int *local_40;
  int local_3c;
  int local_38;
  
  uVar1 = FUN_1004fe9c(param_1,param_2);
  local_44 = *(int **)(param_3 + 0x18);
  local_3c = 0;
  local_48 = param_3;
  local_40 = local_44;
  do {
    iVar3 = *(int *)(local_48 + 4);
    local_3c = local_3c + 1;
    if (iVar3 < 0x3c) {
      *(undefined4 *)(*local_44 + 4) = 0x40;
      memset((void *)(*(int *)*local_44 + iVar3),0,0x40 - iVar3);
    }
    else {
      *(int *)(*local_44 + 4) = iVar3 + 4;
    }
    for (local_38 = 0; local_38 < 8; local_38 = local_38 + 1) {
      local_44[local_38 + 0x14] = 0;
    }
    iVar3 = ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0);
    local_44[iVar3 + 0x14] =
         local_44[iVar3 + 0x14] |
         1 << (uVar1 + (((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * -0x20 &
              0x3f);
    local_44[0x3f] = local_44[0x3f] | 0x40000;
    *(undefined1 *)((int)local_44 + 7) = 3;
    *(undefined1 *)((int)local_44 + 6) = 3;
    local_44[0x3d] = local_48;
    if (*(int *)(local_48 + 0x1c) == 0) {
      local_44[0x40] = 0;
      break;
    }
    if (local_3c == 0x10) {
      if (3 < DAT_11e45404) {
        uVar2 = FUN_10046f5c();
        FUN_10047040(4,"%s %s:%d early send bcm_pkt_list with %lu\n",0x2b,uVar2,&DAT_11322924,0xaeb,
                     0x10);
      }
      local_44[0x40] = 0;
      iVar3 = FUN_10441108(*(undefined4 *)(param_1 + 4),local_40,FUN_1005b2e4,0x10);
      if (iVar3 < 0) {
        if (0 < DAT_11e45404) {
          uVar2 = FUN_10046f5c();
          if ((iVar3 < 1) && (-0x13 < iVar3)) {
            iVar3 = -iVar3;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10047040(1,"%s %s:%d ERR bcm_tx failed: %s\n",0x20,uVar2,&DAT_11322924,0xaf1,
                       (&PTR_DAT_11e43a78)[iVar3]);
        }
        if (param_4 != (int *)0x0) {
          *param_4 = 0x10;
        }
        return 0;
      }
      local_3c = 0;
      local_48 = *(int *)(local_48 + 0x1c);
      local_44 = *(int **)(local_48 + 0x18);
      local_40 = local_44;
    }
    else {
      local_44[0x40] = *(int *)(*(int *)(local_48 + 0x1c) + 0x18);
      local_48 = *(int *)(local_48 + 0x1c);
      local_44 = *(int **)(local_48 + 0x18);
    }
  } while (local_48 != 0);
  if (param_4 != (int *)0x0) {
    *param_4 = local_3c;
  }
  iVar3 = FUN_10441108(*(undefined4 *)(param_1 + 4),local_40,FUN_1005b2e4,local_3c);
  if (iVar3 < 0) {
    if (0 < DAT_11e45404) {
      uVar2 = FUN_10046f5c();
      if ((iVar3 < 1) && (-0x13 < iVar3)) {
        iVar3 = -iVar3;
      }
      else {
        iVar3 = 0x13;
      }
      FUN_10047040(1,"%s %s:%d ERR bcm_tx failed: %s\n",0x20,uVar2,&DAT_11322924,0xb0e,
                   (&PTR_DAT_11e43a78)[iVar3]);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



/* === FUN_101cfe60 (size=3588) === */

undefined4 FUN_101cfe60(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *__dest;
  undefined4 *__dest_00;
  int iVar4;
  short sVar6;
  undefined2 uVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_2c;
  int local_28 [4];
  int local_18;
  int local_14;
  int iVar5;
  
  iVar1 = *(int *)(param_1 + 0x3c);
  iVar11 = *(int *)(param_1 + 0x14) + param_2 * 0xb8;
  uVar2 = *(uint *)(iVar11 + 0xa8);
  uVar3 = *(uint *)(iVar11 + 0xac);
  iVar10 = *(int *)(param_1 + 0x68);
  local_18 = param_1;
  local_14 = param_2;
  FUN_112b3778(iVar1,*(int *)(param_1 + 0x48) + 4,0,&local_2c);
  FUN_112b3778(iVar1,*(int *)(local_18 + 0x48) + 4,0,local_28);
  if ((local_2c == 0) || (local_28[0] == 0)) {
    FUN_10320d20("Error initializing packet buffers\n");
    goto LAB_101d0c0c;
  }
  __dest = *(undefined4 **)(local_2c + 0x108);
  __dest_00 = *(undefined4 **)(local_28[0] + 0x108);
  *(undefined4 *)(local_2c + 0xfc) = 0x30;
  *(undefined4 *)(local_28[0] + 0xfc) = 0x30;
  iVar4 = (int)uVar2 >> 5;
  iVar5 = (int)uVar3 >> 5;
  if ((*(int *)((&DAT_1212b9c4)[iVar1] + 0x10) == 0) &&
     (((((*(uint *)((&DAT_1212b9c4)[iVar1] + 0x14) & 0x7ffff67f) != 0 ||
        ((*(uint *)((&DAT_1212b9c4)[iVar1] + 0x14) & 0x10) != 0)) ||
       ((*(uint *)((&DAT_1212b9c4)[iVar1] + 0x14) & 0x40) != 0)) ||
      ((*(uint *)((&DAT_1212b9c4)[iVar1] + 0x14) & 0x20) != 0)))) {
    if ((*(uint *)((&DAT_1212b9c4)[iVar1] +
                   (iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0) + 0x784) * 4 + 0x14) &
        1 << (uVar2 + (iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * -0x20 & 0x3f)) == 0)
    {
      if ((*(uint *)((&DAT_1212b9c4)[iVar1] +
                     (iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0) + 0x784) * 4 + 0x14) &
          1 << (uVar3 + (iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * -0x20 & 0x3f)) ==
          0) goto LAB_101d022c;
    }
    iVar8 = FUN_101ce330(iVar1,uVar2);
    if (iVar8 < 0) {
      FUN_10320d20("ERROR: port %s: could not get modid\n",
                   (&DAT_1212b9c4)[iVar1] + uVar2 * 0xb + 0x6c7c);
      goto LAB_101d0c0c;
    }
    *(char *)(local_2c + 0x1e) = (char)uVar3;
    *(undefined1 *)(local_2c + 0x22) = 1;
    sVar6 = (short)iVar8;
    *(short *)(local_2c + 0x1c) = sVar6 + 1;
    *(uint *)(local_2c + 0xfc) = *(uint *)(local_2c + 0xfc) | 0x10000;
    *(short *)(local_2c + 0x20) = sVar6;
    *(char *)(local_28[0] + 0x1e) = (char)uVar2;
    *(undefined1 *)(local_28[0] + 0x22) = 1;
    *(short *)(local_28[0] + 0x1c) = sVar6 + 1;
    *(uint *)(local_28[0] + 0xfc) = *(uint *)(local_28[0] + 0xfc) | 0x10000;
    *(short *)(local_28[0] + 0x20) = sVar6;
  }
LAB_101d022c:
  uVar9 = FUN_1009de38(__dest,*(undefined4 *)(local_18 + 0x48),*(undefined4 *)(local_18 + 0x40),
                       *(undefined4 *)(local_18 + 0x44));
  *(undefined4 *)(local_18 + 0x40) = uVar9;
  uVar7 = DAT_1185062c;
  if ((iVar10 == 0) || (iVar10 == 1)) {
    *__dest = DAT_11850628;
    *(undefined2 *)(__dest + 1) = uVar7;
    uVar7 = DAT_11850624;
    *(undefined4 *)((int)__dest + 6) = DAT_11850620;
    *(undefined2 *)((int)__dest + 10) = uVar7;
    *(ushort *)((int)__dest + 0xe) = (ushort)*(undefined4 *)(iVar11 + 0xb0) & 0xfff;
    *(undefined2 *)(__dest + 3) = 0x8100;
    *(short *)(__dest + 4) = (short)*(undefined4 *)(local_18 + 0x48) + -0x12;
    uVar9 = *(undefined4 *)(local_18 + 0x48);
    for (local_94 = 0; local_94 < 8; local_94 = local_94 + 1) {
      *(undefined4 *)(local_2c + (local_94 + 0x14) * 4) = 0;
    }
    iVar10 = iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
    *(uint *)(local_2c + (iVar10 + 0x14) * 4) =
         *(uint *)(local_2c + (iVar10 + 0x14) * 4) |
         1 << (uVar2 + (iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_90 = 0; local_90 < 8; local_90 = local_90 + 1) {
      *(undefined4 *)(local_2c + (local_90 + 0x1c) * 4) = 0;
    }
    iVar10 = iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
    *(uint *)(local_2c + (iVar10 + 0x1c) * 4) =
         *(uint *)(local_2c + (iVar10 + 0x1c) * 4) |
         1 << (uVar2 + (iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_8c = 0; local_8c < 8; local_8c = local_8c + 1) {
      *(undefined4 *)(local_2c + (local_8c + 0x24) * 4) = 0;
    }
    *(undefined4 *)(local_2c + 0x10c) = uVar9;
    uVar7 = DAT_1185062c;
    *__dest_00 = DAT_11850628;
    *(undefined2 *)(__dest_00 + 1) = uVar7;
    uVar7 = DAT_11850624;
    *(undefined4 *)((int)__dest_00 + 6) = DAT_11850620;
    *(undefined2 *)((int)__dest_00 + 10) = uVar7;
    *(ushort *)((int)__dest_00 + 0xe) = (ushort)*(undefined4 *)(iVar11 + 0xb4) & 0xfff;
    *(undefined2 *)(__dest_00 + 3) = 0x8100;
    *(short *)(__dest_00 + 4) = (short)*(undefined4 *)(local_18 + 0x48) + -0x12;
    uVar9 = *(undefined4 *)(local_18 + 0x48);
    for (local_88 = 0; local_88 < 8; local_88 = local_88 + 1) {
      *(undefined4 *)(local_28[0] + (local_88 + 0x14) * 4) = 0;
    }
    iVar10 = iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0);
    *(uint *)(local_28[0] + (iVar10 + 0x14) * 4) =
         *(uint *)(local_28[0] + (iVar10 + 0x14) * 4) |
         1 << (uVar3 + (iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_84 = 0; local_84 < 8; local_84 = local_84 + 1) {
      *(undefined4 *)(local_28[0] + (local_84 + 0x1c) * 4) = 0;
    }
    iVar10 = iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0);
    *(uint *)(local_28[0] + (iVar10 + 0x1c) * 4) =
         *(uint *)(local_28[0] + (iVar10 + 0x1c) * 4) |
         1 << (uVar3 + (iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_80 = 0; local_80 < 8; local_80 = local_80 + 1) {
      *(undefined4 *)(local_28[0] + (local_80 + 0x24) * 4) = 0;
    }
    *(undefined4 *)(local_28[0] + 0x10c) = uVar9;
  }
  else {
    memcpy(__dest,(void *)(iVar11 + 0x58),6);
    memcpy((void *)((int)__dest + 6),(void *)(iVar11 + 4),6);
    *(ushort *)((int)__dest + 0xe) = (ushort)*(undefined4 *)(iVar11 + 0xb0) & 0xfff;
    *(undefined2 *)(__dest + 3) = 0x8100;
    *(short *)(__dest + 4) = (short)*(undefined4 *)(local_18 + 0x48) + -0x12;
    uVar9 = *(undefined4 *)(local_18 + 0x48);
    for (local_7c = 0; local_7c < 8; local_7c = local_7c + 1) {
      *(undefined4 *)(local_2c + (local_7c + 0x14) * 4) = 0;
    }
    iVar10 = iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0);
    *(uint *)(local_2c + (iVar10 + 0x14) * 4) =
         *(uint *)(local_2c + (iVar10 + 0x14) * 4) |
         1 << (uVar3 + (iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_78 = 0; local_78 < 8; local_78 = local_78 + 1) {
      *(undefined4 *)(local_2c + (local_78 + 0x1c) * 4) = 0;
    }
    iVar10 = iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0);
    *(uint *)(local_2c + (iVar10 + 0x1c) * 4) =
         *(uint *)(local_2c + (iVar10 + 0x1c) * 4) |
         1 << (uVar3 + (iVar5 + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_74 = 0; local_74 < 8; local_74 = local_74 + 1) {
      *(undefined4 *)(local_2c + (local_74 + 0x24) * 4) = 0;
    }
    *(undefined4 *)(local_2c + 0x10c) = uVar9;
    memcpy(__dest_00,(void *)(iVar11 + 4),6);
    memcpy((void *)((int)__dest_00 + 6),(void *)(iVar11 + 0x58),6);
    *(ushort *)((int)__dest_00 + 0xe) = (ushort)*(undefined4 *)(iVar11 + 0xb4) & 0xfff;
    *(undefined2 *)(__dest_00 + 3) = 0x8100;
    *(short *)(__dest_00 + 4) = (short)*(undefined4 *)(local_18 + 0x48) + -0x12;
    uVar9 = *(undefined4 *)(local_18 + 0x48);
    for (local_70 = 0; local_70 < 8; local_70 = local_70 + 1) {
      *(undefined4 *)(local_28[0] + (local_70 + 0x14) * 4) = 0;
    }
    iVar10 = iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
    *(uint *)(local_28[0] + (iVar10 + 0x14) * 4) =
         *(uint *)(local_28[0] + (iVar10 + 0x14) * 4) |
         1 << (uVar2 + (iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_6c = 0; local_6c < 8; local_6c = local_6c + 1) {
      *(undefined4 *)(local_28[0] + (local_6c + 0x1c) * 4) = 0;
    }
    iVar10 = iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
    *(uint *)(local_28[0] + (iVar10 + 0x1c) * 4) =
         *(uint *)(local_28[0] + (iVar10 + 0x1c) * 4) |
         1 << (uVar2 + (iVar4 + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * -0x20 & 0x3f);
    for (local_68 = 0; local_68 < 8; local_68 = local_68 + 1) {
      *(undefined4 *)(local_28[0] + (local_68 + 0x24) * 4) = 0;
    }
    *(undefined4 *)(local_28[0] + 0x10c) = uVar9;
  }
  for (local_98 = 0; local_98 < *(int *)(local_18 + 0x38); local_98 = local_98 + 1) {
    iVar10 = FUN_10440c90(iVar1,local_2c,0);
    if (iVar10 < 0) {
      if ((iVar10 < 1) && (-0x13 < iVar10)) {
        iVar10 = -iVar10;
      }
      else {
        iVar10 = 0x13;
      }
      FUN_10320d20("ERROR: port %s: bcm_tx A #%d failed: %s\n",
                   (&DAT_1212b9c4)[iVar1] + uVar3 * 0xb + 0x6c7c,local_98,
                   (&PTR_DAT_11e43a78)[iVar10]);
      break;
    }
    iVar10 = FUN_10440c90(iVar1,local_28[0],0);
    if (iVar10 < 0) {
      if ((iVar10 < 1) && (-0x13 < iVar10)) {
        iVar10 = -iVar10;
      }
      else {
        iVar10 = 0x13;
      }
      FUN_10320d20("ERROR: port %s: bcm_tx B #%d failed: %s\n",
                   (&DAT_1212b9c4)[iVar1] + uVar2 * 0xb + 0x6c7c,local_98,
                   (&PTR_DAT_11e43a78)[iVar10]);
      break;
    }
  }
LAB_101d0c0c:
  if (local_2c != 0) {
    FUN_112b38c4(iVar1,local_2c);
  }
  if (local_28[0] != 0) {
    FUN_112b38c4(iVar1,local_28[0]);
  }
  return 0;
}



/* === FUN_10186ea0 (size=1692) === */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int FUN_10186ea0(undefined4 param_1,uint param_2,undefined4 param_3,void *param_4,void *param_5,
                uint *param_6)

{
  void *__dest;
  bool bVar1;
  int iVar2;
  int iVar3;
  void **local_24c;
  undefined1 local_248;
  uint local_150;
  void *local_144;
  undefined4 local_140;
  void *local_12c;
  undefined1 auStack_124 [208];
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [4];
  undefined4 local_3c;
  undefined4 local_38 [4];
  undefined4 local_28;
  uint local_24;
  undefined4 local_20;
  void *local_1c;
  void *local_18;
  uint *local_14;
  
  bVar1 = false;
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  local_14 = param_6;
  memset(&local_24c,0,0x1f8);
  iVar2 = FUN_1061dfb0(local_28,local_14[0xc],&local_54,&local_4c,&local_44,&local_3c);
  if (-1 < iVar2) {
    if (((int)local_14[0xc] >> 0x1a == 0x10) || ((int)local_14[0xc] >> 0x1a == 6)) {
      bVar1 = true;
    }
    if ((((*local_14 & 8) == 0) && ((int)local_14[0xc] >> 0x1a != 3)) ||
       (iVar2 = FUN_1061dfb0(local_28,local_20,&local_50,&local_48,auStack_40,local_38), -1 < iVar2)
       ) {
      memset(auStack_124,0,0x10);
      FUN_107b5958(local_28,auStack_124,0,0xfc);
      FUN_107b5958(local_28,auStack_124,7,1);
      FUN_107b5958(local_28,auStack_124,0xb,7);
      if (bVar1) {
        FUN_107b5958(local_28,auStack_124,0x25,2);
        FUN_107b5958(local_28,auStack_124,0x28,4);
        FUN_107b5958(local_28,auStack_124,0x27,0);
        FUN_107b5958(local_28,auStack_124,0x30,0);
        FUN_107b5958(local_28,auStack_124,0x31,0);
        if ((*local_14 & 8) == 0) {
          FUN_107b5958(local_28,auStack_124,0x29,local_3c);
          FUN_107b5958(local_28,auStack_124,0x2a,local_3c);
        }
        else {
          FUN_107b5958(local_28,auStack_124,0x29,local_38[0]);
          FUN_107b5958(local_28,auStack_124,0x2a,local_3c);
        }
      }
      else {
        FUN_107b5958(local_28,auStack_124,0x25,0);
        FUN_107b5958(local_28,auStack_124,2,*(undefined2 *)(local_14 + 0xb));
        if ((*local_14 & 8) == 0) {
          if ((int)local_14[0xc] >> 0x1a == 3) {
            FUN_107b5958(local_28,auStack_124,0xe,local_50);
            FUN_107b5958(local_28,auStack_124,10,local_48);
            FUN_107b5958(local_28,auStack_124,6,local_50);
            FUN_107b5958(local_28,auStack_124,9,0);
          }
          else {
            FUN_107b5958(local_28,auStack_124,0xe,local_54);
            FUN_107b5958(local_28,auStack_124,10,local_4c);
            FUN_107b5958(local_28,auStack_124,6,local_54);
            FUN_107b5958(local_28,auStack_124,9,0);
          }
        }
        else {
          FUN_107b5958(local_28,auStack_124,0xe,local_50);
          FUN_107b5958(local_28,auStack_124,10,local_48);
          if ((int)local_14[0xc] >> 0x1a == 3) {
            FUN_107b5958(local_28,auStack_124,0x15,local_44);
            FUN_107b5958(local_28,auStack_124,0x26,1);
          }
          else {
            FUN_107b5958(local_28,auStack_124,6,local_54);
            FUN_107b5958(local_28,auStack_124,9,local_4c);
          }
        }
      }
      local_144 = (void *)FUN_1075fcd4(local_28,0x80,&DAT_113636f4);
      local_12c = local_144;
      if (local_144 == (void *)0x0) {
        FUN_10320d20("WARNING: Could not alloc tx buffer. Memory error.\n");
        iVar2 = -2;
      }
      else {
        local_24c = &local_144;
        local_248 = 1;
        local_140 = 0x80;
        local_150 = local_150 & 0xffffff0f | 0x300020;
        memset(local_144,0,0x80);
        __dest = *local_24c;
        memcpy(__dest,local_1c,6);
        memcpy((void *)((int)__dest + 6),local_18,6);
        *(undefined2 *)((int)__dest + 0xc) = 0x8100;
        *(ushort *)((int)__dest + 0xe) = *(ushort *)(local_14 + 0xb) & 0xfff | 0xa000;
        *(undefined2 *)((int)__dest + 0x10) = 0x8902;
        *(char *)((int)__dest + 0x12) = (char)(((ulonglong)local_14[9] & 0xff) << 5);
        *(undefined1 *)((int)__dest + 0x14) = 0;
        if ((local_24 & 0x400) == 0) {
          *(undefined1 *)((int)__dest + 0x13) = 0x2f;
          *(undefined1 *)((int)__dest + 0x15) = 0x20;
        }
        else {
          *(undefined1 *)((int)__dest + 0x13) = 0x2b;
          *(undefined1 *)((int)__dest + 0x15) = 0xc;
        }
        iVar2 = FUN_10440c90(local_28,&local_24c,0);
        if (iVar2 != 0) {
          if ((iVar2 < 1) && (-0x13 < iVar2)) {
            iVar3 = -iVar2;
          }
          else {
            iVar3 = 0x13;
          }
          FUN_10760cd4(0x200000,"bcm_tx failed: Unit %d: %s\n",local_28,(&PTR_DAT_11e43a78)[iVar3]);
        }
        FUN_1075ffa4(local_28,local_12c);
      }
    }
  }
  return iVar2;
}



/* === FUN_101a70e8 (size=2108) === */

undefined4 FUN_101a70e8(undefined4 *param_1)

{
  int *piVar1;
  void *__dest;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  void *local_58;
  int local_54;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  piVar5 = param_1 + 0x1e;
  local_54 = -1;
  local_58 = (void *)0x0;
  if (((param_1[7] == 0) || (*(char *)param_1[7] == '\0')) ||
     (local_58 = (void *)FUN_101a61c4(*param_1,param_1[7],param_1 + 6), local_58 != (void *)0x0)) {
    if (*(int *)(*piVar5 + 4) != param_1[6]) {
      FUN_1075ffa4(*param_1,*(undefined4 *)*piVar5);
      piVar1 = (int *)*piVar5;
      iVar2 = FUN_1075fcd4(*param_1,param_1[6],&DAT_1136e800);
      *piVar1 = iVar2;
      if (*piVar1 == 0) {
        FUN_10760cd4(0x200000,"Unable to allocate packet memory\n");
        return 0xffffffff;
      }
      *(undefined4 *)(*piVar5 + 4) = param_1[6];
    }
    memset(*(void **)*piVar5,0,*(size_t *)(*piVar5 + 4));
    if (local_58 != (void *)0x0) {
      memcpy(*(void **)*piVar5,local_58,param_1[6]);
      FUN_1075ffa4(*param_1,local_58);
    }
    param_1[0x5d] = param_1[0x5d] & 0xffffff0f;
    if (param_1[0x1d] == 1) {
      uVar8 = 0x20;
    }
    else {
      uVar8 = 0;
    }
    if (param_1[0x1d] == 2) {
      uVar6 = 0x30;
    }
    else {
      uVar6 = 0;
    }
    param_1[0x5d] = param_1[0x5d] | uVar8 | uVar6;
    param_1[0x5d] = param_1[0x5d] & 0xfffffeff;
    if (param_1[0x1a] == 0) {
      iVar2 = 0x40;
    }
    else {
      iVar2 = 0x44;
    }
    if ((int)param_1[6] < iVar2) {
      param_1[0x5d] = param_1[0x5d] | 0x100;
    }
    param_1[0x5d] = param_1[0x5d] & 0xfffffbff;
    if (param_1[0xb1] != 0) {
      param_1[0x5d] = param_1[0x5d] | 0x400;
    }
    FUN_101a62c8(param_1);
    FUN_101a6e68(param_1);
    __dest = *(void **)*piVar5;
    iVar2 = *(int *)*piVar5;
    iVar7 = *(int *)(*piVar5 + 4) + -0x1e;
    if (param_1[2] != 0) {
      FUN_10760cd4(0x2000,"Per port source is active\n");
      param_1[0x12] = param_1[0x32];
      param_1[0x13] = param_1[0x33];
      param_1[0x14] = param_1[0x34];
      param_1[0x15] = param_1[0x35];
      param_1[0x16] = param_1[0x36];
      param_1[0x17] = param_1[0x37];
      param_1[0x18] = param_1[0x38];
      param_1[0x19] = param_1[0x39];
      local_30 = param_1[0x32];
      local_2c = param_1[0x33];
      local_28 = param_1[0x34];
      local_24 = param_1[0x35];
      local_20 = param_1[0x36];
      local_1c = param_1[0x37];
      local_18 = param_1[0x38];
      local_14 = param_1[0x39];
      FUN_101a5b00(*param_1,&local_30,param_1 + 0x32);
      memcpy(param_1 + 0xb,(void *)((int)param_1 + 0x26),6);
    }
    if (param_1[0xb2] != 0) {
      param_1[0x8b] = param_1[0x8b] | 1;
      param_1[0x8b] = param_1[0x8b] | 2;
      *(char *)(param_1 + 0x8c) = (char)param_1[0xb2];
      *(char *)((int)param_1 + 0x231) = (char)param_1[0xb3];
      if (param_1[0xb4] != 0) {
        param_1[0x8b] = param_1[0x8b] | 4;
        *(short *)((int)param_1 + 0x232) = (short)param_1[0xb4];
      }
    }
    param_1[5] = 0;
    while( true ) {
      if (((uint)param_1[4] <= (uint)param_1[5]) || (param_1[3] != 1)) goto LAB_101a7874;
      if (param_1[0xd] != 0) {
        memcpy(__dest,param_1 + 8,6);
      }
      if (param_1[0xe] != 0) {
        memcpy((void *)((int)__dest + 6),(void *)((int)param_1 + 0x26),6);
      }
      if (((param_1[7] == 0) || (*(char *)param_1[7] == '\0')) && (param_1[0x11] != 0)) {
        FUN_1009dcc4(iVar2 + 0x1a,iVar7);
      }
      else if (((param_1[7] == 0) || (*(char *)param_1[7] == '\0')) &&
              ((param_1[5] == 0 || (param_1[0x10] != 0)))) {
        uVar3 = FUN_1009de38(iVar2 + 0x1a,iVar7,param_1[0xf],param_1[0x10]);
        param_1[0xf] = uVar3;
      }
      local_54 = FUN_10440c90(param_1[1],piVar5,0);
      if (local_54 != 0) break;
      FUN_10091c98(param_1 + 8,param_1[0xd]);
      FUN_10091c98((int)param_1 + 0x26,param_1[0xe]);
      if (param_1[2] != 0) {
        local_30 = param_1[0x12];
        local_2c = param_1[0x13];
        local_28 = param_1[0x14];
        local_24 = param_1[0x15];
        local_20 = param_1[0x16];
        local_1c = param_1[0x17];
        local_18 = param_1[0x18];
        local_14 = param_1[0x19];
        iVar4 = FUN_101a5ca4(*param_1,param_1 + 0x32,&local_30);
        if (iVar4 != 0) {
          FUN_10760cd4(0x2000,"resetting mac\n");
          memcpy((void *)((int)param_1 + 0x26),param_1 + 0xb,6);
        }
      }
      param_1[5] = param_1[5] + 1;
    }
    if ((local_54 < 1) && (-0x13 < local_54)) {
      iVar2 = -local_54;
    }
    else {
      iVar2 = 0x13;
    }
    FUN_10760cd4(0x200000,"bcm_tx failed2: TX Unit %d: %s\n",param_1[1],(&PTR_DAT_11e43a78)[iVar2]);
LAB_101a7874:
    if (param_1[2] != 0) {
      memcpy((void *)((int)param_1 + 0x26),param_1 + 0xb,6);
      param_1[0x32] = param_1[0x12];
      param_1[0x33] = param_1[0x13];
      param_1[0x34] = param_1[0x14];
      param_1[0x35] = param_1[0x15];
      param_1[0x36] = param_1[0x16];
      param_1[0x37] = param_1[0x17];
      param_1[0x38] = param_1[0x18];
      param_1[0x39] = param_1[0x19];
    }
    if (local_54 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0xffffffff;
    }
  }
  else {
    FUN_10760cd4(0x200000,"Unable to load packet from file %s\n",param_1[7]);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



