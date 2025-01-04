#pragma once
#include <zmq.hpp>

class NetworkConnection
{
    public:
        NetworkConnection();
        bool Receive(zmq::message_t& msg);

};