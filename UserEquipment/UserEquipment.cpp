#include "UserEquipment.h"
#include "DataAddresses.h"
#include <string>

UserEquipment::UserEquipment(Data::Types::NodeId id, const Data::Types::Address& poolAddress) : mId(id), mPoolAddress(poolAddress)
{

}