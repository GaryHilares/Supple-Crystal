#include "../../../../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../../../../include/UI/Settings/style-constants.hpp"
#include <cassert>
#include <optional>

UIElement* ToolbarMenu::getButtonFromCoords(sf::Vector2f pointCoords)
{
    if (!this->containsPoint(pointCoords) || m_buttons.empty())
        return nullptr;
    sf::Vector2u buttonsSize = m_buttons[0]->getSize();
    int buttonsPerRow = m_size.x / buttonsSize.x;
    if (buttonsPerRow == 0)
        buttonsPerRow = 1;
    int buttonNumber = (pointCoords.x - this->getPosition().x) / buttonsSize.x;
    int rowNumber = (pointCoords.y - this->getPosition().y) / buttonsSize.y;
    std::vector<std::shared_ptr<Button>>::size_type index = buttonNumber + rowNumber * buttonsPerRow;
    return index < m_buttons.size()
        ? dynamic_cast<UIElement*>(m_buttons[index].get())
        : nullptr;
}

ToolbarMenu::ToolbarMenu(const std::vector<std::shared_ptr<Button>>& newButtons, int newWidth)
    : m_buttons(newButtons)
{
    std::optional<sf::Vector2u> buttonsSize;
    for (const std::shared_ptr<Button>& button : newButtons) {
        if (buttonsSize.has_value())
            assert(button->getSize() == buttonsSize);
        else
            buttonsSize = button->getSize();
    }
    this->setWidth(newWidth);
    m_background.setFillColor(sf::Color(Constants::ToolbarMenu::Color));
}

void ToolbarMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(m_background);
    for (const std::shared_ptr<Button>& button : m_buttons)
        target.draw(*button, states);
}

void ToolbarMenu::processEvent(sf::Event event)
{
    const sf::Vector2f coords = { float(event.mouseButton.x), float(event.mouseButton.y) };
    UIElement* buttonInCoords = this->getButtonFromCoords(coords);
    if (buttonInCoords)
        buttonInCoords->processEvent(event);
}

sf::Vector2u ToolbarMenu::getSize() const
{
    return { m_size.x, m_size.y };
}

bool ToolbarMenu::containsPoint(sf::Vector2f pointCoords)
{
    sf::Vector2f position = this->getPosition();
    return position.y < pointCoords.y
        && position.y + m_size.y > pointCoords.y
        && position.x < pointCoords.x
        && position.x + m_size.x > pointCoords.x;
}

void ToolbarMenu::setWidth(unsigned int newWidth)
{
    m_size.x = newWidth;
    unsigned int x = 0;
    unsigned int y = 0;
    for (std::shared_ptr<Button>& button : m_buttons) {
        if (x + button->getSize().x > newWidth && x != 0) {
            x = 0;
            y += button->getSize().y;
        }
        button->setPosition(x, y);
        x += button->getSize().x;
    }
    m_size.y = y;
    if (!m_buttons.empty() && x != 0)
        m_size.y += m_buttons[m_buttons.size() - 1]->getSize().y;
    m_background.setSize(sf::Vector2f { (float)m_size.x, (float)m_size.y });
}