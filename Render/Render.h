//
// Created by STHEP on 8/3/2025.
//

#ifndef RENDER_H
#define RENDER_H
#include "FrameController.h"
#include "../common/VulkPredefs.h"


class Render {
private:
    std::unique_ptr<FrameController> frameController = nullptr;
    RenderInitInfo appRenderInitInfo = {};
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderCompleteSemaphore = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;


public:
    Render(const RenderInitInfo& renderInitInfo);
    ~Render();

};



#endif //RENDER_H
