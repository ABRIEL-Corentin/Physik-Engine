////////////////////////
//
//  Created on Fri Jun 30 2023
//
//  grid.cpp
//
////////////////////////

#include "grid.hpp"

namespace PhysikEngine
{
    std::vector<std::shared_ptr<IShape>> Grid::getShapes(const sf::FloatRect &area)
    {
        std::vector<std::shared_ptr<IShape>> shapes = std::vector<std::shared_ptr<IShape>>();

        for (auto shape = _shapes.begin(); shape != _shapes.end(); ++shape)
            if ((*shape)->getBounds().intersects(area))
                shapes.push_back(*shape);
        return shapes;
    }
}
