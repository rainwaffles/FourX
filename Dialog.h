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
		void setTile(Tile* t);
		void render();
	private:
		Tile* thisTile;
		static TTF_Font* gFont;
		static SDL_Color textColor;
};

#endif