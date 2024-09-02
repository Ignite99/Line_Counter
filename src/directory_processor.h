// Called only once for compilation
#pragma once

#include "line_counts.h"

#include <string>
#include <set>

void processDirectory(std::string &directory, LineCounts &counts, std::set<std::string> &validExtensions, std::set<std::string> &validFiles);
int countFiles(std::string &directory, std::set<std::string> &validExtensions, std::set<std::string> &validFiles);