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
#include "scene.hpp"

namespace PhysikEngine
{
    class Core
    {
        public:
            Core();
            void launch();

        private:
            Window &_window;
            Time &_time;
            Scene _scene;

            void processEvents();
            void update();
            void render();
            void drawDebugWindow();
    };
}
