#ifndef _WIN32
#include "../../include/Utils/WindowOps.hpp"
#include <iostream>

void OS::maximizeWindow(sf::RenderWindow& window)
{
    std::cerr << "Warning: 'maximizeWindow' is currently only supported on Windows." << std::endl;
}

#endif