#include "SDL.h"
#include "BaseObject.h"
#include "CommonFunc.h"
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include "Text.h"

#include"GamePower.h"

BaseObject g_background;
TTF_Font* font_common =NULL ;

void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_Window);
	g_Window = NULL;
	IMG_Quit();
	SDL_Quit();
}

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_Window = SDL_CreateWindow("Gamecpp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_Window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
		if (TTF_Init() == -1)
		{
			success = false;
		}
		font_common = TTF_OpenFont("font//ObelixProB-cyr.ttf", 18);
		if (font_common == NULL)
		{
			success = false;
		}
	}
	return success;
}
bool LoadBackGround()
{
	bool ret = g_background.LoadImg("img//bk1.png", g_screen);
	if (ret == false)
		return false;
	return true;
}
std::vector<ThreatObject*> MakeThreatList()
{
	std::vector<ThreatObject*> list_threats;// static threat


	ThreatObject* dynamic_threats = new ThreatObject[20];
	for (int i = 0; i < 20; i++)
	{
		ThreatObject* p_threat = (dynamic_threats + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move_(ThreatObject::MOVE_IN_SPACE_THREAT);// trang thai threat: di chuyen
			srand(time(0));
			p_threat->set_x_pos( rand()%999 + (i+1) * 1120);
			p_threat->set_y_pos(399);

			int pos1 = p_threat->get_x_pos() - 120;		
			int pos2 = p_threat->get_x_pos() + 120;
			p_threat->setAnimationPos(pos1, pos2);// di chuyen trong pham vi pos1-->pos2
			p_threat->set_input_left(1);


			list_threats.push_back(p_threat);
		}
	}

	ThreatObject* threats_objs = new ThreatObject[20];
	for (int i = 0; i < 16; i++)
	{
		ThreatObject* p_threat = (threats_objs + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_level.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(rand() %1236 + (i+1) * 1356);
			p_threat->set_y_pos(250);
			p_threat->set_type_move_(ThreatObject::STATIC_THREAT);
			p_threat->set_input_left(0);
			//Threat ban dan: 
			BulletObject* p_bullet = new BulletObject;
			p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}

#undef main 
int main(int argc, char* argv[])
{
	ImpTimer fps_timer;


	if (InitData() == false)
		return -1;
	if (LoadBackGround() == false)
		return -1;

	GameMap game_map;
	char nameFileMap[] = "map/map01.dat";
	game_map.LoadMap(nameFileMap);
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.set_clip();

	GamePower player_heart;
	player_heart.Init(g_screen);

	Coin player_money;
	player_money.Init(g_screen);
	player_money.setPos(SCREEN_WIDTH/2 - 100, 12);

	std::vector<ThreatObject*> threats_list = MakeThreatList();

	ExplosionObj exp_threat;
	bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
	if (!tRet)
	{
		return false;
	}
	else {
		exp_threat.set_clip();
	}
	ExplosionObj exp_player;
	bool tRetP = exp_player.LoadImg("img//exp33.png", g_screen);
	if (!tRetP)
	{
		return false;
	}
	else
	{
		exp_player.set_clip();
	}
	int heart = 3;
	//Text:
	TextObj time_game;
	TextObj HP_txt;
	TextObj Coin_txt;
	time_game.SetColor(TextObj::RED_TXT);
	HP_txt.SetColor(TextObj::RED_TXT);
	Coin_txt.SetColor(TextObj::RED_TXT);

	bool is_quit = false;
	while (!is_quit)
	{
		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			p_player.HandleInputAction(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		Map map_data = game_map.getMap();

		// Player
		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		//Map
		game_map.setMap(map_data);
		game_map.DrawMap(g_screen);

	
		//show Mang:

		player_heart.Show(g_screen);

		//Show coin
		player_money.Show(g_screen);

		//Threat
		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatObject* p_threat = threats_list.at(i);
			if (p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);


				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
				for (int j = 0; j < tBullet_list.size(); j++ )
				{
					BulletObject* pt_bullet = tBullet_list.at(j);
					if (pt_bullet)
					{
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
						if (bCol1)
						{
							p_threat->RemoveBullet(j);
							break;
						}
					}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
				if ( bCol1 || bCol2 )
				{
					//Die
					int frame_die_w = exp_player.get_frame_width();
					int frame_die_h = exp_player.get_frame_height();

					for (int ex = 0; ex < 8; ex++)
					{
						int x_pos = p_player.GetRect().x + p_player.get_frame_width() * 0.5 - frame_die_w * 0.5;
						int y_pos = p_player.GetRect().y + p_player.get_frame_height() * 0.5 - frame_die_h * 0.5;

						exp_threat.set_frame(ex);
						exp_threat.SetRect(x_pos, y_pos);
						exp_threat.Show(g_screen);
						SDL_RenderPresent(g_screen);
					}

					heart--;
					
					
					if (heart >= 1)
					{
						

						p_player.SetRect(0, 0);
						p_player.set_comeback_time(100);
						SDL_Delay(500);
						player_heart.Decrease();
						player_heart.Render(g_screen);
						continue;
					}
					else
					{
						if (MessageBox(NULL, L"GameOver!!", L"Alert", MB_OK | MB_ICONSTOP) == IDOK)
						{
							p_threat->Free();
							close();
							SDL_Quit();
							return 0;
						}
					}
					
					
				}


			}
		}

		// Xu li vu no dan player trung dich
		int frame_exp_width = exp_threat.get_frame_width();
		int frame_exp_height = exp_threat.get_frame_height();

		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
		for (int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < threats_list.size(); t++)
				{
					ThreatObject* obj_threat = threats_list.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();// neu dung getRect se lay ra width = 480px;
						tRect.h = obj_threat->get_height_frame();


						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

						if (bCol)
						{
							for (int ex = 0; ex < 8; ex++)
							{
								int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
								int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
								SDL_RenderPresent(g_screen);
							}

							p_player.RemoveBullet(r);
							obj_threat->Free();
							threats_list.erase(threats_list.begin() + t);
						}
					}
				}
			}
		}


		// show Text time:
		std::string str_time = "Time: ";
		Uint32 time_value = SDL_GetTicks() / 1000;
		Uint32 value_time = 180 - time_value;
		if (value_time <= 0)
		{
			if (MessageBox(NULL, L"GameOver!!", L"Alert", MB_OK | MB_ICONSTOP) == IDOK)
			{
				is_quit = true;
				break;
				/*close();
				SDL_Quit();
				return 0;*/
			}
		}
		else {
			std::string str_val = std::to_string(value_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_common, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}
		//Show Heart:
		/*std::string show_heart = "HP: ";
		std::string str_heart = std::to_string(heart);
		show_heart += str_heart;

		HP_txt.SetText(show_heart);
		HP_txt.LoadFromRenderText(font_common, g_screen);
		HP_txt.RenderText(g_screen,150, 15);*/

		//Show Coint
		int cur_coint = p_player.GetCoin();
		std::string show_coin = ":  ";
		std::string coin = std::to_string(cur_coint);
		show_coin += coin;

		Coin_txt.SetText(show_coin);
		Coin_txt.LoadFromRenderText(font_common, g_screen);
		Coin_txt.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

		SDL_RenderPresent(g_screen);

		int real_ipm_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FPS;// ms
		if (real_ipm_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_ipm_time;
			if (delay_time >= 0)
			{
				SDL_Delay(delay_time);
			}
		}
	}
	for (int i = 0; i < threats_list.size(); i++)
	{
		ThreatObject* p_threat = threats_list.at(i);
		if (p_threat != NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}
	threats_list.clear();
	
	close();
	return 0;
}