/*
  Copyright (c) 2013 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
#include "Arduino.h"
#include "uty_mqx.h"
#include "pwm_ifc.h"
#include "servo_mqx.h"
#include <Servo.h>


#define usToPwmSamples(_us)    (_us * DEF_SERVO_TICKS_PERIOD / DEF_SERVO_uSEC_PERIOD)     // converts microseconds to pwm samples
#define pwmSamplesToUs(samples) (samples * DEF_SERVO_uSEC_PERIOD / DEF_SERVO_TICKS_PERIOD) // converts from ticks back to microseconds

static servo_t servos[MAX_SERVOS];                          // static array of servo structures

uint8_t ServoCount = 0;                                     // the total number of attached servos

#define SERVO_MIN() (this->min)  // minimum value in uS for this servo
#define SERVO_MAX() (this->max)  // maximum value in uS for this servo

Servo::Servo()
{
  if (ServoCount < MAX_SERVOS) {
    this->servoIndex = ServoCount++;                    // assign a servo index to this instance
    servos[this->servoIndex].ticks = usToPwmSamples(DEFAULT_PULSE_WIDTH);   // store default values
  } else {
    this->servoIndex = INVALID_SERVO;  // too many servos
  }
}

uint8_t Servo::attach(int pin)
{
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(int pin, int min, int max)
{

	if (pin > ANALOG_WRITE_HIGHEST_NUMBER_PIN) return (255);
	uint16_t pwmChn = ardPinToPwmChn[pin];
	if (pwmChn == 255) return (255);

	if (this->servoIndex < MAX_SERVOS) {
		servos[this->servoIndex].Pin.nbr = pin;
		this->min  = min;
		this->max  = max;
		servos[this->servoIndex].Pin.isActive = true;
		mqx_servo_attach(pwmChn, usToPwmSamples(DEFAULT_PULSE_WIDTH));
	}
	return this->servoIndex;
}

void Servo::detach()
{
	servos[this->servoIndex].Pin.isActive = false;
	mqx_servo_detach(ardPinToPwmChn[servos[this->servoIndex].Pin.nbr]);
}

void Servo::write(int value)
{
  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
  if (value < MIN_PULSE_WIDTH)
  {
    if (value < 0)
      value = 0;
    else if (value > 180)
      value = 180;

    value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
  }
  writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
	// calculate and store the values for the given channel
	byte channel = this->servoIndex;

	if( (channel < MAX_SERVOS) )   // ensure channel is valid
	{
		if (value < SERVO_MIN())          // ensure pulse width is valid
			value = SERVO_MIN();
		else if (value > SERVO_MAX())
			value = SERVO_MAX();

		uint32_t pwmTicks = usToPwmSamples(value);  // convert to ticks after compensating for interrupt overhead
		servos[channel].ticks = pwmTicks;

		pwm_set_sample(ardPinToPwmChn[servos[this->servoIndex].Pin.nbr], pwmTicks);
	}
}

int Servo::read() // return the value as degrees
{
  return map(readMicroseconds(), SERVO_MIN(), SERVO_MAX(), 0, 180);
}

int Servo::readMicroseconds()
{
  unsigned int pulsewidth;
  if (this->servoIndex != INVALID_SERVO)
    pulsewidth = pwmSamplesToUs(servos[this->servoIndex].ticks);
  else
    pulsewidth  = 0;

  return pulsewidth;
}

bool Servo::attached()
{
  return servos[this->servoIndex].Pin.isActive;
}

