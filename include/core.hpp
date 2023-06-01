////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  core.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "window.hpp"

namespace PhysikEngine
{
    class Core
    {
        public:
            Core(const std::string &window_name, sf::Vector2u window_size);

            void launch();

        private:
            Window m_window;

            void processEvents();
    };
}
