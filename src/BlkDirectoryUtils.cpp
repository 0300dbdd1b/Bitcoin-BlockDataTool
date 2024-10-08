#include <string>
#include <regex>
#include <filesystem>
#include <set>
#include <vector>

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


