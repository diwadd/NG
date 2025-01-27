#pragma once
#include <zmq.hpp>
#include "UserEquipment.h"
#include <set>

class NetworkConnection
{
    public:
        NetworkConnection(zmq::context_t& context);
        void Run();

    private:
        zmq::context_t& context_m;
        std::set<UserEquipmentId> ues_m{};
};