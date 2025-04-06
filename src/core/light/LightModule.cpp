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
	// Only execute every 2 seconds
	if (millis() - m_stamp <= Time::ONE_SECOND * 2)
		return;

	if (m_is_dark == m_ldr_driver->readIsDark())
		return;

	// only update the light state if there is a change from the last recorded state
	// toggle the has changed flag to later use when checking whether or not to fire a message to
	// Control Module
	m_has_changed = true;

	m_is_dark = m_ldr_driver->readIsDark();

	if (m_is_manual_mode_enabled)
	{
		m_stamp = millis();
		return;
	}

	m_is_led_enabled = m_is_dark;
	m_led_driver->setLEDState(m_is_led_enabled);

	m_stamp = millis();
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
