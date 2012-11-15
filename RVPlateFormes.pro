include(VRJuggler/VRJuggler.pri)
include(3DEntities/3DEntities.pri)
include(Abstract/Abstract.pri)

SOURCES += \
    main.cpp \
    Scene.cpp \
    Text2d.cpp \
    Skybox.cpp \
    Text3d.cpp

HEADERS += \
    Constants.h \
    Scene.h \
    Text2d.h \
    Skybox.h \
    Text3d.h \
    Utils.h \
    MyMatrixf.h

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
