#include <graphics/swapchain.hpp>
#include <graphics/device.hpp>

#include <cstdint>
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace niqqa
{
namespace graphics
{
SwapchainSupportDetails query_swapchain_support(VkPhysicalDevice device, VkSurfaceKHR surface) noexcept
{
    SwapchainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);
    
    if (format_count != 0)
    {
        details.formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
    }

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

    if (present_mode_count != 0)
    {
        details.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.present_modes.data());
    }

    return details;
}

bool SwapChain::create(VkPhysicalDevice gpu,
                VkDevice device, 
                VkSurfaceKHR surface,
                VkExtent2D actual_extent,
                VkFormat user_defined_format,
                VkPresentModeKHR user_defined_present_mode) noexcept
{
    m_device = device;
    m_surface = surface;

    SwapchainSupportDetails swap_chain_support = query_swapchain_support(gpu, m_surface);
    QueueFamilyIndices indices = find_queue_families(gpu, m_surface);
    uint32_t queue_family_indices[] = {
        indices.graphics_family.value(),
        indices.present_family.value()
    };

    VkSurfaceFormatKHR surface_format = choose_swapchain_surface_format(swap_chain_support.formats, user_defined_format);
    VkPresentModeKHR present_mode = choose_swapchain_present_mode(swap_chain_support.present_modes, user_defined_present_mode);
    VkExtent2D extent = choose_swapchain_extent(swap_chain_support.capabilities, actual_extent);
    
    uint32_t image_count;
    image_count = swap_chain_support.capabilities.minImageCount + 1;

    if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount)
    {
        image_count = swap_chain_support.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = m_surface;
    create_info.minImageCount = image_count;
    create_info.imageFormat = surface_format.format;
    create_info.imageColorSpace = surface_format.colorSpace;
    create_info.imageExtent = actual_extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    if (indices.graphics_family != indices.present_family)
    {
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices = queue_family_indices;
    }
    else
    {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        create_info.queueFamilyIndexCount = 0;
        create_info.pQueueFamilyIndices = nullptr;
    }

    create_info.preTransform = swap_chain_support.capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = present_mode;
    create_info.clipped = VK_TRUE;
    create_info.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(m_device, &create_info, nullptr, &m_swapchain) != VK_SUCCESS)
    {
        std::cerr << "Failed to create swap chain\n";
        return false;
    }

    std::vector<VkImage> images;
    images.resize(image_count);

    if (vkGetSwapchainImagesKHR(m_device, m_swapchain, &image_count, images.data()) != VK_SUCCESS)
    {
        std::cerr << "Failed to get swap chain images\n";
        return false;
    }

    m_present_images.resize(image_count);

    for (size_t i = 0; i < m_present_images.size(); ++i)
    {
        m_present_images[i].image = images[i];
    }

    create_image_views();

    return true;
}

void SwapChain::cleanup() noexcept
{
    for (size_t i = 0; i < m_present_images.size(); ++i)
    {
        if (m_present_images[i].image_view != VK_NULL_HANDLE)
        {
            vkDestroyImageView(m_device, m_present_images[i].image_view, nullptr);
        }
    }

    if (m_swapchain != VK_NULL_HANDLE)
    {
        vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
    }
}

VkSurfaceFormatKHR SwapChain::choose_swapchain_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats, VkFormat desired_format) noexcept
{
    for (const auto &available_format : available_formats)
    {
        if (available_format.format == desired_format)
        {
            return available_format;
        }
    }

    return available_formats[0];
}

VkPresentModeKHR SwapChain::choose_swapchain_present_mode(const std::vector<VkPresentModeKHR> &available_modes, VkPresentModeKHR desired_mode) noexcept
{
    for (const auto &avaiable_mode : available_modes)
    {
        if (avaiable_mode == desired_mode)
        {
            return avaiable_mode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::choose_swapchain_extent(VkSurfaceCapabilitiesKHR capabilities, VkExtent2D actual_extent) noexcept
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }

    actual_extent.width = std::clamp(actual_extent.width,
                                     capabilities.minImageExtent.width,
                                     capabilities.maxImageExtent.width);
    
    actual_extent.height = std::clamp(actual_extent.height, 
                                      capabilities.minImageExtent.height,
                                      capabilities.maxImageExtent.height);

    return actual_extent;
}

bool SwapChain::create_image_views() noexcept
{
    for (size_t i = 0; i < m_present_images.size(); ++i)
    {
        VkImageViewCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        create_info.image = m_present_images[i].image;
        create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        create_info.format = m_present_format;
        create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        create_info.subresourceRange.baseMipLevel = 0;
        create_info.subresourceRange.levelCount = 1;
        create_info.subresourceRange.baseArrayLayer = 0;
        create_info.subresourceRange.layerCount = 1;

        if (vkCreateImageView(m_device, &create_info, nullptr, &m_present_images[i].image_view) != VK_SUCCESS)
        {
            std::cerr << "Failed to create image view\n";

            for (size_t j = 0; j < i; ++j)
            {
                vkDestroyImageView(m_device, m_present_images[i].image_view, nullptr);
            }

            return false;
        }
    }

    return true; 
}
} // namespace graphics
} // namespace niqqa