#ifndef servomqx_h
#define servomqx_h

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#define DEF_SERVO_FWM							3			// default FIFO watermark
#define DEF_SERVO_PRESCALER						7			// default prescale
#define DEF_SERVO_ACT_POL						0			// default active polarity: 0 set at rollover, 1 clear at rollover
#define DEF_SERVO_TICKS_PERIOD					(60000-2)	// default pwm ticks period
#define DEF_SERVO_REPEAT						1			// default repeat
#define DEF_SERVO_uSEC_PERIOD				    20000   	// default pwm period in usec

void mqx_servo_attach (uint16_t pwmChn, uint16_t defPulseWidth);
void mqx_servo_detach(uint16_t pwmChn);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif
