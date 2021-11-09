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

class Node
{
public:
    Node(int n_vars);

private:
    literal label;
    // std::vector<literal> children;
    int clause_id = -1; // == -1 if decision var
};

class impl_graph
{
    // 1-UIP scheme as described here
    // https://www.cs.princeton.edu/courses/archive/fall13/cos402/readings/SAT_learning_clauses.pdf
    // https://users.aalto.fi/~tjunttil/2020-DP-AUT/notes-sat/cdcl.html
public:
    impl_graph();
    impl_graph(int n_vars);

    template <typename... lits>
    requires all_literal<lits...>
    void propagate_literals(lits...);
    void decide_literal();
    void assume_literals();
    void backtrack(int level);

    Node get_1UIP();
    Node CONFLICT{-1};

protected:
    unsigned int decision_level = 0;
    std::vector<Node> trail; // pair <literal label, clause number>
};