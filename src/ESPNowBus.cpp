#include "ESPNowBus.h"
#include "config/Core.h"
#include <WiFi.h>

// why is it defined outside of the class? - because the low level
// esp_now_register_recv func is a lambda that does not have access
// to the this

// static - variable is only visible in this translation unit (.cpp)

void ESPNowBus::init()
{
	// Init ESP-NOW
	if (esp_now_init() != ESP_OK)
	{
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// esp_now_set_pmk(PMK);

	// Register callback middleware (ESP Now supports one)
	register_on_receive_callback_internal();

	Serial.println("ESP-NOW Initialized");

	m_message = ESPNowMessage{};
}

int ESPNowBus::register_peer(uint8_t* mac_addr)
{
	esp_now_peer_info_t peerInfo{};

	memcpy(peerInfo.peer_addr, mac_addr, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;
	// memcpy(peerInfo.lmk, LMK, ESP_NOW_KEY_LEN);

	int status = esp_now_add_peer(&peerInfo);
	if (status != ESP_OK)
	{
		Serial.println("Failed to add peer");
	}

	return status;
}

int ESPNowBus::delete_peer(uint8_t* mac_addr)
{
	int status = esp_now_del_peer(mac_addr);
	return status;
}

void ESPNowBus::register_on_receive_callback(ESPNowMessageTypes			  type,
											 const ESPNowMessageCallback& callback)
{
	__ESP_NOW_MESSAGE_CALLBACKS.insert({type, callback});
}

void ESPNowBus::register_on_receive_callback_internal()
{
	esp_now_register_recv_cb(
		[](const uint8_t* mac_addr, const uint8_t* incomingData, int length)
		{
			memcpy(&__ESP_NOW_MESSAGE, incomingData, sizeof(__ESP_NOW_MESSAGE));

			// Serial.println("");
			// Serial.println("--- RECEIVING ---");
			// Serial.print("ID: ");
			// Serial.println(__ESP_NOW_MESSAGE.id);
			// Serial.print("Type: ");
			// Serial.println(__ESP_NOW_MESSAGE.type);
			// Serial.print("Payload: ");
			// Serial.println(__ESP_NOW_MESSAGE.payload);

			auto iterator = __ESP_NOW_MESSAGE_CALLBACKS.find(__ESP_NOW_MESSAGE.type);
			if (iterator ==
				__ESP_NOW_MESSAGE_CALLBACKS.end()) // if callback not found based on type return
				return;

			// return the value, in our case is the message handler function.
			const ESPNowMessage& message = __ESP_NOW_MESSAGE;
			iterator->second(const_cast<uint8_t*>(mac_addr), message);
		});
}

void ESPNowBus::send_message(uint8_t* mac_addr, ESPNowMessageTypes type, std::string payload)
{
	if (m_is_mock_enabled)
	{
		// Find the mock response for the given message type
		auto mockResponseIter = __ESP_MOCK_RESPONSES.find(type);

		// Check if the mock response exists for this type
		if (mockResponseIter != __ESP_MOCK_RESPONSES.end())
		{
			// Retrieve the mock response
			const MockResponse& mockResponse = mockResponseIter->second;

			// Create a mock ESPNowMessage
			ESPNowMessage message = {
				millis(), mockResponse.type, ""}; // convert std::string to char
			strcpy(message.payload, mockResponse.payload.c_str());

			// Find the registered callback for this message type
			auto iterator = __ESP_NOW_MESSAGE_CALLBACKS.find(message.type);
			if (iterator != __ESP_NOW_MESSAGE_CALLBACKS.end())
			{
				// Call the registered callback with the mock message
				iterator->second(const_cast<uint8_t*>(SENSOR_BOARD_MAC_ADDRESS), message);
			}
		}

		return;
	}

	m_message.id   = millis();
	m_message.type = type;
	strcpy(m_message.payload, payload.c_str());

	/**
	 * IF DEBUG MODE
	 */
	// Serial.println("");
	// Serial.println("--- SENDING ---");
	// Serial.print("ID: ");
	// Serial.println(m_message.id);
	// Serial.print("Type: ");
	// Serial.println(m_message.type);
	// Serial.print("Payload: ");
	// Serial.println(m_message.payload);

	// __MESSAGE_VECTOR.push_back(m_message);

	esp_now_send(mac_addr, (uint8_t*)&m_message, sizeof(m_message));
}

void ESPNowBus::mock_on_receive(ESPNowMessageTypes type)
{
	if (!m_is_mock_enabled)
		return;

	// Find the mock response for the given message type
	auto mockResponseIter = __ESP_MOCK_RESPONSES.find(type);

	// Check if the mock response exists for this type
	if (mockResponseIter == __ESP_MOCK_RESPONSES.end())
		return;

	// Retrieve the mock response
	const MockResponse& mockResponse = mockResponseIter->second;

	// Create a mock ESPNowMessage
	ESPNowMessage message = {millis(), mockResponse.type, ""};
	strcpy(message.payload, mockResponse.payload.c_str());

	// Find the registered callback for this message type
	auto iterator = __ESP_NOW_MESSAGE_CALLBACKS.find(message.type);
	if (iterator != __ESP_NOW_MESSAGE_CALLBACKS.end())
	{
		// Call the registered callback with the address of the sender (SENSOR BOARD)
		iterator->second(SENSOR_BOARD_MAC_ADDRESS, message);
	}
}

void ESPNowBus::get_mac_address()
{

	uint8_t	  baseMac[6];
	esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
	if (ret == ESP_OK)
	{
		Serial.printf("MAC ADDRESS (SENSOR BOARD): %02x:%02x:%02x:%02x:%02x:%02x\n",
					  baseMac[0],
					  baseMac[1],
					  baseMac[2],
					  baseMac[3],
					  baseMac[4],
					  baseMac[5]);
	}
	else
	{
		Serial.println("Failed to read MAC address");
	}
}