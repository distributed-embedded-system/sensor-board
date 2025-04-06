#ifndef CORE
#define CORE

#include "config/Core.h"
#include "core/light/LightModule.h"
#include "core/temperature/TempModule.h"
#include <cstdint>
#include <memory>

class ESPNowBus;

using esp_now_bus_up  = std::unique_ptr<ESPNowBus>;
using temp_module_up  = std::unique_ptr<TempModule>;
using light_module_up = std::unique_ptr<LightModule>;

class Core
{
	// private members
private:
	bool			m_is_mock_enabled;
	unsigned long	m_stamp;
	esp_now_bus_up	m_esp_now;
	temp_module_up	m_temp_module;
	light_module_up m_light_module;

	// public methods
public:
	Core(bool isMockEnabled);
	~Core();
	void update();
	// private methods
private:
	void init_esp_now();
	int32_t getWiFiChannel(const char *ssid);
	void setup_on_receive_callbacks();
};

#endif