#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <z3++.h>

#include "Sudoku.h"

std::string as_string::operator()(double x) const
{
	return std::to_string(x);
}

std::string as_string::operator()(unsigned int x) const
{
	return std::to_string(x);
}

std::string to_string(Param param)
{
	return std::visit(as_string(), param);
}

Sudoku::Sudoku(const std::string& grid_string)
	:grid(Grid()), stats(Stats())
{
	for (auto i = 0; i < 9; i++)
		for (auto j = 0; j < 9; j++)
		{
			auto idx = 9 * i + j;
			if (grid_string[idx] != '.')
				grid[i][j] = grid_string[idx] - '0';
		}
}

Param Sudoku::operator [](const std::string& key) const
{
	return stats.at(key);
}

std::string Sudoku::as_string() const
{
	std::ostringstream result;
	for (auto i = 0; i < 9; i++)
		for (auto j = 0; j < 9; j++)
			result << (grid[i][j] ? static_cast<char>(grid[i][j] + '0') : '.');
	return result.str();
}

void Sudoku::print()
{
	for (auto i = 0; i < 9; i++)
	{
		for (auto j = 0; j < 9; j++)
			std::cout << (grid[i][j] ? static_cast<char>(grid[i][j] + '0') : '.');
		std::cout << std::endl;
	}
}

void Sudoku::solve()
{
	z3::context c;
	z3::solver s(c);
	std::vector<z3::expr_vector> cells;

	for (auto i = 0; i < 9; i++)
	{
		cells.push_back(z3::expr_vector(c));
		for (auto j = 0; j < 9; j++)
		{
			std::ostringstream cell_name;
			cell_name << "r" << i << "c" << j;
			auto expr = c.int_const(cell_name.str().c_str());
			s.add(expr >= 1, expr <= 9);
			cells.back().push_back(expr);
		}
	}

	for (auto i = 0; i < 9; i++)
		for (auto j = 0; j < 9; j++)
			if (grid[i][j])
				s.add(cells[i][j] == grid[i][j]);

	for (auto i = 0; i < 9; i++)
	{
		auto col = z3::expr_vector(c);
		for (auto j = 0; j < 9; j++)
			col.push_back(cells[j][i]);
		s.add(z3::distinct(cells[i]), z3::distinct(col));
	}

	for (auto i = 0; i < 9; i += 3)
		for (auto j = 0; j < 9; j += 3)
		{
			auto box = z3::expr_vector(c);
			for (auto k = 0; k < 3; k++)
				for (auto l = 0; l < 3; l++)
					box.push_back(cells[i + k][j + l]);
			s.add(z3::distinct(box));
		}

	if (s.check() == z3::sat)
	{
		auto m = s.get_model();
		for (auto i = 0; i < 9; i++)
			for (auto j = 0; j < 9; j++)
				grid[i][j] = m.eval(cells[i][j]).as_int64();

		auto statistics = s.statistics();
		for (auto i = 0; i < statistics.size(); i++)
		{
			Param param;
			if (statistics.is_uint(i))
				param = statistics.uint_value(i);
			else
				param = statistics.double_value(i);
			stats[statistics.key(i)] = param;
		}
	}
}
