#include "utils.h"

// Check if extension is valid
bool isValidSourceFile(std::string &extension, std::set<std::string> &validExtensions)
{
    return validExtensions.find(extension) != validExtensions.end();
}