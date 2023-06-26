////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  circle.cpp
//
////////////////////////

#include "shapes/circle.hpp"
#include "core.hpp"

namespace PhysikEngine
{
    Circle::Circle(bool grip, const sf::Vector2f &position, float radius)
        : _grip(grip)
    {
        setRadius(radius);
        setOrigin(sf::Vector2f(radius, radius));
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(-2);
        setFillColor(sf::Color::Transparent);
        setPosition(position);
    }

    void Circle::update()
    {
        if (!_grip)
            return;

        setPosition(sf::Vector2f(sf::Mouse::getPosition(Window::getInstance())));
    }

    void Circle::draw(sf::RenderTarget &target) const
    {
        target.draw(*this);
    }

    bool Circle::collide(const IShape &other)
    {
        if (dynamic_cast<const Circle *>(&other))
            return collide(dynamic_cast<const Circle &>(other));
        return false;
    }

    bool Circle::collide(const Circle &other)
    {
        float x1 = other.getPosition().x;
        float y1 = other.getPosition().y;
        float r1 = other.getRadius();
        float x2 = getPosition().x;
        float y2 = getPosition().y;
        float r2 = getRadius();
        bool coll = std::fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);

        if (coll)
            setOutlineColor(sf::Color::Red);
        else
            setOutlineColor(sf::Color::Green);

        return coll;
    }
}
