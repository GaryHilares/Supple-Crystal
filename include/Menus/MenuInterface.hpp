#include <SFML/Graphics.hpp>

class MenuInterface: public sf::Drawable, public sf::Transformable
{
public:
    virtual MenuInterface* containsPoint(sf::Vector2f) = 0;
    virtual void processEvent(sf::Event event) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
