////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  scene.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "grid.hpp"

namespace PhysikEngine
{
    class Scene
    {
        public:
            template<std::derived_from<IShape> T, typename ... ARGS>
            inline T &addShape(const ARGS &... args) { return _grid.addShape<T>(args...); }

            void update();
            void draw(sf::RenderTarget &target);

            inline std::size_t getSize() const { return _grid.size(); }
            inline void clear() { _grid.clear(); }

        private:
            Grid _grid;
    };
}
