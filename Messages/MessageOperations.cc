#include "MessageOperations.h"
#include <memory>

void SendMessage(zmq::socket_t& socket, Messages::Message& message)
{
    zmq::message_t zmqMessage(sizeof(message));
    memcpy(zmqMessage.data(), &message, sizeof(message));
	socket.send(zmqMessage, zmq::send_flags::none);
}

Messages::Message& DecodeMessage(zmq::message_t& zmqMessage)
{
    return *(reinterpret_cast<Messages::Message*>(zmqMessage.data()));
}