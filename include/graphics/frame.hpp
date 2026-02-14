#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace niqqa
{
namespace graphics
{
struct Frame 
{
    VkSemaphore present_semaphore{VK_NULL_HANDLE};
    VkSemaphore render_semaphore{VK_NULL_HANDLE};
    VkFence render_fence{VK_NULL_HANDLE};
};
} // namespace graphics
} // namespace niqqa