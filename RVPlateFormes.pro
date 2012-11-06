include(InputManager/InputManager.pri)
include(Window/Window.pri)

SOURCES += \
    main.cpp \
    Controller.cpp \
    ModuleRegistry.cpp \
    Module.cpp

HEADERS += \
    Controller.h \
    Constants.h \
    ModuleRegistry.h \
    Module.h

LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf
LIBS += -L/usr/lib -losg -losgUtil -losgDB

INCLUDEPATH = /usr/include/SDL

