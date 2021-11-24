#pragma once
#include "../UIElement.hpp"
#include <string>

/**
 * @brief Class for default image displays.
 * 
 */
class ImageDisplay : public UIElement
{
private:
    sf::Texture image;
    sf::Sprite sprite;

public:
    /**
     * @brief Construct a new empty ImageDisplay object
     * 
     */
    ImageDisplay() = default;

    /**
     * @brief Loads an image from a file and constructs a new ImageDisplay object.
     * 
     * @param filename Filename of image to load.
     */
    ImageDisplay(const std::string& filename);

    /**
     * @brief Copies an ImageDisplay and constructs a new one.
     * 
     * @param filename Image display to copy.
     */
    ImageDisplay(const ImageDisplay& filename);

    void operator=(const ImageDisplay& other);

    /**
     * @brief Currently, just ignores the event passed.
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
