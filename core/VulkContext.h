//
// Created by adnan on 6/30/25.
//

#ifndef VULKCONTEXT_H
#define VULKCONTEXT_H
#include "../common/VulkCommon.h"


class VulkContext {
private:
    VkContext context;
    MainDevice device;
public:
    VulkContext()=default;
};



#endif //VULKCONTEXT_H
