#include <vector>

#include "base/solver.hpp"

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

class SitDown : virtual Solver
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

    SitDown() = delete;

    // std::vector<literal> reasons;
    ClauseCollection clauses;
    std::vector<literal> assigned_trail;
    std::vector<size_t> dec_levels;
};
