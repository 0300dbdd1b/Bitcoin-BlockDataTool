#include "BlockDataTool.hpp"

using namespace std;
// Function to list all files in the blk directory with the specific format
vector<string> listBlkFiles(const string &directoryPath) 
{
    vector<string> blkFiles;
    set<string> uniqueFiles;

    regex blkPattern(R"(blk\d{5}\.dat)");

    for (const auto &entry : filesystem::directory_iterator(directoryPath)) 
	{
        if (entry.is_regular_file()) 
		{
            string fileName = entry.path().filename().string();
            if (regex_match(fileName, blkPattern)) 
			{
                if (uniqueFiles.insert(fileName).second)  // Insert returns a pair, where .second is true if inserted
                    blkFiles.push_back(entry.path().string());
            }
        }
    }
    return blkFiles;
}

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
    vector<string> files = listBlkFiles(blkDir);
    for (const auto &file : files) {
        cout << "Found blk file: " << file << endl;
    }

    return 0;
}
