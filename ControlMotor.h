// ControlMotor.h

#ifndef _CONTROLMOTOR_h
#define _CONTROLMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PWM_ESP32.h"

class ControlMotor
{
public:
	ControlMotor(uint8_t in_1, uint8_t in_2, uint8_t channel1, uint8_t channel2 , float freq);
	void setVelocity(uint8_t velocity);
	PWM pwm1;
	PWM pwm2;
private:
};
#endif

