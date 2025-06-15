#pragma once

#include "framework_window.h"

#include "glad/glad.h"

#include "GLFW/glfw3.h"

namespace PRJ_NAME {
class event;

struct window_user_data
{
    window_properties props;
    bool v_sync = false;
    callback_t<void, event&> cb_event;
};

class window_impl : public implement_t<window>
{
    friend class window;
    MEMBER_DECLARE(window_impl, window_user_data, user_data);

  public:
    window_impl(window& _facade, const window_properties& _props);
    ~window_impl() override;

  public:
    unsigned int height() const;
    unsigned int width() const;
    bool is_v_sync() const;
    window_impl& set_v_sync(bool _enable = true);
    void on_update();

  private:
    void initialize();
    void shutdown();

  protected:
    GLFWwindow* m_window = nullptr;
};
}