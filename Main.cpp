/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Texture.h"
#include "Tile.h"
#include "Map.h"
#include "Dialog.h"
#include "Window.h"

/*
//Screen dimension constants
const int TILES_X = 40;
const int TILES_Y = 20;
const int TILE_SIZE_X = 30;
const int TILE_SIZE_Y = 30;
const int SCREEN_WIDTH = TILES_X*TILE_SIZE_X;
const int SCREEN_HEIGHT = TILES_Y*TILE_SIZE_Y;
*/

//Starts up SDL and creates window
bool init();

//highlights movement
void highlightMovement(Tile* d);

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

/*
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The tiles
*/


Map* mainMap;
Dialog* mainDialog = NULL;

int playerFaction = 1;

bool init()
{
	//This function is basically good.

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		//gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		mainMap = new Map();
		if( !mainMap->init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		/*
		else
		{
			//Create vsynced renderer for window
			
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
			
		}
		*/
	}

	//Tile::init(gRenderer);
	TTF_Init();

	return success;
}

/*
bool loadTiles()
{
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			tiles[i][j] = new Tile(1, gRenderer, i*TILE_SIZE_X, j*TILE_SIZE_Y);
		}
	}
	return true;
}
*/

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//This is where you load images and stuff
	//success = loadTiles();

	return success;
}

void close()
{
	/*
	//Free loaded stuff
	for(int i = 0; i < TILES_X; i++)
	{
		for(int j = 0; j < TILES_Y; j++)
		{
			delete tiles[i][j];
		}
	}
	*/

	/*
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	*/
	mainMap->free();
	delete mainMap;

	if(mainDialog != NULL)
	{
		mainDialog->free();
		delete mainDialog;
	}

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void highlightMovement(Tile* d, int speed)
{
	if (speed <= 0)
	{
		return;
	}

	for (int i = 1; i <= 4; i++)
	{
		Tile* tile = mainMap->get(d, i);
		
		if (tile != NULL)
		{
			if (tile->getUnit() == NULL)
			{
				tile->movement = true;

				highlightMovement(tile, speed - 1);
			}
		}
	}

}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit && mainMap->close != true)
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle button events
					/*
					for(int i = 0; i < TILES_X; i++)
					{
						for(int j = 0; j < TILES_Y; j++)
						{
							tiles[i][j]->handleEvent(&e);
						}
					}
					*/
					if(mainDialog != NULL)
					{ 
						//char i;
						switch(mainDialog->handleEvent(e))
						{
						case 1:
							break;
						case 2:
							break;
						case 3:
							break;
						case 4:
							break;
						}
					}
					/*
					if(mainDialog != NULL)
					{ 
						//char i;
						switch(mainDialog->handleEvent(e))
						{
						case 0:
							break;
						case 1:
							mainMap->transfer(mainDialog->transferT, mainDialog->transferW, mainDialog->getTile(), 1);
							mainDialog->clearTrans();
							mainMap->update = true;
							break;
						case 2:
							mainMap->transfer(mainDialog->transferT, mainDialog->transferW, mainDialog->getTile(), 2);
							mainDialog->clearTrans();
							mainMap->update = true;
							break;
						case 3:
							mainMap->transfer(mainDialog->transferT, mainDialog->transferW, mainDialog->getTile(), 3);
							mainDialog->clearTrans();
							mainMap->update = true;
							break;
						case 4:
							mainMap->transfer(mainDialog->transferT, mainDialog->transferW, mainDialog->getTile(), 4);
							mainDialog->clearTrans();
							mainMap->update = true;
							break;
						}
						//printf("%s\n",mainDialog->handleEvent(e));
					}
					*/
					Tile* d = mainMap->handleEvent(e);
					
					bool unitMove = false;
					
					if(e.type == SDL_KEYDOWN && mainDialog != NULL)
					{
						switch( e.key.keysym.sym )
						{
						case SDLK_w:
							d = mainMap->get(mainDialog->getTile(), 1);
							break;
						case SDLK_d:
							d = mainMap->get(mainDialog->getTile(), 2);
							break;
						case SDLK_s:
							d = mainMap->get(mainDialog->getTile(), 3);
							break;
						case SDLK_a:
							d = mainMap->get(mainDialog->getTile(), 4);
							break;
						case SDLK_UP:
							d = mainMap->get(mainDialog->getTile(), 1);
							unitMove = true;
							break;
						case SDLK_RIGHT:
							d = mainMap->get(mainDialog->getTile(), 2);
							unitMove = true;
							break;
						case SDLK_DOWN:
							d = mainMap->get(mainDialog->getTile(), 3);
							unitMove = true;
							break;
						case SDLK_LEFT:
							d = mainMap->get(mainDialog->getTile(), 4);
							unitMove = true;
							break;
						case SDLK_SPACE:
							mainMap->nextTurn();
							mainDialog->update = true;
							mainMap->update = true;
							if (mainDialog->getTile()->getUnit() != NULL){ highlightMovement(mainDialog->getTile(), mainDialog->getTile()->getUnit()->speed); }
							break;
						}
					}
					if(d != NULL)
					{
						if(mainDialog == NULL)
						{
							mainDialog = new Dialog();
							mainDialog->init();
						}
						else
						{

							Unit* unit = mainDialog->getTile()->getUnit();

							if (unit != NULL)
							{

								if (unit->currentSpeed > 0)
								{
									
									if (unitMove && d->getUnit() == NULL)
									{
										mainDialog->getTile()->removeUnit();
										unit->setX(d->getX());
										unit->setY(d->getY());
										unit->currentSpeed--;
										d->addUnit(unit);
									}
									mainMap->update = true;
									mainDialog->update = true;
									
								}

							}
							mainDialog->getTile()->highlight = false;
							if (d->getUnit() != NULL)
							{
								highlightMovement(d, d->getUnit()->currentSpeed);
							}
						}
						mainDialog->setTile(d);
						if(mainDialog->isShown()){mainDialog->focus();}
						mainDialog->update = true;
						d->highlight = true;
						mainMap->update = true;
					}
					if(e.type == SDL_KEYDOWN)
					{
						switch( e.key.keysym.sym )
						{
						case SDLK_g:
							Tile::grid = !Tile::grid;
							mainMap->update = true;
							break;
						case SDLK_e:
							if(!mainDialog->isShown()){mainDialog->focus();}
							else{mainDialog->hide();}
							break;	
						}
					}
				}

				//Clear screen
				/*
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				*/

				//Render current frame
				/*
				for(int i = 0; i < TILES_X; i++)
				{
					for(int j = 0; j < TILES_Y; j++)
					{
						tiles[i][j]->render();
					}
				}
				*/
				if(mainDialog != NULL && mainDialog->update){ mainDialog->render();}
				if(mainMap->update){mainMap->render();}

				//Update screen
				/*
				SDL_RenderPresent( gRenderer );
				*/

			}
		}
	}

	//Free resources and close SDL
	//SDL_Delay( 2000 );

	close();

	return 0;
}