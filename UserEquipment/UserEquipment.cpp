#include "UserEquipment.h"
#include "DataAddresses.h"
#include "MessageOperations.h"
#include "MessageBuilders.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

UserEquipment::UserEquipment(
    zmq::context_t &context,
    zmq::socket_t &socket,
    Data::Types::NodeId id, const Data::Types::Address& poolAddress) :
    mContext(context), mSocket(socket), mId(id), mPoolAddress(poolAddress)
{
}

std::string_view UserEquipment::name()
{
    return "UserEquipment";
}

void UserEquipment::Register()
{
    const auto log = "UE " + std::to_string(mId) + " - registering to Network control";
    SendLogMessage(mContext, log);

    auto reg = BuildRegisterUserEquipment(mId, mPoolAddress);
    SendMessage(mContext, Addresses::NETWORK_CONTROL, std::move(reg));
}

Data::Types::NodeId UserEquipment::GetId() const
{
    return mId;
}
