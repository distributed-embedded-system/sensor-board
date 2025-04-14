#ifndef CORE
#define CORE

#include "ESPNowMessageTypes.h"
#include "config/Core.h"
#include "core/light/LightModule.h"
#include "core/temperature/TempModule.h"
#include <cstdint>
#include <memory>

struct MockStep
{
	ESPNowMessageTypes type;
	std::string		   payload;
	unsigned long	   delay_after_ms;
};

class ESPNowBus;

using esp_now_bus_up  = std::unique_ptr<ESPNowBus>;
using temp_module_up  = std::unique_ptr<TempModule>;
using light_module_up = std::unique_ptr<LightModule>;

class Core
{
	// private members
private:
	bool			m_is_mock_enabled;
	unsigned long	m_temp_stamp;
	unsigned long	m_light_stamp;
	esp_now_bus_up	m_esp_now;
	temp_module_up	m_temp_module;
	light_module_up m_light_module;

	// mock specific
	std::vector<MockStep> m_mock_steps;
	size_t				  m_current_mock_step	= 0;
	unsigned long		  m_last_mock_step_time = 0;
	bool				  m_mock_initialized	= false;

	// public methods
public:
	Core(const bool is_mock_enabled);
	~Core();
	void update();
	// private methods
private:
	void init_esp_now();
	void setup_on_receive_callbacks();
	void setup_mock_sequence();
};

#endif