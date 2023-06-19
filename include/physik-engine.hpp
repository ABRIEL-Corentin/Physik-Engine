////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  physik-engine.hpp
//
////////////////////////

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define IMGUI_DEFINE_PLACEMENT_NEW
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui_stdlib.h"

#include <iostream>
#include <memory>
#include <concepts>

#define ERROR(x, code) do { \
        std::cerr << __FILE__ << ": line " << __LINE__ << ": " << x << std::endl; \
        exit(code); \
    } while(0)
