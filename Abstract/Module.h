#ifndef MODULE_H
#define MODULE_H

#include "ModuleRegistry.h"

class Module
{
public:
    Module();
    void setModuleRegistry(ModuleRegistry *moduleRegistry);
protected:
    ModuleRegistry *moduleRegistry;
};

#endif // MODULE_H
