#pragma once
#include "../Buttons/PopupMenuButton.hpp"

class PopupMenu: public UIElement
{
private:
    std::vector<PopupMenuButton> buttons;
    bool do_display;
public:
    /**
     * @brief Construct a new PopupMenu object.
     * 
     * @param new_buttons Vector of PopupMenuButton objects to include in the PopupMenu.
     */
    PopupMenu(const std::vector<PopupMenuButton>& new_buttons = {});
    /**
     * @brief Draws the PopupMenu.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the PopupMenu should be drawn.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
     * @brief Displays the PopupMenu.
     *
     */
    void display();
    /**
     * @brief Hides the PopupMenu
     * 
     */
    void hide();
    /**
     * @brief Returns the UIElement subclass object which contacts the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return UIElement* A pointer to the UIElement which contacts the coord given or nullptr if there is no such UIElement.
     */
    UIElement* getPointedElement(sf::Vector2f pointCoords) override;
    /**
     * @brief Process an event and updates the UIElement subclass object accordingly.
     * 
     * @param reference_window Window of reference to process the event. 
     * @param event Event to process.
     */
    void processEvent(const sf::RenderWindow& reference_window, sf::Event event) override;
};
