#include "BlkParser.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

BlkParser::BlkParser(const string& directoryPath)
{
	vector<string> blkFiles = listBlkFiles(directoryPath);
	for (const auto &file : blkFiles)
	{
		ParseBlkFile(file);
	}
}

void BlkParser::ParseBlkFile(const string &blkFilePath)
{
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
		//return ;
	}
	uint32_t magic, blockSize;

	fileStream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
	fileStream.read(reinterpret_cast<char *>(&blockSize), sizeof(blockSize));
	cout << "Magic : " << magic << " Block Size : " << blockSize << endl;
	if (fileStream.eof())
		return;
}

void BlkParser::ParseBlkBlock(ifstream fileStream)
{		
}

void BlkParser::Parse(const string &args)
{

}


