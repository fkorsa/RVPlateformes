#ifndef MODULE_H
#define MODULE_H

#include "ModuleRegistry.h"

class Module
{
public:
    void setModuleRegistry(ModuleRegistry *moduleRegistry);
protected:
    ModuleRegistry *moduleRegistry;
};

#endif // MODULE_H
