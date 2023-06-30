////////////////////////
//
//  Created on Fri Jun 30 2023
//
//  config.hpp
//
////////////////////////

#pragma once

#include "singleton.hpp"

namespace PhysikEngine
{
    using Config = struct Config : public Singleton<Config>
    {
        bool gravity;
        bool air_friction;
        bool grid;
    };
}
