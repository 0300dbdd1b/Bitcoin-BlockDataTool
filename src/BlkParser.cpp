#include "BlkParser.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

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

void BlkParser::ParseBlkFile(const string &blkFilePath, uint8_t *rawData)
{
	vector<Block> blocks;
	filesystem::path filePath = blkFilePath;
	if (!filesystem::exists(filePath))
	{
		cerr << "File does not exist : " << blkFilePath << "\n";
		return ;
	}
	ifstream fileStream(filePath, ios::binary);
	if (!fileStream.is_open())
	{
		cerr << "Failed to open file : " << blkFilePath << "\n";
		return ;
	}
	uint32_t magic, blockSize;

	fileStream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
	fileStream.read(reinterpret_cast<char *>(&blockSize), sizeof(blockSize));
	magic = toBigEndian(magic);
	
	if (magic != MAINNET && magic != REGTEST && magic != TESTNET)
	{
		cerr << "Wrong Magic Number\n";
		return ;
	}
	cout << "magic : " << magic << " Block Size : " << blockSize << endl;
	fileStream.read(reinterpret_cast<char *>(rawData), sizeof(char) * blockSize);
	cout << "TKT FRR : " << rawData << endl;

	if (fileStream.eof())
		return;
	free(rawData);
	fileStream.close();
}

void BlkParser::ParseBlkBlock(ifstream fileStream)
{
}

void BlkParser::Parse(const string &args)
{
}
