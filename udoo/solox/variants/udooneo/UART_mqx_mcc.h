#ifndef UARTmqxmcc_h
#define UARTmqxmcc_h

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void mqx_uartclass_init_mcc (void);
void mqx_uartclass_end_mcc (void);
void mqx_uartclass_flush_mcc (void);
int32_t mqx_uartclass_write_mcc (const uint8_t uc_data);
int32_t mqx_uartclass_write_buffer_mcc (const uint8_t *ptr, uint16_t len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
