#ifndef LDR_DRIVER
#define LDR_DRIVER

#include "config/LightModule.h"
#include <Arduino.h>

class LDRDriver
{
private:
	uint8_t m_signal_pin;

public:
	LDRDriver();
	~LDRDriver();

	bool readIsDark();
};

#endif