#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 8

class ExplosionObj : public BaseObject
{
public:
	ExplosionObj();
	~ExplosionObj();
	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	int get_frame_width() const { return frame_width; }
	int get_frame_height() const { return frame_height; }


private:
	int frame_width;
	int frame_height;
	unsigned int frame_;
	SDL_Rect frame_clip_[8];

};