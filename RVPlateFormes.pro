include(InputManager/InputManager.pri)
include(Window/Window.pri)

SOURCES += \
    main.cpp \
    Controller.cpp

HEADERS += \
    Controller.h \
    Constants.h

LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf
LIBS += -L/usr/lib -losg -losgUtil -losgDB

INCLUDEPATH = /usr/include/SDL

