#include "csv.h"

#include <sstream>

Csv read_csv(std::ifstream& file)
{
    Csv result;
    std::string line;
    while (std::getline(file, line))
    {
        std::string cell;
        std::vector<std::string> row;
        std::stringstream line_stream(line);
        while (std::getline(line_stream, cell, ','))
            row.push_back(cell);
        result.push_back(row);
    }
    file.close();
    return result;
}

Csv read_csv(const std::string& path)
{
    std::ifstream file(path);
    return read_csv(file);
}
