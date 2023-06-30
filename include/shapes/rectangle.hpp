/*
** EPITECH PROJECT, 2023
**
** File description:
** rectangle.hpp
*/

#pragma once

#include "ashape.hpp"
#include "shapes/polygon.hpp"

namespace PhysikEngine
{
    class Circle;

    class Rectangle : public Polygon
    {
        friend class Circle;

        public:
            Rectangle(bool grip, const sf::Vector2f &position, sf::Vector2f dimension);

            inline const sf::Vector2f &getSize() const { return _size; }
        private:
            sf::Vector2f _size;
    };
}
