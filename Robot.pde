// Sketch_11_27_2009_6.pde created for project Sketch_11_27_2009_6 on 11/27/2009 03:00:28

/*****************************************
* 
* Copyright somename 2009
*
*
******************************************/

#include <Servo.h>
#include "Head.h"
#include "Chassis.h"
#include "LED.h"


Chassis chassis;
Head head;
	
LED led = LED(13);

const unsigned int SERVO_WAIT = 15;

void setup()   
{                
	Serial.begin(9600);

	head.init();
	chassis.init(2, 3, 4, 5, 9, 10);
	chassis.enable();
	
	led.blink(250, 3);
	
	chassis.forward();
}

void loop()                     
{
	int distance = head.measureDistance();

	/*
	Serial.print("Distance: ");
	Serial.print(distance, DEC);
	Serial.println("cm");
	*/
	
	if (!head.movementDetected()) 
	{
		Serial.println("No movement detected #1");
		chassis.stop();
		delay(500);
		
		chassis.reverse();
		delay(1000);
		
		chassis.stop();
		delay(500);
		
		chassis.forward();
	}
	else
	{
		if (distance <= 10) {
  		Serial.println("Distance less than 10. Go Back!");
			chassis.stop();
			delay(500);

			chassis.reverse();
			
			while (distance <= 15) {
				
				distance = head.measureDistance();
				
				if (!head.movementDetected()) {
					Serial.println("Stuck @ #1");

					//clear bufffer, because we are not going to estimate speed
					//when stuck
					head.clearBuffer();
					
					chassis.stop();
					delay(500);
					
					//stuck, so better get out of this loop and find another path
					break;
				}
			}
			
			if (distance > 15)
			{
				Serial.println("More than 20 distance detected.");
			}
			else
			{
				//still set distance to 15, in order to get to antoher loop
				distance = 15;
			}
		}
		
		if (distance <= 30 && distance > 10){

  		Serial.println("Distance between 30 - 20.");
			
			chassis.stop();
			
  		Serial.println("Estimating direction.");

			head.estimateDistance();
			
			//decision time
				
			//Find the longest distance to the objects on the left
			int distanceLeft = 0;
			for (int i = 0; i < 8; i++) {      
				if (distanceLeft < head.radarReadings[i]) {
					distanceLeft = head.radarReadings[i];
				}
			}
			
			//Find the longest distance to the objects on the right
			int distanceRight = 0;
			for (int i = 10; i < 19; i++) {      
				if (distanceRight < head.radarReadings[i]) {
					distanceRight = head.radarReadings[i];
				}
			}	
			
			//give 250 ms for servo motor to get to the initial spot
			delay(250);

			int targetDistance = 0;
			
			//turn left or right until the detected distance is reached
			if (distanceLeft > distanceRight) {
    		Serial.println("Going left.");
				targetDistance = distanceLeft;
				chassis.left();
			}
			else {
    		Serial.println("Going right.");
				targetDistance = distanceRight;
				chassis.right();
			}
			
			Serial.print("Target distance: ");
			Serial.println(targetDistance, DEC);
			distance = 0;
			
			distance = head.measureDistance();

			int count = 0;

			while (distance < targetDistance - 2) { //allowing 1cm error for target distance estimation
				count++;
				distance = head.measureDistance();

				Serial.print("Distance: ");
			  Serial.println(distance, DEC);
				
  			//if path is blocked
				if (!head.movementDetected() || count >= 100) {
					Serial.println("Stuck @ #2");

					//clear bufffer, because we are not going to estimate speed
					//when stuck
					head.clearBuffer();
					
					chassis.reverse();
					delay(500);
					
					//stuck, so better get out of this loop and find another path
					break;
				}
			}
			
			//Stop motors otherwise battery gets drained
			chassis.stop();
			delay(100);
			
			//go forward
			chassis.forward();
		}
	}
	
	int speed = head.estimateSpeed();
	
	Serial.print("Speed: ");
	Serial.print(speed, DEC);
	Serial.println("cm/s");
	
	//ignore anything less than 20cm/s and more than 150cm/s
	//and distance to the closest object is less than 1 meter
	if (speed > 15 && speed < 500 && distance < 100)
	{
		int newSpeed = 0;
		
		//adjusting speed
		if (speed < 35)
		{
			newSpeed = chassis.speed + 5;
			
		  Serial.print("Increasing speed to ");
		}

		if (speed > 40)
		{
			newSpeed = chassis.speed - 5;
			
			//don't go less than 128
			if (newSpeed < 128)
				newSpeed = 128;
			
		  Serial.print("Decreasing speed to ");
		}

		if (newSpeed != 0)
		{
			Serial.println(newSpeed);
			chassis.setSpeed(newSpeed);
		}
	}
 
	delay(50);
}