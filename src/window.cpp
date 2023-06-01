////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  window.cpp
//
////////////////////////

#include "window.hpp"

namespace PhysikEngine
{
    Window::Window(const std::string &name, sf::Vector2u size)
        : sf::RenderWindow({size.x, size.y, 32}, name)
    {
        setFramerateLimit(60);
    }
}
