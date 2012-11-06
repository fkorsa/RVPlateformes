#ifndef INPUTMANAGERSTRATEGY_H
#define INPUTMANAGERSTRATEGY_H

#include "Constants.h"

class ModuleRegistry;

class InputStrategy
{
public:
    virtual ReturnStatus handleInput() = 0;
    void setModuleRegistry(ModuleRegistry *moduleRegistry);
private:
    ModuleRegistry *moduleRegistry;
};

#endif // INPUTMANAGERSTRATEGY_H
