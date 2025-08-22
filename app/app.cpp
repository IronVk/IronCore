//
// Created by adnan on 7/2/25.
//

#include "app.h"
#include <format>
#include <utility>
#include "../Util/diagnostic/InstanceInitializationError.h"

app::app() {
    this->createConfStruct = {};
    this->appContext = nullptr;
}
app::~app() {
    delete this->appContext;
}


VulkConf& app::getCreateConfStruct() {
    return this->createConfStruct;
}
void app::setConfig(VulkConf config) {
    this->createConfStruct = std::move(config);
}


void app::build() {
    if (this->createConfStruct.app_name.empty() ||
        this->createConfStruct.engine_name.empty() || this->createConfStruct.window_title.empty())throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Required Parameter Missing"));
    //!compile shader
    const auto vertex_path = this->createConfStruct.vertShaderPath;
    const auto fragment_path = this->createConfStruct.fragShaderPath;
    std::string command_to_compile_vertex_shader = std::format("glslangValidator -V {} -o {}.spv",vertex_path,vertex_path);
    std::string command_to_compile_fragment_shader = std::format("glslangValidator -V {} -o {}.spv",fragment_path,fragment_path);
    if (std::system(command_to_compile_vertex_shader.c_str())!=0||std::system(command_to_compile_fragment_shader.c_str())!=0) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to compile Shader"));
    }

    //# start app
    this->createConfStruct.window_width = this->createConfStruct.window_width ?this->createConfStruct.window_width: 800;
    this->createConfStruct.window_height = this->createConfStruct.window_height?this->createConfStruct.window_height : 600;
    this->createConfStruct.build_mode = this->createConfStruct.build_mode?this->createConfStruct.build_mode:BuildMode::DEV;
    this->window_manager = new WindowManager(this->createConfStruct.window_width, this->createConfStruct.window_height,this->createConfStruct.window_title);
    this->createConfStruct.extensions = this->window_manager->getRequiredInstanceExtensionList();
    this->createConfStruct.window = this->window_manager->getWindow();
    this->appContext = new VulkContext(this->createConfStruct);
    appContext->createContext();
    appContext->setupSwapChain();
    appContext->createGraphicsPipeline();
    appContext->initDrawingScriptInstance();
    appContext->getDrawingScript().draw();
    this->window_manager->onTick([=]()
    {



    });
    this->window_manager->launch();
    this->window_manager->destroy();
}





