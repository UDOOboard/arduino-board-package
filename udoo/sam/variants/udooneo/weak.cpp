#include "Arduino.h"

// ----------------------------------------------------------------------------
__attribute__((weak)) void serialEvent() {_sched_yield();};
__attribute__((weak)) void serialEventDebug() {_sched_yield();};
__attribute__((weak)) void yield() {delay(1000);};
__attribute__((weak)) void user_task1() {delay(1000);};
__attribute__((weak)) void user_task2() {delay(1000);};
__attribute__((weak)) void user_task3() {delay(1000);};

void serialEventRun(void)
{

	if (Serial.available()) serialEvent();
	if (SerialDebug.available()) serialEventDebug();
}
