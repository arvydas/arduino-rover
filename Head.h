// Head.h created for project Rover on 11/30/2009 11:33:40

/*****************************************
* 
* Copyright somename 2009
*
*
******************************************/


#ifndef Head_h
#define Head_h

#include <WProgram.h> 
#include <Servo.h>
#include "RangeFinder.h"

/*
enum Direction {
	Left,
	Right
}
*/

class Head
{
private:
	static const int maxReadings = 10;
  int readingsBuffer[maxReadings];
  int timeBuffer[maxReadings];
	
public:
	RangeFinder rangeFinder;
	Servo servo;

	static const int numOfRadarReadings = 19;
	int radarReadings[numOfRadarReadings];

	Head();
	
	void init(void);
	
	void estimateDistance(void);
	int measureDistance(void);
	bool movementDetected(void);
	int estimateSpeed(void);

	void clearBuffer(void);
};


#endif