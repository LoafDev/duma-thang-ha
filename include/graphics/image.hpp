#pragma once

#include <vulkan/vulkan.h>

namespace niqqa
{
namespace graphics
{
struct Image 
{
    VkImage image{VK_NULL_HANDLE};
    VkImageView image_view{VK_NULL_HANDLE};
};
} // namespace graphics
} // namespace niqqa