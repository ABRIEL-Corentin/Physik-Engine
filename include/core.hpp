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
#include "time.hpp"

namespace PhysikEngine
{
    class Core
    {
        public:
            Core(const std::string &window_name, sf::Vector2u window_size);

            void launch();

        private:
            Window m_window;
            Time &m_time;

            void processEvents();
            void update();
            void render();
    };
}
