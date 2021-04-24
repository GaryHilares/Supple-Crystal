#include "../include/ImageDisplay.hpp"
#include <iostream>

ImageDisplay::ImageDisplay(const std::string& filename)
{
    if(!this->image.loadFromFile(filename))
        std::cerr << "Error opening file!" << std::endl;
    this->sprite.setTexture(this->image);
}

void ImageDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->sprite,states);
}

sf::FloatRect ImageDisplay::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

void ImageDisplay::rotateRight()
{
    this->sprite.rotate(-90);
}

void ImageDisplay::rotateLeft()
{
    this->sprite.rotate(90);
}
