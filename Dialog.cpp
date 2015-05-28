#include "Dialog.h"

TTF_Font* Dialog::gFont = TTF_OpenFont( "./BOOTERFF.ttf", 100 );
SDL_Color Dialog::textColor = {0,0,0};

void Dialog::setTile(Tile* t)
{
	thisTile = t;
	Dialog::gFont = TTF_OpenFont( "./BOOTERFF.ttf", 100 );
}

void Dialog::render()
{
	SDL_RenderClear( mRenderer );
	std::stringstream tmp;
	tmp << "Tile type: " << thisTile->getType() << " Tile X: " << thisTile->getX() << " Tile Y: " << thisTile->getY();
	SDL_Surface* textSurface = TTF_RenderText_Solid( Dialog::gFont, tmp.str().c_str(), Dialog::textColor );
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, NULL );
	SDL_RenderPresent( mRenderer );
}