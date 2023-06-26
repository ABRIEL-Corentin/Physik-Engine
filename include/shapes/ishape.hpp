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
            virtual bool collide(const IShape &other) = 0;
    };
}
