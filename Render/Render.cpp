//
// Created by STHEP on 8/3/2025.
//

#include "Render.h"

Render::Render(const RenderInitInfo& renderInitInfo) {
    this->appInitInfo = std::make_unique<RenderInitInfo>(renderInitInfo);
    this->frameController = std::make_unique<FrameController>
    (this->appInitInfo->pApplicationContext,
     this->appInitInfo->pDisplayAdapter,
     this->appInitInfo->pGraphicsPipeline
    );

}



Render::~Render() {
    this->appInitInfo.reset();
    this->frameController.reset();
}
