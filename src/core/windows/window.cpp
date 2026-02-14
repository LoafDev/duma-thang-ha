#include <core/windows/window.hpp>

#include <iostream>
#include <vulkan/vulkan_core.h>

namespace niqqa
{
namespace core
{
bool Window::should_close() noexcept
{
    return glfwWindowShouldClose(m_window);
}

bool Window::create_surface(VkInstance instance, VkSurfaceKHR &surface) noexcept
{

    if (!glfwCreateWindowSurface(instance, m_window, nullptr, &surface))
    {
        std::cerr << "Failed to create window surface\n";

        return false;
    }

    return true;
}

void Window::poll_events() noexcept
{
    glfwPollEvents();
}

void Window::cleanup() noexcept
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }
}

bool Window::init(uint32_t width, uint32_t height, const std::string &title, bool resizable, bool fullscreen) noexcept
{
    if (!glfwInit())
    {
        const char *desc = nullptr;
        glfwGetError(&desc);

        std::cerr << "Failed to initialize GLFW: " << (desc ? desc : "unknown") << "\n";
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, m_resizable);

    m_window = glfwCreateWindow(static_cast<int>(m_extent.width),
                                static_cast<int>(m_extent.height),
                                m_title.c_str(),
                                nullptr, 
                                nullptr);

    if (!m_window)
    {
        const char *desc = nullptr;
        glfwGetError(&desc);

        std::cerr << "Failed to create GLFW window: " << (desc ? desc : "unknown") << "\n";
        return false;
    }

    return true;
}
} // namespace core
} // namespace niqqa