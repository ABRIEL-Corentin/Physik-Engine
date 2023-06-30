////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  core.cpp
//
////////////////////////

#include "core.hpp"
#include "shapes/circle.hpp"
#include "shapes/rectangle.hpp"
#include "shapes/polygon.hpp"
#include "config.hpp"

namespace PhysikEngine
{
    Core::Core()
        : _window(Window::getInstance()),
          _time(Time::getInstance()),
          _scene()
    {
        std::srand(std::time(nullptr));
        // Circle &c1 = _scene.addShape<Circle>(false, sf::Vector2f(100, 120), 20, true);
        // Circle &c2 = _scene.addShape<Circle>(false, sf::Vector2f(500, 140), 20, true);

        // c1.addForce(sf::Vector2f(20, 0));
        // c2.addForce(sf::Vector2f(-10, 0));

        // Rectangle &r1 = _scene.addShape<Rectangle>(false, sf::Vector2f(100, 200), sf::Vector2f(40, 40), true);
        // Rectangle &r2 = _scene.addShape<Rectangle>(false, sf::Vector2f(500, 185), sf::Vector2f(40, 40), true);

        // r1.setRotation(-30);
        // r1.addForce(sf::Vector2f(40, 0));
        // r2.addForce(sf::Vector2f(-30, 0));

        // Polygon &p1 = _scene.addShape<Polygon>(false, sf::Vector2f(100, 400), 0);
        // Polygon &p2 = _scene.addShape<Polygon>(false, sf::Vector2f(100, 250), 100);

        // // p1.addPoint(sf::Vector2f(-20, -20));
        // // p1.addPoint(sf::Vector2f(20, -20));
        // // p1.addPoint(sf::Vector2f(20, 20));
        // // p1.addPoint(sf::Vector2f(-20, 20));

        // p1.addPoint(sf::Vector2f(-200, -20));
        // p1.addPoint(sf::Vector2f(600, -20));
        // p1.addPoint(sf::Vector2f(600, 20));
        // p1.addPoint(sf::Vector2f(-200, 20));
        // p1.setStatic(true);
        // // p1.rotate(10);

        // p2.addPoint(sf::Vector2f(-10, -10));
        // p2.addPoint(sf::Vector2f(20, -20));
        // p2.addPoint(sf::Vector2f(20, 20));
        // p2.addPoint(sf::Vector2f(10, 30));
        // p2.addPoint(sf::Vector2f(-20, 20));
        // p2.addForce(sf::Vector2f(0, 100));

        // Rectangle &r1 = _scene.addShape<Rectangle>(false, sf::Vector2f(100, 200), sf::Vector2f(40, 40));
        // Rectangle &r2 = _scene.addShape<Rectangle>(false, sf::Vector2f(500, 185), sf::Vector2f(40, 40));
        // Rectangle &r3 = _scene.addShape<Rectangle>(false, sf::Vector2f(600, 135), sf::Vector2f(40, 40));

        // r1.setRotation(-30);
        // r1.addForce(sf::Vector2f(40, 0));
        // r2.addForce(sf::Vector2f(-30, 0));
        // r3.setRotation(-45);

        // Circle &c1 = _scene.addShape<Circle>(false, sf::Vector2f(100, 120), 20, false);
        // Rectangle &r2 = _scene.addShape<Rectangle>(false, sf::Vector2f(500, 115), sf::Vector2f(40, 40), false);
        // c1.addForce(sf::Vector2f(20, 0));
        // r2.addForce(sf::Vector2f(-30, 0));

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            _window.close();
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
        static int spawn_circle_count = 1;
        static int spawn_rectangle_count = 1;
        static int spawn_polygon_count = 1;

        if (ImGui::Begin("Debug Window")) {
            ImGui::Text("FPS: %.2f", 1.0f / _time.getDeltaTime().asSeconds());
            ImGui::Text("Entities: %ld", _scene.getSize());
            ImGui::Checkbox("Gravity", &Config::getInstance().gravity);
            ImGui::Checkbox("Air friction", &Config::getInstance().air_friction);
            ImGui::Checkbox("Grid", &Config::getInstance().grid);

            ImGui::SliderInt("##circle", &spawn_circle_count, 1, 100);
            ImGui::SameLine();
            if (ImGui::Button("Circle")) {
                for (int i = 0; i < spawn_circle_count; ++i) {
                    float radius = rand() % 20 + 10;
                    sf::Vector2f position = sf::Vector2f(
                        rand() % static_cast<int>(_window.getSize().x * 0.9) + _window.getSize().x * 0.05,
                        rand() % static_cast<int>(_window.getSize().y * 0.9) + _window.getSize().y * 0.05
                    );
                    Circle &circle = _scene.addShape<Circle>(false, position, radius);
                    circle.addForce(sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50));
                }
            }

            ImGui::SliderInt("##rectangle", &spawn_rectangle_count, 1, 100);
            ImGui::SameLine();
            if (ImGui::Button("Rectangle")) {
                for (int i = 0; i < spawn_rectangle_count; ++i) {
                    sf::Vector2f size = sf::Vector2f(rand() % 50 + 25, rand() % 50 + 25);
                    sf::Vector2f position = sf::Vector2f(
                        rand() % static_cast<int>(_window.getSize().x * 0.9) + _window.getSize().x * 0.05,
                        rand() % static_cast<int>(_window.getSize().y * 0.9) + _window.getSize().y * 0.05
                    );
                    Rectangle &rectangle = _scene.addShape<Rectangle>(false, position, size);
                    rectangle.addForce(sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50));
                }
            }

            ImGui::SliderInt("##polygon", &spawn_polygon_count, 1, 100);
            ImGui::SameLine();
            if (ImGui::Button("Polygon")) {
                for (int i = 0; i < spawn_polygon_count; ++i) {
                    sf::Vector2f position = sf::Vector2f(
                        rand() % static_cast<int>(_window.getSize().x * 0.9) + _window.getSize().x * 0.05,
                        rand() % static_cast<int>(_window.getSize().y * 0.9) + _window.getSize().y * 0.05
                    );
                    Polygon &polygon = _scene.addShape<Polygon>(false, position, rand() % 100);
                    polygon.addForce(sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50));
                    polygon.addPoint(sf::Vector2f(-(rand() % 50), -(rand() % 50)));
                    polygon.addPoint(sf::Vector2f((rand() % 50), -(rand() % 50)));
                    polygon.addPoint(sf::Vector2f((rand() % 50), (rand() % 50)));
                    polygon.addPoint(sf::Vector2f(-(rand() % 50), (rand() % 50)));
                }
            }

            if (ImGui::Button("clear"))
                _scene.clear();
        }
        ImGui::End();
    }
}
