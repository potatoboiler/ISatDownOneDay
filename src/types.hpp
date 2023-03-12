#pragma once

#include <cstdint>
#include <vector>
#include <functional>

struct Clause;
struct ClauseAlloc;

using std::size_t;
using literal = int32_t; // label for a variable, may split later into an individual literal type

using vector_clause = std::vector<literal>;
using dimacs_clause = std::vector<literal>;
using dimacs_cnf = std::vector<dimacs_clause>;

using clause_t = literal *;
using clause_ref = std::reference_wrapper<Clause>;