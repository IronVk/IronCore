//
// Created by adnan on 7/2/25.
//

#include "app.h"

#include <memory>

#include "../Util/diagnostic/InstanceInitializationError.h"

app::app() {
    this->createConfStruct = {};
    this->appContext = nullptr;
}
app::~app() {
    delete this->appContext;
}


VulkConf &app::getCreateConfStruct() {
    return this->createConfStruct;
}
void app::setConfig(VulkConf config) {
    this->createConfStruct = config;
}


void app::build() {
    if (this->createConfStruct.app_name.empty() ||
        this->createConfStruct.engine_name.empty() || this->createConfStruct.window_title.empty())throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Required Parameter Missing"));
    this->createConfStruct.window_width = this->createConfStruct.window_width ?this->createConfStruct.window_width: 800;
    this->createConfStruct.window_height = this->createConfStruct.window_height?this->createConfStruct.window_height : 600;
    this->createConfStruct.build_mode = this->createConfStruct.build_mode?this->createConfStruct.build_mode:BuildMode::DEV;
    WindowManager* window_manager = new WindowManager(this->createConfStruct.window_width, this->createConfStruct.window_height,this->createConfStruct.window_title);
    this->createConfStruct.extensions = window_manager->getRequiredInstanceExtensionList();
    this->appContext = new VulkContext(this->createConfStruct);
    appContext->createContext();
    window_manager->launch();
    window_manager->destroy();
}





