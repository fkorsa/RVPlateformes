include(VRJuggler/VRJuggler.pri)

SOURCES += \
    main.cpp \
    Controller.cpp \
    ModuleRegistry.cpp \
    Module.cpp \
    Scene.cpp \
    Ball.cpp \
    Text2d.cpp \
    InputManager.cpp \
    SDLInputStrategy.cpp \
    SDLWindow.cpp \
    Platform.cpp \
    Skybox.cpp \
    Pyramid.cpp \
    Text3d.cpp

HEADERS += \
    Controller.h \
    Constants.h \
    ModuleRegistry.h \
    Module.h \
    Scene.h \
    Ball.h \
    Text2d.h \
    InputManager.h \
    SDLInputStrategy.h \
    SDLWindow.h \
    Platform.h \
    Skybox.h \
    Pyramid.h \
    Text3d.h

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
