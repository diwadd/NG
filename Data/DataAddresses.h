#pragma once

#include "DataTypesCommon.h"
#include <vector>

namespace Addresses
{
    const Data::Types::Address LOGGER = "inproc://LOGGER";
    const Data::Types::Address NETWORK_CONTROL = "inproc://NetworkConnection";
    const Data::Types::AddressPrefix USER_EQUIPMENT_POOL_PREFIX = "inproc://UE_POOL_";
    const Data::Types::AddressPrefix USER_EQUIPMENT_PREFIX = "inproc://UE_";
    const Data::Types::AddressPrefix BASE_STATION_POOL_PREFIX = "inproc://BASE_STATION_POOL_";

    using Addresses = std::vector<Data::Types::Address>;

}