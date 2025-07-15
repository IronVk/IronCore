//
// Created by STHEP on 7/16/2025.
//

#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H
#include <vulkan/vulkan.h>
#include <vector>

#include "../../common/VulkCommon.h"

class GraphicsPipeline {
private:
    MainDevice devices;
    DisplayAdapter displayAdapter;
    VkPipelineShaderStageCreateInfo  vertexShaderStage;
    VkPipelineShaderStageCreateInfo  fragmentShaderStage;
public:
    GraphicsPipeline();
    ~GraphicsPipeline();
    void setDisplayAdapter(const DisplayAdapter& displayAdapter);
    void setMainDevice(const MainDevice& device);
    void createVerteShaderStage(const std::vector<char>& vertexShader);
    void createFragmentShaderStage(const std::vector<char>& fragmentShader);

};



#endif //GRAPHICSPIPELINE_H
