//
// Created by adnan on 6/30/25.
//

#include "VulkSwapchain.h"

bool createSurface(VkInstance instance, GLFWwindow& window, VkSurfaceKHR& surface) {
    if (glfwCreateWindowSurface(instance,&window,nullptr,&surface)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Window Surface Creation Error"));
    }
    return true;
}

SwapChainInfo getSwapChainInfo(const VkPhysicalDevice& physical_device,const DisplayAdapter& display_adapter) {
    SwapChainInfo swapChainInfo = {};
    //*parsing surface capabilities from device
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device,display_adapter.surface,&swapChainInfo.surfaceCapabilities);
    //*parsing format from device
    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device,display_adapter.surface,&formatCount,nullptr);
    swapChainInfo.surfaceFormats.resize(formatCount);
    if (formatCount<1) throw std::runtime_error(VULK_RUNTIME_ERROR("Cound not detect surface format"));
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device,display_adapter.surface,&formatCount,swapChainInfo.surfaceFormats.data());
    //* parsing presentation modes from device
    uint32_t presentationModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device,display_adapter.surface,&presentationModeCount,nullptr);
    if (presentationModeCount<1) throw std::runtime_error(VULK_RUNTIME_ERROR("Cound not detect presentation modes"));
    swapChainInfo.presentModes.resize(presentationModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device,display_adapter.surface,&presentationModeCount,swapChainInfo.presentModes.data());
    return swapChainInfo;
}


VkSurfaceFormatKHR pickSuitableSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats) {
    if (formats.empty())throw std::runtime_error(VULK_RUNTIME_ERROR("Could Not Pick From Empty Surface Formats"));
    //? Trying to check if VK_FORMAT_R8G8B8A8_UNORM is available.if it is then return it else return first one
    for (const auto& format : formats) {
        if ((format.format==VK_FORMAT_R8G8B8A8_UNORM || format.format==VK_FORMAT_B8G8R8A8_UNORM) && format.colorSpace==VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
            return format;
        }
    }
    std::cerr<<VULK_NOT_FOUND_ERROR("Unable To Pick: format(VK_FORMAT_R8G8B8A8_UNORM) or format(VK_FORMAT_B8G8R8A8_UNORM) and colorSpace(VK_COLORSPACE_SRGB_NONLINEAR_KHR). Fallback To default one")<<"\n";
    return formats[0];
}
VkPresentModeKHR pickSuitablePresentMode(const std::vector<VkPresentModeKHR> &presentationModes){
    if (presentationModes.empty()) throw std::runtime_error(VULK_RUNTIME_ERROR("Could Not Pick From Empty Presentation Modes"));
    for (const auto &presentationMode:presentationModes) {
        if (presentationMode==VK_PRESENT_MODE_MAILBOX_KHR) {
            return presentationMode;
        }
    }
    std::cerr<<"FALL BACK PRESENT MODE VK_PRESENT_MODE_FIFO_KHR\n  ";
    // vulkan guaranteed that `VK_PRESENT_MODE_FIFO_KHR` is present
    return  VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D pickSuitableExtent(const VkSurfaceCapabilitiesKHR &capabilities) {
    const auto currentExtent = capabilities.currentExtent;
    if (currentExtent.width<=0 ||
        currentExtent.height<=0 ||
        currentExtent.width>=std::numeric_limits<uint32_t>::max() ||
        currentExtent.height>=std::numeric_limits<uint32_t>::max()
        ) throw std::runtime_error(VULK_RUNTIME_ERROR("Invalid Extent. Fallback Failed"));
    return currentExtent;
}