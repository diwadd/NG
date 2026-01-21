#pragma once
#include "DataTypesCommon.h"
#include "DataAddresses.h"
#include "PoolInterface.h"
#include <map>
#include <zmq.hpp>
#include <memory>
#include <deque>

namespace Pools
{

template<typename T> class Pool : public PoolInterface
{
    public:
        Pool(zmq::context_t &context, uint32_t numberOfNodes, const Data::Types::Address& address);

        void RelayMessage(const MessagesX::Message& message) const override;

        static std::string_view name()
        {
            return "Pool";
        }

        void Run();
    private:
        void CreateNodes(uint32_t numberOfNodes);
        void RegisterNodes();

        zmq::context_t &mContext;
        const Data::Types::Address mAddress;
        std::map<Data::Types::NodeId, std::unique_ptr<T>> mNodes{};
};

template<typename T> Pool<T>::Pool(
    zmq::context_t &context, uint32_t numberOfNodes, const Data::Types::Address& address) :
    mContext(context), mAddress(address)
{
    SendLogMessage(context,
        mAddress + " - Creating pool with " + std::to_string(numberOfNodes) + " of " + T::name());

    CreateNodes(numberOfNodes);
    RegisterNodes();
}

template<typename T> void Pool<T>::Run()
{
    zmq::socket_t socket(mContext, zmq::socket_type::router);
    socket.bind(mAddress);

    while(true)
    {
        zmq::message_t identityMsg, zmqMsg;
        const auto id = socket.recv(identityMsg, zmq::recv_flags::dontwait);
        if (not id)
        {
            continue;
        }

        const auto numberOfBytes = socket.recv(zmqMsg, zmq::recv_flags::dontwait);

        if(not numberOfBytes.has_value())
        {
            std::cerr << "Received message with no size!\n";
            std::abort();
        }

        auto message = MessagesX::GetMessage(zmqMsg.data());

        if (auto abort = message->payload_as_Abort(); abort)
        {
            std::cout << "Ending pool " << std::endl;
            break;
        }

        RelayMessage(*message);

    }
}

template<typename T> void Pool<T>::CreateNodes(uint32_t numberOfNodes)
{
    for(uint32_t i = 0; i < numberOfNodes; i++)
    {
        const auto nodeId = GetUniqueId<T>();
        mNodes[nodeId] = std::make_unique<T>(mContext, nodeId, mAddress);
    }
}

template<typename T> void Pool<T>::RegisterNodes()
{
    for(auto& [_, node] : mNodes)
    {
        node->Register();
    }
}

template<typename T> void Pool<T>::RelayMessage([[maybe_unused]] const MessagesX::Message& message) const
{

}


}
