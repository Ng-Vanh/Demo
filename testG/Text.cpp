#include "Text.h"

TextObj::TextObj()
{
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;

	texture_ = NULL;

}
TextObj::~TextObj()
{

}
bool TextObj::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_value_.c_str(), text_color_);
	if (text_surface != NULL)
	{
		texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
		width = text_surface->w;
		height = text_surface->h;
		SDL_FreeSurface(text_surface);
	}

	return text_surface != NULL;
}

void TextObj::Free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}
void TextObj::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = red;

}
void TextObj::SetColor(int type)
{
	if (type == RED_TXT)
	{
		SDL_Color color = { 255,0,0 };
		text_color_ = color;
	}
	else if (type == BLACK_TXT)
	{
		SDL_Color color = { 0,0,0 };
		text_color_ = color;
	}
	else if (type == WHITE_TXT)
	{
		SDL_Color color = { 255,255,255 };
		text_color_ = color;
	}
}
void TextObj::RenderText(SDL_Renderer* screen, int xpos, int ypos, SDL_Rect* clip /*= NULL*/, double angle /*= 0.0*/,
	SDL_Point* center /*= NULL*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
{
	SDL_Rect renderQuad = { xpos,ypos,width, height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

	}

	SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle,center, flip);
}