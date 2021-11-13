#pragma once
#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Elements/Displays/ImageDisplay.hpp"

class SlideController
{
private:
    bool enabled;
    std::optional<sf::Vector2i> last_clicked_mouse_position;
public:
    SlideController();
    void setEnabled(const bool new_enabled);
    void updateIfEnabled(const sf::RenderWindow& window, ImageDisplay& image_display);
};
