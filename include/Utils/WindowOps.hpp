#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

/**
 * @brief Prevents the default resizing SFML does to the contents of a window.
 *
 * @param window The window which threw the resize event.
 * @param resize_event The resize event triggered by the resize button.
 * @param throw FatalError Terminates the program if sf::Event is not a resize event.
 */
void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event);

/**
 * @brief Functions with OS specific implementations.
 *
 */
namespace OS {
/**
 * @brief Maximizes a window.
 *
 * @param window The RenderWindow to maximize.
 */
void maximizeWindow(sf::RenderWindow& window);
}