#pragma once
#include "flatbuffers/flatbuffers.h"
#include <memory>

std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildPing(uint32_t source);
std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildAbort(const std::string& note);
