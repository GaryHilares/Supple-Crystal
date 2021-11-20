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
    /**
     * @brief Construct a new SlideController object
     * 
     * @param new_image_display A reference to the image to control.
     */
    SlideController(ImageDisplay& new_image_display);
    /**
     * @brief Set whether the SlideController is enabled or not.
     * 
     * @param new_enabled New enabled value.
     */
    void setEnabled(const bool new_enabled);
    /**
     * @brief Check for MouseMoved events and slides the image accordingly.
     * 
     * @param event Event to check for updates.
     */
    void checkForUpdates(sf::Event event) override;
};
