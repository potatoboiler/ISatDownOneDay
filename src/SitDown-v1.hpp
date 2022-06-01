#include <vector>

#include "base/solver.hpp"

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
    auto backtrack() -> void;
    auto check_conflict() -> bool;

    std::vector<literal> assigned_trail;
    std::vector<size_t> dec_levels;
};
