#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputStrategy;

class InputManager
{
public:
    InputManager();
private:
    InputStrategy *inputStrategy;
};

#endif // INPUTMANAGER_H
