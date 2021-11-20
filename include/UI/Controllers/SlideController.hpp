#pragma once
#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Elements/Displays/ImageDisplay.hpp"
#include "Controller.hpp"

class SlideController: public Controller
{
private:
    bool enabled;
    std::optional<sf::Vector2i> last_clicked_mouse_position;
    ImageDisplay& image_display;
public:
    SlideController(ImageDisplay& new_image_display);
    /**
     * @brief Set whether the SlideController is enabled or not.
     * 
     * @param new_enabled New enabled value.
     */
    void setEnabled(const bool new_enabled);
    void checkForUpdates(sf::Event event) override;
};
