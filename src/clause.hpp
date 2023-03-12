#include <cassert>

#include "types.hpp"

// VariSAT header items
enum HEADER_NAMES
{
    activity,
    mark,
    deleted,
    length,
    HEADER_LEN,
};

struct Clause
{
    // ClauseHeader header;
    literal header[HEADER_LEN];
    // Because C++ doesn't bounds check, we abuse casting to let this act as a "flexible array member"
    literal data[1];

    Clause() = delete;
};

class ClauseDatabase
{
    std::vector<clause_ref> clause_indices;
};

class ClauseAlloc
{
public:
    inline auto get_clause(size_t i) -> clause_t &;
    // ClauseAlloc(std::vector<clause_t> clauses);
    void set_clauses(dimacs_cnf &&cnf);
    void add_clauses(dimacs_cnf &&cnf);
    void add_clause(std::vector<literal> &&cnf);

private:
    std::vector<literal> buffer; // split clauses to keep them under a certain size?
};