#pragma once

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#include <vulkan/vulkan.h>

#include <string>
#include <cstdint>

namespace niqqa
{
namespace core
{
class Window
{
public:
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool init(uint32_t width, uint32_t height, const std::string &title, bool resizable = true, bool fullscreen = false) noexcept;
    bool should_close() noexcept;
    bool create_surface(VkInstance instance, VkSurfaceKHR &surface) noexcept;

    void poll_events() noexcept;
    void cleanup() noexcept;

private:
    GLFWwindow *m_window{nullptr};

    VkExtent2D m_extent;
    const std::string m_title;

    bool m_resized{false};
    bool m_resizable;
    bool m_fullscreen;
};
} // namespace core
} // namspace niqqa