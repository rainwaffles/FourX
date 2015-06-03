#include "Map.h"

bool Map::init()
{
	//Create window
	mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
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
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
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
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			tiles[i][j] = new Tile((i+j)%3 + 1, i*TILE_SIZE_X, j*TILE_SIZE_Y + TILE_SIZE_Y);
		}
	}
	close = false;
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

void Map::renderStatus()
{
	std::stringstream tmp;
	tmp << "HELLO";
	if(Window::gFont == NULL){Window::gFont = TTF_OpenFont( "./BOOTERFF.ttf", 100 );}
	SDL_Surface* textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	statusClip->w = (textSurface->w / textSurface->h) * TILE_SIZE_Y;
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, statusClip );
}

Tile* Map::handleEvent(SDL_Event &e)
{
	super::handleEvent(e);
	if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID && e.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		close = true;
	}
	Tile* d = NULL;
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			if(tiles[i][j]->handleEvent(&e))
			{
				d = tiles[i][j];
			}
		}
	}
	return d;
}

void Map::free()
{
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			delete tiles[i][j];
		}
	}
	delete statusClip;
}
