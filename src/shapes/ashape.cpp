////////////////////////
//
//  Created on Mon Jun 26 2023
//
//  ashape.cpp
//
////////////////////////

#include "shapes/ashape.hpp"

namespace PhysikEngine
{
    AShape::AShape(bool is_static, float mass)
        : _mass(mass),
          _static(is_static)
    { }
}
