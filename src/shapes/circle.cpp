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
        : AShape(!grip),
          _grip(grip)
    {

        setRadius(radius);
        setOrigin(sf::Vector2f(radius, radius));
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(-2);
        setFillColor(sf::Color::Transparent);
        setPosition(position);
        if (grip)
            setFillColor(sf::Color::Cyan);
        else
            setFillColor(sf::Color::Magenta);
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

    bool Circle::collide(IShape &other)
    {
        if (dynamic_cast<Circle *>(&other))
            return collide(dynamic_cast<Circle &>(other));
        return false;
    }

    bool Circle::collide(Circle &other)
    {
        float x1 = getPosition().x;
        float y1 = getPosition().y;
        float r1 = getRadius();
        float x2 = other.getPosition().x;
        float y2 = other.getPosition().y;
        float r2 = other.getRadius();
        bool coll = std::fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);

        if (coll && !_static) {
            float dist = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
            float dx = x2 - x1;
            float dy = y2 - y1;
            float nx = dx / dist;
            float ny = dy / dist;
            float touchDistFromB1 = (dist * (r1 / (r1 + r2)));
            float contactX = x1 + nx * touchDistFromB1;
            float contactY = y1 + ny * touchDistFromB1;

            setPosition(sf::Vector2f(
                contactX - nx * r1,
                contactY - ny * r1
            ));

            if (!other._static) {
                other.setPosition(sf::Vector2f(
                    contactX + nx * r2,
                    contactY + ny * r2
                ));
            }
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }

        return coll;
    }
}
