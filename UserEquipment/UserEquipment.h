#pragma once
#include <DataTypesCommon.h>

class UserEquipment
{
    public:
        UserEquipment(Data::Types::NodeId id, const Data::Types::Address& poolAddress);

    private:
        const Data::Types::NodeId mId{};
        const Data::Types::Address& mPoolAddress{};
};