#include "../include/Utils.hpp"
#include <cassert>

std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement)
{
    std::replace(str.begin(),str.end(),to_replace,replacement);
    return str;
}

sf::Font loadFontWithFallbacks(const std::string& filename, const std::vector<std::string>& fallbackDirectories)
{
    sf::Font font;
    for(const std::string& directory: fallbackDirectories)
        if(font.loadFromFile(directory + filename))
            return font;
    throw;
}

void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event)
{
    assert(resize_event.type == sf::Event::Resized);
    sf::View view(sf::FloatRect(0, 0, resize_event.size.width, resize_event.size.height));
    window.setView(view);
}
