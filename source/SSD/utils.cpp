#include "../../header/utils.h"
#include <sstream>
#include <string>

uint32_t StrtoHex(const char *hexstr)
{
    std::string str{hexstr};
    if (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X")
    {
        str = str.substr(2);
    }
    uint32_t result;
    std::stringstream ss;
    ss << std::hex << str;
    ss >> result;
    return result;
}