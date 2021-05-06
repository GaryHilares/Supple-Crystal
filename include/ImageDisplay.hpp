#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class ImageDisplay : public sf::Drawable, public sf::Transformable
{
private:
    enum class Orientation{Up=1,Right=2,Down=3,Left=4};
    sf::Texture image;
    sf::Sprite sprite;
    Orientation orientation;
    void updateOrientation();
public:
    ImageDisplay(const std::string& filename);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const;
    void rotateLeft();
    void rotateRight();
    sf::Vector2f getRotatedDimensions();
};
