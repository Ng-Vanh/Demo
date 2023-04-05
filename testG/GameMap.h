#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES  20

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }

};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; };
	void setMap(Map& map_data) { game_map_ = map_data; };
private:
	Map game_map_;// chua all thong tin ve ban do
	TileMap tile_map[MAX_TILES];//luu tru cac dooi tuong cau tao len 1 map

};