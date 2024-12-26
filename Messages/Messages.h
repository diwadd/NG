#pragma once
#include <cstdint>
#include <variant>

using PayloadId = uint32_t;

constexpr PayloadId MASTER_INFORMATION_BLOCK     = 0x0001; 
constexpr PayloadId SYSTEM_INFORMATION_BLOCK_ONE = 0x0002;

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

using Payload = std::variant<
    MasterInformationBlock,
    SystemInformationBlockOne>;

struct Message
{
    Payload payload{};
};

