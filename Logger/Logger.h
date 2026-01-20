#pragma once
#include <zmq.hpp>

class Logger
{
    public:
        Logger(zmq::context_t& context);
        void Run();

    private:
        zmq::context_t& mContext;
};