#include "../../../../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../../../../include/UI/Settings/style-constants.hpp"

UIElement* ToolbarMenu::getButtonFromCoords(sf::Vector2f pointCoords)
{
    return this->containsPoint(pointCoords)
        ? dynamic_cast<UIElement*>(this->buttons[(pointCoords.x - this->getPosition().x)/Constants::ToolbarMenu::Button::Width].get()) : nullptr;
}

ToolbarMenu::ToolbarMenu(const std::vector<std::shared_ptr<Button>>& new_buttons):
    buttons(new_buttons),
    background(sf::Vector2f(0.f,0.f))
{
    this->background.setFillColor(sf::Color(Constants::ToolbarMenu::Color));
    for(std::vector<std::shared_ptr<Button>>::size_type i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->setPosition(i*Constants::ToolbarMenu::Button::Width,0);
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
        && position.y + Constants::ToolbarMenu::Button::Height > pointCoords.y
        && position.x < pointCoords.x
        && position.x + Constants::ToolbarMenu::Button::Width * this->buttons.size() > pointCoords.x;
}