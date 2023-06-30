////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  ishape.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "time.hpp"

namespace PhysikEngine
{
    class IShape
    {
        public:
            virtual ~IShape() = default;

            virtual void update() = 0;
            virtual void draw(sf::RenderTarget &target) const = 0;
            virtual bool collide(IShape &other) = 0;
            virtual sf::FloatRect getBounds() const = 0;
            virtual const sf::Vector2f &getPos() const = 0;
            virtual void setPos(const sf::Vector2f &position) = 0;
            virtual void multiplyVelocity(const sf::Vector2f &velocity) = 0;
    };
}
