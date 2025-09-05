//
// Created by STHEP on 8/3/2025.
//

#include "FrameController.h"

#include <assert.h>

#include "../Util/VulkUtility.h"

FrameController::FrameController(const AppContext &appContext, const DisplayAdapter &displayAdapter,const std::shared_ptr<GraphicsPipeline> graphicsPipeline) {
    this->applicationContext = appContext;
    this->graphicsPipeline = graphicsPipeline;
    this->displayAdapter = displayAdapter;
    this->graphicsCommandPool = VK_NULL_HANDLE;
    const auto TOTAL_SWAP_CHAIN_IMAGE = this->displayAdapter.swapChainImages.size();
    this->swapChainFrameBuffers.resize(TOTAL_SWAP_CHAIN_IMAGE); //*resizing swapChain Frame Buffer at constructor level
    this->CommandBuffers = VK_NULL_HANDLE;
}

VkCommandBuffer &FrameController::getCommandBuffer() {
    return this->CommandBuffers;
}

void FrameController::setupFrameBuffer() {
    const auto N = this->displayAdapter.swapChainImages.size();
    if (N < 1)throw std::logic_error(VULK_LOGIC_ERROR("Invalid FrameBuffer Size."));
    for (u32 i = ZERO; i < N; ++i) {
        if (this->displayAdapter.swapChainImages[i].imageView == VK_NULL_HANDLE) {
            throw std::logic_error(VULK_LOGIC_ERROR("Invalid SwapChain image."));
        }

        std::array<VkImageView, 1> attachments = {this->displayAdapter.swapChainImages[i].imageView};
        VkFramebufferCreateInfo frameBufferCreateInfo = {};
        frameBufferCreateInfo.pNext = nullptr;
        frameBufferCreateInfo.flags = 0;
        frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frameBufferCreateInfo.renderPass = this->graphicsPipeline->getRenderPass();
        frameBufferCreateInfo.attachmentCount = 1;
        frameBufferCreateInfo.pAttachments = attachments.data();
        frameBufferCreateInfo.width = this->displayAdapter.swapChainExtent.width;
        frameBufferCreateInfo.height = this->displayAdapter.swapChainExtent.height;
        frameBufferCreateInfo.layers = 1;
        if (vkCreateFramebuffer(this->applicationContext.Device.logicalDevice, &frameBufferCreateInfo, nullptr,
                                &this->swapChainFrameBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create framebuffer."));
        }
    }
    VLOG("Frame Buffer Setup Complete");
}

void FrameController::setupCommandPool() {
    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolCreateInfo.queueFamilyIndex = this->applicationContext.queueFamilyIndices.graphicsFamilyIndex;
    if (vkCreateCommandPool(this->applicationContext.Device.logicalDevice, &commandPoolCreateInfo, nullptr,
                            &this->graphicsCommandPool) != VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create command pool."));
    }
}

void FrameController::setupCommandBuffer() {
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = this->graphicsCommandPool;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(this->applicationContext.Device.logicalDevice, &commandBufferAllocateInfo,
                                 &this->CommandBuffers) != VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to allocate command buffers."));
    }
    VLOG("CMD ALLOCATED");
}

VkRenderPassBeginInfo FrameController::obtainRenderPassInfo(const u32 imageIndex) const {
    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkExtent2D extent{0,0};
    renderPass = this->graphicsPipeline->getRenderPass();
    assert(imageIndex < this->displayAdapter.swapChainImages.size());
    extent = this->displayAdapter.swapChainExtent;

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = renderPass;
    renderPassBeginInfo.framebuffer = this->swapChainFrameBuffers[imageIndex];
    renderPassBeginInfo.renderArea.offset = {0, 0};
    renderPassBeginInfo.renderArea.extent = extent;
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = CLEAR_COLOR;


    return renderPassBeginInfo;
}


void FrameController::recordCommandBuffer(const u32 imageIndex) {
    VkCommandBufferBeginInfo commandBufferBeginInfo = {};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(this->CommandBuffers, &commandBufferBeginInfo) != VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to begin command buffers."));
    }
    const auto renderPassBeginInfo = this->obtainRenderPassInfo(imageIndex);
    //* Initiate Render Pass
    VLOG("RX");
    vkCmdBeginRenderPass(this->CommandBuffers, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    VLOG("SX");
    //* BInd with graphics pipeline
    vkCmdBindPipeline(this->CommandBuffers, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      this->graphicsPipeline->getGraphicsPipeline());
    vkCmdSetViewport(this->CommandBuffers,ZERO,ONE, &this->graphicsPipeline->getViewport());
    vkCmdSetScissor(this->CommandBuffers,ZERO,ONE, &this->graphicsPipeline->getScissor());
    vkCmdDraw(this->CommandBuffers, 3,ONE,ZERO,ZERO);
    vkCmdEndRenderPass(this->CommandBuffers);
    if (vkEndCommandBuffer(this->CommandBuffers) != VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to end command buffers."));
    }
}


FrameController::~FrameController() {
    if (this->graphicsCommandPool != VK_NULL_HANDLE)vkDestroyCommandPool(
        this->applicationContext.Device.logicalDevice, this->graphicsCommandPool, nullptr);
    for (auto frameBuffer: this->swapChainFrameBuffers) {
        vkDestroyFramebuffer(this->applicationContext.Device.logicalDevice, frameBuffer, nullptr);
    }
    this->swapChainFrameBuffers.clear();

    // this->CommandBuffers.clear();
}
