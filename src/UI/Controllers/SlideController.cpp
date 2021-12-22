#include "../../../include/UI/Controllers/SlideController.hpp"

// std::make_optional may see pretty redundant, but is to avoid bugs in GCC.
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
SlideController::SlideController(ImageDisplay& new_image_display)
    : enabled(true)
    , last_clicked_mouse_position(std::make_optional<sf::Vector2i>())
    , image_display(new_image_display)
{
}

void SlideController::setEnabled(const bool new_enabled) { enabled = new_enabled; }

void SlideController::checkForUpdates(sf::Event event)
{
    if (event.type == sf::Event::MouseMoved && this->enabled) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            const sf::Vector2i current_mouse_position = { event.mouseMove.x, event.mouseMove.y };
            if (this->last_clicked_mouse_position.has_value()) {
                this->image_display.move(-(this->last_clicked_mouse_position.value().x - current_mouse_position.x),
                    -(this->last_clicked_mouse_position.value().y - current_mouse_position.y));
            }
            this->last_clicked_mouse_position = current_mouse_position;
        } else
            this->last_clicked_mouse_position.reset();
    }
}
