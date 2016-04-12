/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "SPI.h"
#include "spi_mqx.h"

SPIClass::SPIClass(char _spi, void(*_initCb)(void)) :
	spi(_spi), initCb(_initCb), initialized(false)
{
	// Empty
}

void SPIClass::begin() {
	init();
	// NPCS control is left to the user
	mqx_spi_begin(0);

	// Default speed set to 4Mhz
	setBaud(4000000);
	setDataMode(SPI_MODE0);
	setBitOrder(MSBFIRST);
}

void SPIClass::begin(uint8_t _pin) {
	init();
	// NPCS control is left to spi driver
	mqx_spi_begin(_pin);

	// Default speed set to 4Mhz
	setBaud(4000000);
	setDataMode(SPI_MODE0);
	setBitOrder(MSBFIRST);
}

void SPIClass::init() {
	if (initialized)
		return;
	initCb();
	initialized = true;
}

void SPIClass::end() {
	//todo SPI_Disable(spi);
	initialized = false;
	mqx_spi_end();
}

void SPIClass::setBitOrder(BitOrder _bitOrder) {
	mqx_spi_set_bit_order (_bitOrder);
}

void SPIClass::setDataMode(uint8_t _mode) {
	mqx_spi_set_data_mode (_mode);
}

void SPIClass::setBaud(uint32_t _baud) {
	mqx_spi_set_baud (_baud);
}

/* Maximum bits of SPI burst. Because some flash commands must finish in one CS
   selection while ECSPI CS is controlled by SPI burst, thus we must try our best
   to put as much data as possible in one burst default = 4096*/
// I thought that was bit len
void SPIClass::setFrameSize(uint32_t _size) {
	mqx_spi_set_frame_size (_size);
}

byte SPIClass::transfer(uint8_t _data, SPITransferMode _mode) {
	/* Data definitions */
	uint8_t rx_buffer[1];
	uint8_t tx_buffer[1];

	mqx_tx_rx_burst(tx_buffer, rx_buffer, 1);
	return (rx_buffer[0]);
}

void SPIClass::transfer(void *_buf, size_t _count, SPITransferMode _mode) {
	if (_count == 0)
		return;

	mqx_tx_rx_burst((uint8_t *)_buf, (uint8_t *)_buf, _count);
}

#if SPI_INTERFACES_COUNT > 0
static void SPI_0_Init(void) {
}

SPIClass SPI(SPI_INTERFACE, SPI_0_Init);
#endif
