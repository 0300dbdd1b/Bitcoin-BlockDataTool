#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

#include "utils.hpp"
#include "Block.hpp"
#include "BlkParser.hpp"

using namespace std;

BlkParser::BlkParser(const string& directoryPath)
{
	uint8_t *rawData = (uint8_t *)malloc(sizeof(uint8_t) * LIMITS_MAX_BLOCK_SIZE);
	int i = 0;
	vector<string> blkFiles = listBlkFiles(directoryPath);
	
	
	for (const auto &file : blkFiles)
	{
		ParseBlkFile(file, rawData);
		i++;
	}
	cout << "IIIIIII : " << i << "\n";
	free(rawData);
}

ErrorCode BlkParser::ParseBlkFile(const string &blkFilePath, uint8_t *rawData)
{
	uint32_t magic, blockSize;
	vector<Block> blocks;

	filesystem::path filePath = blkFilePath;

	if (!filesystem::exists(filePath))
		return Error("File does not exist : " + blkFilePath + "\n", ERROR);
	
	ifstream fileStream(filePath, ios::binary);
	
	if (!fileStream.is_open())
		Error("Failed to open file : " + blkFilePath + "\n", ERROR);


	fileStream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
	fileStream.read(reinterpret_cast<char *>(&blockSize), sizeof(blockSize));
	magic = toBigEndian(magic);
	
	if (magic != MAINNET && magic != REGTEST && magic != TESTNET)
		return Error("Unknown Magic Number\n", ERROR);

	printf("Magic : 0x%08X Block Size : %d\n", magic, blockSize);
	fileStream.read(reinterpret_cast<char *>(rawData), sizeof(char) * blockSize);

	fileStream.close();
	return SUCCESS;
}

ErrorCode BlkParser::ParseBlkBlock(ifstream fileStream)
{
	return Error("", ERROR);
}

ErrorCode BlkParser::Parse(const string &args)
{
	return Error("", ERROR);
}
