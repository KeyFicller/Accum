#include "framework_window.h"

#include "framework_window_impl.h"

namespace PRJ_NAME {
shared<window>
window::create_window(const window_properties& _props)
{
    return shared<window>(new window(_props));
}

window::~window()
{
    IMPL_TERMINATE();
}

window::window(const window_properties& _props)
{
    IMPL_INITIALIZE(window, _props);
}

void
window::on_update()
{
    IMPL(window)->on_update();
}
}