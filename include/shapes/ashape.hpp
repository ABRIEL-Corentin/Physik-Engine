////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  ashape.hpp
//
////////////////////////

#pragma once

#include "ishape.hpp"

namespace PhysikEngine
{
    class AShape : public IShape
    {
        public:
            virtual ~AShape() = default;

            virtual void update() override = 0;
            virtual void draw(sf::RenderTarget &target) const override = 0;
            virtual bool collide(const IShape &other) override = 0;

        protected:
            sf::Vector2f _velocity;
            sf::Vector2f _acceleration;
    };
}
