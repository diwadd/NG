#pragma once
#include "flatbuffers/flatbuffers.h"
#include <memory>

std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildPing(uint32_t source);
std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildAbort(const std::string& note);
std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildLog(const std::string& note);
std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildRegisterUserEquipment(uint32_t id, std::string poolAddress);
