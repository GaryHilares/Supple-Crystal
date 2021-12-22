#pragma once
#include "../Buttons/Button.hpp"
#include "../UIElement.hpp"
#include <memory>

/**
 * @brief Class for default toolbar menus.
 *
 */
class ToolbarMenu: public UIElement
{
private:
    std::vector<std::shared_ptr<Button>> buttons;
    sf::RectangleShape background;
    sf::Vector2u size;

    /**
     * @brief Returns a pointer to the UIElement subclass object which contains the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return UIElement* A pointer to the UIElement which contains the coords given or nullptr if there is no such UIElement.
     */
    UIElement* getButtonFromCoords(sf::Vector2f pointCoords);
public:
    /**
     * @brief Construct a new PopupMenu object with the given buttons.
     * 
     * @param new_buttons Vector of std::shared_ptr<Button> objects to include in the PopupMenu.
     */
    ToolbarMenu(const std::vector<std::shared_ptr<Button>>& new_buttons, int new_width);

    /**
     * @brief Draws the PopupMenu.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the PopupMenu should be drawn.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Process an event and updates the UIElement subclass object accordingly.
     * 
     * @param event Event to process.
     */
    void processEvent(sf::Event event) override;

    /**
     * @brief Finds if a point is inside the bounds of the object or not.
     * 
     * @param pointCoords Coords to check.
     * @return bool True if point is in the bounds of the object, false otherwise.
     */
    bool containsPoint(sf::Vector2f pointCoords);

    void setWidth(unsigned int new_width);

    sf::Vector2u getSize() const override;
};