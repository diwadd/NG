#pragma once
#include <zmq.hpp>
#include <cstdint>
#include <thread>

void uePool(zmq::context_t &context, uint32_t numberOfUesPerPool);
void SpawnUeThreads(zmq::context_t &context, std::vector<std::thread>& threads, uint32_t totalNumberOfUes, uint32_t numberOfUeThreads);