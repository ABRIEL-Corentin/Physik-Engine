////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  circle.cpp
//
////////////////////////

#include "shapes/circle.hpp"
#include "shapes/rectangle.hpp"
#include "core.hpp"
#include "utils.hpp"

namespace PhysikEngine
{
    Circle::Circle(bool grip, const sf::Vector2f &position, float radius, bool air_friction)
        : AShape(false, radius, air_friction, true),
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
        if (_grip)
            setPosition(sf::Vector2f(sf::Mouse::getPosition(Window::getInstance())));
        else {
            applyExternalForces();
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
        if (dynamic_cast<Rectangle *>(&other))
            return collide(dynamic_cast<Rectangle &>(other));
        return false;
    }

    bool Circle::iscollision(Rectangle &other)
    {
        double dx = std::abs(other.getPosition().x + (other.getSize().x / 2) - getPosition().x);
        double dy = std::abs(other.getPosition().y + (other.getSize().y / 2) - getPosition().y);

        if (dx > (other.getSize().x / 2.0 + getRadius()))
            return false;
        if (dy > (other.getSize().y / 2.0 + getRadius()))
            return false;
        if (dx <= (other.getSize().x / 2.0) || dy <= (other.getSize().y / 2.0))
            return true;

        return (std::pow((dx - other.getSize().x / 2.0), 2) + std::pow((dy - other.getSize().y / 2.0), 2) <= std::pow(getRadius(), 2));
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
            sf::Vector2f coll_normal = getPosition() - other.getPosition();

            coll_normal *= 1.0f / length(coll_normal);

            float v1_dot = dot(coll_normal, _velocity);
            sf::Vector2f v1_collide = coll_normal * v1_dot;
            sf::Vector2f v1_remainder = _velocity - v1_collide;

            float v2_dot = dot(coll_normal, other._velocity);
            sf::Vector2f v2_collide = coll_normal * v2_dot;
            sf::Vector2f v2_remainder = other._velocity - v2_collide;

            float v1_length = length(v1_collide) * sgn(v1_dot);
            float v2_length = length(v2_collide) * sgn(v2_dot);
            float common_velocity = 2 * (_mass * v1_length + other._mass * v2_length) / (_mass + other._mass);
            float v1_length_after_collision = common_velocity - v1_length;
            float v2_length_after_collision = common_velocity - v2_length;

            v1_collide *= v1_length_after_collision / v1_length;
            v2_collide *= v2_length_after_collision / v2_length;

            _velocity = v1_collide + v1_remainder;
            other._velocity = v2_collide + v2_remainder;

            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.move(other._velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }

        return coll;
    }
    bool Circle::collide(Rectangle &other)
    {
        bool coll = false;

        if (iscollision(other)) {
            coll = true;

            double collisionNormalX = (getPosition().x + getRadius()) - (other.getPosition().x + other.getSize().x / 2);
            double collisionNormalY = (getPosition().y + getRadius()) - (other.getPosition().y + other.getSize().y / 2);

            double collisionNormalLength = sqrt(collisionNormalX * collisionNormalX + collisionNormalY * collisionNormalY);
            collisionNormalX /= collisionNormalLength;
            collisionNormalY /= collisionNormalLength;

            double rect1NormalVelocity = other._velocity.x * collisionNormalX + other._velocity.y * collisionNormalY;
            double circleNormalVelocity = _velocity.x * collisionNormalX + _velocity.y * collisionNormalY;

            double rect1TangentVelocity = other._velocity.x - rect1NormalVelocity * collisionNormalX;
            double circleTangentVelocity = _velocity.x - circleNormalVelocity * collisionNormalX;

            double temp = rect1NormalVelocity;
            rect1NormalVelocity = circleNormalVelocity;
            circleNormalVelocity = temp;

            other._velocity.x = rect1NormalVelocity * collisionNormalX + rect1TangentVelocity;
            other._velocity.y = rect1NormalVelocity * collisionNormalY + rect1TangentVelocity;

            _velocity.x = circleNormalVelocity * collisionNormalX + circleTangentVelocity;
            _velocity.y = circleNormalVelocity * collisionNormalY + circleTangentVelocity;

            other._rotation = atan2(other.getPosition().y - getPosition().y, other.getPosition().x - getPosition().x) * 2;

            other.rotate(-other._rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);

            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.move(other._velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }

        return coll;
    }
}
