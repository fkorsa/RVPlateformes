include(InputManager/InputManager.pri)
include(Window/Window.pri)

SOURCES += \
    main.cpp \
    Controller.cpp \
    ModuleRegistry.cpp \
    Module.cpp \
    Scene.cpp

HEADERS += \
    Controller.h \
    Constants.h \
    ModuleRegistry.h \
    Module.h \
    Scene.h


# SDL
LIBS += -L/usr/lib -lSDL -lSDL_image -lSDL_ttf
LIBS += -L/usr/lib -losg -losgUtil -losgDB -losgGA -losgViewer
INCLUDEPATH = /usr/include/SDL


# BULLET
LIBS += -L/usr/local/lib/ -lBulletDynamics -lBulletCollision -lLinearMath
INCLUDEPATH += /usr/local/include/bullet

# OSGBULLET
LIBS += -L/usr/local/lib/ -losgbDynamics -losgbCollision -losgbInteraction
LIBS += -L/usr/local/lib64/ -lOpenThreads
