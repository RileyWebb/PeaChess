#include <stdlib.h>

#include "client/client.h"

SDL_Window *window;
unsigned int window_width, window_height;

void C_WindowInit()
{
    SDL_Init(SDL_INIT_EVERYTHING);// | SDL_INIT_EVENTS);
	window = SDL_CreateWindow(
		"PeaChess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 720,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window)
        DEBUG_FATAL("Unable to create window");

    SDL_RaiseWindow(window);
}

void C_WindowProcessEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

        ImGui_ImplSDL2_ProcessEvent(&event);

        switch (event.type) 
        {
            case SDL_QUIT:
                close = 1;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        SDL_GetWindowSize(window, window_width, window_height);
                        break;
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                //C_InputProcessEvent(&e);
                break;
        }
	}
}