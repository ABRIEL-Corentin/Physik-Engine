////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  scene.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "shapes/ishape.hpp"

namespace PhysikEngine
{
    class Scene
    {
        public:
            template<std::derived_from<IShape> T, typename ... ARGS>
            T &addShape(const ARGS &... args)
            {
                _shapes.push_back(std::make_unique<T>(args...));
                return dynamic_cast<T &>(*_shapes.back());
            }

            void update();
            void draw(sf::RenderTarget &target);

        private:
            std::vector<std::unique_ptr<IShape>> _shapes;
    };
}
