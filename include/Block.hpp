#include "BlockDataTool.hpp"

class BlockHeader
{
public:
	uint32_t version;
    std::array<uint8_t, 32> prevBlockHash;
    std::array<uint8_t, 32> merkleRoot;
    uint32_t timestamp;
    uint32_t bits;
    uint32_t nonce;
};


class Block
{
public:
	BlockHeader blockHeader;
	std::vector<Transaction> transactions;
	std::array<uint8_t, 32> blockHash;
	std::string location;
};
