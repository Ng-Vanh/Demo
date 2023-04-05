#include "Explosion.h"

ExplosionObj::ExplosionObj()
{
	frame_ = 0;
	frame_width = 0;
	frame_height = 0;
}
ExplosionObj::~ExplosionObj()
{

}
bool ExplosionObj::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret)
	{
		frame_width = rect_.w / 8;
		frame_height = rect_.h;
	}
	return ret;
}
void ExplosionObj::set_clip()
{
	if (frame_width > 0 && frame_height > 0)
	{
		for (int i = 0; i < 7; i++)
		{
			frame_clip_[i].x = frame_width * i;
			frame_clip_[i].y = 0;
			frame_clip_[i].h = frame_height;
			frame_clip_[i].w = frame_width;
		}
	}
}
void ExplosionObj::Show(SDL_Renderer* screen)
{
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect render_quad = { rect_.x, rect_.y, frame_width, frame_height };
	if (current_clip != NULL)
	{
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}
	SDL_RenderCopy(screen, p_object, current_clip, &render_quad);
}