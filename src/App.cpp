#include "../include/ImageDisplay.hpp"
#include "../include/Menus/PopupMenu.hpp"
#include "../include/Menus/PopupMenuButton.hpp"
#include "../include/Menus/PopupMenuButton.hpp"
#include "../include/App.hpp"
#include <iostream>
#include <windows.h>
#include <optional>

int App::SuppleCrystal::run(int argc, char* argv[])
{
    sf::Clock timer;
    sf::Font arialbd;
    if(!arialbd.loadFromFile("C:/Users/Administrator/Desktop/Supple-Crystal 0.1-alfa/arialbd.ttf"))
    {
        std::cerr << "Couldn't open arialbd.ttf!";
        return 1;
    }
    std::string filename = argv[1];
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Supple Crystal");
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    ImageDisplay imageDisplay(filename);
    imageDisplay.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
    imageDisplay.setOrigin(imageDisplay.getDimensions().x/2,imageDisplay.getDimensions().y/2);
    PopupMenu context_menu({/*PopupMenuButton("Full Mode",arialbd,[&](){std::cout<<"Full mode!";}),*/
                            PopupMenuButton("Rotate left",arialbd,
                                            [&](){
                                                imageDisplay.rotate(-90);
                                            }),
                            PopupMenuButton("Rotate right",arialbd,
                                            [&](){
                                                imageDisplay.rotate(90);
                                            }),
                            PopupMenuButton("Increase zoom",arialbd,
                                            [&](){
                                                imageDisplay.scale({2,2});
                                            }),
                            PopupMenuButton("Decrease zoom",arialbd,
                                            [&](){
                                                imageDisplay.scale({0.5,0.5});
                                            })
                           });
    std::optional<sf::Vector2i> last_clicked_mouse_position;
    while(window.isOpen())
    {
        /* Event handling: Closing window and context menu */
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                {
                    sf::View view(sf::FloatRect(0, 0, event.size.width, event.size.height));
                    window.setView(view);
                }
            case sf::Event::MouseButtonReleased:
                {
                    sf::Vector2f coords = window.mapPixelToCoords({event.mouseButton.x,event.mouseButton.y});
                    MenuInterface* tmp = context_menu.containsPoint(coords);
                    if(tmp)
                        tmp->processEvent(event);
                    else if(event.mouseButton.button == sf::Mouse::Right)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        sf::Vector2f coords = window.mapPixelToCoords(mouse_pos);
                        context_menu.setPosition(coords);
                        context_menu.display();
                    }
                    else
                    {
                         context_menu.hide();
                    }
                }
                break;
            default:
                break;
            }
        }
        /* Slide */
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(last_clicked_mouse_position.has_value())
            {
                const sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
                imageDisplay.move(-(last_clicked_mouse_position.value().x-current_mouse_position.x),-(last_clicked_mouse_position.value().y-current_mouse_position.y));
            }
            last_clicked_mouse_position = sf::Mouse::getPosition(window);
        }
        else
            last_clicked_mouse_position.reset();
        /* Display */
        window.clear(sf::Color::White);
        window.draw(imageDisplay);
        window.draw(context_menu);
        window.display();
    }
    return 0;
}
