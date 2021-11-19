#pragma once
#include "../Buttons/PopupMenuButton.hpp"

class PopupMenu: public MenuInterface
{
private:
    std::vector<PopupMenuButton> buttons;
    bool do_display;
public:
    /**
     * @brief Construct a new PopupMenu object.
     * 
     * @param new_buttons Vector of PopupMenuButton objects to include in the PopupMenu.
     * @throw Never throws.
     */
    PopupMenu(const std::vector<PopupMenuButton>& new_buttons = {});
    /**
     * @brief Draws the PopupMenu.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the PopupMenu should be drawn.
     * @throw Never throws.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
     * @brief Displays the PopupMenu.
     *
     * @throws Never throws.
     */
    void display();
    /**
     * @brief Hides the PopupMenu
     * 
     * @throws Never throws.
     */
    void hide();
    /**
     * @brief Returns the MenuInterface subclass object which contacts the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return MenuInterface* A pointer to the MenuInterface which contacts the coord given or nullptr if there is no such MenuInterface.
     * @throws Never throws.
     */
    MenuInterface* containsPoint(sf::Vector2f pointCoords) override;
    /**
     * @brief Process an event and updates the MenuInterface subclass object accordingly.
     * 
     * @param event Event to process.
     * @throws Never throws.
     */
    void processEvent(sf::Event event) override;
};
