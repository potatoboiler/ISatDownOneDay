#include <algorithm>
#include <cmath>

#include "SitDown-v1.hpp"

/* solver implementation */
bool SitDown::solve()
{
    return false;
}

bool SitDown::check_conflict()
{
    for (clause_t const &clause : this->cnf)
    {
        if (std::all_of(clause.cbegin(), clause.cend(), [this](literal l)
                        { return this->model[std::abs(l)] * l == -1; }))
        {
            return true;
        }
    }
    return false;
}

bool SitDown::unit_propagate()
{
    // std::vector<literal> assigned; // possibly unnecessary
    const static auto test_unit = [this](literal l)
    { return this->model[l] == 0; };
    bool propagated;
    do
    {
        propagated = false;
        for (clause_t const &clause : this->cnf)
        {
            if (std::count_if(clause.cbegin(), clause.cend(), test_unit) == 1 && std::count_if(clause.cbegin(), clause.cend(), [this](literal l)
                                                                                               { return this->model[std::abs(l)] * l == -1; }) == clause.size() - 1)
            {
                const literal unit_literal = *std::find_if(clause.cbegin(), clause.cend(), test_unit);
                this->model[std::abs(unit_literal)] = std::signbit(unit_literal) ? -1 : 1; // can be microoptimized?
                // assigned.push_back(std::abs(unit_literal));
                propagated = true;
            }
        }
    } while (propagated);
    /*
    if (check_conflict())
    {
        for (literal l : assigned)
        {
            this->model[std::abs(l)] = 0;
        }
        return true;
    }
    else
    {
        return false;
    }
    */
    return check_conflict();
}

/* graph implementation */