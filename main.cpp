// main
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

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind("inproc://UE_1");

	std::cout << "Sending message" << std::endl;

	auto ping = BuildPing(123453);
	SendMessage(context, Addresses::NETWORK_CONTROL, std::move(ping));

	std::cout << "End of UE_1" << std::endl;

}



void uePool(zmq::context_t &context, uint32_t numberOfUesPerPool)
{
	const uint32_t poolId = GetUniqueId();
	const std::string uePoolAddress = Addresses::USER_EQUIPMENT_POOL_PREFIX + std::to_string(GetUniqueId());

	std::print("Starting UE Pool {} with {} UEs\n", uePoolAddress, numberOfUesPerPool);

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind(uePoolAddress);

	Pools::Pool<UserEquipment> pool(numberOfUesPerPool, uePoolAddress);

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
        std::cout << "UE Pool " << poolId << " received message (" << numberOfBytes.value() << "): " <<  static_cast<uint32_t>(message->payload_type()) << std::endl;

		if (auto abort = message->payload_as_Abort(); abort)
		{
			std::cout << "Ending UE pool " << poolId << std::endl;
			break;
		}

		pool.RelayMessage(*message);

	}
}

void SpawnUeThreads(zmq::context_t &context, std::vector<std::thread>& threads, uint32_t totalNumberOfUes, uint32_t numberOfUeThreads)
{
	const uint32_t numberOfUesPerThread = totalNumberOfUes / numberOfUeThreads;
	uint32_t uesProcessedSoFar = 0;
	for(uint32_t t = 0; t < numberOfUeThreads - 1; t++)
	{
		std::cout << "Creating UE Pool thread with " << numberOfUesPerThread << " UEs\n";
		threads.push_back(std::thread(uePool, std::ref(context), numberOfUesPerThread));
		uesProcessedSoFar += numberOfUesPerThread;
	}
	const auto remainingUes = totalNumberOfUes - uesProcessedSoFar;
	std::cout << "Creating UE Pool thread with " << remainingUes << " UEs\n";
	threads.push_back(std::thread(uePool, std::ref(context), remainingUes));
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


	auto abort = BuildAbort("Abort from main");
	SendMessage(context, Addresses::NETWORK_CONTROL, std::move(abort));

	// gnbThread.join();
	ueThread.join();
	networkConnectionThread.join();

	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());

	constexpr uint32_t TOTAL_NUMBER_OF_UES = 10;
	constexpr uint32_t NUMBER_OF_UE_THREADS = 3;

	std::vector<std::thread> threads{};

	SpawnUeThreads(context, threads, TOTAL_NUMBER_OF_UES, NUMBER_OF_UE_THREADS);

	for(auto& th : threads)
	{
		th.join();
	}

	// const std::string uePoolAddress = Addresses::USER_EQUIPMENT_POOL_PREFIX + std::to_string(GetUniqueId());
	// Pools::Pool<UserEquipment> pool(5, uePoolAddress);
}
