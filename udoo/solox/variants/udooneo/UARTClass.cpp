/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"

#include "UART_mqx.h"
#include "UART_mqx_mcc.h"

#include "uty_mqx.h"

#define ARDUINO_SERIAL_DEBUG_RX

// Constructors ////////////////////////////////////////////////////////////////
UARTClass::UARTClass(RingBuffer *pRx_buffer, RingBuffer *pTx_buffer, bool mcc) {
	_rx_buffer = pRx_buffer;
	_tx_buffer = pTx_buffer;
	is_mcc = mcc;
}

UARTClass::UARTClass(RingBuffer *pRx_buffer, RingBuffer *pTx_buffer) {
	UARTClass (pRx_buffer, pTx_buffer, false);
}

// Public Methods //////////////////////////////////////////////////////////////

void UARTClass::begin(const uint32_t dwBaudRate) {
	begin(dwBaudRate, Mode_8N1);
}

void UARTClass::begin(const uint32_t dwBaudRate, const UARTModes config) {
	uint32_t modeReg = static_cast<uint32_t>(config) & 0x00000E00;
	init(dwBaudRate, modeReg);
}

void UARTClass::init(const uint32_t dwBaudRate, const uint32_t modeReg) {

	// Make sure both ring buffers are initialized back to empty.
	_rx_buffer->_iHead = _rx_buffer->_iTail = 0;
	_tx_buffer->_iHead = _tx_buffer->_iTail = 0;

	if (!is_mcc)
		mqx_uartclass_init(dwBaudRate, modeReg);
	else
		mqx_uartclass_init_mcc();
}

void UARTClass::end(void) {
	// Clear any received data
	_rx_buffer->_iHead = _rx_buffer->_iTail;
	if (!is_mcc)
		mqx_uartclass_end ();
	else
		mqx_uartclass_end_mcc ();
}


int UARTClass::available(void) {
	return (uint32_t) (SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail)
			% SERIAL_BUFFER_SIZE;
}

int UARTClass::availableForWrite(void) {

	// tobe completed by check available from serial driver
	return (SERIAL_BUFFER_SIZE);
/*
	int head = _tx_buffer->_iHead;
	int tail = _tx_buffer->_iTail;

	if (head >= tail)
		return SERIAL_BUFFER_SIZE - 1 - head + tail;
	return tail - head - 1;
*/
}

int UARTClass::peek(void) {

#ifndef ARDUINO_SERIAL_DEBUG_RX
	if (is_mcc) return (0);
#endif

	if (_rx_buffer->_iHead == _rx_buffer->_iTail)
		return -1;

	return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int UARTClass::read(void) {

#ifndef ARDUINO_SERIAL_DEBUG_RX
	if (is_mcc) return (0);
#endif

	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer->_iHead == _rx_buffer->_iTail)
		return -1;

	uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
	_rx_buffer->_iTail = (unsigned int) (_rx_buffer->_iTail + 1)
				% SERIAL_BUFFER_SIZE;
	return uc;
}

void UARTClass::flush(void) {

	if (!is_mcc)
		mqx_uartclass_flush ();
	else
		mqx_uartclass_flush_mcc();
}

size_t UARTClass::write(const uint8_t uc_data) {

	int32_t wrByte;

	if (!is_mcc)
		wrByte=mqx_uartclass_write (uc_data);
	else
		wrByte=mqx_uartclass_write_mcc (uc_data);

	if (wrByte < 0)
		return (0);
	else
		return (wrByte);
}

void UARTClass::IrqHandler(uint8_t rxChar) {
	_rx_buffer->store_char(rxChar);
}

/*
 * UART objects
 */
RingBuffer rx_buffer1;
RingBuffer rx_buffer2;
UARTClass Serial0(&rx_buffer1, NULL);
UARTClass Serial(&rx_buffer2, NULL, true);

extern "C" {
	void call_irq_handler (UARTClass* ptr, uint8_t rxChar) {
		ptr->IrqHandler(rxChar);
	}
}
