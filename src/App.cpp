#include "../include/ImageDisplay.hpp"
#include "../include/Menus/PopupMenu.hpp"
#include "../include/Menus/PopupMenuButton.hpp"
#include "../include/Menus/PopupMenuButton.hpp"
#include "../include/Menus/style-constants.hpp"
#include "../include/App.hpp"
#include <iostream>
#include <windows.h>
#include <optional>
#include <cassert>

void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event)
{
    assert(resize_event.type == sf::Event::Resized);
    sf::View view(sf::FloatRect(0, 0, resize_event.size.width, resize_event.size.height));
    window.setView(view);
}

class HotkeysController
{
private:
    std::unordered_map<sf::Keyboard::Key,std::function<void()>> hotkey_bindings;
public:
    HotkeysController(std::unordered_map<sf::Keyboard::Key,std::function<void()>> new_hotkey_bindings): hotkey_bindings(new_hotkey_bindings){}
    void checkForHotkeys(sf::Event key_released_event)
    {
        assert(key_released_event.type == sf::Event::KeyReleased);
        if(hotkey_bindings.find(key_released_event.key.code) != hotkey_bindings.end())
            hotkey_bindings[key_released_event.key.code]();
    }
};

class SlideController
{
private:
    bool enabled;
    std::optional<sf::Vector2i> last_clicked_mouse_position;
public:
    // std::make_optional may see pretty redundant, but is to avoid bugs in GCC.
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
    SlideController(): enabled(true), last_clicked_mouse_position(std::make_optional<sf::Vector2i>()) {}
    void setEnabled(const bool new_enabled){enabled = new_enabled;}
    void updateIfEnabled(const sf::RenderWindow& window, ImageDisplay& image_display)
    {
        if(this->enabled)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(this->last_clicked_mouse_position.has_value())
                {
                    const sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
                    image_display.move(-(this->last_clicked_mouse_position.value().x-current_mouse_position.x),
                                       -(this->last_clicked_mouse_position.value().y-current_mouse_position.y));
                }
                this->last_clicked_mouse_position = sf::Mouse::getPosition(window);
            }
            else
                this->last_clicked_mouse_position.reset();
        }
    }
};

void processContextMenu(const sf::RenderWindow& reference_window, PopupMenu& context_menu, sf::Event mouse_event)
{
    assert(mouse_event.type == sf::Event::MouseButtonReleased);
    const sf::Vector2f coords = reference_window.mapPixelToCoords({mouse_event.mouseButton.x,mouse_event.mouseButton.y});
    if(mouse_event.mouseButton.button == sf::Mouse::Right)
    {
        context_menu.setPosition(coords);
        context_menu.display();
    }
    else if(!context_menu.containsPoint(coords))
    {
        context_menu.hide();
    }
}

std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement)
{
    std::replace(str.begin(),str.end(),to_replace,replacement);
    return str;
}

sf::Font loadFont(const std::string& filename, const std::vector<std::string>& fallbackDirectories)
{
    sf::Font font;
    for(const std::string& directory: fallbackDirectories)
        if(font.loadFromFile(directory + filename))
            return font;
    throw;
}

int App::SuppleCrystal::run(const int argc, char* argv[])
{
    //Load fonts.
    const std::string file_path = replaceAllOcurrencesOfCharacter(std::string(argv[0]),'\\','/');
    const std::string folder_path = file_path.substr(0,file_path.rfind("/")) + "/";
    sf::Font calibri = loadFont("PublicSans-Regular.ttf",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    //Gets the filename.
    const std::string filename = argv[1];
    //Opens and sets the window.
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Supple Crystal");
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    //Loads and sets the image.
    ImageDisplay image_display(filename);
    image_display.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
    image_display.setOrigin(image_display.getDimensions().x/2,image_display.getDimensions().y/2);
    //Creates the context_menu.
    PopupMenu context_menu({/*PopupMenuButton("Full Mode",arialbd,[&](){std::cout<<"Full mode!";}),*/
                            PopupMenuButton("Rotate left",calibri,[&](){image_display.rotate(-90);}),
                            PopupMenuButton("Rotate right",calibri,[&](){image_display.rotate(90);}),
                            PopupMenuButton("Increase zoom",calibri,[&](){image_display.scale({1.15,1.15});}),
                            PopupMenuButton("Decrease zoom",calibri,[&](){image_display.scale({0.85,0.85});})
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,[&](){image_display.scale(1.15,1.15);}},
                                            {sf::Keyboard::Subtract,[&](){image_display.scale(0.85,0.85);}},
                                            {sf::Keyboard::Left,[&](){image_display.rotate(90);}},
                                            {sf::Keyboard::Right,[&](){image_display.rotate(-90);}}
                                         });
    SlideController slide_controller;
    while(window.isOpen())
    {
        /* Event handling: Closing window and context menu */
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::LostFocus:
                slide_controller.setEnabled(false);
                break;
            case sf::Event::GainedFocus:
                slide_controller.setEnabled(true);
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                preventWindowContentResize(window,event);
                break;
            case sf::Event::MouseButtonReleased:
                {
                    const sf::Vector2f coords = window.mapPixelToCoords({event.mouseButton.x,event.mouseButton.y});
                    MenuInterface* menu_in_coords = context_menu.containsPoint(coords);
                    if(menu_in_coords) menu_in_coords->processEvent(event);
                    processContextMenu(window,context_menu,event);
                }
                break;
            case sf::Event::KeyReleased:
                hotkeys_controller.checkForHotkeys(event);
            default:
                break;
            }
        }
        slide_controller.updateIfEnabled(window,image_display);
        /* Display */
        window.clear(sf::Color(Constants::background_color));
        window.draw(image_display);
        window.draw(context_menu);
        window.display();
    }
    return 0;
}
