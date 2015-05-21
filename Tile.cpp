#include "Tile.h"

std::string Tile::imgPath = "./imgs/tiles.png";
SDL_Rect* Tile::spriteClips[ 4 ];
Texture Tile::tTex;
int Tile::instances = 0;
int Tile::width = 30;
int Tile::height = 30;


Tile::Tile(int t, SDL_Renderer* rend, int x, int y) : posX(x), posY(y)
{
	setRenderer(rend);
	changeType(t);
	Tile::instances++;
}

Tile::Tile(int t, int x, int y) : posX(x), posY(y)
{
	Tile(t, NULL, x, y);
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
	Tile::spriteClips[UNCLAIMED] = new SDL_Rect();
	Tile::spriteClips[UNCLAIMED]->x = 90;
	Tile::spriteClips[UNCLAIMED]->y = 0;
	Tile::spriteClips[UNCLAIMED]->w = 30;
	Tile::spriteClips[UNCLAIMED]->h = 30;

	Tile::spriteClips[TRIANGLE] = new SDL_Rect();
	Tile::spriteClips[TRIANGLE]->x = 60;
	Tile::spriteClips[TRIANGLE]->y = 0;
	Tile::spriteClips[TRIANGLE]->w = 30;
	Tile::spriteClips[TRIANGLE]->h = 30;
	
	Tile::spriteClips[SQUARE] = new SDL_Rect();
	Tile::spriteClips[SQUARE]->x = 0;
	Tile::spriteClips[SQUARE]->y = 0;
	Tile::spriteClips[SQUARE]->w = 30;
	Tile::spriteClips[SQUARE]->h = 30;
	
	Tile::spriteClips[PENTAGON] = new SDL_Rect();
	Tile::spriteClips[PENTAGON]->x = 30;
	Tile::spriteClips[PENTAGON]->y = 0;
	Tile::spriteClips[PENTAGON]->w = 30;
	Tile::spriteClips[PENTAGON]->h = 30;
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

void Tile::handleEvent(SDL_Event* e)
{
	if(e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if(x > posX && x < posX + width &&
		   y > posY && y < posY + height)
		{
			printf("CLICKED\n");
		}
	}
}