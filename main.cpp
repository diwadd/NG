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

// void gnb(zmq::context_t &context)
// {

// 	zmq::socket_t socket(context, zmq::socket_type::pair);
// 	socket.bind("inproc://GNB_1");

// 	std::cout << "Waiting for UEs to span\n";
// 	std::chrono::milliseconds timespan(2000); // or whatever
// 	std::this_thread::sleep_for(timespan);
// 	std::cout << "UEs spanned\n";

// 	zmq::socket_t sender(context, zmq::socket_type::pair);
// 	sender.connect("inproc://UE_1");

// 	Message message{
// 		.payload = SystemInformationBlockOne{
// 			.cellAccessRelatedInfo = CellAccessRelatedInfo{
// 				.cellIdentity = 3427}}};

// 	SendMessage(sender, message);
// }

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
	func();

	zmq::context_t context;
	// std::cout << "Creating gnb thread\n";
	// std::thread gnbThread(gnb, std::ref(context));
	// std::cout << "Creating ue thread\n";


	const auto runNetworkConnection = [](zmq::context_t& context){
		NetworkConnection nc(context);
		nc.Run();
	};

	std::thread networkConnectionThread(runNetworkConnection, std::ref(context));
	std::thread ueThread(ue, std::ref(context));
	std::cout << "Threads created\n";

	std::chrono::milliseconds timespan(2000); // or whatever
	std::this_thread::sleep_for(timespan);

	constexpr uint32_t TOTAL_NUMBER_OF_UES = 10;
	constexpr uint32_t TOTAL_NUMBER_OF_BASE_STATIONS = 3;
	constexpr uint32_t NUMBER_OF_UE_THREADS = 3;
	constexpr uint32_t NUMBER_OF_BASE_STATION_THREADS = 1;

	std::vector<std::thread> threads{};

	SpwanThreads<UserEquipment>(
		context,
		threads,
		TOTAL_NUMBER_OF_UES,
		NUMBER_OF_UE_THREADS,
		Addresses::USER_EQUIPMENT_POOL_PREFIX);
	SpwanThreads<BaseStation>(
		context,
		threads,
		TOTAL_NUMBER_OF_BASE_STATIONS,
		NUMBER_OF_BASE_STATION_THREADS,
		Addresses::BASE_STATION_POOL_PREFIX);


	std::chrono::milliseconds timespan2(2000); // or whatever
	std::this_thread::sleep_for(timespan2);

	auto abort = BuildAbort("Abort from main");
	SendMessage(context, Addresses::NETWORK_CONTROL, std::move(abort));


	for(auto& th : threads)
	{
		th.join();
	}

	// gnbThread.join();
	ueThread.join();
	networkConnectionThread.join();

	// const std::string uePoolAddress = Addresses::USER_EQUIPMENT_POOL_PREFIX + std::to_string(GetUniqueId());
	// Pools::Pool<UserEquipment> pool(5, uePoolAddress);
}
