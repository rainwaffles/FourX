#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class Texture
{
	public:
		//Initializes variables
		Texture();
		Texture(SDL_Renderer* rend);

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		void setRenderer(SDL_Renderer* rend);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		bool hasTex();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Renderer, passed via constructor
		SDL_Renderer* gRenderer;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif
