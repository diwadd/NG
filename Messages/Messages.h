#pragma once
#include <cstdint>
#include <variant>

using MessageId = uint32_t;

constexpr MessageId MASTER_INFORMATION_BLOCK     = 0x0001; 
constexpr MessageId SYSTEM_INFORMATION_BLOCK_ONE = 0x0002;


struct MasterInformationBlock
{
    static constexpr MessageId id = MASTER_INFORMATION_BLOCK;
	uint32_t messageId{};
};

using CellIdentity = uint32_t;

struct CellAccessRelatedInfo
{
    CellIdentity cellIdentity{};
};

struct SystemInformationBlockOne
{
    static constexpr MessageId id = SYSTEM_INFORMATION_BLOCK_ONE;
    CellAccessRelatedInfo cellAccessRelatedInfo{};
};

using Payload = std::variant<
    MasterInformationBlock,
    SystemInformationBlockOne>;

struct Message
{
    MessageId id{};
    Payload payload{};
};

