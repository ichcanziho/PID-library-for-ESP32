// 
// 
// 

#include "ControlMotor.h"



ControlMotor::ControlMotor(uint8_t in_1, uint8_t in_2, uint8_t channel1, uint8_t channel2, float freq) 
{
	pwm1.setup(in_1, channel1, freq, 10, true);
	pwm2.setup(in_2, channel2, freq, 10, true);
}

void ControlMotor::setVelocity(uint8_t velocity)
{
	if (velocity > 0) {
		pwm1.setDuty(velocity);
		pwm2.setDuty(0);
	}
	else {
		pwm1.setDuty(0);
		pwm2.setDuty(velocity*-1);
	}

}

