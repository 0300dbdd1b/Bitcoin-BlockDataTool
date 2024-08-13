#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

#include "ErrorHandler.hpp"
#include "utils.hpp"
#include "Block.hpp"
#include "BlkParser.hpp"

using namespace std;

BlkParser::BlkParser(const string& directoryPath)
{
	this->blkFiles = listBlkFiles(directoryPath);
}

ErrorCode BlkParser::ParseBlkFile(const string &blkFilePath, uint8_t *rawData)
{
	vector<Block> blocks;
	filesystem::path filePath = blkFilePath;

	if (!filesystem::exists(filePath))
		return Error("File does not exist : " + blkFilePath + "\n", ERROR);
	
	ifstream fileStream(filePath, ios::binary);
	
	if (!fileStream.is_open())
		Error("Failed to open file : " + blkFilePath + "\n", ERROR);

	while (!fileStream.eof())
	{
		Block block;
		uint32_t magic;
		uint32_t blockSize;

		fileStream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
		if (fileStream.eof())
			break;
		magic = toBigEndian(magic);
		if (magic != MAINNET && magic != REGTEST && magic != TESTNET)
			return Error("Unknown Magic Number\n", ERROR);
		
		fileStream.read(reinterpret_cast<char *>(&blockSize), sizeof(blockSize));
		printf("Magic : 0x%08X Block Size : %d\n", magic, blockSize);
		if (blockSize > LIMITS_MAX_BLOCK_SIZE)
			return Error("Block Size > MAX_BLOCK_SIZE", ERROR);
		fileStream.read(reinterpret_cast<char *>(rawData), sizeof(char) * blockSize);
		if (ParseBlock(rawData) != SUCCESS)
			return Error("Unable to parse  block\n", ERROR);
		memset(rawData, 0, sizeof(uint8_t) * LIMITS_MAX_BLOCK_SIZE);
	}
	fileStream.close();
	return SUCCESS;
}

ErrorCode BlkParser::ParseBlock(const uint8_t *rawData)
{
	Block block;


	return Error("", ERROR);
}

ErrorCode BlkParser::Parse(const string &args)
{
	uint8_t *rawData = (uint8_t *)malloc(sizeof(uint8_t) * LIMITS_MAX_BLOCK_SIZE);
	
	for (const auto &file : this->blkFiles)
	{
		if (ParseBlkFile(file, rawData) != SUCCESS)
			return Error("Failed to parse " + file + "\n", ERROR);
	}
	free(rawData);
	return SUCCESS;
}
