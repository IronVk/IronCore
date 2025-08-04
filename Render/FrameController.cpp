//
// Created by STHEP on 8/3/2025.
//

#include "FrameController.h"

#include "../Util/VulkUtility.h"

FrameController::FrameController(const DisplayAdapter &displayAdapter, const GraphicsPipeline &graphicsPipeline) {
    this->displayAdapter = displayAdapter;
    this->graphicsPipeline = graphicsPipeline;
    this->swapChainFrameBuffers.resize(this->displayAdapter.swapChainImages.size()); //*resizing swapChain Frame Buffer at constructor level
}

void FrameController::setupFrameBuffer() {
    for (auto swapChainImage: this->displayAdapter.swapChainImages) {

    }

}


FrameController::~FrameController() {
    clearVector(this->swapChainFrameBuffers);
}
