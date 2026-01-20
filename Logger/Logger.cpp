#include "Logger.h"
#include "SimulatorConstants.h"
#include "DataAddresses.h"
#include "Definitions/Messages_generated.h"
#include <iostream>

Logger::Logger(zmq::context_t& context) : mContext(context)
{
}

void Logger::Run()
{
    zmq::socket_t socket(mContext, zmq::socket_type::router);

    socket.set(zmq::sockopt::rcvhwm, SimulatorConstants::RECEIVER_HIGH_WATER_MARK);
    socket.bind(Addresses::LOGGER.c_str());

    while(true)
    {
        zmq::message_t identityMsg, zmqMsg;
        const auto id = socket.recv(identityMsg, zmq::recv_flags::dontwait);
        if (not id)
        {
            continue;
        }

        const auto numberOfBytes = socket.recv(zmqMsg, zmq::recv_flags::dontwait);
        // std::cout << "Logger recv result " << id.value() << " received message size: " <<  numberOfBytes.value() << std::endl;
        (void)numberOfBytes;

        auto message = MessagesX::GetMessage(zmqMsg.data());

        if (auto log = message->payload_as_Log(); log)
        {
            std::cout << log->note()->c_str() << std::endl;
        }
        else if (auto abort = message->payload_as_Abort(); abort)
        {
            std::cout << "Logger received Abort: " << abort->note()->c_str() << std::endl;
            break;
        }
        else
        {
            std::cout << "Logger received unknown message!" << std::endl;
        }

    }
    std::cout << "Logger - Exited while loop - End of Run" << std::endl;

}