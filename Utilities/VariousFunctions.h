#pragma once
#include <cstdint>
#include <iostream>

template<typename T> uint32_t GetUniqueId()
{
    static uint32_t id = 0;
    return id++;
}
