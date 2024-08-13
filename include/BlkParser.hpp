#ifndef BLOCKPARSER_HPP
#define BLOCKPARSER_HPP

#include "BlockDataTool.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>


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
	void Parse(const std::string& args);
	void ParseBlkFile(const std::string& blkFilePath, uint8_t *rawData);
	void ParseBlkBlock(std::ifstream fileStream);

};

#endif // BLOCKPARSER_HPP
