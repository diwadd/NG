#pragma once
#include "Messages.h"
#include <zmq.hpp>
#include <cassert>

void SendMessage(zmq::socket_t& socket, Messages::Message& message);

std::unique_ptr<Messages::Message> DecodeMessage(zmq::message_t& zmqMessage);
 
template<typename Type> Type ExtractPayload(Messages::Payload& payload)
{
	return std::get<Type>(payload);
}