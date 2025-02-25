#pragma once
#include <DataTypesCommon.h>
#include <string_view>
#include <zmq.hpp>
#include <string>

class UserEquipment
{
    public:
        UserEquipment(
            zmq::context_t &context,
            zmq::socket_t &socket,
            Data::Types::NodeId id,
            const Data::Types::Address& poolAddress);

        static std::string_view name();
        void Register();
        Data::Types::NodeId GetId() const;
    private:

        zmq::context_t &mContext;
        zmq::socket_t &mSocket;
        const Data::Types::NodeId mId{};
        const Data::Types::Address& mPoolAddress{};
};