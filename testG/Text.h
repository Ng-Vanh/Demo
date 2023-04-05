#pragma once
#include "CommonFunc.h"

class TextObj
{
public:
	TextObj();
	~TextObj();

	enum TextColor
	{
		RED_TXT = 0,
		WHITE_TXT = 1,
		BLACK_TXT = 2,
	};
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	void RenderText(SDL_Renderer* screen,
					int xpos, int ypos,
					SDL_Rect* clip = NULL,
					double angle = 0.0,
					SDL_Point* center = NULL,
					SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth()const { return width; }
	int GetHeight() const { return height; }
	void SetText(const std::string& text) { str_value_ = text; }
	std::string GetText() const { return str_value_; }

private:
	std::string str_value_;
	SDL_Color text_color_;
	SDL_Texture* texture_;
	int width;
	int height;


};