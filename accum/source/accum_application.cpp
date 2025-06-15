#include "accum_application.h"
#include "accum_application_impl.h"

namespace PRJ_NAME {
application::application(const std::string& _name)
{
    IMPL_INITIALIZE(application, _name);
}
application::~application()
{
    IMPL_TERMINATE();
}

void
application::run()
{
    IMPL(application)->run();
}
}