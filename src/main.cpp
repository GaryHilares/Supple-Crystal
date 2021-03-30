#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Invalid number of arguments!" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    sf::Texture texture;
    texture.loadFromFile(filename);
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height),"GViewer");
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
