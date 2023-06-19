////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  scene.cpp
//
////////////////////////

#include "scene.hpp"

namespace PhysikEngine
{
    void Scene::update()
    {
        for (auto shape = _shapes.begin(); shape != _shapes.end(); ++shape) {
            for (auto target = _shapes.begin(); target != _shapes.end(); ++target) {
                if (shape->get() != target->get()) {
                    if ((*shape)->collide(**target)) {
                        std::cout << "Collision!!!" << std::endl;
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
