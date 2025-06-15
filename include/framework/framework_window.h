#pragma once

#include "framework_event.h"
#include "framework_export.h"

#include "basic_include.h"

namespace PRJ_NAME {
class window_impl;

struct window_properties
{
    std::string title;
    unsigned int width = 1200;
    unsigned int height = 800;
};

class FMW_EXPORT window
{
    IMPL_BASE(window);
    DISABLE_COPY(window);

  public:
    static shared<window> create_window(const window_properties& _props);
    virtual ~window();

  protected:
    window(const window_properties& _props);

  public:
    void on_update();
};
}