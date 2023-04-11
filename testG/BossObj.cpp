
#include "BossObj.h"
#include<iostream>
#include<string>
using namespace std;

BossObject::BossObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground = 0;
    come_back_time_ = 0;
    frame_ = 0;
    count_ = 0;
    input_type_.left_ = 0;
}

BossObject::~BossObject()
{

}

bool BossObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = rect_.w / BOSS_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect BossObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;
    return rect;
}

void BossObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].h = height_frame_;
        frame_clip_[0].w = width_frame_;

        for (int i = 1; i <= 31; i++)
        {
            frame_clip_[i].x = i * width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].h = height_frame_;
            frame_clip_[i].w = width_frame_;
        }
    }
}

void BossObject::Show(SDL_Renderer* des, int Boss_blood)
{
    if (come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= 32)
        {
            frame_ = 0;
        }

        SDL_Rect* currentclip = &frame_clip_[frame_];
        SDL_Rect renderquad = { rect_.x, rect_.y, width_frame_, height_frame_ };
        SDL_RenderCopy(des, p_object, currentclip, &renderquad);


        //ShowHP
        
      /*  if (Boss_blood > 0)
        {
            SDL_Texture* HP;
            string s = "img/Hp1.png";
            SDL_Surface* load_surface = IMG_Load(s.c_str());
            HP = SDL_CreateTextureFromSurface(des, load_surface);
            SDL_Rect hp_;
            hp_.x = SCREEN_WIDTH - 1050;
            hp_.y = SCREEN_HEIGHT * 0.1;
            hp_.w = SCREEN_WIDTH * 0.4 * Boss_blood / 50;
            hp_.h = 50;
            SDL_RenderCopy(des, HP, NULL, &hp_);
        }*/

    }
}
void BossObject::ShowHP(SDL_Renderer* des, int & Boss_blood)
{
    if (Boss_blood > 0)
    {
        SDL_Texture* HP;
        string s = "img/Hp1.png";
        SDL_Surface* load_surface = IMG_Load(s.c_str());
        HP = SDL_CreateTextureFromSurface(des, load_surface);
        SDL_Rect hp_;
        hp_.x = SCREEN_WIDTH - 1050;
        hp_.y = SCREEN_HEIGHT * 0.1;
        hp_.w = SCREEN_WIDTH * 0.4 * Boss_blood / 50;
        hp_.h = 50;
        SDL_RenderCopy(des, HP, NULL, &hp_);
    }
}
void BossObject::DoPlayer(Map& gMap, int Boss_blood)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += BOSS_GRAVITY_SPEED;
        if (y_val_ >= BOSS_MAX_FALL_SPEED)
        {
            y_val_ = BOSS_MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= BOSS_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += BOSS_SPEED;
        }

        CheckToMap(gMap, Boss_blood);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_--;
        if (come_back_time_ == 0)
        {
            InitBoss();
        }
    }
}

void BossObject::InitBoss()
{
    x_val_ = 0;
    y_val_ = 0;
    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
    }
    else
    {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time_ = 0;
}

void BossObject::CheckToMap(Map& map_data, int Boss_blood)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check_horizontal
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min) / TILE_SIZE;

    /*
        x1,x1..........x2,y1
        .
        .
        .
        .
        x1,y2..........x2,y2
    */

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // mainobject is moving to right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];


            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }

        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];


            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }


    //Check vertical

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if (Boss_blood >= 40)
            {
                if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
                {
                    y_pos_ = y2 * TILE_SIZE;
                    y_pos_ -= (height_frame_ + 1);
                    y_val_ = 0;
                    on_ground = true;
                }
            }
            else
            {
                if (y_pos_ >= SCREEN_HEIGHT / 2 - 100 || ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)))
                {
                    y_pos_ -= (height_frame_ + 10);
                    y_val_ = 0;
                    on_ground = true;
                }
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];


            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }

        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    if (y_pos_ > map_data.max_y_)
    {
        come_back_time_ = 60;
    }
}

void BossObject::InitBullet(SDL_Renderer* screen)
{
    BulletObject* p_bullet = new BulletObject();
    bool ret;
    if (count_ % 8 != 0)
    {
        ret = p_bullet->LoadImg("img//boss_bullet.png", screen);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(rect_.x - 100, rect_.y + height_frame_ - 50);
            p_bullet->set_x_val(20);
            bullet_list.push_back(p_bullet);
        }
    }
    else
    {
        ret = p_bullet->LoadImg("img//genki.png", screen);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(rect_.x - 50, rect_.y + height_frame_ - 100);
            p_bullet->set_x_val(50);
            bullet_list.push_back(p_bullet);
        }
    }

}

void BossObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{

    if (frame_ == 18)
    {
        InitBullet(screen);
        count_++;
    }
    for (int i = 0; i < bullet_list.size(); i++)
    {
        BulletObject* p_bullet = bullet_list[i];
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
                if (bullet_distance < 750 && bullet_distance > 0)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }

            }
            else
            {
                p_bullet->Free();
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x - 15, rect_.y - 5);
                bullet_list.erase(bullet_list.begin() + i);
            }
        }
    }
}
void BossObject::RemoveBullet(const int& idx)
{
    int sizex = bullet_list.size();
    if (sizex > 0 && idx < sizex)
    {
        BulletObject* p_bullet = bullet_list[idx];
        bullet_list.erase(bullet_list.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }

}














