#include "../../../../include/UI/Elements/Menus/PopupMenu.hpp"
#include <cassert>
#include <optional>

PopupMenu::PopupMenu(const std::vector<std::shared_ptr<Button>>& new_buttons)
    : buttons(new_buttons)
    , do_display(false)
    , border(sf::Vector2f(new_buttons[0]->getSize().x, new_buttons[0]->getSize().y * new_buttons.size()))
{
    std::optional<sf::Vector2u> buttons_size;
    for (const std::shared_ptr<Button>& button : new_buttons) {
        if (buttons_size.has_value())
            assert(button->getSize() == buttons_size);
        else
            buttons_size = button->getSize();
    }
    this->border.setFillColor(sf::Color::Transparent);
    this->border.setOutlineColor(sf::Color::Black);
    this->border.setOutlineThickness(1);
    unsigned int x = 0;
    for (std::shared_ptr<Button>& button : this->buttons) {
        button->setPosition(0, x);
        x += button->getSize().y;
    }
}

void PopupMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->do_display) {
        states.transform *= this->getTransform();
        target.draw(this->border, states);
        for (const std::shared_ptr<Button>& button : this->buttons)
            target.draw(*button, states);
    }
}

void PopupMenu::display(bool new_do_display)
{
    this->do_display = new_do_display;
}

UIElement* PopupMenu::getButtonFromCoords(sf::Vector2f pointCoords)
{
    return this->containsPoint(pointCoords) && !this->buttons.empty()
        ? dynamic_cast<UIElement*>(this->buttons[(pointCoords.y - this->getPosition().y) / this->buttons[0]->getSize().y].get())
        : nullptr;
}

void PopupMenu::processEvent(sf::Event event)
{
    const sf::Vector2f coords = { float(event.mouseButton.x), float(event.mouseButton.y) };
    UIElement* button_in_coords = this->getButtonFromCoords(coords);
    if (button_in_coords)
        button_in_coords->processEvent(event);
}

bool PopupMenu::containsPoint(sf::Vector2f pointCoords)
{
    sf::Vector2f position = this->getPosition();
    return this->do_display
        && !this->buttons.empty()
        && position.y < pointCoords.y
        && position.y + this->buttons.size() * this->buttons[0]->getSize().y > pointCoords.y
        && position.x < pointCoords.x
        && position.x + this->buttons[0]->getSize().x > pointCoords.x;
}

sf::Vector2u PopupMenu::getSize() const
{
    return !this->buttons.empty() ? sf::Vector2u { this->buttons[0]->getSize().x, (unsigned int)this->buttons.size() * this->buttons[0]->getSize().y } : sf::Vector2u { 0, 0 };
}