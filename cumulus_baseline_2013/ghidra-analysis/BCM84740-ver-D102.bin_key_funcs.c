/* PHY firmware key functions, decompiled */
/* Note: 8051 decompilation is generally LOW QUALITY - prefer assembly */

/* === 0xacce (size=1453) === */

void FUN_CODE_acce(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar3 = 1;
  FUN_CODE_e2cd(0xcb,0xe0);
  DAT_EXTMEM_01ee = bVar3 & 1;
  DAT_EXTMEM_01ed = '\0';
  bVar3 = 0x27;
  FUN_CODE_e2cd(0x81,0x96);
  DAT_EXTMEM_01f0 = bVar3 & 1;
  DAT_EXTMEM_01ef = '\0';
  DAT_EXTMEM_0107 = DAT_EXTMEM_0100;
  DAT_EXTMEM_0108 = DAT_EXTMEM_0101;
  bVar3 = 0x21;
  FUN_CODE_e2cd(0xcd,10);
  DAT_EXTMEM_0101 = bVar3 & 1;
  DAT_EXTMEM_0100 = '\0';
  bVar3 = 0x19;
  FUN_CODE_e3de(0xc9);
  DAT_EXTMEM_01ec = bVar3 & 3;
  DAT_EXTMEM_01eb = 0;
  if (DAT_EXTMEM_01ec == 0) {
    DAT_EXTMEM_0103 = DAT_EXTMEM_0174;
    DAT_EXTMEM_0104 = DAT_EXTMEM_0175;
    DAT_EXTMEM_0174 = '\0';
    DAT_EXTMEM_0175 = '\x01';
  }
  else if (DAT_EXTMEM_01ec == 1) {
    DAT_EXTMEM_0175 = '\x01';
    DAT_EXTMEM_0103 = '\0';
    DAT_EXTMEM_0104 = '\0';
    DAT_EXTMEM_0174 = '\0';
  }
  else if (DAT_EXTMEM_01ec == 2) {
    DAT_EXTMEM_0103 = '\0';
    DAT_EXTMEM_0104 = '\0';
    DAT_EXTMEM_0174 = '\0';
    DAT_EXTMEM_0175 = '\0';
  }
  else if (DAT_EXTMEM_01ec == 3) {
    DAT_EXTMEM_0104 = '\x01';
    DAT_EXTMEM_0174 = '\0';
    DAT_EXTMEM_0175 = '\0';
    DAT_EXTMEM_0103 = '\0';
  }
  DAT_EXTMEM_0105 = DAT_EXTMEM_0197;
  DAT_EXTMEM_0106 = DAT_EXTMEM_0198;
  bVar3 = 1;
  FUN_CODE_e2cd(0xcd,10);
  if ((bVar3 & 1) == 1) {
LAB_CODE_adcf:
    DAT_EXTMEM_0198 = '\x01';
  }
  else {
    if (_0_4 != '\0') {
      bVar3 = 0;
      FUN_CODE_e2cd(0,0);
      if ((bVar3 >> 1 & 1) != 0) goto LAB_CODE_adcf;
    }
    DAT_EXTMEM_0198 = '\0';
  }
  DAT_EXTMEM_0197 = '\0';
  bVar3 = 0x78;
  uVar1 = 200;
  FUN_CODE_e3de();
  DAT_EXTMEM_0172 = DAT_EXTMEM_0117;
  DAT_EXTMEM_0173 = DAT_EXTMEM_0118;
  DAT_EXTMEM_0118 = bVar3 & 0x20;
  DAT_EXTMEM_0117 = '\0';
  bVar4 = 0x1d;
  uVar2 = 200;
  DAT_EXTMEM_01eb = uVar1;
  DAT_EXTMEM_01ec = bVar3;
  FUN_CODE_e3de();
  DAT_EXTMEM_011b = DAT_EXTMEM_0114;
  DAT_EXTMEM_011c = DAT_EXTMEM_0115;
  DAT_EXTMEM_0119 = DAT_EXTMEM_0111;
  DAT_EXTMEM_011a = DAT_EXTMEM_0112;
  DAT_EXTMEM_0112 = bVar4 & 2;
  DAT_EXTMEM_0111 = 0;
  DAT_EXTMEM_0115 = bVar4 & 4;
  DAT_EXTMEM_0114 = '\0';
  uVar1 = 0x58;
  bVar3 = 0xcd;
  DAT_EXTMEM_01eb = uVar2;
  DAT_EXTMEM_01ec = bVar4;
  FUN_CODE_e3de();
  DAT_EXTMEM_01f3 = bVar3 & 1;
  DAT_EXTMEM_01f4 = '\0';
  DAT_EXTMEM_01f5 = bVar3 & 2;
  DAT_EXTMEM_01f6 = '\0';
  DAT_EXTMEM_01eb = bVar3;
  DAT_EXTMEM_01ec = uVar1;
  if ((_0_0 == '\x01') || (_0_2 != '\0')) {
    if (DAT_EXTMEM_0118 == 0 && DAT_EXTMEM_0117 == '\0') {
      FUN_CODE_e293(0xff,0xfe,199,0x35);
    }
    else {
      FUN_CODE_e259(0,1,199,0x35);
    }
    bVar3 = 0x2d;
    FUN_CODE_e3de(199);
    if ((bVar3 & 1) != 0) {
      bVar3 = 0x2f;
      FUN_CODE_e3de(199);
      if ((bVar3 & 1) != 0) {
        bVar3 = 0x31;
        FUN_CODE_e3de(199);
        if ((bVar3 & 1) != 0) {
          bVar3 = 0x33;
          FUN_CODE_e3de(199);
          if ((bVar3 & 1) == 1) goto LAB_CODE_af04;
        }
      }
    }
    if ((_0_0 == '\x01') || (_0_2 != '\0')) {
      bVar3 = 0;
      FUN_CODE_e2cd(199,0x10);
      if ((bVar3 >> 1 & 1) != 1) {
        FUN_CODE_e392(0,8,199,0);
      }
    }
  }
LAB_CODE_af04:
  if (((DAT_EXTMEM_0198 == '\0' && DAT_EXTMEM_0197 == '\0') ||
      (DAT_EXTMEM_0106 != '\0' || DAT_EXTMEM_0105 != '\0')) &&
     ((DAT_EXTMEM_0198 != '\0' || DAT_EXTMEM_0197 != '\0' ||
      (DAT_EXTMEM_0106 == '\0' && DAT_EXTMEM_0105 == '\0')))) {
    if ((DAT_EXTMEM_01f4 == '\0' && DAT_EXTMEM_01f3 == 0) &&
       ((((DAT_EXTMEM_0198 != '\0' || DAT_EXTMEM_0197 != '\0' &&
          (DAT_EXTMEM_0118 != 0 || DAT_EXTMEM_0117 != '\0')) &&
         (DAT_EXTMEM_0173 == '\0' && DAT_EXTMEM_0172 == '\0')) ||
        ((DAT_EXTMEM_0198 == '\0' && DAT_EXTMEM_0197 == '\0' &&
         ((((DAT_EXTMEM_0115 != 0 || DAT_EXTMEM_0114 != '\0' &&
            (DAT_EXTMEM_0175 != '\0' || DAT_EXTMEM_0174 != '\0')) &&
           (DAT_EXTMEM_0104 == '\0' && DAT_EXTMEM_0103 == '\0')) ||
          (((DAT_EXTMEM_0115 != 0 || DAT_EXTMEM_0114 != '\0' &&
            (DAT_EXTMEM_011c == '\0' && DAT_EXTMEM_011b == '\0')) ||
           ((DAT_EXTMEM_0115 == 0 && DAT_EXTMEM_0114 == '\0' &&
            (DAT_EXTMEM_011c != '\0' || DAT_EXTMEM_011b != '\0')))))))))))) {
      FUN_CODE_e218(0xf3,0xff,0xcd,0x53,1);
      FUN_CODE_e259(3,0,0xcd,0x53);
      FUN_CODE_e293(0xc,0xff,0xcd,0x53);
      FUN_CODE_e259(0,8,0xce,2);
      FUN_CODE_e259(0x40,0,200,0x78);
      FUN_CODE_e293(0xbf,0xff,200,0x78);
    }
  }
  else {
    if (DAT_EXTMEM_01ee == 0 && DAT_EXTMEM_01ed == '\0') {
      FUN_CODE_e259(0,1,0xcb,0xe0);
      FUN_CODE_e293(0xff,0xfe,0xcb,0xe0);
      FUN_CODE_e3bd(DAT_EXTMEM_0225,0,0x10);
      FUN_CODE_e259(0,1,0xce,2);
      FUN_CODE_e259(0x40,0,200,0x78);
      FUN_CODE_e293(0xbf,0xff,200,0x78);
    }
    if (DAT_EXTMEM_01f4 == '\0' && DAT_EXTMEM_01f3 == 0) {
      FUN_CODE_e218(0xf3,0xff,0xcd,0x53,1);
      FUN_CODE_e259(3,0,0xcd,0x53);
      FUN_CODE_e293(0xc,0xff,0xcd,0x53);
      FUN_CODE_e259(0,4,0xce,2);
      FUN_CODE_e259(0x40,0,200,0x78);
      FUN_CODE_e293(0xbf,0xff,200,0x78);
    }
  }
  if ((((DAT_EXTMEM_0101 != 0 || DAT_EXTMEM_0100 != '\0') &&
       (DAT_EXTMEM_0108 == '\0' && DAT_EXTMEM_0107 == '\0')) ||
      ((DAT_EXTMEM_0101 == 0 && DAT_EXTMEM_0100 == '\0' &&
       (DAT_EXTMEM_0108 != '\0' || DAT_EXTMEM_0107 != '\0')))) &&
     (DAT_EXTMEM_01f0 == 0 && DAT_EXTMEM_01ef == '\0')) {
    FUN_CODE_e1d7(0,1,0x81,0x96,0x27);
    FUN_CODE_e293(0xff,0xfe,0x81,0x96);
    FUN_CODE_e259(0,2,0xce,2);
    FUN_CODE_e259(0x40,0,200,0x78);
    FUN_CODE_e293(0xbf,0xff,200,0x78);
  }
  if (((DAT_EXTMEM_01f6 == '\0' && DAT_EXTMEM_01f5 == 0) &&
      (DAT_EXTMEM_0101 == 0 && DAT_EXTMEM_0100 == '\0')) &&
     ((((DAT_EXTMEM_0112 != 0 || DAT_EXTMEM_0111 != 0 &&
        ((DAT_EXTMEM_0118 != 0 || DAT_EXTMEM_0117 != '\0' &&
         (DAT_EXTMEM_0173 == '\0' && DAT_EXTMEM_0172 == '\0')))) ||
       ((DAT_EXTMEM_0112 != 0 || DAT_EXTMEM_0111 != 0 &&
        (DAT_EXTMEM_011a == '\0' && DAT_EXTMEM_0119 == '\0')))) ||
      ((DAT_EXTMEM_0112 == 0 && DAT_EXTMEM_0111 == 0 &&
       (DAT_EXTMEM_011a != '\0' || DAT_EXTMEM_0119 != '\0')))))) {
    if ((DAT_EXTMEM_011a == '\0' && DAT_EXTMEM_0119 == '\0') ||
       ((DAT_EXTMEM_0173 == '\0' && DAT_EXTMEM_0172 == '\0' ||
        (DAT_EXTMEM_0108 != '\0' || DAT_EXTMEM_0107 != '\0')))) {
      FUN_CODE_e3bd(DAT_EXTMEM_0225,0,10);
    }
    FUN_CODE_e218(0xff,0x3f,0xcd,0x53,1);
    FUN_CODE_e259(0,0x30,0xcd,0x53);
    FUN_CODE_e293(0xff,0xcf,0xcd,0x53);
    FUN_CODE_e259(0,0x10,0xce,2);
    FUN_CODE_e259(0x40,0,200,0x78);
    bVar3 = 0;
    FUN_CODE_e293(0xbf,0xff,0x78);
  }
  else {
    bVar3 = DAT_EXTMEM_01f5;
    if ((DAT_EXTMEM_01f6 == '\0' && DAT_EXTMEM_01f5 == 0) &&
       (bVar3 = DAT_EXTMEM_0111, DAT_EXTMEM_0112 == 0 && DAT_EXTMEM_0111 == 0)) {
      FUN_CODE_e1d7(0,0xf0,0xcd,0x53,1);
      FUN_CODE_e259(0,0x10,0xce,2);
      bVar3 = 0;
      FUN_CODE_e259(0x40,0,0x78);
    }
  }
  FUN_CODE_e2cd(0xcd,0x14,0x21);
  if ((bVar3 & 1) != 1) {
    bVar3 = 1;
    FUN_CODE_e2cd(0,0);
    if ((((bVar3 & 1) == 0) || (DAT_EXTMEM_0112 == 0 && DAT_EXTMEM_0111 == 0)) ||
       (DAT_EXTMEM_0115 == 0 && DAT_EXTMEM_0114 == '\0')) {
      DAT_EXTMEM_01f2 = '\0';
      goto LAB_CODE_b23b;
    }
  }
  DAT_EXTMEM_01f2 = '\x01';
LAB_CODE_b23b:
  DAT_EXTMEM_01f1 = 0;
  if (DAT_EXTMEM_01f2 == '\0') {
    if (DAT_EXTMEM_0116 == '\x01') {
      FUN_CODE_e218(0xff,0xfe,0xcd,10,0x21);
      DAT_EXTMEM_0116 = '\0';
    }
    return;
  }
  FUN_CODE_e1d7(0,1,0xcd,10,0x21);
  DAT_EXTMEM_0116 = 1;
  return;
}



/* === 0xcead (size=314) === */

void FUN_CODE_cead(char param_1)

{
  char cVar1;
  byte bVar2;
  
  FUN_CODE_d1e0(0x1f1);
  DAT_EXTMEM_01f4 = param_1;
  FUN_CODE_d1d7(0x1f1);
  DAT_EXTMEM_01f9 = FUN_CODE_d135(1);
  DAT_EXTMEM_01f8 = 0;
  FUN_CODE_d1d7(0x1f1);
  bVar2 = FUN_CODE_d11c();
  DAT_EXTMEM_01f8 = DAT_EXTMEM_01f9;
  DAT_EXTMEM_01fa = 0;
  cVar1 = BANK0_R5 + '\x01';
  DAT_EXTMEM_01fb = 1;
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01fa = DAT_EXTMEM_01fa << 1 | DAT_EXTMEM_01fb >> 7;
    DAT_EXTMEM_01fb = DAT_EXTMEM_01fb << 1;
  }
  DAT_EXTMEM_01f9 = bVar2;
  FUN_CODE_d196(0x1fa,0xff,DAT_EXTMEM_01f4 + '\x01');
  cVar1 = BANK0_R5 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01fb = DAT_EXTMEM_01fb >> 1 | DAT_EXTMEM_01fa << 7;
    DAT_EXTMEM_01fa = DAT_EXTMEM_01fa >> 1;
  }
  cVar1 = BANK0_R5 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01fa = DAT_EXTMEM_01fa << 1 | DAT_EXTMEM_01fb >> 7;
    DAT_EXTMEM_01fb = DAT_EXTMEM_01fb << 1;
  }
  DAT_EXTMEM_01fd = ~DAT_EXTMEM_01fb;
  DAT_EXTMEM_01fc = ~DAT_EXTMEM_01fa;
  cVar1 = BANK0_R5 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01f6 = DAT_EXTMEM_01f6 << 1 | DAT_EXTMEM_01f7 >> 7;
    DAT_EXTMEM_01f7 = DAT_EXTMEM_01f7 << 1;
  }
  cVar1 = (DAT_EXTMEM_01f9 & DAT_EXTMEM_01fd) + (DAT_EXTMEM_01f7 & DAT_EXTMEM_01fb);
  DAT_EXTMEM_01f8 =
       (DAT_EXTMEM_01f8 & DAT_EXTMEM_01fc) +
       ((DAT_EXTMEM_01f6 & DAT_EXTMEM_01fa) -
       ((CARRY1(DAT_EXTMEM_01f9 & DAT_EXTMEM_01fd,DAT_EXTMEM_01f7 & DAT_EXTMEM_01fb) << 7) >> 7));
  DAT_EXTMEM_01f9 = cVar1;
  FUN_CODE_d1d7(0x1f1,cVar1);
  FUN_CODE_d162(cVar1);
  cVar1 = DAT_EXTMEM_01f8;
  FUN_CODE_d1d7(0x1f1,DAT_EXTMEM_01f8);
  FUN_CODE_d174(cVar1,1);
  return;
}



/* === 0xc4cc (size=648) === */

void FUN_CODE_c4cc(void)

{
  DAT_EXTMEM_9431 = 0;
  DAT_EXTMEM_9430 = 8;
  DAT_EXTMEM_9433 = 0xba;
  DAT_EXTMEM_9432 = 0xa1;
  DAT_EXTMEM_9437 = 0x1a;
  DAT_EXTMEM_9436 = 0xc;
  DAT_EXTMEM_9511 = 0;
  DAT_EXTMEM_9510 = 0;
  DAT_EXTMEM_9513 = 0;
  DAT_EXTMEM_9512 = 0;
  DAT_EXTMEM_9515 = 0;
  DAT_EXTMEM_9514 = 0;
  DAT_EXTMEM_9516 = 0;
  DAT_EXTMEM_9517 = 0;
  DAT_EXTMEM_9519 = 0;
  DAT_EXTMEM_9518 = 0;
  DAT_EXTMEM_01a1 = 0;
  DAT_EXTMEM_01a2 = 0x18;
  FUN_CODE_df80(0x3e,0x95,1,0xff,0xe0);
  DAT_EXTMEM_01ef = 2;
  DAT_EXTMEM_01f0 = 0;
  DAT_EXTMEM_01f1 = 1;
  FUN_CODE_d355(2,0x83,0x78,7);
  DAT_EXTMEM_01ef = 9;
  DAT_EXTMEM_01f0 = 0;
  DAT_EXTMEM_01f1 = 1;
  FUN_CODE_d355(9,0x83,0x70,7);
  DAT_EXTMEM_01ef = 1;
  DAT_EXTMEM_01f0 = 0;
  DAT_EXTMEM_01f1 = 1;
  FUN_CODE_d355(1,0x83,0x70,7);
  DAT_EXTMEM_01ef = 0xe;
  DAT_EXTMEM_01f0 = 0;
  DAT_EXTMEM_01f1 = 0;
  FUN_CODE_d355(0xf,0x83,0x72,7);
  FUN_CODE_e334(0,2,0x83,0x50,7);
  FUN_CODE_e334(6,0,0x83,0x56,7);
  FUN_CODE_e334(0,0,0x83,0x57,7);
  FUN_CODE_e334(0,0,0x83,0x74,7);
  FUN_CODE_e334(0x12,0,0,0,7);
  FUN_CODE_e334(0,0,0xce,0x10,1);
  FUN_CODE_e334(0,0x80,0xce,0x11,1);
  FUN_CODE_e334(0,0x80,0xce,0x12,1);
  DAT_EXTMEM_01f5 = 8;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 7;
  FUN_CODE_cead(0xe2,0x94,1,10);
  DAT_EXTMEM_01f5 = 0xc;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 7;
  FUN_CODE_cead(0xe2,0x94,1,0xe);
  DAT_EXTMEM_01f5 = 0xf;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 1;
  FUN_CODE_cead(0xe2,0x94,1,0xf);
  DAT_EXTMEM_01f5 = 0;
  DAT_EXTMEM_01f6 = 0x40;
  DAT_EXTMEM_01f7 = 0;
  FUN_CODE_cead(0x54,0x94,1,0xf);
  DAT_EXTMEM_01f5 = 0;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 0xd;
  FUN_CODE_cead(0x56,0x94,1,0xd);
  DAT_EXTMEM_01f5 = 0;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 0xd;
  FUN_CODE_cead(0x58,0x94,1,0xd);
  DAT_EXTMEM_01f5 = 8;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 0x1b;
  FUN_CODE_cead(0x5a,0x94,1,0xc);
  DAT_EXTMEM_01f5 = 0;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 0x19;
  FUN_CODE_cead(0x5a,0x94,1,4);
  DAT_EXTMEM_948c = 0x33;
  DAT_EXTMEM_948d = 3;
  DAT_EXTMEM_94e4 = 8;
  DAT_EXTMEM_94e5 = 8;
  DAT_EXTMEM_94e6 = 0xb;
  DAT_EXTMEM_94e7 = 0x13;
  DAT_EXTMEM_9544 = 7;
  DAT_EXTMEM_9545 = 0;
  DAT_EXTMEM_94c3 = 0xb4;
  DAT_EXTMEM_94c2 = 0x9b;
  DAT_EXTMEM_94c1 = 0x30;
  DAT_EXTMEM_94c0 = 0x2d;
  DAT_EXTMEM_94bf = 0x1c;
  DAT_EXTMEM_94be = 0x20;
  DAT_EXTMEM_94bd = 0xc;
  DAT_EXTMEM_94bc = 0x7b;
  DAT_EXTMEM_94bb = 0x23;
  DAT_EXTMEM_94ba = 0x12;
  DAT_EXTMEM_94b9 = 8;
  DAT_EXTMEM_94b8 = 0xfe;
  DAT_EXTMEM_94b7 = 3;
  DAT_EXTMEM_94b6 = 7;
  DAT_EXTMEM_94ad = 0x7f;
  DAT_EXTMEM_94ac = 0x34;
  DAT_EXTMEM_94ab = 0x14;
  DAT_EXTMEM_94a9 = 0x5a;
  DAT_EXTMEM_94a8 = 0x56;
  DAT_EXTMEM_940f = DAT_EXTMEM_940f | 1;
  DAT_EXTMEM_965a = DAT_EXTMEM_965a & 0xf3 | 0xc;
  DAT_EXTMEM_9649 = DAT_EXTMEM_9649 & 0xc1 | 0x36;
  DAT_EXTMEM_9648 = 0xa9;
  return;
}



/* === 0xc978 (size=526) === */

void FUN_CODE_c978(void)

{
  DAT_EXTMEM_9431 = 0;
  DAT_EXTMEM_9430 = 8;
  DAT_EXTMEM_9433 = 10;
  DAT_EXTMEM_9432 = 0xa0;
  DAT_EXTMEM_9437 = 0xf8;
  DAT_EXTMEM_9436 = 0xc;
  DAT_EXTMEM_9511 = 0;
  DAT_EXTMEM_9510 = 0;
  DAT_EXTMEM_9513 = 0;
  DAT_EXTMEM_9512 = 0;
  DAT_EXTMEM_9515 = 0;
  DAT_EXTMEM_9514 = 0;
  DAT_EXTMEM_9516 = 0;
  DAT_EXTMEM_9517 = 0;
  DAT_EXTMEM_9519 = 0;
  DAT_EXTMEM_9518 = 0;
  DAT_EXTMEM_01a1 = 0;
  DAT_EXTMEM_01a2 = 0x18;
  FUN_CODE_df80(0x3e,0x95,1,0xff,0xe0);
  if (DAT_EXTMEM_9434 == 'D') {
    DAT_EXTMEM_94a4 = 0;
    DAT_EXTMEM_94a6 = 1;
    DAT_EXTMEM_94a7 = 0x7f;
    DAT_EXTMEM_94a8 = 0;
    DAT_EXTMEM_94a9 = 0;
  }
  else {
    DAT_EXTMEM_94a4 = 0x75;
    DAT_EXTMEM_94a6 = 0x7e;
    DAT_EXTMEM_94a7 = 2;
    DAT_EXTMEM_94a8 = 0x7c;
    DAT_EXTMEM_94a9 = 4;
  }
  DAT_EXTMEM_94a5 = 0;
  DAT_EXTMEM_94aa = 0x7a;
  DAT_EXTMEM_94ab = 6;
  DAT_EXTMEM_94ac = 0x78;
  DAT_EXTMEM_94ad = 8;
  DAT_EXTMEM_94ae = 0x76;
  DAT_EXTMEM_94af = 10;
  DAT_EXTMEM_94b0 = 0x74;
  DAT_EXTMEM_94b1 = 0xc;
  DAT_EXTMEM_94b2 = 0x72;
  DAT_EXTMEM_94b3 = 0xe;
  DAT_EXTMEM_94b4 = 0x70;
  DAT_EXTMEM_94b5 = 0x10;
  DAT_EXTMEM_94b6 = 0x6e;
  DAT_EXTMEM_94b7 = 0x12;
  DAT_EXTMEM_94b8 = 0x6c;
  DAT_EXTMEM_94b9 = 0x14;
  DAT_EXTMEM_94ba = 0x6a;
  DAT_EXTMEM_94bb = 0x16;
  DAT_EXTMEM_94bc = 0x68;
  DAT_EXTMEM_94bd = 0x18;
  DAT_EXTMEM_94be = 0x77;
  DAT_EXTMEM_94bf = 0x16;
  DAT_EXTMEM_94c0 = 0x18;
  DAT_EXTMEM_94c1 = 0x1a;
  DAT_EXTMEM_94c2 = 0x1c;
  DAT_EXTMEM_94c3 = 0x7c;
  DAT_EXTMEM_9596 = 7;
  DAT_EXTMEM_9597 = 0;
  DAT_EXTMEM_9544 = 3;
  DAT_EXTMEM_9545 = 0;
  DAT_EXTMEM_01a1 = 0;
  DAT_EXTMEM_01a2 = 0x14;
  FUN_CODE_df80(0x46,0x96,1,0xff,0xc3);
  DAT_EXTMEM_9462 = 0;
  DAT_EXTMEM_9463 = 1;
  DAT_EXTMEM_9464 = 0xff;
  DAT_EXTMEM_9465 = 0xff;
  DAT_EXTMEM_948a = 0;
  DAT_EXTMEM_948b = 2;
  DAT_EXTMEM_948c = 0x37;
  DAT_EXTMEM_948d = 99;
  DAT_EXTMEM_945a = 0x1a;
  DAT_EXTMEM_945b = 0x1c;
  DAT_EXTMEM_9458 = 0xff;
  DAT_EXTMEM_9459 = 0xf;
  DAT_EXTMEM_9456 = 0xff;
  DAT_EXTMEM_9457 = 0xf;
  DAT_EXTMEM_9454 = 0;
  DAT_EXTMEM_9455 = 0xff;
  DAT_EXTMEM_9452 = 0x48;
  DAT_EXTMEM_9453 = 0;
  DAT_EXTMEM_947e = 0x7b;
  DAT_EXTMEM_947f = 0x7b;
  FUN_CODE_e334(0,0,0x83,0x29,7);
  DAT_EXTMEM_940f = DAT_EXTMEM_940f & 0xfe;
  DAT_EXTMEM_01f0 = 0xd0;
  DAT_EXTMEM_01f1 = 0;
  FUN_CODE_e0f2(3,0xff,0xca,2,1);
  DAT_EXTMEM_01f0 = 0;
  DAT_EXTMEM_01f1 = 0x50;
  FUN_CODE_e0f2(0xff,0xf,0xca,6,1);
  FUN_CODE_e334(0,0,0xce,0x10,1);
  FUN_CODE_e334(0,0x80,0xce,0x11,1);
  FUN_CODE_e334(0,0x80,0xce,0x12,1);
  DAT_EXTMEM_01f0 = 0xd0;
  DAT_EXTMEM_01f1 = 0;
  FUN_CODE_e0f2(3,0xff,0xc9,0xb,0x21);
  DAT_EXTMEM_01f0 = 0;
  DAT_EXTMEM_01f1 = 0x50;
  FUN_CODE_e0f2(0xff,0xf,0xc9,0xc,0x21);
  return;
}



/* === 0xc1d7 (size=838) === */

void FUN_CODE_c1d7(byte param_1)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  
  DAT_EXTMEM_019b = '\x01';
  FUN_CODE_df11();
  _1_0 = _0_3 & 1;
  _0_6 = _0_0 & 1;
  if ((_1_1 == '\x01') || (_0_0 != 0)) {
    FUN_CODE_c4cc();
  }
  else {
    FUN_CODE_c978();
  }
  FUN_CODE_bc17();
  FUN_CODE_d463();
  DAT_EXTMEM_e001 = DAT_EXTMEM_e001 & 0xfd;
  FUN_CODE_e1d7(0x80,0,200,0x2b,1);
  do {
    FUN_CODE_e2cd(200,0x44,1);
    if ((param_1 >> 6 & 1) == 0) {
      cVar2 = '\0';
    }
    else {
      cVar2 = -0x80;
    }
  } while (-1 < cVar2);
  bVar1 = 0;
  FUN_CODE_e2cd(200,0x47);
  DAT_EXTMEM_0222 = (bVar1 >> 1 & 1) != 0;
  DAT_EXTMEM_0220 = 0;
  DAT_EXTMEM_0221 = 0;
  DAT_EXTMEM_021f = 0;
  DAT_EXTMEM_0199 = 0xff;
  DAT_EXTMEM_019a = 0xff;
  FUN_CODE_dc92();
  bVar1 = 1;
  FUN_CODE_e03f(200,0xe4);
  if ((bVar1 >> 4 & 1) != 0) {
    DAT_EXTMEM_019b = '\x01';
    DAT_EXTMEM_965c = 0xff;
    DAT_EXTMEM_965d = DAT_EXTMEM_965d | 0x6f;
    DAT_EXTMEM_9641 = DAT_EXTMEM_9641 & 0xf3;
    while( true ) {
      bVar1 = 1;
      FUN_CODE_e03f(200,0xe4);
      if ((bVar1 >> 4 & 1) == 0) break;
      FUN_CODE_d655();
      FUN_CODE_da26();
    }
  }
  if (DAT_EXTMEM_019b == '\x01') {
    DAT_EXTMEM_965d = DAT_EXTMEM_965d & 0xbf;
    FUN_CODE_e3bd(DAT_EXTMEM_0225,3,0xe8);
    DAT_EXTMEM_965d = DAT_EXTMEM_965d & 0xfd;
    FUN_CODE_e3bd(DAT_EXTMEM_0225,3,0xe8);
    DAT_EXTMEM_965d = DAT_EXTMEM_965d & 0xfe;
    FUN_CODE_e3bd(DAT_EXTMEM_0225,3,0xe8);
    DAT_EXTMEM_965c = DAT_EXTMEM_965c & 0x7f;
    FUN_CODE_e3bd(DAT_EXTMEM_0225,3,0xe8);
    DAT_EXTMEM_965c = DAT_EXTMEM_965c & 0xbf;
    bVar1 = 0xe8;
    FUN_CODE_e3bd(DAT_EXTMEM_0225,3);
    DAT_EXTMEM_965c = DAT_EXTMEM_965c & 0xdf;
    DAT_EXTMEM_019b = '\0';
  }
  FUN_CODE_df11();
  if ((_1_0 == 0) || (_0_0 == 0)) {
    if ((_0_6 != 0) && (_0_3 != 0)) {
      DAT_EXTMEM_9542 = DAT_EXTMEM_9542 | 1;
      FUN_CODE_c978();
      FUN_CODE_d463();
      FUN_CODE_e334(0,0,0,0,7);
      FUN_CODE_e334(0,0,0,0x96,1);
      bVar1 = 7;
      FUN_CODE_e334(0,0,0,0x11);
      DAT_EXTMEM_9472 = DAT_EXTMEM_9472 | 2;
      DAT_EXTMEM_94a2 = 0;
      DAT_EXTMEM_94a3 = 0;
      DAT_EXTMEM_94c8 = 0;
      DAT_EXTMEM_94c9 = 0;
      DAT_EXTMEM_94e6 = DAT_EXTMEM_94e6 & 0xfb;
      DAT_EXTMEM_94e4 = DAT_EXTMEM_94e4 & 0xf7;
      DAT_EXTMEM_94e2 = 0;
      DAT_EXTMEM_94e3 = 0;
      DAT_EXTMEM_9542 = DAT_EXTMEM_9542 & 0xfe;
    }
  }
  else {
    DAT_EXTMEM_9542 = DAT_EXTMEM_9542 | 1;
    FUN_CODE_e3bd(DAT_EXTMEM_0225,0,2);
    DAT_EXTMEM_9542 = DAT_EXTMEM_9542 & 0xfe;
    FUN_CODE_c4cc();
    FUN_CODE_d463();
    bVar1 = 1;
    FUN_CODE_e334(0,2,0,0x96);
    if (DAT_EXTMEM_021b == '\0') {
      FUN_CODE_e334(2,0,0,0x11,7);
      bVar1 = 7;
      FUN_CODE_e334(0x10,0,0,0);
    }
  }
  _1_0 = _0_3 & 1;
  _0_6 = _0_0 & 1;
  FUN_CODE_d980();
  pbVar3 = &DAT_EXTMEM_0199;
  DAT_EXTMEM_019a = bVar1;
  if (DAT_EXTMEM_0199 == bVar1) {
    pbVar3 = &DAT_EXTMEM_019a;
    FUN_CODE_d1e9(bVar1);
  }
  else {
    FUN_CODE_d1e9(DAT_EXTMEM_0199);
  }
  *pbVar3 = *pbVar3 | 4;
  DAT_EXTMEM_965c = DAT_EXTMEM_965c | 0x7f;
  FUN_CODE_e218(0xfe,0xff,0x83,0x45,7);
  FUN_CODE_e13f(7,0x77,0xf0,0,0x82,0x14);
  FUN_CODE_e13f(2,0x22,0xf0,0,0x82,0x15);
  cVar2 = -0x7e;
  FUN_CODE_e13f(0x87,0,0x78,0x7f,0);
  FUN_CODE_e218(0x7f,0xff,0x82,0x1e,7);
  FUN_CODE_de1d();
  DAT_EXTMEM_019e = '\0';
  FUN_CODE_e18b();
LAB_CODE_c123:
  if (DAT_EXTMEM_019e != '\0') {
    DAT_EXTMEM_965d = DAT_EXTMEM_965d | 0xc;
    if (DAT_EXTMEM_0116 == '\x01') {
      FUN_CODE_e218(0xff,0xfe,0xcd,10,0x21);
      DAT_EXTMEM_0116 = '\0';
    }
    return;
  }
  FUN_CODE_acce();
  FUN_CODE_d655();
  FUN_CODE_da26();
  bVar1 = 1;
  FUN_CODE_e2cd(0xce,0x13);
  if ((bVar1 >> 1 & 1) != 1) {
    DAT_EXTMEM_01a3 = 0xc;
    bVar1 = 1;
    FUN_CODE_dc00(0xc,0xcc,0x37);
    if (bVar1 == 1 && cVar2 == '\0') {
      DAT_EXTMEM_01a3 = 7;
      bVar1 = 7;
      FUN_CODE_dc00(0xd,0x82,0x23);
      if (bVar1 == 0x20 && cVar2 == '\0') {
        FUN_CODE_e334(2,0x32,0x82,4,7);
        DAT_EXTMEM_01ef = 3;
        DAT_EXTMEM_01f0 = 0;
        DAT_EXTMEM_01f1 = 1;
        bVar1 = 7;
        FUN_CODE_d355(3,0x82,4);
      }
    }
  }
  FUN_CODE_d980();
  if (bVar1 == 6) goto code_c0xc199;
  goto LAB_CODE_c1a9;
code_c0xc199:
  bVar1 = 0;
  FUN_CODE_e03f(200,0xe4);
  if ((bVar1 >> 4 & 1) == 1) {
LAB_CODE_c1a9:
    DAT_EXTMEM_019e = '\x01';
  }
  goto LAB_CODE_c123;
}



/* === 0xbc17 (size=466) === */

void FUN_CODE_bc17(void)

{
  DAT_EXTMEM_021e = 0;
  DAT_EXTMEM_021c = 0x7f;
  DAT_EXTMEM_021d = 0xff;
  if ((_1_1 == '\x01') || (_0_0 != '\0')) {
    DAT_EXTMEM_01f0 = 2;
    DAT_EXTMEM_01f1 = 0;
    FUN_CODE_e0f2(0xf8,0x7f,0xca,2,1);
  }
  else {
    DAT_EXTMEM_01f0 = 0;
    DAT_EXTMEM_01f1 = 0x80;
    FUN_CODE_e0f2(0xf8,0x7f,0xca,2,1);
  }
  FUN_CODE_e334(0x47,0x40,200,0x8c,1);
  FUN_CODE_e334(0x80,8,200,0x8d,1);
  FUN_CODE_e1d7(0,0x20,199,0x40,1);
  FUN_CODE_e259(0,0x20,199,0x44);
  FUN_CODE_e259(0,0x20,199,0x48);
  FUN_CODE_e259(0,0x20,199,0x4c);
  DAT_EXTMEM_9643 = DAT_EXTMEM_9643 | 0x1e;
  DAT_EXTMEM_01f0 = 1;
  DAT_EXTMEM_01f1 = 0x1c;
  FUN_CODE_e0f2(0xf8,3,0xca,0x1d,1);
  FUN_CODE_e334(0,0,0x80,99,0x27);
  FUN_CODE_e392(0,1,0x80,0x62);
  FUN_CODE_e334(0,0,0xce,1,1);
  FUN_CODE_e392(0,0,0xce,2);
  FUN_CODE_e392(0,0,0xce,3);
  FUN_CODE_e392(0,0,0xce,4);
  FUN_CODE_e392(0,0,0xce,5);
  FUN_CODE_e392(0,0,0xce,0x13);
  FUN_CODE_e392(0,0,0xcd,0x13);
  FUN_CODE_e392(0,0x7f,0xcb,0x1c);
  FUN_CODE_e293(0xff,0xf3,0xcd,0x17);
  FUN_CODE_e293(0x9f,0xff,200,0x78);
  FUN_CODE_e259(0x70,0,200,0x7a);
  DAT_EXTMEM_01f5 = 0xc;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 5;
  FUN_CODE_cead(0x86,0x95,1,0xe);
  DAT_EXTMEM_01f5 = 9;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 5;
  FUN_CODE_cead(0x86,0x95,1,0xb);
  DAT_EXTMEM_01f5 = 6;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 4;
  FUN_CODE_cead(0x86,0x95,1,8);
  DAT_EXTMEM_01f5 = 0xc;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 6;
  FUN_CODE_cead(0x88,0x95,1,0xe);
  DAT_EXTMEM_01f5 = 9;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 6;
  FUN_CODE_cead(0x88,0x95,1,0xb);
  DAT_EXTMEM_01f5 = 6;
  DAT_EXTMEM_01f6 = 0;
  DAT_EXTMEM_01f7 = 4;
  FUN_CODE_cead(0x88,0x95,1,8);
  FUN_CODE_e218(0xff,0xfb,0x83,0,7);
  return;
}



/* === 0xd355 (size=270) === */

void FUN_CODE_d355(char param_1,undefined1 param_2,undefined1 param_3,byte param_4,byte param_5)

{
  char cVar1;
  byte bVar2;
  
  DAT_EXTMEM_01eb = param_5;
  DAT_EXTMEM_01ec = param_2;
  DAT_EXTMEM_01ed = param_3;
  DAT_EXTMEM_01ee = param_1;
  FUN_CODE_e2cd(param_2,param_3);
  DAT_EXTMEM_01f4 = 0;
  cVar1 = BANK0_R5 + '\x01';
  DAT_EXTMEM_01f5 = 1;
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01f4 = DAT_EXTMEM_01f4 << 1 | DAT_EXTMEM_01f5 >> 7;
    DAT_EXTMEM_01f5 = DAT_EXTMEM_01f5 << 1;
  }
  DAT_EXTMEM_01f2 = param_4;
  DAT_EXTMEM_01f3 = param_5;
  FUN_CODE_d196(500,0xff,DAT_EXTMEM_01ee + '\x01');
  cVar1 = BANK0_R5 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01f5 = DAT_EXTMEM_01f5 >> 1 | DAT_EXTMEM_01f4 << 7;
    DAT_EXTMEM_01f4 = DAT_EXTMEM_01f4 >> 1;
  }
  cVar1 = BANK0_R5 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01f4 = DAT_EXTMEM_01f4 << 1 | DAT_EXTMEM_01f5 >> 7;
    DAT_EXTMEM_01f5 = DAT_EXTMEM_01f5 << 1;
  }
  DAT_EXTMEM_01f7 = ~DAT_EXTMEM_01f5;
  DAT_EXTMEM_01f6 = ~DAT_EXTMEM_01f4;
  cVar1 = BANK0_R5 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    DAT_EXTMEM_01f0 = DAT_EXTMEM_01f0 << 1 | DAT_EXTMEM_01f1 >> 7;
    DAT_EXTMEM_01f1 = DAT_EXTMEM_01f1 << 1;
  }
  bVar2 = DAT_EXTMEM_01f3 & DAT_EXTMEM_01f7;
  DAT_EXTMEM_01f3 = bVar2 + (DAT_EXTMEM_01f1 & DAT_EXTMEM_01f5);
  DAT_EXTMEM_01f2 =
       (DAT_EXTMEM_01f2 & DAT_EXTMEM_01f6) +
       ((DAT_EXTMEM_01f0 & DAT_EXTMEM_01f4) -
       ((CARRY1(bVar2,DAT_EXTMEM_01f1 & DAT_EXTMEM_01f5) << 7) >> 7));
  FUN_CODE_e334(DAT_EXTMEM_01f2,DAT_EXTMEM_01f3,DAT_EXTMEM_01ec,DAT_EXTMEM_01ed,DAT_EXTMEM_01eb);
  return;
}



/* === 0xd463 (size=256) === */

void FUN_CODE_d463(void)

{
  byte bVar1;
  
  if (_1_1 == '\0') {
    FUN_CODE_e218(0xff,0xbf,0x81,0xc,7);
  }
  else {
    FUN_CODE_e1d7(0,0x40,0x81,0xc,7);
  }
  DAT_EXTMEM_021b = 0;
  if ((_0_0 == '\x01') || (_0_2 != '\0')) {
    bVar1 = 0;
    FUN_CODE_e2cd(199,0x20);
    DAT_EXTMEM_021b = (bVar1 & 0x30) >> 4;
    if (DAT_EXTMEM_021b != 0) {
      FUN_CODE_e259(0,8,0xcd,0x16);
    }
    bVar1 = 0;
    FUN_CODE_e2cd(199,0x10);
    if ((bVar1 >> 1 & 1) != 1) {
      FUN_CODE_e392(0,8,199,0);
    }
  }
  else {
    FUN_CODE_e218(0xff,0xf7,0xcd,0x16,1);
  }
  FUN_CODE_e1d7(4,0,200,0x40,1);
  if (_0_3 != '\0') {
    DAT_EXTMEM_9434 = 0x44;
    FUN_CODE_e1d7(1,0,200,0x40,1);
  }
  if (_0_4 == '\0') {
    FUN_CODE_e334(0,1,200,0x4b,1);
  }
  else {
    FUN_CODE_e334(0,0,200,0x4b,1);
    FUN_CODE_e259(0,1,199,0x50);
    FUN_CODE_e334(0x55,8,0xc9,10,0x21);
    FUN_CODE_e392(0x88,0,0xc9,0xb);
    FUN_CODE_e392(0x1b,0xd0,0xc9,0xc);
  }
  FUN_CODE_e392(0,0,0xce,4);
  FUN_CODE_e392(0,0,0xce,5);
  return;
}



/* === 0xe301 (size=51) === */

void FUN_CODE_e301(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  
  cVar1 = DAT_SFR_ab;
  if (cVar1 == '\0') {
    uVar3 = 0xd;
    uVar2 = 0x60;
    FUN_CODE_e3fd();
    DAT_EXTMEM_9438 = uVar2;
    DAT_EXTMEM_9439 = uVar3;
    return;
  }
  DAT_EXTMEM_9438 = DAT_SFR_ab;
  DAT_EXTMEM_9439 = bCODEfffe ^ bCODEffff;
  return;
}



/* === 0xbe00 (size=5) === */

void FUN_CODE_be00(void)

{
  HIFLG_0 = 1;
  EA = 1;
  return;
}



/* === 0xe2cd (size=52) === */

undefined1 FUN_CODE_e2cd(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  
  DAT_EXTMEM_01f8 = param_3;
  DAT_EXTMEM_01f9 = param_1;
  DAT_EXTMEM_01fa = param_2;
  HIE = param_3;
  FIE1 = param_1;
  FIE = param_2;
  P2 = 0;
  do {
    cVar1 = P2_0;
  } while (cVar1 == '\x01');
  DAT_EXTMEM_01fb = WCON;
  DAT_EXTMEM_01fc = WDTRST;
  return DAT_EXTMEM_01fc;
}



/* === 0xe3fd (size=28) === */

undefined1 FUN_CODE_e3fd(undefined1 param_1,undefined1 param_2)

{
  DAT_EXTMEM_0199 = param_1;
  DAT_EXTMEM_019a = param_2;
  DAT_EXTMEM_019b = param_2;
  DAT_EXTMEM_019c = param_1;
  return param_1;
}



