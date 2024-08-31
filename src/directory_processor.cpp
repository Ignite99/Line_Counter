#include "directory_processor.h"
#include "file_processor.h"
#include "utils.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <set>

using namespace std;
namespace fs = filesystem;

// Called when main.cpp iterates through the directory path to process the files
void processDirectory(string &directory, LineCounts &counts, set<string> &validExtensions)
{
    string extension;

    // Iterate through directory
    for (auto &entry : fs::recursive_directory_iterator(directory))
    {
        // Check if it is a file
        if (entry.is_regular_file())
        {
            // Check if it is a valid extension
            extension = entry.path().extension().string();
            if (isValidSourceFile(extension, validExtensions))
            {
                processFile(entry.path().string(), counts);
            }
        }
    }
}

// Counts number of files in said directory
int countFiles(string &directory, set<string> &validExtensions)
{
    int fileCount = 0;
    string extension;

    // Iterates through directory
    for (auto &entry : fs::recursive_directory_iterator(directory))
    {
        // Check if it is a file
        if (entry.is_regular_file())
        {
            // Check if extension is part of the valid set of extensions
            extension = entry.path().extension().string();
            if (isValidSourceFile(extension, validExtensions))
            {
                fileCount++;
            }
        }
    }

    return fileCount;
}