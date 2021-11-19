#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ImageDisplay : public sf::Drawable, public sf::Transformable
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
     * @brief Draws the object.
     * 
     * @param target RenderTarget to draw the object.
     * @param states States in which the object should be drawn.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f getDimensions();
};
