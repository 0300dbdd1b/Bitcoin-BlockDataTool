#include "Transaction.hpp"

void Transaction::AddInput(const TxInput& input)
{
	inputs.push_back(input);
}

void Transaction::AddOutput(const TxOutput& output)
{
	outputs.push_back(output);
}
