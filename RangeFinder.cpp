// RangeFinder.cpp created for project Robot on 11/27/2009 03:43:23

/*****************************************
* 
* Copyright somename 2009
*
*
******************************************/

#include "RangeFinder.h"
#include <WProgram.h>

RangeFinder::RangeFinder(void)
{
	_echoPin = 6;
	_initPin = 7;
}

void RangeFinder::init(int initPin = 7, int echoPin = 6)
{
	_echoPin = echoPin;
	_initPin = initPin;
	
  // make the init pin an output:
  pinMode(initPin, OUTPUT);
  // make the echo pin an input:
  pinMode(echoPin, INPUT);
}

//returns distance in cm
int RangeFinder::read(int numReadings = 5)
{
	unsigned long pulseTime = 0;  // variable for reading the pulse
	int total = 0;                // stores the cumlative total

	for (int i = 0; i < numReadings; i++) {
		//digitalWrite(_initPin, LOW);
		//delayMicroseconds(50);
		
		digitalWrite(_initPin, HIGH);
		delayMicroseconds(50);
		digitalWrite(_initPin, LOW);
		
		pulseTime = pulseIn(_echoPin, HIGH);
		
		total = total + pulseTime/58;
	}

	return total / numReadings;
}