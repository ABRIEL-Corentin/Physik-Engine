////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  window.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"

namespace PhysikEngine
{
    class Window : public sf::RenderWindow
    {
        public:
            Window(const std::string &name, sf::Vector2u size);
    };
}
