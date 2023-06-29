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
    Rectangle::Rectangle(bool grip, const sf::Vector2f &position, sf::Vector2f dimension, bool air_friction)
        : AShape(false, abs(dimension.x * dimension.y), air_friction, true),
          _grip(grip)
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
            applyExternalForces();
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
        if (dynamic_cast<Circle *>(&other))
            return collide(dynamic_cast<Circle &>(other));
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

    bool Rectangle::iscollision(Circle &other)
    {
        double dx = std::abs(getPosition().x + (getSize().x / 2) - other.getPosition().x);
        double dy = std::abs(getPosition().y + (getSize().y / 2) - other.getPosition().y);

        if (dx > (getSize().x / 2.0 + other.getRadius()))
            return false;
        if (dy > (getSize().y / 2.0 + other.getRadius()))
            return false;
        if (dx <= (getSize().x / 2.0) || dy <= (getSize().y / 2.0))
            return true;

        return (std::pow((dx - getSize().x / 2.0), 2) + std::pow((dy - getSize().y / 2.0), 2) <= std::pow(other.getRadius(), 2));
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

    bool Rectangle::collide(Circle &other)
    {
        bool coll = false;

        if (iscollision(other)) {
            coll = true;

            double collisionNormalX = (getPosition().x + getSize().x / 2) - (other.getPosition().x + other.getRadius());
            double collisionNormalY = (getPosition().y + getSize().y / 2) - (other.getPosition().y + other.getRadius());

            double collisionNormalLength = sqrt(collisionNormalX * collisionNormalX + collisionNormalY * collisionNormalY);
            collisionNormalX /= collisionNormalLength;
            collisionNormalY /= collisionNormalLength;

            double rect1NormalVelocity = _velocity.x * collisionNormalX + _velocity.y * collisionNormalY;
            double circleNormalVelocity = other._velocity.x * collisionNormalX + other._velocity.y * collisionNormalY;

            double rect1TangentVelocity = _velocity.x - rect1NormalVelocity * collisionNormalX;
            double circleTangentVelocity = other._velocity.x - circleNormalVelocity * collisionNormalX;

            double temp = rect1NormalVelocity;
            rect1NormalVelocity = circleNormalVelocity;
            circleNormalVelocity = temp;

            _velocity.x = rect1NormalVelocity * collisionNormalX + rect1TangentVelocity;
            _velocity.y = rect1NormalVelocity * collisionNormalY + rect1TangentVelocity;

            other._velocity.x = circleNormalVelocity * collisionNormalX + circleTangentVelocity;
            other._velocity.y = circleNormalVelocity * collisionNormalY + circleTangentVelocity;

            _rotation = atan2(other.getPosition().y - getPosition().y, other.getPosition().x - getPosition().x) * 2;

            rotate(-_rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);

            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.move(other._velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }
        return coll;
    }
}
