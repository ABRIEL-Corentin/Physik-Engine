/*
** EPITECH PROJECT, 2023
**
** File description:
** rectangle.hpp
*/

#pragma once

#include "ashape.hpp"

namespace PhysikEngine
{
    class Rectangle : public AShape, public sf::RectangleShape
    {
        public:
            Rectangle(bool grip, const sf::Vector2f &position, sf::Vector2f dimension, bool air_friction);

            void update() override;
            void draw(sf::RenderTarget &target) const override;
            bool collide(IShape &other) override;

        private:
            bool _grip;
            bool _air_friction;
            bool collide(Rectangle &other);
            bool iscollision(Rectangle &other);
            double dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3);
    };
}