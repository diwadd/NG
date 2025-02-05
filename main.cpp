// main
#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <print>
#include <chrono>
#include "VariousFunctions.h"
#include "MessageOperations.h"
#include "NetworkConnection.h"
#include "Addresses.h"
#include "MessageBuilders.h"

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
}
