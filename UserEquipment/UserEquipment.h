#pragma once
#include <DataTypesCommon.h>
#include <string_view>

class UserEquipment
{
    public:
        UserEquipment(
            Data::Types::NodeId id,
            const Data::Types::Address& poolAddress);

        static std::string_view name();

    private:
        const Data::Types::NodeId mId{};
        const Data::Types::Address& mPoolAddress{};
};