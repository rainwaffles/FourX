#include "Unit.h"
#include <iostream>

std::string Unit::imgPath = "./imgs/units.png";
SDL_Rect* Unit::spriteClips[4];
//SDL_Renderer* Unit::renderer;
Texture Unit::tTex;
int Unit::instances = 0;
int Unit::width = 30;
int Unit::height = 30;


Unit::Unit()
{
	Unit(0, 0, 0);
}

Unit::Unit(int t, SDL_Renderer* rend, int x, int y)
{
	Unit(t, x, y);
//	Unit::renderer = rend;

	setRenderer(rend);
}

Unit::Unit(int t, int x, int y) : posX(x), posY(y), health(0), power(0), speed(0), currentSpeed(0), name("")
{
	changeType(t);
	Unit::instances++;
}

Unit::~Unit()
{
	free();
}

void Unit::render()
{
//	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if (getType() == RSOLDIER)
	{
		Unit::tTex.render(posX, posY, spriteClips[RSOLDIER]);
	}

	if (getType() == RWORKER)
	{
		Unit::tTex.render(posX, posY, spriteClips[RWORKER]);
	}

}

void Unit::setRenderer(SDL_Renderer* rend)
{
	Unit::tTex.setRenderer(rend);
}

void Unit::init(SDL_Renderer* rend)
{
	tTex.setRenderer(rend);
	tTex.loadFromFile(Unit::imgPath);
	setClips();
}

void Unit::setClips()
{
	Unit::spriteClips[BSOLDIER] = new SDL_Rect();
	Unit::spriteClips[BSOLDIER]->x = 0;
	Unit::spriteClips[BSOLDIER]->y = 0;
	Unit::spriteClips[BSOLDIER]->w = 30;
	Unit::spriteClips[BSOLDIER]->h = 30;

	Unit::spriteClips[BWORKER] = new SDL_Rect();
	Unit::spriteClips[BWORKER]->x = 30;
	Unit::spriteClips[BWORKER]->y = 0;
	Unit::spriteClips[BWORKER]->w = 30;
	Unit::spriteClips[BWORKER]->h = 30;
	
	Unit::spriteClips[RSOLDIER] = new SDL_Rect();
	Unit::spriteClips[RSOLDIER]->x = 30;
	Unit::spriteClips[RSOLDIER]->y = 0;
	Unit::spriteClips[RSOLDIER]->w = 30;
	Unit::spriteClips[RSOLDIER]->h = 30;

	Unit::spriteClips[RWORKER] = new SDL_Rect();
	Unit::spriteClips[RWORKER]->x = 35;
	Unit::spriteClips[RWORKER]->y = 30;
	Unit::spriteClips[RWORKER]->w = 30;
	Unit::spriteClips[RWORKER]->h = 30;

}

void Unit::free()
{
	instances--;
	if (instances <= 0)
	{
		Unit::tTex.free();
		for (int i = 0; i < 2; i++)
		{
			delete Unit::spriteClips[i];
		}
	}
}


int Unit::getWidth()
{
	return width;
}

int Unit::getHeight()
{
	return height;
}

int Unit::setX(int newX)
{

	int temp = posX;
	posX = newX;

	return temp;
}

int Unit::getX()
{
	return posX;
}

int Unit::setY(int newY)
{
	int temp = posY;
	posY = newY;
	return temp;
}

int Unit::getY()
{
	return posY;
}

void Unit::newTurn()
{
	Unit::currentSpeed = speed;
}

int Unit::changeType(int newType)
{
	int temp = type;
	type = newType;


	switch (type)
	{
	case RSOLDIER:
		health = 3;
		power = 3;
		speed = 2;
		name = "Red Soldier";
		break;
	case BSOLDIER:
		health = 3;
		power = 3;
		speed = 2;
		name = "Blue Soldier";
		break;
	}

	return temp;

}

int Unit::getType()
{
	return type;
}