#pragma once
#include <zmq.hpp>
#include "flatbuffers/flatbuffers.h"
#include "DataTypesCommon.h"
#include <string>

void SendMessage(
	zmq::context_t &context,
	const Data::Types::Address& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder);

void SendLogMessage(zmq::context_t &context, const std::string& note);

void SendMessage(
	zmq::socket_t &socket,
	const Data::Types::Address& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder);