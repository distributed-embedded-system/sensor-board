#ifndef FAN_RPM_READING_PAYLOAD
#define FAN_RPM_READING_PAYLOAD

#include "utils/validators.h"
#include <cstdlib>
#include <string>

class FanRPMReadingMsgPayload
{
private:
	int m_fanRPM;

public:
	// Constructor from integer fan speed
	FanRPMReadingMsgPayload(int RPMs) : m_fanRPM(RPMs) {}

	// Constructor from string
	FanRPMReadingMsgPayload(const std::string& raw_data) { parseInt(raw_data, m_fanRPM); }

	int getFanRPM() const { return m_fanRPM; }

	std::string to_string() const { return std::to_string(m_fanRPM); }
};

#endif
