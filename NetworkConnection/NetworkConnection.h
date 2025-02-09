#pragma once
#include <zmq.hpp>

class NetworkConnection
{
    public:
        NetworkConnection(zmq::context_t& context);
        void Run();

    private:
        zmq::context_t& mContext;
};