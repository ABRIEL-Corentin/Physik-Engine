/*
** EPITECH PROJECT, 2023
**
** File description:
** rectangle.cpp
*/

#include "shapes/rectangle.hpp"
#include "shapes/circle.hpp"
#include "core.hpp"
#include "cmath"


namespace PhysikEngine
{
    Rectangle::Rectangle(bool grip, const sf::Vector2f &position, sf::Vector2f dimension)
        : Polygon(grip, position, 20),
          _size(dimension)
    {
        addPoint(sf::Vector2f(-dimension.x / 2, -dimension.y / 2));
        addPoint(sf::Vector2f(dimension.x / 2, -dimension.y / 2));
        addPoint(sf::Vector2f(dimension.x / 2, dimension.y / 2));
        addPoint(sf::Vector2f(-dimension.x / 2, dimension.y / 2));
    }
}
