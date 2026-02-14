#pragma once

#include <vulkan/vulkan.h>

#include <cstdint>
#include <optional>
#include <vector>
#include <string>
#include <array>

namespace niqqa
{
namespace graphics
{
struct QueueFamilyIndices
{
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool is_complete() const noexcept;
};

QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface) noexcept;

class Device
{
public:
    bool init(VkInstance instance, VkSurfaceKHR surface) noexcept;
    void cleanup() noexcept;

private:
    VkInstance m_instance{VK_NULL_HANDLE};
    VkDevice m_device{VK_NULL_HANDLE};
    VkPhysicalDevice m_gpu{VK_NULL_HANDLE};
    VkQueue m_graphics_queue{VK_NULL_HANDLE};
    VkQueue m_present_queue{VK_NULL_HANDLE};

    VkPhysicalDeviceProperties m_properties;
    VkPhysicalDeviceFeatures m_features;

    const std::vector<const char *> m_validation_layers = {
        "VK_LAYER_KHRONOS_validation"
    };

    static constexpr std::array<const char *, 1> REQUIRED_EXTS = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    static constexpr std::array<const char *, 2> OPTIONAL_EXTS = {
        VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
        VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
    };

    static constexpr std::array<const char *, 3> RT_EXTS = {
        VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
        VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
        VK_KHR_RAY_QUERY_EXTENSION_NAME
    };

#ifdef NDEBUG
    static constexpr bool enable_validation_layers = false;
#else 
    static constexpr bool enable_validation_layers = true;
#endif

    bool pick_physical_device(VkSurfaceKHR surface) noexcept;
    bool create_logical_device(VkSurfaceKHR surface) noexcept;

    int32_t rate_device_suitability(VkPhysicalDevice device, VkSurfaceKHR surface) noexcept;

    bool check_device_extension_support(VkPhysicalDevice device, const std::vector<const char *> &extensions) noexcept;
    bool is_device_extension_supported(const std::string &extension_name) noexcept;
};
} // namespace graphics
} // namespace niqqa