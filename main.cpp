#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <print>
#include <chrono>
#include "VariousFunctions.h"
#include "Messages.h"
#include "MessageOperations.h"


void gnb(zmq::context_t &context)
{

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind("inproc://GNB_1");

	std::cout << "Waiting for UEs to span\n";
	std::chrono::milliseconds timespan(2000); // or whatever
	std::this_thread::sleep_for(timespan);
	std::cout << "UEs spanned\n";

	zmq::socket_t sender(context, zmq::socket_type::pair);
	sender.connect("inproc://UE_1");

	Message message{
		.payload = SystemInformationBlockOne{
			.cellAccessRelatedInfo = CellAccessRelatedInfo{
				.cellIdentity = 3427}}};

	SendMessage(sender, message);
}

void ue(zmq::context_t &context)
{

	std::print("In UE function\n");

	// std::cout << "UE ready, signaling to main" << std::endl;

	// xmitter.send(zmq::str_buffer("UE READY"), zmq::send_flags::none);

	// std::cout << "UE ready, sent to main" << std::endl;

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind("inproc://UE_1");


	zmq::message_t msg;
	const auto numberOfBytes = socket.recv(msg, zmq::recv_flags::none);

	std::cout << "UE received a message with: " << numberOfBytes.value() << " bytes of payload\n";
	
	// Message* message = reinterpret_cast<Message*>(msg.data());
	// SystemInformationBlockOne sib1 = std::get<SystemInformationBlockOne>(message->payload);

	auto sib1 = ExtractPayload<SystemInformationBlockOne>(msg);
	std::cout << "SIB1 cellAccessRelatedInfo.cellIdentity: " << sib1.cellAccessRelatedInfo.cellIdentity << "\n";

}

int main()
{
    const uint32_t N_THREADS = std::thread::hardware_concurrency();
	std::print("{} concurrent threads are supported.\n", N_THREADS);

	auto [one, two, three] = zmq::version();
	std::cout << "ZeroMQ version: " << one << "." << two << "." << three << "\n";
	func();

	zmq::context_t context;
	std::cout << "Creating gnb thread\n";
	std::thread gnbThread(gnb, std::ref(context));
	std::cout << "Creating ue thread\n";
	std::thread ueThread(ue, std::ref(context));
	std::cout << "Threads created\n";

	// zmq::context_t context;
	// zmq::socket_t sender(context, zmq::socket_type::pair);
	// sender.bind("inproc://main");

	// std::cout << "Creating thread\n";
	// std::thread thd(ueFunction, std::ref(context));
	// std::cout << "Thread created\n";

	// sender.send(zmq::str_buffer("UE READY 1"), zmq::send_flags::none);
	// sender.send(zmq::str_buffer("UE READY 2"), zmq::send_flags::none);
	// sender.send(zmq::str_buffer("UE READY 3"), zmq::send_flags::none);

	gnbThread.join();
	ueThread.join();

	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
}
