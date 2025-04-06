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
	const int PULSES_PER_REVOLUTION = PULSES_PER_REVOLUTION;
	const int MAX_RPM				= MAX_RPM;

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