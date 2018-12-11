#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <math.h>
#include <time.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

int main(int argc, char **argv)
{
	int ret = 0;

	 int lastTime = 0, currentTime;
    
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		ret = -1;
		goto endmain;
	}

	SDL_Window *window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 0);
	if (!window)
	{
		SDL_Log("unable to create window: %s", SDL_GetError());
		ret = -1;
		goto sdlquit;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("unable to create renderer: %s", SDL_GetError());
		ret = -1;
		goto closewindow;
	}

	float val = 0;
	


	for (;;)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto closerendered;
			}
		}

		
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000)
		{
			lastTime = currentTime;
			val += 0.06f;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(renderer, WIN_WIDTH / 2, WIN_HEIGHT / 2, cos(val) * currentTime, sin(val) * currentTime);

		SDL_RenderPresent(renderer);

	}

closerendered:
	SDL_DestroyRenderer(renderer);
closewindow:
	SDL_DestroyWindow(window);
sdlquit:
	SDL_Quit();
endmain:
	return ret;
}
