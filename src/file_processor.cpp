#include "file_processor.h"
#include <fstream>
#include <regex>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

void processFile(const std::string &filename, LineCounts &counts)
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