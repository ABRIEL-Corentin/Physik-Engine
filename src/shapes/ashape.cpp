////////////////////////
//
//  Created on Mon Jun 26 2023
//
//  ashape.cpp
//
////////////////////////

#include "shapes/ashape.hpp"
#include "config.hpp"

namespace PhysikEngine
{
    AShape::AShape(bool is_static, float mass)
        : _velocity(),
          _acceleration(),
          _mass(mass),
          _rotation(),
          _static(is_static)
    { }

    void AShape::applyExternalForces()
    {
        if (_static) {
            _velocity = sf::Vector2f();
            _rotation = 0;
            return;
        }

        if (Config::getInstance().air_friction) {
            _velocity.x -= (abs(_velocity.x) >= 0.001) ? sqrt(abs(_velocity.x)) * Time::getInstance().getDeltaTime().asSeconds() * 4.0f * 0.3 * ((_velocity.x < 0) ? -1.0 : 1.0) : 0;
            _velocity.y -= (abs(_velocity.y) >= 0.001) ? sqrt(abs(_velocity.y)) * Time::getInstance().getDeltaTime().asSeconds() * 4.0f * 0.3 * ((_velocity.y < 0) ? -1.0 : 1.0) : 0;
            _rotation -= (abs(_rotation) >= 0.001) ? sqrt(abs(_rotation)) * Time::getInstance().getDeltaTime().asSeconds() * 4.0f * 0.1 * ((_rotation < 0) ? -1.0 : 1.0) : 0;
        }

        if (Config::getInstance().gravity)
            _velocity.y += 9.81f * 9.81f * Time::getInstance().getDeltaTime().asSeconds();
    }
}
