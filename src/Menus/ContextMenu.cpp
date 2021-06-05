#include "../../include/Menus/ContextMenu.hpp"

/*class ContextMenu
{
private:
    MenuInterface* on_activate;
    std::unordered_map<sf::Keyboard::Key,std::function<void()>> binded_keys;
public:
    void bindContextMenu(MenuInterface* new_on_activate);
    void bindHotKey(sf::Keyboard::Key key_code, std::function<void()> function_to_call);
    void processEvent(sf::Event event);
};*/

ContextMenu::ContextMenu(): on_activate(nullptr) {}

void ContextMenu::bindContextMenu(PopupMenu* new_on_activate)
{
    this->on_activate = new_on_activate;
}

void ContextMenu::bindHotKey(sf::Keyboard::Key key_code, const std::function<void()>& function_to_call)
{
    this->binded_keys[key_code] = function_to_call;
}

void ContextMenu::processEvent(sf::RenderWindow& window, sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::MouseButtonReleased:
        if(this->on_activate != nullptr && event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f coords = window.mapPixelToCoords(mouse_pos);
            this->on_activate->setPosition(coords);
            this->on_activate->display();
        }
        else if(this->on_activate != nullptr)
        {
             this->on_activate->hide();
        }
        break;
    case sf::Event::KeyReleased:
        if(this->binded_keys.find(event.key.code) != this->binded_keys.end())
            this->binded_keys[event.key.code]();
        break;
    default:
        break;
    }
}

