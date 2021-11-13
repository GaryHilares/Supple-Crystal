#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement);
sf::Font loadFontWithFallbacks(const std::string& filename, const std::vector<std::string>& fallbackDirectories);
void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event);
