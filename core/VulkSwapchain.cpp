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
    VkSurfaceFormatKHR surfaceFormat = formats[0];
    //? Trying to check if VK_FORMAT_R8G8B8A8_UNORM is available.if it is then return it else return first one
    for (const auto& format : formats) {
        if (format.format==VK_FORMAT_R8G8B8A8_UNORM  && format.colorSpace==VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
            VLOG("Selected SURFACE FORMAT ${} & ColorSpace: ${}",format.format==VK_FORMAT_R8G8B8A8_UNORM?"VK_FORMAT_R8G8B8A8_UNORM":"VK_FORMAT_B8G8R8A8_UNORM", "VK_COLORSPACE_SRGB_NONLINEAR_KHR");
            return format;
        }
        if (format.format==VK_FORMAT_B8G8R8A8_UNORM &&  format.colorSpace==VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
            surfaceFormat = format;
        }
    }
    VLOG("Selected SURFACE FORMAT ${} & ColorSpace: ${}",surfaceFormat.format==VK_FORMAT_R8G8B8A8_UNORM?"VK_FORMAT_R8G8B8A8_UNORM":"VK_FORMAT_B8G8R8A8_UNORM", "VK_COLORSPACE_SRGB_NONLINEAR_KHR");
    return surfaceFormat;
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

bool createSwapChain(const AppContext& context,DisplayAdapter& displayAdapter) {
    const auto& surfaceCapabilities = displayAdapter.swapChainInfo.surfaceCapabilities;
    if (surfaceCapabilities.maxImageCount<1)throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to get swapchain max image count"));
    //? pick suitable surface formats
    VkSurfaceFormatKHR surfaceFormat = pickSuitableSurfaceFormat(displayAdapter.swapChainInfo.surfaceFormats);
    //? pick suitable present mode
    VkPresentModeKHR presentMode = pickSuitablePresentMode(displayAdapter.swapChainInfo.presentModes);
    //? pick image resolution
    VkExtent2D swapChainExtent = pickSuitableExtent(surfaceCapabilities);
    uint32_t imageCount = static_cast<uint32_t>(surfaceCapabilities.minImageCount+1);
    if (surfaceCapabilities.maxImageCount<imageCount)imageCount=surfaceCapabilities.maxImageCount;
    VkSwapchainCreateInfoKHR swapChainCreateInfo = {};
    swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainCreateInfo.surface = displayAdapter.surface;
    swapChainCreateInfo.minImageCount = imageCount; // Enabling Triple Buffer. 1 front 2 back
    swapChainCreateInfo.imageFormat = surfaceFormat.format;
    swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
    swapChainCreateInfo.imageExtent = swapChainExtent;
    swapChainCreateInfo.imageArrayLayers = 1; //* numbers of layers for each image in chain
    swapChainCreateInfo.imageUsage =  VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // what attachment we will be using
    swapChainCreateInfo.preTransform = surfaceCapabilities.currentTransform; // transform to perform on swap chain
    swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // how to blend with external graphics , like how to blend with things outside of window area
    swapChainCreateInfo.clipped = VK_TRUE;     //Clipping part of image which are off screen
    swapChainCreateInfo.presentMode = presentMode;
    if (context.queueFamilyIndices.graphicsFamilyIndex==context.queueFamilyIndices.presentationFamilyIndex) {
        swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapChainCreateInfo.queueFamilyIndexCount = 0;
        swapChainCreateInfo.pQueueFamilyIndices = nullptr;
    }else {
        // ? Image will be share between queue families concurrently
        uint32_t queueFamilyIndices[]={
            static_cast<uint32_t>(context.queueFamilyIndices.graphicsFamilyIndex),
            static_cast<uint32_t>(context.queueFamilyIndices.presentationFamilyIndex),
          };
        swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapChainCreateInfo.queueFamilyIndexCount = 2;
        swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    //! if we have old swapChain then we will pass it it to oldSwapChain, which is mainly used when resizing screen.
    swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
    if (vkCreateSwapchainKHR(context.Device.logicalDevice,&swapChainCreateInfo,nullptr,&displayAdapter.swapchain)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create Vulk Swap Chain"));
    }
    displayAdapter.swapChainImageFormat = surfaceFormat.format;
    displayAdapter.swapChainExtent = swapChainExtent;
    return true;
}

std::vector<VkImage> getSwapChainImages(const AppContext& context, const DisplayAdapter& displayAdapter) {
    std::vector<VkImage> swapChainImages;
    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(context.Device.logicalDevice,displayAdapter.swapchain,&imageCount,nullptr);
    if (imageCount==0) throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to get swapchain images"));
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(context.Device.logicalDevice,displayAdapter.swapchain,&imageCount,swapChainImages.data());
    return swapChainImages;
}

VkImageView createImageView(const AppContext& context,const VkImage& img) {
    VkImageView imageView = VK_NULL_HANDLE;
    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.image = img;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = ZERO;
    imageViewCreateInfo.subresourceRange.levelCount = ONE;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = ZERO;
    imageViewCreateInfo.subresourceRange.layerCount = ONE;

    if (vkCreateImageView(context.Device.logicalDevice,&imageViewCreateInfo,nullptr,&imageView)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create Vulk Image View"));
    }
    if (imageView==VK_NULL_HANDLE) throw std::runtime_error(VULK_RUNTIME_ERROR("Invalid ImageView Generated"));
    return imageView;
}