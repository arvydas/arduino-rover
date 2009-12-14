#ifndef Chassis_h
#define Chassis_h

class Chassis
{
private:
  //motor driver chip default pinouts
  int _motor1Pin1;    // H-bridge leg 1 (pin 2, 1A)
  int _motor1Pin2;    // H-bridge leg 2 (pin 7, 2A)
  int _motor2Pin1;    // H-bridge leg 1 (pin 2, 1A)
  int _motor2Pin2;    // H-bridge leg 2 (pin 7, 2A)
  int _enable1Pin;    // H-bridge enable pin
  int _enable2Pin;    // H-bridge enable pin
	
public:
	int speed;

  Chassis();

  void init(int, int, int, int, int, int);
	void enable(void);

  //Robot movement
  void forward(void);
  void reverse(void);
  void stop(void);
  void left(void);
  void right(void);
  void slowToStop(void); 
	
	void setSpeed(int newSpeed);
};

#endif