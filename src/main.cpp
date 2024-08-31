#include "file_processor.h"
#include "directory_processor.h"
#include "utils.h"

#include <filesystem>
#include <iomanip>
#include <fstream>
#include <set>
#include <iostream>

using namespace std;
namespace fs = filesystem;

void printReport(int fileCount, LineCounts &counts, string folderName, string path)
{
    // Create directory if it does not exist
    if (!fs::exists(folderName))
    {
        fs::create_directory(folderName);
    }

    // Open file in the specified directory to log output
    ofstream reportFile(fs::path(folderName) / "report.txt");
    if (!reportFile)
    {
        cerr << "Error opening report file for writing" << endl;
        return;
    }

    // Write report to report.txt file
    reportFile << path << endl;
    reportFile << "--------------------------------------------------------------------------------------------------" << endl;
    reportFile << setw(6) << "Files" << setw(8) << "Lines" << setw(8) << "Code"
               << setw(10) << "Comments" << setw(8) << "Blanks" << endl;
    reportFile << "--------------------------------------------------------------------------------------------------" << endl;
    reportFile << setw(6) << fileCount << setw(8) << counts.total << setw(8) << counts.code
               << setw(10) << counts.comments << setw(8) << counts.blanks << endl;
    reportFile << "--------------------------------------------------------------------------------------------------" << endl;

    reportFile.close();
}

int main(int argc, char *argv[])
{
    LineCounts counts;
    string extension, path;
    set<string> validExtensions = {".c", ".cpp", ".cc"};

    if (argc < 2)
    {
        cerr << "[ERROR] Usage: " << argv[0] << " <path_to_directory>/<path_to_file>" << endl;
        return 1;
    }

    path = argv[1];
    extension = fs::path(path).extension().string();

    if (fs::is_regular_file(path) && isValidSourceFile(extension, validExtensions))
    {
        counts.fileCounts = 1;
        processFile(path, counts);
    }
    else if (fs::is_directory(path))
    {
        counts.fileCounts = countFiles(path, validExtensions);
        processDirectory(path, counts);
    }
    else
    {
        cerr << "The path provided is not a valid file or a directory with the files that are valid for tabulating." << endl;
        return 1;
    }

    printReport(counts.fileCounts, counts, "report", path);

    return 0;
}