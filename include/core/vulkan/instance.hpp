#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace niqqa
{
namespace core
{
class Instance
{
public:
    bool init() noexcept;
    void cleanup() noexcept;

private:
    VkInstance m_instance{VK_NULL_HANDLE};

    std::vector<const char *> get_required_extensions();
}; 
} // namespace core
} // namespace niqqa