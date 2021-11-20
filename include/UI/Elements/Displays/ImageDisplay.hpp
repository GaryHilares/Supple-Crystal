#pragma once
#include "../UIElement.hpp"
#include <string>

class ImageDisplay : public UIElement
{
private:
    sf::Texture image;
    sf::Sprite sprite;

public:
    /**
     * @brief Construct a new ImageDisplay object.
     * 
     * @param filename Filename of image to load.
     */
    ImageDisplay(const std::string& filename);

    /**
     * @brief By the time being, does nothing.
     * 
     * @param event An event to be ignored.
     */
    void processEvent(sf::Event event) override;

    /**
     * @brief Draws the object.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the object should be drawn.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Get the dimensions of the object.
     * 
     * @return sf::Vector2f Dimensions of the object.
     */
    sf::Vector2f getDimensions();
};
