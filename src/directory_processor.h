// Called only once for compilation
#pragma once

#include "line_counts.h"

#include <string>
#include <set>

void processDirectory(std::string &directory, LineCounts &counts, std::set<std::string> &validExtensions);
int countFiles(std::string &directory, std::set<std::string> &validExtensions);