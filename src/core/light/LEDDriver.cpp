#include "core/light/LEDDriver.h"

LEDDriver::LEDDriver() : m_stamp{millis()}
{
	m_signal_pin = LEDConfig{}.SIGNAL_PIN;
	pinMode(m_signal_pin, OUTPUT);
}

LEDDriver::~LEDDriver() = default;

void LEDDriver::setLEDState(bool isEnabled)
{
	Serial.print("DRIVER LOW LEVEL Setting LED state: ");
	Serial.println(isEnabled ? "ON" : "OFF");
	digitalWrite(m_signal_pin, isEnabled ? HIGH : LOW);
}