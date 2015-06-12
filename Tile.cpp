#include "Tile.h"

std::string Tile::imgPath = "./imgs/claim.png", Tile::unitImgPath = "./imgs/unit_tileset.png";
SDL_Rect* Tile::spriteClips[ 4 ];
SDL_Renderer* Tile::renderer;
Texture Tile::tTex, Tile::hl, Tile::unit;
int Tile::instances = 0;
int Tile::width = 30;
int Tile::height = 30;


//Color messing about

Tile::Tile(int t, SDL_Renderer* rend, int x, int y)
{
	Tile(t, x, y);
	Tile::renderer = rend;
	setRenderer(rend);
}

Tile::Tile(int t, int x, int y) : posX(x), posY(y), troops(0), workers(0), 
									metals(0), oil(0), timber(0), 
									tMetals(std::rand()%4 + 1), tOil(std::rand()%4 + 1), tTimber(std::rand()%4 + 1),
									citySize(0), highlight(false), unitHere(false)
{
	changeType(t);
	Tile::instances++;
	a = 255 * .25;
	r[0] = 255;
	g[0] = 0;
	b[0] = 0;

	r[1] = 0;
	g[1] = 255;
	b[1] = 0;

	r[2] = 0;
	g[2] = 0;
	b[2] = 255;
	
	//productionCapacity = std::rand()%5 + 1;
}

Tile::~Tile()
{
	free();
}

void Tile::render()
{

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	if (getType() == TRIANGLE)
	{
		tTex.setColor(r[0], g[0], b[0]);
		tTex.setAlpha(a);
		Tile::tTex.render(posX, posY);
	}

	if (getType() == SQUARE)
	{
		tTex.setColor(r[1], g[1], b[1]);
		tTex.setAlpha(a);
		Tile::tTex.render(posX, posY);
	}

	if (getType() == PENTAGON)
	{
		tTex.setColor(r[2], g[2], b[2]);
		tTex.setAlpha(a);
		Tile::tTex.render(posX, posY);
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if (unitHere)
	{
		printf("IDK\n");
		/*unit->changeType(Unit::WORKER); 
		unit->setX(posX);
		unit->setX(posY);
		unit->render();*/
	}

	if(highlight)
	{
		Tile::hl.render(posX, posY);
	}

}

void Tile::setRenderer(SDL_Renderer* rend)
{
	Tile::tTex.setRenderer(rend);
}

void Tile::init(SDL_Renderer* rend)
{
	tTex.setRenderer(rend);
	tTex.loadFromFile(Tile::imgPath);
	hl.setRenderer(rend);
	hl.loadFromFile("./imgs/hl.png");
	unit.setRenderer(rend);
	unit.loadFromFile(Tile::unitImgPath);
	setClips();
	

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

bool Tile::handleEvent(SDL_Event* e)
{
	if(e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if(x > getX() && x < getX() + getWidth() &&
		   y > getY() && y < getY() + getHeight())
		{
			return true;
		}
	}
	return false;
}

int Tile::getType()
{
	return type;
}
