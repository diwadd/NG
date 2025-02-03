// main
#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <print>
#include <chrono>
#include "VariousFunctions.h"
#include "Messages.h"
#include "MessageOperations.h"
#include "NetworkConnection.h"
#include "Addresses.h"
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

	// std::cout << "UE ready, signaling to main" << std::endl;

	// xmitter.send(zmq::str_buffer("UE READY"), zmq::send_flags::none);

	// std::cout << "UE ready, sent to main" << std::endl;

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind("inproc://UE_1");

	std::cout << "Preparing message" << std::endl;

	// Messages::Message message{.id = Messages::PING,
	// 	.payload = Messages::Ping{.note="asd"}};

	std::cout << "Sending message" << std::endl;

    zmq::socket_t sender(context, zmq::socket_type::pair);
    sender.connect(Address::NETWORK_CONTROL.data());

	flatbuffers::FlatBufferBuilder builder;
	auto ping = MessagesX::CreatePing(builder, 12354);
	auto msgX = MessagesX::CreateMessage(builder, MessagesX::Payload_Ping, ping.Union());

	builder.Finish(msgX);


    zmq::message_t zmqMessage(builder.GetSize());
    memcpy(zmqMessage.data(), builder.GetBufferPointer(), builder.GetSize());
	sender.send(zmqMessage, zmq::send_flags::none);


	// zmq::socket_t sender(context, zmq::socket_type::pair);
	// sender.connect(Address::NETWORK_CONTROL.data());
	// SendMessage(sender, message);

	std::cout << "End of UE_1" << std::endl;

	// zmq::message_t msg;
	// const auto numberOfBytes = socket.recv(msg, zmq::recv_flags::none);

	// std::cout << "UE received a message with: " << numberOfBytes.value() << " bytes of payload\n";
	
	// Message* message = reinterpret_cast<Message*>(msg.data());
	// SystemInformationBlockOne sib1 = std::get<SystemInformationBlockOne>(message->payload);

	// auto sib1 = ExtractPayload<SystemInformationBlockOne>(msg);
	// std::cout << "SIB1 cellAccessRelatedInfo.cellIdentity: " << sib1.cellAccessRelatedInfo.cellIdentity << "\n";

	// zmq::socket_t sender(context, zmq::socket_type::pair);
	// sender.connect(Address::NETWORK_CONTROL.data());
	// sender.send(zmq::str_buffer("READY 1"), zmq::send_flags::none);
	// sender.send(zmq::str_buffer("READY 2"), zmq::send_flags::none);
	// sender.send(zmq::str_buffer("READY 3"), zmq::send_flags::none);

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

	// zmq::socket_t sender(context, zmq::socket_type::pair);
	// sender.bind("inproc://main");

	// std::cout << "Creating thread\n";
	// std::thread thd(ueFunction, std::ref(context));
	// std::cout << "Thread created\n";

	// sender.send(zmq::str_buffer("UE READY 1"), zmq::send_flags::none);
	// sender.send(zmq::str_buffer("UE READY 2"), zmq::send_flags::none);
	// sender.send(zmq::str_buffer("UE READY 3"), zmq::send_flags::none);


	zmq::socket_t sender(context, zmq::socket_type::pair);
	sender.connect(Address::NETWORK_CONTROL.data());

	// Messages::Message message{.id = Messages::ABORT,
	// 	.payload = Messages::Abort{.note = "Abort - Closing Network Connection"}};

	flatbuffers::FlatBufferBuilder builder;
	auto abort = MessagesX::CreateAbort(builder, 1237);
	auto msgX = MessagesX::CreateMessage(builder, MessagesX::Payload_Abort, abort.Union());

	builder.Finish(msgX);


    zmq::message_t zmqMessage(builder.GetSize());
    memcpy(zmqMessage.data(), builder.GetBufferPointer(), builder.GetSize());
	sender.send(zmqMessage, zmq::send_flags::none);

	// SendMessage(sender, message);


	// gnbThread.join();
	ueThread.join();
	networkConnectionThread.join();

	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
	std::print("id: {}\n", GetUniqueId());
}
