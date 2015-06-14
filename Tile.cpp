#include "Tile.h"

bool Tile::grid = false;
std::string Tile::imgPath = "./imgs/claim.png";
SDL_Rect* Tile::spriteClips[ 4 ];
SDL_Renderer* Tile::renderer;
Texture Tile::tTex, Tile::hl, Tile::grd;
int Tile::instances = 0;
int Tile::width = 30;
int Tile::height = 30;


//Color messing about

Tile::Tile(SDL_Renderer* rend, int x, int y)
{
	Tile(x, y);
	Tile::renderer = rend;
	setRenderer(rend);
}

Tile::Tile(int x, int y) : posX(x), posY(y), highlight(false), movement(false)
{
	//changeType(t);
	Tile::instances++;
	unit = NULL;
	
	a = 255 * .25;
	r[0] = 255;
	g[0] = 0;
	b[0] = 0;

	r[1] = 100;
	g[1] = 100;
	b[1] = 100;

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
	/*
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
	*/
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (movement)
	{
		tTex.setColor(r[2], g[2], b[2]);
		tTex.setAlpha(a);
		Tile::tTex.render(posX, posY);
		movement = false;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if(unit != NULL)
	{
		unit->render();
		if(unit->currentSpeed <= 0)
		{
			tTex.setColor(r[1], g[1], b[1]);
			tTex.setAlpha(255*.6);
			Tile::tTex.render(posX, posY);
		}
		//printf("IDK\n");
		/*
		unit->changeType(Unit::WORKER); 
		unit->setX(posX);
		unit->setX(posY);
		unit->render();
		*/
	}

	if(grid)
	{
		Tile::grd.render(posX, posY);
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
	grd.setRenderer(rend);
	grd.loadFromFile("./imgs/grid.png");
//	setClips();
	

}

/*
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
*/


Unit* Tile::getUnit()
{
	return unit;
}

Unit* Tile::addUnit(Unit* newUnit)
{
	Unit* temp = unit;
	if (newUnit != NULL)
	{
		unit = newUnit;
	}
	return temp;
}

Unit* Tile::removeUnit()
{
	Unit* temp = unit;
	unit = NULL;
	return temp;
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
/*
int Tile::changeType(int newType)
{
	int temp = type;
	type = newType;
	return temp;
}
*/
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
/*
int Tile::getType()
{
	return type;
}
*/
