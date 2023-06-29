/*
** EPITECH PROJECT, 2023
**
** File description:
** rectangle.cpp
*/

#include "shapes/rectangle.hpp"
#include "core.hpp"
#include "cmath"


namespace PhysikEngine
{
    Rectangle::Rectangle(bool grip, const sf::Vector2f &position, sf::Vector2f dimension, bool air_friction)
        : AShape(false, abs(dimension.x * dimension.y)),
          _grip(grip),
          _air_friction(air_friction)
    {
        std::cout << "mass: " << _mass << std::endl;
        setSize(dimension);
        setOrigin(0,0);
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(-2);
        setFillColor(sf::Color::Transparent);
        setPosition(position);
        if (grip)
            setFillColor(sf::Color::Cyan);
        else
            setFillColor(sf::Color::Magenta);
    }

    void Rectangle::update()
    {
        if (_grip)
            setPosition(sf::Vector2f(sf::Mouse::getPosition(Window::getInstance())));
        else {
            _velocity.x -= (_air_friction && abs(_velocity.x) >= 0.001) ? sqrt(abs(_velocity.x)) * Time::getInstance().getDeltaTime().asSeconds() * 4.0f * 0.3 * ((_velocity.x < 0) ? -1.0 : 1.0) : 0;
            _velocity.y -= (_air_friction && abs(_velocity.y) >= 0.001) ? sqrt(abs(_velocity.y)) * Time::getInstance().getDeltaTime().asSeconds() * 4.0f * 0.3 * ((_velocity.y < 0) ? -1.0 : 1.0) : 0;
            _rotation -= (_air_friction && abs(_rotation) >= 0.001) ? sqrt(abs(_rotation)) * Time::getInstance().getDeltaTime().asSeconds() * 4.0f * 0.1 * ((_rotation < 0) ? -1.0 : 1.0) : 0;
            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            _velocity += _acceleration;
            _acceleration = sf::Vector2f();
            rotate(-(_rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f));
        }
    }

    void Rectangle::draw(sf::RenderTarget &target) const
    {
        target.draw(*this);
    }

    bool Rectangle::collide(IShape &other)
    {
        if (dynamic_cast<Rectangle *>(&other))
            return collide(dynamic_cast<Rectangle &>(other));
        return false;
    }

    double Rectangle::dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3) {
        return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y);
    }

    bool Rectangle::iscollision(Rectangle &other)
    {
        float angle = (getRotation() * M_PI) / 180.0;
        float halfWidth = (getSize().x / 2.0);
        float halfHeight = (getSize().y / 2.0);
        float centerX = getPosition().x + halfWidth;
        float centerY = getPosition().y + halfHeight;
        sf::Vector2f rect1points[4];
        sf::Vector2f rect2points[4];

        rect1points[0] = {centerX + cos(angle) * halfWidth - sin(angle) * halfHeight, centerY + sin(angle) * halfWidth + cos(angle) * halfHeight};
        rect1points[1] = {centerX - cos(angle) * halfWidth - sin(angle) * halfHeight, centerY - sin(angle) * halfWidth + cos(angle) * halfHeight};
        rect1points[2] = {2 * centerX - rect1points[0].x, 2 * centerY - rect1points[0].y};
        rect1points[3] = {2 * centerX - rect1points[1].x, 2 * centerY - rect1points[1].y};

        angle = (other.getRotation() * M_PI) / 180.0;
        halfWidth = (other.getSize().x / 2.0);
        halfHeight = (other.getSize().y / 2.0);
        centerX = other.getPosition().x + halfWidth;
        centerY = other.getPosition().y + halfHeight;
        rect2points[0] = {centerX + cos(angle) * halfWidth - sin(angle) * halfHeight, centerY + sin(angle) * halfWidth + cos(angle) * halfHeight};
        rect2points[1] = {centerX - cos(angle) * halfWidth - sin(angle) * halfHeight, centerY - sin(angle) * halfWidth + cos(angle) * halfHeight};
        rect2points[2] = {2 * centerX - rect2points[0].x, 2 * centerY - rect2points[0].y};
        rect2points[3] = {2 * centerX - rect2points[1].x, 2 * centerY - rect2points[1].y};

        if (dotProduct(rect1points[0], rect1points[1], rect2points[0]) * dotProduct(rect1points[0], rect1points[1], rect2points[1]) < 0 ||
            dotProduct(rect1points[2], rect1points[3], rect2points[0]) * dotProduct(rect1points[2], rect1points[3], rect2points[1]) < 0 ||
            dotProduct(rect2points[0], rect2points[1], rect1points[0]) * dotProduct(rect2points[0], rect2points[1], rect1points[1]) < 0 ||
            dotProduct(rect2points[2], rect2points[3], rect1points[0]) * dotProduct(rect2points[2], rect2points[3], rect1points[1]) < 0)
            return true;
        return false;
    }

    bool Rectangle::collide(Rectangle &other)
    {
        bool coll = false;

        if (iscollision(other)) {
            coll = true;
            double collisionNormalX = (getPosition().x + getSize().x / 2) - (other.getPosition().x + other.getSize().x / 2);
            double collisionNormalY = (getPosition().y + getSize().y / 2) - (other.getPosition().y + other.getSize().y / 2);

            double collisionNormalLength = sqrt(collisionNormalX * collisionNormalX + collisionNormalY * collisionNormalY);
            collisionNormalX /= collisionNormalLength;
            collisionNormalY /= collisionNormalLength;

            double rect1NormalVelocity = _velocity.x * collisionNormalX + _velocity.y * collisionNormalY;
            double rect2NormalVelocity = other._velocity.x * collisionNormalX + other._velocity.y * collisionNormalY;

            double rect1TangentVelocity = _velocity.x - rect1NormalVelocity * collisionNormalX;
            double rect2TangentVelocity = other._velocity.x - rect2NormalVelocity * collisionNormalX;

            double temp = rect1NormalVelocity;
            rect1NormalVelocity = rect2NormalVelocity;
            rect2NormalVelocity = temp;

            _velocity.x = rect1NormalVelocity * collisionNormalX + rect1TangentVelocity;
            _velocity.y = rect1NormalVelocity * collisionNormalY + rect1TangentVelocity;

            other._velocity.x = rect2NormalVelocity * collisionNormalX + rect2TangentVelocity;
            other._velocity.y = rect2NormalVelocity * collisionNormalY + rect2TangentVelocity;

            _rotation = atan2(other.getPosition().y - getPosition().y, other.getPosition().x - getPosition().x);
            other._rotation = atan2(getPosition().y - other.getPosition().y , getPosition().x - other.getPosition().x);

            rotate(-_rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.rotate(-other. _rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);

            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.move(other._velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }

        return coll;
    }
}