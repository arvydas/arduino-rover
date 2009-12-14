/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Chassis.h"
#include <WProgram.h>


/******************************************************************************
 * Constructors
 ******************************************************************************/
Chassis::Chassis(void)
{
  _motor1Pin1 = 2;    // H-bridge leg 1 (pin 2, 1A)
  _motor1Pin2 = 3;    // H-bridge leg 2 (pin 7, 2A)
  _motor2Pin1 = 4;    // H-bridge leg 1 (pin 2, 1A)
  _motor2Pin2 = 5;    // H-bridge leg 2 (pin 7, 2A)
  _enable1Pin = 9;    // H-bridge enable pin
  _enable2Pin = 10;    // H-bridge enable pin
	
	speed = 255;
}

void Chassis::init(int motor1Pin1, int motor1Pin2, int motor2Pin1, int motor2Pin2, int enable1Pin, int enable2Pin)
{
  _motor1Pin1 = motor1Pin1;
  _motor1Pin2 = motor1Pin2;
  _motor2Pin1 = motor2Pin1;
  _motor2Pin2 = motor2Pin2;

  _enable1Pin = enable1Pin;
  _enable2Pin = enable2Pin;

  pinMode(motor1Pin1, OUTPUT); 
  pinMode(motor1Pin2, OUTPUT); 
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT); 
  pinMode(motor2Pin2, OUTPUT); 
  pinMode(enable2Pin, OUTPUT);
}

void Chassis::enable(void)
{
  digitalWrite(_enable1Pin, HIGH);   
  digitalWrite(_enable2Pin, HIGH);   
}

void Chassis::forward(void)
{
  digitalWrite(_motor1Pin1, LOW);   
  digitalWrite(_motor2Pin1, LOW);   
  
	if (speed == 255)
	{
		digitalWrite(_motor1Pin2, HIGH);  
		digitalWrite(_motor2Pin2, HIGH);     
	}
	else
	{
		analogWrite(_motor1Pin2, speed);  
		analogWrite(_motor2Pin2, speed);     
	}
}

void Chassis::reverse(void)
{
  digitalWrite(_motor1Pin1, HIGH);   
  digitalWrite(_motor1Pin2, LOW);  
  digitalWrite(_motor2Pin1, HIGH);   
  digitalWrite(_motor2Pin2, LOW);     
}

void Chassis::stop(void)
{
  digitalWrite(_motor1Pin1, LOW);   
  digitalWrite(_motor1Pin2, LOW);  
  digitalWrite(_motor2Pin1, LOW);   
  digitalWrite(_motor2Pin2, LOW);     
}

void Chassis::left(void)
{
  digitalWrite(_motor1Pin1, HIGH);   
  digitalWrite(_motor1Pin2, LOW);  
  digitalWrite(_motor2Pin1, LOW);   
  digitalWrite(_motor2Pin2, HIGH);  
}

void Chassis::right(void)
{
  digitalWrite(_motor1Pin1, LOW);   
  digitalWrite(_motor1Pin2, HIGH);  
  digitalWrite(_motor2Pin1, HIGH);   
  digitalWrite(_motor2Pin2, LOW);  
}

void Chassis::slowToStop(void) 
{
  for (int i = 255; i == 0; i--) {
		analogWrite(_motor1Pin2, i);  
		analogWrite(_motor2Pin2, i);  
  }

  stop();
}

void Chassis::setSpeed(int newSpeed)
{
	if (newSpeed > 255)
		newSpeed = 255;
		
	if (newSpeed < 0)
		newSpeed = 0;
	
	speed = newSpeed;
	forward();
}