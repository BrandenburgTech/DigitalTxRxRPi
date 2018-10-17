/*! \copyright
  Copyright (C) 2018 Jonathan Brandenburg
  ---
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  ---
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  ---
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

 \file ax5043spi_p.h
 \brief Provides an abstraction layer for the SPI interface communicating to the digital transceiver
 */

#ifndef AX5043SPI_P_H_
#define AX5043SPI_P_H_

#include <stdint.h>

#define SPI_CHANNEL (0) //!< The default SPI channel for the digital transceiver
#define SPI_SPEED (32000000) //!< The default SPI bus speed for the digital transceiver

/*! \fn void setSpiChannel(int newSpiChannel)
 \brief Set the SPI channel for the digital transceiver.

 setSpiChannel must be called before initializeSpi(). The default is SPI_CHANNEL.
 \param newSpiChannel The SPI channel for the digital transceiver.
 \sa SPI_CHANNEL
 \sa initializeSpi
 */
void setSpiChannel(int newSpiChannel);

/*! \fn void setSpiSpeed(int newSpiSpeed)
 \brief Set the SPI bus speed for the digital transceiver.


 setSpiSpeed must be called before initializeSpi(). The default is SPI_SPEED.
 \param newSpiSpeed The SPI bus speed for the digital transceiver.
 \sa SPI_SPEED
 \sa initializeSpi
 */
void setSpiSpeed(int newSpiSpeed);

/*! \fn void initializeSpi()
 \brief Initilize the SPI bus to communicate with the digital transceiver.

 setSpiChannel() and setSpiSpeed() must both be called before initializeSPI().
 \sa setSpiChannel
 \sa setSpiSpeed
 */
void initializeSpi(void);

/*! \fn void ax5043WriteReg(uint16_t reg, uint8_t val)
 \brief Write a value to an AX5043 register.
 \param reg The register to write.
 \param val The value to right to the register.
 */
void ax5043WriteReg(uint16_t reg, uint8_t val);

/*! \fn void ax5043WriteReg2(uint16_t reg, uint16_t val)
 \brief Write a two byte value to an AX5043 register.
 \param reg The register to write.
 \param val The value to right to the register.
 */
void ax5043WriteReg2(uint16_t reg, uint16_t val);

/*! \fn void ax5043WriteReg3(uint16_t reg, uint32_t val)
 \brief Write a three byte value to an AX5043 register.
 \param reg The register to write.
 \param val The value to right to the register.
 */
void ax5043WriteReg3(uint16_t reg, uint32_t val);

/*! \fn void ax5043WriteReg4(uint16_t reg, uint32_t val)
 \brief Write a four byte value to an AX5043 register.
 \param reg The register to write.
 \param val The value to right to the register.
 */
void ax5043WriteReg4(uint16_t reg, uint32_t val);

/*! \fn void ax5043WriteRegN(uint16_t reg, const uint8_t *in, uint32_t len)
 \brief Write a four byte value to an AX5043 register.
 \param reg The register to write.
 \param val The value to right to the register.
 */
void ax5043WriteRegN(uint16_t reg, const uint8_t *in, uint32_t len);

/*! \fn uint8_t ax5043ReadReg(uint16_t reg)
 \brief Read a one byte value from an AX5043 register.
 \param reg The register to read.
 \return The value read from the register.
 */
uint8_t ax5043ReadReg(uint16_t reg);

/*! \fn uint16_t ax5043ReadReg2(uint16_t reg)
 \brief Read a two value from an AX5043 register.
 \param reg The register to read.
 \return The value read from the register.
 */
uint16_t ax5043ReadReg2(uint16_t reg);

/*! \fn uint32_t ax5043ReadReg3(uint16_t reg)
 \brief Read a three byte value from an AX5043 register.
 \param reg The register to read.
 \return The value read from the register.
 */
uint32_t ax5043ReadReg3(uint16_t reg);

/*! \fn uint32_t ax5043ReadReg4(uint16_t reg)
 \brief Read a four byte value from an AX5043 register.
 \param reg The register to read.
 \return The value read from the register.
 */
uint32_t ax5043ReadReg4(uint16_t reg);

#endif /* AX5043SPI_P_H_ */
