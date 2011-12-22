/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),
                             zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2010  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2010  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2010  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2010  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/

#include <math.h>
#include "snes9x.h"
#include "memmap.h"
#include "seta.h"

uint8	(*GetSETA) (uint32)        = &S9xGetST010;
void	(*SetSETA) (uint32, uint8) = &S9xSetST010;


uint8 S9xGetSetaDSP (uint32 Address)
{
	return (GetSETA(Address));
}

void S9xSetSetaDSP (uint8 Byte, uint32 Address)
{
	SetSETA (Address, Byte);
}

/***********************************************************************************
 Seta 010
***********************************************************************************/

static const int16	ST010_SinTable[256] =
{
	 0x0000,  0x0324,  0x0648,  0x096a,  0x0c8c,  0x0fab,  0x12c8,  0x15e2,
	 0x18f9,  0x1c0b,  0x1f1a,  0x2223,  0x2528,  0x2826,  0x2b1f,  0x2e11,
	 0x30fb,  0x33df,  0x36ba,  0x398c,  0x3c56,  0x3f17,  0x41ce,  0x447a,
	 0x471c,  0x49b4,  0x4c3f,  0x4ebf,  0x5133,  0x539b,  0x55f5,  0x5842,
	 0x5a82,  0x5cb3,  0x5ed7,  0x60eb,  0x62f1,  0x64e8,  0x66cf,  0x68a6,
	 0x6a6d,  0x6c23,  0x6dc9,  0x6f5e,  0x70e2,  0x7254,  0x73b5,  0x7504,
	 0x7641,  0x776b,  0x7884,  0x7989,  0x7a7c,  0x7b5c,  0x7c29,  0x7ce3,
	 0x7d89,  0x7e1d,  0x7e9c,  0x7f09,  0x7f61,  0x7fa6,  0x7fd8,  0x7ff5,
	 0x7fff,  0x7ff5,  0x7fd8,  0x7fa6,  0x7f61,  0x7f09,  0x7e9c,  0x7e1d,
	 0x7d89,  0x7ce3,  0x7c29,  0x7b5c,  0x7a7c,  0x7989,  0x7884,  0x776b,
	 0x7641,  0x7504,  0x73b5,  0x7254,  0x70e2,  0x6f5e,  0x6dc9,  0x6c23,
	 0x6a6d,  0x68a6,  0x66cf,  0x64e8,  0x62f1,  0x60eb,  0x5ed7,  0x5cb3,
	 0x5a82,  0x5842,  0x55f5,  0x539b,  0x5133,  0x4ebf,  0x4c3f,  0x49b4,
	 0x471c,  0x447a,  0x41ce,  0x3f17,  0x3c56,  0x398c,  0x36ba,  0x33df,
	 0x30fb,  0x2e11,  0x2b1f,  0x2826,  0x2528,  0x2223,  0x1f1a,  0x1c0b,
	 0x18f8,  0x15e2,  0x12c8,  0x0fab,  0x0c8c,  0x096a,  0x0648,  0x0324,
	 0x0000, -0x0324, -0x0648, -0x096b, -0x0c8c, -0x0fab, -0x12c8, -0x15e2,
	-0x18f9, -0x1c0b, -0x1f1a, -0x2223, -0x2528, -0x2826, -0x2b1f, -0x2e11,
	-0x30fb, -0x33df, -0x36ba, -0x398d, -0x3c56, -0x3f17, -0x41ce, -0x447a,
	-0x471c, -0x49b4, -0x4c3f, -0x4ebf, -0x5133, -0x539b, -0x55f5, -0x5842,
	-0x5a82, -0x5cb3, -0x5ed7, -0x60ec, -0x62f1, -0x64e8, -0x66cf, -0x68a6,
	-0x6a6d, -0x6c23, -0x6dc9, -0x6f5e, -0x70e2, -0x7254, -0x73b5, -0x7504,
	-0x7641, -0x776b, -0x7884, -0x7989, -0x7a7c, -0x7b5c, -0x7c29, -0x7ce3,
	-0x7d89, -0x7e1d, -0x7e9c, -0x7f09, -0x7f61, -0x7fa6, -0x7fd8, -0x7ff5,
	-0x7fff, -0x7ff5, -0x7fd8, -0x7fa6, -0x7f61, -0x7f09, -0x7e9c, -0x7e1d,
	-0x7d89, -0x7ce3, -0x7c29, -0x7b5c, -0x7a7c, -0x7989, -0x7883, -0x776b,
	-0x7641, -0x7504, -0x73b5, -0x7254, -0x70e2, -0x6f5e, -0x6dc9, -0x6c23,
	-0x6a6d, -0x68a6, -0x66cf, -0x64e8, -0x62f1, -0x60eb, -0x5ed7, -0x5cb3,
	-0x5a82, -0x5842, -0x55f5, -0x539a, -0x5133, -0x4ebf, -0x4c3f, -0x49b3,
	-0x471c, -0x447a, -0x41cd, -0x3f17, -0x3c56, -0x398c, -0x36b9, -0x33de,
	-0x30fb, -0x2e10, -0x2b1f, -0x2826, -0x2527, -0x2223, -0x1f19, -0x1c0b,
	-0x18f8, -0x15e2, -0x12c8, -0x0fab, -0x0c8b, -0x096a, -0x0647, -0x0324
};

static const uint8	ST010_ArcTan[32][32] =
{
	{ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },
	{ 0x80, 0xa0, 0xad, 0xb3, 0xb6, 0xb8, 0xb9, 0xba, 0xbb, 0xbb, 0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd,
	  0xbd, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf },
	{ 0x80, 0x93, 0xa0, 0xa8, 0xad, 0xb0, 0xb3, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xb9, 0xba, 0xba, 0xbb,
	  0xbb, 0xbb, 0xbb, 0xbc, 0xbc, 0xbc, 0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd },
	{ 0x80, 0x8d, 0x98, 0xa0, 0xa6, 0xaa, 0xad, 0xb0, 0xb1, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb7, 0xb8,
	  0xb8, 0xb9, 0xb9, 0xba, 0xba, 0xba, 0xba, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbc, 0xbc, 0xbc, 0xbc },
	{ 0x80, 0x8a, 0x93, 0x9a, 0xa0, 0xa5, 0xa8, 0xab, 0xad, 0xaf, 0xb0, 0xb2, 0xb3, 0xb4, 0xb5, 0xb5,
	  0xb6, 0xb7, 0xb7, 0xb8, 0xb8, 0xb8, 0xb9, 0xb9, 0xb9, 0xba, 0xba, 0xba, 0xba, 0xba, 0xbb, 0xbb },
	{ 0x80, 0x88, 0x90, 0x96, 0x9b, 0xa0, 0xa4, 0xa7, 0xa9, 0xab, 0xad, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3,
	  0xb4, 0xb4, 0xb5, 0xb6, 0xb6, 0xb6, 0xb7, 0xb7, 0xb8, 0xb8, 0xb8, 0xb9, 0xb9, 0xb9, 0xb9, 0xb9 },
	{ 0x80, 0x87, 0x8d, 0x93, 0x98, 0x9c, 0xa0, 0xa3, 0xa6, 0xa8, 0xaa, 0xac, 0xad, 0xae, 0xb0, 0xb0,
	  0xb1, 0xb2, 0xb3, 0xb4, 0xb4, 0xb5, 0xb5, 0xb6, 0xb6, 0xb6, 0xb7, 0xb7, 0xb7, 0xb8, 0xb8, 0xb8 },
	{ 0x80, 0x86, 0x8b, 0x90, 0x95, 0x99, 0x9d, 0xa0, 0xa3, 0xa5, 0xa7, 0xa9, 0xaa, 0xac, 0xad, 0xae,
	  0xaf, 0xb0, 0xb1, 0xb2, 0xb2, 0xb3, 0xb3, 0xb4, 0xb4, 0xb5, 0xb5, 0xb6, 0xb6, 0xb6, 0xb7, 0xb7 },
	{ 0x80, 0x85, 0x8a, 0x8f, 0x93, 0x97, 0x9a, 0x9d, 0xa0, 0xa2, 0xa5, 0xa6, 0xa8, 0xaa, 0xab, 0xac,
	  0xad, 0xae, 0xaf, 0xb0, 0xb0, 0xb1, 0xb2, 0xb2, 0xb3, 0xb3, 0xb4, 0xb4, 0xb5, 0xb5, 0xb5, 0xb5 },
	{ 0x80, 0x85, 0x89, 0x8d, 0x91, 0x95, 0x98, 0x9b, 0x9e, 0xa0, 0xa0, 0xa4, 0xa6, 0xa7, 0xa9, 0xaa,
	  0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb0, 0xb1, 0xb1, 0xb2, 0xb2, 0xb3, 0xb3, 0xb4, 0xb4, 0xb4 },
	{ 0x80, 0x84, 0x88, 0x8c, 0x90, 0x93, 0x96, 0x99, 0x9b, 0x9e, 0xa0, 0xa2, 0xa4, 0xa5, 0xa7, 0xa8,
	  0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xaf, 0xb0, 0xb0, 0xb1, 0xb2, 0xb2, 0xb2, 0xb3, 0xb3 },
	{ 0x80, 0x84, 0x87, 0x8b, 0x8e, 0x91, 0x94, 0x97, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa3, 0xa5, 0xa6,
	  0xa7, 0xa9, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xae, 0xae, 0xaf, 0xb0, 0xb0, 0xb1, 0xb1, 0xb2, 0xb2 },
	{ 0x80, 0x83, 0x87, 0x8a, 0x8d, 0x90, 0x93, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa3, 0xa5,
	  0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xae, 0xae, 0xaf, 0xb0, 0xb0, 0xb0, 0xb1 },
	{ 0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x94, 0x96, 0x99, 0x9b, 0x9d, 0x9e, 0xa0, 0xa2, 0xa3,
	  0xa4, 0xa5, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xae, 0xae, 0xaf, 0xaf, 0xb0 },
	{ 0x80, 0x83, 0x86, 0x89, 0x8b, 0x8e, 0x90, 0x93, 0x95, 0x97, 0x99, 0x9b, 0x9d, 0x9e, 0xa0, 0xa1,
	  0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xaa, 0xab, 0xac, 0xad, 0xad, 0xae, 0xae, 0xaf },
	{ 0x80, 0x83, 0x85, 0x88, 0x8b, 0x8d, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9b, 0x9d, 0x9f, 0xa0,
	  0xa1, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa8, 0xa9, 0xaa, 0xab, 0xab, 0xac, 0xad, 0xad, 0xae },
	{ 0x80, 0x83, 0x85, 0x88, 0x8a, 0x8c, 0x8f, 0x91, 0x93, 0x95, 0x97, 0x99, 0x9a, 0x9c, 0x9d, 0x9f,
	  0xa0, 0xa1, 0xa2, 0xa3, 0xa5, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xaa, 0xab, 0xab, 0xac, 0xad },
	{ 0x80, 0x82, 0x85, 0x87, 0x89, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x97, 0x99, 0x9b, 0x9c, 0x9d,
	  0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa8, 0xa9, 0xaa, 0xaa, 0xab, 0xac },
	{ 0x80, 0x82, 0x85, 0x87, 0x89, 0x8b, 0x8d, 0x8f, 0x91, 0x93, 0x95, 0x96, 0x98, 0x99, 0x9b, 0x9c,
	  0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab },
	{ 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x95, 0x97, 0x98, 0x9a, 0x9b,
	  0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa8, 0xa9, 0xaa },
	{ 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x91, 0x93, 0x94, 0x96, 0x97, 0x99, 0x9a,
	  0x9b, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa5, 0xa6, 0xa7, 0xa7, 0xa8, 0xa9 },
	{ 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8b, 0x8d, 0x8f, 0x90, 0x92, 0x94, 0x95, 0x97, 0x98, 0x99,
	  0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8 },
	{ 0x80, 0x82, 0x84, 0x86, 0x87, 0x89, 0x8b, 0x8d, 0x8e, 0x90, 0x91, 0x93, 0x94, 0x96, 0x97, 0x98,
	  0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa3, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7 },
	{ 0x80, 0x82, 0x84, 0x85, 0x87, 0x89, 0x8a, 0x8c, 0x8e, 0x8f, 0x91, 0x92, 0x94, 0x95, 0x96, 0x98,
	  0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa2, 0xa3, 0xa4, 0xa5, 0xa5, 0xa6 },
	{ 0x80, 0x82, 0x83, 0x85, 0x87, 0x88, 0x8a, 0x8c, 0x8d, 0x8f, 0x90, 0x92, 0x93, 0x94, 0x96, 0x97,
	  0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa2, 0xa3, 0xa4, 0xa5, 0xa5 },
	{ 0x80, 0x82, 0x83, 0x85, 0x86, 0x88, 0x8a, 0x8b, 0x8d, 0x8e, 0x90, 0x91, 0x92, 0x94, 0x95, 0x96,
	  0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa2, 0xa3, 0xa4, 0xa4 },
	{ 0x80, 0x82, 0x83, 0x85, 0x86, 0x88, 0x89, 0x8b, 0x8c, 0x8e, 0x8f, 0x90, 0x92, 0x93, 0x94, 0x95,
	  0x96, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa2, 0xa3, 0xa4 },
	{ 0x80, 0x82, 0x83, 0x85, 0x86, 0x87, 0x89, 0x8a, 0x8c, 0x8d, 0x8e, 0x90, 0x91, 0x92, 0x93, 0x95,
	  0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9e, 0x9f, 0xa0, 0xa1, 0xa1, 0xa2, 0xa3 },
	{ 0x80, 0x81, 0x83, 0x84, 0x86, 0x87, 0x89, 0x8a, 0x8b, 0x8d, 0x8e, 0x8f, 0x90, 0x92, 0x93, 0x94,
	  0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9e, 0x9f, 0xa0, 0xa1, 0xa1, 0xa2 },
	{ 0x80, 0x81, 0x83, 0x84, 0x86, 0x87, 0x88, 0x8a, 0x8b, 0x8c, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93,
	  0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0, 0xa1, 0xa1 },
	{ 0x80, 0x81, 0x83, 0x84, 0x85, 0x87, 0x88, 0x89, 0x8b, 0x8c, 0x8d, 0x8e, 0x90, 0x91, 0x92, 0x93,
	  0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0, 0xa1 },
	{ 0x80, 0x81, 0x83, 0x84, 0x85, 0x87, 0x88, 0x89, 0x8a, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92,
	  0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0 }
};

// Mode 7 scaling constants for all raster lines
static const int16	ST010_M7Scale[176] =
{
	0x0380, 0x0325, 0x02da, 0x029c, 0x0268, 0x023b, 0x0215, 0x01f3,
	0x01d5, 0x01bb, 0x01a3, 0x018e, 0x017b, 0x016a, 0x015a, 0x014b,
	0x013e, 0x0132, 0x0126, 0x011c, 0x0112, 0x0109, 0x0100, 0x00f8,
	0x00f0, 0x00e9, 0x00e3, 0x00dc, 0x00d6, 0x00d1, 0x00cb, 0x00c6,
	0x00c1, 0x00bd, 0x00b8, 0x00b4, 0x00b0, 0x00ac, 0x00a8, 0x00a5,
	0x00a2, 0x009e, 0x009b, 0x0098, 0x0095, 0x0093, 0x0090, 0x008d,
	0x008b, 0x0088, 0x0086, 0x0084, 0x0082, 0x0080, 0x007e, 0x007c,
	0x007a, 0x0078, 0x0076, 0x0074, 0x0073, 0x0071, 0x006f, 0x006e,
	0x006c, 0x006b, 0x0069, 0x0068, 0x0067, 0x0065, 0x0064, 0x0063,
	0x0062, 0x0060, 0x005f, 0x005e, 0x005d, 0x005c, 0x005b, 0x005a,
	0x0059, 0x0058, 0x0057, 0x0056, 0x0055, 0x0054, 0x0053, 0x0052,
	0x0051, 0x0051, 0x0050, 0x004f, 0x004e, 0x004d, 0x004d, 0x004c,
	0x004b, 0x004b, 0x004a, 0x0049, 0x0048, 0x0048, 0x0047, 0x0047,
	0x0046, 0x0045, 0x0045, 0x0044, 0x0044, 0x0043, 0x0042, 0x0042,
	0x0041, 0x0041, 0x0040, 0x0040, 0x003f, 0x003f, 0x003e, 0x003e,
	0x003d, 0x003d, 0x003c, 0x003c, 0x003b, 0x003b, 0x003a, 0x003a,
	0x003a, 0x0039, 0x0039, 0x0038, 0x0038, 0x0038, 0x0037, 0x0037,
	0x0036, 0x0036, 0x0036, 0x0035, 0x0035, 0x0035, 0x0034, 0x0034,
	0x0034, 0x0033, 0x0033, 0x0033, 0x0032, 0x0032, 0x0032, 0x0031,
	0x0031, 0x0031, 0x0030, 0x0030, 0x0030, 0x0030, 0x002f, 0x002f,
	0x002f, 0x002e, 0x002e, 0x002e, 0x002e, 0x002d, 0x002d, 0x002d,
	0x002d, 0x002c, 0x002c, 0x002c, 0x002c, 0x002b, 0x002b, 0x002b
};

#ifndef PI
#define PI	3.1415926535897932384626433832795
#endif

#define ST010_WORD(offset)	(Memory.SRAM[offset + 1] << 8) | Memory.SRAM[offset]

static int16 ST010_Sin (int16 Theta)
{
	return (ST010_SinTable[(Theta >> 8) & 0xff]);
}

static int16 ST010_Cos (int16 Theta)
{
	return (ST010_SinTable[((Theta + 0x4000) >> 8) & 0xff]);
}

static void ST010_OP01 (int16 x0, int16 y0, int16 * x1, int16 * y1, int16 * Quadrant, int16 * Theta)
{
	if ((x0 < 0) && (y0 < 0))
	{
		*x1 = -x0;
		*y1 = -y0;
		*Quadrant = -0x8000;
	}
	else
	if (x0 < 0)
	{
		*x1 =  y0;
		*y1 = -x0;
		*Quadrant = -0x4000;
	}
	else
	if (y0 < 0)
	{
		*x1 = -y0;
		*y1 =  x0;
		*Quadrant =  0x4000;
	}
	else
	{
		*x1 =  x0;
		*y1 =  y0;
		*Quadrant =  0x0000;
	}

	while ((*x1 > 0x1f) || (*y1 > 0x1f))
	{
		if (*x1 > 1)
			*x1 >>= 1;
		if (*y1 > 1)
			*y1 >>= 1;
	}

	if (*y1 == 0)
		*Quadrant += 0x4000;

	*Theta = (ST010_ArcTan[*y1][*x1] << 8) ^ *Quadrant;
}

static void ST010_Scale (int16 Multiplier, int16 X0, int16 Y0, int32 *X1, int32 * Y1)
{
	*X1 = X0 * Multiplier << 1;
	*Y1 = Y0 * Multiplier << 1;
}

static void ST010_Multiply (int16 Multiplicand, int16 Multiplier, int32 * Product)
{
	*Product = Multiplicand * Multiplier << 1;
}

static void ST010_Rotate (int16 Theta, int16 X0, int16 Y0, int16 * X1, int16 * Y1)
{
	*X1 = (Y0 * ST010_Sin(Theta) >> 15) + (X0 * ST010_Cos(Theta) >> 15);
	*Y1 = (Y0 * ST010_Cos(Theta) >> 15) - (X0 * ST010_Sin(Theta) >> 15);
}

static void ST010_SortDrivers (uint16 Positions, uint16 Places[32], uint16 Drivers[32])
{
	bool	Sorted;
	uint16	Temp;

	if (Positions > 1)
	{
		do
		{
			Sorted = true;

			for (int i = 0; i < Positions - 1; i++)
			{
				if (Places[i] < Places[i + 1])
				{
					Temp = Places[i + 1];
					Places[i + 1] = Places[i];
					Places[i] = Temp;

					Temp = Drivers[i + 1];
					Drivers[i + 1] = Drivers[i];
					Drivers[i] = Temp;

					Sorted = false;
				}
			}

			Positions--;
		}
		while (!Sorted);
	}
}

/*
static void SETA_Distance (int16 Y0, int16 X0, int16 &Distance)
{
	if (X0 < 0)
		X0 = -X0;
	if (Y0 < 0)
		Y0 = -Y0;

	Distance = ((X0 * 0x7af0) + 0x4000) >> 15;
}
*/

uint8 S9xGetST010 (uint32 Address)
{
	if (!(Address & 0x80000))
		return (0x80);

	if ((Address & 0xFFF) == 0x20)
		return (ST010.op_reg);

	if ((Address & 0xFFF) == 0x21)
		return (ST010.execute);

	return (Memory.SRAM[Address & Memory.SRAMMask]);
}

void S9xSetST010 (uint32 Address, uint8 Byte)
{
	if (!(Address & 0x80000))
	{
		ST010.control_enable = TRUE;
		return;
	}


	if ((Address & 0xFFF) == 0x20 && ST010.control_enable)
		ST010.op_reg = Byte;

	if ((Address & 0xFFF) == 0x21 && ST010.control_enable)
		ST010.execute = Byte;
	else
		Memory.SRAM[Address & Memory.SRAMMask] = Byte;

	if (ST010.execute & 0x80)
	{
		switch (ST010.op_reg)
		{
			// Sorts Driver Placements
			//
			// Input
			//   0x0024-0x0025 : Positions
			//   0x0040-0x007f : Places
			//   0x0080-0x00ff : Drivers
			// Output
			//   0x0040-0x007f : Places
			//   0x0080-0x00ff : Drivers
			//
			case 0x02:
			{
			#ifdef FAST_LSB_WORD_ACCESS
				ST010_SortDrivers(*(uint16 *) (Memory.SRAM + 0x0024), (uint16 *) (Memory.SRAM + 0x0040), (uint16 *) (Memory.SRAM + 0x0080));
			#else
				uint16	Places[32];
				uint16	Positions = ST010_WORD(0x0024);
				int		Pos, Offset;

				Offset = 0;

				for (Pos = 0; Pos < Positions; Pos++)
				{
					Places[Pos] = ST010_WORD(0x0040 + Offset);
					Offset += 2;
				}

				ST010_SortDrivers(Positions, Places, (uint16 *) (Memory.SRAM + 0x0080));

				Offset = 0;

				for (Pos = 0; Pos < Positions; Pos++)
				{
					Memory.SRAM[0x0040 + Offset] = (uint8) (Places[Pos]);
					Memory.SRAM[0x0041 + Offset] = (uint8) (Places[Pos] >> 8);
					Offset += 2;
				}
			#endif
				break;
			}

			// Two Dimensional Coordinate Scale
			//
			// Input
			//   0x0000-0x0001 : X0 (signed)
			//   0x0002-0x0003 : Y0 (signed)
			//   0x0004-0x0005 : Multiplier (signed)
			// Output
			//   0x0010-0x0013 : X1 (signed)
			//   0x0014-0x0017 : Y1 (signed)
			//
			case 0x03:
			{
			#ifdef FAST_LSB_WORD_ACCESS
				ST010_Scale(*(int16 *) &Memory.SRAM[0x0004], *(int16 *) &Memory.SRAM[0x0000], *(int16 *) &Memory.SRAM[0x0002], (int32 *) Memory.SRAM[0x0010], (int32 *) Memory.SRAM[0x0014]);
			#else
				int32	x1, y1;

				ST010_Scale(ST010_WORD(0x0004), ST010_WORD(0x0000), ST010_WORD(0x0002), &x1, &y1);

				Memory.SRAM[0x0010] = (uint8) (x1);
				Memory.SRAM[0x0011] = (uint8) (x1 >> 8);
				Memory.SRAM[0x0012] = (uint8) (x1 >> 16);
				Memory.SRAM[0x0013] = (uint8) (x1 >> 24);
				Memory.SRAM[0x0014] = (uint8) (y1);
				Memory.SRAM[0x0015] = (uint8) (y1 >> 8);
				Memory.SRAM[0x0016] = (uint8) (y1 >> 16);
				Memory.SRAM[0x0017] = (uint8) (y1 >> 24);
			#endif
				break;
			}

			// 16-bit Multiplication
			//
			// Input
			//   0x0000-0x0001 : Multiplcand (signed)
			//   0x0002-0x0003 : Multiplier (signed)
			// Output
			//   0x0010-0x0013 : Product (signed)
			//
			case 0x06:
			{
			#ifdef FAST_LSB_WORD_ACCESS
				ST010_Multiply(*(int16 *) &Memory.SRAM[0x0000], *(int16 *) &Memory.SRAM[0x0002], (int32 *) Memory.SRAM[0x0010]);
			#else
				int32	Product;

				ST010_Multiply(ST010_WORD(0x0000), ST010_WORD(0x0002), &Product);

				Memory.SRAM[0x0010] = (uint8) (Product);
				Memory.SRAM[0x0011] = (uint8) (Product >> 8);
				Memory.SRAM[0x0012] = (uint8) (Product >> 16);
				Memory.SRAM[0x0013] = (uint8) (Product >> 24);
			#endif
				break;
			}

			// Mode 7 Raster Data Calculation
			//
			// Input
			//   0x0000-0x0001 : Angle (signed)
			// Output
			//   0x00f0-0x024f : Mode 7 Matrix A
			//   0x0250-0x03af : Mode 7 Matrix B
			//   0x03b0-0x050f : Mode 7 Matrix C
			//   0x0510-0x066f : Mode 7 Matrix D
			//
			case 0x07:
			{
				int16	data;
				int32	offset = 0;
				int16	Theta = ST010_WORD(0x0000);

				for (int32 line = 0; line < 176; line++)
				{
					// Calculate Mode 7 Matrix A/D data
					data = ST010_M7Scale[line] * ST010_Cos(Theta) >> 15;

					Memory.SRAM[0x00f0 + offset] = (uint8) (data);
					Memory.SRAM[0x00f1 + offset] = (uint8) (data >> 8);
					Memory.SRAM[0x0510 + offset] = (uint8) (data);
					Memory.SRAM[0x0511 + offset] = (uint8) (data >> 8);

					// Calculate Mode 7 Matrix B/C data
					data = ST010_M7Scale[line] * ST010_Sin(Theta) >> 15;

					Memory.SRAM[0x0250 + offset] = (uint8) (data);
					Memory.SRAM[0x0251 + offset] = (uint8) (data >> 8);

					if (data)
						data = ~data;

					Memory.SRAM[0x03b0 + offset] = (uint8) (data);
					Memory.SRAM[0x03b1 + offset] = (uint8) (data >> 8);

					offset += 2;
				}

				// Shift Angle for use with Lookup table
				Memory.SRAM[0x00] = Memory.SRAM[0x01];
				Memory.SRAM[0x01] = 0x00;

				break;
			}

			// Two dimensional Coordinate Rotation
			//
			// Input
			//   0x0000-0x0001 : X0 (signed)
			//   0x0002-0x0003 : Y0 (signed)
			//   0x0004-0x0005 : Angle (signed)
			// Output
			//   0x0010-0x0011 : X1 (signed)
			//   0x0012-0x0013 : Y1 (signed)
			//
			case 0x08:
			{
			#ifdef FAST_LSB_WORD_ACCESS
				ST010_Rotate(*(int16 *) &Memory.SRAM[0x0004], *(int16 *) &Memory.SRAM[0x0000], *(int16 *) &Memory.SRAM[0x0002], (int16 *) Memory.SRAM[0x0010], (int16 *) Memory.SRAM[0x0012]);
			#else
				int16	x1, y1;

				ST010_Rotate(ST010_WORD(0x0004), ST010_WORD(0x0000), ST010_WORD(0x0002), &x1, &y1);

				Memory.SRAM[0x0010] = (uint8) (x1);
				Memory.SRAM[0x0011] = (uint8) (x1 >> 8);
				Memory.SRAM[0x0012] = (uint8) (y1);
				Memory.SRAM[0x0013] = (uint8) (y1 >> 8);
			#endif
				break;
			}

			// Input
			//   0x0000-0x0001 : DX (signed)
			//   0x0002-0x0003 : DY (signed)
			// Output
			//   0x0010-0x0011 : Angle (signed)
			//
			case 0x01:
			{
				Memory.SRAM[0x0006] = Memory.SRAM[0x0002];
				Memory.SRAM[0x0007] = Memory.SRAM[0x0003];

			#ifdef FAST_LSB_WORD_ACCESS
				ST010_OP01(*(int16 *) &Memory.SRAM[0x0000], *(int16 *) &Memory.SRAM[0x0002], (int16 *)Memory.SRAM[0x0000], (int16 *) Memory.SRAM[0x0002], (int16 *) Memory.SRAM[0x0004], (int16 *) Memory.SRAM[0x0010]);
			#else
				int16	x1, y1, Quadrant, Theta;

				ST010_OP01(ST010_WORD(0x0000), ST010_WORD(0x0002), &x1, &y1, &Quadrant, &Theta);

				Memory.SRAM[0x0000] = (uint8) (x1);
				Memory.SRAM[0x0001] = (uint8) (x1 >> 8);
				Memory.SRAM[0x0002] = (uint8) (y1);
				Memory.SRAM[0x0003] = (uint8) (y1 >> 8);
				Memory.SRAM[0x0004] = (uint8) (Quadrant);
				Memory.SRAM[0x0005] = (uint8) (Quadrant >> 8);
				Memory.SRAM[0x0010] = (uint8) (Theta);
				Memory.SRAM[0x0011] = (uint8) (Theta >> 8);
			#endif
				break;
			}

			// calculate the vector length of (x, y)
			case 0x04:
			{
				int16	square, x, y;
			#ifdef FAST_LSB_WORD_ACCESS
				x = *((int16 *) Memory.SRAM);
				y = *((int16 *) &Memory.SRAM[2]);
			#else
				x = Memory.SRAM[0] | (Memory.SRAM[1] << 8);
				y = Memory.SRAM[2] | (Memory.SRAM[3] << 8);
			#endif
				square = (int16) sqrt((double) (y * y + x * x));
				//SETA_Distance(x, y, square);

			#ifdef FAST_LSB_WORD_ACCESS
				*((int16 *) &Memory.SRAM[0x10]) = square;
			#else
				Memory.SRAM[0x10] = (uint8) (square);
				Memory.SRAM[0x11] = (uint8) (square >> 8);
			#endif
				break;
			}

			// calculate AI orientation based on specific guidelines
			case 0x05:
			{
				int32	dx, dy;
				int16	a1, b1, c1;
				uint16	o1;
				bool	wrap = false;

				// target (x, y) coordinates
				int16	ypos_max  = ST010_WORD(0x00C0);
				int16	xpos_max  = ST010_WORD(0x00C2);

				// current coordinates and direction
				int32	ypos = Memory.SRAM[0xC4] | (Memory.SRAM[0xC5] << 8) | (Memory.SRAM[0xC6] << 16) | (Memory.SRAM[0xC7] << 24);
				int32	xpos = Memory.SRAM[0xC8] | (Memory.SRAM[0xC9] << 8) | (Memory.SRAM[0xCA] << 16) | (Memory.SRAM[0xCB] << 24);
				uint16	rot  = Memory.SRAM[0xCC] | (Memory.SRAM[0xCD] << 8);

				// physics
				uint16	speed     = ST010_WORD(0x00D4);
				uint16	accel     = ST010_WORD(0x00D6);
				uint16	speed_max = ST010_WORD(0x00D8);

				// special condition acknowledgment
				int16	system    = ST010_WORD(0x00DA);
				int16	flags     = ST010_WORD(0x00DC);

				// new target coordinates
				int16	ypos_new  = ST010_WORD(0x00DE);
				int16	xpos_new  = ST010_WORD(0x00E0);

				// mask upper bit
				xpos_new &= 0x7FFF;

				// get the current distance
				dx = xpos_max - (xpos >> 16);
				dy = ypos_max - (ypos >> 16);

				// quirk: clear and move in9
				Memory.SRAM[0xD2] = 0xFF;
				Memory.SRAM[0xD3] = 0xFF;
				Memory.SRAM[0xDA] = 0;
				Memory.SRAM[0xDB] = 0;

				// grab the target angle
				ST010_OP01(dy, dx, &a1, &b1, &c1, (int16 *)&o1);

				// check for wrapping
				//if ((o1 < 0x6000 && rot > 0xA000) || (rot < 0x6000 && o1 > 0xA000))
				//if (o1 < rot)
				if (abs(o1 - rot) > 0x8000)
				{
					o1  += 0x8000;
					rot += 0x8000;
					wrap = true;
				}
				//o1  = 0x0000;
				//rot = 0xFF00;

				uint16	old_speed;

				old_speed = speed;

				// special case
				if (abs(o1 - rot) == 0x8000)
					speed = 0x100;
				// slow down for sharp curves
				else
				if (abs(o1 - rot) >= 0x1000)
				{
					uint32	slow = abs(o1 - rot);
					slow >>= 4;	// scaling
					speed -= slow;
				}
				// otherwise accelerate
				else
				{
					speed += accel;
					if (speed > speed_max)
					{
						// clip speed
						speed = speed_max;
					}
				}

				// prevent negative/positive overflow
				if (abs(old_speed - speed) > 0x8000)
				{
					if (old_speed < speed)
						speed = 0;
					else
						speed = 0xff00;
				}

				// adjust direction by so many degrees
				// be careful of negative adjustments
				if ((o1 > rot && (o1 - rot) > 0x80) || (o1 < rot && (rot - o1) >= 0x80))
				{
					if (o1 < rot)
						rot -= 0x280;
					else
					if (o1 > rot)
						rot += 0x280;
				}

				// turn off wrapping
				if (wrap)
					rot -= 0x8000;

				// now check the distances (store for later)
				dx = (xpos_max << 16) - xpos;
				dy = (ypos_max << 16) - ypos;
				dx >>= 16;
				dy >>= 16;

				// if we're in so many units of the target, signal it
				if ((system && (dy <= 6 && dy >= -8) && (dx <= 126 && dx >= -128)) || (!system && (dx <= 6 && dx >= -8) && (dy <= 126 && dy >= -128)))
				{
					// announce our new destination and flag it
					xpos_max = xpos_new & 0x7FFF;
					ypos_max = ypos_new;
					flags |= 0x08;
				}

				// update position
				xpos -= (ST010_Cos(rot) * 0x400 >> 15) * (speed >> 8) << 1;
				ypos -= (ST010_Sin(rot) * 0x400 >> 15) * (speed >> 8) << 1;

				// quirk: mask upper byte
				xpos &= 0x1FFFFFFF;
				ypos &= 0x1FFFFFFF;

				Memory.SRAM[0x00C0] = (uint8) (ypos_max);
				Memory.SRAM[0x00C1] = (uint8) (ypos_max >> 8);
				Memory.SRAM[0x00C2] = (uint8) (xpos_max);
				Memory.SRAM[0x00C3] = (uint8) (xpos_max >> 8);
				Memory.SRAM[0x00C4] = (uint8) (ypos);
				Memory.SRAM[0x00C5] = (uint8) (ypos >> 8);
				Memory.SRAM[0x00C6] = (uint8) (ypos >> 16);
				Memory.SRAM[0x00C7] = (uint8) (ypos >> 24);
				Memory.SRAM[0x00C8] = (uint8) (xpos);
				Memory.SRAM[0x00C9] = (uint8) (xpos >> 8);
				Memory.SRAM[0x00CA] = (uint8) (xpos >> 16);
				Memory.SRAM[0x00CB] = (uint8) (xpos >> 24);
				Memory.SRAM[0x00CC] = (uint8) (rot);
				Memory.SRAM[0x00CD] = (uint8) (rot >> 8);
				Memory.SRAM[0x00D4] = (uint8) (speed);
				Memory.SRAM[0x00D5] = (uint8) (speed >> 8);
				Memory.SRAM[0x00DC] = (uint8) (flags);
				Memory.SRAM[0x00DD] = (uint8) (flags >> 8);

				break;
			}

			default:
				break;
		}

		// lower signal: op processed
		ST010.op_reg  = 0;
		ST010.execute = 0;
	}
}

/***********************************************************************************
 Seta 011
***********************************************************************************/

static uint8	board[9][9];	// shougi playboard

uint8 S9xGetST011 (uint32 Address)
{
	uint8	t;
	uint16	address = (uint16) Address & 0xFFFF;

	// status check
	if (address == 0x01)
		t = 0xFF;	
	else
		t = Memory.SRAM[address]; // read directly from s-ram

	return (t);
}

void S9xSetST011 (uint32 Address, uint8 Byte)
{
	static bool	reset   = false;
	uint16		address = (uint16) Address & 0xFFFF;

	if (!reset)
	{
		// bootup values
		ST011.waiting4command = true;
		reset = true;
	}

	Memory.SRAM[address] = Byte;

	// op commands/data goes through this address
	if (address == 0x00)
	{
		// check for new commands
		if (ST011.waiting4command)
		{
			ST011.waiting4command = false;
			ST011.command         = Byte;
			ST011.in_index        = 0;
			ST011.out_index       = 0;

			switch (ST011.command)
			{
				case 0x01: ST011.in_count = 12 * 10 + 8; break;
				case 0x02: ST011.in_count = 4;           break;
				case 0x04: ST011.in_count = 0;           break;
				case 0x05: ST011.in_count = 0;           break;
				case 0x06: ST011.in_count = 0;           break;
				case 0x07: ST011.in_count = 0;           break;
				case 0x0E: ST011.in_count = 0;           break;
				default:   ST011.waiting4command = true; break;
			}
		}
		else
		{
			ST011.parameters[ST011.in_index] = Byte;
			ST011.in_index++;
		}
	}

	if (ST011.in_count == ST011.in_index)
	{
		// actually execute the command
		ST011.waiting4command = true;
		ST011.out_index       = 0;

		switch (ST011.command)
		{
			// unknown: download playboard
			case 0x01:
				// 9x9 board data: top to bottom, left to right
				// Values represent piece types and ownership
				for (int lcv = 0; lcv < 9; lcv++)
					memcpy(board[lcv], ST011.parameters + lcv * 10, 9 * 1);
				break;

			// unknown
			case 0x02:
				break;

			// unknown
			case 0x04:
				// outputs
				Memory.SRAM[0x12C] = 0x00;
				//Memory.SRAM[0x12D] = 0x00;
				Memory.SRAM[0x12E] = 0x00;
				break;

			// unknown
			case 0x05:
				// outputs
				Memory.SRAM[0x12C] = 0x00;
				//Memory.SRAM[0x12D] = 0x00;
				Memory.SRAM[0x12E] = 0x00;
				break;

			// unknown
			case 0x06:
				break;

			case 0x07:
				break;

			// unknown
			case 0x0E:
				// outputs
				Memory.SRAM[0x12C] = 0x00;
				Memory.SRAM[0x12D] = 0x00;
				break;
		}
	}
}

/***********************************************************************************
 Seta 018
***********************************************************************************/

uint8 S9xGetST018 (uint32 Address)
{
	uint8	t       = 0;
	uint16	address = (uint16) Address & 0xFFFF;

	// these roles may be flipped
	// op output
	if (address == 0x3804)
	{
		if (ST018.out_count)
		{
			t = (uint8) ST018.output[ST018.out_index];
			ST018.out_index++;
			if (ST018.out_count == ST018.out_index)
				ST018.out_count = 0;
		}
		else
			t = 0x81;
	}
	// status register
	else
	if (address == 0x3800)
		t = ST018.status;


	return (t);
}

void S9xSetST018 (uint8 Byte, uint32 Address)
{
	static bool	reset   = false;
	uint16		address = (uint16) Address & 0xFFFF;

	if (!reset)
	{
		// bootup values
		ST018.waiting4command = true;
		ST018.part_command    = 0;
		reset = true;
	}

	Memory.SRAM[address] = Byte;

	// default status for now
	ST018.status = 0x00;

	// op data goes through this address
	if (address == 0x3804)
	{
		// check for new commands: 3 bytes length
		if (ST018.waiting4command && ST018.part_command == 2)
		{
			ST018.waiting4command = false;
			ST018.in_index        = 0;
			ST018.out_index       = 0;
			ST018.part_command    = 0; // 3-byte commands
			ST018.pass            = 0; // data streams into the chip
			ST018.command <<= 8;
			ST018.command |= Byte;

			switch (ST018.command & 0xFFFFFF)
			{
				case 0x0100: ST018.in_count        = 0;    break;
				case 0xFF00: ST018.in_count        = 0;    break;
				default:     ST018.waiting4command = true; break;
			}
		}
		else
		if (ST018.waiting4command)
		{
			// 3-byte commands
			ST018.part_command++;
			ST018.command <<= 8;
			ST018.command |= Byte;
		}
	}
	// extra parameters
	else
	if (address == 0x3802)
	{
		ST018.parameters[ST018.in_index] = Byte;
		ST018.in_index++;
	}

	if (ST018.in_count == ST018.in_index)
	{
		// qctually execute the command
		ST018.waiting4command = true;
		ST018.in_index        = 0;
		ST018.out_index       = 0;

		switch (ST018.command)
		{
			// hardware check?
			case 0x0100:
				ST018.waiting4command = false;
				ST018.pass++;

				if (ST018.pass == 1)
				{
					ST018.in_count  = 1;
					ST018.out_count = 2;

					// Overload's research
					ST018.output[0x00] = 0x81;
					ST018.output[0x01] = 0x81;
				}
				else
				{
					//ST018.in_count = 1;
					ST018.out_count = 3;

					// no reason to change this
					//ST018.output[0x00] = 0x81;
					//ST018.output[0x01] = 0x81;
					ST018.output[0x02] = 0x81;

					// done processing requests
					if (ST018.pass == 3)
						ST018.waiting4command = true;
				}

				break;

			// unknown: feels like a security detection
			// format identical to 0x0100
			case 0xFF00:
				ST018.waiting4command = false;
				ST018.pass++;

				if (ST018.pass == 1)
				{
					ST018.in_count  = 1;
					ST018.out_count = 2;

					// Overload's research
					ST018.output[0x00] = 0x81;
					ST018.output[0x01] = 0x81;
				}
				else
				{
					//ST018.in_count = 1;
					ST018.out_count = 3;

					// no reason to change this
					//ST018.output[0x00] = 0x81;
					//ST018.output[0x01] = 0x81;
					ST018.output[0x02] = 0x81;

					// done processing requests
					if (ST018.pass == 3)
						ST018.waiting4command = true;
				}

				break;
		}
	}
}
