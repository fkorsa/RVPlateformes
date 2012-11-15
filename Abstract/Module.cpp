#include "Module.h"

Module::Module() :
    moduleRegistry(NULL)
{
}

void Module::setModuleRegistry(ModuleRegistry *moduleRegistry)
{
    this->moduleRegistry = moduleRegistry;
}
