#include "../../../../include/UI/Elements/Menus/ContextMenu.hpp"
#include <cassert>

void ContextMenu::processEvent(const sf::RenderWindow& reference_window, sf::Event mouse_event)
{
    assert(mouse_event.type == sf::Event::MouseButtonReleased);
    const sf::Vector2f coords = reference_window.mapPixelToCoords({mouse_event.mouseButton.x,mouse_event.mouseButton.y});
    if(mouse_event.mouseButton.button == sf::Mouse::Right)
    {
        this->setPosition(coords);
        this->display(true);
    }
    else if(!this->getPointedElement(coords))
    {
        this->display(false);
    }
}
