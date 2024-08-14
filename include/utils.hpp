#ifndef UTILS_HPP
#define UTILS_HPP

 #include <string>
 #include <vector>
 #include <array>
 #include <cstdint>
 #include <set>

 // Maximum size of a raw block in bytes
 #define LIMITS_MAX_BLOCK_SIZE 4718592

enum  MagicByte
{
	MAINNET = 0xf9beb4d9,
	TESTNET = 0x0b110907,
	REGTEST = 0xfabfb5da
};

std::string bytesToHex(const std::vector<uint8_t>& bytes);
std::string bytesToHex(const std::array<uint8_t, 32>& bytes);
std::vector<std::string> listBlkFiles(const std::string &directoryPath);
uint32_t readLittleEndian(const std::vector<uint8_t>& data, size_t start);
uint32_t toBigEndian(uint32_t value);
uint64_t decodeCompactSize(const std::vector<uint8_t>& data, size_t& bytesConsumed);


#endif // UTILS_HPP
