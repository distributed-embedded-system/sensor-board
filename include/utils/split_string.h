#ifndef SPLIT_STRING_UTIL
#define SPLIT_STRING_UTIL

#include <sstream>
#include <string>
#include <vector>

inline std::vector<std::string> split_string(const std::string &str, char delimeter)
{
    std::string token;
    std::istringstream token_stream(str);
    std::vector<std::string> strings;
    strings.clear();
    
    while(std::getline(token_stream, token, delimeter))
    {
        strings.push_back(token);
    }

    return strings;
}

#endif