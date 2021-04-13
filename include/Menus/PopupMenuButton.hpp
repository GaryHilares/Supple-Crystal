#pragma once
#include "MenuInterface.hpp"
#include <string>
#include <functional>

class PopupMenuButton : public MenuInterface
{
private:
    sf::RectangleShape background;
    const sf::Font& font;
    sf::Text text;
    std::function<void()> on_click;
public:
    PopupMenuButton(const std::string& text_to_display, const sf::Font& new_font, const std::function<void()>& new_on_click);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    MenuInterface* containsPoint(sf::Vector2f pointCoords) override;
    void processEvent(sf::Event event) override;
};
