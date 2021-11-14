#pragma once

#include <array>
#include <string>
#include <variant>
#include <unordered_map>

#include <z3++.h>

using Grid = std::array<std::array<int, 9>, 9>;
using Param = std::variant<double, unsigned int>;
using Stats = std::unordered_map<std::string, Param>;

struct as_string {
	std::string operator()(double x) const;
	std::string operator()(unsigned int x) const;
};

std::string to_string(Param param);

class Sudoku
{
	Grid grid;
	Stats stats;
public:
	Sudoku(const std::string& grid_string);

	Param operator [](const std::string& key) const;

	std::string as_string() const;

	void print();
	void solve();
};
