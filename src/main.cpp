#include "Core.h"
#include <Arduino.h>

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
}

void loop()
{
	// Serial.println("Hello Sensor board!");

	static Core core(false); // pass mock_enabled
	core.update();

	delay(1000);
}
