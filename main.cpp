#include "tests/test1.hpp"

#include <cstdlib>

int main()
{
    niqqa::app::Test1 test;

    if (!test.init(800, 600, "Test 1"))
    {
        return EXIT_FAILURE;
    }

    test.run();
    
    return EXIT_SUCCESS;
}