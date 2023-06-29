/*
** EPITECH PROJECT, 2023
**
** File description:
** check_and_get_args.cpp
*/

#include <string>
#include <iostream>
#include <getopt.h>

int help()
{
    std::cout << "\n USAGE 1 : ./physik-engine\n" << std::endl;
    std::cout << "  It will open a menu where you can choose which shape and setting you want to add," << std::endl;
    std::cout << "  It will then open the simulation.\n\n" << std::endl;
    std::cout << " Possible Argument :\n" << std::endl;
    std::cout << " -f x         x = 1 -> enable friction | 0 -> enable friction." << std::endl;
    std::cout << " -fps x       x = nbr of frame per second\n" << std::endl;
    return 1;
}

int check_and_get_args(int argc, char **argv)
{
    struct option long_options[] = {"-help", no_argument, 0, 0};
    int opt_idx;
    int opt;
    while ((opt = getopt_long(argc, argv, "h:j:", long_options, &opt_idx)) != -1) {
        switch (opt) {
            case 0:
                return help();
            case 'j':
                return 0;
            default:
                std::cerr << "invalid flag name" << std::endl;
                return 42;
        }
    }
    return 0;
}
