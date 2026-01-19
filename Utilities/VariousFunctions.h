#pragma once
#include <cstdint>
#include <iostream>

void func();


// uint32_t GetUniqueId();

// uint32_t GetUniquePoolId();
//
// uint32_t GetUniqueUserEquipmentId();
//
// uint32_t GetUniqueBaseStationId();

template<typename T> uint32_t GetUniqueId()
{
    static uint32_t id = 0;
    std::cout << "Generating unique Id " << (id++) << " for " << T::name() << std::endl;
    return id;
}
