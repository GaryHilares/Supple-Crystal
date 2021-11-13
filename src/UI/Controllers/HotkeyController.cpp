#include "../../../include/UI/Controllers/HotkeyController.hpp"

HotkeysController::HotkeysController(std::unordered_map<sf::Keyboard::Key,std::function<void()>> new_hotkey_bindings): hotkey_bindings(new_hotkey_bindings){}

void HotkeysController::checkForHotkeys(sf::Event key_released_event)
{
    assert(key_released_event.type == sf::Event::KeyReleased);
    if(hotkey_bindings.find(key_released_event.key.code) != hotkey_bindings.end())
        hotkey_bindings[key_released_event.key.code]();
}
