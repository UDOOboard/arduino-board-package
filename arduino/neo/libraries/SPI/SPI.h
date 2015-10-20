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

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include <stdio.h>

//#define SPI_MODE0 0x02
//#define SPI_MODE1 0x00
//#define SPI_MODE2 0x03
//#define SPI_MODE3 0x01

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

enum SPITransferMode {
	SPI_CONTINUE,
	SPI_LAST
};

class SPIClass {
  public:
	SPIClass(char _spi, void(*_initCb)(void));

	// Transfer functions on default pin BOARD_SPI_DEFAULT_SS
	byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST);
	void transfer(void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST);

	void begin(void);
	void end(void);
	void begin(uint8_t _pin);

	// These methods sets a parameter on a single pin
	void setBitOrder(BitOrder);
	void setDataMode(uint8_t);
	void setBaud(uint32_t);
	void setFrameSize(uint32_t);


  private:
	void init();

	char spi;
	void (*initCb)(void);
	bool initialized;
	//BitOrder bitOrder;
};

#if SPI_INTERFACES_COUNT > 0
extern SPIClass SPI;
#endif

#endif
