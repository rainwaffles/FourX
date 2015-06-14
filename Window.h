#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Texture.h"

class Window
{
		public:
		//Intializes internals
		Window();

		//Creates window
		bool init();

		//Handles window events
		void handleEvent( SDL_Event& e );

		//Focuses on window
		void focus();
		void hide();

		//Shows windows contents
		void render();

		//Deallocates internals
		void free();

		//Window dimensions
		int getWidth();
		int getHeight();
		void setWidth(int w);
		void setHeight(int h);

		//Window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();
		bool isShown();

		bool update;

		static TTF_Font* gFont;
		static SDL_Color textColor;

	protected:
		//Window data
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		int mWindowID;

		static const int SCREEN_WIDTH = 160;
		static const int SCREEN_HEIGHT = 640;


		//Window dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
		bool mShown;
};

#endif