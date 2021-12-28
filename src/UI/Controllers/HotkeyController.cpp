#include "../../../include/UI/Controllers/HotkeyController.hpp"
#include <cassert>

HotkeysController::HotkeysController(std::unordered_map<sf::Keyboard::Key, std::function<void()>> newHotkeyBindings)
    : m_hotkeyBindings(newHotkeyBindings)
{
}

void HotkeysController::checkForUpdates(sf::Event keyReleasedEvent)
{
    if (keyReleasedEvent.type == sf::Event::KeyReleased && m_hotkeyBindings.find(keyReleasedEvent.key.code) != m_hotkeyBindings.end())
        m_hotkeyBindings.at(keyReleasedEvent.key.code)();
}
