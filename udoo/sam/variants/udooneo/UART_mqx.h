#ifndef UARTmqx_h
#define UARTmqx_h

void mqx_uartclass_init (const uint32_t dwBaudRate, const uint32_t modeReg);
void mqx_uartclass_end (void);
void mqx_uartclass_flush (void);
int32_t mqx_uartclass_write (const uint8_t uc_data);
int32_t mqx_uartclass_read (void);
int32_t mqx_uartclass_write_buffer (const uint8_t *ptr, uint16_t len);

#endif
