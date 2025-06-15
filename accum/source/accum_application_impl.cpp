#include "accum_application_impl.h"

namespace PRJ_NAME {
application_impl::application_impl(application& _facade, const std::string& _name)
  : implement_t<application>(_facade)
  , m_name(_name)
{
    window_properties props{ name(), 1200, 800 };
    main_window() = window::create_window(props);
}

application_impl::~application_impl() {}

void
application_impl::run()
{
    running() = true;
    while (running()) {
        main_window()->on_update();
    }
}
}