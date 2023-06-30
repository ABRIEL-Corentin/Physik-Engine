////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  scene.cpp
//
////////////////////////

#include "scene.hpp"
#include "window.hpp"

namespace PhysikEngine
{
    void Scene::update()
    {
        sf::Vector2f window_size = sf::Vector2f(Window::getInstance().getSize());

        for (auto shape = _shapes.begin(); shape != _shapes.end(); ++shape) {
            (*shape)->update();
            sf::FloatRect rect = (*shape)->getBounds();
            sf::Vector2f pos = (*shape)->getPos();

            if (pos.x - rect.width <= 0)
                (*shape)->multiplyVelocity(sf::Vector2f(-1, 1));
                // (*shape)->setPos(sf::Vector2f(window_size.x + rect.width, pos.y));

            if (pos.x + rect.width >= window_size.x)
                (*shape)->multiplyVelocity(sf::Vector2f(-1, 1));
                // (*shape)->setPos(sf::Vector2f(-rect.width, pos.y));

            if (pos.y - rect.height <= 0)
                (*shape)->multiplyVelocity(sf::Vector2f(1, -1));
                // (*shape)->setPos(sf::Vector2f(pos.x, window_size.y + rect.height));

            if (pos.y + rect.height >= window_size.y)
                (*shape)->multiplyVelocity(sf::Vector2f(1, -1));
                // (*shape)->setPos(sf::Vector2f(pos.x, -rect.height));
        }

        for (auto shape = _shapes.begin(); shape != _shapes.end(); ++shape) {
            for (auto target = _shapes.begin(); target != _shapes.end(); ++target) {
                if (shape->get() != target->get()) {
                    if ((*shape)->collide(**target)) {
                        // Collision
                    }
                }
            }
        }
    }

    void Scene::draw(sf::RenderTarget &target)
    {
        for (auto shape = _shapes.begin(); shape != _shapes.end(); ++shape)
            (*shape)->draw(target);
    }
}
