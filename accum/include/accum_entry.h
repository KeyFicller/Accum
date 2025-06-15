#pragma once

#include "accum_application.h"

namespace PRJ_NAME {
extern application*
create_application();
}

extern "C" int
main(int _argc, char** _argv)
{
    INFO("Application start running.");
    PRJ_NAME::application* app = PRJ_NAME::create_application();
    app->run();
    delete app;

    INFO("Application stopped running.");
}