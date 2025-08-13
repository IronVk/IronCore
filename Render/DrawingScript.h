//
// Created by STHEP on 8/13/2025.
//
#pragma once
#ifndef PRACTICEVK_DRAWINGSCRIPT_H
#define PRACTICEVK_DRAWINGSCRIPT_H
#include "FrameController.h"
#include "../common/VulkPredefs.h"

class DrawingScript {
private:
    std::unique_ptr<RenderInitInfo> appInitInfo = nullptr;
    std::unique_ptr<FrameController> frameController = nullptr;
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderCompleteSemaphore = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;

public:
    DrawingScript(RenderInitInfo renderInitInfo);
    ~DrawingScript();
};


#endif //PRACTICEVK_DRAWINGSCRIPT_H