#include "Block.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

void BlockHeader::print(void)
{
        cout << "Block Header:" << endl;
        cout << "Version: " << version << endl;
        cout << "Previous Block Hash: " << bytesToHex(prevBlockHash) << endl;
        cout << "Merkle Root: " << bytesToHex(merkleRoot) << endl;
        cout << "Timestamp: " << timestamp << endl;
        cout << "Bits: " << bits << endl;
        cout << "Nonce: " << nonce << endl;
}


