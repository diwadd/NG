#pragma once
#include "Messages.h"
#include <zmq.hpp>
#include <cassert>

void SendMessage(zmq::socket_t& socket, Message& message);

template<typename Payload> Payload ExtractPayload(zmq::message_t& zmqMessage)
{
    Message* message = reinterpret_cast<Message*>(zmqMessage.data());
    assert(message->id == Payload::id && "Message Id does not match payload Id!");
	return std::get<Payload>(message->payload);
}