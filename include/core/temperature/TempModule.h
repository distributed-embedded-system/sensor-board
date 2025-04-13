#ifndef TEMP_MODULE
#define TEMP_MODULE

#include "config/TempModule.h"
#include "core/temperature/DHTDriver.h"
#include "core/temperature/FanDriver.h"
#include <cstdint>
#include <memory>

using dht_driver_up = std::unique_ptr<DHTDriver>;
using fan_driver_up = std::unique_ptr<FanDriver>;

class TempModule
{
	// private members
private:
	unsigned long m_stamp;

	bool	m_has_changed			 = INITIAL_HAS_TEMP_CHANGED;
	float	m_humidity				 = INITIAL_HUMIDITY;
	float	m_temperature			 = INITIAL_TEMP;
	float	m_temp_threshold		 = INITIAL_TEMPERATURE_THRESHOLD;
	uint8_t m_fan_speed				 = INITIAL_FAN_SPEED;
	int		m_fan_rpm				 = INITIAL_FAN_RPM;
	bool	m_is_manual_mode_enabled = INITIAL_IS_FAN_MANUAL_MODE_ENABLED;

	dht_driver_up m_dht_driver;
	fan_driver_up m_fan_driver;

	// public methods
public:
	TempModule();
	~TempModule();

	void update();

	bool  getHasChanged();
	float getTemp();
	float getHumidity();
	void  setHasChanged(bool hasChanged);
	bool  getIsManualModeEnabled();
	int	  getFanRPM();
	int	  getFanSpeed();
	void  setFanSpeed(int fanSpeed);
	void  setTempThreshold(float tempThreshold);
	void  setIsManualModeEnabled(bool isManualModeEnabled);
	// private methods
private:
};

#endif
