#pragma once
#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Texture.h"
#include "Dialog.h"
#include "Tile.h"
#include "Window.h"

class Map : public Window
{
	public:
		typedef Window super;
		bool init();
		Tile* handleEvent( SDL_Event& e );
		void render();
		bool close;
		void free();
		void renderStatus();
		void transfer(int t, int w, Tile *tile, int dir);
		Tile* get(Tile* t, int dir);

	protected:
		static const int TILES_X = 30;
		static const int TILES_Y = 20;
		static const int TILE_SIZE_X = 30;
		static const int TILE_SIZE_Y = 30;
		static const int SCREEN_WIDTH = TILES_X*TILE_SIZE_X;
		static const int SCREEN_HEIGHT = TILES_Y*TILE_SIZE_Y + TILE_SIZE_Y;
		Tile *tiles[TILES_X][TILES_Y];
		SDL_Rect* statusClip;

	private:
		static std::string imgPath;
		static Texture background;
		static SDL_Rect* backrect;

};

#endif