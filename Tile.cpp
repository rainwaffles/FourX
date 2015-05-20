#include "Tile.h"

Tile::Tile(int t, SDL_Renderer* rend, int x, int y) : tTex(rend), posX(x), posY(y)
{
	changeType(t);
}

Tile::~Tile()
{
	free();
}

void Tile::render()
{
	tTex.render(posX, posY);
}

void Tile::setRenderer(SDL_Renderer* rend)
{
	tTex.setRenderer(rend);
}

void Tile::free()
{
	tTex.free();
}

int Tile::getWidth()
{
	return width;
}

int Tile::getHeight()
{
	return height;
}

int Tile::getX()
{
	return posX;
}

int Tile::getY()
{
	return posY;
}

int Tile::changeType(int newType)
{
	int temp = type;
	type = newType;
	return temp;
}