#pragma once
#include "../Elements/Displays/ImageDisplay.hpp"
#include "Controller.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <optional>

/**
 * @brief Class which controls the sliding and modifies an ImageDisplay based on it.
 *
 */
class SlideController : public Controller {
private:
    bool m_enabled;
    std::optional<sf::Vector2i> m_lastClickedMousePosition;
    ImageDisplay& m_imageDisplay;

public:
    /**
     * @brief Construct a new SlideController object
     *
     * @param new_image_display A reference to the image to control.
     */
    SlideController(ImageDisplay& newImageDisplay);

    /**
     * @brief Set whether the SlideController is enabled or not.
     *
     * @param new_enabled New enabled value.
     */
    void setEnabled(const bool newEnabled);

    /**
     * @brief Check for MouseMoved events and slides the image accordingly.
     *
     * @param event Event to check for updates.
     */
    void checkForUpdates(sf::Event event) override;
};
