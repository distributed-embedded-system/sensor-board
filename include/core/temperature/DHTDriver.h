#ifndef TEMP_DRIVER
#define TEMP_DRIVER

#include "DHT.h"
#include "config/TempModule.h"

#define DHT_TYPE DHT22

class DHTDriver
{
private:
	unsigned long m_stamp;
	DHT			  m_dht_sensor;

public:
	DHTDriver();
	~DHTDriver();
	float readTemperature();
	float readHumidity();
};

#endif
