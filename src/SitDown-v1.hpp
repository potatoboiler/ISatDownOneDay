#pragma once

#include <cstdint>
#include <vector>

using std::size_t;
using literal = int32_t; // label for a variable, may split later into an individual literal type
using clause_t = std::vector<literal>;
using cnf_t = std::vector<clause_t>;

template <typename... Ts>
concept all_literal = std::same_as<literal, std::common_type<Ts...>>;

class ClauseCollection
{
public:
    inline auto get_clause(size_t i) -> clause_t & { return this->clauses[i]; }
    ClauseCollection(std::vector<clause_t> clauses);

private:
    std::vector<clause_t> clauses; // split clauses to keep them under a certain size?
    std::vector<size_t> reasons;
    std::vector<size_t> index_map; // in case we try to reorder, but probably not necessary for now
};

class SitDown
{
public:
    bool solve();

private:
    auto unit_propagate() -> bool;
    auto assign_pure_literals() -> bool;

    auto prune_clauses() -> void;
    auto restore_clauses() -> void;

    auto assign_literal(literal l) -> void;
    auto assign_literal(literal l, int val) -> void;

    auto analyze() -> clause_t;
    auto backtrack() -> void;
    auto check_conflict() -> bool;
    auto check_satisfied() -> bool;

    SitDown() = delete;

    // std::vector<literal> reasons;
    ClauseCollection clauses;
    std::vector<literal> assigned_trail;
    std::vector<size_t> dec_levels;

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
    std::vector<int8_t> model; // for now, unassigned == 0; can replace with 2 bitfield?
};
