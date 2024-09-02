#include "utils.h"

// Check if extension is valid
bool isValidSourceFile(std::string &extension, std::set<std::string> &validExtensions)
{
    return validExtensions.find(extension) != validExtensions.end();
}

bool isValidFile(std::string &file, std::set<std::string> &validFiles)
{
    return validFiles.find(file) != validFiles.end();
}