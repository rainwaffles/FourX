#include "Dialog.h"

void Dialog::init()
{
	super::init();
	statusClip = new SDL_Rect();
	statusClip->h = SCREEN_HEIGHT/2;
	statusClip->w = SCREEN_WIDTH;
	statusClip->x = 0;
	statusClip->y = 0;

	statusClip2 = new SDL_Rect();
	statusClip2->h = SCREEN_HEIGHT/2;
	statusClip2->w = SCREEN_WIDTH;
	statusClip2->x = 0;
	statusClip2->y = SCREEN_HEIGHT/2;
	compass = new Texture(mRenderer);
	compass->loadFromFile("./imgs/compass.png");
}

void Dialog::setTile(Tile* t)
{
	thisTile = t;
}

void Dialog::render()
{
	SDL_RenderClear( mRenderer );
	std::stringstream tmp;
	tmp << "Metal: " << thisTile->metals << "/" << thisTile->tMetals 
		<< " Oil: " << thisTile->oil << "/" << thisTile->tOil 
		<< " Timber: " << thisTile->timber << "/" << thisTile->tTimber;
	SDL_Surface* textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	statusClip->w = (textSurface->w / textSurface->h) * (SCREEN_HEIGHT/2);
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, statusClip );
	compass->render(SCREEN_WIDTH - 80, 0);
	tmp.str("");
	tmp << "Troops: " << thisTile->troops << " Workers: " << thisTile->workers;
	textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	statusClip2->w = (textSurface->w / textSurface->h) * (SCREEN_HEIGHT/2);
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, statusClip2 );
	SDL_RenderPresent( mRenderer );
	update = false;
}

int Dialog::handleEvent(SDL_Event &e)
{
	super::handleEvent(e);
	if(e.type == SDL_MOUSEBUTTONDOWN && hasMouseFocus())
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if(x > SCREEN_WIDTH - 65 && x < SCREEN_WIDTH - 15 &&
		   y > 0 && y < 20)
		{
			return 1; //North
		}
		else if(x > SCREEN_WIDTH - 20 && x < SCREEN_WIDTH &&
		   y > 15 && y < SCREEN_HEIGHT - 15)
		{
			return 2; //East
		}
		else if(x > SCREEN_WIDTH - 65 && x < SCREEN_WIDTH - 15 &&
		   y > SCREEN_HEIGHT - 20 && y < SCREEN_HEIGHT)
		{
			return 3; //South
		}
		else if(x > SCREEN_WIDTH - 80 && x < SCREEN_WIDTH - 60 &&
		   y > 15 && y < SCREEN_HEIGHT - 15)
		{
			return 4; //West
		}
	}
	if(e.type == SDL_KEYDOWN && hasKeyboardFocus())
	{
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:
			return 1;
		case SDLK_RIGHT:
			return 2;
		case SDLK_DOWN:
			return 3;
		case SDLK_LEFT:
			return 4;
		case SDLK_PLUS:
			return 5;
		case SDLK_MINUS:
			return 6;
		}
	}
	return 0;
}

void Dialog::free()
{
	super::free();
	delete statusClip;
	compass->free();
	delete compass;
}