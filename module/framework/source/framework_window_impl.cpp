#include "framework_window_impl.h"

#include "GLFW/glfw3native.h"

namespace PRJ_NAME {
namespace {
int g_window_count = 0;

void
glfw_error_callback(int _error, const char* _desc)
{
    ASSERT(false, "GLFW error ([0]): [1]", _error, _desc);
}
}

window_impl::window_impl(window& _facade, const window_properties& _props)
  : implement_t<window>(_facade)
{
    user_data().props = _props;
    initialize();
}
window_impl::~window_impl()
{
    shutdown();
}

unsigned int
window_impl::height() const
{
    return user_data().props.height;
}
unsigned int
window_impl::width() const
{
    return user_data().props.width;
}

bool
window_impl::is_v_sync() const
{
    return user_data().v_sync;
}
window_impl&
window_impl::set_v_sync(bool _enable)
{
    user_data().v_sync = _enable;
    glfwSwapInterval(user_data().v_sync ? 1 : 0);
    return *this;
}

void
window_impl::on_update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void
window_impl::initialize()
{
    INFO("Create window [0] ([1], [2]).", user_data().props.title, user_data().props.width, user_data().props.height);

    if (g_window_count == 0) {
        ASSERT(glfwInit(), "Glfw initialize failed.");
        glfwSetErrorCallback(glfw_error_callback);
    }

    m_window = glfwCreateWindow(
      user_data().props.width, user_data().props.height, user_data().props.title.c_str(), nullptr, nullptr);
    g_window_count++;

    glfwMakeContextCurrent(m_window);
    int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    ASSERT(status, "Initialize glad failed.");

    INFO("OpenGL Vendor: [0].", (char*)glGetString(GL_VENDOR));
    INFO("OpenGL Renderer: [0].", (char*)glGetString(GL_RENDERER));
    INFO("OpenGL Version: [0].", (char*)glGetString(GL_VERSION));

    glfwSetWindowUserPointer(m_window, &m_user_data);

    // add event callbacks...
}

void
window_impl::shutdown()
{
    glfwDestroyWindow(m_window);
    if (--g_window_count == 0) {
        glfwTerminate();
    }
}
}