#pragma once
#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.h"

class Tile
{
	public:
		//Constructor 
		Tile(int t, SDL_Renderer* rend, int x, int y);
		Tile(int t, int x, int y);
		//Deconstuctor (just calls free())
		~Tile();

		//Renders with the renderer the tile on the right X and Y
		void render();
		static void init(SDL_Renderer* rend);
		static void setRenderer(SDL_Renderer* rend);

		//Deallocates all the stuff that should be deallocated, ie. texture
		void free();

		//Gets image dimensions
		int getWidth();
		int getHeight();

		//Gets location
		int getX();
		int getY();

		//Changes type, to be used when a tile is conquered
		int changeType(int newType);

		//Takes in an SDL event and processes it.
		void handleEvent(SDL_Event* e);

		static void setClips();

		/*
			This is where we add other stuff that determine the composition of a tile, 
			such as terrain, units, income, resources, ect. 
		*/

		enum TileType
		{
			UNCLAIMED,
			TRIANGLE,
			SQUARE,
			PENTAGON
		};

	private:
		static std::string imgPath;
		static SDL_Rect* spriteClips[ 4 ];
		static Texture tTex;
		static int instances;

		int posX, posY;
		static int width, height;
		int type;
		/*
			0: Unclaimed
			1: Triangle
			2: Square
			3: Pentagon
		*/
};

#endif