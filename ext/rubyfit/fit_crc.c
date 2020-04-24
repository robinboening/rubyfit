////////////////////////////////////////////////////////////////////////////////
// The following FIT Protocol software provided may be used with FIT protocol
// devices only and remains the copyrighted property of Garmin Canada Inc.
// The software is being provided on an "as-is" basis and as an accommodation,
// and therefore all warranties, representations, or guarantees of any kind
// (whether express, implied or statutory) including, without limitation,
// warranties of merchantability, non-infringement, or fitness for a particular
// purpose, are specifically disclaimed.
//
// Copyright 2020 Garmin Canada Inc.
////////////////////////////////////////////////////////////////////////////////
// ****WARNING****  This file is auto-generated!  Do NOT edit this file.
// Profile Version = 21.27Release
// Tag = production/akw/21.27.00-0-gef9575d
// Product = EXAMPLE
// Alignment = 4 bytes, padding disabled.
////////////////////////////////////////////////////////////////////////////////


#include "fit_crc.h"


//////////////////////////////////////////////////////////////////////////////////
// Public Functions
//////////////////////////////////////////////////////////////////////////////////

FIT_UINT16 FitCRC_Get16(FIT_UINT16 crc, FIT_UINT8 byte)
{
   static const FIT_UINT16 crc_table[16] =
   {
      0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
      0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400
   };
   FIT_UINT16 tmp;

   // compute checksum of lower four bits of byte
   tmp = crc_table[crc & 0xF];
   crc  = (crc >> 4) & 0x0FFF;
   crc  = crc ^ tmp ^ crc_table[byte & 0xF];

   // now compute checksum of upper four bits of byte
   tmp = crc_table[crc & 0xF];
   crc  = (crc >> 4) & 0x0FFF;
   crc  = crc ^ tmp ^ crc_table[(byte >> 4) & 0xF];

   return crc;
}

FIT_UINT16 FitCRC_Update16(FIT_UINT16 crc, const volatile void *data, FIT_UINT32 size)
{
   FIT_BYTE *data_ptr = (FIT_BYTE *)data;

   while (size)
   {
      crc = FitCRC_Get16(crc, *data_ptr);
      data_ptr++;
      size--;
   }

   return crc;
}

FIT_UINT16 FitCRC_Calc16(const volatile void *data, FIT_UINT32 size)
{
   return FitCRC_Update16(0, data, size);
}

