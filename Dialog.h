#pragma once
#ifndef DIALOG_H
#define DIALOG_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Texture.h"
#include "Tile.h"
#include "Window.h"

class Dialog : public Window
{
	public:
		typedef Window super;
		void init();
		void setTile(Tile* t);
		int handleEvent( SDL_Event& e );
		void render();
		void free();
		Tile* getTile();
//		int transferT;
//		int transferW;
//		void clearTrans();
	private:
		Tile* thisTile;
		SDL_Rect *statusClip, *statusClip2; //*tt, *tw;
		Texture *compass, *background; // *arrows; //This will be used to command units to move around I guess
};

#endif