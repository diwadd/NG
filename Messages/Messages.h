#pragma once
#include <cstdint>
#include <variant>
#include <string>

namespace Messages
{

using PayloadId = uint32_t;

constexpr PayloadId MASTER_INFORMATION_BLOCK     = 0x0001; 
constexpr PayloadId SYSTEM_INFORMATION_BLOCK_ONE = 0x0002;
constexpr PayloadId ABORT = 0x0003;
constexpr PayloadId PING = 0x0004;
constexpr PayloadId REGISTER_USER_EQUIPMENT_REQUEST = 0x0005;

struct MasterInformationBlock
{
    static constexpr PayloadId id = MASTER_INFORMATION_BLOCK;
	uint32_t messageId{};
};

using CellIdentity = uint32_t;

struct CellAccessRelatedInfo
{
    CellIdentity cellIdentity{};
};

struct SystemInformationBlockOne
{
    static constexpr PayloadId id = SYSTEM_INFORMATION_BLOCK_ONE;
    CellAccessRelatedInfo cellAccessRelatedInfo{};
};

struct Abort
{
    static constexpr PayloadId id = ABORT;
    std::string note{};
};

struct Ping
{
    static constexpr PayloadId id = PING;
    std::string note{};
};

struct RegisterUserEquipmentRequest
{
    static constexpr PayloadId id = REGISTER_USER_EQUIPMENT_REQUEST;
    std::string address{};
};

using Payload = std::variant<
    MasterInformationBlock,
    SystemInformationBlockOne,
    Abort,
    Ping,
    RegisterUserEquipmentRequest>;

struct Message
{
    PayloadId id{};
    Payload payload{};
};

}
