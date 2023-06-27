/*
** EPITECH PROJECT, 2023
**
** File description:
** rectangle.cpp
*/

#include "shapes/rectangle.hpp"
#include "core.hpp"

namespace PhysikEngine
{
    Rectangle::Rectangle(bool grip, const sf::Vector2f &position, sf::Vector2f dimension)
        : AShape(false, abs(dimension.x * dimension.y)),
          _grip(grip)
    {
        std::cout << "mass: " << _mass << std::endl;
        setSize(dimension);
        setOrigin(sf::Vector2f(dimension.x / 2, dimension.y / 2));
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

    bool Rectangle::collide(Rectangle &other)
    {
        bool coll = false;
        double rect1_xf = getPosition().x;
        double rect1_yf = getPosition().y;

        if (rect1_xf >= other.getPosition().x && rect1_xf <= other.getPosition().x + other.getSize().x && rect1_yf >= other.getPosition().y && rect1_yf <= other.getPosition().y + other.getSize().y)
            coll = true;

        if (coll) {
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
            rotate(-_rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.rotate(- _rotation * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);

            move(_velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            other.move(other._velocity * Time::getInstance().getDeltaTime().asSeconds() * 4.0f);
            setOutlineColor(sf::Color::Red);
        } else {
            setOutlineColor(sf::Color::Green);
        }

        return coll;
    }
}