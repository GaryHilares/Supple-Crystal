#include "../../../../include/UI/Elements/Displays/ImageDisplay.hpp"
#include <iostream>
#include <fstream>
#include <codecvt>

ImageDisplay::ImageDisplay(const std::string& filename)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(filename);
    sf::String file = wide;
    if(!this->image.loadFromFile(file))
        std::cerr << "Error opening file!" << std::endl;
    this->sprite.setTexture(this->image,true);
}

ImageDisplay::ImageDisplay(const ImageDisplay& other)
{
    this->image = other.image;
    this->sprite.setTexture(this->image,true);
}

void ImageDisplay::operator=(const ImageDisplay& other)
{
    this->image = other.image;
    this->sprite.setTexture(this->image,true);
}

void ImageDisplay::processEvent(sf::Event) {}

void ImageDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->sprite,states);
}

sf::Vector2u ImageDisplay::getSize() const
{
    return this->sprite.getTexture()->getSize();
}