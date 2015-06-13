#pragma once
#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.h"
#include "Unit.h"

class Tile
{
	public:
		//Constructor 
		Tile(SDL_Renderer* rend, int x, int y);
		Tile(int x, int y);
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
//		int changeType(int newType);

		//Takes in an SDL event and processes it.
		bool handleEvent(SDL_Event* e);

//		int getType();

		
//		static void setClips();

		/*
			This is where we add other stuff that determine the composition of a tile, 
			such as terrain, units, income, resources, ect. 
		*/
/*
		enum TileType
		{
			UNCLAIMED,
			TRIANGLE,
			SQUARE,
			PENTAGON
		};
*/
/*
		enum UnitType
		{
			TROOPER,
			WORKERS
		};
*/
//		int troops;
//		int workers;
/*
		//These represent production levels for now
		int metals;
		int oil;
		int timber;

		int tMetals;
		int tOil;
		int tTimber;

		int citySize;
*/
		Unit *unit;

		Unit* getUnit();
		Unit* addUnit(Unit* newUnit);
		Unit* removeUnit();

		bool highlight;

		static bool grid;
//		int type;

	private:
		static std::string imgPath;
		static SDL_Rect* spriteClips[ 4 ], unitClips[ 2 ];
		static Texture tTex, hl, grd;
		static int instances;
		static SDL_Renderer* renderer;


		int posX, posY;
		static int width, height;

//		Uint8 r[ 3 ], g[ 3 ], b[ 3 ], a;
};

#endif