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
    Data::Types::NodeId id, const Data::Types::Address& poolAddress) :
    mContext(context),
    mId(id),
    selfAddress(Addresses::USER_EQUIPMENT_PREFIX + std::to_string(mId)), mPoolAddress(poolAddress)
{
}

std::string UserEquipment::name()
{
    return "UserEquipment";
}

void UserEquipment::Register()
{
    const auto log = selfAddress + " - registering to Network control";
    SendLogMessage(mContext, log);

    auto reg = BuildRegisterUserEquipment(mId, mPoolAddress);
    SendMessage(mContext, Addresses::NETWORK_CONTROL, std::move(reg));
}

Data::Types::NodeId UserEquipment::GetId() const
{
    return mId;
}
