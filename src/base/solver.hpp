#pragma once
#include <vector>

#include "../DIMACS.hpp"

using literal = int32_t; // label for a variable, may split later into an individual literal type
using clause_t = std::vector<literal>;
using cnf_t = std::vector<clause_t>;

template <typename... Ts>
concept all_literal = std::same_as<literal, std::common_type<Ts...>>;

class Solver
{
	// remember to inherit virtually from this class
public:
	Solver() : cnf(), n_clauses(0), n_vars(0), model(0){};
	Solver(cnf_t const &input) : cnf(input), n_clauses(input.size()), n_vars(count_vars()), model(n_vars){};
	Solver(cnf_t &&input) : cnf(input), n_clauses(input.size()), n_vars(count_vars()), model(n_vars){};

	template <typename... lits>
	requires all_literal<lits...>
	void add_clause(lits...);
	void add_clause(clause_t);
	void add_clause(clause_t &&);
	void add_clause(clause_t const &);

	void change_cnf(cnf_t);
	void change_cnf(cnf_t &&);
	void change_cnf(cnf_t const &);

	size_t count_vars();

protected:
	cnf_t cnf;
	size_t n_clauses;
	size_t n_vars;
	std::vector<literal> model; // for now, unassigned == 0

	virtual ~Solver() = 0;
	virtual bool solve() = 0;
	virtual bool check_satisfied() = 0;
	virtual bool check_conflict() = 0;
	virtual void clear() = 0;
};