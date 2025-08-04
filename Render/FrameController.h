//
// Created by STHEP on 8/3/2025.
//

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H
#include <vector>
#include <vulkan/vulkan.h>

#include "../common/VulkCommon.h"
#include "../pipeline/Graphics/GraphicsPipeline.h"

//# we will handle everything about frame buffer and command buffer from this class
class FrameController {
private:
    GraphicsPipeline graphicsPipeline;
    DisplayAdapter displayAdapter ;
    std::vector<VkFramebuffer> swapChainFrameBuffers;
    std::vector<VkCommandBuffer> CommandBuffers;
    VkCommandPool graphicsCommandPool;
public:
    FrameController(const DisplayAdapter& displayAdapter,const GraphicsPipeline& graphicsPipeline);
    ~FrameController();

    void setupFrameBuffer();
    void setupCommandPool();

};



#endif //FRAMEMANAGER_H
