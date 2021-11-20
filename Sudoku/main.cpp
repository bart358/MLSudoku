#include <Csv.h>
#include <Timer.h>
#include <Sudoku.h>

constexpr auto rows = 100000;
const std::string input_path = "../../../../sudoku-3m.csv";
const std::string output_path = "../../../../result.csv";

Row params = {
	"arith-make-feasible",
	"conflicts",
	"decisions",
	"memory",
	"mk clause",
	"arith-diseq",
	"arith eq adapter",
	"propagations",
	"binary propagations",
	"added eqs",
	"mk bool var",
	"arith-lower",
	"arith-upper",
	"arith-fixed-eqs",
	"arith-conflicts",
	"arith-bound-propagations-lp",
	"arith-max-columns",
	"arith-max-rows",
	"arith-offset-eqs",
	"rlimit count",
};

int main()
{
	const Timer timer;
	Csv input = read_csv(input_path, rows + 1), output = Csv(input.size());
	output.front() = params;
	output.front().insert(output.front().end(), {"clues", "difficulty"});
#pragma omp parallel for
	for (auto i = 1; i < static_cast<int>(input.size()); i++)
	{
		Sudoku sudoku(input[i][1]);
		sudoku.solve();
		if (sudoku.as_string() != input[i][2])
		{
			auto msg = "Solution no. " + std::to_string(i) + " is incorrect.";
			throw std::runtime_error(msg);
		}
		for (auto &param : params)
			output[i].push_back(to_string(sudoku[param]));
		output[i].insert(output[i].end(), {input[i][3], input[i][4]});
	}
	to_csv(output, output_path);
	return 0;
}
