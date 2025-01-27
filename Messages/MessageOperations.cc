#include "MessageOperations.h"
#include <memory>

void SendMessage(zmq::socket_t& socket, Messages::Message& message)
{
    zmq::message_t zmqMessage(sizeof(message));
    memcpy(zmqMessage.data(), &message, sizeof(message));
	socket.send(zmqMessage, zmq::send_flags::none);
}

std::unique_ptr<Messages::Message> DecodeMessage(zmq::message_t& zmqMessage)
{
    Messages::Message* message = reinterpret_cast<Messages::Message*>(zmqMessage.data());
    return std::unique_ptr<Messages::Message>(message);
}