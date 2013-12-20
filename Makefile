# Le nom de l'application
APP = RVPlateformes

# La liste des fichiers à compiler
SRC = main.cpp Text2d.cpp 3DEntities/Platform.cpp 3DEntities/Ball.cpp 3DEntities/Pyramid.cpp Abstract/ModuleRegistry.cpp Abstract/Controller.cpp Abstract/SDLWindow.cpp Abstract/Module.cpp Abstract/SDLInputStrategy.cpp Abstract/InputManager.cpp Text3d.cpp Scene.cpp VRJuggler/OsgNav.cpp Skybox.cpp

OBJ = $(SRC:.cpp=.o)

# Les options de compilation + répertoire des .h
CXXFLAGS += -m32
CXXFLAGS += -g -Wall -fexceptions -pthread -Wall -DHAVE_CONFIG_H -DJUGGLER_DEBUG -Wno-deprecated
CXXFLAGS += -I${VJ_BASE_DIR}/include/
CXXFLAGS += -I${VJ_BASE_DIR}/include/vrjuggler-2.2/
CXXFLAGS += -I${VJ_BASE_DIR}/include/gadgeteer-1.2/
CXXFLAGS += -I${VJ_BASE_DIR}/include/jccl-1.2/
CXXFLAGS += -I${VJ_BASE_DIR}/include/vpr-2.0/
CXXFLAGS += -I${VJ_BASE_DIR}/include/cppdom-0.7.10/
CXXFLAGS += -I${VJ_BASE_DIR}/include/gmtl-0.5.4/
CXXFLAGS += -I/net/bonne/exports/users/jeconc/Téléchargements/bullet-install/include/bullet/
#CXXFLAGS += -I${FMODROOT}/inc

# Les options d'édition des liens + répertoires et noms des .so
LDFLAGS += -m32
LDFLAGS += -L$(VJ_BASE_DIR)/lib -lvrj-2_2 -lvrj_ogl-2_2 -lgadget-1_2 -ljccl-1_2 -lvpr-2_0
LDFLAGS += -losg -losgDB -losgUtil -lOpenThreads
LDFLAGS += -lGLU -lGL -lm -losgGA -losgViewer -losgText -L/net/bonne/exports/users/jeconc/Téléchargements/bullet-install/lib -lBulletDynamics -lBulletCollision -lLinearMath
#LDFLAGS += -L$(FMODROOT)/lib -lfmodex

# ( pour linker avec ${HOME}/plib/libplibssg.so et ${HOME}/plib/libplibnet.so
#   on ajoutera "-L${HOME}/plib -lplibssg  -lplibnet" )

def:
	. site_init_vj2.2.0.sh; make $(APP)

$(APP) : $(OBJ)
	$(CXX) $(LDFLAGS) -o $(APP) $(OBJ)

#include Dep.mk
#dep:
#	$(CXX) -MM -MG $(SRC) >Dep.mk

clean:
	-\find . -name '*.o' | xargs rm && rm $(APP)

run:
	. site_init_vj2.2.0.sh; ./$(APP) standalone.jconf
sim:
	startSIM ./$(APP)
cave:
	startCAVE ./$(APP)
