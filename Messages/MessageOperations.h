#pragma once
#include "Messages.h"
#include <zmq.hpp>
#include <cassert>

void SendMessage(zmq::socket_t& socket, Message& message);

template<typename Payload> Payload ExtractPayload(zmq::message_t& zmqMessage)
{
    Message* message = reinterpret_cast<Message*>(zmqMessage.data());
	return std::get<Payload>(message->payload);
}