#ifndef UTILS_HPP
#define UTILS_HPP

#include "BlockDataTool.hpp"

std::string bytesToHex(const std::vector<uint8_t>& bytes);
std::string bytesToHex(const std::array<uint8_t, 32>& bytes);
std::vector<std::string> listBlkFiles(const std::string &directoryPath);
#endif // UTILS_HPP
