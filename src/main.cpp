#include <cstddef>
#include <string>
#include <vector>

#include "utils.hpp"
#include "BlkParser.hpp"

using namespace std;
int main(int ac, char *av[]) 
{
	string blkDir;
	if (ac != 2)
		blkDir = "data";
	else
		blkDir = av[1];

	// ifstream test(blkDir);
	if (!filesystem::exists(blkDir))
	{
		fprintf(stderr, "\"%s\" is not a valid path !\n", blkDir.c_str());
		return 1;
	}
	BlkParser parser(blkDir);
	parser.Parse("");
	return 0;
    vector<string> files = listBlkFiles(blkDir);
    for (const auto &file : files) {
        cout << "Found blk file: " << file << endl;
    }

    return 0;
}
