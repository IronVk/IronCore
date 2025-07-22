//
// Created by STHEP on 7/16/2025.
//

#include "GraphicsPipeline.h"

#include <vector>

GraphicsPipeline::GraphicsPipeline() {
    this->vertexShaderStage = {};
    this->fragmentShaderStage = {};
    this->vertexInputCreateInfo = {};
    this->inputAssemblyCreateInfo = {};
    this->viewportInfo = {};
    this->scissorInfo = {};
    this->viewportStateCreateInfo = {};
    this->rasterizationStateCreateInfo = {};
    this->multisampleStateCreateInfo = {};
    this->colorBlendAttachmentState = {};
    this->colorBlendStateCreateInfo = {};
}

void GraphicsPipeline::setDisplayAdapter(const DisplayAdapter &displayAdapter) {
    this->displayAdapter = displayAdapter;
}

void GraphicsPipeline::setMainDevice(const MainDevice &device) {
    this->devices = device;
}


void GraphicsPipeline::createVerteShaderStage(const std::vector<char> &vertexCode) {
    if (this->devices.logicalDevice == VK_NULL_HANDLE)throw std::runtime_error(VULK_RUNTIME_ERROR("Device is null"));
    VkShaderModule shaderModule = VK_NULL_HANDLE;
    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = vertexCode.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t *>(vertexCode.data());
    if (vkCreateShaderModule(this->devices.logicalDevice, &shaderModuleCreateInfo, nullptr, &shaderModule) !=
        VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to create shader module"));
    }
    this->vertexShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    this->vertexShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    this->vertexShaderStage.module = shaderModule;
    this->vertexShaderStage.pName = "main";
    // ! destroy shader module
    vkDestroyShaderModule(this->devices.logicalDevice, shaderModule, nullptr);
}

void GraphicsPipeline::createFragmentShaderStage(const std::vector<char> &fragmentShader) {
    if (this->devices.logicalDevice == VK_NULL_HANDLE)throw std::runtime_error(VULK_RUNTIME_ERROR("Device is null"));
    VkShaderModule shaderModule = VK_NULL_HANDLE;
    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = fragmentShader.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t *>(fragmentShader.data());
    if (vkCreateShaderModule(this->devices.logicalDevice, &shaderModuleCreateInfo, nullptr, &shaderModule) !=
        VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module");
    }
    this->fragmentShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    this->fragmentShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    this->fragmentShaderStage.module = shaderModule;
    this->fragmentShaderStage.pName = "main";
    // ! destroy shader module
    vkDestroyShaderModule(this->devices.logicalDevice, shaderModule, nullptr);
}

void GraphicsPipeline::setupVertexInputInfo() {
    this->vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    this->vertexInputCreateInfo.vertexBindingDescriptionCount = 0;
    this->vertexInputCreateInfo.pVertexBindingDescriptions = nullptr;
    this->vertexInputCreateInfo.vertexAttributeDescriptionCount = 0;
    this->vertexInputCreateInfo.pVertexAttributeDescriptions = nullptr;
}


void GraphicsPipeline::setupInputAssembly() {
    this->inputAssemblyCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    this->inputAssemblyCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    this->inputAssemblyCreateInfo.primitiveRestartEnable = VK_FALSE;
}


void GraphicsPipeline::setupViewportState() {
    //? Initializing ViewportCreateInfo
    this->viewportInfo.x = ZERO;
    this->viewportInfo.y = ZERO;
    this->viewportInfo.width = static_cast<float>(this->displayAdapter.swapChainExtent.width);
    this->viewportInfo.height = static_cast<float>(this->displayAdapter.swapChainExtent.height);
    this->viewportInfo.minDepth = ZERO;
    this->viewportInfo.maxDepth = ONE;

    //? Initializing viewport scissors
    this->scissorInfo.offset.x = ZERO;
    this->scissorInfo.offset.y = ZERO;
    this->scissorInfo.extent = this->displayAdapter.swapChainExtent;

    //? now setup viewport state
    this->viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    this->viewportStateCreateInfo.viewportCount = ONE;
    this->viewportStateCreateInfo.scissorCount = ONE;
    this->viewportStateCreateInfo.pViewports = &this->viewportInfo;
    this->viewportStateCreateInfo.pScissors = &this->scissorInfo;
}


void GraphicsPipeline::setupRasterizationState() {
    this->rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    this->rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    this->rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    this->rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    this->rasterizationStateCreateInfo.lineWidth = ONE;
    this->rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    this->rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    this->rasterizationStateCreateInfo.depthBiasClamp = VK_FALSE;
    this->rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
    this->rasterizationStateCreateInfo.depthBiasConstantFactor = ZERO; // Optional
    this->rasterizationStateCreateInfo.depthBiasClamp = ZERO; // Optional
    this->rasterizationStateCreateInfo.depthBiasSlopeFactor = ZERO; // Optional
}


void GraphicsPipeline::setupMultisampleState() {
    this->multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    this->multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    this->multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    this->multisampleStateCreateInfo.minSampleShading = ONE; // Optional
    this->multisampleStateCreateInfo.pSampleMask = nullptr; // Optional
    this->multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE; // Optional
    this->multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE; // Optional
}

void GraphicsPipeline::setupColorBlending() {
    //? color blend attachment
    this->colorBlendAttachmentState.colorWriteMask = COLOR_WRITE_MASK::RGBA;
    this->colorBlendAttachmentState.blendEnable = VK_TRUE;
    this->colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    this->colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    this->colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
    this->colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    this->colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    this->colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

    //? color blend attachment.
    this->colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    this->colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    this->colorBlendStateCreateInfo.logicOpEnable = VK_LOGIC_OP_COPY;
    this->colorBlendStateCreateInfo.attachmentCount = 1;
    this->colorBlendStateCreateInfo.pAttachments = &this->colorBlendAttachmentState;
    this->colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
    this->colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
    this->colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
    this->colorBlendStateCreateInfo.blendConstants[3] = 0.0f;
}
