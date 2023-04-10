#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"

class GamePower : public BaseObject
{
public:
	GamePower();
	~GamePower();

	void setNum(const int& num) { number_ = num; }
	void addPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);
	void Increase();//tang so mang
	void Decrease();//Giam so mang

private:
	int number_;
	std::vector<int> pos_list_;
};


class Coin : public BaseObject
{
public:
	Coin();
	~Coin();
	void Init(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void setPos(const int& xP, const int& yP)
	{
		x_pos = xP;
		y_pos = yP;
	}
private:
	int x_pos;
	int y_pos;
};