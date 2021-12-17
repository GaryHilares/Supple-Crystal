#ifdef _WIN32
#include "../../include/Utils/WindowOps.hpp"
#include <Windows.h>

void OS::maximizeWindow(sf::RenderWindow& window){
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
}

#endif