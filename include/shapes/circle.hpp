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
    class Rectangle;

    class Circle : public AShape, public sf::CircleShape
    {
        friend class Rectangle;

        public:
            Circle(bool grip, const sf::Vector2f &position, float radius);

            void update() override;
            void draw(sf::RenderTarget &target) const override;
            bool collide(IShape &other) override;

            inline sf::FloatRect getBounds() const override { return getGlobalBounds(); }
            inline const sf::Vector2f &getPos() const override { return sf::CircleShape::getPosition(); }
            inline void setPos(const sf::Vector2f &position) override { return sf::CircleShape::setPosition(position); }

        private:
            bool _grip;

            bool iscollision(Rectangle &other);
            bool collide(Circle &other);
            bool collide(Rectangle &other);
    };
}
