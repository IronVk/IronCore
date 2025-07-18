//
// Created by STHEP on 7/16/2025.
//

#include "GraphicsPipeline.h"

#include <vector>

GraphicsPipeline::GraphicsPipeline() {
    this->vertexShaderStage ={};
    this->fragmentShaderStage ={};
    this->vertexInputCreateInfo = {};
    this->inputAssemblyCreateInfo = {};
    this->viewportCreateInfo = {};
}

void GraphicsPipeline::setDisplayAdapter(const DisplayAdapter &displayAdapter) {
    this->displayAdapter = displayAdapter;
}

void GraphicsPipeline::setMainDevice(const MainDevice& device) {
    this->devices = device;
}




void GraphicsPipeline::createVerteShaderStage(const std::vector<char>& vertexCode) {
    if (this->devices.logicalDevice==VK_NULL_HANDLE)throw std::runtime_error("Device is null");
    VkShaderModule shaderModule = VK_NULL_HANDLE;
    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = vertexCode.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(vertexCode.data());
    if (vkCreateShaderModule(this->devices.logicalDevice,&shaderModuleCreateInfo,nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module");
    }
    this->vertexShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    this->vertexShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    this->vertexShaderStage.module = shaderModule;
    this->vertexShaderStage.pName = "main";
    // ! destroy shader module
    vkDestroyShaderModule(this->devices.logicalDevice,shaderModule,nullptr);

}

void GraphicsPipeline::createFragmentShaderStage(const std::vector<char>& fragmentShader) {
    if (this->devices.logicalDevice==VK_NULL_HANDLE)throw std::runtime_error("Device is null");
    VkShaderModule shaderModule = VK_NULL_HANDLE;
    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = fragmentShader.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(fragmentShader.data());
    if (vkCreateShaderModule(this->devices.logicalDevice,&shaderModuleCreateInfo,nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module");
    }
    this->fragmentShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    this->fragmentShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    this->fragmentShaderStage.module = shaderModule;
    this->fragmentShaderStage.pName = "main";
    // ! destroy shader module
    vkDestroyShaderModule(this->devices.logicalDevice,shaderModule,nullptr);
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


void GraphicsPipeline::setupViewport() {

}
