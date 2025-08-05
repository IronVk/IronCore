//
// Created by STHEP on 8/3/2025.
//

#include "FrameController.h"

#include "../Util/VulkUtility.h"

FrameController::FrameController(const AppContext& appContext,const DisplayAdapter &displayAdapter, const GraphicsPipeline &graphicsPipeline) {
    this->applicationContext = appContext;
    this->displayAdapter = displayAdapter;
    this->graphicsPipeline = graphicsPipeline;
    this->graphicsCommandPool = VK_NULL_HANDLE;
    this->swapChainFrameBuffers.resize(this->displayAdapter.swapChainImages.size()); //*resizing swapChain Frame Buffer at constructor level
}

void FrameController::setupFrameBuffer() {
    const auto N = this->swapChainFrameBuffers.size();
    if (N<1)throw std::logic_error(VULK_LOGIC_ERROR("Invalid FrameBuffer Size."));
    for (unsigned int i = 0; i < N; ++i) {
        std::array<VkImageView, 1> attachments = {this->displayAdapter.swapChainImages[i].imageView};
        VkFramebufferCreateInfo frameBufferCreateInfo = {};
        frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frameBufferCreateInfo.renderPass = this->graphicsPipeline.getRenderPass();
        frameBufferCreateInfo.attachmentCount = 1;
        frameBufferCreateInfo.pAttachments = attachments.data();
        frameBufferCreateInfo.width  = this->displayAdapter.swapChainExtent.width;
        frameBufferCreateInfo.height = this->displayAdapter.swapChainExtent.height;
        frameBufferCreateInfo.layers = 1;
        if (vkCreateFramebuffer(this->applicationContext.Device.logicalDevice,&frameBufferCreateInfo,nullptr,&this->swapChainFrameBuffers[i])!=VK_SUCCESS) {
            throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create framebuffer."));
        }
        VLOG("Frame Buffer Setup Complete");
    }

}

void FrameController::setupCommandPool() {
    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolCreateInfo.queueFamilyIndex = this->applicationContext.queueFamilyIndices.graphicsFamilyIndex;
    if (vkCreateCommandPool(this->applicationContext.Device.logicalDevice,&commandPoolCreateInfo,nullptr,&this->graphicsCommandPool)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create command pool."));
    }

}



FrameController::~FrameController() {
    if (this->graphicsCommandPool!=VK_NULL_HANDLE)vkDestroyCommandPool(this->applicationContext.Device.logicalDevice,this->graphicsCommandPool,nullptr);
    for (auto frameBuffer: this->swapChainFrameBuffers) {
        vkDestroyFramebuffer(this->applicationContext.Device.logicalDevice,frameBuffer,nullptr);
    }
    this->swapChainFrameBuffers.clear();
}
