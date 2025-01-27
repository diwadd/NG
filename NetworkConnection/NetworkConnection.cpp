#include "NetworkConnection.h"
#include "Messages.h"
#include "MessageOperations.h"
#include "Addresses.h"
#include <iostream>

NetworkConnection::NetworkConnection(zmq::context_t& context) : context_m(context)
{

}

void NetworkConnection::Run()
{
    zmq::socket_t socket(context_m, zmq::socket_type::pair);
    socket.bind(Address::NETWORK_CONTROL.data());

    while(true)
    {
        zmq::message_t msg;
        const auto numberOfBytes = socket.recv(msg, zmq::recv_flags::none);
        std::cout << "Network Connection received message: " <<  numberOfBytes.value() << std::endl;

        auto message = DecodeMessage(msg);

        std::cout << "Received message with ID: " << message->id << std::endl;
        if (message->id == Messages::ABORT)
        {
            std::cout << "Received ABORT" << std::endl;
            break;
        }
        else if (message->id == Messages::PING)
        {
            auto ping = ExtractPayload<Messages::Ping>(message->payload);
            std::cout << "Ping received. Note: " << ping.note << std::endl;
        }
        else if (message->id == Messages::REGISTER_USER_EQUIPMENT_REQUEST)
        {

        }
    }
    std::cout << "Exited while loop" << std::endl;


}