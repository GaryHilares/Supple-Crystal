#include "PopupMenu.hpp"
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

class ContextMenu
{
private:
    PopupMenu* on_activate;
    std::unordered_map<sf::Keyboard::Key,std::function<void()>> binded_keys;
public:
    ContextMenu();
    void bindContextMenu(PopupMenu* new_on_activate);
    void bindHotKey(sf::Keyboard::Key key_code, const std::function<void()>& function_to_call);
    void processEvent(sf::RenderWindow& window, sf::Event event);
};
