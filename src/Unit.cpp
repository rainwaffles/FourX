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
	Unit(NONE, 0, 0);
}

Unit::Unit(UnitType t, SDL_Renderer* rend, int x, int y)
{
	Unit(t, x, y);
//	Unit::renderer = rend;

	setRenderer(rend);
}

Unit::Unit(UnitType t, int x, int y) : posX(x), posY(y), health(0), power(0), speed(0), currentSpeed(0), name("")
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
	Unit::tTex.render(posX, posY, spriteClips[getType()]);
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

Unit::UnitType Unit::changeType(UnitType newType)
{
	UnitType temp = type;
	type = newType;

	switch (type)
	{
	case RSOLDIER:
		maxHealth = 46 + std::rand()%6;
		power = 10;
		speed = 3;
		name = "Red Soldier";
		break;
	case BSOLDIER:
		maxHealth = 39 + std::rand()%4;
		power = 12;
		speed = 3 + std::rand()%2;
		name = "Blue Soldier";
		break;
	}
	health = maxHealth;
	
	return temp;

}

Unit::UnitType Unit::getType()
{
	return type;
}

Unit::UnitType Unit::oppType()
{
	if(getType() == RSOLDIER){return BSOLDIER;}
	if(getType() == BSOLDIER){return RSOLDIER;}
	return NONE;
}

int Unit::fight(Unit *enemy)
{
	/*
	1: win
	0: tie
	-1: loss
	*/
	enemy->health -= power + std::rand()%3;
	if(enemy->health <= 0){return 1;}
	health -= enemy->power + std::rand()%3;
	if(health <= 0){return -1;}
	return 0;
}