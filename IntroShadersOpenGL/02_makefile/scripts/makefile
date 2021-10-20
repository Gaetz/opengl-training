PROJECT := hello.exe
SRC_DIR := ../src
BUILD_DIR := ../build
OBJ_DIR := ../build/obj
EXT_DIR := ../external

SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(PROJECT)

$(PROJECT): $(OBJ_FILES)
	g++ -g -o $(BUILD_DIR)\$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -Wall -Wextra -pedantic -c -o $@ $<
