////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  core.cpp
//
////////////////////////

#include "core.hpp"

namespace PhysikEngine
{
    Core::Core(const std::string &window_name, sf::Vector2u window_size)
        : _window(window_name, window_size),
          _time(Time::getInstance()),
          _scene()
    {
        sf::RectangleShape &shape = _scene.addShape<sf::RectangleShape>(sf::Vector2f(100, 100));

        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(-2);

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
