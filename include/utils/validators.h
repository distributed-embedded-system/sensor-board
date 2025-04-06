#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <cctype>
#include <sstream>
#include <string>

bool parseFloat(const std::string& str, float& outValue)
{
	char* ending;
	outValue = strtof(str.c_str(), &ending);
	return *ending == '\0'; // Ensure entire string was parsed
}

bool isValidFloat(const std::string& str)
{
	char* ending;
	strtof(str.c_str(), &ending);
	return *ending == '\0'; // Ensure entire string was parsed
}


int parseInt(const std::string& str, int& outValue)
{
	char* ending;
	long  value = strtol(str.c_str(), &ending, 10); // Base 10 for decimal numbers

	// Ensure the entire string is a valid integer
	if (*ending != '\0')
		return false;

	// Ensure it's within the range of `int`
	if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		return false;

	outValue = static_cast<int>(value);
	return true;
}

bool isValidInt(const std::string& str)
{
	char* ending;
	strtol(str.c_str(), &ending, 10);
	return *ending == '\0'; // Ensure entire string is an integer
}


bool isValidBool(const std::string& str)
{
	return str == "0" || str == "1";
}

bool parseBool(const std::string& str, bool& outValue)
{
	if (str == "0")
	{
		outValue = false;
		return true;
	}
	else if (str == "1")
	{
		outValue = true;
		return true;
	}
	return false;
}

#endif