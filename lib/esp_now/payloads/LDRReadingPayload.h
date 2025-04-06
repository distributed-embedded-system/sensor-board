#ifndef LDR_READING_PAYLOAD
#define LDR_READING_PAYLOAD

#include <string>

class LDRReadingMsgPayload
{
private:
	bool m_is_dark;

public:
	// Construct from boolean value
	LDRReadingMsgPayload(bool isDark) : m_is_dark{isDark} {}

	// Construct from string
	LDRReadingMsgPayload(const std::string& raw_data) { std::istringstream(raw_data) >> m_is_dark; }

	bool getIsDark() const { return m_is_dark; }

	std::string to_string() const { return m_is_dark ? "1" : "0"; }
};

#endif
