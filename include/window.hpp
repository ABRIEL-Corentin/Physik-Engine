////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  window.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "singleton.hpp"

namespace PhysikEngine
{
    class Window : public sf::RenderWindow, public Singleton<Window>
    {
        public:
            Window();
            ~Window();

        private:
            void initImGui();
    };
}
