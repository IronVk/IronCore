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

        //* Work With Semaphores
        this->imageAvailableSemaphore = {};

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

