APP_BIN = MetalShadowWars



CC = gcc

CXX = g++

CCFLAGS = -Wall -g -std=c11

CXXFLAGS = -Wall -g -std=c++11

LDFLAGS  = -lm

INC_FLAGS = -I./include

SRC_PATH = .

OBJ_PATH = obj

BIN_PATH = bin

LIB_PATH = lib

SDL_PATH =

GLUT_PATH =

GL_PATH =

SDL = SDL

# SDL = SDL2



ECHO_CMD = echo

SLASH = /



ifneq ($(SDL_PATH),)

	LDFLAGS += -L$(SDL_PATH)/lib

	INC_FLAGS += -I$(SDL_PATH)/include

	# BIN_FLAGS +=

endif

ifneq ($(GLUT_PATH),)

	LDFLAGS += -L$(GLUT_PATH)/lib

	INC_FLAGS += -I$(GLUT_PATH)/include

	# BIN_FLAGS +=

endif

ifneq ($(GL_PATH),)

	LDFLAGS += -L$(GL_PATH)/lib

	INC_FLAGS += -I$(GL_PATH)/include

	# BIN_FLAGS +=

endif



ifeq ($(OS),Windows_NT)

	SDL_FLAGS = -lmingw32 -l$(SDL)main -l$(SDL)

	GL_FLAGS = -lopengl32 -lglu32 -lfreeglut

	IF_N_EXIST = if not exist

	OBJ_FILES2 = $(subst /,\, $(OBJ_FILES))

	CLEAN_CMD = for %%x in ($(OBJ_FILES2)) do (if exist %%x (del /q %%x))

	CCFLAGS += -D WIN32

	CXXFLAGS += -D WIN32

	# CXX = x86_64-w64-mingw32-g++

else

    IF_N_EXIST = if [ ! -d

    THEN = ]; then

    ENDIF =; fi



	SDL_FLAGS = -l$(SDL)

	GL_FLAGS = -lGL -lGLU

	CCFLAGS += -D LINUX

	CXXFLAGS += -D LINUX



    ifeq ($(shell uname),Darwin)

		INC_FLAGS += -I/opt/local/include

		INC_FLAGS += -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers

		LDFLAGS += `sdl-config --libs` `sdl-config --cflags`

		LDFLAGS += -framework Cocoa -framework OpenGL -lSDL_image -lSDL_mixer -lSDL_ttf -lglut

		CCFLAGS += -D OSX

		CXXFLAGS += -D OSX

    endif

    CLEAN_CMD = rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)

endif



SRC_FILES = $(wildcard $(SRC_PATH)/*.cpp) $(wildcard $(SRC_PATH)/*/*.cpp)

OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC_FILES))

LDFLAGS += $(SDL_FLAGS) $(GL_FLAGS) -l$(SDL)_image -l$(SDL)_mixer -l$(SDL)_ttf





all: $(BIN_PATH) $(OBJ_PATH) $(OBJ_FILES)

	@echo "Building $(APP_BIN)"

	$(CXX)  $(CXXFLAGS) $(INC_FLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(BIN_PATH)/$(APP_BIN)

	@echo "$(APP_BIN) has been created"



$(OBJ_PATH):

	@echo "------------Make directory $<---------------------"

	$(IF_N_EXIST) "$(OBJ_PATH)" $(THEN) mkdir "$(OBJ_PATH)" $(ENDIF)



$(BIN_PATH):

	@echo "------------Make directory $<---------------------"

	$(IF_N_EXIST) "$(BIN_PATH)" $(THEN) mkdir "$(BIN_PATH)" $(ENDIF)



$(OBJ_PATH)$(SLASH)%.o: $(SRC_PATH)$(SLASH)%.cpp $(OBJ_PATH)

	@echo "------------COMPILATION $< -> $@---------------------"

	$(IF_N_EXIST) "$(@D)" $(THEN) mkdir "$(@D)" $(ENDIF)

	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@





clean:

	$(CLEAN_CMD)
