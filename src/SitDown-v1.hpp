#pragma once

#include <cassert>
#include <cstdint>
#include <vector>
#include <optional>

using std::size_t;
using literal = int32_t; // label for a variable, may split later into an individual literal type
using clause_t = int32_t *;

template <typename... Ts>
concept all_literal = std::same_as<literal, std::common_type<Ts...>>;

// Structured after VariSAT
class VariableAssignments
{
    std::vector<std::optional<bool>> variables;
    std::vector<bool> last_values;

public:
    std::size_t size() const
    {
        return variables.size();
    }

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

struct ClauseHeader
{
};

class ClauseDatabase
{
};

class ClauseAlloc
{
public:
    inline auto get_clause(size_t i) -> clause_t &;
    // ClauseAlloc(std::vector<clause_t> clauses);

private:
    std::vector<int32_t> buffer; // split clauses to keep them under a certain size?
};

class SitDown
{
public:
    bool solve();

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
    ClauseAlloc clauses;
    ClauseDatabase db;

protected:
};
