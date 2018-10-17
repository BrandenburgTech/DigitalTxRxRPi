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

#include "ax5043spi.h"

//#include <process.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "dummyspi.h"
//#warning "For production builds, must not include dummyspi.h"
#include <wiringPiSPI.h>
#include <wiringPi.h>

#define MAX_SPI_WRITE_SIZE (512)

int spiChannel = -1;
int spiSpeed = -1;

void setSpiChannel(int newSpiChannel) {
    spiChannel = newSpiChannel;
}

void setSpiSpeed(int newSpiSpeed) {
    spiSpeed = newSpiSpeed;
}

void initializeSpi() {
    //printf("INFO: Initializing SPI\n");

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }
    if (spiSpeed < 0) {
        fprintf(stderr, "ERROR: invalid SPI speed %d\n", spiSpeed);
        exit(EXIT_FAILURE);
    }

    int fd;

    wiringPiSetup();

    fd = wiringPiSPISetup(spiChannel, spiSpeed);
    if (fd < 0) {
        fprintf(stderr, "ERROR: Cannot open SPI bus with error %d, %s\n",
        errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //printf("INFO: Finished initializing SPI\n");
}

void ax5043WriteReg(uint16_t reg, uint8_t val) {
    uint8_t buf[3];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0xF0;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = val & 0xff;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to write the register with result %d and error %s\n",
                result, strerror(result));
        exit(EXIT_FAILURE);
    }
}

void ax5043WriteReg2(uint16_t reg, uint16_t val) {
    uint8_t buf[4];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0xF0;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = (val >> 8) & 0xff;
    buf[3] = val & 0xff;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to write the register with result %d and error %s\n",
                result, strerror(result));
        exit(EXIT_FAILURE);
    }
}

void ax5043WriteReg3(uint16_t reg, uint32_t val) {
    uint8_t buf[5];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0xF0;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = (val >> 16)& 0xff;
    buf[3] = (val >> 8) & 0xff;
    buf[4] = val & 0xff;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to write the register with result %d and error %s\n",
                result, strerror(result));
        exit(EXIT_FAILURE);
    }
}

void ax5043WriteReg4(uint16_t reg, uint32_t val) {
    uint8_t buf[6];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0xF0;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = (val >> 24) & 0xff;
    buf[3] = (val >> 16) & 0xff;
    buf[4] = (val >> 8) & 0xff;
    buf[5] = val & 0xff;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to write the register with result %d and error %s\n",
                result, strerror(result));
        exit(EXIT_FAILURE);
    }
}

void ax5043WriteRegN(uint16_t reg, const uint8_t *in, uint32_t len) {
    uint8_t buf[MAX_SPI_WRITE_SIZE + 2];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }
    if (len > MAX_SPI_WRITE_SIZE) {
        fprintf(stderr,
                "ERROR: attempting to write too much data to SPI channel (max of %d): %d\n",
                MAX_SPI_WRITE_SIZE, len);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0xF0;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    for (uint32_t i = 0; i < len; ++i) {
        buf[i + 2] = *(in + i);
    }

    result = wiringPiSPIDataRW(spiChannel, buf, len + 2);
    if (result < 0) {
        fprintf(stderr,
                "Failed to write the register with result %d and error %s\n",
                result, strerror(result));
        exit(EXIT_FAILURE);
    }
}

uint8_t ax5043ReadReg(uint16_t reg) {
    uint8_t buf[3];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0x70;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = 0x0000;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to read register with result = %d and error %s\n",
                result, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //printf("DEBUG: read value: %d\n", (int)buf[2]);
    return (buf[2]);
}

uint16_t ax5043ReadReg2(uint16_t reg) {
    uint8_t buf[4];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0x70;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = 0x0000;
    buf[3] = 0x0000;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to read register with result = %d and error %s\n",
                result, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //printf("DEBUG: read value: %d\n", (int)buf[2]);
    return (buf[3]) | (buf[2] << 8);
}

uint32_t ax5043ReadReg3(uint16_t reg) {
    uint8_t buf[5];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0x70;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = 0x0000;
    buf[3] = 0x0000;
    buf[4] = 0x0000;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to read register with result = %d and error %s\n",
                result, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //printf("DEBUG: read value: %d\n", (int)buf[2]);
    return (buf[4]) | (buf[3] << 8) | (buf[2] << 16);
}

uint32_t ax5043ReadReg4(uint16_t reg) {
    uint8_t buf[6];
    int result;

    if (spiChannel < 0) {
        fprintf(stderr, "ERROR: invalid SPI channel %d\n", spiChannel);
        exit(EXIT_FAILURE);
    }

    uint8_t mask = 0x70;

    buf[0] = mask | (~mask & (reg >> 8));
    buf[1] = (reg & 0xff);
    buf[2] = 0x0000;
    buf[3] = 0x0000;
    buf[4] = 0x0000;
    buf[5] = 0x0000;

    result = wiringPiSPIDataRW(spiChannel, buf, sizeof(buf));
    if (result < 0) {
        fprintf(stderr,
                "Failed to read register with result = %d and error %s\n",
                result, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //printf("DEBUG: read value: %d\n", (int)buf[2]);
    return (buf[5]) | (buf[4] << 8) | (buf[3] << 16) | (buf[2] << 24);
}
