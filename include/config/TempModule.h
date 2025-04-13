#ifndef TEMP_MODULE_CONFIG
#define TEMP_MODULE_CONFIG
#include <cstdint>

const auto INITIAL_HAS_TEMP_CHANGED			  = true;
const auto INITIAL_TEMP						  = 0.0f;
const auto INITIAL_HUMIDITY					  = 0.0f;
const auto INITIAL_FAN_SPEED				  = 33;
const auto INITIAL_FAN_RPM					  = 0;
const auto INITIAL_TEMPERATURE_THRESHOLD	  = 25.0f;
const auto INITIAL_IS_FAN_MANUAL_MODE_ENABLED = false;

const auto PULSES_PER_REVOLUTION = 2;
const auto MAX_RPM				 = 7500;

struct DHTConfig
{
	const uint8_t SIGNAL_PIN = 22;
};

struct FanConfig
{
	const uint8_t PWM_PIN  = 17;
	const uint8_t TACH_PIN = 33;
};

#endif
