#include "../../../include/UI/Controllers/SlideController.hpp"

// std::make_optional may see pretty redundant, but is to avoid bugs in GCC.
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
SlideController::SlideController(ImageDisplay& newImageDisplay)
    : m_enabled(true)
    , m_lastClickedMousePosition(std::make_optional<sf::Vector2i>())
    , m_imageDisplay(newImageDisplay)
{
}

void SlideController::setEnabled(const bool newEnabled) { m_enabled = newEnabled; }

void SlideController::checkForUpdates(sf::Event event)
{
    if (event.type == sf::Event::MouseMoved && m_enabled) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            const sf::Vector2i currentMousePosition = { event.mouseMove.x, event.mouseMove.y };
            if (m_lastClickedMousePosition.has_value()) {
                m_imageDisplay.move(-(m_lastClickedMousePosition.value().x - currentMousePosition.x),
                    -(m_lastClickedMousePosition.value().y - currentMousePosition.y));
            }
            m_lastClickedMousePosition = currentMousePosition;
        } else
            m_lastClickedMousePosition.reset();
    }
}
