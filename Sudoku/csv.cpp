#include "Csv.h"

#include <sstream>

Csv read_csv(std::ifstream& file, int limit)
{
	Csv result;
	std::string line;
	auto counter = 0;
	while (std::getline(file, line))
	{
		std::string cell;
		std::vector<std::string> row;
		std::stringstream line_stream(line);
		while (std::getline(line_stream, cell, ','))
			row.push_back(cell);
		result.push_back(row);

		counter++;
		if (counter == limit)
			break;
	}
	file.close();
	return result;
}

Csv read_csv(const std::string& path, int limit)
{
	std::ifstream file(path);
	return read_csv(file, limit);
}

void to_csv(Csv csv, std::ofstream& file, int limit)
{
	limit = limit < 0 ? csv.size() : limit;
	for (auto i = 0; i < limit && i < csv.size(); i++)
	{
		for (auto& cell : csv[i])
			file << cell << ",";
		file << std::endl;
	}
	file.close();
}

void to_csv(Csv csv, const std::string& path, int limit)
{
	std::ofstream file(path);
	return to_csv(csv, file, limit);
}
