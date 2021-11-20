#pragma once
#include <SFML/Window/Event.hpp>

class Controller{
public:
    virtual void checkForUpdates(sf::Event event) = 0;
};