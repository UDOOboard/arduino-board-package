#ifndef UARTmqxrpmsg_h
#define UARTmqxrpmsg_h

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void mqx_uartclass_init_rpmsg (void);
void mqx_uartclass_end_rpmsg (void);
void mqx_uartclass_flush_rpmsg (void);
int32_t mqx_uartclass_write_rpmsg (const uint8_t uc_data);
int32_t mqx_uartclass_write_buffer_rpmsg (const uint8_t *ptr, uint16_t len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
