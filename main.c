#include "framework.h"
#include "sprite.h"

Sprite ball;
Sprite bat;
Sprite blocks[14];

int ball_x_velocity;
int ball_y_velocity;

void Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(renderer, 128, 20, 255, 255);
}

void Load()
{
	InitSprite(&ball, renderer, 300, 400, 36, 36, "Assets/Ball.bmp");
	InitSprite(&bat, renderer, 300, 450, 106, 28, "Assets/Bat.bmp");

	if (1)
	{
		int b = 0;
		for (; b<sizeof(blocks) / sizeof(Sprite); ++b)
		{
			int xPos;
			int yPos;

			if (b - 1<0 || b == 7)
				xPos = 13;
			else
				xPos = blocks[b - 1].rectangle.x + blocks[b - 1].rectangle.w + 2;

			if (b<7)
				yPos = 2;
			else
				yPos = 50;

			InitSprite(&blocks[b], renderer, xPos, yPos, 86, 45, "Assets/Block.bmp");
		}
	}

	ball_x_velocity = 4;
	ball_y_velocity = 3;

}

void Update()
{
	ball.rectangle.x += ball_x_velocity;
	ball.rectangle.y -= ball_y_velocity;

	if (ball.rectangle.y < 0 || (ball.rectangle.y + ball.rectangle.h > bat.rectangle.y &&
		ball.rectangle.x + ball.rectangle.w > bat.rectangle.x &&
		ball.rectangle.x < bat.rectangle.x + bat.rectangle.w))
	{
		ball_y_velocity *= -1;
	}

	if (ball.rectangle.x + ball.rectangle.w > 640 || ball.rectangle.x < 0)
	{
		ball_x_velocity *= -1;
	}

	if (ball.rectangle.y > 500)
	{
		ball.rectangle.x = 300;
		ball.rectangle.y = 140;
	}

	if (1)
	{
		int b = 0;
		int deadBlocks = 0;
		for (; b<sizeof(blocks) / sizeof(Sprite); ++b)
		{
			if (ball.rectangle.x + ball.rectangle.w > blocks[b].rectangle.x &&
				ball.rectangle.x < blocks[b].rectangle.x + blocks[b].rectangle.w &&
				ball.rectangle.y + ball.rectangle.h > blocks[b].rectangle.y &&
				ball.rectangle.y < blocks[b].rectangle.y + blocks[b].rectangle.h && !blocks[b].dead)
			{
				DestroySprite(&blocks[b]);
				ball_y_velocity *= -1;
			}

			if (blocks[b].dead)
			{
				deadBlocks++;
			}
		}

		if (deadBlocks >= sizeof(blocks) / sizeof(Sprite))
		{
			Close();
			main();
		}
	}
}

void Controls()
{
	switch (event.key.keysym.sym)
	{
	case SDLK_LEFT:  bat.rectangle.x -= 8; break;
	case SDLK_RIGHT: bat.rectangle.x += 8; break;
	}
}

void Draw()
{
	SDL_RenderClear(renderer);

	//Draw Calls
	DrawSprite(&ball, renderer);
	DrawSprite(&bat, renderer);

	if (1)
	{
		int b = 0;
		for (; b<sizeof(blocks) / sizeof(Sprite); ++b)
		{
			DrawSprite(&blocks[b], renderer);
		}
	}



	SDL_RenderPresent(renderer);
}

void Close()
{
	//Destroy Stuff
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	DestroySprite(&ball);
	DestroySprite(&bat);

	//Quit SDL subsystems
	SDL_Quit();
}

