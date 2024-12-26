#pragma once
#include <cstdint>
#include <map>
#include "UserEquipment.h"

class UserEquipmentPool
{

    public:
        UserEquipmentPool(uint32_t numberOfUesInPool);
        void StartPool();
    
    private:
        uint32_t numberOfUesInPool_m{};
        std::map<UserEquipmentId, UserEquipment> userEquipments_m{};
};
