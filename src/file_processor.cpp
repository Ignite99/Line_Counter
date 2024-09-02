#include "file_processor.h"

#include <fstream>
#include <regex>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

const string clearWhiteSpace = "^\\s+|\\s+$";

// Checks if there is quote before (Check if comment is within string)
bool hasQuoteBefore(const string &line, size_t pos)
{
    return pos > 0 && line.find('"', 0) < pos;
}

// Checks if there is quote after (Check if comment is within string)
bool hasQuoteAfter(const string &line, size_t pos)
{
    return line.find('"', pos) != string::npos;
}

// Check if substring before comment syntax has something present.
// If there is something before the comment syntax, it is code
void checkBeforeComment(string trimmedLine, LineCounts &counts, string commentSyntax)
{
    string beforeComment;

    // Take substring before syntax to check if it is empty
    beforeComment = trimmedLine.substr(0, trimmedLine.find(commentSyntax));
    beforeComment = regex_replace(beforeComment, regex(clearWhiteSpace), "");

    // If not empty before the comment syntax, it is a code line
    if (!beforeComment.empty())
    {
        // cout << trimmedLine << endl;
        counts.code++;
    }
    // If nothing else before comment syntax then it is a comment line
    else
    {
        counts.comments++;
    }
}

// Process the file targeted from directory_processor.cpp
void processCPPFile(const string &filename, LineCounts &counts)
{
    string line, trimmedLine;
    size_t startPos;
    bool quoteBefore, quoteAfter;
    ifstream file(filename);

    // Specific check for multiline comment header /* */
    bool inMultiLineComment = false;

    // Matches multiline or single line comments for all non-edge cases
    // EDIT: Realised some files did not have inline syntax editor turned on and had some
    // weird comment and code block placements imo (edge cases essentially) thus regex
    // was insufficient for such situations.
    regex commentRegex(R"((\/\*[\s\S]*\*\/)|(\/\/.*$))");

    // Opens the file, does another check if opened file is valid file.
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    // Iterate through every line of the file.
    while (getline(file, line))
    {
        counts.total++;
        // Clear whitespace in line to ensure no misinputs
        trimmedLine = regex_replace(line, regex(clearWhiteSpace), "");

        // If line is empty then adds to blank in counts struct from include/line_counts.h
        if (trimmedLine.empty())
        {
            counts.blanks++;
        }
        // Catches multiline comment after /* in next else if condition statement below,
        // thereafter every line up till */ will be a comment
        else if (inMultiLineComment)
        {
            counts.comments++;
            // If find */ will exit continuous loop to catch multiline comment
            if (trimmedLine.find("*/") != string::npos)
            {
                inMultiLineComment = false;
            }
        }
        // Catches multiline comment /* initiation
        else if (trimmedLine.find("/*") != string::npos)
        {
            // To check if multiline comment had code before it
            checkBeforeComment(trimmedLine, counts, "/*");

            // If multiline comment does not have end of multiline syntax within current line mutliline boolean = true to
            // make all further lines after this line comment till */ is found
            if (trimmedLine.find("*/") == string::npos)
            {
                // Another check if multiline comment syntax is within a string literal
                startPos = trimmedLine.find("/*");
                quoteBefore = hasQuoteBefore(trimmedLine, startPos);
                quoteAfter = hasQuoteAfter(trimmedLine, startPos + 2);

                // If /* is nested in a string, then it is code not a multiline comment starter
                if (quoteAfter == true && quoteBefore == true)
                {
                    inMultiLineComment = false;
                }
                // /* is not nested in a string, thus it is a multiline comment initiator
                else
                {
                    inMultiLineComment = true;
                }
            }
        }
        // Checks commentRegex to determine if line is a comment or not
        else if (regex_search(trimmedLine, commentRegex))
        {
            // Check if before the comment syntax there is code
            checkBeforeComment(trimmedLine, counts, "//");
        }
        else
        {
            counts.code++;
        }
    }

    file.close();
}

void processRubyFile(const string &filename, LineCounts &counts)
{
    string line, trimmedLine;
    size_t startPos;
    bool quoteBefore, quoteAfter;
    ifstream file(filename);
    bool inMultiLineComment = false;

    if (!file.is_open())
    {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    while (getline(file, line))
    {
        counts.total++;
        trimmedLine = regex_replace(line, regex(clearWhiteSpace), "");
        if (trimmedLine.empty())
        {
            counts.blanks++;
        }
        else if (inMultiLineComment)
        {
            counts.comments++;
            if (trimmedLine.find("=end") != string::npos)
            {
                inMultiLineComment = false;
            }
        }
        else if (trimmedLine.find("=begin") != string::npos)
        {
            checkBeforeComment(trimmedLine, counts, "=begin");
            if (trimmedLine.find("=end") == string::npos)
            {
                startPos = trimmedLine.find("=begin");
                quoteBefore = hasQuoteBefore(trimmedLine, startPos);
                quoteAfter = hasQuoteAfter(trimmedLine, startPos + 2);
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
        else if (trimmedLine.find("#") == 0)
        {
            checkBeforeComment(trimmedLine, counts, "#");
        }
        else
        {
            // cout << trimmedLine << endl;
            counts.code++;
        }
    }
}