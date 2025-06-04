#include "basic_log.h"

#include <iostream>

using namespace PRJ_NAME;

int main()
{
    PRJ_NAME::log::instance().trace("hello");
    PRJ_NAME::log::instance().warn("world");
    PRJ_NAME::log::instance().trace("%d%d", 2, 3);
    while (true);
}