#include "Tile.h"

std::string Tile::imgPath = "./imgs/tiles.png";
SDL_Rect* Tile::spriteClips[ 4 ];
Texture Tile::tTex;
int Tile::instances = 0;

Tile::Tile(int t, SDL_Renderer* rend, int x, int y) : posX(x), posY(y)
{
	setRenderer(rend);
	changeType(t);
	Tile::instances++;
}

Tile::Tile(int t, int x, int y) : posX(x), posY(y)
{
	if(instances <= 0) { setRenderer(NULL); }
	changeType(t);
	Tile::instances++;
}

Tile::~Tile()
{
	free();
}

void Tile::render()
{
	Tile::tTex.render(posX, posY, spriteClips[type]);
}

void Tile::setRenderer(SDL_Renderer* rend)
{
	Tile::tTex.setRenderer(rend);
	if(Tile::instances <= 0 || !Tile::tTex.hasTex())
	{
		Tile::tTex.loadFromFile(imgPath);
		setClips();
	}
}

void Tile::setClips()
{
	Tile::spriteClips[3] = new SDL_Rect();
	Tile::spriteClips[3]->x = 30;
	Tile::spriteClips[3]->y = 0;
	Tile::spriteClips[3]->w = 30;
	Tile::spriteClips[3]->h = 30;

	Tile::spriteClips[1] = new SDL_Rect();
	Tile::spriteClips[1]->x = 60;
	Tile::spriteClips[1]->y = 0;
	Tile::spriteClips[1]->w = 30;
	Tile::spriteClips[1]->h = 30;
	
	Tile::spriteClips[0] = new SDL_Rect();
	Tile::spriteClips[0]->x = 90;
	Tile::spriteClips[0]->y = 0;
	Tile::spriteClips[0]->w = 30;
	Tile::spriteClips[0]->h = 30;
	
	Tile::spriteClips[2] = new SDL_Rect();
	Tile::spriteClips[2]->x = 0;
	Tile::spriteClips[2]->y = 0;
	Tile::spriteClips[2]->w = 30;
	Tile::spriteClips[2]->h = 30;
}


void Tile::free()
{
	instances--;
	if(instances <= 0)
	{
		Tile::tTex.free();
		for(int i = 0; i < 4; i++)
		{
			delete Tile::spriteClips[i];
		}
	}
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