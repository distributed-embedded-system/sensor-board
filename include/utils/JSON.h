#ifndef JSON_UTIL
#define JSON_UTIL

#include <sstream>
#include <string>
#include <vector>

class JSONArray
{
private:
	std::stringstream m_stream;

public:
	JSONArray();

	JSONArray& push(const std::string& value);
	JSONArray& push(std::uint8_t value);
	JSONArray& push_object(const std::string& stringified_object);
	JSONArray& push(JSONArray& json_array);

	std::string stringify() const;
};

class JSONObject
{
private:
	std::stringstream m_stream;

public:
	JSONObject();

	JSONObject& add_entry(std::uint8_t key, std::uint8_t value);
	JSONObject& add_entry(const std::string& key, std::uint8_t value);
	JSONObject& add_entry(const std::string& key, std::uint32_t value);
	JSONObject& add_entry(const std::string& key, int value);
	JSONObject& add_entry(const std::string& key, unsigned long value);
	JSONObject& add_entry(const std::string& key, const std::string& value);
	JSONObject& add_entry(const std::string& key, bool value);
	JSONObject& add_entry(const std::string& key, const std::vector<std::uint8_t>& numbers);
	JSONObject& add_entry(const std::string& key, const std::vector<std::string>& strings);
	JSONObject& add_entry(const std::string& key, JSONObject& object);
	JSONObject& add_entry(const std::string& key, JSONArray& json_array);

	std::string stringify() const;
};

#endif // JSON_UTIL
