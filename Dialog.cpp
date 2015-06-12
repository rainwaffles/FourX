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
	tt = new SDL_Rect();
	tt->h = SCREEN_HEIGHT/2;
	tt->w = 30;
	tt->x = SCREEN_WIDTH - 200;
	tt->y = SCREEN_HEIGHT/2;
	tw = new SDL_Rect();
	tw->h = SCREEN_HEIGHT/2;
	tw->w = 30;
	tw->x = SCREEN_WIDTH - 120;
	tw->y = SCREEN_HEIGHT/2;
	compass = new Texture(mRenderer);
	compass->loadFromFile("./imgs/compass.png");
	arrows = new Texture(mRenderer);
	arrows->loadFromFile("./imgs/arrows.png");
	background = new Texture(mRenderer);
	background->loadFromFile("./imgs/dialogueBackground.png");
	transferT = 0;
	transferW = 0;
}

void Dialog::setTile(Tile* t)
{
	clearTrans();
	thisTile = t;
}

void Dialog::clearTrans()
{
	transferT = 0;
	transferW = 0;
}

void Dialog::render()
{
	SDL_RenderClear( mRenderer );

	background->render(0, 0);

	std::stringstream tmp;
	tmp << "Metal: " << thisTile->metals << "/" << thisTile->tMetals 
		<< " Oil: " << thisTile->oil << "/" << thisTile->tOil 
		<< " Timber: " << thisTile->timber << "/" << thisTile->tTimber;
	SDL_Surface* textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	statusClip->w = (textSurface->w / textSurface->h) * (SCREEN_HEIGHT/2);
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, statusClip );

	tmp.str("");
	tmp << "Troops: " << thisTile->troops << " Workers: " << thisTile->workers;
	textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	statusClip2->w = (textSurface->w / textSurface->h) * (SCREEN_HEIGHT/2);
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, statusClip2 );

	tmp.str("");
	tmp << transferT;
	textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
//	tt->w = (textSurface->w / textSurface->h) * (SCREEN_HEIGHT/2);
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, tt );
	tmp.str("");
	tmp << transferW;
	textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
//	tw->w = (textSurface->w / textSurface->h) * (SCREEN_HEIGHT/2);
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, tw );

	compass->render(SCREEN_WIDTH - 80, 0);
	arrows->render(SCREEN_WIDTH - 160, 40);
	arrows->render(SCREEN_WIDTH - 240, 40);

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
			update = true;
			return 1; //North
		}
		else if(x > SCREEN_WIDTH - 20 && x < SCREEN_WIDTH &&
		   y > 15 && y < SCREEN_HEIGHT - 15)
		{
			update = true;
			return 2; //East
		}
		else if(x > SCREEN_WIDTH - 65 && x < SCREEN_WIDTH - 15 &&
		   y > SCREEN_HEIGHT - 20 && y < SCREEN_HEIGHT)
		{
			update = true;
			return 3; //South
		}
		else if(x > SCREEN_WIDTH - 80 && x < SCREEN_WIDTH - 60 &&
		   y > 15 && y < SCREEN_HEIGHT - 15)
		{
			update = true;
			return 4; //West
		}
		else if(x > SCREEN_WIDTH - 160 && x < SCREEN_WIDTH - 120 &&
		   y > SCREEN_HEIGHT - 40 && y < SCREEN_HEIGHT - 20)
		{
			if(thisTile->workers > transferW) transferW++;
			update = true;
			return 0; //Up
		}
		else if(x > SCREEN_WIDTH - 160 && x < SCREEN_WIDTH - 120 &&
		   y > SCREEN_HEIGHT - 20 && y < SCREEN_HEIGHT)
		{
			if(transferW > 0) transferW--;
			update = true;
			return 0; //Down
		}
		else if(x > SCREEN_WIDTH - 240 && x < SCREEN_WIDTH - 200 &&
		   y > SCREEN_HEIGHT - 40 && y < SCREEN_HEIGHT - 20)
		{
			if(thisTile->troops > transferT) transferT++;
			update = true;
			return 0; //Up
		}
		else if(x > SCREEN_WIDTH - 240 && x < SCREEN_WIDTH - 200 &&
		   y > SCREEN_HEIGHT - 20 && y < SCREEN_HEIGHT)
		{
			if(transferT > 0) transferT--;
			update = true;
			return 0; //Down
		}
	}
	if(e.type == SDL_KEYDOWN && hasKeyboardFocus())
	{
		switch( e.key.keysym.sym )
		{
		case SDLK_KP_8:
			update = true;
			return 1;
		case SDLK_KP_6:
			update = true;
			return 2;
		case SDLK_KP_2:
			update = true;
			return 3;
		case SDLK_KP_4:
			update = true;
			return 4;
		case SDLK_KP_PLUS:
			if(thisTile->troops > transferT) transferT++;
			update = true;
			return 0;
		case SDLK_KP_MINUS:
			if(transferT > 0) transferT--;
			update = true;
			return 0;
		case SDLK_ESCAPE:
			SDL_HideWindow( mWindow );
			return 0;
		}
	}
	return 0;
}

Tile* Dialog::getTile()
{
	return thisTile;
}

void Dialog::free()
{
	super::free();
	delete statusClip;
	compass->free();
	delete compass;
	arrows->free();
	delete arrows;
}