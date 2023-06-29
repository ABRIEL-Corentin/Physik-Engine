////////////////////////
//
//  Created on Tue Jun 27 2023
//
//  polygon.hpp
//
////////////////////////

#pragma once

#include "ashape.hpp"

namespace PhysikEngine
{
    class Polygon : public AShape, public sf::ConvexShape
    {
        private:
            using ContactInfo = struct ContactInfo
            {
                bool collided;
                std::vector<sf::Vector2f> points;
                sf::Vector2f normal;

                ContactInfo();
            };

        public:
            Polygon(bool grip, const sf::Vector2f &position, float mass);

            void update() override;
            void draw(sf::RenderTarget &target) const override;
            bool collide(IShape &other) override;
            void addPoint(const sf::Vector2f &point);
            sf::Vector2f getPointGlobal(std::size_t index);
            sf::Vector2f getPointGlobal(std::size_t index, const sf::ConvexShape &shape);

        private:
            bool _grip;
            float _inv_mass;

            bool collide(Polygon &other);
            ContactInfo findContactPoints(Polygon &other);
    };
}
