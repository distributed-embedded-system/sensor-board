#include "core/temperature/DHTDriver.h"

DHTDriver::DHTDriver() : m_stamp{millis()}, m_dht_sensor{DHT{DHTConfig{}.SIGNAL_PIN, DHT_TYPE}}
{

	m_dht_sensor.begin();
}

DHTDriver::~DHTDriver() = default;

float DHTDriver::readTemperature()
{
	float readTemp = m_dht_sensor.readTemperature();
	return roundf(readTemp * 100) / 100;
}

float DHTDriver::readHumidity()
{
	float humidity = m_dht_sensor.readHumidity();
	return roundf(humidity * 100) / 100;
}