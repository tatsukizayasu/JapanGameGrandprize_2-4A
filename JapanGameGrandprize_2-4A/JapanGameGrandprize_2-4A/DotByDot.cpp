#include "DotByDot.h"
#include "PadInput.h"
#include "GameMain.h"
#include "Undead.h"
#include"EnemySlime.h"
#include"EnemyGhost.h"
#include"Harpy.h"
#include "Mage.h"
#include "Torrent.h"
#include "EnemySlimeBoss.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
DotByDot::DotByDot()
{
#define DOT_BY_DOT 1
	state = 0;
	enemy = new EnemyBase * [1];
	Location spawn_location;
	spawn_location.x = 100;
	spawn_location.y = 100;
	enemy[0] = new Undead(spawn_location);
	player = new Player();
	stage = new Stage();
}

//-----------------------------------
//デストラクタ
//-----------------------------------
DotByDot::~DotByDot()
{

	for (int i = 0; i < 1; i++)
	{
		delete enemy[i];
	}
	delete[] enemy;

	delete player;

	delete stage;
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* DotByDot::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		return new GameMain();
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		state++;
		state = state % 5;
	}


	for (int i = 0; i < 1; i++)
	{
		enemy[i]->Update(static_cast<ENEMY_STATE>(state));
	}
	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void DotByDot::Draw() const
{
	DrawFormatString(500, 1000, 0xffffff, "%s", str[state]);

	for (int i = 0; i < 1; i++)
	{
		enemy[i]->DebugDraw();
	}
}