include(InputManager/InputManager.pri)
include(Window/Window.pri)

SOURCES += \
    main.cpp \
    Controller.cpp \
    ModuleRegistry.cpp \
    Module.cpp \
    Scene.cpp \
    Ball.cpp \
    Text2d.cpp

HEADERS += \
    Controller.h \
    Constants.h \
    ModuleRegistry.h \
    Module.h \
    Scene.h \
    Ball.h \
    Text2d.h


# SDL
LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf
INCLUDEPATH = /usr/include/SDL

#OSG
LIBS += -L/usr/lib -losg -losgUtil -losgDB -losgGA -losgViewer -losgText

# BULLET
LIBS += -L/usr/local/lib/ -lBulletDynamics -lBulletCollision -lLinearMath
INCLUDEPATH += /usr/local/include/bullet

# OSGBULLET
LIBS += -L/usr/local/lib/ -losgbDynamics -losgbCollision -losgbInteraction
LIBS += -L/usr/local/lib64/ -lOpenThreads
