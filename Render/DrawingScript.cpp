//
// Created by STHEP on 8/13/2025.
//

#include "DrawingScript.h"

DrawingScript::DrawingScript(RenderInitInfo renderInitInfo) {
    try {
        this->appInitInfo = std::make_unique<RenderInitInfo>(renderInitInfo);
        this->frameController = std::make_unique<FrameController>
        (this->appInitInfo->pApplicationContext,
         this->appInitInfo->pDisplayAdapter,
         this->appInitInfo->pGraphicsPipeline
        );
        //* Build the FrameController
        this->frameController->setupFrameBuffer();
        this->frameController->setupCommandPool();
        this->frameController->setupCommandBuffer();

        //* Setting Up Semaphores
        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        if (
            vkCreateSemaphore(this->appInitInfo->pApplicationContext.Device.logicalDevice,&semaphoreCreateInfo,nullptr,&this->imageAvailableSemaphore)!=VK_SUCCESS ||
            vkCreateSemaphore(this->appInitInfo->pApplicationContext.Device.logicalDevice,&semaphoreCreateInfo,nullptr,&this->renderCompleteSemaphore)!=VK_SUCCESS
        ) {
            throw std::runtime_error(VULK_RUNTIME_ERROR("Failed To Create Semaphore."));
        }
        VLOG("SEMAPHORES INITIALIZED");

        //* setting up fences


    }catch(std::exception& e) {
        VLOG("${}")
    }
}

DrawingScript::~DrawingScript() {
    vkDestroySemaphore(this->appInitInfo->pApplicationContext.Device.logicalDevice, this->imageAvailableSemaphore,nullptr);
    vkDestroySemaphore(this->appInitInfo->pApplicationContext.Device.logicalDevice, this->renderCompleteSemaphore,nullptr);

    this->appInitInfo.reset();
    this->frameController.reset();

}

