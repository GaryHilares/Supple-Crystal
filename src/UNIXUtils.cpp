#ifndef _WIN32
#include "../include/OSUtils.hpp"
#include <iostream>

void OS::maximizeWindow(sf::RenderWindow& window){
    std::cerr << "Warning: 'maximizeWindow' is currently only supported on Windows."
}

#endif