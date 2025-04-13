
#include "Core.h"
#include "../lib/esp_now/payloads/DHTReadingsPayload.h"
#include "../lib/esp_now/payloads/FanManualControlPayload.h"
#include "../lib/esp_now/payloads/FanRPMReadingPayload.h"
#include "../lib/esp_now/payloads/FanSpeedControlPayload.h"
#include "../lib/esp_now/payloads/LDRReadingPayload.h"
#include "../lib/esp_now/payloads/LEDManualControlPayload.h"
#include "../lib/esp_now/payloads/LEDStateControlPayload.h"
#include "../lib/esp_now/payloads/TempThresholdControlPayload.h"
#include "ArduinoJson.h"
#include "ESPNowBus.h"
#include "WiFi.h"
#include "utils/Time.h"
#include <Arduino.h>

Core::Core()
	// initialize the class member field in order to be ready by the time we reach the constructor
	// and call init_server as the function uses m_server
	// "{}" are used instead of "()" because we use newer C++ standard
	: m_temp_stamp{millis()}, m_light_stamp{millis()}, m_esp_now{std::make_unique<ESPNowBus>()},
	  m_temp_module{std::make_unique<TempModule>()}, m_light_module{std::make_unique<LightModule>()}
{
	Serial.println("Core initialized.");
	Serial.println("Initializing ESP Now...");

	WiFi.disconnect(); // Ensure clean init
	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);

	init_esp_now();
};

// use default destructor
Core::~Core() = default;

void Core::update()
{
	m_temp_module->update();
	m_light_module->update();

	// stop flooding with calls because we cannot read more than once every 2 secs anyway
	// if (millis() - m_stamp <= Time::ONE_SECOND * 2)
	// 	return;

	unsigned long now = millis();

	if (now - m_temp_stamp >= 2 * Time::ONE_SECOND && m_temp_module->getHasChanged())
	{
		// send new temp data to main board
		DHTReadingsMsgPayload tempPayload(m_temp_module->getTemp(), m_temp_module->getHumidity());
		m_esp_now->send_message(
			MAIN_BOARD_MAC_ADDRESS, ESPNowMessageTypes::TEMP_CHANGED, tempPayload.to_string());

		FanRPMReadingMsgPayload fanPayload(m_temp_module->getFanRPM());
		m_esp_now->send_message(
			MAIN_BOARD_MAC_ADDRESS, ESPNowMessageTypes::FAN_RPM_CHANGED, fanPayload.to_string());

		m_temp_module->setHasChanged(false);

		m_temp_stamp = millis();
	}

	if (now - m_light_stamp >= Time::ONE_SECOND && m_light_module->getHasChanged())
	{
		// send new light data to main board
		Serial.print("LIGHT MODULE READING: ");
		Serial.println(m_light_module->getIsDark());

		LDRReadingMsgPayload payload(m_light_module->getIsDark());

		m_esp_now->send_message(
			MAIN_BOARD_MAC_ADDRESS, ESPNowMessageTypes::IS_DARK_CHANGED, payload.to_string());
		m_light_module->setHasChanged(false);

		m_light_stamp = millis();
	}
}

void Core::init_esp_now()
{
	m_esp_now->init();
	m_esp_now->register_peer(MAIN_BOARD_MAC_ADDRESS);
	m_esp_now->get_mac_address();
	setup_on_receive_callbacks();
}

// All are triggered by the user
void Core::setup_on_receive_callbacks()
{
	// TEMPERATURE

	// TOGGLE MANUAL MODE (TEMP)
	m_esp_now->register_on_receive_callback(
		ESPNowMessageTypes::MANUAL_FAN_CONTROL_CHANGE,
		[tempModule = m_temp_module.get(), espNow = m_esp_now.get()](uint8_t* mac_address,
																	 const ESPNowMessage& message)
		{
			Serial.print("MANUAL MODE (FAN) CHANGE MESSAGE: ");
			Serial.println(message.payload);

			std::string rawData(message.payload);

			FanManualControlMsgPayload payload(rawData);

			tempModule->setIsManualModeEnabled(payload.getIsManualModeEnabled());

			espNow->send_message(MAIN_BOARD_MAC_ADDRESS,
								 ESPNowMessageTypes::ACK_MANUAL_FAN_CONTROL_CHANGE,
								 payload.to_string());
		});

	// CHANGE TEMPERATURE THREHSHOLD
	m_esp_now->register_on_receive_callback(
		ESPNowMessageTypes::TEMP_THRESHOLD_CHANGE,
		[tempModule = m_temp_module.get(), espNow = m_esp_now.get()](uint8_t* mac_address,
																	 const ESPNowMessage& message)
		{
			Serial.print("TEMP THRESHOLD CHANGE MESSAGE: ");
			Serial.println(message.payload);

			std::string rawData(message.payload);

			TempThresholdControlPayload payload(rawData);

			tempModule->setTempThreshold(payload.getTempThreshold());

			espNow->send_message(MAIN_BOARD_MAC_ADDRESS,
								 ESPNowMessageTypes::ACK_TEMP_THRESHOLD_CHANGE,
								 payload.to_string());
		});

	// CHANGE FAN SPEED
	m_esp_now->register_on_receive_callback(
		ESPNowMessageTypes::FAN_SPEED_CHANGE,
		[tempModule = m_temp_module.get(), espNow = m_esp_now.get()](uint8_t* mac_address,
																	 const ESPNowMessage& message)
		{
			Serial.print("FAN SPEED CHANGE MESSAGE: ");
			Serial.println(message.payload);

			// if manual mode is disabled return the current speed
			if (!tempModule->getIsManualModeEnabled())
			{

				FanSpeedControlMsgPayload payload(tempModule->getFanSpeed());
				return espNow->send_message(MAIN_BOARD_MAC_ADDRESS,

											ESPNowMessageTypes::ACK_FAN_SPEED_CHANGED,
											payload.to_string());
			}

			std::string rawData(message.payload);

			FanSpeedControlMsgPayload payload(rawData);

			tempModule->setFanSpeed(payload.getFanSpeed());

			// send an esp now message with new fan speed to mainBoard
			espNow->send_message(MAIN_BOARD_MAC_ADDRESS,
								 ESPNowMessageTypes::ACK_FAN_SPEED_CHANGED,
								 payload.to_string());
		});

	// LIGHT

	// MANUAL MODE (LIGHT) STATE CHANGE HANDLER
	m_esp_now->register_on_receive_callback(
		ESPNowMessageTypes::MANUAL_LED_CONTROL_CHANGE,
		[lightModule = m_light_module.get(), espNow = m_esp_now.get()](uint8_t* mac_address,
																	   const ESPNowMessage& message)
		{
			Serial.print("MANUAL MODE (LED) CHANGE MESSAGE: ");
			Serial.println(message.payload);

			std::string rawData(message.payload);

			LEDManualControlMsgPayload payload(rawData);

			lightModule->setIsManualModeEnabled(payload.getIsManualModeEnabled());

			// send an esp now message with new isManualModeStatus to mainBoard
			espNow->send_message(MAIN_BOARD_MAC_ADDRESS,
								 ESPNowMessageTypes::ACK_MANUAL_LED_CONTROL_CHANGED,
								 payload.to_string());

			// if manual mode is disabled make the LED state respond to the current reading of the
			// LDR
			if (lightModule->getIsManualModeEnabled())
				return;

			bool isDark = lightModule->getIsDark();
			lightModule->setLEDState(isDark);
			LEDStateControlMsgPayload ledPayload(isDark);
			espNow->send_message(
				MAIN_BOARD_MAC_ADDRESS, ACK_LED_STATE_CHANGED, ledPayload.to_string());
		});

	// LED STATE CHANGE HANDLER
	m_esp_now->register_on_receive_callback(
		ESPNowMessageTypes::LED_STATE_CHANGE,
		[lightModule = m_light_module.get(), espNow = m_esp_now.get()](uint8_t* mac_address,
																	   const ESPNowMessage& message)
		{
			Serial.print("LED STATE CHANGE MESSAGE: ");
			Serial.println(message.payload);

			// if manual mode is disabled ignore (maybe even throw an error)
			if (!lightModule->getIsManualModeEnabled())
			{
				LEDStateControlMsgPayload payload(lightModule->getLEDState());
				return espNow->send_message(MAIN_BOARD_MAC_ADDRESS,

											ESPNowMessageTypes::ACK_LED_STATE_CHANGED,
											payload.to_string());
			}

			std::string rawData(message.payload);

			LEDStateControlMsgPayload payload(rawData);

			lightModule->setLEDState(payload.getIsLEDEnabled());

			// send an esp now message with new led state mainBoard
			espNow->send_message(MAIN_BOARD_MAC_ADDRESS,
								 ESPNowMessageTypes::ACK_LED_STATE_CHANGED,
								 payload.to_string());
		});
}
