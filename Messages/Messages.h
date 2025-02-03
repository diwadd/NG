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
	uint32_t messageId{};
};

using CellIdentity = uint32_t;

struct CellAccessRelatedInfo
{
    CellIdentity cellIdentity{};
};

struct SystemInformationBlockOne
{
    CellAccessRelatedInfo cellAccessRelatedInfo{};
};

struct Abort
{
    std::string note{};
};

struct Ping
{
    std::string note{};
};

struct RegisterUserEquipmentRequest
{
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
