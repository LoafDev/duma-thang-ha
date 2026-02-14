#pragma once

#include <core/vulkan/instance.hpp>
#include <systems/engine.hpp>

namespace niqqa
{
namespace app
{
class Test1
{
public:
    bool init(uint32_t width, uint32_t height, const std::string &title, bool resizable = true, bool fullscreen = false) noexcept;

    void run() noexcept;

private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    VkSurfaceKHR surface{VK_NULL_HANDLE};
    core::Instance m_instance;
};
} // namespace app
} // namspace niqqa