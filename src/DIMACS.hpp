#pragma once

#include "types.hpp"

#include <vector>
#include <string>

class DIMACS
{
public:
	// constructors
	DIMACS() = default;
	DIMACS(std::string const &filename); // reads input from file
	DIMACS(std::vector<std::vector<int>> &cnf) : _cnf(cnf){};

	// file i/o
	void clear_cnf() noexcept;
	void write_to_file(std::string const &filename) const; // writes cnf to file
	void get_vec_cnf(std::vector<std::vector<int>> &cnf) noexcept;

private:
	unsigned int n_vars = 0;
	unsigned int n_clauses = 0;
	dimacs_cnf _cnf{};
};