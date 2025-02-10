#include "BaseStation.h"

BaseStation::BaseStation(
    Data::Types::NodeId id,
    const Data::Types::Address& poolAddress) :
        mId(id), mPoolAddress(poolAddress)
{

}


std::string_view BaseStation::name()
{
    return "BaseStation";
}