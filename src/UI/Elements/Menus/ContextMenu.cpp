#include "../../../../include/UI/Elements/Menus/ContextMenu.hpp"
#include <cassert>
#include <iostream>

void ContextMenu::processEvent(sf::Event mouse_event)
{
    assert(mouse_event.type == sf::Event::MouseButtonReleased);
    const sf::Vector2f coords = {float(mouse_event.mouseButton.x),float(mouse_event.mouseButton.y)};
    if(mouse_event.mouseButton.button == sf::Mouse::Right)
    {
        this->setPosition(coords);
        this->display(true);
    }
    else if(!this->containsPoint(coords))
    {
        this->display(false);
    }
    this->PopupMenu::processEvent(mouse_event);
}
