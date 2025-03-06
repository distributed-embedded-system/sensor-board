#include "JSON.h"

class JSONArray
{
private:
	std::stringstream m_stream;

public:
	JSONArray() { m_stream << "["; }

	JSONArray& push(const std::string& value)
	{
		m_stream << "\"" << value << "\"" << ',';
		return *this;
	}

	JSONArray& push(std::uint8_t value)
	{
		m_stream << static_cast<int>(value) << ',';
		return *this;
	}

	JSONArray& push_object(const std::string& stringified_object)
	{
		m_stream << stringified_object << ',';
		return *this;
	}

	JSONArray& push(JSONArray& json_array)
	{
		m_stream << json_array.stringify() << ",";
		return *this;
	}

	std::string stringify() const
	{
		std::string data			  = m_stream.str();
		std::string stringified_array = data.substr(0, data.size() - 1);

		stringified_array += "]";

		return stringified_array;
	}
};

class JSONObject
{
private:
	std::stringstream m_stream;

public:
	JSONObject() { m_stream << "{"; }

	JSONObject& add_entry(std::uint8_t key, std::uint8_t value)
	{
		m_stream << "\"" << static_cast<int>(key) << "\": " << static_cast<int>(value) << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, std::uint8_t value)
	{
		m_stream << "\"" << key << "\": " << static_cast<int>(value) << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, std::uint32_t value)
	{
		m_stream << "\"" << key << "\": " << value << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, int value)
	{
		m_stream << "\"" << key << "\": " << value << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, unsigned long value)
	{
		m_stream << "\"" << key << "\": " << value << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, const std::string& value)
	{
		m_stream << "\"" << key << "\": \"" << value << "\",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, bool value)
	{
		m_stream << "\"" << key << "\": " << (value ? "true" : "false") << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, const std::vector<std::uint8_t>& numbers)
	{
		JSONArray json_array;
		for (std::uint8_t number : numbers)
		{
			json_array.push(number);
		}
		add_entry(key, json_array);
		return *this;
	}

	JSONObject& add_entry(const std::string& key, const std::vector<std::string>& strings)
	{
		JSONArray json_array;
		for (const std::string& str : strings)
		{
			json_array.push(str);
		}
		add_entry(key, json_array);
		return *this;
	}

	JSONObject& add_entry(const std::string& key, JSONObject& object)
	{
		m_stream << "\"" << key << "\": " << object.stringify() << ",";
		return *this;
	}

	JSONObject& add_entry(const std::string& key, JSONArray& json_array)
	{
		m_stream << "\"" << key << "\": " << json_array.stringify() << ",";
		return *this;
	}

	std::string stringify() const
	{
		std::string data			 = m_stream.str();
		std::string stringified_json = data.substr(0, data.size() - 1);

		stringified_json += "}";

		return stringified_json;
	}
};