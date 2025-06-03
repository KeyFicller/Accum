#include "basic_guard.h"

#include <iostream>

int main()
{
    int a = 0;
    std::cout << a << std::endl;

    {
        VALUE_REVERTER(a, 2);
        std::cout << a << std::endl;
    }

    std::cout << a << std::endl;
}