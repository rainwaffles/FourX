#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.h"

class Unit
{
public:
	//Constructor
	Unit();
	Unit(int t, SDL_Renderer* rend, int x, int y);
	Unit(int t, int x, int y);

	//Deconstructor, calls free()
	~Unit();

	void render();
	static void init(SDL_Renderer* rend);
	static void setRenderer(SDL_Renderer* rend);

	void free();

	int getWidth();
	int getHeight();

	int getX();
	int getY();

	int setX(int newX);
	int setY(int newY);

	int changeType(int newType);

	int getType();

	static void setClips();

	enum UnitType
	{
		SOLDIER,
		WORKER
	};

	int health;

private:
	static std::string imgPath;
	static SDL_Rect* spriteClips[ 2 ];
	static Texture tTex;
	static int instances;
	static SDL_Renderer* renderer;

	int posX, posY;
	static int width, height;
	int type;

	Uint8 r[3], g[3], b[3], a;
};

#endif