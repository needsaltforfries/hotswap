FLAGS = -Wall -shared -fPIC
TIMESTAMP := $(shell powershell -Command "[System.DateTime]::Now.ToString('yyyyMMddHHmmss')")
SRC = $(wildcard ./src/*.cpp) $(wildcard ./src/visualizer/*.cpp) ./src/glad.c main.cpp
LIBSRC = $(wildcard ./src/assets/*.cpp)
LIBS = -lglfw3 -lglfw3dll -lgdi32
INCLUDE_PATH = ./include/
TARGET = a.exe

default: compile run

build:
# 	@if exist gamelib.dll del gamelib.dll
	g++ $(FLAGS) -o gamelib_$(TIMESTAMP).dll $(LIBSRC)
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