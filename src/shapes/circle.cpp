////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  circle.cpp
//
////////////////////////

#include "shapes/circle.hpp"

namespace PhysikEngine
{
    void Circle::update(Time &time)
    {

    }

    void Circle::draw(sf::RenderTarget &target) const
    {
        target.draw(*this);
    }

    bool Circle::collide(const IShape &other) const
    {
        if (dynamic_cast<const Circle *>(&other))
            return collide(dynamic_cast<const Circle &>(other));
        return false;
    }

    bool Circle::collide(const Circle &other) const
    {
        float x1 = other.getPosition().x;
        float y1 = other.getPosition().y;
        float r1 = other.getRadius();
        float x2 = getPosition().x;
        float y2 = getPosition().y;
        float r2 = getRadius();

        return std::fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
    }
}
