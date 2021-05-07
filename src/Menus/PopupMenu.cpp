#include "../../include/Menus/PopupMenu.hpp"

PopupMenu::PopupMenu(const std::vector<PopupMenuButton>& new_buttons): buttons(new_buttons), do_display(false)
{
    for(std::vector<PopupMenuButton>::size_type i = 0; i < this->buttons.size(); i++)
        this->buttons[i].setPosition(0,i*20);
}

void PopupMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->do_display)
    {
        states.transform *= this->getTransform();
        for(const PopupMenuButton& button: this->buttons)
            target.draw(button,states);
    }
}

void PopupMenu::display()
{
    this->do_display = true;
}

MenuInterface* PopupMenu::containsPoint(sf::Vector2f pointCoords)
{
    sf::Vector2f position = this->getPosition();
    return (position.y < pointCoords.y
        && position.y + this->buttons.size() * 20 > pointCoords.y
        && position.x < pointCoords.x
        && position.x + 150 > pointCoords.x)
        ? &this->buttons[(pointCoords.y - this->getPosition().y)/20] : nullptr;
}

void PopupMenu::processEvent(sf::Event event)
{
    throw std::exception();
}

void PopupMenu::hide()
{
    this->do_display = false;
}
