#pragma once

#include "line_counts.h"

#include <string>
#include <set>

void processDirectory(std::string &directory, LineCounts &counts);
int countFiles(std::string &directory, std::set<std::string> &validExtensions);