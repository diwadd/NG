#include "PoolFactory.h"
#include <iostream>
#include <print>
#include "VariousFunctions.h"
#include "DataTypesCommon.h"
#include "Definitions/Messages_generated.h"

void uePool(zmq::context_t &context, uint32_t numberOfUesPerPool)
{
	const uint32_t poolId = GetUniqueId();
	const std::string uePoolAddress = Addresses::USER_EQUIPMENT_POOL_PREFIX + std::to_string(GetUniqueId());

	std::print("Starting UE Pool {} with {} UEs\n", uePoolAddress, numberOfUesPerPool);

	zmq::socket_t socket(context, zmq::socket_type::pair);
	socket.bind(uePoolAddress);

	Pools::Pool<UserEquipment> pool(numberOfUesPerPool, uePoolAddress);

	while(true)
	{
		zmq::message_t zmqMsg;
        const auto numberOfBytes = socket.recv(zmqMsg, zmq::recv_flags::none);

		if(not numberOfBytes.has_value())
		{
			std::cerr << "Received message with no size!\n";
			std::abort();
		}

		auto message = MessagesX::GetMessage(zmqMsg.data());
        std::cout << "UE Pool " << poolId << " received message (" << numberOfBytes.value() << "): " <<  static_cast<uint32_t>(message->payload_type()) << std::endl;

		if (auto abort = message->payload_as_Abort(); abort)
		{
			std::cout << "Ending UE pool " << poolId << std::endl;
			break;
		}

		pool.RelayMessage(*message);

	}
}

void SpawnUeThreads(zmq::context_t &context, std::vector<std::thread>& threads, uint32_t totalNumberOfUes, uint32_t numberOfUeThreads)
{
	const uint32_t numberOfUesPerThread = totalNumberOfUes / numberOfUeThreads;
	uint32_t uesProcessedSoFar = 0;
	for(uint32_t t = 0; t < numberOfUeThreads - 1; t++)
	{
		std::cout << "Creating UE Pool thread with " << numberOfUesPerThread << " UEs\n";
		threads.push_back(std::thread(uePool, std::ref(context), numberOfUesPerThread));
		uesProcessedSoFar += numberOfUesPerThread;
	}
	const auto remainingUes = totalNumberOfUes - uesProcessedSoFar;
	std::cout << "Creating UE Pool thread with " << remainingUes << " UEs\n";
	threads.push_back(std::thread(uePool, std::ref(context), remainingUes));
}
