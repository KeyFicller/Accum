#pragma once

#include "accum_export.h"

#include "basic_include.h"

namespace PRJ_NAME {

class application_impl;
class ACCUM_EXPORT application
{
    IMPL_BASE(application);

  public:
    application(const std::string& _name);
    virtual ~application();

  public:
    void run();
};
}