////////////////////////
//
//  Created on Mon Jun 19 2023
//
//  scene.cpp
//
////////////////////////

#include "scene.hpp"
#include "window.hpp"
#include "config.hpp"

namespace PhysikEngine
{
    void Scene::update()
    {
        sf::Vector2f window_size = sf::Vector2f(Window::getInstance().getSize());
        std::vector<std::shared_ptr<IShape>> &all_shapes = _grid.getAllShapes();

        for (auto shape = all_shapes.begin(); shape != all_shapes.end(); ++shape) {
            (*shape)->update();
            sf::FloatRect rect = (*shape)->getBounds();
            sf::Vector2f pos = (*shape)->getPos();

            if (pos.x - rect.width <= 0)
                (*shape)->multiplyVelocity(sf::Vector2f(-1, 1));

            if (pos.x + rect.width >= window_size.x)
                (*shape)->multiplyVelocity(sf::Vector2f(-1, 1));

            if (pos.y - rect.height <= 0)
                (*shape)->multiplyVelocity(sf::Vector2f(1, -1));

            if (pos.y >= window_size.y)
                (*shape)->multiplyVelocity(sf::Vector2f(1, -1));
        }

        float grid_size = 200;
        for (std::size_t x = 0; x < window_size.x; x += grid_size) {
            for (std::size_t y = 0; y < window_size.y; y += grid_size) {
                std::vector<std::shared_ptr<IShape>> shapes = _grid.getShapes(sf::FloatRect(x, y, grid_size, grid_size));

                for (auto first = shapes.begin(); first != shapes.end(); ++first)
                    for (auto second = shapes.begin(); second != shapes.end(); ++second)
                        if (first->get() != second->get())
                            (*first)->collide(**second);
            }
        }
    }

    void Scene::draw(sf::RenderTarget &target)
    {
        float grid_size = 200;
        sf::Vector2f window_size = sf::Vector2f(Window::getInstance().getSize());
        sf::RectangleShape grid_shape = sf::RectangleShape();
        std::vector<std::shared_ptr<IShape>> &all_shapes = _grid.getAllShapes();

        grid_shape.setFillColor(sf::Color::Transparent);
        grid_shape.setOutlineColor(sf::Color::Green);
        grid_shape.setOutlineThickness(-1);
        grid_shape.setSize(sf::Vector2f(grid_size, grid_size));

        if (Config::getInstance().grid) {
            for (std::size_t x = 0; x < window_size.x; x += grid_size) {
                for (std::size_t y = 0; y < window_size.y; y += grid_size) {
                    grid_shape.setPosition(x, y);
                    target.draw(grid_shape);
                }
            }
        }

        for (auto shape = all_shapes.begin(); shape != all_shapes.end(); ++shape)
            (*shape)->draw(target);
    }
}
