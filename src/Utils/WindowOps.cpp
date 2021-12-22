#include "../../include/Utils/WindowOps.hpp"

void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event)
{
    if (resize_event.type == sf::Event::Resized) {
        sf::View view(sf::FloatRect(0, 0, resize_event.size.width, resize_event.size.height));
        window.setView(view);
    }
}