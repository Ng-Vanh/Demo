#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define BOSS_FRAME_NUM 32
#define BOSS_GRAVITY_SPEED 0.8
#define BOSS_MAX_FALL_SPEED 10
#define BOSS_SPEED 3
#define BOSS_HIGHT_VAL 18

class BossObject : public BaseObject
{
public:
    BossObject();
    ~BossObject();

    void set_x_val(const float& xVal) { x_val_ = xVal; }
    void set_y_val(const float& yVal) { y_val_ = yVal; }

    void set_x_pos(const float& xP) { x_pos_ = xP; }
    void set_y_pos(const float& yP) { y_pos_ = yP; }

    float get_x_pos() const { return x_pos_; }
    float get_y_pos() const { return y_pos_; }

    void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; }

    void set_clips();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des, int Boss_blood);
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }

    void DoPlayer(Map& gMap, int Boss_blood);
    void CheckToMap(Map& gMap, int Boss_blood);

    void InitBoss();

    std::vector<BulletObject*> get_bullet_list() const { return bullet_list; }
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) { bullet_list = bl_list; }

    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);
    void ShowHP(SDL_Renderer* des, int &Boss_blood);
    SDL_Rect GetRectFrame();
private:
    int count_;
    int map_x_;
    int map_y_;
    float y_val_;
    float x_val_;
    float x_pos_;
    float y_pos_;

    bool on_ground;
    int come_back_time_;

    SDL_Rect frame_clip_[BOSS_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move;
    Input input_type_;

    std::vector<BulletObject*> bullet_list;
};
