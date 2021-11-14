#pragma once

#include <string>
#include <vector>
#include <fstream>

using Row = std::vector<std::string>;
using Csv = std::vector<Row>;

Csv read_csv(std::ifstream& file, int limit = -1);

Csv read_csv(const std::string& path, int limit = -1);

void to_csv(Csv csv, std::ofstream& file, int limit = -1);

void to_csv(Csv csv, const std::string& path, int limit = -1);

