#ifndef FAN_MANUAL_CONTROL_PAYLOAD
#define FAN_MANUAL_CONTROL_PAYLOAD

#include <sstream>
#include <string>

class FanManualControlMsgPayload
{
private:
	bool m_is_manual_mode_enabled;

public:
	// Constructor from boolean value
	FanManualControlMsgPayload(bool is_manual_mode_enabled)
		: m_is_manual_mode_enabled(is_manual_mode_enabled)
	{
	}

	// Constructor from string
	FanManualControlMsgPayload(const std::string& raw_data)
	{
		std::istringstream(raw_data) >> m_is_manual_mode_enabled;
	}

	bool getIsManualModeEnabled() const { return m_is_manual_mode_enabled; }

	std::string to_string() const { return m_is_manual_mode_enabled ? "1" : "0"; }
};

#endif
