// RangeFinder.h created for project Robot on 11/27/2009 03:43:30

/*****************************************
* 
* Copyright somename 2009
*
*
******************************************/


#ifndef RangeFinder_h
#define RangeFinder_h

class RangeFinder
{
private:
	int _echoPin;             // the SRF04-SRF05's echo pin
	int _initPin;             // the SRF04-SRF05's init pin
	
public:
  RangeFinder();

  void init(int, int);

	int read(int);
	
};

#endif