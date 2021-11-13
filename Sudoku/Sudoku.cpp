#include "Sudoku.h"

int main()
{
	auto sudokus = read_csv("../../../../sudoku-3m.csv");
    for (auto &cell : sudokus.front())
    {
        std::cout << cell << std::endl;
    }
	return 0;
}
