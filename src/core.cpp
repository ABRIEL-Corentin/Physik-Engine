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
        : m_window(window_name, window_size),
          m_time(Time::getInstance())
    { }

    void Core::launch()
    {
        while (m_window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

    void Core::processEvents()
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                default:
                    break;
            }
        }
    }

    void Core::update()
    {
        m_time.update();
        ImGui::SFML::Update(m_window, m_time.getDeltaTime());
    }

    void Core::render()
    {
        m_window.clear();

        ImGui::Begin("Window");

        ImGui::End();

        ImGui::SFML::Render(m_window);
        m_window.display();
    }
}
