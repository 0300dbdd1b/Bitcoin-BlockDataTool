#ifndef BLOCKPARSER_HPP
#define BLOCKPARSER_HPP

#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>

#include "ErrorHandler.hpp"
#include "Block.hpp"

typedef struct BlkFile
{
	std::filesystem::path path;
	std::ifstream fileStream;
	std::streamsize size;
}BlkFile;

class BlkParser
{
public:
	std::vector<std::string> blkFiles;
	std::vector<Block> blocks;
	BlkParser(const std::string &directoryPath);
	ErrorCode Parse(const std::string& args);
	ErrorCode ParseBlkFile(const std::string& blkFilePath, uint8_t *rawData);
	ErrorCode ParseBlock(const uint8_t *rawData);

};

#endif // BLOCKPARSER_HPP
