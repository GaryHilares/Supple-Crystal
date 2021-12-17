#include "../../../../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../../../../include/UI/Settings/style-constants.hpp"
#include <cassert>

UIElement* ToolbarMenu::getButtonFromCoords(sf::Vector2f pointCoords)
{
    if(!this->containsPoint(pointCoords) || this->buttons.empty())
        return nullptr;
    sf::Vector2u buttons_size = this->buttons[0]->getSize();
    int buttons_per_row = this->size.x/buttons_size.x;
    if(buttons_per_row == 0)
        buttons_per_row = 1;
    int button_number = (pointCoords.x - this->getPosition().x)/buttons_size.x;
    int row_number = (pointCoords.y - this->getPosition().y)/buttons_size.y;
    std::vector<std::shared_ptr<Button>>::size_type index =  button_number + row_number * buttons_per_row;
    return index < this->buttons.size()
        ? dynamic_cast<UIElement*>(this->buttons[index].get()) : nullptr;
}

ToolbarMenu::ToolbarMenu(const std::vector<std::shared_ptr<Button>>& new_buttons, int new_width):
    buttons(new_buttons)
{
    std::optional<sf::Vector2u> buttons_size;
    for(const std::shared_ptr<Button>& button: new_buttons)
    {
        if(buttons_size.has_value())
            assert(button->getSize() == buttons_size);
        else
            buttons_size = button->getSize();
    }
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

sf::Vector2u ToolbarMenu::getSize() const
{
    return {this->size.x,this->size.y};
}

bool ToolbarMenu::containsPoint(sf::Vector2f pointCoords)
{
    sf::Vector2f position = this->getPosition();
    return position.y < pointCoords.y
        && position.y + this->size.y > pointCoords.y
        && position.x < pointCoords.x
        && position.x + this->size.x > pointCoords.x;
}

void ToolbarMenu::setWidth(unsigned int new_width)
{
    this->size.x = new_width;
    unsigned int x = 0;
    unsigned int y = 0;
    for(std::shared_ptr<Button>& button: buttons)
    {
        if(x + button->getSize().x > new_width && x != 0)
        {
            x = 0;
            y += button->getSize().y;
        }
        button->setPosition(x,y);
        x += button->getSize().x;
    }
    this->size.y = y;
    if(!this->buttons.empty() && x != 0)
        this->size.y += this->buttons[this->buttons.size()-1]->getSize().y;
    this->background.setSize(sf::Vector2f{(float) this->size.x, (float) this->size.y});
}