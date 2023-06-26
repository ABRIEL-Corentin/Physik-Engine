////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  window.cpp
//
////////////////////////

#include "window.hpp"

namespace PhysikEngine
{
    Window::Window()
        : sf::RenderWindow({800, 600, 32}, "Physik Engine")
    {
        initImGui();
    }

    Window::~Window()
    {
        ImGui::SFML::Shutdown(*this);
    }

    void Window::initImGui()
    {
        if (!ImGui::SFML::Init(*this))
            ERROR("init ImGui with SFML", 84);
    }
}
