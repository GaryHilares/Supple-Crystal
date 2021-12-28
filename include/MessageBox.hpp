#include <SFML/Graphics.hpp>
#include <string>

class MessageBox {
private:
    const std::string& title;
    const std::string& name;
    const sf::Font& font;

    void run() const;

public:
    MessageBox(const std::string& new_title, const std::string& new_name, const sf::Font& new_font);
};