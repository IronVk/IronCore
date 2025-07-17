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
    VkPipelineVertexInputStateCreateInfo vertexInputInfo;
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
    //#stage 1
    void setVertexInputInfo();

    //#stage 2



};



#endif //GRAPHICSPIPELINE_H
