#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <regex>
#include <set>

using namespace std;
namespace fs = filesystem;

struct LineCounts
{
    int fileCounts = 0;
    int total = 0;
    int code = 0;
    int comments = 0;
    int blanks = 0;
};

void processFile(const string &filename, LineCounts &counts)
{
    string line;
    bool inMultiLineComment = false;

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }
    regex commentRegex(R"((\/\*[\s\S]*\*\/)|(\/\/.*$))");

    while (getline(file, line))
    {
        counts.total++;
        string trimmedLine = regex_replace(line, regex("^\\s+|\\s+$"), "");

        if (trimmedLine.empty())
        {
            counts.blanks++;
        }
        else if (inMultiLineComment)
        {
            counts.comments++;
            if (trimmedLine.find("*/") != string::npos)
            {
                inMultiLineComment = false;
            }
        }
        else if (trimmedLine.find("/*") != string::npos)
        {
            counts.comments++;
            if (trimmedLine.find("*/") == string::npos)
            {
                inMultiLineComment = true;
            }
        }
        else if (regex_search(trimmedLine, commentRegex))
        {
            string beforeComment = trimmedLine.substr(0, trimmedLine.find("//"));
            beforeComment = regex_replace(beforeComment, regex("^\\s+|\\s+$"), "");
            if (!beforeComment.empty())
            {
                counts.code++;
            }
            else
            {
                counts.comments++;
            }
        }
        else
        {
            counts.code++;
        }
    }

    file.close();
}

void processDirectory(string &directory, LineCounts &counts)
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

bool isValidSourceFile(string &extension, set<string> &validExtensions)
{
    return validExtensions.find(extension) != validExtensions.end();
}

int countFiles(string &directory, set<string> &validExtensions)
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
    int fileCount;
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
        cerr << "The path provided is neither a valid file nor a directory with source files." << endl;
        return 1;
    }

    printReport(fileCount, counts);

    return 0;
}