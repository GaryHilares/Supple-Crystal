#pragma once
#include "Button.hpp"
#include <functional>

/**
 * @brief Class for default toolbar menu buttons.
 *
 */
class ToolbarMenuButton : public Button {
private:
    sf::RectangleShape m_background;
    std::function<void()> m_onClick;

public:
    /**
     * @brief Construct a new ToolbarMenuButton object.
     *
     * @param new_on_click Function to run when the button is clicked.
     */
    ToolbarMenuButton(const std::function<void()>& newOnClick);

    /**
     * @brief Draws the object to a RenderTarget.
     *
     * @param target RenderTarget to draw the object.
     * @param states The states in which the object should be drawn.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Processes an event and changes the ToolbarMenuButton accordingly.
     *
     * @param event Event to process.
     */
    void processEvent(sf::Event event) override;

    sf::Vector2u getSize() const override;
};