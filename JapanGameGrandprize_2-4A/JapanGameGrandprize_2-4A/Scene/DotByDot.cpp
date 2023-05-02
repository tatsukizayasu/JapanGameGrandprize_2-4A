#include "DotByDot.h"
#include "../PadInput.h"
#include "GameMain.h"
#include "../Undead.h"
#include"../EnemySlime.h"
#include"../EnemyGhost.h"
#include"../Harpy.h"
#include "../Mage.h"
#include "../Torrent.h"
#include "../EnemySlimeBoss.h"

#define ENEMY_NUM 3

enum class CHARACTER_STATE
{
	IDOL,   //アイドル状態
	MOVE,   //移動
	FALL,	//落下
	ATTACK, //攻撃
	DEATH,  //死亡
};



//-----------------------------------
//コンストラクタ
//-----------------------------------
DotByDot::DotByDot()
{
	state = 0;
	enemy = new EnemyBase * [ENEMY_NUM];
	Location spawn_location;
	spawn_location.y = 100;
	spawn_location.x = 280;
	enemy[0] = new Undead(spawn_location);
	spawn_location.x = 500;
	enemy[1] = new EnemyGhost(spawn_location);
	spawn_location.x = 700;
	enemy[2] = new EnemySlime(spawn_location);

	player = new Player();
	element = new Stage_Element();

	element->InitDemo({100.0f,400.0f});


	font = CreateFontToHandle("DotByDotFont", 32, 1, DX_FONTTYPE_NORMAL);
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

	DeleteFontToHandle(font);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* DotByDot::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		return new GameMain(1);
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		state++;
	}

#ifdef _DEBUG
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i]->Update(static_cast<ENEMY_STATE>(state % 5));
	}

	player->Update(static_cast<PLAYER_STATE>(state % 6));
#endif // _DEBUG

	element->Update(player);

	return this;

	
}

//-----------------------------------
// 描画
//-----------------------------------
void DotByDot::Draw() const
{
	SetBackgroundColor(0,255,255);
#ifdef _DEBUG
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i]->DebugDraw();
	}

	player->DebugDraw();
#endif // _DEBUG

	element->Draw();

	DrawFormatStringToHandle(1160, 660, 0x000000, font, "%s", str[state % 5]);

}