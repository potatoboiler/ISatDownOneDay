#include "clause.hpp"

ClauseManager::ClauseManager(dimacs_cnf const &)
{
}

std::vector<size_t> ClauseAlloc::add_clauses(dimacs_cnf const &cnf)
{
    size_t total_size = cnf.size() * HEADER_LEN;
    for (auto const &cnf_clause : cnf)
    {
        total_size += cnf_clause.size();
    }
    this->buffer.reserve(total_size);

    std::vector<size_t> offsets;
    offsets.reserve(cnf.size());
    for (auto const &cnf_clause : cnf)
    {
        offsets.push_back(this->add_clause(cnf_clause));
    }
    return std::move(offsets);
}