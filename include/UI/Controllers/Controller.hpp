#pragma once
#include <SFML/Window/Event.hpp>

class Controller{
public:
    virtual ~Controller() = default;

    /**
     * @brief Processes events on the controller and updates it correspondingly.
     * 
     * @param event The event to process.
     */
    virtual void checkForUpdates(sf::Event event) = 0;
};