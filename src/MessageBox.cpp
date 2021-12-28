#include "../include/MessageBox.hpp"

void MessageBox::run() const
{
    const int windowWidth = 10 * m_name.size();
    constexpr int windowHeight = 100;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), m_title);
    window.setFramerateLimit(60);
    sf::Text text(m_name, m_font, 14);
    text.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(windowWidth / 2, windowHeight / 2);
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

MessageBox::MessageBox(const std::string& newTitle, const std::string& newName, const sf::Font& newFont)
    : m_title(newTitle)
    , m_name(newName)
    , m_font(newFont)
{
    this->run();
}