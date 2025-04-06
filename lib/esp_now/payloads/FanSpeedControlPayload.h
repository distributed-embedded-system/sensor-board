#ifndef FAN_SPEED_CONTROL_PAYLOAD
#define FAN_SPEED_CONTROL_PAYLOAD

#include "utils/validators.h"
#include <cstdlib>
#include <string>

class FanSpeedControlMsgPayload
{
private:
	float m_fanSpeed;

public:
	// Constructor from integer fan speed
	FanSpeedControlMsgPayload(float speed)
		: m_fanSpeed((speed >= 0 && speed <= 100) ? speed : INITIAL_TEMPERATURE_THRESHOLD)
	{
	}

	// Constructor from string
	FanSpeedControlMsgPayload(const std::string& raw_data)
	{
		int temp;
		int rawSpeed = parseInt(raw_data, temp) ? temp : INITIAL_TEMPERATURE_THRESHOLD;
		m_fanSpeed	 = (rawSpeed >= 0 && rawSpeed <= 100) ? rawSpeed : 0;
	}

	uint8_t getFanSpeed() const { return m_fanSpeed; }

	std::string to_string() const { return std::to_string(m_fanSpeed); }
};

#endif
