#include "../include/MessageBox.hpp"

void MessageBox::run() const
{
    const int window_width = 10 * this->name.size();
    constexpr int window_height = 100;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), this->title);
    window.setFramerateLimit(60);
    sf::Text text(this->name, this->font, 14);
    text.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(window_width / 2, window_height / 2);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::EventType::Closed:
                window.close();
            default:
                break;
            }
        }
        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}

MessageBox::MessageBox(const std::string& new_title, const std::string& new_name, const sf::Font& new_font)
    : title(new_title)
    , name(new_name)
    , font(new_font)
{
    this->run();
}