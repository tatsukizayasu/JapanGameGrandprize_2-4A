#pragma once
#include "DxLib.h"
#include "Stage/StageBuilder/KeyManager.h"
#include "define.h"
#define _USE_MATH_DEFINES
#include <math.h>

class ColliderBase
{
public:
	ColliderBase()
	{
		location = { 0,0 };
	}
	ColliderBase(Location location)
	{
		this->location = location;
	}

	//中心座標の取得
	Location GetLocation()const
	{
		return location;
	}

	//中心座標の移動
	void MoveLocation()
	{
		const float scalar = 5;
		if (KeyManager::OnKeyClicked(KEY_INPUT_W) || KeyManager::OnKeyClicked(KEY_INPUT_UP))
		{
			location.y -= scalar;
		}

		if (KeyManager::OnKeyClicked(KEY_INPUT_S) || KeyManager::OnKeyClicked(KEY_INPUT_DOWN))
		{
			location.y += scalar;
		}

		if (KeyManager::OnKeyClicked(KEY_INPUT_A) || KeyManager::OnKeyClicked(KEY_INPUT_LEFT))
		{
			location.x -= scalar;
		}

		if (KeyManager::OnKeyClicked(KEY_INPUT_D) || KeyManager::OnKeyClicked(KEY_INPUT_RIGHT))
		{
			location.x += scalar;
		}

	}

	//中心座標の設定
	void SetLocation(Location location)
	{
		const float distance_limit = 700.f;
		Location distance;
		distance.x = this->location.x - location.x;
		distance.y = this->location.y - location.y;

		if (powf(distance.x, 2) + powf(distance.y, 2) < powf(distance_limit, 2))
		{
			this->location = location;
		}
	}



protected:
	Location location;	//中心座標
};