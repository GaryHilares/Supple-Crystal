#pragma once
#include <optional>
#include "../Elements/Displays/ImageDisplay.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class SlideController
{
private:
    bool enabled;
    std::optional<sf::Vector2i> last_clicked_mouse_position;
public:
    SlideController();
    /**
     * @brief Set whether the SlideController is enabled or not.
     * 
     * @param new_enabled New enabled value.
     */
    void setEnabled(const bool new_enabled);
    /**
     * @brief If enabled, moves the ImageDisplay if the user is dragging the screen with the mouse.
     * 
     * @param window The window of reference for the movement.
     * @param image_display The ImageDisplay to move.
     */
    void updateIfEnabled(const sf::RenderWindow& window, ImageDisplay& image_display);
};
