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

#include "dummyspi.h"

int wiringPiSPIDataRW(int spiChannel __attribute__((unused)),
		unsigned char buf[] __attribute__((unused)), int len __attribute__((unused))) {
	return 0;
}

void wiringPiSetup() {
}

int wiringPiSPISetup(int spiChannel __attribute__((unused)),
		int spiSpeed __attribute__((unused))) {
	return 0;
}
