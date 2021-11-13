#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ImageDisplay : public sf::Drawable, public sf::Transformable
{
private:
    sf::Texture image;
    sf::Sprite sprite;
public:
    ImageDisplay(const std::string& filename);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f getDimensions();
};
