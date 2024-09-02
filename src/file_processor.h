#pragma once
#include <string>
#include "line_counts.h"

void processCPPFile(const std::string &filename, LineCounts &counts);
void processRubyFile(const std::string &filename, LineCounts &counts);