#include "../../../../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../../../../include/UI/Settings/style-constants.hpp"

PopupMenuButton::PopupMenuButton(const std::string& textToDisplay, const sf::Font& newFont, const std::function<void()>& newOnClick)
    : m_background({ Constants::PopupMenu::Button::Width, Constants::PopupMenu::Button::Height })
    , m_font(newFont)
    , m_text(textToDisplay, m_font, Constants::PopupMenu::Button::FontSize)
    , m_onClick(newOnClick)
{
    m_text.move(Constants::PopupMenu::Button::TextPadding::Left, Constants::PopupMenu::Button::TextPadding::Top);
    m_background.setFillColor(sf::Color::White);
    m_text.setFillColor(sf::Color::Black);
}

void PopupMenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_background, states);
    target.draw(m_text, states);
}

void PopupMenuButton::processEvent(sf::Event mouse_event)
{
    if (mouse_event.type == sf::Event::MouseButtonReleased && mouse_event.mouseButton.button == sf::Mouse::Left)
        return m_onClick();
}

sf::Vector2u PopupMenuButton::getSize() const
{
    return { Constants::PopupMenu::Button::Width, Constants::PopupMenu::Button::Height };
}