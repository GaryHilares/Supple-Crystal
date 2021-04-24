#include "../include/ImageDisplay.hpp"
#include "../include/Menus/PopupMenu.hpp"
#include "../include/Menus/PopupMenuButton.hpp"
#include "../include/Menus/PopupMenuButton.hpp"
#include "../include/App.hpp"
#include <iostream>

int App::SuppleCrystal::run(int argc, char* argv[])
{
    sf::Clock timer;
    sf::Font arialbd;
    if(!arialbd.loadFromFile("arialbd.ttf"))
    {
        std::cerr << "Couldn't open arialbd.ttf!";
        return 1;
    }
    std::string filename = argv[1];
    ImageDisplay imageDisplay(filename);
    sf::RenderWindow window(sf::VideoMode(imageDisplay.getGlobalBounds().width,imageDisplay.getGlobalBounds().height),"GViewer");
    PopupMenu context_menu({PopupMenuButton("Full Mode",arialbd,[&](){std::cout<<"Full mode!";}),
                            PopupMenuButton("Rotate left",arialbd,
                                            [&](){
                                                imageDisplay.rotateLeft();
                                            }),
                            PopupMenuButton("Rotate right",arialbd,
                                            [&](){
                                                imageDisplay.rotateRight();
                                            })
                           });
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                {
                    sf::Vector2f coords = window.mapPixelToCoords({event.mouseButton.x,event.mouseButton.y});
                    MenuInterface* tmp = context_menu.containsPoint(coords);
                    if(tmp)
                        tmp->processEvent(event);
                    else if(event.mouseButton.button == sf::Mouse::Left)
                        context_menu.hide();
                }
                break;
            default:
                break;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f coords = window.mapPixelToCoords(mouse_pos);
            context_menu.setPosition(coords);
            context_menu.display();
        }
        window.clear();
        window.draw(imageDisplay);
        window.draw(context_menu);
        window.display();
    }
    return 0;
}
