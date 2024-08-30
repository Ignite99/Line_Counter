#include "file_processor.h"
#include "directory_processor.h"
#include "utils.h"
#include <filesystem>
#include <set>
#include <iostream>

using namespace std;

void printReport(int fileCount, LineCounts &counts)
{
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << setw(6) << "Files" << setw(8) << "Lines" << setw(8) << "Code"
         << setw(10) << "Comments" << setw(8) << "Blanks" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << setw(6) << fileCount << setw(8) << counts.total << setw(8) << counts.code
         << setw(10) << counts.comments << setw(8) << counts.blanks << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
}

int main(int argc, char *argv[])
{
    LineCounts counts;
    int fileCount = 0;
    std::string extension, path;
    std::set<std::string> validExtensions = {".c", ".cpp", ".cc"};

    if (argc < 2)
    {
        std::cerr << "[ERROR] Usage: " << argv[0] << " <path_to_directory>/<path_to_file>" << std::endl;
        return 1;
    }

    path = argv[1];
    extension = std::filesystem::path(path).extension().string();

    if (std::filesystem::is_regular_file(path) && isValidSourceFile(extension, validExtensions))
    {
        counts.fileCounts = 1;
        processFile(path, counts);
    }
    else if (std::filesystem::is_directory(path))
    {
        counts.fileCounts = countFiles(path, validExtensions);
        processDirectory(path, counts);
    }
    else
    {
        std::cerr << "The path provided is neither a valid file nor a directory with source files." << std::endl;
        return 1;
    }

    printReport(fileCount, counts);

    return 0;
}