# Version 2/28/16

all: fourx

fourx:
	g++ --std=c++11 -Wall -ggdb ./Dialog.cpp ./Map.cpp ./Texture.cpp ./Tile.cpp ./Unit.cpp ./Window.cpp ./Main.cpp -o fourx -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -f ./fourx
