#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class ImageDisplay : public sf::Drawable, public sf::Transformable
{
private:
    sf::Texture image;
    sf::Sprite sprite;
public:
    ImageDisplay(const std::string& filename);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const;
};
