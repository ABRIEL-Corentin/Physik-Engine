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
        : m_window(window_name, window_size)
    { }

    void Core::launch()
    {
        while (m_window.isOpen()) {
            processEvents();

            m_window.clear();

            m_window.display();
        }
    }

    void Core::processEvents()
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                default:
                    break;
            }
        }
    }
}
