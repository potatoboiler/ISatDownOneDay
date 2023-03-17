#include <algorithm>
#include <cmath>
#include <cassert>

#include "SitDown-v1.hpp"

SitDown::SitDown()
{
}

SitDown::SitDown(dimacs_cnf const &cnf) : clauses{}
{
    std::vector<size_t> offsets = clauses.add_clauses(cnf);
}