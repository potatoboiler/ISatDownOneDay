#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../src/SitDown-v1.hpp"
#include "../src/DIMACS.hpp"
#include <cassert>

TEST_CASE("Construction")
{
    REQUIRE_NOTHROW(SitDown{});
}

namespace bump_allocator_tests
{
    bool validate_clause_conversion(vector_clause from, bump_allocator::Clause &to)
    {
        for (size_t i = 0; i < from.size(); i++)
        {
            REQUIRE(from[i] == to.data[i]);
        }
        return true; // TODO: replace
    }

    bool validate_dimacs_conversion(dimacs_clause from, bump_allocator::Clause &to)
    {
        for (size_t i = 0; i < from.size(); i++)
        {
            REQUIRE(from[i] == to.data[i] + 1);
        }
        return true; // TODO: replace
    }

    TEST_CASE("DIMACS parse test")
    {
        dimacs_cnf expected = {{1, 2, 3}, {2, 3, 4}, {-1, -2, -3}, {-2, -3}};
        dimacs_cnf actual = DIMACS("test_dimacs/dimacs_1.txt").get_cnf();

        REQUIRE(actual.size() == expected.size());
        for (size_t i = 0; i < expected.size(); i++)
        {
            REQUIRE(actual[i].size() == expected[i].size());
            for (size_t j = 0; j < expected[i].size(); j++)
            {
                REQUIRE(actual[i][j] == expected[i][j]);
            }
        }
    }
}