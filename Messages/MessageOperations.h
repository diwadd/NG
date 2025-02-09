#pragma once
#include <zmq.hpp>
#include "flatbuffers/flatbuffers.h"
#include "DataTypesCommon.h"

void SendMessage(
	zmq::context_t &context,
	const Data::Types::Address& address,
	std::unique_ptr<flatbuffers::FlatBufferBuilder> messageBuilder);