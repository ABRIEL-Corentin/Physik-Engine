////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  main.cpp
//
////////////////////////

#include "core.hpp"

int main()
{
    PhysikEngine::Core core = PhysikEngine::Core("Physik Engine", {800, 600});

    core.launch();
    return 0;
}
