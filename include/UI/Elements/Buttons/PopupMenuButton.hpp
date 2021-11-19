#pragma once
#include "../Menus/MenuInterface.hpp"
#include <functional>
#include <string>

class PopupMenuButton : public MenuInterface
{
private:
    sf::RectangleShape background;
    const sf::Font& font;
    sf::Text text;
    std::function<void()> on_click;
public:
    /**
     * @brief Construct a new PopupMenuButton object.
     * 
     * @param text_to_display Text to display in the button.
     * @param new_font A reference to the font to use on the button. If the font is destroyed before the button, a dangling reference is generated.
     * @param new_on_click Function to run when the button is clicked.
     */
    PopupMenuButton(const std::string& text_to_display, const sf::Font& new_font, const std::function<void()>& new_on_click);
    /**
     * @brief Draws the object to a RenderTarget.
     * 
     * @param target RenderTarget to draw the object.
     * @param states The states in which the object should be drawn.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
     * @brief Returns the MenuInterface which contacts the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return MenuInterface* A pointer to the MenuInterface which contacts the coord given or nullptr if there is no such MenuInterface.
     */
    MenuInterface* containsPoint(sf::Vector2f pointCoords) override;
    /**
     * @brief Processes an event and changes the PopupMenuButton accordingly.
     * 
     * @param event Event to process.
     */
    void processEvent(sf::Event event) override;
};
