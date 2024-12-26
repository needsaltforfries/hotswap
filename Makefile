FLAGS = -Wall -shared -fPIC
LIBS = -lglfw3 -lglfw3dll -lgdi32
INCLUDE_PATH = ./include/
TARGET = a.exe
TIMESTAMP := $(shell powershell -Command "[System.DateTime]::Now.ToString('yyyyMMddHHmmss')")
OBJSRC = $(wildcard ./src/assets/objects/*.cpp)
GAMESRC = ./src/Game.cpp ./src/GameHeader.cpp ./src/assets/GameObject.cpp
OBJ_OUT = objectslib.dll
OBJ_LIB = -lobjectslib

SRC := $(wildcard ./src/*.cpp) $(wildcard ./src/visualizer/*.cpp)
SRC := main.cpp ./src/glad.c $(filter-out $(OBJSRC) $(GAMESRC), $(SRC))

default: compile run

build_all: build_obj build

build_obj:
	g++ $(FLAGS) -I $(INCLUDE_PATH) $(OBJSRC) -o $(OBJ_OUT)
build:
	g++ $(FLAGS) -I $(INCLUDE_PATH) $(GAMESRC) -o gamelib_$(TIMESTAMP).dll
	move gamelib_$(TIMESTAMP).dll gamelib.dll

compile:
	g++ -Wall -I $(INCLUDE_PATH) $(SRC) -L ./lib/ $(LIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	@if exist gen\gamelib_cpy.dll del gen\gamelib_cpy.dll
	@for %%f in (gamelib_*.dll) do del %%f
	@if exist gamelib.dll del gamelib.dll
	@if exist a.exe del a.exe