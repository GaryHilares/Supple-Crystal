#include "../include/App.hpp"
#include "../include/UI/Controllers/HotkeyController.hpp"
#include "../include/UI/Controllers/SlideController.hpp"
#include "../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "../include/UI/Elements/Menus/ContextMenu.hpp"
#include "../include/UI/Elements/Menus/PopupMenu.hpp"
#include "../include/UI/Settings/style-constants.hpp"
#include "../include/utils.hpp"
#include "../include/OSUtils.hpp"
#include <iostream>

const std::pair<std::string,std::string> App::parseArguments(const int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Invalid number of arguments!" << std::endl;
        throw;
    }
    const std::string file_path = replaceAllOcurrencesOfCharacter(std::string(argv[0]),'\\','/');
    const std::string folder_path = file_path.substr(0,file_path.rfind("/")) + "/";
    const std::string filename = replaceAllOcurrencesOfCharacter(std::string(argv[1]),'\\','/');
    return {folder_path,filename};
}

void App::runFastMode(const std::string folder_path, const std::string filename)
{
    std::cout << "Fast mode" << std::endl;
    //Load fonts.
    sf::Font font = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    //Opens and sets the window.
    sf::Image icon = loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",{folder_path,"","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height), filename.substr(filename.rfind("/")+1,filename.size()) + " - Supple Crystal: Fast mode");
    window.setIcon(32, 32, icon.getPixelsPtr());
    OS::maximizeWindow(window);
    //Loads and sets the image.
    ImageDisplay image_display(filename);
    image_display.setOrigin(image_display.getDimensions().x/2,image_display.getDimensions().y/2);
    image_display.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
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
    SlideController slide_controller(image_display);
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
            case sf::Event::MouseMoved:
                slide_controller.checkForUpdates(event);
                break;
            case sf::Event::Resized:
                preventWindowContentResize(window,event);
                break;
            case sf::Event::MouseButtonReleased:
                context_menu.processEvent(event);
                break;
            case sf::Event::KeyReleased:
                hotkeys_controller.checkForUpdates(event);
                break;
            default:
                break;
            }
        }
        /* Display */
        window.clear(sf::Color(Constants::background_color));
        window.draw(image_display);
        window.draw(context_menu);
        window.display();
    }
}

void App::runPolishedMode(const std::string folder_path, const std::string filename)
{
    std::cout << "Polished mode" << std::endl;
    this->do_exit = true;
    this->exit_code = 0;
}

int App::run(const int argc, char* argv[])
{
    const std::pair<std::string,std::string> arguments = this->parseArguments(argc,argv);
    const std::string folder_path = arguments.first;
    const std::string filename = arguments.second;
    while(!do_exit)
    {
        switch(current_activity)
        {
        case Activity::FastMode:
            this->runFastMode(folder_path,filename);
            break;
        case Activity::PolishedMode:
            this->runPolishedMode(folder_path,filename);
            break;
        }
    }
    return this->exit_code;
}

App::App(): do_exit(false), exit_code(0), current_activity(Activity::FastMode) {}
