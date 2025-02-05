#include "MessageOperations.h"
#include <memory>

void SendMessage(
	zmq::context_t &context,
	const std::string_view& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder)
{
	zmq::socket_t sender(context, zmq::socket_type::pair);
    sender.connect(address.data());

    const auto messageSize = messageBuilder->GetSize();
    zmq::message_t zmqMessage(messageSize);
    memcpy(zmqMessage.data(), messageBuilder->GetBufferPointer(), messageSize);
	sender.send(zmqMessage, zmq::send_flags::none);
}