#pragma once

#include <vulkan/vulkan.h>

namespace niqqa
{
namespace systems
{
class BaseRenderer
{
public:
    bool init(VkDevice device) noexcept;

private:
    VkDevice m_device{VK_NULL_HANDLE};
};
} // namespace systems
} // namespace niqqa