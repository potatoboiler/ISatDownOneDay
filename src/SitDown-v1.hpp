#include <vector>

#include "base/solver.hpp"

class SitDown : virtual Solver
{
public:
    bool solve();

private:
    bool check_conflict();
	bool unit_propagate();
    bool assign_pure_literals();
    void prune_clauses();
    void restore_clauses();
    void assign_literal(literal l);

    std::vector<literal> assigned_trail;
    std::vector<size_t> dec_levels;
};
