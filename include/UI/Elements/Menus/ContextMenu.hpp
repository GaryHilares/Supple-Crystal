#pragma once
#include "PopupMenu.hpp"

/**
 * @brief Class for default context menus.
 *
 */
class ContextMenu : public PopupMenu {
public:
    using PopupMenu::PopupMenu;

    /**
     * @brief Processes an event and updates the ContextMenu accordingly.
     *
     * @param reference_window The window of reference.
     * @param mouse_event A mouse event to process.
     * @throws Error if the event type isn't MouseReleased.
     */
    void processEvent(sf::Event mouseEvent) override;
};