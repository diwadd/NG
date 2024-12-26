#include "VariousFunctions.h"
#include <iostream>

void func()
{
    std::cout << "In func\n";
}


uint32_t GetUniqueId()
{
    static uint32_t id = 0;
    return (id++);
}