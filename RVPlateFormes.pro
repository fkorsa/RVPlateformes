include(InputManager/InputManager.pri)

SOURCES += \
    main.cpp \
    Controller.cpp \
    InterfaceStrategy.cpp \
    Window.cpp

HEADERS += \
    Controller.h \
    Constants.h \
    InterfaceStrategy.h \
    Window.h

LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf
LIBS += -L/usr/lib -losg -losgUtil -losgDB

INCLUDEPATH = /usr/include/SDL

