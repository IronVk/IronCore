//
// Created by STHEP on 8/3/2025.
//

#include "FrameController.h"

#include "../Util/VulkUtility.h"

FrameController::FrameController(const DisplayAdapter &displayAdapter, const GraphicsPipeline &graphicsPipeline) {
    this->displayAdapter = displayAdapter;
    this->graphicsPipeline = graphicsPipeline;
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
        if (vkCreateFramebuffer(this->graphicsPipeline.getDevice(),&frameBufferCreateInfo,nullptr,&this->swapChainFrameBuffers[i])!=VK_SUCCESS) {
            throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create framebuffer."));
        }
        VLOG("Frame Buffer Setup Complete");
    }

}

void FrameController::setupCommandPool() {

}



FrameController::~FrameController() {
    for (auto frameBuffer: this->swapChainFrameBuffers) {
        vkDestroyFramebuffer(this->graphicsPipeline.getDevice(),frameBuffer,nullptr);
    }
    clearVector(this->swapChainFrameBuffers);
}
