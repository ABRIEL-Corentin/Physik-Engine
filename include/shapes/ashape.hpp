////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  ashape.hpp
//
////////////////////////

#pragma once

#include "ishape.hpp"

namespace PhysikEngine
{
    class AShape : public IShape
    {
        public:
            AShape(bool is_static, float mass);
            virtual ~AShape() = default;

            virtual void update() override = 0;
            virtual void draw(sf::RenderTarget &target) const override = 0;
            virtual bool collide(IShape &other) override = 0;

            inline void addForce(const sf::Vector2f &force) { _acceleration += force; }
            inline void setStatic(bool is_static) { _static = is_static; }

            inline const sf::Vector2f &getVelocity() const { return _velocity; }
            inline const sf::Vector2f &getAcceleration() const { return _acceleration; }
            inline float getMass() const { return _mass; }
            inline bool getStatic() const { return _static; }

        protected:
            sf::Vector2f _velocity;
            sf::Vector2f _acceleration;
            float _mass;
            bool _static;
            float _rotation;
    };
}
