#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <unordered_map>
#include "Controller.hpp"

class HotkeysController: public Controller
{
private:
    const std::unordered_map<sf::Keyboard::Key,std::function<void()>> hotkey_bindings;
public:
    /**
     * @brief Construct a new HotkeysController object.
     * 
     * @param new_hotkey_bindings Hotkey bindings to manage.
     */
    HotkeysController(std::unordered_map<sf::Keyboard::Key,std::function<void()>> new_hotkey_bindings);
    /**
     * @brief Checks if any hotkey has been triggered.
     * 
     * @param key_released_event A key released event to check.
     * @throws FatalError Terminates the program if the event isn't a key released event.
     */
    void checkForUpdates(sf::Event key_released_event) override;
};
