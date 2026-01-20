#include "NetworkConnection.h"
#include "MessageOperations.h"
#include "DataAddresses.h"
#include <iostream>
#include "Definitions/Messages_generated.h"
#include "SimulatorConstants.h"

NetworkConnection::NetworkConnection(zmq::context_t& context) : mContext(context)
{

}

void NetworkConnection::Run()
{
    zmq::socket_t socket(mContext, zmq::socket_type::router);

    socket.set(zmq::sockopt::rcvhwm, SimulatorConstants::RECEIVER_HIGH_WATER_MARK);
    socket.bind(Addresses::NETWORK_CONTROL.c_str());

    while(true)
    {
        zmq::message_t identityMsg, zmqMsg;
        const auto id = socket.recv(identityMsg, zmq::recv_flags::dontwait);
        if (not id)
        {
            continue;
        }

        const auto numberOfBytes = socket.recv(zmqMsg, zmq::recv_flags::dontwait);
        (void)numberOfBytes;
        // SendLogMessage(mContext,
        //     "NC - Received Msg " + std::to_string(id.value()) + " size " + std::to_string(numberOfBytes.value()));

        auto message = MessagesX::GetMessage(zmqMsg.data());

        if (auto ping = message->payload_as_Ping(); ping)
        {
            SendLogMessage(mContext, "NC - Received Ping from " + std::to_string(ping->source()));
        }
        else if (auto abort = message->payload_as_Abort(); abort)
        {
            SendLogMessage(mContext, "NC - Received Abort: " + abort->note()->str());
            break;
        }
        else if (auto registerUe = message->payload_as_RegisterUserEquipment(); registerUe)
        {
            SendLogMessage(mContext, "NC - Registering UE " + std::to_string(registerUe->id()) + " UE Pool " +
                registerUe->pool_address()->str());
        }
    }
    SendLogMessage(mContext, "NC - Exited while loop - End of Run");
}