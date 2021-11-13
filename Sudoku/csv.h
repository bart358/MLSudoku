#pragma once

#include <string>
#include <vector>
#include <fstream>

using Csv = std::vector<std::vector<std::string >>;

Csv read_csv(std::ifstream& file);

Csv read_csv(const std::string& path);
