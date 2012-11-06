#ifndef MODULE_H
#define MODULE_H

class ModuleRegistry;

class Module
{
public:
    void setModuleRegistry(ModuleRegistry *moduleRegistry);
private:
    ModuleRegistry *moduleRegistry;
};

#endif // MODULE_H
