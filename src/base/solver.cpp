#include <cmath>
#include <algorithm>

#include "solver.hpp"

template <typename... lits>
requires all_literal<lits...>
void Solver::add_clause(lits... literals)
{
	this->cnf.emplace_back(literals...);
}
void Solver::add_clause(clause_t in)
{
	this->cnf.push_back(in);
}
void Solver::add_clause(clause_t &&in)
{
	this->cnf.push_back(in);
}
void Solver::add_clause(clause_t const &in)
{
	this->cnf.push_back(in);
}

size_t Solver::count_vars()
{
	// if literal type changes, this also needs to change
	size_t out = 0;
	for (auto &cl : this->cnf)
	{
		for (auto lit : cl)
		{
			out = std::max((size_t)std::abs(lit), out);
		}
	}
	return out;
}