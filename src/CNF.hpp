#include <concepts>
#include <vector>

#include "DIMACS.hpp"

template <std::convertible_to<bool> B, std::unsigned_integral T>
struct literal_t
{
    B polarity;
    T index;
};

template <std::convertible_to<bool> B, std::unsigned_integral T>
struct clause_t
{
    std::vector<literal_t<B, T>> literals;
};

template <std::convertible_to<bool> B, std::unsigned_integral T>
struct cnf_t
{
    std::vector<clause_t<B,T>> clauses;
};

template <>
struct literal_t<bool, size_t>;
struct clause_t<bool, size_t>;
struct cnf_t<bool, size_t>;

