#include "../include/utils.hpp"
#include <cassert>

std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement)
{
    std::replace(str.begin(),str.end(),to_replace,replacement);
    return str;
}

void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event)
{
    assert(resize_event.type == sf::Event::Resized);
    sf::View view(sf::FloatRect(0, 0, resize_event.size.width, resize_event.size.height));
    window.setView(view);
}
