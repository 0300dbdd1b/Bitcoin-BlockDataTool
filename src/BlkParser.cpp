#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>
#include <cstring>

#include "ErrorHandler.hpp"
#include "utils.hpp"
#include "Block.hpp"
#include "BlkParser.hpp"

using namespace std;

BlkParser::BlkParser(const string& directoryPath)
{
	this->blkFiles = listBlkFiles(directoryPath);
}

ErrorCode BlkParser::ParseBlkFile(const string &blkFilePath, vector<uint8_t> &rawData)
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

		fileStream.read(reinterpret_cast<char *>(&magic), sizeof(uint32_t));
		if (fileStream.eof())
			break;
		magic = toBigEndian(magic);
		if (magic != MAINNET && magic != REGTEST && magic != TESTNET)
			return Error("Unknown Magic Number\n", ERROR);
		
		fileStream.read(reinterpret_cast<char *>(&blockSize), sizeof(uint32_t));
		printf("Magic : 0x%08X Block Size : %d\n", magic, blockSize);
		if (blockSize > LIMITS_MAX_BLOCK_SIZE)
			return Error("Block Size > MAX_BLOCK_SIZE", ERROR);
		rawData.resize(blockSize);
		fileStream.read(reinterpret_cast<char *>(rawData.data()), sizeof(char) * blockSize);
		if (ParseBlock(rawData) != SUCCESS)
			return Error("Unable to parse block\n", ERROR);
	}
	fileStream.close();
	return SUCCESS;
}


BlockHeader BlkParser::ParseBlockHeader(const vector<uint8_t> &rawData)
{
	BlockHeader header;
	size_t pos = 0;

	memcpy(&header.version, rawData.data() + pos, sizeof(header.version));
	pos += sizeof(header.version);

	memcpy(&header.prevBlockHash, rawData.data() + pos, sizeof(header.prevBlockHash));
	pos += sizeof(header.prevBlockHash);
	reverse(header.prevBlockHash.begin(), header.prevBlockHash.end());

	memcpy(&header.merkleRoot, rawData.data() + pos, sizeof(header.merkleRoot));
	pos += sizeof(header.merkleRoot);
	reverse(header.merkleRoot.begin(), header.merkleRoot.end());

	memcpy(&header.timestamp, rawData.data() + pos, sizeof(header.timestamp));
	pos += sizeof(header.timestamp);

	memcpy(&header.bits, rawData.data() + pos, sizeof(header.bits));
	pos += sizeof(header.bits);

	memcpy(&header.nonce, rawData.data() + pos, sizeof(header.nonce));
	header.print();
	return header;


}

ErrorCode BlkParser::ParseBlock(const vector<uint8_t> &rawData)
{
	Block block;
	size_t pos = 0;


	uint64_t size = decodeCompactSize(rawData, pos);

	printf("SIZE : %d \n",  size);
	while (size > 0)
	{
		uint32_t version = readLittleEndian(rawData, 0);
		uint8_t marker = rawData[4];
		uint8_t flag = rawData[5];
		pos += sizeof(version) + sizeof(marker) + sizeof(flag);
		
		block.blockHeader = ParseBlockHeader(rawData);
		pos += 80;


		uint32_t inputCount = decodeCompactSize(rawData, pos);
		printf("%ld INPUTS\n", inputCount);
		
		size--;
		return ERROR;
	}
}

ErrorCode BlkParser::Parse(const string &args)
{
	vector<uint8_t> rawData;
	for (const auto &file : this->blkFiles)
	{
		if (ParseBlkFile(file, rawData) != SUCCESS)
			return Error("Failed to parse " + file + "\n", ERROR);
	}
	return SUCCESS;
}


