#pragma once
#include <string_view>
#include "DataTypesCommon.h"

namespace Addresses
{
    const Data::Types::Address NETWORK_CONTROL = "inproc://NetworkConnection";
    const Data::Types::AddressPrefix USER_EQUIPMENT_POOL_PREFIX = "inproc://UE_POOL_";
    const Data::Types::AddressPrefix BASE_STATION_POOL_PREFIX = "inproc://BASE_STATION_POOL_";

}