#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

 #include <vector>
 #include <cstdint>
 #include <array>

struct TxInput {
    std::array<uint8_t, 32> prevTxHash;
    uint32_t outputIndex;
    std::vector<uint8_t> scriptSig;
    uint32_t sequence;
};

struct TxOutput {
    uint64_t value;
    std::vector<uint8_t> scriptPubKey;
};

class Transaction
{
public:
	void AddInput(const TxInput& input);
	void AddOutput(const TxOutput& output);
	uint64_t GetFees();
	void print();

	uint32_t version;
	uint32_t marker;
	uint32_t flag;
	uint32_t inputCount;
	std::vector<TxInput> inputs;
	uint32_t outputCount;
	std::vector<TxOutput> outputs;
	uint32_t witness;
	uint32_t lockTime;

	std::array<uint8_t, 32> txid;
	std::array<uint8_t, 32> wtxid;
	uint64_t size;
	uint64_t weight;
	uint64_t vsize;

};

#endif // TRANSACTION_HPP
