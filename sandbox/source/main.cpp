#pragma once

#include "accum_entry.h"

class sandbox : public PRJ_NAME::application
{
  public:
    sandbox(const std::string& _name)
      : PRJ_NAME::application(_name)
    {
    }

    ~sandbox() override = default;
};

PRJ_NAME::application*
PRJ_NAME::create_application()
{
    return new sandbox("Sandbox");
}