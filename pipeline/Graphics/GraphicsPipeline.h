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
    //? GRAPHICS PIPELINE STATE HOLDER
    VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo;
    VkViewport viewportCreateInfo;
public:
    //* constructor
    GraphicsPipeline();

    //! destructor
    ~GraphicsPipeline()=default;

    //* setters
    void setDisplayAdapter(const DisplayAdapter& displayAdapter);
    void setMainDevice(const MainDevice& device);

    //* shader stages
    void createVerteShaderStage(const std::vector<char>& vertexShader);
    void createFragmentShaderStage(const std::vector<char>& fragmentShader);

    //* pipeline stages
    //#stage 1: set vertex input info
    void setupVertexInputInfo();

    //#stage 2: setupInput assembly describes two things: what kind of geometry will be drawn from the vertices and if primitive restart should be enabled
    void setupInputAssembly();

    //# stage 3: VIEWPORT & SCISSOR describe how you want to raster image in you window or screen.
    void setupViewport();



};



#endif //GRAPHICSPIPELINE_H
