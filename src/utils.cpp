#include "utils.h"

bool isValidSourceFile(std::string &extension, std::set<std::string> &validExtensions)
{
    return validExtensions.find(extension) != validExtensions.end();
}