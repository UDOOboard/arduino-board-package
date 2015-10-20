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

#ifndef _UART_CLASS_
#define _UART_CLASS_

// otherwise write method change in _io_write and I have compiler error !!!
//#define _io_write	write
//#define _io_read	read

#include "HardwareSerial.h"
#include "RingBuffer.h"

#define SERIAL_8N1 UARTClass::Mode_8N1
#define SERIAL_8E1 UARTClass::Mode_8E1
#define SERIAL_8O1 UARTClass::Mode_8O1
#define SERIAL_8M1 UARTClass::Mode_8M1
#define SERIAL_8S1 UARTClass::Mode_8S1

class UARTClass : public HardwareSerial
{
  public:
    enum UARTModes {
      Mode_8N1 = 0,
      Mode_8E1 = 1,
      Mode_8O1 = 2,
      Mode_8M1 = 3,
      Mode_8S1 = 4
    };
    UARTClass(RingBuffer* pRx_buffer, RingBuffer* pTx_buffer, bool mcc);
    UARTClass(RingBuffer* pRx_buffer, RingBuffer* pTx_buffer);

    void begin(const uint32_t dwBaudRate);
    void begin(const uint32_t dwBaudRate, const UARTModes config);
    void end(void);
    int available(void);
    int availableForWrite(void);
    int peek(void);
    int read(void);
    int _read(void);		// only for test
    void flush(void);
    size_t write(const uint8_t c);
    using Print::write; // pull in write(str) and write(buf, size) from Print

    virtual void IrqHandler(uint8_t rxChar);

    operator bool() { return true; }; // UART always active

  protected:
    void init(const uint32_t dwBaudRate, const uint32_t config);

    RingBuffer *_rx_buffer;
    RingBuffer *_tx_buffer;
};

extern UARTClass Serial;
extern UARTClass SerialDebug;

#endif // _UART_CLASS_
