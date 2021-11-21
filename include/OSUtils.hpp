#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief Functions with OS specific implementations.
 * 
 */
namespace OS{
    /**
     * @brief Maximizes a window.
     * 
     * @param window The RenderWindow to maximize.
     */
    void maximizeWindow(sf::RenderWindow& window);
}