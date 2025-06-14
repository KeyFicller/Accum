#pragma once

#include "basic_filer.h"

#include <vector>

namespace PRJ_NAME {
class filer_impl : public implement_t<filer>
{
    MEMBER_DECLARE(filer_impl, std::vector<char>, data);
    MEMBER_DECLARE(filer_impl, size_t, index);
    MEMBER_DECLARE(filer_impl, size_t, last_index);
    friend class filer;

  public:
    filer_impl(filer& _facade);
    ~filer_impl() = default;

  public:
    filer& write_bytes(const void* _value, int _bytes);
    filer& read_bytes(void* _value, int _bytes);

    void flush_in(filer& _other, int _bytes);
    void flush_out(filer& _other, int _bytes);
    bool seek(int _position);
    int position() const;
    filer& clear();

  private:
    void* ptr();
};
}