#ifndef ESP_NOW_MOCK_RESPONSE
#define ESP_NOW_MOCK_RESPONSE

#include "ESPNowMessageTypes.h"
#include <Arduino.h>

struct MockResponse
{
	ESPNowMessageTypes type;
	std::string		   payload;
};

//(send)
// Define mock responses for each type directly in the map

const std::unordered_map<ESPNowMessageTypes, MockResponse> __ESP_MOCK_RESPONSES = {
	// CONTROL BOARD
	// here they are identical because there is no request in order to receive that message
	{ESPNowMessageTypes::TEMP_CHANGED,
	 {ESPNowMessageTypes::TEMP_CHANGED, "24.50,45.3"}}, // TEMP + HUMIDITY
	{ESPNowMessageTypes::IS_DARK_CHANGED, {ESPNowMessageTypes::IS_DARK_CHANGED, "1"}},

	// SENSOR BOARD
	{ESPNowMessageTypes::MANUAL_LED_CONTROL_CHANGE,
	 {ESPNowMessageTypes::MANUAL_LED_CONTROL_CHANGE, "1"}},
	{ESPNowMessageTypes::LED_STATE_CHANGE, {ESPNowMessageTypes::LED_STATE_CHANGE, "1"}},

	{ESPNowMessageTypes::TEMP_THRESHOLD_CHANGE,
	 {ESPNowMessageTypes::TEMP_THRESHOLD_CHANGE, "21.50"}},

	{ESPNowMessageTypes::MANUAL_FAN_CONTROL_CHANGE,
	 {ESPNowMessageTypes::MANUAL_FAN_CONTROL_CHANGE, "1"}},

	{ESPNowMessageTypes::FAN_SPEED_CHANGE, {ESPNowMessageTypes::FAN_SPEED_CHANGE, "100"}},
};

#endif