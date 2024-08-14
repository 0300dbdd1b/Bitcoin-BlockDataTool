#include "utils.hpp"
#include <cstdint>
#include <stdexcept>

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

uint32_t readLittleEndian(const vector<uint8_t>& data, size_t start)
{
    return uint32_t(data[start]) |
           (uint32_t(data[start + 1]) << 8) |
           (uint32_t(data[start + 2]) << 16) |
           (uint32_t(data[start + 3]) << 24);
}

uint32_t toBigEndian(uint32_t value) 
{
    return ((value >> 24) & 0x000000FF)| 
           ((value >> 8) & 0x0000FF00) | 
           ((value << 8) & 0x00FF0000) | 
           ((value << 24) & 0xFF000000);
}




uint64_t decodeCompactSize(std::vector<uint8_t>::const_iterator& begin, std::vector<uint8_t>::const_iterator end) {
    if (begin == end) {
        throw std::runtime_error("Empty range for decodeCompactSize");
    }

    uint64_t value = 0;
    uint8_t firstByte = *begin++;  // Advance iterator and read the first byte

    if (firstByte < 0xfd) {
        value = firstByte;
    } else if (firstByte == 0xfd) {
        if (std::distance(begin, end) < 2) {
            throw std::runtime_error("Not enough data for CompactSize");
        }
        value = static_cast<uint64_t>(*begin) | (static_cast<uint64_t>(*(begin + 1)) << 8);
        begin += 2;  // Advance iterator past the next 2 bytes
    } else if (firstByte == 0xfe) {
        if (std::distance(begin, end) < 4) {
            throw std::runtime_error("Not enough data for CompactSize");
        }
        value = static_cast<uint64_t>(*begin) |
                (static_cast<uint64_t>(*(begin + 1)) << 8) |
                (static_cast<uint64_t>(*(begin + 2)) << 16) |
                (static_cast<uint64_t>(*(begin + 3)) << 24);
        begin += 4;  // Advance iterator past the next 4 bytes
    } else if (firstByte == 0xff) {
        if (std::distance(begin, end) < 8) {
            throw std::runtime_error("Not enough data for CompactSize");
        }
        value = static_cast<uint64_t>(*begin) |
                (static_cast<uint64_t>(*(begin + 1)) << 8) |
                (static_cast<uint64_t>(*(begin + 2)) << 16) |
                (static_cast<uint64_t>(*(begin + 3)) << 24) |
                (static_cast<uint64_t>(*(begin + 4)) << 32) |
                (static_cast<uint64_t>(*(begin + 5)) << 40) |
                (static_cast<uint64_t>(*(begin + 6)) << 48) |
                (static_cast<uint64_t>(*(begin + 7)) << 56);
        begin += 8;  // Advance iterator past the next 8 bytes
    }

    return value;
}


uint64_t decodeCompactSize(const std::vector<uint8_t>& data, size_t& bytesConsumed) {
    size_t pos = bytesConsumed; // Start from the current offset in data

    if (pos >= data.size()) throw std::runtime_error("Out of range");

    uint64_t value = 0;
    uint8_t firstByte = data[pos++];
    bytesConsumed++;

    if (firstByte < 0xfd) {
        value = firstByte;
    } else if (firstByte == 0xfd) {
        if (pos + 1 >= data.size()) throw std::runtime_error("Not enough data for CompactSize");
        value = static_cast<uint64_t>(data[pos]) | (static_cast<uint64_t>(data[pos + 1]) << 8);
        bytesConsumed += 2;
    } else if (firstByte == 0xfe) {
        if (pos + 3 >= data.size()) throw std::runtime_error("Not enough data for CompactSize");
        value = static_cast<uint64_t>(data[pos]) |
                (static_cast<uint64_t>(data[pos + 1]) << 8) |
                (static_cast<uint64_t>(data[pos + 2]) << 16) |
                (static_cast<uint64_t>(data[pos + 3]) << 24);
        bytesConsumed += 4;
    } else if (firstByte == 0xff) {
        if (pos + 7 >= data.size()) throw std::runtime_error("Not enough data for CompactSize");
        value = static_cast<uint64_t>(data[pos]) |
                (static_cast<uint64_t>(data[pos + 1]) << 8) |
                (static_cast<uint64_t>(data[pos + 2]) << 16) |
                (static_cast<uint64_t>(data[pos + 3]) << 24) |
                (static_cast<uint64_t>(data[pos + 4]) << 32) |
                (static_cast<uint64_t>(data[pos + 5]) << 40) |
                (static_cast<uint64_t>(data[pos + 6]) << 48) |
                (static_cast<uint64_t>(data[pos + 7]) << 56);
        bytesConsumed += 8;
    }

    return value;
}
