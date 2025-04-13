#ifndef FAN_DRIVER
#define FAN_DRIVER

#include "config/TempModule.h"
#include <Arduino.h>
class FanDriver
{
private:
	uint8_t	  m_pwm_pin;
	uint8_t	  m_tach_pin;
	int		  m_rpm;

public:
	FanDriver();
	~FanDriver();
	// private methods
	int	 readRPM();
	void setSpeed(int speedPercentage);

private:
	int percentageToPWM(float percentage);
	int getRPMFromPercentage(int percentage);
};

#endif