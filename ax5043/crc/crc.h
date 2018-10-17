// Copyright (c) 2018 Brandenburg Tech, LLC
// All rights reserved.
//
// This file is derived from LibMF, a library provided AXSEM AG. Based on the
// context of the library and the provision of source code, it is assumed
// the source code can be modified for specific applications of the AX5043.
//
// The documentation provides the following notice:
//    LibMF is available in source and binary form for SDCC, Keil C51 and IAR
//    ICC.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>

uint16_t crc_crc16(const uint8_t *buf, uint16_t buflen, uint16_t crc);
uint16_t crc_crc16_byte(uint16_t crc, uint8_t c);
uint16_t pn9_buffer(uint8_t *buf, uint16_t buflen, uint16_t pn9, uint8_t xor);
uint16_t pn9_advance_bits(uint16_t pn9, uint16_t bits);
uint16_t pn9_advance_byte(uint16_t pn9);

#endif /* CRC_H_ */
