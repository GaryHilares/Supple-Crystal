#include "../../include/Utils/StringOps.hpp"
#include <algorithm>

std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement)
{
    std::replace(str.begin(), str.end(), to_replace, replacement);
    return str;
}