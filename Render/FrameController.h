//
// Created by STHEP on 8/3/2025.
//
#pragma once
#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H
#include <vector>
#include <vulkan/vulkan.h>
#include "../common/VulkPredefs.h"
#include "../pipeline/Graphics/GraphicsPipeline.h"
inline VkClearValue CLEAR_COLOR = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
//# we will handle everything about frame buffer and command buffer from this class
class FrameController {
private:
    AppContext applicationContext;
    GraphicsPipeline graphicsPipeline;
    DisplayAdapter displayAdapter ;
    std::vector<VkFramebuffer> swapChainFrameBuffers;
    VkCommandBuffer CommandBuffers;
    VkCommandPool graphicsCommandPool;

    VkRenderPassBeginInfo obtainRenderPassInfo(const u32 imageIndex);
public:
    FrameController(const AppContext& appContext,const DisplayAdapter& displayAdapter,const GraphicsPipeline& graphicsPipeline);
    ~FrameController();
    VkCommandBuffer& getCommandBuffer();
    void setupFrameBuffer();
    void setupCommandPool();
    void setupCommandBuffer();
    void recordCommandBuffer(const u32 imageIndex);

};



#endif //FRAMEMANAGER_H
