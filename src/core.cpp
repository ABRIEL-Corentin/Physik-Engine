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
    Core::Core()
        : _window(Window::getInstance()),
          _time(Time::getInstance()),
          _scene()
    {
        Circle &c1 = _scene.addShape<Circle>(false, sf::Vector2f(100, 100), 20);
        Circle &c2 = _scene.addShape<Circle>(false, sf::Vector2f(500, 120), 20);

        c1.addForce(sf::Vector2f(20, 0));
        c2.addForce(sf::Vector2f(-10, 0));
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
                case sf::Event::Resized:
                    _window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    break;
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
