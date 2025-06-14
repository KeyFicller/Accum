#include "basic_prompts.h"

#include <map>

namespace PRJ_NAME {
static std::map<prompt_id, std::string> prompt_strs = { { prompt_id::k_undefined_print_behavior,
                                                          "Undefined print behavior" } };

BASIC_EXPORT std::string
prompt(const prompt_id& _id)
{
    return prompt_strs.at(_id);
}
}