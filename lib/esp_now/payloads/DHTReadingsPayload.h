#ifndef DHT_READINGS_PAYLOAD
#define DHT_READINGS_PAYLOAD

#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

class DHTReadingsMsgPayload
{
private:
	float m_temp;
	float m_humidity;

public:
	// Construct from two float values
	DHTReadingsMsgPayload(float temp, float humidity) : m_temp{temp}, m_humidity{humidity} {}

	// Construct from a comma-separated string
	DHTReadingsMsgPayload(const std::string& raw_data)
	{
		std::istringstream iss(raw_data);
		char			   comma; // To discard the comma
		iss >> m_temp >> comma >> m_humidity;
	}

	// Convert to string format "temp,humidity"
	std::string to_string() const
	{
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << m_temp << "," << m_humidity;
		return oss.str();
	}

	float getTemp() const { return m_temp; }
	float getHumidity() const { return m_humidity; }
};

#endif
