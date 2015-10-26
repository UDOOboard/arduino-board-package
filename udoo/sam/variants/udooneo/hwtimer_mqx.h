#ifndef HWTIMERmqx_h
#define HWTIMERmqx_h

#ifdef __cplusplus
extern "C" {
uint32_t mqx_hwtimer_get_us (void);
void mqx_init_hwtimer1 (void);
void mqx_deinit_hwtimer1 (void);
}
#else
uint32_t mqx_hwtimer_get_us (void);
void mqx_init_hwtimer1 (void);
void mqx_deinit_hwtimer1 (void);
#endif
#endif
