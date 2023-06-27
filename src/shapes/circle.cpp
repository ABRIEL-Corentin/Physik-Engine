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
        : AShape(false, radius),
          _grip(grip)
    {
        std::cout << "mass: " << _mass << std::endl;
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
        if (_grip)
            setPosition(sf::Vector2f(sf::Mouse::getPosition(Window::getInstance())));
        else {
            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            _velocity += _acceleration;
            _acceleration = sf::Vector2f();
        }
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

        if (coll) {
            sf::Vector2f tmp_vel = _velocity;

            _velocity = sf::Vector2f(
                (_velocity.x * (_mass - other._mass) + (2 * other._mass * other._velocity.x)) / (_mass + other._mass),
                (_velocity.y * (_mass - other._mass) + (2 * other._mass * other._velocity.y)) / (_mass + other._mass)
            );

            other._velocity = sf::Vector2f(
                (other._velocity.x * (other._mass - _mass) + (2 * _mass * tmp_vel.x)) / (_mass + other._mass),
                (other._velocity.y * (other._mass - _mass) + (2 * _mass * tmp_vel.y)) / (_mass + other._mass)
            );

            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.move(other._velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }

        return coll;
    }
}
