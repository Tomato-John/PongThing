#include "Game.h"

SDL_Renderer* renderer;
const int thickness = 15;

Game::Game()
{
	isRunning = true;
	window = nullptr;
}

int Game::initialize()
{
	// Init SDL
	SDL_Log("Iniitializing SDL...");
	int result = SDL_Init(SDL_INIT_EVERYTHING);
	if (result != 0)
	{
		SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
	}

	// Create window
	window = SDL_CreateWindow("Pong Thing", 100, 100, 1024, 768, 0);
	if (!window)
	{
		result = -1;
		SDL_Log("Failed to create window: %s", SDL_GetError());
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		result = -1;
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
	}

	return result;
}

void Game::runLoop()
{
	while (isRunning)
	{
		processInput();
		update();
		generateOutput();
	}
}


void Game::shutdown(){
	SDL_DestroyRenderer(renderer);
}

void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	//Get keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

}

void Game::update()
{
}

void Game::generateOutput()
{
	// Draw background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw walls
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect topWall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(renderer, &topWall);

	SDL_Rect bottomWall{
	0,
	768-thickness,
	1024,
	thickness
	};
	SDL_RenderFillRect(renderer, &bottomWall);

	SDL_Rect rightWall{
	1024-thickness,
	0,
	thickness,
	768
	};
	SDL_RenderFillRect(renderer, &rightWall);



	SDL_RenderPresent(renderer);
}
