#include "../include/ImageDisplay.hpp"
#include <iostream>

ImageDisplay::ImageDisplay(const std::string& filename): orientation(Orientation::Up)
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
    if(this->orientation == Orientation::Left)
        this->orientation = Orientation::Up;
    else
        this->orientation = static_cast<Orientation>((int) this->orientation + 1);
    this->updateOrientation();
}

void ImageDisplay::rotateLeft()
{
    if(this->orientation == Orientation::Up)
        this->orientation = Orientation::Left;
    else
        this->orientation = static_cast<Orientation>((int) this->orientation - 1);
    this->updateOrientation();
}

void ImageDisplay::updateOrientation()
{
    switch(this->orientation)
    {
    case Orientation::Up:
        {
            const sf::Vector2f& old_position = this->getPosition();
            this->setRotation(0);
            this->setOrigin(0,0);
            this->setPosition(old_position);
        }
        break;
    case Orientation::Right:
        {
            const sf::Vector2f& old_position = this->getPosition();
            this->setRotation(90);
            this->setOrigin(0,this->getGlobalBounds().height);
            this->setPosition(old_position);
        }
        break;
    case Orientation::Down:
        {
            const sf::Vector2f& old_position = this->getPosition();
            this->setRotation(180);
            this->setOrigin(this->getGlobalBounds().width,this->getGlobalBounds().height);
            this->setPosition(old_position);
        }
        break;
    case Orientation::Left:
        {
            const sf::Vector2f& old_position = this->getPosition();
            this->setRotation(270);
            this->setOrigin(this->getGlobalBounds().width,0);
            this->setPosition(old_position);
        }
        break;
    default:
        std::cout << static_cast<int>(this->orientation);
        std::terminate();
    }
}

sf::Vector2f ImageDisplay::getRotatedDimensions()
{
    const sf::FloatRect& globalBounds = this->sprite.getLocalBounds();
    return ((this->orientation == Orientation::Up || this->orientation == Orientation::Down) ? sf::Vector2f(globalBounds.width,globalBounds.height):sf::Vector2f(globalBounds.height,globalBounds.width));
}
