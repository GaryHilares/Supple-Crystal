#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement);
void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event);

template <class LoadableObject> LoadableObject loadFromFileWithFallbacks(const std::string& filename, const std::vector<std::string>& fallbackDirectories){
    LoadableObject loaded_object;
    for(const std::string& directory: fallbackDirectories)
        if(loaded_object.loadFromFile(directory + filename))
            return loaded_object;
    throw;
}
