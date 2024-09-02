#pragma once

#include <string>
#include <set>

bool isValidSourceFile(std::string &extension, std::set<std::string> &validExtensions);
bool isValidFile(std::string &file, std::set<std::string> &validFiles);