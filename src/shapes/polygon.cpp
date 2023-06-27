////////////////////////
//
//  Created on Tue Jun 27 2023
//
//  polygon.cpp
//
////////////////////////

#include "shapes/polygon.hpp"
#include "window.hpp"
#include "utils.hpp"

namespace PhysikEngine
{
    Polygon::Polygon(bool grip, const sf::Vector2f &position, float mass)
        : AShape(false, mass),
          sf::ConvexShape(0),
          _grip(grip),
          _draw_triangles(false),
          _triangles()
    {
        setPosition(position);
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(-2);
        setFillColor(sf::Color::Magenta);
    }

    void Polygon::update()
    {
        setOutlineColor(sf::Color::Red);
        if (_grip)
            setPosition(sf::Vector2f(sf::Mouse::getPosition(Window::getInstance())));

        for (auto triangle = _triangles.begin(); triangle != _triangles.end(); ++triangle) {
            triangle->setPosition(getPosition());
            triangle->setRotation(getRotation());
            triangle->setScale(getScale());
            triangle->setOutlineColor(sf::Color::Red);
        }
    }

    void Polygon::draw(sf::RenderTarget &target) const
    {
        if (_draw_triangles)
            for (auto triangle = _triangles.begin(); triangle != _triangles.end(); ++triangle)
                target.draw(*triangle);
        else
            target.draw(*this);
    }

    bool Polygon::collide(IShape &other)
    {
        if (dynamic_cast<Polygon *>(&other))
            return collide(dynamic_cast<Polygon &>(other));
        return false;
    }

    void Polygon::addPoint(const sf::Vector2f &point)
    {
        std::size_t index = getPointCount();

        setPointCount(index + 1);
        setPoint(index, point);
    }

    sf::Vector2f Polygon::getPointGlobal(std::size_t index)
    {
        return getTransform().transformPoint(getPoint(index));
    }

    sf::Vector2f Polygon::getPointGlobal(std::size_t index, const sf::ConvexShape &shape)
    {
        return shape.getTransform().transformPoint(shape.getPoint(index));
    }

    void Polygon::bind()
    {
        _triangles.clear();
        std::vector<sf::Vector2f> points = std::vector<sf::Vector2f>();

        for (std::size_t i = 0; i < getPointCount(); ++i)
            points.push_back(getPoint(i));

        while (getPointCount()) {
            int n = points.size();
            bool ear_found = false;

            for (int i = 0; i < n; ++i) {
                int prev = (i + n - 1) % n;
                int next = (i + 1) % n;

                const sf::Vector2f &p1 = points.at(prev);
                const sf::Vector2f &p2 = points.at(i);
                const sf::Vector2f &p3 = points.at(next);

                if (isTriangle(p1, p2, p3)) {
                    sf::ConvexShape triangle = sf::ConvexShape(3);
                    triangle.setPoint(0, p1);
                    triangle.setPoint(1, p2);
                    triangle.setPoint(2, p3);
                    triangle.setOutlineColor(sf::Color::Red);
                    triangle.setOutlineThickness(-2);
                    triangle.setFillColor(sf::Color::Magenta);

                    _triangles.push_back(triangle);

                    points.erase(points.begin() + i);
                    ear_found = true;
                    break;
                }
            }

            if (!ear_found)
                break;
        }
    }

    bool Polygon::collide(Polygon &other)
    {
        for (auto other_triangle = other._triangles.begin(); other_triangle != other._triangles.end(); ++other_triangle) {
            for (auto triangle = _triangles.begin(); triangle != _triangles.end(); ++triangle) {
                if (collide(*other_triangle, *triangle)) {
                    setOutlineColor(sf::Color::Green);
                    other.setOutlineColor(sf::Color::Green);
                    triangle->setOutlineColor(sf::Color::Green);
                    other_triangle->setOutlineColor(sf::Color::Green);
                    return true;
                }
            }
        }
        return false;
    }

    bool Polygon::collide(const sf::ConvexShape &shape1, const sf::ConvexShape &shape2)
    {
        for (std::size_t i = 0; i < shape1.getPointCount(); ++i)
            if (isPointInside(shape2, getPointGlobal(i, shape1)))
                return true;

        for (std::size_t i = 0; i < shape2.getPointCount(); ++i)
            if (isPointInside(shape1, getPointGlobal(i, shape2)))
                return true;
        return false;
    }

    bool Polygon::isPointInside(const sf::ConvexShape &shape, const sf::Vector2f &point)
    {
        bool result = false;
        std::size_t i = 0;
        int j = shape.getPointCount() - 1;

        for (; i < shape.getPointCount(); j = i++) {
            sf::Vector2f pi = getPointGlobal(i, shape);
            sf::Vector2f pj = getPointGlobal(j, shape);
            if (((pi.y > point.y) != (pj.y > point.y)) && (point.x < (pj.x - pi.x) * (point.y - pi.y) / (pj.y - pi.y) + pi.x))
                result = !result;
        }
        return result;
    }

    bool Polygon::isConvex(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3)
    {
        return crossProduct(p1, p2, p3) >= 0;
    }

    bool Polygon::isTriangle(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3)
    {
        for (std::size_t i = 0; i < getPointCount(); ++i) {
            sf::Vector2f point = getPoint(i);
            if ((point != p1) && (point != p2) && (point != p3))
                if (isConvex(p1, p2, point) && isConvex(p2, p3, point) && isConvex(p3, p1, point))
                    return false;
        }
        return true;
    }
}
