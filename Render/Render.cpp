//
// Created by STHEP on 8/3/2025.
//

#include "Render.h"

Render::Render(const RenderInitInfo& renderInitInfo) {
    this->appRenderInitInfo = {};
    this->appRenderInitInfo = std::move(renderInitInfo);
    this->frameController = std::make_unique<FrameController>
    (this->appRenderInitInfo.applicationContext,
     this->appRenderInitInfo.displayAdapter,
     this->appRenderInitInfo.graphicsPipeline
    );
}
