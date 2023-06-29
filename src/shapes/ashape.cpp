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
    AShape::AShape(bool is_static, float mass, bool air_friction)
        : _velocity(),
          _acceleration(),
          _mass(mass),
          _rotation(),
          _static(is_static),
          _air_friction(air_friction)
    { }
}
