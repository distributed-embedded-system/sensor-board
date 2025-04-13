#include "core/light/LightModule.h"
#include "utils/Time.h"
#include <Arduino.h>

LightModule::LightModule()
	: m_stamp{millis()}, m_ldr_driver{std::make_unique<LDRDriver>(LDRDriver())},
	  m_led_driver{std::make_unique<LEDDriver>(LEDDriver())}
{
}

LightModule::~LightModule() = default;

void LightModule::update()
{
	bool currentReading = m_ldr_driver->readIsDark();

	// If state has changed, start debounce timer
	if (currentReading != m_last_reading)
	{
		m_last_debounce_time = millis();
		m_last_reading		 = currentReading;
	}

	// Only update state if the reading has been stable for 300ms
	if ((millis() - m_last_debounce_time) < 300 || currentReading == m_is_dark)
		return;

	m_is_dark	  = currentReading;
	m_has_changed = true;

	if (!m_is_manual_mode_enabled)
	{
		m_is_led_enabled = m_is_dark;
		m_led_driver->setLEDState(m_is_led_enabled);
	}
}

// Get
bool LightModule::getHasChanged() { return m_has_changed; }

bool LightModule::getIsDark() { return m_is_dark; }

bool LightModule::getLEDState() { return m_is_led_enabled; }

bool LightModule::getIsManualModeEnabled() { return m_is_manual_mode_enabled; }

// Set
void LightModule::setHasChanged(bool hasChanged) { m_has_changed = hasChanged; }

void LightModule::setLEDState(bool isEnabled)
{
	Serial.print("Setting LED state to: ");
	Serial.println(isEnabled ? "ON" : "OFF");

	m_is_led_enabled = isEnabled;
	m_led_driver->setLEDState(m_is_led_enabled);
}

void LightModule::setIsManualModeEnabled(bool isManualModeEnabled)
{
	Serial.print("LIGHT MODULE IS MANUAL MODE ENABLED ");
	Serial.println(isManualModeEnabled);
	m_is_manual_mode_enabled = isManualModeEnabled;
}
