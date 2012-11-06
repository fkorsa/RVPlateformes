#ifndef MODULEREGISTRY_H
#define MODULEREGISTRY_H

class Window;
class InputManager;

class ModuleRegistry
{
public:
    ModuleRegistry();

    void registerWindow(Window *window);
    Window* getWindow();

    void registerInputManager(InputManager *inputManager);
    InputManager* getInputManager();

private:
    Window *window;
    InputManager *inputManager;
};

#endif // MODULEREGISTRY_H
