#ifndef _FRAMEWORK_SDL_C_H_
#define _FRAMEWORK_SDL_C_H_

#include <SDL.h>

void Init();
void Load();
void Update();
void Controls();
void Draw();
void Close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Event event;
int gameRunning = 0;

int main()
{
	Init();
	Load();

	gameRunning = 1;

	while(gameRunning) 
	{
		while( SDL_PollEvent(&event) )
        {
            Controls();
            
            if( event.type == SDL_QUIT )
            {
                gameRunning = 0;
            }
        }

		Update();
		Draw();
	}

	Close();
	
	return 0;
}

#endif
