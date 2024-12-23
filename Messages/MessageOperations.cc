#include "MessageOperations.h"


void SendMessage(zmq::socket_t& socket, Message& message)
{
    zmq::message_t zmqMessage(sizeof(message));
    memcpy(zmqMessage.data(), &message, sizeof(message));
	socket.send(zmqMessage, zmq::send_flags::none);
}
