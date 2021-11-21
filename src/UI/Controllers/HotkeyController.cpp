#include "../../../include/UI/Controllers/HotkeyController.hpp"
#include <cassert>

HotkeysController::HotkeysController(std::unordered_map<sf::Keyboard::Key,std::function<void()>> new_hotkey_bindings): hotkey_bindings(new_hotkey_bindings){}

void HotkeysController::checkForUpdates(sf::Event key_released_event)
{
    if(key_released_event.type == sf::Event::KeyReleased && hotkey_bindings.find(key_released_event.key.code) != hotkey_bindings.end())
        hotkey_bindings.at(key_released_event.key.code)();
}
