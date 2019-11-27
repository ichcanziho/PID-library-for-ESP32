// PID.h

#ifndef _PID_h
#define _PID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define WINDUP 10000.0f
class PID
{
public:
	PID(float reference,int dt);
	void setReference(float reference);
	void setGains(float kp, float ki, float kd);
	float doControl(float measurement);
	void setDTms(uint16_t time_ms);
	float getError();
	float getReference();

private:
	float _reference;
	float _kp;
	float _ki;
	float _kd;
	float _time;
	float _output;
	float _error;
	float _error_prev;
};



#endif

