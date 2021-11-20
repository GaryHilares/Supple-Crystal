#include "../../../../include/UI/Elements/Displays/ImageDisplay.hpp"
#include <iostream>

ImageDisplay::ImageDisplay(const std::string& filename)
{
    if(!this->image.loadFromFile(filename))
        std::cerr << "Error opening file!" << std::endl;
    this->sprite.setTexture(this->image);
}

void ImageDisplay::processEvent(sf::Event event) {}

void ImageDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->sprite,states);
}

sf::Vector2f ImageDisplay::getDimensions()
{
    const sf::FloatRect& globalBounds = this->sprite.getLocalBounds();
    return sf::Vector2f(globalBounds.width,globalBounds.height);
}