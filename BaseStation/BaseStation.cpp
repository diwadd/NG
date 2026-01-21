#include "BaseStation.h"

BaseStation::BaseStation(
    zmq::context_t &context,
    Data::Types::NodeId id,
    const Data::Types::Address& poolAddress) : mContext(context),
        mId(id), mPoolAddress(poolAddress)
{

}


std::string BaseStation::name()
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
