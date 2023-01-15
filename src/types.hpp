#pragma once

#include <cstdint>
#include <vector>

using std::size_t;
using literal = int32_t; // label for a variable, may split later into an individual literal type
using clause_t = int32_t *;
using dimacs_cnf = std::vector<std::vector<literal>>;