# Version 2/28/16

all: fourx

fourx:
	g++ --std=c++11 -Wall -ggdb ./src/Dialog.cpp ./src/Map.cpp ./src/Texture.cpp ./src/Tile.cpp ./src/Unit.cpp ./src/Window.cpp ./src/Main.cpp -o fourx -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -f ./fourx
