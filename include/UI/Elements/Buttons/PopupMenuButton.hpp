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
     * @param text_to_display 
     * @param new_font 
     * @param new_on_click
     */
    PopupMenuButton(const std::string& text_to_display, const sf::Font& new_font, const std::function<void()>& new_on_click);
    /**
     * @brief Draws the object to a RenderTarget.
     * 
     * @param target RenderTarget to draw the object.
     * @param states The states in which the object should be drawn.
     * @throw Never throws.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
     * @brief Returns the MenuInterface which contacts the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return MenuInterface* A pointer to the MenuInterface which contacts the coord given or nullptr if there is no such MenuInterface.
     * @throw Never throws.
     */
    MenuInterface* containsPoint(sf::Vector2f pointCoords) override;
    /**
     * @brief Processes an event and changes the PopupMenuButton accordingly.
     * 
     * @param event Event to process.
     * @throw Never throws.
     */
    void processEvent(sf::Event event) override;
};
