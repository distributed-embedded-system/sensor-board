#ifndef LIGHT_MODULE_CONFIG
#define LIGHT_MODULE_CONFIG
#include <cstdint>

const auto INITIAL_HAS_IS_DARK_CHANGED		  = true;
const auto INITIAL_IS_DARK					  = false;
const auto INITIAL_IS_LED_ENABLED			  = false;
const auto INITIAL_IS_LED_MANUAL_MODE_ENABLED = false;

struct LDRConfig
{
	const uint8_t SIGNAL_PIN = 16;
};

struct LEDConfig
{
	const uint8_t SIGNAL_PIN = 5;
};

#endif
