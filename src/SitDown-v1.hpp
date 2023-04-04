#pragma once

#include <cassert>
#include <cstdint>
#include <vector>
#include <optional>

#include "types.hpp"
#include "clause.hpp"

template <typename... Ts>
concept all_literal = std::same_as<literal, std::common_type<Ts...>>;

// Structured after VariSAT
class VariableAssignments
{
    std::vector<std::optional<bool>> variables;
    std::vector<bool> last_values;

public:
    std::size_t size() const { return variables.size(); }

    void assign(int n, bool value)
    {
        assert(0 <= n && (unsigned)n < variables.size());
        variables[n] = value;
    }

    void resize(int n)
    {
        variables.resize(n);
        last_values.resize(n);
        assert(variables.size() == last_values.size());
    }
};

class SitDown
{
public:
    bool solve();
    SitDown();
    SitDown(dimacs_cnf const &);

private:
    auto unit_propagate() -> bool;
    auto assign_pure_literals() -> bool;

    auto prune_clauses() -> void;
    auto restore_clauses() -> void;

    auto analyze() -> clause_t;
    auto backtrack() -> void;
    auto check_conflict() -> bool;
    auto check_satisfied() -> bool;

    // std::vector<literal> reasons;

protected:
    ClauseManager clauses;
};
