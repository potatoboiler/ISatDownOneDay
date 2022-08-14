#include <algorithm>
#include <cmath>
#include <cassert>

#include "SitDown-v1.hpp"

/* solver implementation */
auto SitDown::solve() -> bool
{
    this->dec_levels.push_back(this->assigned_trail.size());
    if (assign_pure_literals())
    {
        backtrack();
        return false;
    }
    if (unit_propagate())
    {
        backtrack();
        return false;
    }

    if (check_satisfied())
    {
        return true;
    }
    for (size_t i = 0; i < this->model.size(); i++)
    {
        if (!this->model[i])
        {
            assign_literal(i, 1);
            if (solve())
                return true;
            assign_literal(i, -1);
            if (solve())
                return true;
        }
    }
    return false; // if we manage to get down here without a satisfying assignment, then this is a bad branch
}

auto SitDown::check_conflict() -> bool
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

auto SitDown::unit_propagate() -> bool
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
                assign_literal(unit_literal);
                // this->model[std::abs(unit_literal)] = std::signbit(unit_literal) ? -1 : 1; // can be microoptimized?
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

auto SitDown::assign_pure_literals() -> bool
{
    std::vector<int> signs(this->cnf.size());
    std::vector<bool> modify_mask(this->cnf.size(), true);
    for (auto const &clause : this->cnf)
    {
        for (literal l : clause)
        {
            const int sign = std::signbit(l) ? -1 : 1;
            const literal idx = std::abs(l);
            if (!signs[idx])
            {
                signs[idx] = sign;
            }
            else if (signs[idx] != sign)
            {
                modify_mask[idx] = false;
            }
        }
    }
    // guaranteed positive
    for (size_t i = 0; i < this->model.size(); i++)
    {
        /*
        if (this->model[i] != 0)
        {
            modify_mask[i] = false;
        }
        */
        modify_mask[i] = !(bool)this->model[i];
    }
    for (size_t i = 0; i < modify_mask.size(); i++)
    {
        this->model[i] = signs[i] ? -1 : 1;
    }
    return check_conflict();
}

// to be called from within a loop with clauses with potential parity issue
auto SitDown::assign_literal(literal l) -> void
{
    const literal idx = std::abs(l);
    this->model[idx] = std::signbit(l) ? -1 : 1;
    this->assigned_trail.push_back(idx);
}
auto SitDown::assign_literal(literal l, int val) -> void
{
    assert(val == -1 || val == 1);
    this->model[l] = val;
    this->assigned_trail.push_back(l);
}

auto SitDown::backtrack() -> void
{
    const size_t last = this->dec_levels.back();
    this->dec_levels.pop_back();
    while (this->assigned_trail.size() > last)
    {
        const literal l = this->assigned_trail.back();
        this->model[l] = 0;
        this->assigned_trail.pop_back();
    }
}

auto SitDown::analyze() -> void
{
    // size(trail) <= size(seen)
    // size(seen) == num(vars)
    /*
    inputs:
     - confl 
     - pathC
     - p = ???? a literal that determines whether we start from clause's 0th or 1st literal

    while (pathCounter > 0) {
        get conflicted clause

        for lit in clause {
            if (lit not seen && lit dec level > 0) {
                this lit has been seen;
                if lit's assignment level >= current decision level {
                    pathC++;
                } else {
                    put this lit in the learned clause
                }
            }
        }

        // select next clause
        while (traverse trail backwards until we find another SEEN variable)
        p is set to this seen variable
        conflicted clause <-- the clause that caused the assignment of p
        the variable behind p is no longer seen
        pathC--
    }
    learned clause[0] = ~p // negation?
    */
}