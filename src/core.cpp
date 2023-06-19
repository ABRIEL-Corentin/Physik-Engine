////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  core.cpp
//
////////////////////////

#include "core.hpp"
#include "shapes/circle.hpp"

namespace PhysikEngine
{
    Core::Core(const std::string &window_name, sf::Vector2u window_size)
        : _window(window_name, window_size),
          _time(Time::getInstance()),
          _scene()
    {
        Circle &shape1 = _scene.addShape<Circle>();

        shape1.setRadius(20);
        shape1.setOutlineColor(sf::Color::Red);
        shape1.setFillColor(sf::Color::Transparent);
        shape1.setOutlineThickness(-2);

        Circle &shape2 = _scene.addShape<Circle>();

        shape2.setRadius(20);
        shape2.setOutlineColor(sf::Color::Red);
        shape2.setFillColor(sf::Color::Transparent);
        shape2.setOutlineThickness(-2);
        shape2.setPosition(sf::Vector2f(25, 0));
    }

    void Core::launch()
    {
        while (_window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

    void Core::processEvents()
    {
        sf::Event event;

        while (_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type) {
                case sf::Event::Closed:
                    _window.close();
                    break;
                default:
                    break;
            }
        }
    }

    void Core::update()
    {
        _time.update();
        ImGui::SFML::Update(_window, _time.getDeltaTime());
        _scene.update();
    }

    void Core::render()
    {
        _window.clear();

        drawDebugWindow();
        _scene.draw(_window);

        ImGui::SFML::Render(_window);
        _window.display();
    }

    void Core::drawDebugWindow()
    {
        if (ImGui::Begin("Debug Window")) {
            ImGui::Text("FPS: %.2f", 1.0f / _time.getDeltaTime().asSeconds());
        }
        ImGui::End();
    }
}
