#include "BlockDataTool.hpp"

using namespace std;
string bytesToHex(const vector<uint8_t>& bytes)
{
	string hex;
	for (uint8_t byte : bytes) {
		char buf[3];
		snprintf(buf, sizeof(buf), "%02x", byte);
		hex += buf;
	}
	return hex;
}

string bytesToHex(const array<uint8_t, 32>& bytes)
{
	string hex;
	for (uint8_t byte : bytes) {
		char buf[3];
		snprintf(buf, sizeof(buf), "%02x", byte);
		hex += buf;
	}
	return hex;
}

