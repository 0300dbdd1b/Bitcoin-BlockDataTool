#ifndef BLOCKPARSER_HPP
#define BLOCKPARSER_HPP

#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <ios>

#include "ErrorHandler.hpp"

typedef struct BlkFile
{
	std::filesystem::path path;
	std::ifstream fileStream;
	std::streamsize size;
}BlkFile;

class BlkParser
{
public:
	BlkParser(const std::string &directoryPath);
	ErrorCode Parse(const std::string& args);
	ErrorCode ParseBlkFile(const std::string& blkFilePath, uint8_t *rawData);
	ErrorCode ParseBlkBlock(std::ifstream fileStream);

};

#endif // BLOCKPARSER_HPP
