#ifndef Utymqx_h
#define Utymqx_h

#ifdef __cplusplus
extern "C" {
void mqx_sched_yield (void);
void mqx_debug_int (int id, int d);
void mqx_debug_str (uint8_t *str);
}
#else
void mqx_sched_yield (void);
void mqx_debug_int (int id, int d);
void mqx_debug_str (uint8_t *str);
#endif
#endif
