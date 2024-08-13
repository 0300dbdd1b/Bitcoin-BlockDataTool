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

uint32_t toBigEndian(uint32_t value) 
{
    return ((value >> 24) & 0x000000FF)| 
           ((value >> 8) & 0x0000FF00) | 
           ((value << 8) & 0x00FF0000) | 
           ((value << 24) & 0xFF000000);
}
