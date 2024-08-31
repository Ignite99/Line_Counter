#include "file_processor.h"
#include <fstream>
#include <regex>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

void checkBeforeComment(string trimmedLine, LineCounts &counts, string type)
{
    string beforeComment;

    beforeComment = trimmedLine.substr(0, trimmedLine.find(type));
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

bool hasQuoteBefore(const string &line, size_t pos)
{
    return pos > 0 && line.find('"', 0) < pos;
}

bool hasQuoteAfter(const string &line, size_t pos)
{
    return line.find('"', pos) != string::npos;
}

void processFile(const std::string &filename, LineCounts &counts)
{
    string line, trimmedLine;
    ifstream file(filename);
    bool inMultiLineComment = false;
    regex commentRegex(R"((\/\*[\s\S]*\*\/)|(\/\/.*$))");

    if (!file.is_open())
    {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    while (getline(file, line))
    {
        counts.total++;
        trimmedLine = regex_replace(line, regex("^\\s+|\\s+$"), "");

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
            checkBeforeComment(trimmedLine, counts, "/*");
            if (trimmedLine.find("*/") == string::npos)
            {
                size_t startPos = trimmedLine.find("/*");
                bool quoteBefore = hasQuoteBefore(trimmedLine, startPos);
                bool quoteAfter = hasQuoteAfter(trimmedLine, startPos + 2);

                if (quoteAfter == true && quoteBefore == true)
                {
                    inMultiLineComment = false;
                }
                else
                {
                    inMultiLineComment = true;
                }
            }
        }
        else if (regex_search(trimmedLine, commentRegex))
        {
            checkBeforeComment(trimmedLine, counts, "//");
        }
        else
        {
            counts.code++;
        }
    }

    file.close();
}