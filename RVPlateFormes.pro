SOURCES += \
    main.cpp \
    Controller.cpp \
    InputManager.cpp \
    InterfaceStrategy.cpp \
    Window.cpp

HEADERS += \
    Controller.h \
    InputManager.h \
    Constants.h \
    InterfaceStrategy.h \
    Window.h

LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf
LIBS += -L/usr/lib -losg -losgUtil -losgDB

INCLUDEPATH = /usr/include/SDL

