#include "core/light/LDRDriver.h"

LDRDriver::LDRDriver()
{
	LDRConfig ldrConfig{};
	m_signal_pin = ldrConfig.SIGNAL_PIN;

	pinMode(m_signal_pin, INPUT);
};
LDRDriver::~LDRDriver() = default;

bool LDRDriver::readIsDark() { return digitalRead(m_signal_pin); }