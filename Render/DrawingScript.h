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
    u32 imageIndex{};
    std::shared_ptr<RenderInitInfo> drawInitInfo = nullptr;
    std::unique_ptr<FrameController> frameController = nullptr;
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderCompleteSemaphore = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;
    void cleanup();
public:
    DrawingScript(const std::shared_ptr<RenderInitInfo> &renderInitInfo);
    ~DrawingScript();

    void draw();

};


#endif //PRACTICEVK_DRAWINGSCRIPT_H