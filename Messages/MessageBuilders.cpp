#include "MessageBuilders.h"
#include "Definitions/Messages_generated.h"

std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildPing(uint32_t source)
{
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    auto ping = MessagesX::CreatePing(*builder, source);
    auto msgX = MessagesX::CreateMessage(*builder, MessagesX::Payload_Ping, ping.Union());

    builder->Finish(msgX);

    return builder;
}

std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildAbort(const std::string& note)
{
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    auto flatBufferString = builder->CreateString(note);
    auto ping = MessagesX::CreateAbort(*builder, flatBufferString);
    auto msgX = MessagesX::CreateMessage(*builder, MessagesX::Payload_Abort, ping.Union());

    builder->Finish(msgX);

    return builder;
}

std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildLog(const std::string& note)
{
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    auto flatBufferString = builder->CreateString(note);
    auto log = MessagesX::CreateLog(*builder, flatBufferString);
    auto msgX = MessagesX::CreateMessage(*builder, MessagesX::Payload_Log, log.Union());

    builder->Finish(msgX);

    return builder;
}

std::unique_ptr<flatbuffers::FlatBufferBuilder> BuildRegisterUserEquipment(uint32_t id, std::string poolAddress)
{
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    auto flatBufferString = builder->CreateString(poolAddress);
    auto registerUserEquipment = MessagesX::CreateRegisterUserEquipment(*builder, id, flatBufferString);
    auto msgX = MessagesX::CreateMessage(*builder, MessagesX::Payload_RegisterUserEquipment, registerUserEquipment.Union());

    builder->Finish(msgX);

    return builder;
}