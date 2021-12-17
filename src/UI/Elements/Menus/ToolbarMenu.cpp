#include "../../../../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../../../../include/UI/Settings/style-constants.hpp"
#include <iostream>
#include <cassert>

UIElement* ToolbarMenu::getButtonFromCoords(sf::Vector2f pointCoords)
{
    int buttons_per_row = this->dimensions.x/Constants::ToolbarMenu::Button::Width;
    if(buttons_per_row == 0)
        buttons_per_row = 1;
    int button_number = (pointCoords.x - this->getPosition().x)/Constants::ToolbarMenu::Button::Width;
    int row_number = (pointCoords.y - this->getPosition().y)/Constants::ToolbarMenu::Button::Height;
    std::vector<std::shared_ptr<Button>>::size_type index =  button_number + row_number * buttons_per_row;
    std::cout << "Index: " << index << std::endl;
    return this->containsPoint(pointCoords) && index < this->buttons.size()
        ? dynamic_cast<UIElement*>(this->buttons[index].get()) : nullptr;
}

ToolbarMenu::ToolbarMenu(const std::vector<std::shared_ptr<Button>>& new_buttons, int new_width):
    buttons(new_buttons)
{
    this->setWidth(new_width);
    this->background.setFillColor(sf::Color(Constants::ToolbarMenu::Color));
}

void ToolbarMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->background);
    for(const std::shared_ptr<Button>& button: this->buttons)
        target.draw(*button,states);
}

void ToolbarMenu::processEvent(sf::Event event)
{
    const sf::Vector2f coords = {float(event.mouseButton.x),float(event.mouseButton.y)};
    UIElement* button_in_coords = this->getButtonFromCoords(coords);
    if(button_in_coords)
        button_in_coords->processEvent(event);
}

bool ToolbarMenu::containsPoint(sf::Vector2f pointCoords)
{
    sf::Vector2f position = this->getPosition();
    return position.y < pointCoords.y
        && position.y + this->dimensions.y > pointCoords.y
        && position.x < pointCoords.x
        && position.x + this->dimensions.x > pointCoords.x;
}

void ToolbarMenu::setWidth(int new_width)
{
    this->dimensions.x = new_width;
    int x = 0;
    int y = 0;
    for(std::shared_ptr<Button>& button: buttons)
    {
        if(x + Constants::ToolbarMenu::Button::Width > new_width && x != 0)
        {
            x = 0;
            y += Constants::ToolbarMenu::Button::Height;
        }
        button->setPosition(x,y);
        x += Constants::ToolbarMenu::Button::Width;
    }
    this->dimensions.y = y + (x == 0 ? 0:Constants::ToolbarMenu::Button::Height);
    this->background.setSize(sf::Vector2f{(float) this->dimensions.x, (float) this->dimensions.y});
}