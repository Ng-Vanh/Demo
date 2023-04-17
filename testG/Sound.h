#pragma once
#include "SDL_mixer.h"

static bool checkSound = true;
static Mix_Chunk* laser = NULL;
static Mix_Chunk* hit_threat;
static Mix_Chunk* mix_select_click;
static void MixLaser()
{
	laser = Mix_LoadWAV("sound//Laser.wav");
	if (laser == NULL)
	{
		checkSound = false;
	}
	else {
		Mix_PlayChannel(-1, laser, 0);
	}
}

static void MixHitThreat()
{
	hit_threat = Mix_LoadWAV("sound//hit_threat.wav");
	if (hit_threat == NULL)
	{
		checkSound = false;
	}
	else {
		Mix_PlayChannel(-1, hit_threat, 0);
	}
}
static void MixSelect()
{
	mix_select_click = Mix_LoadWAV("sound//select_click.wav");
	if (mix_select_click == NULL)
	{
		checkSound = false;
	}
	else
	{
		Mix_PlayChannel(-1, mix_select_click, 0);
	}
}
