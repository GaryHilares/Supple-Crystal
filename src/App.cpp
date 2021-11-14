#include "../include/App.hpp"
#include "../include/UI/Controllers/HotkeyController.hpp"
#include "../include/UI/Controllers/SlideController.hpp"
#include "../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "../include/UI/Elements/Menus/ContextMenu.hpp"
#include "../include/UI/Elements/Menus/PopupMenu.hpp"
#include "../include/UI/Settings/style-constants.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <string>
#include <windows.h>

void App::runFastMode(const int argc, char* argv[])
{
    std::cout << "Fast mode" << std::endl;
    //Load fonts.
    const std::string file_path = replaceAllOcurrencesOfCharacter(std::string(argv[0]),'\\','/');
    const std::string folder_path = file_path.substr(0,file_path.rfind("/")) + "/";
    sf::Font font = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    //Gets the filename.
    const std::string filename = replaceAllOcurrencesOfCharacter(std::string(argv[1]),'\\','/');
    //Opens and sets the window.
    sf::Image icon = loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height), filename.substr(filename.rfind("/")+1,filename.size()) + " - Supple Crystal: Fast mode");
    window.setIcon(32, 32, icon.getPixelsPtr());
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    //Loads and sets the image.
    ImageDisplay image_display(filename);
    image_display.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
    image_display.setOrigin(image_display.getDimensions().x/2,image_display.getDimensions().y/2);
    //Creates the context_menu.
    ContextMenu context_menu({
                            PopupMenuButton("Polished Mode",font,[&](){this->current_activity = Activity::PolishedMode; window.close();}),
                            PopupMenuButton("Rotate left",font,[&](){image_display.rotate(-90);}),
                            PopupMenuButton("Rotate right",font,[&](){image_display.rotate(90);}),
                            PopupMenuButton("Increase zoom",font,[&](){image_display.scale({1.15,1.15});}),
                            PopupMenuButton("Decrease zoom",font,[&](){image_display.scale({0.85,0.85});})
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,[&](){image_display.scale(1.1,1.1);}},
                                            {sf::Keyboard::Subtract,[&](){image_display.scale(0.8,0.8);}},
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
                this->do_exit = true;
                break;
            case sf::Event::Resized:
                preventWindowContentResize(window,event);
                break;
            case sf::Event::MouseButtonReleased:
                {
                    const sf::Vector2f coords = window.mapPixelToCoords({event.mouseButton.x,event.mouseButton.y});
                    MenuInterface* menu_in_coords = context_menu.containsPoint(coords);
                    if(menu_in_coords) menu_in_coords->processEvent(event);
                    context_menu.processEvent(window,event);
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
}

void App::runPolishedMode(const int argc, char* argv[])
{
    std::cout << "Polished mode" << std::endl;
    //Load fonts.
    const std::string file_path = replaceAllOcurrencesOfCharacter(std::string(argv[0]),'\\','/');
    const std::string folder_path = file_path.substr(0,file_path.rfind("/")) + "/";
    sf::Font font = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    //Gets the filename.
    const std::string filename = replaceAllOcurrencesOfCharacter(std::string(argv[1]),'\\','/');
    //Opens and sets the window.
    sf::Image icon = loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height), filename.substr(filename.rfind("/")+1,filename.size()) + " - Supple Crystal: Polished mode");
    window.setIcon(32, 32, icon.getPixelsPtr());
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    //Loads and sets the image.
    ImageDisplay image_display(filename);
    image_display.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
    image_display.setOrigin(image_display.getDimensions().x/2,image_display.getDimensions().y/2);
    //Creates the context_menu.
    ContextMenu context_menu({
                            PopupMenuButton("Fast Mode",font,[&](){this->current_activity = Activity::FastMode; window.close();}),
                            PopupMenuButton("Rotate left",font,[&](){image_display.rotate(-90);}),
                            PopupMenuButton("Rotate right",font,[&](){image_display.rotate(90);}),
                            PopupMenuButton("Increase zoom",font,[&](){image_display.scale({1.15,1.15});}),
                            PopupMenuButton("Decrease zoom",font,[&](){image_display.scale({0.85,0.85});})
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,[&](){image_display.scale(1.1,1.1);}},
                                            {sf::Keyboard::Subtract,[&](){image_display.scale(0.8,0.8);}},
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
                this->do_exit = true;
                break;
            case sf::Event::Resized:
                preventWindowContentResize(window,event);
                break;
            case sf::Event::MouseButtonReleased:
                {
                    const sf::Vector2f coords = window.mapPixelToCoords({event.mouseButton.x,event.mouseButton.y});
                    MenuInterface* menu_in_coords = context_menu.containsPoint(coords);
                    if(menu_in_coords) menu_in_coords->processEvent(event);
                    context_menu.processEvent(window,event);
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
}

int App::run(const int argc, char* argv[])
{
    while(!do_exit)
    {
        switch(current_activity)
        {
        case Activity::FastMode:
            this->runFastMode(argc,argv);
            break;
        case Activity::PolishedMode:
            this->runPolishedMode(argc,argv);
            break;
        }
    }
    return this->exit_code;
}

App::App(): do_exit(false), exit_code(0), current_activity(Activity::FastMode) {}
