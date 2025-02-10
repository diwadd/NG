#pragma once
#include "DataTypesCommon.h"
#include "DataAddresses.h"
#include "PoolInterface.h"
#include <map>
#include <zmq.hpp>
#include <memory>

namespace Pools
{

template<typename T> class Pool : public PoolInterface
{
    public:
        Pool(uint32_t numberOfNodes, const Data::Types::Address& address);

        void RelayMessage(const MessagesX::Message& message) const override;

    private:
        void CreateNodes(uint32_t numberOfNodes);

        const Data::Types::Address& mAddress;
        std::map<Data::Types::NodeId, std::unique_ptr<T>> mNodes{};
};

template<typename T> Pool<T>::Pool(uint32_t numberOfNodes, const Data::Types::Address& address) : mAddress(address)
{
    CreateNodes(numberOfNodes);
}

template<typename T> void Pool<T>::CreateNodes(uint32_t numberOfNodes)
{
    for(uint32_t i = 0; i < numberOfNodes; i++)
    {
        const auto nodeId = GetUniqueId();
        mNodes[nodeId] = std::make_unique<T>(nodeId, mAddress);
    }
}

template<typename T> void Pool<T>::RelayMessage([[maybe_unused]] const MessagesX::Message& message) const
{

}


}
