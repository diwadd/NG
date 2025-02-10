#include "NetworkConnection.h"
#include "MessageOperations.h"
#include "DataAddresses.h"
#include <iostream>
#include "Definitions/Messages_generated.h"

NetworkConnection::NetworkConnection(zmq::context_t& context) : mContext(context)
{

}

void NetworkConnection::Run()
{
    zmq::socket_t socket(mContext, zmq::socket_type::pair);
    socket.bind(Addresses::NETWORK_CONTROL.c_str());

    while(true)
    {
        zmq::message_t zmqMsg;
        const auto numberOfBytes = socket.recv(zmqMsg, zmq::recv_flags::none);
        std::cout << "Network Connection received message: " <<  numberOfBytes.value() << std::endl;

        auto message = MessagesX::GetMessage(zmqMsg.data());

        std::cout << "Payload type: " << static_cast<int>(message->payload_type()) << " - " << static_cast<int>(MessagesX::Payload_Ping) << std::endl;

        if (auto ping = message->payload_as_Ping(); ping)
        {
            std::cout << "Received Ping from " << ping->source() << std::endl;
        }
        else if (auto abort = message->payload_as_Abort(); abort)
        {
            std::cout << "Received Abort: " << abort->note()->c_str() << std::endl;
            break;
        }
    }
    std::cout << "NetworkConnection - Exited while loop - End of Run" << std::endl;

}