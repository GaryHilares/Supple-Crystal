#pragma once
#include <SFML/Graphics.hpp>

class MenuInterface: public sf::Drawable, public sf::Transformable
{
public:
    /**
     * @brief Returns the MenuInterface subclass object which contacts the coords given.
     * 
     * @param pointCoords Coords to look at.
     * @return MenuInterface* A pointer to the MenuInterface which contacts the coord given or nullptr if there is no such MenuInterface.
     */
    virtual MenuInterface* containsPoint(sf::Vector2f) = 0;
    /**
     * @brief Process an event and updates the MenuInterface subclass object accordingly.
     * 
     * @param event Event to process.
     */
    virtual void processEvent(sf::Event event) = 0;
    /**
     * @brief Draws the MenuInterface subclass object.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the object should be drawn.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
