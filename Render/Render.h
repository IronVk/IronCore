//
// Created by STHEP on 8/3/2025.
//

#ifndef RENDER_H
#define RENDER_H
#include "FrameController.h"
#include "../common/VulkPredefs.h"


class Render {
private:
    std::unique_ptr<FrameController> controller = nullptr;
    RenderInitInfo appRenderInitInfo;


public:
    Render(RenderInitInfo renderInitInfo);
    ~Render();

};



#endif //RENDER_H
