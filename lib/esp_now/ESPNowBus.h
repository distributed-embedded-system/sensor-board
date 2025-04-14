#ifndef ESP_NOW_COMMUNICATION_BUS
#define ESP_NOW_COMMUNICATION_BUS

#include "ESPMockResponses.h"
#include "ESPNowMessage.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <cstdint>
#include <esp_now.h>
#include <esp_wifi.h>

using ESPNowMessageCallback =
	std::function<void(uint8_t* mac_address, const ESPNowMessage& message)>;

class ESPNowBus
{
private:
	bool						m_is_mock_enabled;
	ESPNowMessage				m_message;
	static inline ESPNowMessage __ESP_NOW_MESSAGE{}; // it should be initialized and available in
													 // the main register recv callback
	static inline std::unordered_map<ESPNowMessageTypes, ESPNowMessageCallback>
		__ESP_NOW_MESSAGE_CALLBACKS;

public:
	ESPNowBus(bool isMockEnabled = false) : m_is_mock_enabled{isMockEnabled} {};
	void init();
	void get_mac_address();
	int	 register_peer(uint8_t* mac_addr);
	int	 delete_peer(uint8_t* mac_addr);
	void register_on_receive_callback(ESPNowMessageTypes		   type,
									  const ESPNowMessageCallback& callback);
	void send_message(uint8_t* mac_addr, ESPNowMessageTypes type, std::string payload);
	void mock_on_receive(ESPNowMessageTypes type, const std::string& payload);

private:
	void register_on_receive_callback_internal();
	ESPNowMessage
	create_message_internal(unsigned long id, ESPNowMessageTypes type, const std::string& str);
};

#endif
