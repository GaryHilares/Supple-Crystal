#include "../../../../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../../../../include/UI/Settings/style-constants.hpp"

PopupMenuButton::PopupMenuButton(const std::string& text_to_display, const sf::Font& new_font, const std::function<void()>& new_on_click): background({Constants::PopupMenu::Button::Width,Constants::PopupMenu::Button::Height}), font(new_font), text(text_to_display,font,Constants::PopupMenu::Button::FontSize), on_click(new_on_click)
{
    this->text.move(Constants::PopupMenu::Button::TextPadding::Left,Constants::PopupMenu::Button::TextPadding::Top);
    this->background.setFillColor(sf::Color::White);
    this->text.setFillColor(sf::Color::Black);
}

void PopupMenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->background,states);
    target.draw(this->text,states);
}

UIElement* PopupMenuButton::containsPoint(sf::Vector2f pointCoords)
{
    return this->background.getGlobalBounds().contains(pointCoords.x,pointCoords.y) ? this : nullptr;
}

void PopupMenuButton::processEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        return this->on_click();
}
