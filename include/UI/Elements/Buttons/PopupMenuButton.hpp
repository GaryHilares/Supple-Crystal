#pragma once
#include "../UIElement.hpp"
#include <functional>
#include <string>

class Button : public UIElement{
public:
    virtual ~Button() = default;
};

class PopupMenuButton : public Button
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
     * @brief Processes an event and changes the PopupMenuButton accordingly.
     * 
     * @param reference_window Window of reference to process the event.
     * @param event Event to process.
     */
    void processEvent(sf::Event event) override;
};
