// Head.cpp created for project Rover on 11/30/2009 11:33:34

/*****************************************
* 
* Copyright somename 2009
*
*
******************************************/

#include "Head.h"

Head::Head(void) {
	clearBuffer();
}

void Head::init(void)
{
	rangeFinder.init(7, 6);
	servo.attach(11);
	
	//set head to the default position
	servo.write(90);
}

void Head::estimateDistance(void) {
	servo.write(180);

	delay(250);
	
	//Get the distances to surrounding area objects -90 to 90 degrees
	for (int i = 0; i < numOfRadarReadings; i++) {      
		//skip the center calculation
		if (i == 9)
			continue;
		
		servo.write(180 - i * 10);
		
		delay(50);
		
		radarReadings[i] = rangeFinder.read(2);
	}
	
	//set head to the default position
	servo.write(90);
}


int Head::measureDistance(void)
{
	//shift readings
	for (int i = 1; i < maxReadings; i++)
	{
		readingsBuffer[i - 1] = readingsBuffer[i];
		timeBuffer[i - 1] = timeBuffer[i];
	}

	int distance = rangeFinder.read(1);
	
	readingsBuffer[maxReadings - 1] = distance;
	timeBuffer[maxReadings - 1] = millis();
	
	return distance;
}

bool Head::movementDetected(void) {
	for (int i = 1; i < maxReadings; i++)
	{
		if (readingsBuffer[i - 1] != readingsBuffer[i])
			return true;
	}
	
	return false;
}

int Head::estimateSpeed(void)
{
	if (readingsBuffer[maxReadings - 2] == -1)
	{
		return -1;
	}
	
	/*
	Serial.print(readingsBuffer[maxReadings - 1], DEC);
	Serial.print(" | ");
	Serial.println(readingsBuffer[maxReadings - 2], DEC);
	Serial.print(timeBuffer[maxReadings - 1], DEC);
	Serial.print(" | ");
	Serial.println(timeBuffer[maxReadings - 2], DEC);
	*/
	
	return -1 * float(readingsBuffer[maxReadings - 1] - readingsBuffer[maxReadings - 2]) / 
					float(timeBuffer[maxReadings - 1] - timeBuffer[maxReadings - 2]) * 1000 ;
}

void Head::clearBuffer(void)
{
	for (int i = 0; i < maxReadings; i++)
	{
		readingsBuffer[i] = -1;
		timeBuffer[i] = -1;
	}
}