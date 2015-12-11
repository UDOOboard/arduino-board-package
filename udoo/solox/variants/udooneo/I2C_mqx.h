
#ifndef I2Cmqx_h
#define I2Cmqx_h

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void mqx_towire_begin (uint8_t i2cId);
void mqx_towire_end (uint8_t i2cId);
void mqx_towire_flush (uint8_t i2cId);
int32_t mqx_towire_requestFrom(uint8_t i2cId, uint8_t address, uint8_t quantity, uint8_t sendStop, uint8_t *ptrRx);
int32_t mqx_towire_endTransmission(uint8_t i2cId, uint8_t address, uint8_t quantity, uint8_t sendStop, uint8_t *ptrTx);
int32_t mqx_towire_setClock(uint8_t i2cId, uint32_t fr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
