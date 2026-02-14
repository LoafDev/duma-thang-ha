#pragma once

#include <graphics/device.hpp>
#include <core/windows/window.hpp>
#include <vulkan/vulkan.h>
#include <array>

namespace niqqa
{
namespace systems
{
class Engine
{
public:
#ifdef NDEBUG
    static constexpr bool enable_validation_layers = false;
#else 
    static constexpr bool enable_validation_layers = true;
#endif

    static constexpr std::array<const char *, 1> validation_layers = {
        "VK_LAYER_KHRONOS_validation"
    };

    bool init(uint32_t width, 
              uint32_t height, 
              const std::string &title, 
              bool resizable = true, 
              bool fullscreen = false
              ) noexcept;

private:
    core::Window m_window;
    graphics::Device m_device;
};
} // namespace systems
} // namespace niqqa