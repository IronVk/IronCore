//
// Created by STHEP on 7/16/2025.
//
#pragma once
#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H
#include <vulkan/vulkan.h>
#include <vector>
#include "../../common/VulkPredefs.h"

class GraphicsPipeline {
private:
    //!temporary shader module holder
    VkShaderModule vertexShaderModule;
    VkShaderModule fragmentShaderModule;
    //?Required lifetime instances
    //! warning: Don't Reference MainDevice directly.Rather use AppContext from here.
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
    VkRenderPass renderPass;
    //#GRAPHICS PIPELINE
    VkPipeline graphicsPipeline;
public:
    //* constructor
    GraphicsPipeline();

    //! destructor
    ~GraphicsPipeline();

    VkRenderPass& getRenderPass() { return this->renderPass; }
    VkPipeline& getGraphicsPipeline() { return this->graphicsPipeline; }
    VkRect2D& getScissor() { return this->scissorInfo; }
    VkViewport& getViewport() { return this->viewportInfo; }
    VkPipelineLayout& getPipelineLayout() { return this->pipeLineLayout; }


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

    //# stage 5: Create Render pass
    void setupRenderPass();

    //#stage 7: Create GraphicsPipeline
    void createGraphicsPipeline();





};



#endif //GRAPHICSPIPELINE_H
