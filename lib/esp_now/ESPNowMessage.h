#ifndef ESP_NOW_MESSAGE
#define ESP_NOW_MESSAGE

#include <cstdint>
#include <string>

#include "ESPNowMessageTypes.h"

typedef struct ESPNowMessage
{
	unsigned long	   id{0};
	ESPNowMessageTypes type{ESPNowMessageTypes::UNDEFINED_MESSAGE};
	char			   payload[200]{"undefined_payload"};

} ESPNowMessage;

#endif