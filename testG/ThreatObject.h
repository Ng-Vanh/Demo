#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_FRAME_NUMBER 8
#define THREAT_GRAVITY_SPEED 0.6
#define THREAT_MAX_FAIL_SPEED 10
#define THREAT_SPEED 3
class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	enum TypeMove
	{
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void set_x_val(const float& xVal) { x_val_ = xVal; }
	void set_y_val(const float& yVal) { y_val_ = yVal; }

	void set_x_pos(const float& xPos) { x_pos_ = xPos; }
	void set_y_pos(const float& yPos) { y_pos_ = yPos; }
	float get_x_pos() const { return x_pos_; }
	float get_y_pos() const { return y_pos_; }

	void SetMapXY(const int& mpX, const int& mpY) { map_x_ = mpX; map_y_ = mpY; }
	
	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }

	void DoPlayer(Map& gMap);
	void RemoveBullet(const int& idx);
	SDL_Rect GetRectFrame();

	void CheckToMap(Map& gMap);
	void InitThreat();

	void set_type_move_(const int& typeMove) { type_move_ = typeMove; }
	void setAnimationPos(const int& pos_a, const int& pos_b)
	{
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	}
	void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; }
	void ImpMoveType(SDL_Renderer* screen);

	std::vector<BulletObject*>get_bullet_list() const {return bullet_list_;}
	void set_bullet_list(const std::vector<BulletObject*> &bl_list) { bullet_list_ = bl_list; }
	void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
private:
	bool on_ground_;
	int come_back_time;
	float x_pos_, y_pos_;
	float x_val_, y_val_;
	int map_x_, map_y_;

	int frame_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[THREAT_FRAME_NUMBER];

	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;

	std::vector<BulletObject*> bullet_list_;

};