////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  circle.hpp
//
////////////////////////

#pragma once

#include "ashape.hpp"

namespace PhysikEngine
{
    class Circle : public AShape, public sf::CircleShape
    {
        public:
            void update(Time &time) override;
            void draw(sf::RenderTarget &target) const override;
            bool collide(const IShape &other) const override;

        private:
            bool collide(const Circle &other) const;
    };
}
