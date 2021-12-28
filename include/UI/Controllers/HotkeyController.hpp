#pragma once
#include "Controller.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <unordered_map>

/**
 * @brief Class which controls hotkeys.
 *
 */
class HotkeysController : public Controller {
private:
    const std::unordered_map<sf::Keyboard::Key, std::function<void()>> m_hotkeyBindings;

public:
    /**
     * @brief Construct a new HotkeysController object.
     *
     * @param new_hotkey_bindings Hotkey bindings to manage.
     */
    HotkeysController(std::unordered_map<sf::Keyboard::Key, std::function<void()>> newHotkeyBindings);

    /**
     * @brief Checks if any hotkey has been triggered.
     *
     * @param key_released_event A key released event to check.
     * @throws FatalError Terminates the program if the event isn't a key released event.
     */
    void checkForUpdates(sf::Event keyReleasedEvent) override;
};
