#ifndef BLOCKPARSER_HPP
#define BLOCKPARSER_HPP

#include "BlockDataTool.hpp"

class BlockParser
{
public:
	BlockParser(const std::string& path);
	void Parse(const std::string& args);
};

#endif // BLOCKPARSER_HPP
