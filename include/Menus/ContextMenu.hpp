#include "PopupMenu.hpp"

class ContextMenu: public PopupMenu
{
public:
    using PopupMenu::PopupMenu;
    void processEvent(const sf::RenderWindow& reference_window, sf::Event mouse_event);
};

