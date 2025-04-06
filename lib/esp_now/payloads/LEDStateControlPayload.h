#ifndef LED_STATE_CONTROL_PAYLOAD
#define LED_STATE_CONTROL_PAYLOAD

#include <sstream>
#include <string>

class LEDStateControlMsgPayload
{
private:
	bool m_isEnabled;

public:
	// Constructor from boolean value
	LEDStateControlMsgPayload(bool isEnabled) : m_isEnabled(isEnabled) {}

	// Constructor from string
	LEDStateControlMsgPayload(const std::string& raw_data)
	{
		std::istringstream(raw_data) >> m_isEnabled;
	}

	bool getIsLEDEnabled() const { return m_isEnabled; }

	std::string to_string() const { return m_isEnabled ? "1" : "0"; }
};

#endif
