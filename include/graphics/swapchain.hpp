#pragma once

#include <graphics/image.hpp>

#include <vector>
#include <vulkan/vulkan_core.h>

namespace niqqa
{
namespace graphics
{
struct SwapchainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

SwapchainSupportDetails query_swapchain_support(VkPhysicalDevice device, VkSurfaceKHR surface) noexcept;

class SwapChain
{
public:
    bool create(VkPhysicalDevice gpu,
                VkDevice device, 
                VkSurfaceKHR surface, 
                VkExtent2D extent,
                VkFormat user_defined_format,
                VkPresentModeKHR user_defined_present_mode) noexcept;
    
    void cleanup() noexcept;

private:
    VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
    VkDevice m_device{VK_NULL_HANDLE};
    VkSurfaceKHR m_surface{VK_NULL_HANDLE};
    VkFormat m_present_format;
    VkPresentModeKHR m_present_mode;

    std::vector<Image> m_present_images;

    VkSurfaceFormatKHR choose_swapchain_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats, VkFormat desired_format) noexcept;
    VkPresentModeKHR choose_swapchain_present_mode(const std::vector<VkPresentModeKHR> &available_modes, VkPresentModeKHR desired_mode) noexcept;
    VkExtent2D choose_swapchain_extent(VkSurfaceCapabilitiesKHR capabilities, VkExtent2D actual_extent) noexcept;

    bool create_image_views() noexcept;
};
} // namespace graphics
} // namespace niqqa