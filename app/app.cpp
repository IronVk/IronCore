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
        this->createConfStruct.engine_name.empty() ||
        !this->createConfStruct.window || this->createConfStruct.extensions.empty())throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Required Parameter Missing"));
    this->appContext = new VulkContext(this->createConfStruct);
    appContext->createContext();

}




