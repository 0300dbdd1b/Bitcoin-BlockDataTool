#include "Transaction.hpp"
#include <cstdio>


using namespace std;
void Transaction::AddInput(const TxInput& input)
{
	inputs.push_back(input);
}

void Transaction::AddOutput(const TxOutput& output)
{
	outputs.push_back(output);
}


void Transaction::print() {
    printf("Transaction ID (txid): ");
    for (auto byte : txid) {
        printf("%02x", byte);
    }
    printf("\n");

    printf("Witness Transaction ID (wtxid): ");
    for (auto byte : wtxid) {
        printf("%02x", byte);
    }
    printf("\n");

    printf("Version: %u\n", version);
    printf("Marker: %u\n", marker);
    printf("Flag: %u\n", flag);
    printf("Input Count: %u\n", inputCount);

    printf("Inputs:\n");
    for (size_t i = 0; i < inputs.size(); ++i) {
        const TxInput& input = inputs[i];
        printf("  Input %zu:\n", i + 1);

        printf("    Previous Transaction Hash: ");
        for (auto byte : input.prevTxHash) {
            printf("%02x", byte);
        }
        printf("\n");

        printf("    Output Index: %u\n", input.outputIndex);

        printf("    ScriptSig: ");
        for (auto byte : input.scriptSig) {
            printf("%02x", byte);
        }
        printf("\n");

        printf("    Sequence: %u\n", input.sequence);
    }

    printf("Output Count: %u\n", outputCount);

    printf("Outputs:\n");
    for (size_t i = 0; i < outputs.size(); ++i) {
        const TxOutput& output = outputs[i];
        printf("  Output %zu:\n", i + 1);
        printf("    Value: %llu (satoshis)\n", output.value);

        printf("    ScriptPubKey: ");
        for (auto byte : output.scriptPubKey) {
            printf("%02x", byte);
        }
        printf("\n");
    }

    printf("Witness: %u\n", witness);
    printf("Lock Time: %u\n", lockTime);
    printf("Size: %llu bytes\n", size);
    printf("Weight: %llu weight units\n", weight);
    printf("Virtual Size (vsize): %llu virtual bytes\n", vsize);
}

