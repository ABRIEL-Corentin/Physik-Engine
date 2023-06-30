////////////////////////
//
//  Created on Fri Jun 30 2023
//
//  grid.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"
#include "shapes/ishape.hpp"

namespace PhysikEngine
{
    class Grid
    {
        public:
            Grid() = default;

            std::vector<std::shared_ptr<IShape>> getShapes(const sf::FloatRect &area);

            template<std::derived_from<IShape> T, typename ... ARGS>
            inline T &addShape(const ARGS &... args)
            {
                _shapes.push_back(std::make_shared<T>(args...));
                return dynamic_cast<T &>(*_shapes.back());
            }

            inline std::size_t size() const { return _shapes.size(); }
            inline void clear() { _shapes.clear(); }
            inline std::vector<std::shared_ptr<IShape>> &getAllShapes() { return _shapes; }

        private:
            std::vector<std::shared_ptr<IShape>> _shapes;
    };
}
