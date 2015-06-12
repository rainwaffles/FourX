#include "Unit.h"
#include <iostream>

std::string Unit::imgPath = "./imgs/unit_tileset.png";
SDL_Rect* Unit::spriteClips[2];
SDL_Renderer* Unit::renderer;
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
	Unit::renderer = rend;
	setRenderer(rend);
}

Unit::Unit(int t, int x, int y) : posX(x), posY(y)
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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);



	if (getType() == SOLDIER)
	{
		Unit::tTex.render(posX, posY, spriteClips[SOLDIER]);
	}

	if (getType() == WORKER)
	{
		printf("%d type\n", getType());
		Unit::tTex.render(posX, posY);
		Unit::tTex.render(posX, posY, spriteClips[WORKER]);
	}

}

void Unit::setRenderer(SDL_Renderer* rend)
{
	Unit::tTex.setRenderer(rend);
}

void Unit::init(SDL_Renderer* rend)
{
	printf("Hello\n");
	tTex.setRenderer(rend);
	printf("Jk\n");
	tTex.loadFromFile(Unit::imgPath);
	setClips();
}

void Unit::setClips()
{
	Unit::spriteClips[SOLDIER] = new SDL_Rect();
	Unit::spriteClips[SOLDIER]->x = 116;
	Unit::spriteClips[SOLDIER]->y = 98;
	Unit::spriteClips[SOLDIER]->w = 85;
	Unit::spriteClips[SOLDIER]->h = 85;

	Unit::spriteClips[WORKER] = new SDL_Rect();
	Unit::spriteClips[WORKER]->x = 560;
	Unit::spriteClips[WORKER]->y = 0;
	Unit::spriteClips[WORKER]->w = 80;
	Unit::spriteClips[WORKER]->h = 90;

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
	posY = newX;
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

int Unit::changeType(int newType)
{
	int temp = type;
	type = newType;
	return temp;
}

int Unit::getType()
{
	return type;
}