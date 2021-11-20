#pragma once
#include <SFML/Graphics.hpp>

class UIElement: public sf::Drawable, public sf::Transformable
{
public:

    /**
     * @brief Process an event and updates the UIElement subclass object accordingly.
     * 
     * @param reference_window Window of reference to process the event.
     * @param event Event to process.
     */
    virtual void processEvent(sf::Event event) = 0;
    
    /**
     * @brief Draws the UIElement subclass object.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the object should be drawn.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
