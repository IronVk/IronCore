//
// Created by STHEP on 8/13/2025.
//

#include "DrawingScript.h"

DrawingScript::DrawingScript(RenderInitInfo renderInitInfo) {
    try {
        this->drawInitInfo = std::make_unique<RenderInitInfo>(renderInitInfo);
        this->frameController = std::make_unique<FrameController>
        (this->drawInitInfo->pApplicationContext,
         this->drawInitInfo->pDisplayAdapter,
         this->drawInitInfo->pGraphicsPipeline
        );
        //* Build the FrameController
        this->frameController->setupFrameBuffer();
        this->frameController->setupCommandPool();
        this->frameController->setupCommandBuffer();

        //* Setting Up Semaphores & fences
        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        // need to initialize fence as signalled. Either it will block for ever
        fenceCreateInfo.flags  = VK_FENCE_CREATE_SIGNALED_BIT;
        if (
            vkCreateSemaphore(this->drawInitInfo->pApplicationContext.Device.logicalDevice,&semaphoreCreateInfo,nullptr,&this->imageAvailableSemaphore)!=VK_SUCCESS ||
            vkCreateSemaphore(this->drawInitInfo->pApplicationContext.Device.logicalDevice,&semaphoreCreateInfo,nullptr,&this->renderCompleteSemaphore)!=VK_SUCCESS ||
            vkCreateFence(this->drawInitInfo->pApplicationContext.Device.logicalDevice,&fenceCreateInfo,nullptr,&this->inFlightFence)!=VK_SUCCESS
        ) {
            throw std::runtime_error(VULK_RUNTIME_ERROR("Failed To Create Semaphore."));
        }
        VLOG("SEMAPHORES & Fences INITIALIZED");

    }catch(std::exception& e) {
        VLOG("Drawing Script Failed: ${}",e.what());
        this->cleanup();
        throw std::runtime_error(VULK_RUNTIME_ERROR("Drawing Script Failed."));
    }
}

void DrawingScript::draw() {
    VkDevice& logicalDevice = this->drawInitInfo->pApplicationContext.Device.logicalDevice;
    vkWaitForFences(logicalDevice,1,&this->inFlightFence,VK_TRUE,u64_max);
    vkResetFences(logicalDevice,1,&this->inFlightFence);
    u32 imageIndex;
    vkAcquireNextImageKHR(logicalDevice,this->drawInitInfo->pDisplayAdapter.swapchain,u64_max,this->imageAvailableSemaphore,VK_NULL_HANDLE,&imageIndex);
    vkResetCommandBuffer(this->frameController->getCommandBuffer(),0);
    this->frameController->recordCommandBuffer(imageIndex);
    //# submitting CommandBuffer
    VkSemaphore waitSemaphore[] = {this->imageAvailableSemaphore};
    VkSemaphore signalSemaphore[] = {this->renderCompleteSemaphore};
    VkPipelineStageFlags pipelineWaitStageFlags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->frameController->getCommandBuffer();
    submitInfo.pWaitSemaphores = waitSemaphore;
    submitInfo.pWaitDstStageMask = pipelineWaitStageFlags;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphore;

    if (vkQueueSubmit(this->drawInitInfo->pQueueList.graphicsQueue,1,&submitInfo,this->inFlightFence)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Drawing Script Failed."));
    }

}

void DrawingScript::cleanup() {
    vkDestroySemaphore(this->drawInitInfo->pApplicationContext.Device.logicalDevice, this->imageAvailableSemaphore,nullptr);
    vkDestroySemaphore(this->drawInitInfo->pApplicationContext.Device.logicalDevice, this->renderCompleteSemaphore,nullptr);
    vkDestroyFence(this->drawInitInfo->pApplicationContext.Device.logicalDevice,this->inFlightFence,nullptr);
    this->drawInitInfo.reset();
    this->frameController.reset();
}


DrawingScript::~DrawingScript() {
    this->cleanup();
}

