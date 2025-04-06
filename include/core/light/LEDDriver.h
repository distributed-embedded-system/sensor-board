#ifndef LED_DRIVER
#define LED_DRIVER

#include "config/LightModule.h"
#include <Arduino.h>

class LEDDriver
{
	// private members
private:
	unsigned long m_stamp;
	uint8_t		  m_signal_pin;
	// public methods
public:
	LEDDriver();
	~LEDDriver();
	void setLEDState(bool isEnabled);
	// private methods
private:
};

#endif