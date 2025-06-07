#pragma once

#include "basic_export.h"

#include <string>

namespace PRJ_NAME
{
    enum class prompt_id
    {
        k_undefined_print_behavior = 0,
    };

    BASIC_EXPORT std::string prompt(const prompt_id& _id);
}