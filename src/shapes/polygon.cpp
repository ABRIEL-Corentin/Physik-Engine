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
    Polygon::ContactInfo::ContactInfo()
        : collided(false),
          points(),
          normal()
    { }

    Polygon::Polygon(bool grip, const sf::Vector2f &position, float mass)
        : AShape(false, mass),
          sf::ConvexShape(0),
          _grip(grip),
          _inv_mass(_mass ? 1.0f / _mass : 0)
    {
        setPosition(position);
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(-2);
        setFillColor(sf::Color::Cyan);
    }

    void Polygon::update()
    {
        setOutlineColor(sf::Color::Red);
        if (_grip)
            setPosition(sf::Vector2f(sf::Mouse::getPosition(Window::getInstance())));

        applyExternalForces();
        if (_static)
            return;

        move(_velocity * Time::getInstance().getDeltaTime().asSeconds());
        rotate(_rotation * Time::getInstance().getDeltaTime().asSeconds());
        _velocity += _acceleration;
        _acceleration = sf::Vector2f();
    }

    void Polygon::draw(sf::RenderTarget &target) const
    {
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

    bool Polygon::collide(Polygon &other)
    {
        ContactInfo contact_info = findContactPoints(other);
        float e = 0.2f;
        float deg_to_rad = 180 / M_PI;

        if (!contact_info.collided)
            return false;

        std::vector<sf::Vector2f> ra_vec = std::vector<sf::Vector2f>();
        std::vector<sf::Vector2f> rb_vec = std::vector<sf::Vector2f>();
        std::vector<sf::Vector2f> impulse_vec = std::vector<sf::Vector2f>();
        float inertia_a = _mass * (std::pow(_velocity.x, 2) + std::pow(_velocity.y, 2));
        float inv_inertia_a = inertia_a > 0 ? 1.0f / inertia_a : 0;
        float inertia_b = other._mass * (std::pow(other._velocity.x, 2) + std::pow(other._velocity.y, 2));
        float inv_inertia_b = inertia_b > 0 ? 1.0f / inertia_b : 0;

        for (auto contact_point = contact_info.points.begin(); contact_point != contact_info.points.end(); ++contact_point) {
            sf::Vector2f ra = *contact_point - getPosition();
            sf::Vector2f rb = *contact_point - other.getPosition();
            sf::Vector2f ra_perp = sf::Vector2f(-ra.y, ra.x);
            sf::Vector2f rb_perp = sf::Vector2f(-rb.y, rb.x);
            sf::Vector2f vel_rotation_a = ra_perp * _rotation / deg_to_rad;
            sf::Vector2f vel_rotation_b = rb_perp * other._rotation / deg_to_rad;
            sf::Vector2f relative_velocity = (other._velocity + vel_rotation_b) - (_velocity + vel_rotation_a);
            float contact_velocity_mag = dot(relative_velocity, contact_info.normal);

            ra_vec.push_back(ra);
            rb_vec.push_back(rb);

            if (contact_velocity_mag > 0) {
                impulse_vec.push_back(sf::Vector2f());
                continue;
            }

            float ra_perp_dot_n = dot(ra_perp, contact_info.normal);
            float rb_perp_dot_n = dot(rb_perp, contact_info.normal);
            float denom = _inv_mass + other._inv_mass +
                (ra_perp_dot_n * ra_perp_dot_n) * inv_inertia_a +
                (rb_perp_dot_n * rb_perp_dot_n) * inv_inertia_b;

            float j = -(1.0f + e) * contact_velocity_mag;
            j /= denom;
            j /= static_cast<float>(contact_info.points.size());

            sf::Vector2f impulse = j * contact_info.normal;

            impulse_vec.push_back(impulse);
        }

        for (std::size_t i = 0; i < contact_info.points.size(); ++i) {
            sf::Vector2f impulse = impulse_vec.at(i);
            sf::Vector2f ra = ra_vec.at(i);
            sf::Vector2f rb = rb_vec.at(i);

            _velocity += -impulse * _inv_mass;
            _rotation += -cross(ra, impulse) * inv_inertia_a * (180 / M_PI);
            other._velocity += impulse * other._inv_mass;
            other._rotation += cross(rb, impulse) * inv_inertia_b * (180 / M_PI);
        }
        return true;
    }

    Polygon::ContactInfo Polygon::findContactPoints(Polygon &other)
    {
        ContactInfo contact_info = ContactInfo();

        for (size_t i = 0; i < getPointCount(); ++i) {
            size_t j = (i + 1) % getPointCount();
            const sf::Vector2f& p1 = getPointGlobal(i);
            const sf::Vector2f& p2 = getPointGlobal(j);

            for (size_t k = 0; k < other.getPointCount(); ++k) {
                size_t l = (k + 1) % other.getPointCount();
                const sf::Vector2f& p3 = other.getPointGlobal(k, other);
                const sf::Vector2f& p4 = other.getPointGlobal(l, other);

                float denominator = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

                if (denominator != 0) {
                    float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denominator;
                    float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denominator;

                    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
                        sf::Vector2f collision_point;
                        collision_point.x = p1.x + ua * (p2.x - p1.x);
                        collision_point.y = p1.y + ua * (p2.y - p1.y);
                        contact_info.points.push_back(collision_point);
                        contact_info.collided = true;

                        float nx = p2.y - p1.y;
                        float ny = p1.x - p2.x;
                        float length = std::sqrt(nx * nx + ny * ny);
                        contact_info.normal.x = nx / length;
                        contact_info.normal.y = ny / length;
                    }
                }
            }
        }

        return contact_info;
    }
}
