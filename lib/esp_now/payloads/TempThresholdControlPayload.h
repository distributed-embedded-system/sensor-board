#ifndef FAN_THRESHOLD_CONTROL_PAYLOAD
#define FAN_THRESHOLD_CONTROL_PAYLOAD

#include "utils/validators.h"
#include <algorithm> // For std::all_of
#include <cctype>
#include <cstdio>
#include <cstdlib> // For std::stof
#include <string>

class TempThresholdControlPayload
{
private:
	float __INITIAL_TEMPERATURE_THRESHOLD = 25.0f;
	float m_temp_threshold; // in Celsius

public:
	// Constructor from float value
	TempThresholdControlPayload(float temp_threshold) : m_temp_threshold(temp_threshold) {}

	// Constructor from string
	TempThresholdControlPayload(const std::string& raw_data)
	{
		float temp;
		m_temp_threshold = parseFloat(raw_data, temp) ? temp : __INITIAL_TEMPERATURE_THRESHOLD;
	}

	float getTempThreshold() const { return m_temp_threshold; }

	std::string to_string() const
	{
		char buffer[7];
		sprintf(buffer, "%.2f", m_temp_threshold);
		return std::string(buffer);
	}
};

#endif
