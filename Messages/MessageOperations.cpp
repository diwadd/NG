#include "MessageOperations.h"
#include <memory>
#include "DataAddresses.h"
#include "MessageBuilders.h"

void SendMessage(
	zmq::context_t &context,
	const Data::Types::Address& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder)
{
	zmq::socket_t sender(context, zmq::socket_type::dealer);
    sender.connect(address.c_str());

    const auto messageSize = messageBuilder->GetSize();
    zmq::message_t zmqMessage(messageSize);
    memcpy(zmqMessage.data(), messageBuilder->GetBufferPointer(), messageSize);
	sender.send(zmqMessage, zmq::send_flags::none);
}

void SendLogMessage(zmq::context_t &context, const std::string& note)
{
	zmq::socket_t sender(context, zmq::socket_type::dealer);
	sender.connect(Addresses::LOGGER.c_str());

	auto log = BuildLog(note);
	const auto messageSize = log->GetSize();
	zmq::message_t zmqMessage(messageSize);
	memcpy(zmqMessage.data(), log->GetBufferPointer(), messageSize);
	sender.send(zmqMessage, zmq::send_flags::none);
}

// void SendMessage(
// 	zmq::context_t &context,
// 	const Data::Types::Address& address,
// 	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder)
// {
// 	zmq::socket_t sender(context, zmq::socket_type::dealer);
// 	sender.connect(address.c_str());
//
// 	const auto messageSize = messageBuilder->GetSize();
// 	zmq::message_t zmqMessage(messageSize);
// 	memcpy(zmqMessage.data(), messageBuilder->GetBufferPointer(), messageSize);
// 	sender.send(zmqMessage, zmq::send_flags::none);
// }

void SendMessage(
	zmq::socket_t &socket,
	const Data::Types::Address& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder)
{
    const auto messageSize = messageBuilder->GetSize();
    zmq::message_t zmqMessage(messageSize);
    memcpy(zmqMessage.data(), messageBuilder->GetBufferPointer(), messageSize);
	socket.send(zmqMessage, zmq::send_flags::none);
}
