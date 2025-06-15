#pragma once

#include "accum_application.h"

#include "framework_window.h"

namespace PRJ_NAME {
class application_impl : public implement_t<application>
{
    MEMBER_DECLARE(application_impl, std::string, name);
    MEMBER_DECLARE(application_impl, shared<window>, main_window);
    MEMBER_DECLARE(application_impl, bool, running);
    IMPL_EXPOSE(application);
    friend class application;

  public:
    application_impl(application& _facade, const std::string& _name);
    ~application_impl() override;

  public:
    void run();
};
}