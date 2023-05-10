OBJS = $(wildcard *.cpp)
OBJ_NAME = main.exe
COMPILER_FLAGS = -std=c++17
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
INCLUDE_DIR = -IC:\Users\khuatduchoa\Documents\SDL\SDL2-2.26.3\x86_64-w64-mingw32\include\SDL2
LIB_DIR = -LC:\Users\khuatduchoa\Documents\SDL\SDL2-2.26.3\x86_64-w64-mingw32\lib
compile:
	g++ $(COMPILER_FLAGS) $(INCLUDE_DIR) $(LIB_DIR) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)