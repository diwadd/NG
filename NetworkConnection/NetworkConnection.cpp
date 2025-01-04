#include <print>
#include "NetworkConnection.h"


NetworkConnection::NetworkConnection()
{

}

bool NetworkConnection::Receive([[maybe_unused]] zmq::message_t& msg)
{
    std::print("NetworkConnection received message");
    return true;
}