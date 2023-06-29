////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  main.cpp
//
////////////////////////

#include "core.hpp"
#include "error_handling/check_and_get_args.hpp"

int main(int argc, char **argv)
{
    int check_arg = check_and_get_args(argc, argv);

    if (check_arg == 1)
        return 0;
    if (check_arg == 42)
        return 42;

    PhysikEngine::Core core = PhysikEngine::Core();
    core.launch();
    return 0;
}
