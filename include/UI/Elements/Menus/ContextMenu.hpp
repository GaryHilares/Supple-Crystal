#pragma once
#include "PopupMenu.hpp"

class ContextMenu: public PopupMenu
{
public:
    using PopupMenu::PopupMenu;
    /**
     * @brief Processes an event and updates the ContextMenu accordingly.
     * 
     * @param reference_window The window of reference.
     * @param mouse_event A mouse event to process.
     * @throws Throws if the event type isn't MouseReleased.
     */
    void processEvent(const sf::RenderWindow& reference_window, sf::Event mouse_event);
};

