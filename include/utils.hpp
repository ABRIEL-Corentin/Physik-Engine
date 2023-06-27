////////////////////////
//
//  Created on Tue Jun 27 2023
//
//  utils.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"

namespace PhysikEngine
{
    template<typename T>
    inline T length(const sf::Vector2<T> &vec)
    {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    template<typename T>
    inline T length(const sf::Vector3<T> &vec)
    {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    }

    template<typename T, typename U>
    inline T dot(const sf::Vector2<T> &vec1, const sf::Vector2<U> &vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    template<typename T, typename U>
    inline T dot(const sf::Vector3<T> &vec1, const sf::Vector3<U> &vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    template<typename T>
    inline int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    template<typename T>
    sf::Vector2<T> normal(const sf::Vector2<T> &vec1, const sf::Vector2<T> &vec2)
    {
        sf::Vector2<T> normal = sf::Vector2<T>(vec2.y - vec1.y, vec1.x - vec2.x);
        return normal / length(normal);
    }

    template<typename T>
    T crossProduct(const sf::Vector2<T> &vec1, const sf::Vector2<T> &vec2, const sf::Vector2<T> &vec3)
    {
        return (vec2.x - vec1.x) * (vec3.y - vec1.y) - (vec2.y - vec1.y) * (vec3.x - vec1.x);
    }
}
