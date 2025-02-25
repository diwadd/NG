#include "BaseStation.h"

BaseStation::BaseStation(
    zmq::context_t &context,
    zmq::socket_t &socket,
    Data::Types::NodeId id,
    const Data::Types::Address& poolAddress) : mContext(context), mSocket(socket),
        mId(id), mPoolAddress(poolAddress)
{

}


std::string_view BaseStation::name()
{
    return "BaseStation";
}

void BaseStation::Register()
{

}


Data::Types::NodeId BaseStation::GetId() const
{
    return mId;
}
