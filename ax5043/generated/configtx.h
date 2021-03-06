/*
 *  Copyright (C) 2018 Jonathan Brandenburg
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Warning: This file is automatically generated by AX-RadioLAB.
Manual changes are overwritten! */

#include "../axradio/axradioinit_p.h"

//#define USE_LCD
//#define USE_DBGLINK
#define USE_COM0
//#define DEBUGMSG 
//#define MCU_SLEEP
#define WTIMER0_CLKSRC	CLKSRC_LPOSC
#define WTIMER0_PRESCALER 0x01
#define WTIMER0_PERIOD    0x0280
#define RADIO_MODE_TX        AXRADIO_MODE_ASYNC_TRANSMIT
extern const struct axradio_address remoteaddr_tx;
extern const struct axradio_address_mask localaddr_tx;
extern const uint8_t demo_packet[6];
extern const uint8_t framing_insert_counter;
extern const uint8_t framing_counter_pos;

extern const uint16_t lpxosc_settlingtime;
