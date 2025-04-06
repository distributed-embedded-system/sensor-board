#include "core/temperature/TempModule.h"
#include "utils/Time.h"
#include <Arduino.h>

TempModule::TempModule()
	: m_stamp{millis()}, m_dht_driver{std::make_unique<DHTDriver>()},
	  m_fan_driver{std::make_unique<FanDriver>()}
{
	Serial.print("INITTING TEMP MODULE: ");
	Serial.print("READ TEMP: ");
	Serial.println(m_dht_driver->readTemperature());
	Serial.print("READ HUMIDITY: ");
	Serial.println(m_dht_driver->readHumidity());

	m_humidity	  = m_dht_driver->readHumidity();
	m_temperature = m_dht_driver->readTemperature();
}

TempModule::~TempModule() = default;

void TempModule::update()
{
	/**
	 * UPDATE EVERY 2 SECONDS
	 * m_temperature
	 * m_humidity
	 *
	 * react to the temperature change if manual_mode is disabled and temp has reached threshold
	 */

	// Only execute every 2 seconds
	if (millis() - m_stamp <= Time::ONE_SECOND * 2)
		return;

	if (m_temperature == m_dht_driver->readTemperature() &&
		m_humidity == m_dht_driver->readHumidity())
		return;

	// only update the temperature if there is a change from the last recorded state
	// toggle the has changed flag to later use when checking whether or not to fire a message to
	// Control Module
	m_has_changed = true;

	m_humidity	  = m_dht_driver->readHumidity();
	m_temperature = m_dht_driver->readTemperature();

	if (m_is_manual_mode_enabled)
	{
		m_stamp = millis();
		return;
	}

	// if in auto mode set fan speed based on current temperature
	const float MAX_DELTA = 10.0; // max delta over threshold for max fan speed
	int			speed	  = 0;

	if (m_temperature > m_temp_threshold)
	{
		float delta	 = m_temperature - m_temp_threshold;
		float factor = std::min(delta / MAX_DELTA, 1.0f); // Clamp between 0 and 1
		speed		 = static_cast<int>(factor * 100);	  // Scale fan speed 0-100%
	}

	m_fan_speed = speed;
	m_fan_driver->setSpeed(m_fan_speed);

	m_stamp = millis();
}

int	  TempModule::getFanSpeed() { return m_fan_speed; }
float TempModule::getTemp() { return m_temperature; }
float TempModule::getHumidity() { return m_humidity; }
bool  TempModule::getHasChanged() { return m_has_changed; }
bool  TempModule::getIsManualModeEnabled() { return m_is_manual_mode_enabled; }

void TempModule::setHasChanged(bool hasChanged) { m_has_changed = hasChanged; }
void TempModule::setFanSpeed(int fanSpeed)
{
	m_fan_speed = fanSpeed;
	m_fan_driver->setSpeed(m_fan_speed);
}
void TempModule::setTempThreshold(float tempThreshold) { m_temp_threshold = tempThreshold; }
void TempModule::setIsManualModeEnabled(bool isManualModeEnabled)
{
	Serial.print("TEMP MODULE IS MANUAL MODE ENABLED ");
	Serial.println(isManualModeEnabled);
	m_is_manual_mode_enabled = isManualModeEnabled;
}
