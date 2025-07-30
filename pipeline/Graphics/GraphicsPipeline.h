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
    //!temporary shader module holder
    VkShaderModule vertexShaderModule;
    VkShaderModule fragmentShaderModule;

    //?Required lifetime instances
    MainDevice devices;
    DisplayAdapter displayAdapter;
    VkPipelineShaderStageCreateInfo  vertexShaderStage;
    VkPipelineShaderStageCreateInfo  fragmentShaderStage;
    //? GRAPHICS PIPELINE STATE HOLDER
    VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo;
    VkViewport viewportInfo;
    VkRect2D scissorInfo;
    VkPipelineViewportStateCreateInfo viewportStateCreateInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo;
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachmentState;
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo;
    VkPipelineLayout pipeLineLayout;
    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo;
    //#GRAPHICS PIPELINE
    VkPipeline graphicsPipeline;
public:
    //* constructor
    GraphicsPipeline();

    //! destructor
    ~GraphicsPipeline();

    VkPipeline& getGraphicsPipeline() { return graphicsPipeline; }

    //*Cleaner
    void destroySelf();

    //* setters
    void setDisplayAdapter(const DisplayAdapter& displayAdapter);
    void setMainDevice(const MainDevice& device);

    //* shader stages
    void createVertexShaderStage(const std::vector<char>& vertexShader);
    void createFragmentShaderStage(const std::vector<char>& fragmentShader);


    //* pipeline stages
    //#stage 1: set vertex input info
    void setupVertexInputInfo();

    //#stage 2: setupInput assembly describes two things: what kind of geometry will be drawn from the vertices and if primitive restart should be enabled
    void setupInputAssembly();

    //# stage 3: VIEWPORT, SCISSOR & VIEW_PORT_STATE [describe how you want to raster image in you window or screen].
    void setupViewportState();

    //@ Rasterization
    //# stage 3: setting up ratering steps
    void setupRasterizationState();

    //# stage 4: Multisampling
    void setupMultisampleState();

    //# stage 5: Blending
    void setupColorBlending();

    //# stage 5: Blending
    void setupPipeLineLayout();

    //#stage 6: Create GraphicsPipeline
    void createGraphicsPipeline();





};



#endif //GRAPHICSPIPELINE_H
