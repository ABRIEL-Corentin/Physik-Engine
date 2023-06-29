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
        public:
            Polygon(bool grip, const sf::Vector2f &position, float mass);

            void update() override;
            void draw(sf::RenderTarget &target) const override;
            bool collide(IShape &other) override;
            void addPoint(const sf::Vector2f &point);
            sf::Vector2f getPointGlobal(std::size_t index);
            sf::Vector2f getPointGlobal(std::size_t index, const sf::ConvexShape &shape);
            void bind();

            inline void setDrawTriangle(bool draw_mode) { _draw_triangles = draw_mode; }

        private:
            bool _grip;
            bool _draw_triangles;
            bool _air_friction;
            std::vector<sf::ConvexShape> _triangles;

            bool collide(Polygon &other);
            bool collide(const sf::ConvexShape &shape1, const sf::ConvexShape &shape2);
            bool isPointInside(const sf::ConvexShape &shape, const sf::Vector2f &point);
            bool isConvex(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3);
            bool isTriangle(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3);
    };
}
