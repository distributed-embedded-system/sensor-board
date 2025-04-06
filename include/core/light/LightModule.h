#ifndef LIGHT_MODULE
#define LIGHT_MODULE

#include "config/LightModule.h"
#include "core/light/LDRDriver.h"
#include "core/light/LEDDriver.h"
#include <memory>

using ldr_driver_up = std::unique_ptr<LDRDriver>;
using led_driver_up = std::unique_ptr<LEDDriver>;

class LightModule
{
	// private members
private:
	unsigned long m_stamp;

	bool m_has_changed			  = INITIAL_HAS_IS_DARK_CHANGED;
	bool m_is_dark				  = INITIAL_IS_DARK;
	bool m_is_led_enabled		  = INITIAL_IS_LED_ENABLED;
	bool m_is_manual_mode_enabled = INITIAL_IS_LED_MANUAL_MODE_ENABLED;

	ldr_driver_up m_ldr_driver;
	led_driver_up m_led_driver;

	// public methods
public:
	LightModule();
	~LightModule();

	void update();

	bool getIsDark();
	bool getLEDState();
	bool getHasChanged();
	bool getIsManualModeEnabled();
	void setHasChanged(bool hasChanged);

	void setLEDState(bool isEnabled);
	void setIsManualModeEnabled(bool isManualModeEnabled);

	// private methods
private:
};

#endif