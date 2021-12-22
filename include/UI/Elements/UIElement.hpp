#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Base pure virtual class for UI elements.
 *
 */
class UIElement : public sf::Drawable, public sf::Transformable {
public:
    virtual ~UIElement() = default;

    virtual sf::Vector2u getSize() const = 0;

    /**
     * @brief Process an event and updates the UIElement subclass object accordingly.
     *
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