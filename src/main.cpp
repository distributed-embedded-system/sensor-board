#include "Core.h"
#include <Arduino.h>

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
}

void loop()
{

	static Core core;
	core.update();

	delay(1000);
}
