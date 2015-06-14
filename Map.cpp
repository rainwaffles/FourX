#include "Map.h"

std::string Map::imgPath = "./imgs/background.png";
Texture Map::background;
SDL_Rect* Map::backrect;
int Map::turnCount = -1; //Blue goes first

bool Map::init()
{
	//Create window
	mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( mWindow != NULL )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( mRenderer == NULL )
		{
			SDL_DestroyWindow( mWindow );
			mWindow = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Grab window identifier
			mWindowID = SDL_GetWindowID( mWindow );

			//Flag as opened
			mShown = true;
		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}
	Tile::init(mRenderer);
	background.setRenderer(mRenderer);
	background.loadFromFile(imgPath);
	
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			if(i + j < 5)
			{
				tiles[i][j] = new Tile(i*TILE_SIZE_X, j*TILE_SIZE_Y + TILE_SIZE_Y);
//				tiles[i][j]->troops = 2;
//				tiles[i][j]->workers = 2;
			}
			else {tiles[i][j] = new Tile(i*TILE_SIZE_X, j*TILE_SIZE_Y + TILE_SIZE_Y);}
		}
	}
	close = false;

	int tempX = (TILES_X - 1);
	int tempY = (TILES_Y - 1);
	tiles[tempX][tempY]->unit = new Unit(Unit::RSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);
	tiles[tempX][tempY]->unit->init(mRenderer);


	tempX = (TILES_X - 1) - 1;
	tempY = (TILES_Y - 1) - 1;
	tiles[tempX][tempY]->unit = new Unit(Unit::RSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);

	tempX = (TILES_X - 1) - 1;
	tempY = (TILES_Y - 1);
	tiles[tempX][tempY]->unit = new Unit(Unit::RSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);

	tempX = (TILES_X - 1);
	tempY = (TILES_Y - 1) - 1;
	tiles[tempX][tempY]->unit = new Unit(Unit::RSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);

	tempX = 0;
	tempY = 0;
	tiles[tempX][tempY]->unit = new Unit(Unit::BSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);

	tempX = 0;
	tempY = 1;
	tiles[tempX][tempY]->unit = new Unit(Unit::BSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);
	
	tempX = 1;
	tempY = 0;
	tiles[tempX][tempY]->unit = new Unit(Unit::BSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);
	
	tempX = 1;
	tempY = 1;
	tiles[tempX][tempY]->unit = new Unit(Unit::BSOLDIER, tempX*TILE_SIZE_X, tempY*TILE_SIZE_Y + TILE_SIZE_Y);


	Map::backrect = new SDL_Rect();
	Map::backrect->h = 1200;
	Map::backrect->w = 1200; 
	Map::backrect->x = 0;
	Map::backrect->y = 0;

	statusClip = new SDL_Rect();
	statusClip->h = TILE_SIZE_Y;
	statusClip->w = SCREEN_WIDTH;
	statusClip->x = 0;
	statusClip->y = 0;
	return mWindow != NULL && mRenderer != NULL;
}

void Map::render()
{
	SDL_RenderClear( mRenderer );
	
	Map::background.render(0, 0, backrect);
	
	renderStatus();
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			tiles[i][j]->render();
		}
	}
	SDL_RenderPresent( mRenderer );
	update = false;
}

/*
void Map::transfer(int t, int w, Tile *tile, int dir)
{
	Tile *t1 = get(tile, dir);
	if(t1 == NULL) {return;}
	if(t1->type == tile->type)
	{
		tile->troops -= t;
		tile->workers -= w;
		t1->troops += t;
		t1->workers += w;
	}
	else if(t1->troops < tile->troops)
	{
		t1->troops = tile->troops - t1->troops;
		t1->workers += w;
		tile->troops -= t;
		tile->workers -= w;
		t1->type = tile->type;
	}
}
*/

Tile* Map::get(Tile* tile, int dir)
{
	Tile *t1 = NULL;
	if(tile->getX() <= 0 && dir == 4){return t1;}
	if(tile->getX() >= SCREEN_WIDTH - TILE_SIZE_X && dir == 2){return t1;}
	if(tile->getY() <= TILE_SIZE_Y && dir == 1){return t1;}
	if(tile->getY() >= SCREEN_HEIGHT - TILE_SIZE_Y && dir == 3){return t1;}
	switch(dir)
	{
	case 1:
		t1 = tiles[tile->getX()/tile->getWidth()][(tile->getY() - 2*tile->getHeight())/tile->getHeight()];
		break;
	case 2:
		t1 = tiles[(tile->getX() + tile->getWidth())/tile->getWidth()][(tile->getY() - tile->getHeight())/tile->getHeight()];
		break;
	case 3:
		t1 = tiles[tile->getX()/tile->getWidth()][(tile->getY())/tile->getHeight()];
		break;
	case 4:
		t1 = tiles[(tile->getX() - tile->getWidth())/tile->getWidth()][(tile->getY() - tile->getHeight())/tile->getHeight()];
		break;
	}
	return t1;
}

void Map::nextTurn()
{
	turnCount++;
//	printf("%d\n", turnCount);

	for (int i = 0; i < TILES_X; i++)
	{
		for (int j = 0; j < TILES_Y; j++)
		{
			Unit* unit = tiles[i][j]->getUnit();
			if (unit != NULL && unit->getType() == static_cast<Unit::UnitType>(Map::turnCount%2))
			{
				unit->newTurn();
			}
		}
	}
}

void Map::renderStatus()
{
	std::stringstream tmp;
	tmp << "Turn: " << turnCount;
	if(Window::gFont == NULL){Window::gFont = TTF_OpenFont( "./fonts/BOOTERFF.ttf", 100 );}
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_Surface* textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	statusClip->w = (textSurface->w / textSurface->h) * TILE_SIZE_Y;
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, statusClip );
}

Tile* Map::handleEvent(SDL_Event &e)
{

	bool exists = false;

	super::handleEvent(e);
	if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID && e.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		close = true;
	}
	Tile* d = NULL;
	if(hasMouseFocus())
	{
		for(int i = 0; i < TILES_X; i++)
		{
			for(int j = 0; j < TILES_Y; j++)
			{
				if(tiles[i][j]->handleEvent(&e))
				{
					d = tiles[i][j];
					exists = true;
				}
			}
		}
	}

	//if (!exists)
	//{
	//	d = tiles[0][0];
	//}

	return d;
}

void Map::free()
{
	super::free();
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			delete tiles[i][j];
		}
	}
	delete statusClip;
}
