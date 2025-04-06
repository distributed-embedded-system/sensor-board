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
	// {ESPNowMessageTypes::ACK_TEMP_CHANGED, {ESPNowMessageTypes::ACK_TEMP_CHANGED, NULL}},

	{ESPNowMessageTypes::IS_DARK_CHANGED, {ESPNowMessageTypes::IS_DARK_CHANGED, "1"}},
	// {ESPNowMessageTypes::ACK_IS_DARK_CHANGED, {ESPNowMessageTypes::IS_DARK_CHANGED, NULL}},

	// SENSOR BOARD
	{ESPNowMessageTypes::FAN_SPEED_CHANGE, {ESPNowMessageTypes::ACK_FAN_SPEED_CHANGED, "100"}},
	{ESPNowMessageTypes::ACK_FAN_SPEED_CHANGED, {ESPNowMessageTypes::ACK_FAN_SPEED_CHANGED, "100"}},

	{ESPNowMessageTypes::TEMP_THRESHOLD_CHANGE,
	 {ESPNowMessageTypes::TEMP_THRESHOLD_CHANGE, "21.50"}},
	{ESPNowMessageTypes::ACK_TEMP_THRESHOLD_CHANGE,
	 {ESPNowMessageTypes::ACK_TEMP_THRESHOLD_CHANGE, "21.50"}},

	{ESPNowMessageTypes::MANUAL_FAN_CONTROL_CHANGE,
	 {ESPNowMessageTypes::MANUAL_FAN_CONTROL_CHANGE, "1"}},
	{ESPNowMessageTypes::ACK_MANUAL_FAN_CONTROL_CHANGE,
	 {ESPNowMessageTypes::ACK_MANUAL_FAN_CONTROL_CHANGE, "1,80"}}, // is_manual_mode_enabled, fan_speed

		// message								//response to that message
	{ESPNowMessageTypes::LED_STATE_CHANGE, {ESPNowMessageTypes::ACK_LED_STATE_CHANGED, "1"}},
	{ESPNowMessageTypes::ACK_LED_STATE_CHANGED, {ESPNowMessageTypes::ACK_LED_STATE_CHANGED, "1"}}, // is_led_enabled

	{ESPNowMessageTypes::MANUAL_LED_CONTROL_CHANGE,
	 {ESPNowMessageTypes::MANUAL_LED_CONTROL_CHANGE, "1"}},
	{ESPNowMessageTypes::ACK_MANUAL_LED_CONTROL_CHANGED,
	 {ESPNowMessageTypes::ACK_MANUAL_LED_CONTROL_CHANGED, "1,0"}}}; // is_manual_mode_enabled, is_led_enabled

#endif