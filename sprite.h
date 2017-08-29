#ifndef _SPRITE_SDL_C_H_
#define _SPRITE_SDL_C_H_

#include <SDL.h>

typedef struct 
{
	SDL_Rect rectangle;
	SDL_Surface* image;
	SDL_Texture* texture;
	int dead;
} Sprite;


void InitSprite(Sprite* sprite, SDL_Renderer* renderer, int x, int y, int w, int h, char* path)
{
	sprite->dead = 0;
	sprite->rectangle.x = x;
	sprite->rectangle.y = y;
	sprite->rectangle.w = w;
	sprite->rectangle.h = h;
	sprite->image = SDL_LoadBMP(path);
	SDL_SetColorKey(sprite->image, SDL_TRUE, SDL_MapRGB( sprite->image->format, 0xFF, 0, 0xFF));
	sprite->texture = SDL_CreateTextureFromSurface(renderer,sprite->image);
	
}

void DrawSprite(Sprite* sprite, SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, sprite->texture, NULL, &(sprite->rectangle));
}

void DestroySprite(Sprite* sprite)
{
	SDL_DestroyTexture(sprite->texture);  
    SDL_FreeSurface(sprite->image);

	sprite->texture = NULL;
	sprite->image = NULL;

	sprite->dead = 1;
}

#endif
