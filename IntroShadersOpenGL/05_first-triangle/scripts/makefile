PROJECT := Triangle.exe
SRC_DIR := ../src
BUILD_DIR := ../build
OBJ_DIR := ../build/obj
EXT_DIR := ../external

SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBRAIRIES := -lSDL2main -lSDL2 -lSDL2_image -lglew32 -lzlib1 -lopengl32

INCLUDE :=-I$(EXT_DIR)\SDL2-2.0.12\include \
	-I$(EXT_DIR)\SDL2_image-2.0.5\include \
	-I$(EXT_DIR)\glew-2.1.0\include

LIB :=-L$(EXT_DIR)\SDL2-2.0.12\lib\x64 \
	-L$(EXT_DIR)\SDL2_image-2.0.5\lib\x64 \
	-L$(EXT_DIR)\glew-2.1.0\lib\Release\x64

all: $(PROJECT)

$(PROJECT): $(OBJ_FILES)
	g++ -g -o $(BUILD_DIR)\$@ $^ $(LIB) $(LIBRAIRIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -Wall -Wextra -pedantic -c -o $@ $< $(INCLUDE) 
