#pragma once
#include "Definitions/Messages_generated.h"

namespace Pools
{

class PoolInterface
{
    public:
        virtual ~PoolInterface() = default;
        virtual void RelayMessage(const MessagesX::Message& message) const = 0;
};


}