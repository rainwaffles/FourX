#include "Dialog.h"

void Dialog::setTile(Tile* t)
{
	thisTile = t;
}

void Dialog::render()
{
	SDL_RenderClear( mRenderer );
	std::stringstream tmp;
	tmp << "Tile type: " << thisTile->getType() << " Tile X: " << thisTile->getX() << " Tile Y: " << thisTile->getY() << " PC: " << thisTile->getproductionCapacity();
	SDL_Surface* textSurface = TTF_RenderText_Solid( Window::gFont, tmp.str().c_str(), Window::textColor );
	SDL_RenderCopy( mRenderer, SDL_CreateTextureFromSurface( mRenderer, textSurface ), NULL, NULL );
	SDL_RenderPresent( mRenderer );
	update = false;
}