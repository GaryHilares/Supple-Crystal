#include <SFML/Graphics.hpp>
#include <string>

class MessageBox {
private:
    const std::string& m_title;
    const std::string& m_name;
    const sf::Font& m_font;

    void run() const;

public:
    MessageBox(const std::string& newTitle, const std::string& newName, const sf::Font& newFont);
};