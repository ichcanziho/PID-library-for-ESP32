/*
 Name:		Lab3.ino
 Created:	27/11/2019 10:15:02
 Author:	Gabriel Ichcanziho
*/

// the setup function runs once when you press reset or power the board
#include "PID.h"
#include "ControlMotor.h"
//---------------------------------------
//variables de encoder de motor
#define EncoderPinA 2   /// encoder pin 2 (interrupcion 0)
#define EncoderPinB 3  ///encoder pin 3 (interrupcion 1)
volatile long counter = 0;
volatile long realcounter = 0;
volatile bool Anuevo = 0;
volatile bool Aanterior = 0;
volatile bool Bnuevo = 0;
volatile bool Banterior = 0;
volatile long errors = 0;
//---------------------------------------
int dt = 200;
long start_time;
int elapsed_time;
float output;
//---------------------------------------
ControlMotor Motor1(10, 11, 0, 1, 5000);
PID control(10,dt);
void setup() {
	EncoderInit();
	control.setGains(1.3, 0.1, 0.2);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	output = control.doControl(counter);
	Motor1.setVelocity(output);
	start_time = millis();
	elapsed_time = millis() - start_time;
	if (elapsed_time <= dt) {
		delay(dt - elapsed_time);
		counter = 0;
	}
}
void encoderRutine()
{
	Anuevo = digitalRead(EncoderPinA);
	Bnuevo = digitalRead(EncoderPinB);
	bool result1 = Anuevo ^ Banterior;
	bool result2 = Bnuevo ^ Aanterior;
	if (result1 && result2)
		errors += 1;
	if (result1 && !result2) {
		counter += 1;
		realcounter += 1;
	}
	if (!result1 && result2) {
		counter -= 1;
		realcounter -= 1;
	}
	Aanterior = Anuevo;
	Banterior = Bnuevo;
}

void EncoderInit(void) {
	pinMode(EncoderPinA, INPUT);
	digitalWrite(EncoderPinA, LOW);
	pinMode(EncoderPinB, INPUT);
	digitalWrite(EncoderPinB, LOW);

	attachInterrupt(digitalPinToInterrupt(EncoderPinA), encoderRutine, CHANGE);
	attachInterrupt(digitalPinToInterrupt(EncoderPinB), encoderRutine, CHANGE);
}