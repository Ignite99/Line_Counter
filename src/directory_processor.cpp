#include "directory_processor.h"
#include "file_processor.h"
#include "utils.h"

#include <filesystem>

using namespace std;
namespace fs = filesystem;

void processDirectory(std::string &directory, LineCounts &counts)
{
    for (auto &entry : fs::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            string extension = entry.path().extension().string();
            if (extension == ".c" || extension == ".cpp" || extension == ".cc")
            {
                processFile(entry.path().string(), counts);
            }
        }
    }
}

int countFiles(std::string &directory, std::set<std::string> &validExtensions)
{
    int fileCount = 0;
    for (auto &entry : fs::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            string extension = entry.path().extension().string();
            if (isValidSourceFile(extension, validExtensions))
            {
                fileCount++;
            }
        }
    }

    return fileCount;
}