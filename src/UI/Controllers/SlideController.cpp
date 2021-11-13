#include "../../../include/UI/Controllers/SlideController.hpp"


// std::make_optional may see pretty redundant, but is to avoid bugs in GCC.
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
SlideController::SlideController(): enabled(true), last_clicked_mouse_position(std::make_optional<sf::Vector2i>()) {}

void SlideController::setEnabled(const bool new_enabled){enabled = new_enabled;}

void SlideController::updateIfEnabled(const sf::RenderWindow& window, ImageDisplay& image_display)
{
    if(this->enabled)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(this->last_clicked_mouse_position.has_value())
            {
                const sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
                image_display.move(-(this->last_clicked_mouse_position.value().x-current_mouse_position.x),
                                    -(this->last_clicked_mouse_position.value().y-current_mouse_position.y));
            }
            this->last_clicked_mouse_position = sf::Mouse::getPosition(window);
        }
        else
            this->last_clicked_mouse_position.reset();
    }
}
