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

bool SitDown::assign_pure_literals()
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
       modify_mask[i] = !(bool) this->model[i];
    }
    for (size_t i = 0; i < modify_mask.size(); i++)
    {
        this->model[i] = signs[i] ? -1 : 1;
    }
    return check_conflict();
}

// to be called from within a loop with clauses with potential parity issue
void SitDown::assign_literal(literal l)
{
    const literal idx = std::abs(l);
    this->model[idx] = std::signbit(l) ? -1 : 1;
    this->assigned_trail.push_back(idx);
}
void SitDown::assign_literal(literal l, int val)
{
    assert(val == -1 || val == 1);
    this->model[l] = val;
    this->assigned_trail.push_back(l);
}

auto SitDown::backtrack() -> void {
    const size_t last = this->dec_levels.back();
    this->dec_levels.pop_back();
    while (this->assigned_trail.size() > last) {
        const literal l = this->assigned_trail.back();
        this->model[l] = 0;
        this->assigned_trail.pop_back();
    }
}