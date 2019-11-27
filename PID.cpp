// 
// 
// 

#include "PID.h"

PID::PID(float reference,int dt)
{
	_reference = reference;
	_time = dt/1000.0f;
	_output = 0;
	_error = 0;
	_error_prev = 0;
	_kp = 0;
	_ki = 0;
	_kd = 0;
}

void PID::setReference(float reference)
{
	_reference = reference;
}

void PID::setGains(float kp, float ki, float kd)
{
	_kp = kp;
	_ki = ki;
	_kd = kd;
}

float PID::doControl(float measurement)
{
	_error = _reference - measurement;
	if (_error + _error_prev < WINDUP) { // windup 10000.0f
		_output = _kp * _error + (_kd * ((_error - _error_prev) / _time)) + (_ki * (_error + _error_prev) * _time);
	}
	else {
		_error_prev = 0;
		_output = _kp * _error + (_kd * ((_error - _error_prev) / _time)) + (_ki * (_error + _error_prev) * _time);
	}
	_error_prev = _error;

	return _output;
}

void PID::setDTms(uint16_t time_ms)
{
	_time = time_ms / 1000.0f;
}

float PID::getError()
{
	return _error;
}

float PID::getReference()
{
	return _reference;
}
