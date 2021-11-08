#pragma once
#include <vector>

#include "../DIMACS.hpp"

using literal = int;
using clause = std::vector<literal>;
using cnf_t = std::vector<clause>;

template<typename ... Ts>
concept all_literal = std::same_as<literal, std::common_type<Ts...>>;


class Solver {
	// remember to inherit virtually from this class
	public:
		Solver() : cnf(), n_vars(0), n_clauses(0), model(n_vars) {};
		Solver(cnf_t const & input) : cnf(input), n_clauses(input.size()), n_vars(count_vars()), model(n_vars) {};
		Solver(cnf_t&& input) : cnf(input), n_clauses(input.size()), n_vars(count_vars()), model(n_vars) {};

		virtual bool solve() = 0;

		template<typename ... lits> requires all_literal<lits...>
		void add_clause(lits ...);
		void add_clause(clause);
		void add_clause(clause&&);
		void add_clause(clause const &);
		
		void change_cnf(cnf_t);
		void change_cnf(cnf_t&&);
		void change_cnf(cnf_t const &);

		//
		bool unit_propagate();

		size_t count_vars();

	protected:
		cnf_t cnf;
		std::vector<literal> model;
		size_t n_vars;
		size_t n_clauses;
};