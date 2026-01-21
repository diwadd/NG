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
void PoolCallable(
	zmq::context_t &context,
	uint32_t numberOfNodesPerPool,
	const Data::Types::Address& poolAddress)
{
	const auto nodeName = T::name();

	SendLogMessage(context, poolAddress + " - Starting pool for " + nodeName + "s");

	Pools::Pool<T> pool(context, numberOfNodesPerPool, poolAddress);
	pool.Run();
}

template<typename T> Addresses::Addresses SpwanThreads(
	zmq::context_t &context,
	std::vector<std::thread>& threads,
	uint32_t totalNumberOfNodes,
	uint32_t numberOfThreads,
	const Data::Types::AddressPrefix& addressPrefix)
{
	Addresses::Addresses addressesOfPools = {};

	const uint32_t numberOfNodesPerThread = totalNumberOfNodes / numberOfThreads;
	uint32_t nodesProcessedSoFar = 0;
	const auto nodeName = T::name();
	for(uint32_t t = 0; t < numberOfThreads - 1; t++)
	{
		const uint32_t poolId = GetUniqueId<Pools::Pool<T>>();
		const Data::Types::Address poolAddress = addressPrefix + std::to_string(poolId);

		addressesOfPools.push_back(poolAddress);

		threads.push_back(std::thread(PoolCallable<T>,
			std::ref(context), numberOfNodesPerThread, poolAddress));
		nodesProcessedSoFar += numberOfNodesPerThread;
	}

	const uint32_t poolId = GetUniqueId<Pools::Pool<T>>();
	const Data::Types::Address poolAddress = addressPrefix + std::to_string(poolId);
	const auto remainingNodes = totalNumberOfNodes - nodesProcessedSoFar;
	threads.push_back(std::thread(PoolCallable<T>, std::ref(context), remainingNodes, poolAddress));

	return addressesOfPools;
}
