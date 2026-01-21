//
//
//
//
#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <print>
#include <chrono>
#include "VariousFunctions.h"
#include "MessageOperations.h"
#include "NetworkConnection.h"
#include "DataAddresses.h"
#include "MessageBuilders.h"
#include "Pool.h"
#include "UserEquipment.h"
#include "Definitions/Messages_generated.h"
#include "PoolFactory.h"
#include "BaseStation.h"
#include "Logger.h"

namespace
{
	const auto runLogger = [](zmq::context_t& context){
		Logger logger(context);
		logger.Run();
	};

	const auto runNetworkConnection = [](zmq::context_t& context){
		NetworkConnection nc(context);
		nc.Run();
	};

}

void ue(zmq::context_t &context)
{

	std::print("In UE function\n");
	std::cout << "Sending message" << std::endl;

	auto ping = BuildPing(123453);
	SendMessage(context, Addresses::NETWORK_CONTROL, std::move(ping));

	std::cout << "End of UE_1" << std::endl;
}


int main()
{
    const uint32_t N_THREADS = std::thread::hardware_concurrency();
	std::print("{} concurrent threads are supported.\n", N_THREADS);

	auto [one, two, three] = zmq::version();
	std::cout << "ZeroMQ version: " << one << "." << two << "." << three << "\n";

	zmq::context_t context;

	std::thread loggerThread(runLogger, std::ref(context));
	SendLogMessage(context, "Main - Logger thread created");

	std::thread networkConnectionThread(runNetworkConnection, std::ref(context));

	constexpr uint32_t TOTAL_NUMBER_OF_UES = 10;
	constexpr uint32_t TOTAL_NUMBER_OF_BASE_STATIONS = 3;
	constexpr uint32_t NUMBER_OF_UE_THREADS = 3;
	constexpr uint32_t NUMBER_OF_BASE_STATION_THREADS = 1;

	std::vector<std::thread> threads{};

	const Addresses::Addresses addressesOfUserEquipmentPools = SpwanThreads<UserEquipment>(
		context,
		threads,
		TOTAL_NUMBER_OF_UES,
		NUMBER_OF_UE_THREADS,
		Addresses::USER_EQUIPMENT_POOL_PREFIX);

	const Addresses::Addresses addressesOfBaseStationPools = SpwanThreads<BaseStation>(
		context,
		threads,
		TOTAL_NUMBER_OF_BASE_STATIONS,
		NUMBER_OF_BASE_STATION_THREADS,
		Addresses::BASE_STATION_POOL_PREFIX);

	for(auto& th : threads)
	{
		th.join();
	}

	SendLogMessage(context, "Main - Sending Abort to Network Control");

	SendMessage(context, Addresses::NETWORK_CONTROL, BuildAbort("Abort from main"));

	networkConnectionThread.join();
	loggerThread.join();
}
