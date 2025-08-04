//
// Created by STHEP on 8/3/2025.
//

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H
#include <vector>
#include <vulkan/vulkan.h>

//# we will handle everything about frame buffer and command buffer from this class
class FrameController {
private:
    std::vector<VkFramebuffer> FrameBuffers;

};



#endif //FRAMEMANAGER_H
