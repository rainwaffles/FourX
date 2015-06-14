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
	enum UnitType
	{
		RSOLDIER,
		RWORKER,
		BSOLDIER,
		BWORKER,
		NONE
	};	
	
	Unit();
	Unit(UnitType t, SDL_Renderer* rend, int x, int y);
	Unit(UnitType t, int x, int y);

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


	void newTurn();

	static void setClips();



	std::string name;

	UnitType oppType();
	int fight(Unit *enemy);
	UnitType getType();
	UnitType changeType(UnitType newType);

	int health;
	int maxHealth;
	int power;
	int speed;
	int currentSpeed;

private:
	static std::string imgPath;
	static SDL_Rect* spriteClips[ 4 ];
	static Texture tTex;
	static int instances;
//	static SDL_Renderer* renderer;

	int posX, posY;
	static int width, height;
	UnitType type;

	Uint8 r[3], g[3], b[3], a;
};

#endif