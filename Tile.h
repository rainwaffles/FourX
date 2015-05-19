#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.h"

class Tile
{
	public:
		Tile(int x, int y, int t);
		~Tile();

	private:
		Texture tTex;
		int posX, posY;
		int type;
		/*
			0: Unclaimed
			1: Triangle
			2: Square
			3: Pentagon
		*/
}