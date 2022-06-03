#include <immintrin.h>
#include <vector>

template <std::integral T>
struct clause_t
{
    std::vector<T> signs;
    std::vector<T> truth_values;
    std::vector<T> assigned;
};

template <std::integral T>
bool check_satisfied(clause<T> const &c)
{
}

template <std::integral T>
struct cnf_t
{
};