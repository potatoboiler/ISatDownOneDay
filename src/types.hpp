#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <functional>
#include <limits>
#include <vector>

struct Clause;
struct ClauseAlloc;

using std::size_t;
using literal = int32_t; // label for a variable, may split later into an individual literal type

typedef struct literal_struct
{
    literal val;

    literal get_index()
    {
        return this->val >> 1;
    }
    literal get_sign()
    {
        return this->val & 1;
    }

    literal_struct(uint32_t value, int sign)
    {
        assert(value < std::numeric_limits<literal>::max());
        this->val = (value << 1) + (sign & 1);
    }
    literal_struct(literal value)
    {
        assert(value < std::numeric_limits<literal>::max());
        literal sign = std::signbit(value);
        literal index = std::abs(value);
        this->val = (index << 1) + (sign & 1);
    }
} literal_struct;

using vector_clause = std::vector<literal>;
using dimacs_clause = std::vector<literal>;
using dimacs_cnf = std::vector<dimacs_clause>;

using clause_t = literal *;
using clause_ref = std::reference_wrapper<Clause>;