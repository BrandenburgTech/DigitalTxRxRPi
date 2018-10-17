// Copyright (c) 2018 Brandenburg Tech, LLC
// All rights reserved.
//
// This file is derived from LibMF, a library provided AXSEM AG. Based on the
// context of the library and the provision of source code, it is assumed
// the source code can be modified for specific applications of the AX5043.
//
// The Lib MF documentation provides the following notice:
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

#include "ax5043init.h"

#include <unistd.h>

#include "../axradio/axradioinit.h"
#include "../spi/ax5043spi.h"

uint8_t ax5043_reset(void)
{
	//printf("INFO: Resetting AX5043 (ax5043_reset)\n");
	uint8_t i;
	// Initialize Interface
	// Reset Device
	ax5043WriteReg(AX5043_PWRMODE, 0x80);
	ax5043WriteReg(AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN);
	// Wait some time for regulator startup
	usleep(10000);

	// Check Scratch
	i = ax5043ReadReg(AX5043_SILICONREVISION);
	i = ax5043ReadReg(AX5043_SILICONREVISION);

	if (i != SILICONREV1)
		return RADIO_ERR_REVISION;

	ax5043WriteReg(AX5043_SCRATCH, 0x55);
	if (ax5043ReadReg(AX5043_SCRATCH) != 0x55)
		return RADIO_ERR_COMM;

	ax5043WriteReg(AX5043_SCRATCH, 0xAA);
	if (ax5043ReadReg(AX5043_SCRATCH) != 0xAA)
		return RADIO_ERR_COMM;

	return RADIO_OK;
}


