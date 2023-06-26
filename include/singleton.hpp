////////////////////////
//
//  Created on Thu Jun 01 2023
//
//  singleton.hpp
//
////////////////////////

#pragma once

#include "physik-engine.hpp"

namespace PhysikEngine
{
    template<typename T>
    class Singleton
    {
        public:
            virtual ~Singleton() = default;

            static inline T &getInstance() { return _instance; }

        private:
            static T _instance;
    };

    template<typename T>
    T Singleton<T>::_instance = T();
}
