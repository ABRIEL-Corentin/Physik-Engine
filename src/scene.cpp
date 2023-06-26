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

    }

    void Scene::draw(sf::RenderTarget &target)
    {
        for (auto shape = _shapes.begin(); shape != _shapes.end(); ++shape)
            target.draw(**shape);
    }
}
