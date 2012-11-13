include(VRJuggler/VRJuggler.pri)
include(3DEntities/3DEntities.pri)

SOURCES += \
    main.cpp \
    Controller.cpp \
    ModuleRegistry.cpp \
    Module.cpp \
    Scene.cpp \
    Text2d.cpp \
    InputManager.cpp \
    SDLInputStrategy.cpp \
    SDLWindow.cpp \
    Skybox.cpp \
    Text3d.cpp

HEADERS += \
    Controller.h \
    Constants.h \
    ModuleRegistry.h \
    Module.h \
    Scene.h \
    Text2d.h \
    InputManager.h \
    SDLInputStrategy.h \
    SDLWindow.h \
    Skybox.h \
    Text3d.h \
    Utils.h

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
