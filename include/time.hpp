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

            inline void update() { m_delta_time = m_clock.restart(); }
            inline const sf::Time &getDeltaTime() const { return m_delta_time; }

        private:
            sf::Clock m_clock;
            sf::Time m_delta_time;
    };
}
