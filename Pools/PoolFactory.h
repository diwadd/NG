#pragma once
#include <zmq.hpp>
#include <cstdint>
#include <thread>
#include <iostream>
#include <print>
#include "VariousFunctions.h"
#include "DataTypesCommon.h"
#include "DataAddresses.h"
#include "Definitions/Messages_generated.h"
#include "UserEquipment.h"
#include "Pool.h"


template<typename T>
void poolCallable(
	zmq::context_t &context,
	uint32_t numberOfNodesPerPool,
	const Data::Types::AddressPrefix& addressPrefix)
{
	const uint32_t poolId = GetUniqueId();
	const std::string poolAddress = addressPrefix + std::to_string(GetUniqueId());

	const auto nodeName = T::name();
	std::print("Starting Pool {} with {} {}s\n", poolAddress, numberOfNodesPerPool, nodeName);

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind(poolAddress);

	Pools::Pool<UserEquipment> pool(numberOfNodesPerPool, poolAddress);

	while(true)
	{
		zmq::message_t zmqMsg;
        const auto numberOfBytes = socket.recv(zmqMsg, zmq::recv_flags::none);

		if(not numberOfBytes.has_value())
		{
			std::cerr << "Received message with no size!\n";
			std::abort();
		}

		auto message = MessagesX::GetMessage(zmqMsg.data());
        std::cout << nodeName << " Pool " << poolId << " received message ("
			<< numberOfBytes.value() << "): " <<  static_cast<uint32_t>(message->payload_type()) << std::endl;

		if (auto abort = message->payload_as_Abort(); abort)
		{
			std::cout << "Ending UE pool " << poolId << std::endl;
			break;
		}

		pool.RelayMessage(*message);

	}
}

template<typename T> void SpwanThreads(
	zmq::context_t &context,
	std::vector<std::thread>& threads,
	uint32_t totalNumberOfNodes,
	uint32_t numberOfThreads,
	const Data::Types::AddressPrefix& addressPrefix)
{
	const uint32_t numberOfNodesPerThread = totalNumberOfNodes / numberOfThreads;
	uint32_t nodesProcessedSoFar = 0;
	const auto nodeName = T::name();
	for(uint32_t t = 0; t < numberOfThreads - 1; t++)
	{
		std::cout << "Creating " << nodeName << " Pool thread with " << numberOfNodesPerThread << " " << nodeName << "s\n";
		threads.push_back(std::thread(poolCallable<T>,
			std::ref(context), numberOfNodesPerThread, addressPrefix));
		nodesProcessedSoFar += numberOfNodesPerThread;
	}
	const auto remainingNodes = totalNumberOfNodes - nodesProcessedSoFar;
	std::cout << "Creating " << nodeName << " Pool thread with " << remainingNodes << " " << nodeName << "s\n";
	threads.push_back(std::thread(poolCallable<T>, std::ref(context), remainingNodes, addressPrefix));
}
