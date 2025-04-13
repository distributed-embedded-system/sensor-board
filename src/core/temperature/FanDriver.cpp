
#include "core/temperature/FanDriver.h"

FanDriver::FanDriver()
{
	m_rpm = getRPMFromPercentage(INITIAL_FAN_SPEED);

	FanConfig fanConfig{};

	m_pwm_pin  = fanConfig.PWM_PIN;
	m_tach_pin = fanConfig.TACH_PIN;

	pinMode(m_pwm_pin, OUTPUT);
	pinMode(m_tach_pin, INPUT);
}

FanDriver::~FanDriver() = default;

int FanDriver::readRPM()
{
	// Find a way to fix the readings
	// auto rpm = analogRead(m_tach_pin);
	// Serial.print("RPM: ");
	// Serial.println(rpm);
	// m_rpm = rpm;
	return m_rpm;
}

void FanDriver::setSpeed(int speedPercentage)
{
	int value = percentageToPWM(speedPercentage);
	analogWrite(m_pwm_pin, value);

	m_rpm = getRPMFromPercentage(speedPercentage);
}

int FanDriver::percentageToPWM(float percentage)
{
	// Clamp the percentage between 0 and 100
	if (percentage < 0.0f)
	{
		percentage = 0.0f;
	}
	else if (percentage > 100.0f)
	{
		percentage = 100.0f;
	}

	return static_cast<int>((percentage / 100.0f) * 255.0f);
}

int FanDriver::getRPMFromPercentage(int percentage)
{
	return static_cast<int>((percentage / 100.0f) * MAX_RPM);
}