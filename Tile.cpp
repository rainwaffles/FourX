#include "Tile.h"

Tile::Tile(int t, SDL_Renderer* rend, int x, int y) : type(t), tTex(rend), posX(x), posY(y)
{

}

Tile::~Tile()
{

}

int Tile::render()
{

}

void Tile::setRenderer(SDL_Renderer* rend)
{

}

void Tile::free()
{

}

int Tile::getWidth()
{

}

int Tile::getHeight()
{

}

int Tile::getX()
{

}

int Tile::getY()
{

}

int Tile::changeType(int newType)
{

}