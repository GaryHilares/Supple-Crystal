#pragma once
#include "PopupMenuButton.hpp"

class PopupMenu: public MenuInterface
{
private:
    std::vector<PopupMenuButton> buttons;
    bool do_display;
public:
    PopupMenu(const std::vector<PopupMenuButton>& new_buttons = {});
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void display();
    void hide();
    MenuInterface* containsPoint(sf::Vector2f pointCoords) override;
    void processEvent(sf::Event event) override;
};
