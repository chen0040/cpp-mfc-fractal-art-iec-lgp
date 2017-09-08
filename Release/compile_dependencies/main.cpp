#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <vector>
#include "lgp_program.h"
#include "lgp_constants.h"
#include <cmath>

bool handle_input();
void render();
double normalize(double k);

SDL_Surface* pScreen=NULL;
SDL_Surface* pImage=NULL;

int main(int argc, char** argv)
{
	atexit(SDL_Quit);

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Video initialization failed: " << SDL_GetError( ) << "\n";
		return 0;
	}

	pScreen=SDL_SetVideoMode(IMAGE_WIDTH, IMAGE_HEIGHT, 32, SDL_SWSURFACE);

	pImage=SDL_CreateRGBSurface(
		SDL_SWSURFACE, 
		pScreen->w, 
		pScreen->h, 
		pScreen->format->BitsPerPixel, 
		0/*pScreen->format->Rmask*/, 
		0/*pScreen->format->Gmask*/, 
		0/*pScreen->format->Bmask*/, 
		0); 

	double offset_x=static_cast<double>(pImage->w) / 2.0;
	double offset_y=static_cast<double>(pImage->h) / 2.0;

	if(SDL_LockSurface(pImage) < 0)
	{
		return 0;
	}

	Uint32* pixels=(Uint32*)pImage->pixels;

	for(int row=0; row < pImage->h; ++row)
	{
		double normalized_y=static_cast<double>(row-offset_y) / pImage->h;
		for(int col=0; col < pImage->w; ++col)
		{
			double normalized_x=static_cast<double>(col-offset_x) / pImage->w;
			double inputs[2]={normalized_x, normalized_y};
			std::vector<double> registers=lgp_program(inputs);

			//pixels[row * pImage->w + col]=SDL_MapRGB(pImage->format, 255, 255, 255);
			pixels[row * pImage->w + col]=SDL_MapRGB(
				pImage->format, 
				static_cast<int>(normalize(registers[2]) * 255), 
				static_cast<int>(normalize(registers[1]) * 255), 
				static_cast<int>(normalize(registers[0]) * 255)
				);
		}
	}

	SDL_UnlockSurface(pImage);

	bool running=true;
	while(running)
	{
		running=handle_input();
		if(running)	
		{
			render();
			SDL_Delay(200);
		}
	}

	SDL_FreeSurface(pImage);
	SDL_FreeSurface(pScreen);

	return 0;
}

bool handle_input()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					return false;
					break;
				}
				break;
			case SDL_QUIT:
				return false;
				break;
		}
	} 
	return true;
} 

void render()
{
	SDL_Rect offset; 
	offset.x=0;
	offset.y=0;

	SDL_FillRect(pScreen, 0, SDL_MapRGB(pScreen->format, 0, 0, 0 ) );
		
	if(SDL_MUSTLOCK(pScreen))
	{
		if(SDL_LockSurface(pScreen) < 0 )
		{
			return;
		}
	}

	SDL_BlitSurface(pImage, NULL, pScreen, &offset); 

	if(SDL_MUSTLOCK(pScreen))
	{
		SDL_UnlockSurface(pScreen);
	}

	SDL_Flip(pScreen);
}

double normalize(double k)
{
	if(k <= 0 || k > 1)
	{
		return 1.0 / (1.0 + exp(-k));
	}
	return k;
}


