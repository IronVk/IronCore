//
// Created by adnan on 6/30/25.
//

#include "VulkContext.h"

void VulkContext::__intialize_vulkan__context() {
    //TODO: if (this->appName.empty() || this->engineName.empty() || this->requiredExtensions.empty())


}


void VulkContext::setAppName(std::string appName) {
    this->appName = std::move(appName);
}
void VulkContext::setEngineName(std::string engineName) {
    this->engineName = std::move(engineName);
}

void VulkContext::setRequiredExtensions(std::vector<const char *> requiredExtensions) {
    this->requiredExtensions = std::move(requiredExtensions);
}
