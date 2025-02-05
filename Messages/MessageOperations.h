#pragma once
#include <zmq.hpp>
#include "flatbuffers/flatbuffers.h"

void SendMessage(
	zmq::context_t &context,
	const std::string_view& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder);