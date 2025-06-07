#include "tests.h"

using namespace PRJ_NAME;

int main(int _argc, char** _argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&_argc, _argv);

    vec2_i test(1, 2);
    vec3_i test1;
    vec4_i test2;

    return RUN_ALL_TESTS();
}