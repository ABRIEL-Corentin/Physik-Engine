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
            Circle(bool grip, const sf::Vector2f &position, float radius);

            void update() override;
            void draw(sf::RenderTarget &target) const override;
            bool collide(IShape &other) override;

        private:
            bool _grip;

            bool collide(Circle &other);
    };
}
