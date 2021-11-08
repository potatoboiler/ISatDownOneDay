#include "base/solver.hpp"

// implement probSAT local search
// implement basic CDCL
// note that clause lists may need to be pointers to clauses to avoid extra copies...
class SitDown : virtual Solver
{
public:
    bool solve();

protected:
    bool local_search_when_complete();
    clause analyze();
    void simplify_learned();
    void restart();
    void backtrack();

    impl_graph g;
    std::vector<clause> learned_clauses;
};

class impl_graph
{
};