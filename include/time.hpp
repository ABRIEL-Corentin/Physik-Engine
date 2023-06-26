////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  time.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "singleton.hpp"

namespace PhysikEngine
{
    class Time : public Singleton<Time>
    {
        public:
            Time();

            inline void update() { _delta_time = _clock.restart(); }
            inline const sf::Time &getDeltaTime() const { return _delta_time; }

        private:
            sf::Clock _clock;
            sf::Time _delta_time;
    };
}
