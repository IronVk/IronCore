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
inline VkClearValue CLEAR_COLOR[] = {
    {0.25,0.5,0.65,1.0}
};
//# we will handle everything about frame buffer and command buffer from this class
class FrameController {
private:
    AppContext applicationContext;
    std::shared_ptr<GraphicsPipeline> graphicsPipeline;
    DisplayAdapter displayAdapter;
    std::vector<VkFramebuffer> swapChainFrameBuffers;
    VkCommandBuffer CommandBuffers;
    VkCommandPool graphicsCommandPool;

    VkRenderPassBeginInfo obtainRenderPassInfo(const u32 imageIndex) const;
public:
    FrameController(const AppContext& appContext,const DisplayAdapter& displayAdapter, std::shared_ptr<GraphicsPipeline> graphicsPipeline);
    ~FrameController();
    VkCommandBuffer& getCommandBuffer();
    void setupFrameBuffer();
    void setupCommandPool();
    void setupCommandBuffer();
    void recordCommandBuffer(const u32 imageIndex);

};



#endif //FRAMEMANAGER_H
