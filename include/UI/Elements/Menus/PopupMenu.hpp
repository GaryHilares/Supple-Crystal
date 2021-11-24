#pragma once
#include "../Buttons/Button.hpp"
#include <memory>

/**
 * @brief Class for default popup menus.
 * 
 */
class PopupMenu: public UIElement
{
private:
    std::vector<std::shared_ptr<Button>> buttons;
    bool do_display;

    /**
     * @brief Returns the UIElement subclass object which contacts the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return UIElement* A pointer to the UIElement which contacts the coord given or nullptr if there is no such UIElement.
     */
    UIElement* getButtonFromCoords(sf::Vector2f pointCoords);

public:
    virtual ~PopupMenu() = default;

    /**
     * @brief Construct a new PopupMenu object.
     * 
     * @param new_buttons Vector of std::shared_ptr<Button> objects to include in the PopupMenu.
     */
    PopupMenu(const std::vector<std::shared_ptr<Button>>& new_buttons);

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
     * @param new_do_display Whether the PopupMenu should be displayed or not.
     */
    void display(bool new_do_display);
    
    /**
     * @brief Process an event and updates the UIElement subclass object accordingly.
     * 
     * @param event Event to process.
     */
    virtual void processEvent(sf::Event event) override;

    /**
     * @brief Finds if a point is inside the bounds of the object or not.
     * 
     * @param pointCoords Coords to check.
     * @return bool True if point is in the bounds of the object, false otherwise.
     */
    bool containsPoint(sf::Vector2f pointCoords);
};
