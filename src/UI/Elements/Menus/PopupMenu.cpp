#include "../../../../include/UI/Elements/Menus/PopupMenu.hpp"
#include <cassert>
#include <optional>

PopupMenu::PopupMenu(const std::vector<std::shared_ptr<Button>>& newButtons)
    : m_buttons(newButtons)
    , m_doDisplay(false)
    , m_border(sf::Vector2f(newButtons[0]->getSize().x, newButtons[0]->getSize().y * newButtons.size()))
{
    std::optional<sf::Vector2u> buttonsSize;
    for (const std::shared_ptr<Button>& button : newButtons) {
        if (buttonsSize.has_value())
            assert(button->getSize() == buttonsSize);
        else
            buttonsSize = button->getSize();
    }
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(sf::Color::Black);
    m_border.setOutlineThickness(1);
    unsigned int x = 0;
    for (std::shared_ptr<Button>& button : m_buttons) {
        button->setPosition(0, x);
        x += button->getSize().y;
    }
}

void PopupMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_doDisplay) {
        states.transform *= this->getTransform();
        target.draw(m_border, states);
        for (const std::shared_ptr<Button>& button : m_buttons)
            target.draw(*button, states);
    }
}

void PopupMenu::display(bool newDoDisplay)
{
    m_doDisplay = newDoDisplay;
}

UIElement* PopupMenu::getButtonFromCoords(sf::Vector2f pointCoords)
{
    return this->containsPoint(pointCoords) && !m_buttons.empty()
        ? dynamic_cast<UIElement*>(m_buttons[(pointCoords.y - this->getPosition().y) / m_buttons[0]->getSize().y].get())
        : nullptr;
}

void PopupMenu::processEvent(sf::Event event)
{
    const sf::Vector2f coords = { float(event.mouseButton.x), float(event.mouseButton.y) };
    UIElement* buttonInCoords = this->getButtonFromCoords(coords);
    if (buttonInCoords)
        buttonInCoords->processEvent(event);
}

bool PopupMenu::containsPoint(sf::Vector2f pointCoords)
{
    sf::Vector2f position = this->getPosition();
    return m_doDisplay
        && !m_buttons.empty()
        && position.y < pointCoords.y
        && position.y + m_buttons.size() * m_buttons[0]->getSize().y > pointCoords.y
        && position.x < pointCoords.x
        && position.x + m_buttons[0]->getSize().x > pointCoords.x;
}

sf::Vector2u PopupMenu::getSize() const
{
    return !m_buttons.empty() ? sf::Vector2u { m_buttons[0]->getSize().x, (unsigned int)m_buttons.size() * m_buttons[0]->getSize().y } : sf::Vector2u { 0, 0 };
}