#include "GamePower.h"

GamePower::GamePower()
{
	number_ = 0;

}
GamePower::~GamePower()
{

}
void GamePower::addPos(const int& xPos)
{
	pos_list_.push_back(xPos); 
}
void GamePower::Init(SDL_Renderer * screen)
{
	LoadImg("img//Heart.png", screen);
	number_ = 5;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	addPos(20);
	addPos(60);
	addPos(100);
}

void GamePower::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < (int)pos_list_.size(); i++)
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}
void GamePower::Decrease()
{
	number_--;
	pos_list_.pop_back();
}
void GamePower::Increase()
{
	number_++;
	int last_pos = pos_list_.back();
	last_pos += 40;
	pos_list_.push_back(last_pos);
}


Coin::Coin()
{
	x_pos = 0;
	y_pos = 0;
}
Coin::~Coin()
{

}
void Coin::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("img//money.png", screen);
}
void Coin::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	Render(screen);
}